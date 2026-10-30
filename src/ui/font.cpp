// Font renderer leaves, hand-decompiled from SLUS_216.21 (game/include/p3fes/game/font.h; docs/ANALYSIS/
// 20_menu_ui.md sections 5.2-5.3). Phase 5: these replace the recompiled bodies listed under "font" in
// game/replaced.txt; tests/game/test_font.cpp runs each against its __recomp body (every glyph of the real
// FONT0.FNT through both decoders, random line chains, random tag strings).
//
// Virtual time per ADR-0013: guest::enter / charge / backedge mirror the `ctx.cycles += N` lines and the
// back-edge checks of recomp/generated/fn_0033_003ac6f0_003b64c0.cpp. A block's cost is charged before the
// calls it contains, as the recompiled body does. The bodies are written with the original's block
// structure (labels where the compiler's loops enter at their test), so the check points fall in the same
// places. Still-recompiled callees (memcpy, K_Assert / K_Abort, frFontCacheGlyph, the tag handlers of
// sFrTagTable) go through guest::call / rt::lookup_func.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 41 of the 48 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: scratch GPRs 25, frame/spills 11, $v0 4, faults
// only 1); the others are the hand-written versions this header describes.
//
// Readability pass (read_text, 2026-10-21): the 41 generated bodies keep every statement, charge, check point and call
// of p3fes_handgen's output in the same order on every path; on top of it they name what they touch (text_view.h:
// glyph_node:: / line_node:: / fnt_style:: / raster_slot:: / tag_scan:: offsets, `gp_off(font::kTagFlags)` for a $gp
// offset, `k_assert(a0, a1, pc, kFrFontFile, line)` for the four-statement K_Assert call), say what each block does,
// and replace the generator's gotos by if / else / break with a host bool where paths merge (frFontSetGlyphMetrics,
// frFontKerningAdjust, frFontProcessTagEx, frFontRasterAgeSlots, frFontRasterLookup: none left). The row walks of the
// chain helpers read `for (;;) { test; if (!a) break; check; ...; if (!b) break; ...; next }`, the original's blocks in
// order. Each function's comment gives its role.
#include "p3fes/game/font.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/ui.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/text_view.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_frFontProcessTagEx_003b2a30(p3fes::EEContext&);
void fn_frFontRasterLookup_003b3e00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in retail
void fn_sub_19D400_0019d400(p3fes::EEContext&);  // K_Abort(msg, file, line): `jr $ra` in retail
void fn_frFontCacheGlyph_003b0430(p3fes::EEContext&);
void fn_rbAlloc_003b46b0(p3fes::EEContext&);             // hand-written below (the shim)
void fn_frFontSetGlyphMetrics_003b01d0(p3fes::EEContext&);  // hand-written below (the shim)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tview;  // text_view.h: la / k_assert / hi / lo / gp_off and the record offsets

namespace {

using namespace font;

u32 ld32(const EEContext& ctx, u32 va) { return guest::load<u32>(ctx, va); }
void st32(EEContext& ctx, u32 va, u32 v) { guest::store<u32>(ctx, va, v); }

}  // namespace

// ======================================= fmGslCont.c ====================================================

// 0x003B4770 fmGslGetGlyphBlocks -- 52 bytes; leaf frame (no stack)
// fmGslGetGlyphBlocks(block, out): the three regions of a style's Huffman block, which follow each other: out =
// {block + hdr[0] (the dictionary), + hdr[0] + hdr[1] (the offsets), + that + hdr[6] (the bit stream)}. One block
// of 13.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void fmGslGetGlyphBlocks(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x003b4770
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(t0, a0, gsl_blocks::kDictOffset);
    lw(v1, a0, gsl_blocks::kDictBytes);
    a3 = addu(t0, v1);  // the offsets
    lw(v1, a0, gsl_blocks::kOffsetsBytes);
    a2 = addu(a3, v1);  // the stream
    v1 = addu(a0, t0);
    sw(v1, a1, gsl_blocks::kOutDict);
    v1 = addu(a0, a3);
    sw(v1, a1, gsl_blocks::kOutOffsets);
    v1 = addu(a0, a2);
    sw(v1, a1, gsl_blocks::kOutStream);
}

// 0x003B47B0 fmGslDecodeGlyph -- 360 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// fmGslDecodeGlyph(dst, glyph, -, blocks): Huffman-decodes one glyph's bitmap bytes into dst and returns their
// count (also kept in font::kLastDecodedBytes). The bit range of the glyph is offsets[glyph] ..
// offsets[glyph + 1], both memcpy'd into the frame (sp+0x9C, sp+0x98: the table may be unaligned in a style's
// file). The stream is read as u16 words LSB first through a 17-bit register with a sentinel bit (value 1 =
// empty -> refill). Dictionary nodes are 6 bytes {u16, u16 child0, u16 child1}; the bit picks the child; a node
// whose child0 is 0 is a leaf whose symbol is the byte at +4, copied with memcpy(dst + n, sym, 1), and the walk
// restarts at node 0. Blocks: entry 44 (both memcpys); per bit 12, leaf 7, refill 6, loop tail 3; exit 14.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void fmGslDecodeGlyph(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::sq, hg::srav, hg::srl, hg::subu, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b47b0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s7 = a0;  // dst
    s0 = a1;  // glyph
    s1 = a3;  // blocks {dict, offsets, stream}
    lw(s5, a3, gsl_blocks::kOutDict);  // s5 = the dictionary
    s3 = 0;   // bytes written
    // memcpy(frame + 0x9C, &offsets[glyph], 4); memcpy(frame + 0x98, &offsets[glyph + 1], 4)
    v1 = sll(s0, 2);
    lw(v0, a3, gsl_blocks::kOutOffsets);
    a1 = addu(v0, v1);
    a0 = addiu(sp, 0x9C);
    a2 = 4;
    jal(ctx, 0x3B4800u, gen::fn_memcpy_00521250);
    v0 = addiu(s0, 1);
    v1 = sll(v0, 2);
    lw(v0, s1, gsl_blocks::kOutOffsets);
    a1 = addu(v0, v1);
    a0 = addiu(sp, 0x98);
    a2 = 4;
    jal(ctx, 0x3B4820u, gen::fn_memcpy_00521250);
    // s0 = v0 = &node0.child0; s6 = the stream; s2 = the word index (first bit >> 4); s4 = that word | the
    // sentinel, shifted to the first bit (first bit & 15); s1 = the bit count
    s0 = addiu(s5, gsl_blocks::kNodeChild0);
    v0 = s0;
    lw(s6, s1, gsl_blocks::kOutStream);
    lw(a1, sp, 0x9C);
    s2 = srl(a1, 4);
    v1 = sll(s2, 1);
    v1 = addu(s6, v1);
    lhu(a0, v1, 0);
    v1 = gsl_blocks::kSentinel;
    a0 = a0 | v1;
    v1 = a1 & 0xF;
    s4 = srav(a0, v1);
    lw(v1, sp, 0x98);
    s1 = subu(v1, a1);
    for (;;) {
        // 0x003b4860: node = dict + 6 * node->child[bit]; v0 = &node.child0
        charge(ctx, 12);
        v1 = s4 & 0x1;
        v1 = sll(v1, 1);
        v0 = addu(v0, v1);
        lhu(v1, v0, 0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v1 = addu(s5, v0);
        v0 = addiu(v1, 2);
        lhu(v1, v1, 2);
        if (v1 == 0) {
            // 0x003b4890: a leaf: memcpy(dst + n++, &node.symbol, 1); restart at node 0
            charge(ctx, 7);
            a0 = addu(s7, s3);
            a1 = addiu(v0, 2);
            a2 = 1;
            jal(ctx, 0x3B489Cu, gen::fn_memcpy_00521250);
            s3 = addiu(s3, 1);
            v0 = s0;
        }
        // 0x003b48ac: next bit; the register empty (only the sentinel left)?
        charge(ctx, 4);
        s4 = srl(s4, 1);
        v1 = 1;
        if (s4 == v1) {
            // 0x003b48bc: refill: the next stream word | the sentinel
            charge(ctx, 6);
            s2 = addiu(s2, 1);
            v1 = sll(s2, 1);
            v1 = addu(s6, v1);
            lhu(a0, v1, 0);
            v1 = gsl_blocks::kSentinel;
            s4 = a0 | v1;
        }
        // 0x003b48d4: until the bit count runs out
        charge(ctx, 3);
        s1 = addiu(s1, -1);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003b48e0: kLastDecodedBytes = n; return n
    charge(ctx, 14);
    sw(s3, gp, gp_off(font::kLastDecodedBytes));
    v0 = s3;
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003B4520 fmGslAllocEntry -- 88 bytes; leaf frame (no stack)
// fmGslAllocEntry: unlinks the first entry of the free GS list (the container's +0x1C) and returns it; 0 when the
// list is empty (the first entry's +0 is 0: the container itself). The list is circular and doubly linked through
// +0x18 (prev) / +0x1C (next); font::kGslFreeCount counts the free entries. Blocks: entry 6; empty 3; unlink 11;
// return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void fmGslAllocEntry_regs(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003b4520
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = hi(font::kGslList);
    lw(v0, v0, lo(font::kGslList));
    lw(v0, v0, gsl_entry::kNext);  // v0 = the first entry
    lw(v1, v0, gsl_entry::kWord0);
    if (v1 != 0) {
        // 0x003b4544: entry->prev->next = entry->next; entry->next->prev = entry->prev; --free count
        charge(ctx, 11);
        lw(a0, v0, gsl_entry::kNext);
        lw(v1, v0, gsl_entry::kPrev);
        sw(a0, v1, gsl_entry::kNext);
        lw(a0, v0, gsl_entry::kPrev);
        lw(v1, v0, gsl_entry::kNext);
        sw(a0, v1, gsl_entry::kPrev);
        v1 = hi(font::kGslFreeCount);
        lw(v1, v1, lo(font::kGslFreeCount));
        a0 = addiu(v1, -1);
        v1 = hi(font::kGslFreeCount);
        sw(a0, v1, lo(font::kGslFreeCount));
    } else {
        // 0x003b4538: empty: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b4570: return
    charge(ctx, 2);
}

// 0x003B4580 fmGslReleaseEntry -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// fmGslReleaseEntry(entry): links the entry back in right after the GS-list container and returns the new free
// count. K_Assert("fmGslCont.c", 194) on a null entry (`jr $ra` in retail: the stores then go through address 0).
// Blocks: entry 6; null 5; link 17.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void fmGslReleaseEntry(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b4580
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // entry
    if (s0 == 0) {
        // 0x003b4598: K_Assert(entry != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3B45A4u, kGslContFile, 194);
    }
    // 0x003b45ac: entry->prev = container; entry->next = container->next; both neighbours point at it; ++free count
    charge(ctx, 17);
    v0 = hi(font::kGslList);
    lw(v1, v0, lo(font::kGslList));
    lw(v0, v1, gsl_entry::kNext);
    sw(v1, s0, gsl_entry::kPrev);
    sw(v0, s0, gsl_entry::kNext);
    sw(s0, v1, gsl_entry::kNext);
    sw(s0, v0, gsl_entry::kPrev);
    v0 = hi(font::kGslFreeCount);
    lw(v0, v0, lo(font::kGslFreeCount));
    v0 = addiu(v0, 1);
    v1 = hi(font::kGslFreeCount);
    sw(v0, v1, lo(font::kGslFreeCount));
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B46B0 rbAlloc -- 52 bytes; leaf frame (no stack)
// rbAlloc(ring): pops the ring's free head record and returns its payload (record + 8); 0 when the head is the
// ring's end (its +0 is 0). Blocks: entry 4; empty 3 / pop 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void rbAlloc(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003b46b0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, ring::kHead);
    lw(v0, v1, ring::kWord0);
    if (v0 != 0) {
        // 0x003b46cc: ring->head = rec->next; rec->next = 0; return rec + 8
        charge(ctx, 4);
        lw(v0, v1, ring::kNext);
        sw(v0, a0, ring::kHead);
        sw(zero, v1, ring::kNext);
        v0 = addiu(v1, ring::kPayload);
    } else {
        // 0x003b46c0: empty: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b46dc: return
    charge(ctx, 2);
}

// 0x003B46F0 rbFree -- 72 bytes; leaf frame (no stack)
// rbFree(payload, ring): pushes the payload's record (payload - 8) back on the ring and returns 1; 0 for a null
// payload or a record that is still linked (its next is non-zero). Blocks: entry 2; null 3; check 4; still
// linked 3 / push 4; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void rbFree(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b46f0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x003b4704: v1 = the record; is it handed out (next == 0)?
        charge(ctx, 4);
        v1 = addiu(a0, -ring::kPayload);
        lw(v0, a0, ring::kNext - ring::kPayload);
        if (v0 == 0) {
            // 0x003b4720: rec->next = ring->head; ring->head = rec; return 1
            charge(ctx, 4);
            lw(v0, a1, ring::kHead);
            sw(v0, v1, ring::kNext);
            sw(v1, a1, ring::kHead);
            v0 = 1;
        } else {
            // 0x003b4714: still linked: return 0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003b46f8: null: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b4730: return
    charge(ctx, 2);
}

// ========================================= frFont.c =====================================================

// 0x003B01D0 frFontSetGlyphMetrics -- 460 bytes; leaf frame (no stack)
// frFontSetGlyphMetrics(glyph, index): the glyph node's scaled sizes (+0x18 / +0x19) and advance (+0xC) = the
// style's size (32 = 1:1). With the proportional flag (bit 0 of +0x17), a width table in the style's .FNT and a
// glyph inside it whose right edge is non-zero: w = right - left (+4 for '!' and '1', then +2 below glyph 454,
// +3 from it), x16 = left * 16 (- 32 for '!' / '1'); x offset (+4) = -x16 * size / 32, advance = w * size / 32
// (rounded toward zero), then the global x / y scales (/128) when positive. No calls.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontSetGlyphMetrics(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::lb, hg::lbu, hg::lw, hg::mult, hg::sb,
          hg::sll, hg::slt, hg::slti, hg::sra, hg::subu, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28};
    // 0x003b01d0: t0 = the glyph's style record; the sizes and the advance from the style's size
    enter(ctx, 21);  // entry check point + this block's cycles
    lbu(a3, a0, glyph_node::kStyle);
    a2 = sll(a3, 5);
    la(v1, font::kStyles);
    t0 = addu(v1, a2);
    a2 = addiu(gp, gp_off(font::kStyleSizes));  // &sizes
    v1 = addu(a2, a3);
    lb(v1, v1, 0);
    sb(v1, a0, 24);  // size x
    lbu(v1, a0, glyph_node::kStyle);
    v1 = addu(a2, v1);
    lb(v1, v1, 0);
    sb(v1, a0, 25);  // size y
    lbu(v1, a0, glyph_node::kStyle);
    v1 = addu(a2, v1);
    lb(v1, v1, 0);
    sw(v1, a0, glyph_node::kAdvance);
    lbu(v1, a0, glyph_node::kFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x003b0224: proportional: does the style's .FNT have a width table?
        charge(ctx, 4);
        lw(v1, t0, fnt_style::kFnt);
        lbu(v1, v1, fnt_hdr::kHasWidths);
        if (v1 != 0) {
            // 0x003b0234: is the glyph inside it (2 * index < table bytes)?
            charge(ctx, 5);
            a3 = sll(a1, 1);
            lw(v1, t0, fnt_style::kWidthBytes);
            at = slt(a3, v1);
            if (at != 0) {
                // 0x003b0248: a1 = right edge (s8)
                charge(ctx, 6);
                lw(a2, t0, fnt_style::kWidthTable);
                v1 = addiu(a2, 1);
                v1 = addu(v1, a3);
                lb(a1, v1, 0);
                if (a1 != 0) {
                    // 0x003b0260: t1 = left * 16, t0 = w = right - left; a1 = the text code (index + 32)
                    charge(ctx, 9);
                    v1 = addu(a2, a3);
                    lb(v1, v1, 0);
                    t1 = sll(v1, 4);
                    t0 = subu(a1, v1);
                    a2 = sra(a3, 1);
                    a1 = addiu(a2, 32);
                    v1 = text_code::kExclam;
                    bool narrow = true;  // '!' or '1'
                    if (a1 != v1) {
                        // 0x003b0284: '1'?
                        charge(ctx, 3);
                        v1 = text_code::kOne;
                        narrow = a1 == v1;
                        if (!narrow) {
                            // 0x003b0290
                            charge(ctx, 2);
                        }
                    }
                    if (narrow) {
                        // 0x003b0298: '!' / '1': x16 -= 32, w += 4
                        charge(ctx, 2);
                        t1 = addiu(t1, -32);
                        t0 = addiu(t0, 4);
                    }
                    // 0x003b02a0: w += 2 below glyph 454, += 3 from it
                    charge(ctx, 3);
                    v1 = slti(a2, 454);
                    if (v1 != 0) {
                        // 0x003b02b8
                        charge(ctx, 1);
                        t0 = addiu(t0, 2);
                    } else {
                        // 0x003b02ac
                        charge(ctx, 3);
                        t0 = addiu(t0, 3);
                    }
                    // 0x003b02bc: x offset = -x16 * size / 32
                    charge(ctx, 9);
                    lbu(a1, a0, glyph_node::kStyle);
                    v1 = addiu(gp, gp_off(font::kStyleSizes));  // &sizes
                    v1 = addu(v1, a1);
                    lb(a1, v1, 0);
                    v1 = subu(0, t1);
                    mult(a1, v1, a1);
                    v1 = sra(a1, 5);
                    if (i64(a1) < 0) {
                        // 0x003b02e0: round toward zero
                        charge(ctx, 2);
                        v1 = addiu(a1, 31);
                        v1 = sra(v1, 5);
                    }
                    // 0x003b02e8: advance = w * size / 32
                    charge(ctx, 9);
                    sw(v1, a0, glyph_node::kOffsetX);
                    lbu(a1, a0, glyph_node::kStyle);
                    v1 = addiu(gp, gp_off(font::kStyleSizes));  // &sizes
                    v1 = addu(v1, a1);
                    lb(v1, v1, 0);
                    mult(a1, t0, v1);
                    v1 = sra(a1, 5);
                    if (i64(a1) < 0) {
                        // 0x003b030c: round toward zero
                        charge(ctx, 2);
                        v1 = addiu(a1, 31);
                        v1 = sra(v1, 5);
                    }
                    // 0x003b0314: the x scale
                    charge(ctx, 4);
                    sw(v1, a0, glyph_node::kAdvance);
                    lw(a1, gp, gp_off(font::kScaleX));
                    if (i64(a1) > 0) {
                        // 0x003b0324: size x = size x * scale / 128
                        charge(ctx, 5);
                        lbu(v1, a0, 24);
                        mult(a1, v1, a1);
                        v1 = sra(a1, 7);
                        if (i64(a1) < 0) {
                            // 0x003b0338
                            charge(ctx, 2);
                            v1 = addiu(a1, 127);
                            v1 = sra(v1, 7);
                        }
                        // 0x003b0340: advance = advance * scale / 128
                        charge(ctx, 7);
                        sb(v1, a0, 24);
                        lw(a1, a0, glyph_node::kAdvance);
                        lw(v1, gp, gp_off(font::kScaleX));
                        mult(a1, a1, v1);
                        v1 = sra(a1, 7);
                        if (i64(a1) < 0) {
                            // 0x003b035c
                            charge(ctx, 2);
                            v1 = addiu(a1, 127);
                            v1 = sra(v1, 7);
                        }
                        // 0x003b0364
                        charge(ctx, 1);
                        sw(v1, a0, glyph_node::kAdvance);
                    }
                    // 0x003b0368: the y scale
                    charge(ctx, 3);
                    lw(a1, gp, gp_off(font::kScaleY));
                    if (i64(a1) > 0) {
                        // 0x003b0374: size y = size y * scale / 128
                        charge(ctx, 5);
                        lbu(v1, a0, 25);
                        mult(a1, v1, a1);
                        v1 = sra(a1, 7);
                        if (i64(a1) < 0) {
                            // 0x003b0388
                            charge(ctx, 2);
                            v1 = addiu(a1, 127);
                            v1 = sra(v1, 7);
                        }
                        // 0x003b0390
                        charge(ctx, 1);
                        sb(v1, a0, 25);
                    }
                }
            }
        }
    }
    // 0x003b0394: return
    charge(ctx, 2);
}

// 0x003B05C0 frFontInitLineNode -- 88 bytes; leaf frame (no stack)
// frFontInitLineNode(node): a blank line node: everything 0 except the code ' ' (0x20), alpha 0xFF and the chain's
// first line (+0x2C) pointing at the node itself. One block of 22.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontInitLineNode(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sb, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003b05c0
    enter(ctx, 22);  // entry check point + this block's cycles
    sw(zero, a0, line_node::kX);
    sw(zero, a0, line_node::kY);
    sb(zero, a0, line_node::kSpacing);
    sw(zero, a0, line_node::kGlyphCount);
    sw(zero, a0, line_node::kWord20);
    v1 = line_node::kOpaque;
    sb(v1, a0, line_node::kAlpha);
    v1 = line_node::kBlankCode;
    sh(v1, a0, line_node::kCode);
    sw(zero, a0, line_node::kNext);
    sw(zero, a0, line_node::kChainNext);
    sw(a0, a0, line_node::kChainFirst);  // a chain of one
    sw(zero, a0, line_node::kGlyphs);
    sw(zero, a0, line_node::kStyleGlyph);
    sw(zero, a0, 24);
    sw(zero, a0, 48);
    sw(zero, a0, 52);
    sw(zero, a0, 56);
    sw(zero, a0, 60);
    sw(zero, a0, line_node::kDirty);
}

u32 frFontCreateGlyphNode(EEContext& ctx, u32 code, u32 style, u32 colour, u32 mode) {
    // 0x3B0620 (proposed in 20_menu_ui.md: frFontCreateGlyphNode, the master's name). The glyph index:
    //   code < 0x80: ' ' -> 0x1F7, else code - 0x20;  code >= 0x80: (((code - 0x8080) & 0xFF00) >> 1) +
    //   ((code - 0x8080) & 0x7F)  (two-byte codes 80 80 .. map linearly, 128 glyphs per lead byte);
    //   >= the style's glyph count -> 0x147.
    // An empty ring calls K_Abort (`jr $ra` in retail) and the stores land at address 0, as in retail.
    // Descenders g j p q y Q (index + 32) get y offset 16 when flag bit 4 is set.
    //
    // Register for register (the shop replay route caught the earlier host-variable version: it never opened the
    // 96-byte frame, so the `sq` spills of $s0..$s4 were missing from a thread stack in the heap). Frame 96:
    // $s0..$s4 as 128-bit `sq` at +0..+64, $ra at +80. $s4 = code, $s3 = style, $s2 = colour, $s1 = the node,
    // $s0 = mode, then the glyph index. Callees go through their entry points with the original links.
    using ee::core::sext32;
    ee::core::set_gpr64(ctx, GPR_A0, sext32(code));
    ee::core::set_gpr64(ctx, GPR_A1, sext32(style));
    ee::core::set_gpr64(ctx, GPR_A2, sext32(colour));
    ee::core::set_gpr64(ctx, GPR_A3, sext32(mode));
    rt::check_events(ctx);
    ctx.cycles += 23;
    rt::addiu(ctx, 29, 29, -96);
    rt::sd(ctx, 31, 29, 80);
    rt::sq(ctx, 20, 29, 64);
    rt::sq(ctx, 19, 29, 48);
    rt::sq(ctx, 18, 29, 32);
    rt::sq(ctx, 17, 29, 16);
    rt::sq(ctx, 16, 29, 0);
    rt::daddu(ctx, 20, 4, 0);
    rt::daddu(ctx, 19, 5, 0);
    rt::daddu(ctx, 18, 6, 0);
    rt::daddu(ctx, 16, 7, 0);
    rt::lui(ctx, 2, 0x96u);
    rt::lw(ctx, 4, 2, -20964);  // the glyph ring (kGlyphRing)
    rt::jal(ctx, 0x3b0654u);
    recomp_gen::fn_rbAlloc_003b46b0(ctx);
    rt::daddu(ctx, 17, 2, 0);  // the node
    rt::lui(ctx, 2, 0x96u);
    rt::lw(ctx, 2, 2, -20972);  // ++ the created-glyph count (kGlyphCreatedCount)
    rt::addiu(ctx, 3, 2, 1);
    rt::lui(ctx, 2, 0x96u);
    rt::sw(ctx, 3, 2, -20972);
    if (rt::cmp_eq(ctx, 17, 0)) {
        // an empty ring: K_Abort (`jr $ra` in retail) and the stores below land at address 0, as in retail
        ctx.cycles += 7;
        rt::lui(ctx, 4, 0x6au);
        rt::addiu(ctx, 4, 4, 10336);
        rt::lui(ctx, 5, 0x6au);
        rt::addiu(ctx, 5, 5, 10032);
        rt::addiu(ctx, 6, 0, 1859);
        rt::jal(ctx, 0x3b0690u);
        recomp_gen::fn_sub_19D400_0019d400(ctx);
    }
    // the node's fields
    ctx.cycles += 20;
    rt::sh(ctx, 20, 17, 0);     // +0 code
    rt::sb(ctx, 19, 17, 21);    // +21 style
    rt::sw(ctx, 0, 17, 4);
    rt::sw(ctx, 0, 17, 8);
    rt::sw(ctx, 0, 17, 12);
    rt::sb(ctx, 18, 17, 20);    // +20 colour
    rt::addiu(ctx, 2, 0, -256);
    rt::sw(ctx, 2, 17, 16);     // +16 0xFFFFFF00
    rt::sb(ctx, 16, 17, 22);    // +22 mode
    rt::lh(ctx, 2, 28, -22512);
    rt::sb(ctx, 2, 17, 23);     // +23 the default glyph flags
    rt::sh(ctx, 0, 17, 2);
    rt::sw(ctx, 0, 17, 28);
    rt::sw(ctx, 0, 17, 32);
    rt::sw(ctx, 0, 17, 36);
    rt::sw(ctx, 0, 17, 40);
    // the glyph index into $s0
    rt::lhu(ctx, 3, 17, 0);
    rt::slti(ctx, 1, 3, 128);
    if (!rt::cmp_eq(ctx, 1, 0)) {
        ctx.cycles += 3;
        rt::addiu(ctx, 2, 0, 32);
        if (!rt::cmp_ne(ctx, 3, 2)) {
            ctx.cycles += 3;
            rt::addiu(ctx, 16, 0, 503);  // ' ' -> kGlyphSpace
        } else {
            ctx.cycles += 3;
            rt::addiu(ctx, 16, 3, -32);
        }
    } else {
        ctx.cycles += 6;  // two-byte codes 80 80 .. : 128 glyphs per lead byte
        rt::addiu(ctx, 2, 3, -32768);
        rt::addiu(ctx, 4, 2, -128);
        rt::andi(ctx, 2, 4, 0xff00u);
        rt::sra(ctx, 3, 2, 1);
        rt::andi(ctx, 2, 4, 0x7fu);
        rt::addu(ctx, 16, 3, 2);
    }
    // >= the style's glyph count -> kGlyphReplacement
    ctx.cycles += 10;
    rt::andi(ctx, 2, 19, 0xffu);
    rt::sll(ctx, 3, 2, 5);
    rt::lui(ctx, 2, 0x96u);
    rt::addiu(ctx, 2, 2, -21264);
    rt::addu(ctx, 2, 2, 3);
    rt::lw(ctx, 2, 2, 4);
    rt::lhu(ctx, 2, 2, 14);
    rt::slt(ctx, 1, 16, 2);
    if (!rt::cmp_ne(ctx, 1, 0)) {
        ctx.cycles += 1;
        rt::addiu(ctx, 16, 0, 327);
    }
    ctx.cycles += 13;
    rt::daddu(ctx, 4, 17, 0);
    rt::daddu(ctx, 5, 16, 0);
    rt::jal(ctx, 0x3b0758u);
    recomp_gen::fn_frFontCacheGlyph_003b0430(ctx);
    rt::sw(ctx, 2, 17, 28);     // +28 the cached glyph
    rt::daddu(ctx, 4, 17, 0);
    rt::daddu(ctx, 5, 16, 0);
    rt::jal(ctx, 0x3b076cu);
    recomp_gen::fn_frFontSetGlyphMetrics_003b01d0(ctx);
    rt::lbu(ctx, 2, 17, 23);
    rt::andi(ctx, 2, 2, 0x10u);
    if (!rt::cmp_eq(ctx, 2, 0)) {
        // flag bit 4: descenders y q p j g Q (index + 32) get y offset 16 at +8
        ctx.cycles += 5;
        rt::daddu(ctx, 4, 0, 0);
        rt::addiu(ctx, 3, 16, 32);
        static constexpr s16 kDescenders[6] = {121, 113, 112, 106, 103, 81};
        bool hit = false;
        for (int i = 0; i < 6 && !hit; ++i) {
            if (i > 0) ctx.cycles += 3;
            rt::addiu(ctx, 2, 0, kDescenders[i]);
            hit = rt::cmp_eq(ctx, 3, 2);
        }
        if (hit) {
            ctx.cycles += 1;
            rt::addiu(ctx, 4, 0, 1);
        } else {
            ctx.cycles += 2;
        }
        ctx.cycles += 4;
        rt::dsll32(ctx, 2, 4, 24);
        rt::dsra32(ctx, 2, 2, 24);
        if (!rt::cmp_ne(ctx, 2, 0)) {
            ctx.cycles += 3;
            rt::daddu(ctx, 2, 0, 0);
        } else {
            ctx.cycles += 1;
            rt::addiu(ctx, 2, 0, 16);
        }
        ctx.cycles += 5;
        rt::dsll32(ctx, 2, 2, 24);
        rt::dsra32(ctx, 2, 2, 24);
        rt::sw(ctx, 2, 17, 8);
    } else {
        ctx.cycles += 1;
        rt::sw(ctx, 0, 17, 8);
    }
    ctx.cycles += 10;
    rt::daddu(ctx, 2, 17, 0);
    rt::ld(ctx, 31, 29, 80);
    rt::lq(ctx, 20, 29, 64);
    rt::lq(ctx, 19, 29, 48);
    rt::lq(ctx, 18, 29, 32);
    rt::lq(ctx, 17, 29, 16);
    rt::lq(ctx, 16, 29, 0);
    rt::addiu(ctx, 29, 29, 96);
    return ee::core::gpr32(ctx, GPR_V0);
}

// 0x003B0840 frFontKerningAdjust -- 292 bytes; leaf frame (no stack)
// frFontKerningAdjust(glyph): the kerning between a glyph and the next one (+0x24), styles 0 and 1 only: a / e /
// o / u (or the two-byte 80C1 / 80C5 / 80CF / 80D5) before 'T' / 80B4 -> 3, before 'Y' / 80B9 -> 2, each
// scaled by the x scale / 128 when it is positive. Returns 0 otherwise. The chains of compares are the
// original's, one block per compare.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontKerningAdjust(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::lbu, hg::lhu, hg::lw, hg::sll, hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x003b0840: a2 = the next glyph; result 0; a1 = the style
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a2, a0, 36);
    v0 = 0;
    lbu(a1, a0, glyph_node::kStyle);
    bool kerned_style = true;  // style 0 or 1
    if (a1 != 0) {
        // 0x003b0854: style 1?
        charge(ctx, 3);
        v1 = 1;
        kerned_style = a1 == v1;
    }
    if (kerned_style) {
        // 0x003b0860: a next glyph?
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x003b0868: is this glyph a / e / o / u?
            charge(ctx, 4);
            lhu(a0, a0, glyph_node::kCode);
            v1 = text_code::kU2;
            bool vowel = a0 == v1;
            if (!vowel) {
                // 0x003b0878
                charge(ctx, 3);
                v1 = text_code::kO2;
                vowel = a0 == v1;
            }
            if (!vowel) {
                // 0x003b0884
                charge(ctx, 3);
                v1 = text_code::kE2;
                vowel = a0 == v1;
            }
            if (!vowel) {
                // 0x003b0890
                charge(ctx, 3);
                v1 = text_code::kA2;
                vowel = a0 == v1;
            }
            if (!vowel) {
                // 0x003b089c
                charge(ctx, 3);
                v1 = text_code::kU;
                vowel = a0 == v1;
            }
            if (!vowel) {
                // 0x003b08a8
                charge(ctx, 3);
                v1 = text_code::kO;
                vowel = a0 == v1;
            }
            if (!vowel) {
                // 0x003b08b4
                charge(ctx, 3);
                v1 = text_code::kE;
                vowel = a0 == v1;
            }
            if (!vowel) {
                // 0x003b08c0
                charge(ctx, 3);
                v1 = text_code::kA;
                vowel = a0 == v1;
            }
            if (!vowel) {
                // 0x003b08cc: no kerning
                charge(ctx, 2);
            } else {
                // 0x003b08d4: the next glyph T?
                charge(ctx, 4);
                lhu(a0, a2, glyph_node::kCode);
                v1 = text_code::kT;
                bool before_t = a0 == v1;
                if (!before_t) {
                    // 0x003b08e4
                    charge(ctx, 3);
                    v1 = text_code::kT2;
                    before_t = a0 == v1;
                }
                if (before_t) {
                    // 0x003b08f0: 3, times the x scale / 128
                    charge(ctx, 4);
                    v0 = 3;
                    lw(v1, gp, gp_off(font::kScaleX));
                    if (i64(v1) > 0) {
                        // 0x003b0900
                        charge(ctx, 5);
                        v0 = sll(v1, 1);
                        v1 = addu(v0, v1);
                        v0 = sra(v1, 7);
                        if (i64(v1) < 0) {
                            // 0x003b0914
                            charge(ctx, 2);
                            v0 = addiu(v1, 127);
                            v0 = sra(v0, 7);
                        }
                    }
                }
                // 0x003b091c: the next glyph Y?
                charge(ctx, 3);
                v1 = text_code::kY;
                bool before_y = a0 == v1;
                if (!before_y) {
                    // 0x003b0928
                    charge(ctx, 3);
                    v1 = text_code::kY2;
                    before_y = a0 == v1;
                }
                if (before_y) {
                    // 0x003b0934: 2, times the x scale / 128
                    charge(ctx, 4);
                    v0 = 2;
                    lw(v1, gp, gp_off(font::kScaleX));
                    if (i64(v1) > 0) {
                        // 0x003b0944
                        charge(ctx, 4);
                        v1 = sll(v1, 1);
                        v0 = sra(v1, 7);
                        if (i64(v1) < 0) {
                            // 0x003b0954
                            charge(ctx, 2);
                            v0 = addiu(v1, 127);
                            v0 = sra(v0, 7);
                        }
                    }
                }
            }
        }
    }
    // 0x003b095c: return
    charge(ctx, 2);
}

// 0x003B0BB0 frFontLineSetAlpha -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// frFontLineSetAlpha(line, alpha): alpha (+2) = alpha on the line and every line after it (+0x24).
// K_Assert("frFont.c", 2072) on a null line. Blocks: entry 8; null 7; per line 2; loop test 5; exit 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontLineSetAlpha(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sb, hg::sd,
          hg::sq;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0bb0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // line
    s0 = a1;  // alpha
    if (s1 == 0) {
        // 0x003b0bd0: K_Assert(line != 0)
        charge(ctx, 7);
        k_assert(a0, a1, 0x3B0BDCu, kFrFontFile, 2072);
    }
    for (;;) {
        // 0x003b0bf4: while (line)
        charge(ctx, 5);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b0bec: line->alpha = alpha; line = line->next
        charge(ctx, 2);
        sb(s0, s1, line_node::kAlpha);
        lw(s1, s1, line_node::kNext);
    }
    // 0x003b0c08: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B0C20 frFontNodeSetCode -- 80 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// frFontNodeSetCode(node, code): node->code (+0) = code. K_Assert("frFont.c", 2092) on a null node (the store
// then goes to address 0). Blocks: entry 8; null 5; store 7.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontNodeSetCode(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sh, hg::sq;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0c20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // node
    s0 = a1;  // code
    if (s1 == 0) {
        // 0x003b0c40: K_Assert(node != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3B0C4Cu, kFrFontFile, 2092);
    }
    // 0x003b0c54: node->code = code; epilogue
    charge(ctx, 7);
    sh(s0, s1, line_node::kCode);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B0C70 frFontLineResetAlpha -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// frFontLineResetAlpha(line): line->dirty (+0x40) = 1 (stored before the null check), then alpha 0xFF on the line
// and every line after it. K_Assert("frFont.c", 2072) on a null line. Blocks: entry 8; null 7; per line 3; loop
// test 4; exit 5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontLineResetAlpha(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sb, hg::sd,
          hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0c70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 1;
    sw(v1, a0, line_node::kDirty);
    s0 = a0;  // line
    if (a0 == 0) {
        // 0x003b0c90: K_Assert(line != 0)
        charge(ctx, 7);
        k_assert(a0, a1, 0x3B0C9Cu, kFrFontFile, 2072);
    }
    for (;;) {
        // 0x003b0cb8: while (line)
        charge(ctx, 4);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b0cac: line->alpha = 255; line = line->next
        charge(ctx, 3);
        v1 = line_node::kOpaque;
        sb(v1, s0, line_node::kAlpha);
        lw(s0, s0, line_node::kNext);
    }
    // 0x003b0cc8: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B0CE0 frFontLineSetStyle -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// frFontLineSetStyle(line, style): every glyph's style (+0x15) on the line and the lines after it.
// K_Assert("frFont.c", 2167) on a null line. Blocks: entry 8; null 7; per line 3 + inner test 5 per glyph (+2
// body) + 1; outer test 2; exit 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontLineSetStyle(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sb, hg::sd,
          hg::sq;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0ce0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // line
    s0 = a1;  // style
    if (s1 == 0) {
        // 0x003b0d00: K_Assert(line != 0)
        charge(ctx, 7);
        k_assert(a0, a1, 0x3B0D0Cu, kFrFontFile, 2167);
    }
    for (;;) {
        // 0x003b0d48: while (line)
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b0d1c: glyph = line->glyphs
        charge(ctx, 3);
        lw(v1, s1, line_node::kGlyphs);
        for (;;) {
            // 0x003b0d30: while (glyph)
            charge(ctx, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b0d28: glyph->style = style; glyph = glyph->next
            charge(ctx, 2);
            sb(s0, v1, glyph_node::kStyle);
            lw(v1, v1, glyph_node::kNext);
        }
        // 0x003b0d44: line = line->next
        charge(ctx, 1);
        lw(s1, s1, line_node::kNext);
    }
    // 0x003b0d50: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B0D70 frFontLineSetPos -- 96 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// frFontLineSetPos(line, x, y): the line's position. K_Assert("frFont.c", 2188) on a null line. Blocks: entry
// 10; null 5; store 9.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontLineSetPos(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0d70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;  // line
    s1 = a1;  // x
    s0 = a2;  // y
    if (s2 == 0) {
        // 0x003b0d98: K_Assert(line != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3B0DA4u, kFrFontFile, 2188);
    }
    // 0x003b0dac: line->x = x; line->y = y; epilogue
    charge(ctx, 9);
    sw(s1, s2, line_node::kX);
    sw(s0, s2, line_node::kY);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B0DD0 frFontLineSetColourSet -- 68 bytes; leaf frame (no stack)
// frFontLineSetColourSet(line, value): every glyph's colour set (+0x14) on the line and the lines after it.
// Blocks: entry 2; line test 2 (first); glyph setup 3; glyph test 5; body 2; next line 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontLineSetColourSet(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sb;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b0dd0
    enter(ctx, 2);  // entry check point + this block's cycles
    for (;;) {
        // 0x003b0e04: while (line)
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b0dd8: glyph = line->glyphs
        charge(ctx, 3);
        lw(v1, a0, line_node::kGlyphs);
        for (;;) {
            // 0x003b0dec: while (glyph)
            charge(ctx, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b0de4: glyph->colour_set = value; glyph = glyph->next
            charge(ctx, 2);
            sb(a1, v1, glyph_node::kColourSet);
            lw(v1, v1, glyph_node::kNext);
        }
        // 0x003b0e00: line = line->next
        charge(ctx, 1);
        lw(a0, a0, line_node::kNext);
    }
    // 0x003b0e0c: return
    charge(ctx, 2);
}

// 0x003B0E20 frFontLineSetRgba -- 68 bytes; leaf frame (no stack)
// frFontLineSetRgba(line, rgba): every glyph's colour word (+0x10) on the line and the lines after it. Blocks:
// entry 2; line test 2 (first); glyph setup 3; glyph test 5; body 2; next line 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontLineSetRgba(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b0e20
    enter(ctx, 2);  // entry check point + this block's cycles
    for (;;) {
        // 0x003b0e54: while (line)
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b0e28: glyph = line->glyphs
        charge(ctx, 3);
        lw(v1, a0, line_node::kGlyphs);
        for (;;) {
            // 0x003b0e3c: while (glyph)
            charge(ctx, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b0e34: glyph->rgba = rgba; glyph = glyph->next
            charge(ctx, 2);
            sw(a1, v1, glyph_node::kRgba);
            lw(v1, v1, glyph_node::kNext);
        }
        // 0x003b0e50: line = line->next
        charge(ctx, 1);
        lw(a0, a0, line_node::kNext);
    }
    // 0x003b0e5c: return
    charge(ctx, 2);
}

// 0x003B0E70 frFontSetDefaultGlyphFlags -- 32 bytes; leaf frame (no stack)
// frFontSetDefaultGlyphFlags(bits): the default glyph flags (s16, OR-ed into every new glyph node) |= (s16)bits;
// returns the old flags (u16). One block of 8.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontSetDefaultGlyphFlags(EEContext& ctx) {
    using hg::Gpr, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sh;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003b0e70
    enter(ctx, 8);  // entry check point + this block's cycles
    lh(a1, gp, gp_off(font::kDefaultGlyphFlags));
    v0 = a1 & 0xFFFF;  // the old flags
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v1 = a1 | v1;
    sh(v1, gp, gp_off(font::kDefaultGlyphFlags));
}

// 0x003B0E90 frFontClearDefaultGlyphFlags -- 40 bytes; leaf frame (no stack)
// frFontClearDefaultGlyphFlags(bits): the default glyph flags &= ~bits; returns the old flags (u16). One block of
// 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontClearDefaultGlyphFlags(EEContext& ctx) {
    using hg::Gpr, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::nor, hg::sh;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003b0e90
    enter(ctx, 10);  // entry check point + this block's cycles
    lh(a1, gp, gp_off(font::kDefaultGlyphFlags));
    v0 = a1 & 0xFFFF;  // the old flags
    v1 = a0 & 0xFFFF;
    v1 = nor(v1, 0);
    v1 = dsll32(v1, 16);
    v1 = dsra32(v1, 16);
    v1 = a1 & v1;
    sh(v1, gp, gp_off(font::kDefaultGlyphFlags));
}

// 0x003B0EC0 frFontLineFadeStep -- 140 bytes; leaf frame (no stack)
// frFontLineFadeStep(line): one fade step for every glyph in mode 2 (+0x16, fading) with a non-zero alpha byte
// (the low byte of +0x10) on the line and the lines after it: alpha = max(alpha - 8, 0), y offset (+0x8) += 16;
// returns 1 when any glyph changed, else 0. Blocks: entry 6; per line 3 / glyph 3, alpha test 4, 3, clamp 1,
// update 7, next 1, glyph test 2, line tail 1; line test 2; exit 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void frFontLineFadeStep(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lbu, hg::lw, hg::si, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x003b0ec0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0;          // changed
    a1 = si(-256);   // ~0xFF
    v1 = 1;
    t0 = 2;          // mode 2: fading
    for (;;) {
        // 0x003b0f3c: while (line)
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b0ed8: glyph = line->glyphs
        charge(ctx, 3);
        lw(t1, a0, line_node::kGlyphs);
        for (;;) {
            // 0x003b0f30: while (glyph)
            charge(ctx, 2);
            if (t1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b0ee4: fading?
            charge(ctx, 3);
            lbu(a2, t1, glyph_node::kMode);
            if (a2 == t0) {
                // 0x003b0ef0: a2 = its alpha byte
                charge(ctx, 4);
                lw(a3, t1, glyph_node::kRgba);
                a2 = a3 & 0xFF;
                if (a2 != 0) {
                    // 0x003b0f00: alpha - 8
                    charge(ctx, 3);
                    a2 = addiu(a2, -8);
                    if (i64(a2) < 0) {
                        // 0x003b0f0c: clamped at 0
                        charge(ctx, 1);
                        a2 = 0;
                    }
                    // 0x003b0f10: store the alpha, the glyph drops 16 (1 px); changed = 1
                    charge(ctx, 7);
                    v0 = a3 & a1;
                    v0 = v0 | a2;
                    sw(v0, t1, glyph_node::kRgba);
                    lw(v0, t1, glyph_node::kOffsetY);
                    v0 = addiu(v0, 16);
                    sw(v0, t1, glyph_node::kOffsetY);
                    v0 = v1;
                }
            }
            // 0x003b0f2c: glyph = glyph->next
            charge(ctx, 1);
            lw(t1, t1, glyph_node::kNext);
        }
        // 0x003b0f38: line = line->next
        charge(ctx, 1);
        lw(a0, a0, line_node::kNext);
    }
    // 0x003b0f44: return changed
    charge(ctx, 2);
}

// 0x003B1920 frFontLineChainJoin -- 116 bytes; leaf frame (no stack)
// frFontLineChainJoin(a, b, place): appends chain b to line a: a null side returns the other; else a->chain_next
// = b's first line, that line's next = a, b->chain_first = a->chain_first and, for place == 1, b takes the
// position right after a (a.x + a.glyph_count * 16, a.y); returns b. Blocks: entry 2; a null 3; 2; b null 3;
// link 9; place 7; 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void frFontLineChainJoin(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::lw, hg::sll, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003b1920
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x003b1934: b null?
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x003b1948: link the chains
            charge(ctx, 9);
            lw(v0, a1, line_node::kChainFirst);
            sw(v0, a0, line_node::kChainNext);
            lw(v0, a1, line_node::kChainFirst);
            sw(a0, v0, line_node::kNext);
            lw(v0, a0, line_node::kChainFirst);
            sw(v0, a1, line_node::kChainFirst);
            v0 = 1;
            if (a2 == v0) {
                // 0x003b196c: place: b.x = a.x + a.glyph_count * 16, b.y = a.y
                charge(ctx, 7);
                lw(v0, a0, line_node::kGlyphCount);
                v1 = sll(v0, 4);
                lw(v0, a0, line_node::kX);
                v0 = addu(v0, v1);
                sw(v0, a1, line_node::kX);
                lw(v0, a0, line_node::kY);
                sw(v0, a1, line_node::kY);
            }
            // 0x003b1988: return b
            charge(ctx, 1);
            v0 = a1;
        } else {
            // 0x003b193c: b null: return a
            charge(ctx, 3);
            v0 = a0;
        }
    } else {
        // 0x003b1928: a null: return b
        charge(ctx, 3);
        v0 = a1;
    }
    // 0x003b198c: return
    charge(ctx, 2);
}

// 0x003B19D0 frFontLineGetWidth -- 52 bytes; leaf frame (no stack)
// frFontLineGetWidth(line): the line's width in 1/16 px: the sum over its glyphs of advance + the line's letter
// spacing (s8 +3). Blocks: entry 4; per glyph 5; test 2; exit 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void frFontLineGetWidth(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lb, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b19d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0;  // width
    lw(a1, a0, line_node::kGlyphs);
    for (;;) {
        // 0x003b19f4: while (glyph)
        charge(ctx, 2);
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b19e0: width += glyph->advance + line->spacing; glyph = glyph->next
        charge(ctx, 5);
        lw(v1, a1, glyph_node::kAdvance);
        v1 = addu(v0, v1);
        lb(v0, a0, line_node::kSpacing);
        v0 = addu(v1, v0);
        lw(a1, a1, glyph_node::kNext);
    }
    // 0x003b19fc: return width
    charge(ctx, 2);
}

// 0x003B1A10 frFontGetStyleGlyphWidth -- 36 bytes; leaf frame (no stack)
// frFontGetStyleGlyphWidth(style): the glyph width (u16) of the style's .FNT header. One block of 9.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontGetStyleGlyphWidth(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lhu, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003b1a10
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = a0 & 0xFF;
    v1 = sll(v0, 5);
    la(v0, font::kStyles + fnt_style::kFnt);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);  // the style's .FNT
    lhu(v0, v0, fnt_hdr::kGlyphWidth);
}

// 0x003B1A40 frFontGetStyleGlyphHeight -- 36 bytes; leaf frame (no stack)
// frFontGetStyleGlyphHeight(style): the glyph height (u16) of the style's .FNT header. One block of 9.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontGetStyleGlyphHeight(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lhu, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003b1a40
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = a0 & 0xFF;
    v1 = sll(v0, 5);
    la(v0, font::kStyles + fnt_style::kFnt);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);  // the style's .FNT
    lhu(v0, v0, fnt_hdr::kGlyphHeight);
}

// 0x003B1A70 frFontResetLineSpacing -- 16 bytes; leaf frame (no stack)
// frFontResetLineSpacing(): the line spacing (font::kLineSpacing, 1/8 px) back to 25. One block of 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontResetLineSpacing(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr v1{ctx, 3}, gp{ctx, 28};
    // 0x003b1a70
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 25;  // the default line spacing
    sw(v1, gp, gp_off(font::kLineSpacing));
}

void frFontSetLineSpacing(EEContext& ctx, u32 spacing) {
    // 0x3B1A80 frFontSetLineSpacing. One block of 3.
    guest::enter(ctx, 3);
    st32(ctx, kLineSpacing, spacing);
}

// 0x003B1A90 frFontChainCountLines -- 108 bytes; leaf frame (no stack)
// frFontChainCountLines(chain): the number of lines of the chain (walking +0x28 from its first line, +0x2C).
// Each step also walks the row that starts at the line (the lines below its y + 100) without using the result:
// dead code kept for its cycles and check points. Blocks: entry 3; null 2; 3; per line 5 + walk (test 3, 4, 1) +
// 2; line test 2; exit 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void frFontChainCountLines(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::slt;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x003b1a90
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;  // count
    if (a0 != 0) {
        // 0x003b1aa4: line = the chain's first line
        charge(ctx, 3);
        lw(a0, a0, line_node::kChainFirst);
        for (;;) {
            // 0x003b1aec: while (line)
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b1ab0: the row starting here: v1 = its y + 100
            charge(ctx, 5);
            a2 = a0;
            lw(v1, a0, line_node::kY);
            v1 = addiu(v1, line_node::kRowSpan);
            for (;;) {
                // 0x003b1ad8: walk the row (unused): while (l && l->y < row_y + 100)
                charge(ctx, 3);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b1ac4
                charge(ctx, 4);
                lw(a1, a2, line_node::kY);
                at = slt(a1, v1);
                if (at == 0) {
                    break;
                }
                // 0x003b1ad4: l = l->chain_next
                charge(ctx, 1);
                lw(a2, a2, line_node::kChainNext);
            }
            // 0x003b1ae4: ++count; line = line->chain_next
            charge(ctx, 2);
            v0 = addiu(v0, 1);
            lw(a0, a0, line_node::kChainNext);
        }
    } else {
        // 0x003b1a9c: no chain: 0
        charge(ctx, 2);
    }
    // 0x003b1af4: return count
    charge(ctx, 2);
}

// 0x003B1B00 frFontChainGetRowWidth -- 180 bytes; leaf frame (no stack)
// frFontChainGetRowWidth(row, chain): the width of row `row` of the chain, << 4: step `row` + 1 times along the
// chain (+0x28 from its first line); each step sums the widths (glyph advances + letter spacing) of the row that
// starts at the step's line (the lines below its y + 100) -- the last sum is the result. 0 for a null chain.
// Blocks: entry 4; null 3; 3; per step 6, run test 2, y test 4, per line 4 + width (5 per glyph, test 2) + 2;
// step tail 4, next 1; step test 2; 1 (<< 4); return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontChainGetRowWidth(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lb, hg::lw, hg::sll, hg::slt;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x003b1b00: t1 = the row's width, t0 = the step
    enter(ctx, 4);  // entry check point + this block's cycles
    t1 = 0;
    t0 = 0;
    if (a1 != 0) {
        // 0x003b1b1c: line = the chain's first line
        charge(ctx, 3);
        lw(a1, a1, line_node::kChainFirst);
        for (;;) {
            // 0x003b1ba0: while (line)
            charge(ctx, 2);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b1b28: the row starting here: a2 = its y + 100; t2 walks it
            charge(ctx, 6);
            t1 = 0;
            t2 = a1;
            lw(v0, a1, line_node::kY);
            a2 = addiu(v0, line_node::kRowSpan);
            for (;;) {
                // 0x003b1b84: while (l && l->y < row_y + 100)
                charge(ctx, 2);
                if (t2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b1b40
                charge(ctx, 4);
                lw(v0, t2, line_node::kY);
                at = slt(v0, a2);
                if (at == 0) {
                    break;
                }
                // 0x003b1b50: v1 = l's width
                charge(ctx, 4);
                v1 = 0;
                lw(a3, t2, line_node::kGlyphs);
                for (;;) {
                    // 0x003b1b74: while (glyph)
                    charge(ctx, 2);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003b1b60: width += glyph->advance + l->spacing; glyph = glyph->next
                    charge(ctx, 5);
                    lw(v0, a3, glyph_node::kAdvance);
                    v1 = addu(v1, v0);
                    lb(v0, t2, line_node::kSpacing);
                    v1 = addu(v1, v0);
                    lw(a3, a3, glyph_node::kNext);
                }
                // 0x003b1b7c: the row's width += it; l = l->chain_next
                charge(ctx, 2);
                t1 = addu(t1, v1);
                lw(t2, t2, line_node::kChainNext);
            }
            // 0x003b1b8c: the row asked for?
            charge(ctx, 4);
            v0 = t0;
            t0 = addiu(t0, 1);
            if (v0 == a0) {
                break;
            }
            // 0x003b1b9c: line = line->chain_next
            charge(ctx, 1);
            lw(a1, a1, line_node::kChainNext);
        }
        // 0x003b1ba8: return width << 4
        charge(ctx, 1);
        v0 = sll(t1, 4);
    } else {
        // 0x003b1b10: no chain: 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b1bac: return
    charge(ctx, 2);
}

// 0x003B1BC0 frFontChainGetRowPos -- 128 bytes; leaf frame (no stack)
// frFontChainGetRowPos(out, row, chain): out = {x, y} of the chain's line at step `row` (+0x28 from its first
// line); each step also walks the row that starts there (unused, kept for its cycles). out is left alone for a
// null chain. Blocks: entry 3; 3; per step 9 + walk (test 3, 4, 1); 4, next 1; step test 2; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontChainGetRowPos(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::slt, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x003b1bc0: t0 = the step
    enter(ctx, 3);  // entry check point + this block's cycles
    t0 = 0;
    if (a2 != 0) {
        // 0x003b1bcc: line = the chain's first line
        charge(ctx, 3);
        lw(a2, a2, line_node::kChainFirst);
        for (;;) {
            // 0x003b1c30: while (line)
            charge(ctx, 2);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b1bd8: out = {line->x, line->y}; the row starting here (v1 = its y + 100)
            charge(ctx, 9);
            t1 = a2;
            lw(v1, a2, line_node::kX);
            sw(v1, a0, 0);
            lw(v1, a2, line_node::kY);
            sw(v1, a0, 4);
            lw(v1, a2, line_node::kY);
            v1 = addiu(v1, line_node::kRowSpan);
            for (;;) {
                // 0x003b1c10: walk the row (unused): while (l && l->y < row_y + 100)
                charge(ctx, 3);
                if (t1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b1bfc
                charge(ctx, 4);
                lw(a3, t1, line_node::kY);
                at = slt(a3, v1);
                if (at == 0) {
                    break;
                }
                // 0x003b1c0c
                charge(ctx, 1);
                lw(t1, t1, line_node::kChainNext);
            }
            // 0x003b1c1c: the row asked for?
            charge(ctx, 4);
            v1 = t0;
            t0 = addiu(t0, 1);
            if (v1 == a1) {
                break;
            }
            // 0x003b1c2c: line = line->chain_next
            charge(ctx, 1);
            lw(a2, a2, line_node::kChainNext);
        }
    }
    // 0x003b1c38: return
    charge(ctx, 2);
}

// 0x003B1C40 frFontChainMoveTo -- 80 bytes; leaf frame (no stack)
// frFontChainMoveTo(x, y, chain): moves the whole chain so that its first line sits at (x, y): every line (+0x28
// from the first) moves by (x, y) - the first line's position. Blocks: entry 2; 7; per line 7; test 2; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontChainMoveTo(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::subu, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x003b1c40
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a2 != 0) {
        // 0x003b1c48: line = the first line; a3 = dx, a0 = dy
        charge(ctx, 7);
        lw(a2, a2, line_node::kChainFirst);
        lw(v1, a2, line_node::kX);
        a3 = subu(a0, v1);
        lw(v1, a2, line_node::kY);
        a0 = subu(a1, v1);
        for (;;) {
            // 0x003b1c80: while (line)
            charge(ctx, 2);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b1c64: line->x += dx; line->y += dy; line = line->chain_next
            charge(ctx, 7);
            lw(v1, a2, line_node::kX);
            v1 = addu(v1, a3);
            sw(v1, a2, line_node::kX);
            lw(v1, a2, line_node::kY);
            v1 = addu(v1, a0);
            sw(v1, a2, line_node::kY);
            lw(a2, a2, line_node::kChainNext);
        }
    }
    // 0x003b1c88: return
    charge(ctx, 2);
}

// 0x003B1C90 frFontChainCentreAt -- 248 bytes; leaf frame (no stack)
// frFontChainCentreAt(x, y, chain): centres every row of the chain on x and moves the chain to y: per row (the
// lines from the row's first line whose y is below its y + 100), the row's width W is summed, then each line of
// the row gets x += (x - the row's first x) - (W / 2) * 16 and y += y - the chain's first y; the walk goes on
// from the first line past the row. Blocks: entry 2; 5; per row 6, width walk (2, 4, 4 + glyphs 5 / 2, 2), 5,
// halving bias 2, 4, move walk (2, 4, 9); row test 2; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontChainCentreAt(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lb, hg::lw, hg::sll,
          hg::slt, hg::sra, hg::subu, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x003b1c90
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a2 != 0) {
        // 0x003b1c98: line = the chain's first line; t2 = dy = y - its y
        charge(ctx, 5);
        lw(a2, a2, line_node::kChainFirst);
        lw(v1, a2, line_node::kY);
        t2 = subu(a1, v1);
        for (;;) {
            // 0x003b1d78: while (line): a row starts here
            charge(ctx, 2);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b1cac: t3 = the row's width; t4 walks the row; t1 = its y, a3 = y + 100
            charge(ctx, 6);
            t3 = 0;
            t4 = a2;
            lw(t1, a2, line_node::kY);
            a3 = addiu(t1, line_node::kRowSpan);
            for (;;) {
                // 0x003b1d08: while (l && l->y < row_y + 100)
                charge(ctx, 2);
                if (t4 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b1cc4
                charge(ctx, 4);
                lw(v1, t4, line_node::kY);
                at = slt(v1, a3);
                if (at == 0) {
                    break;
                }
                // 0x003b1cd4: a1 = l's width
                charge(ctx, 4);
                a1 = 0;
                lw(t0, t4, line_node::kGlyphs);
                for (;;) {
                    // 0x003b1cf8: while (glyph)
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003b1ce4: width += glyph->advance + l->spacing; glyph = glyph->next
                    charge(ctx, 5);
                    lw(v1, t0, glyph_node::kAdvance);
                    a1 = addu(a1, v1);
                    lb(v1, t4, line_node::kSpacing);
                    a1 = addu(a1, v1);
                    lw(t0, t0, glyph_node::kNext);
                }
                // 0x003b1d00: W += it; l = l->chain_next
                charge(ctx, 2);
                t3 = addu(t3, a1);
                lw(t4, t4, line_node::kChainNext);
            }
            // 0x003b1d10: t0 = x - the row's x; v1 = W / 2
            charge(ctx, 5);
            lw(v1, a2, line_node::kX);
            t0 = subu(a0, v1);
            v1 = sra(t3, 1);
            if (i64(t3) < 0) {
                // 0x003b1d24: round toward zero
                charge(ctx, 2);
                v1 = addiu(t3, 1);
                v1 = sra(v1, 1);
            }
            // 0x003b1d2c: a3 = (W / 2) * 16; a1 = the row's y + 100
            charge(ctx, 4);
            a3 = sll(v1, 4);
            a1 = addiu(t1, line_node::kRowSpan);
            for (;;) {
                // 0x003b1d70: move the row's lines: while (line && line->y < row_y + 100)
                charge(ctx, 2);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003b1d3c
                charge(ctx, 4);
                lw(v1, a2, line_node::kY);
                at = slt(v1, a1);
                if (at == 0) {
                    break;
                }
                // 0x003b1d4c: line->x += dx, -= (W / 2) * 16; line->y += dy; line = line->chain_next
                charge(ctx, 9);
                lw(v1, a2, line_node::kX);
                v1 = addu(v1, t0);
                sw(v1, a2, line_node::kX);
                v1 = subu(v1, a3);
                sw(v1, a2, line_node::kX);
                lw(v1, a2, line_node::kY);
                v1 = addu(v1, t2);
                sw(v1, a2, line_node::kY);
                lw(a2, a2, line_node::kChainNext);
            }
        }
    }
    // 0x003b1d80: return
    charge(ctx, 2);
}

// ======================================== frFontEx.c ====================================================

// 0x003B2400 frFontLayoutNewRow -- 40 bytes; leaf frame (no stack)
// frFontLayoutNewRow(layout): starts a new row: layout->y (+4) += the line spacing * 8; the two new-row bytes
// (+0x1C, +0x1D) = 1. One block of 10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontLayoutNewRow(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sb, hg::sll, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003b2400
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, gp, gp_off(font::kLineSpacing));
    a1 = sll(v1, 3);
    lw(v1, a0, tag_scan::kY);
    v1 = addu(v1, a1);
    sw(v1, a0, tag_scan::kY);
    v1 = 1;
    sb(v1, a0, tag_scan::kNewRowA);
    sb(v1, a0, tag_scan::kNewRowB);
}

u32 frFontTestTagFlags(EEContext& ctx, u32 mask) {
    // 0x3B2A00 frFontTestTagFlags. One block of 4.
    guest::enter(ctx, 4);
    return ld32(ctx, kTagFlags) & mask;
}

// 0x003B2A10 frFontSetTagSlot -- 28 bytes; leaf frame (no stack)
// frFontSetTagSlot(i, word): kFrMessageArgTable[i] = word (the message arguments the tags read; no bounds
// check). One block of 7.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontSetTagSlot(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::sll, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003b2a10
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = sll(a0, 2);
    la(v1, kFrMessageArgTable);
    v1 = addu(v1, a0);
    sw(a1, v1, 0);
}

// 0x003B2A30 frFontProcessTagEx -- 436 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// frFontProcessTagEx(scan, tag): walks the text at scan->text from scan->offset and runs sFrTagTable[code &
// 0xFF](code, scan) for every tag code equal to `tag` (none when tag is 0). A tag is a byte 0xFn followed by one
// more byte; its parameter words ((code >> 8 & 0xF) - 1 of them) are skipped after the handler. A non-zero
// handler result, or the codes F131 / F110 / F104, end the scan. A byte >= 0x80 (other than a tag) is a
// two-byte glyph and skips one more byte; '\n' and ASCII are single. Before the walk: a text whose first byte
// is no tag but whose second is 8 skips 4 bytes, and the low 6 bits of the tag flags are cleared. Returns 0.
// Blocks: entry 13; 4; 3; flags 6; loop head 8 (exit 8); tag 4 + 11, tag != 0 2, dispatch 10, skip 9, result 3 /
// end-code chain 3, 3, 3 (miss 2), 3 / 1, 2, end 2; non-tag 3, 3, 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontProcessTagEx(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jalr, hg::lbu, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::si, hg::sll, hg::slti, hg::sq, hg::sra, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b2a30: s2 = scan, s1 = tag; does the text start with a tag?
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(a0, a0, tag_scan::kText);
    lbu(v0, a0, 0);
    v1 = v0 & 0xF0;
    v0 = text_code::kTagLead;
    if (v1 != v0) {
        // 0x003b2a64: no tag first: a second byte of 8?
        charge(ctx, 4);
        lbu(v1, a0, 1);
        v0 = 8;
        if (v1 == v0) {
            // 0x003b2a74: skip a 4-byte header
            charge(ctx, 3);
            lw(v0, s2, tag_scan::kOffset);
            v0 = addiu(v0, 4);
            sw(v0, s2, tag_scan::kOffset);
        }
    }
    // 0x003b2a80: clear the low 6 bits of the tag flags
    charge(ctx, 6);
    lw(v1, gp, gp_off(font::kTagFlags));
    v0 = si(tag_flags::kScanClear);
    v0 = v1 & v0;
    sw(v0, gp, gp_off(font::kTagFlags));
    for (;;) {
        // 0x003b2ba4: v1 = text[offset++]; the end at a 0 byte
        charge(ctx, 8);
        lw(v1, s2, tag_scan::kOffset);
        v0 = addiu(v1, 1);
        sw(v0, s2, tag_scan::kOffset);
        lw(v0, s2, tag_scan::kText);
        v0 = addu(v0, v1);
        lbu(v1, v0, 0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b2a98: a tag (0xFn)?
        charge(ctx, 4);
        a0 = v1 & 0xF0;
        v0 = text_code::kTagLead;
        if (a0 != v0) {
            // 0x003b2b80: not a tag: '\n'?
            charge(ctx, 3);
            v0 = text_code::kNewline;
            if (v1 != v0) {
                // 0x003b2b8c: a two-byte glyph?
                charge(ctx, 3);
                v0 = slti(v1, text_code::kTwoByte);
                if (v0 == 0) {
                    // 0x003b2b98: skip its second byte
                    charge(ctx, 3);
                    lw(v0, s2, tag_scan::kOffset);
                    v0 = addiu(v0, 1);
                    sw(v0, s2, tag_scan::kOffset);
                }
            }
            continue;
        }
        // 0x003b2aa8: s0 = code = (lead << 8) | text[offset++]; result v0 = 0
        charge(ctx, 11);
        v0 = 0;
        lw(a1, s2, tag_scan::kOffset);
        a0 = addiu(a1, 1);
        sw(a0, s2, tag_scan::kOffset);
        lw(a0, s2, tag_scan::kText);
        a0 = addu(a0, a1);
        lbu(a0, a0, 0);
        v1 = sll(v1, 8);
        s0 = v1 | a0;
        if (s1 != 0) {
            // 0x003b2ad4: the tag asked for?
            charge(ctx, 2);
            if (s0 == s1) {
                // 0x003b2adc: v0 = sFrTagTable[code & 0xFF](code, scan)
                charge(ctx, 10);
                a0 = s0;
                a1 = s2;
                v0 = s0 & 0xFF;
                v1 = sll(v0, 2);
                la(v0, font::kTagHandlers);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                jalr(ctx, 0x3B2AFCu, v0.u());
            }
        }
        // 0x003b2b04: skip the parameter words: offset += 2 * (((code & 0xF00) >> 8) - 1)
        charge(ctx, 9);
        v1 = s0 & 0xF00;
        v1 = sra(v1, 8);
        v1 = addiu(v1, -1);
        a0 = sll(v1, 1);
        lw(v1, s2, tag_scan::kOffset);
        v1 = addu(v1, a0);
        sw(v1, s2, tag_scan::kOffset);
        if (v0 == 0) {
            // 0x003b2b34: no handler result: an end code (F131 / F110 / F104)?
            charge(ctx, 3);
            v0 = text_code::kTagEnd31;
            bool end_code = s0 == v0;
            if (!end_code) {
                // 0x003b2b40
                charge(ctx, 3);
                v0 = text_code::kTagEnd10;
                end_code = s0 == v0;
            }
            if (!end_code) {
                // 0x003b2b4c
                charge(ctx, 3);
                v0 = text_code::kTagEnd04;
                end_code = s0 == v0;
            }
            if (!end_code) {
                // 0x003b2b58, 0x003b2b6c: go on
                charge(ctx, 2);
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x003b2b60: end
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x003b2b28: the handler ended the scan
            charge(ctx, 3);
            v0 = 1;
        }
        // 0x003b2b70: end the scan?
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003b2b78
            charge(ctx, 2);
            break;
        }
    }
    // 0x003b2bc4: return 0
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B2BF0 frFontProcessTag -- 108 bytes; frame 0x30: ra sp+0x0
// frFontProcessTag(text, window, tag): builds a 32-byte scan record in the frame (sp+0x10: zeros, text +0x10,
// window +0x14, offset 0, the new-row bytes +0x1C = +0x1D = 1, +0x1E = 32) and runs frFontProcessTagEx on it;
// returns its result as s8. One block of 27.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontProcessTag(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::sb, hg::sd, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    constexpr s32 kScan = 0x10;  // the scan record in the frame
    // 0x003b2bf0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    sw(zero, sp, kScan + tag_scan::kX);
    sw(zero, sp, kScan + tag_scan::kY);
    sw(zero, sp, kScan + 0x8);
    sb(zero, sp, kScan + 0xC);
    sb(zero, sp, kScan + 0xD);
    sb(zero, sp, kScan + 0xE);
    sb(zero, sp, kScan + 0xF);
    sw(a0, sp, kScan + tag_scan::kText);
    sw(a1, sp, kScan + tag_scan::kWindow);
    sw(zero, sp, kScan + tag_scan::kOffset);
    v0 = 1;
    sb(v0, sp, kScan + tag_scan::kNewRowA);
    sb(v0, sp, kScan + tag_scan::kNewRowB);
    v0 = 32;
    sh(v0, sp, kScan + tag_scan::kHalf1E);
    a0 = addiu(sp, kScan);
    a1 = a2;
    jal(ctx, 0x3B2C3Cu, gen::fn_frFontProcessTagEx_003b2a30);
    v0 = dsll32(v0, 24);  // (s8) result
    v0 = dsra32(v0, 24);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The four tag parameters (0x95ABE0..0x95ABEC). One block of 4 each.
u32 frFontTagGetParam0(EEContext& ctx) { guest::enter(ctx, 4); return ld32(ctx, kTagParams + 0); }   // 0x3AF360
u32 frFontTagGetParam1(EEContext& ctx) { guest::enter(ctx, 4); return ld32(ctx, kTagParams + 4); }   // 0x3AF370
u32 frFontTagGetParam2(EEContext& ctx) { guest::enter(ctx, 4); return ld32(ctx, kTagParams + 8); }   // 0x3AF380
u32 frFontTagGetParam3(EEContext& ctx) { guest::enter(ctx, 4); return ld32(ctx, kTagParams + 12); }  // 0x3AF390

// 0x003AF3A0 frFontTagSetParams01 -- 180 bytes; leaf frame (no stack)
// frFontTagSetParams01(code, scan) (tag 0x42): font::kTagParams[0] and [1] = the tag's two parameters; returns 0. A parameter is two text bytes b0 b1 after the tag, both stored + 1 so that no byte is 0: value = ((b1 == 255 ?
// 0 : b1 - 1) << 8) | (b0 - 1).
// Blocks: entry 10; 255 test 3 / 2; 16; 255 test 3 / 2; 9.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontTagSetParams01(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sll, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003af3a0
    enter(ctx, 10);  // entry check point + this block's cycles
    // the first parameter: b0, b1 at scan->text + scan->offset
    lw(v1, a1, tag_scan::kOffset);
    lw(v0, a1, tag_scan::kText);
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003af3d4: b1 - 1
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af3c8: b1 == 255: high byte 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af3dc: params[0] = (high << 8) | (b0 - 1); the second parameter: b2, b3
    charge(ctx, 16);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v1 = v1 | v0;
    v0 = hi(font::kTagParams);
    sw(v1, v0, lo(font::kTagParams));
    lw(v1, a1, tag_scan::kOffset);
    lw(v0, a1, tag_scan::kText);
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003af428: b3 - 1
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af41c: b3 == 255: high byte 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af430: params[1] = (high << 8) | (b2 - 1); return 0
    charge(ctx, 9);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v1 = v1 | v0;
    v0 = hi(font::kTagParams + 4);
    sw(v1, v0, lo(font::kTagParams + 4));
    v0 = 0;
}

// 0x003AF460 frFontTagSetParams23 -- 180 bytes; leaf frame (no stack)
// frFontTagSetParams23(code, scan) (tag 0x43): font::kTagParams[2] and [3] = the tag's two parameters; returns 0. A parameter is two text bytes b0 b1 after the tag, both stored + 1 so that no byte is 0: value = ((b1 == 255 ?
// 0 : b1 - 1) << 8) | (b0 - 1).
// Blocks: entry 10; 255 test 3 / 2; 16; 255 test 3 / 2; 9.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontTagSetParams23(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sll, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003af460
    enter(ctx, 10);  // entry check point + this block's cycles
    // the first parameter: b0, b1 at scan->text + scan->offset
    lw(v1, a1, tag_scan::kOffset);
    lw(v0, a1, tag_scan::kText);
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003af494: b1 - 1
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af488: b1 == 255: high byte 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af49c: params[2] = (high << 8) | (b0 - 1); the second parameter: b2, b3
    charge(ctx, 16);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v1 = v1 | v0;
    v0 = hi(font::kTagParams + 8);
    sw(v1, v0, lo(font::kTagParams + 8));
    lw(v1, a1, tag_scan::kOffset);
    lw(v0, a1, tag_scan::kText);
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003af4e8: b3 - 1
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af4dc: b3 == 255: high byte 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af4f0: params[3] = (high << 8) | (b2 - 1); return 0
    charge(ctx, 9);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v1 = v1 | v0;
    v0 = hi(font::kTagParams + 12);
    sw(v1, v0, lo(font::kTagParams + 12));
    v0 = 0;
}

// 0x003AF5A0 frFontTagWait -- 180 bytes; leaf frame (no stack)
// frFontTagWait(code, scan) (tag 0x46): the window waits (s16)param ticks: window->wait_tag (+48) = code,
// window->wait (+60) = param (a negative one clamps to 0), window +56 = 1 when its +52 is set; tag flag 0x80.
// Returns 0. A parameter is two text bytes b0 b1 after the tag, both stored + 1 so that no byte is 0: value = ((b1 == 255 ?
// 0 : b1 - 1) << 8) | (b0 - 1). Blocks: 10; 255 test 3 / 2; 10; +52 set 2; 11; clamp 1; 6.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontTagWait(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::lbu, hg::lw,
          hg::sll, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x003af5a0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, tag_scan::kOffset);
    lw(v0, a1, tag_scan::kText);
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a2 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003af5d4: b1 - 1
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af5c8: b1 == 255: high byte 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af5dc: a2 = (s16)param; the window's +52 set?
    charge(ctx, 10);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a2 & 0xFF;
    v0 = v1 | v0;
    a2 = dsll32(v0, 16);
    a2 = dsra32(a2, 16);
    lw(v1, a1, tag_scan::kWindow);
    lw(v0, v1, tag_window::kWord52);
    if (v0 != 0) {
        // 0x003af604: window +56 = 1
        charge(ctx, 2);
        v0 = 1;
        sw(v0, v1, tag_window::kWord56);
    }
    // 0x003af60c: window->wait_tag = code; window->wait = param; negative?
    charge(ctx, 11);
    lw(v0, a1, tag_scan::kWindow);
    sw(a0, v0, tag_window::kWaitTag);
    v1 = dsll32(a2, 16);
    v1 = dsra32(v1, 16);
    lw(v0, a1, tag_scan::kWindow);
    sw(v1, v0, tag_window::kWait);
    lw(v0, a1, tag_scan::kWindow);
    v1 = addiu(v0, tag_window::kWait);
    lw(v0, v0, tag_window::kWait);
    if (i64(v0) < 0) {
        // 0x003af638: clamp to 0
        charge(ctx, 1);
        sw(zero, v1, 0);
    }
    // 0x003af63c: tag flags |= 0x80; return 0
    charge(ctx, 6);
    lw(v0, gp, gp_off(font::kTagFlags));
    v0 = v0 | tag_flags::kWait;
    sw(v0, gp, gp_off(font::kTagFlags));
    v0 = 0;
}

// 0x003AF660 frFontTagWaitIfFlag389 -- 260 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// frFontTagWaitIfFlag389(code, scan) (tag 0x47): as tag 0x46 when the global flag 389 is set (datGetFlag), with
// tag flag 0x40; nothing otherwise. Returns 0. Blocks: 17; 255 test 3 / 2; 11 (the datGetFlag call); flag clear
// 3; 4; +52 set 2; 11; clamp 1; 4; 7.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontTagWaitIfFlag389(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::lbu,
          hg::ld, hg::lq, hg::lw, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003af660
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;  // code
    s1 = a1;  // scan
    lw(v1, a1, tag_scan::kOffset);
    lw(v0, a1, tag_scan::kText);
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003af6b0: b1 - 1
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003af6a4: b1 == 255: high byte 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af6b8: s0 = (s16)param; datGetFlag(389)
    charge(ctx, 11);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    a0 = tag_flags::kFlag389;
    jal(ctx, 0x3AF6D4u, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x003af6f0: the flag is set: the window's +52 set?
        charge(ctx, 4);
        lw(v1, s1, tag_scan::kWindow);
        lw(v0, v1, tag_window::kWord52);
        if (v0 != 0) {
            // 0x003af700: window +56 = 1
            charge(ctx, 2);
            v0 = 1;
            sw(v0, v1, tag_window::kWord56);
        }
        // 0x003af708: window->wait_tag = code; window->wait = param; negative?
        charge(ctx, 11);
        lw(v0, s1, tag_scan::kWindow);
        sw(s2, v0, tag_window::kWaitTag);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        lw(v0, s1, tag_scan::kWindow);
        sw(v1, v0, tag_window::kWait);
        lw(v0, s1, tag_scan::kWindow);
        v1 = addiu(v0, tag_window::kWait);
        lw(v0, v0, tag_window::kWait);
        if (i64(v0) < 0) {
            // 0x003af734: clamp to 0
            charge(ctx, 1);
            sw(zero, v1, 0);
        }
        // 0x003af738: tag flags |= 0x40; return 0
        charge(ctx, 4);
        lw(v0, gp, gp_off(font::kTagFlags));
        v0 = v0 | tag_flags::kWaitIfFlag;
        sw(v0, gp, gp_off(font::kTagFlags));
        v0 = 0;
    } else {
        // 0x003af6e4: the flag is clear: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003af748: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// ======================================= frFontRaster.c =================================================

// 0x003B35C0 frFontGetStyleSize -- 28 bytes; leaf frame (no stack)
// frFontGetStyleSize(style): the glyph size of a style (s8 sizes[(s8)style], 32 = 1:1). One block of 7.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontGetStyleSize(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::dsll32, hg::dsra32, hg::enter, hg::lb;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x003b35c0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = addiu(gp, gp_off(font::kStyleSizes));  // &sizes
    v0 = addu(v0, v1);
    lb(v0, v0, 0);
}

// 0x003B3770 frFontRasterAgeSlots -- 376 bytes; leaf frame (no stack)
// frFontRasterAgeSlots(): ages the raster-slot cache once a frame. Every slot on the active list (manager +8,
// linked by +0x18) that was not used this frame (bit 0 of +0) or has no GS entry (+0x10) loses one tick (s16
// +0xA); a slot whose ticks went negative moves to the tail of the free list (manager +0x10 head / +0x14 tail).
// Removing the head restarts the walk from the new head. v1 = the previous slot (0 at the head).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void frFontRasterAgeSlots(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lh, hg::lw, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x003b3770: v1 = prev = 0, a0 = slot = the first active slot
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0;
    lw(a0, gp, gp_off(font::kRasterSlots));
    lw(a0, a0, raster_mgr::kActive);
    for (;;) {
        // 0x003b38d8: while (slot)
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b3784: used this frame?
        charge(ctx, 4);
        lw(a1, a0, raster_slot::kFlags);
        a1 = a1 & 0x1;
        bool age = true;  // not used, or no GS entry
        if (a1 != 0) {
            // 0x003b3794: used: does it have a GS entry?
            charge(ctx, 3);
            lw(a1, a0, raster_slot::kGsEntry);
            age = a1 == 0;
        }
        if (age) {
            // 0x003b37a0: --ticks
            charge(ctx, 3);
            lh(a1, a0, raster_slot::kTicks);
            a1 = addiu(a1, -1);
            sh(a1, a0, raster_slot::kTicks);
        }
        // 0x003b37ac: expired?
        charge(ctx, 3);
        lh(a1, a0, raster_slot::kTicks);
        if (i64(a1) >= 0) {
            // 0x003b38d0: keep it: prev = slot, slot = slot->next
            charge(ctx, 2);
            v1 = a0;
            lw(a0, a0, raster_slot::kNext);
        } else {
            // 0x003b37b8: expired: unlink it (the head, or after prev)
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x003b382c: after prev; was it the last slot?
                charge(ctx, 3);
                lw(a1, a0, raster_slot::kNext);
                if (a1 != 0) {
                    // 0x003b3888: prev->next = slot->next; append slot to the free list
                    charge(ctx, 6);
                    sw(a1, v1, raster_slot::kNext);
                    lw(a1, gp, gp_off(font::kRasterSlots));
                    a2 = addiu(a1, raster_mgr::kFreeTail);
                    lw(a1, a1, raster_mgr::kFreeTail);
                    if (a1 == 0) {
                        // 0x003b38b4: the free list was empty: head = tail = slot
                        charge(ctx, 3);
                        sw(a0, a2, 0);
                        lw(a1, gp, gp_off(font::kRasterSlots));
                        sw(a0, a1, raster_mgr::kFree);
                    } else {
                        // 0x003b38a0: tail->next = slot; tail = slot
                        charge(ctx, 5);
                        sw(a0, a1, raster_slot::kNext);
                        lw(a1, gp, gp_off(font::kRasterSlots));
                        sw(a0, a1, raster_mgr::kFreeTail);
                    }
                    // 0x003b38c0: slot->next = 0; slot = prev->next
                    charge(ctx, 4);
                    sw(zero, a0, raster_slot::kNext);
                    lw(a0, v1, raster_slot::kNext);
                } else {
                    // 0x003b3838: the last slot: the active tail = prev; prev->next = 0; append slot to the free list
                    charge(ctx, 8);
                    lw(a1, gp, gp_off(font::kRasterSlots));
                    sw(v1, a1, raster_mgr::kActiveTail);
                    sw(zero, v1, raster_slot::kNext);
                    lw(a1, gp, gp_off(font::kRasterSlots));
                    a2 = addiu(a1, raster_mgr::kFreeTail);
                    lw(a1, a1, raster_mgr::kFreeTail);
                    if (a1 == 0) {
                        // 0x003b386c: the free list was empty
                        charge(ctx, 3);
                        sw(a0, a2, 0);
                        lw(a1, gp, gp_off(font::kRasterSlots));
                        sw(a0, a1, raster_mgr::kFree);
                    } else {
                        // 0x003b3858: tail->next = slot
                        charge(ctx, 5);
                        sw(a0, a1, raster_slot::kNext);
                        lw(a1, gp, gp_off(font::kRasterSlots));
                        sw(a0, a1, raster_mgr::kFreeTail);
                    }
                    // 0x003b3878: slot->next = 0; the walk ends
                    charge(ctx, 4);
                    sw(zero, a0, raster_slot::kNext);
                    a0 = 0;
                }
            } else {
                // 0x003b37c0: the head: active = slot->next (the tail too when that empties it)
                charge(ctx, 7);
                lw(a1, a0, raster_slot::kNext);
                lw(v1, gp, gp_off(font::kRasterSlots));
                sw(a1, v1, raster_mgr::kActive);
                lw(a1, gp, gp_off(font::kRasterSlots));
                lw(v1, a1, raster_mgr::kActive);
                if (v1 == 0) {
                    // 0x003b37dc
                    charge(ctx, 1);
                    sw(zero, a1, raster_mgr::kActiveTail);
                }
                // 0x003b37e0: append slot to the free list
                charge(ctx, 5);
                lw(v1, gp, gp_off(font::kRasterSlots));
                a1 = addiu(v1, raster_mgr::kFreeTail);
                lw(v1, v1, raster_mgr::kFreeTail);
                if (v1 == 0) {
                    // 0x003b3808: the free list was empty
                    charge(ctx, 3);
                    sw(a0, a1, 0);
                    lw(v1, gp, gp_off(font::kRasterSlots));
                    sw(a0, v1, raster_mgr::kFree);
                } else {
                    // 0x003b37f4: tail->next = slot
                    charge(ctx, 5);
                    sw(a0, v1, raster_slot::kNext);
                    lw(v1, gp, gp_off(font::kRasterSlots));
                    sw(a0, v1, raster_mgr::kFreeTail);
                }
                // 0x003b3814: slot->next = 0; restart from the new head
                charge(ctx, 6);
                sw(zero, a0, raster_slot::kNext);
                v1 = 0;
                lw(a0, gp, gp_off(font::kRasterSlots));
                lw(a0, a0, raster_mgr::kActive);
            }
        }
    }
    // 0x003b38e0: return
    charge(ctx, 2);
}

// 0x003B3E00 frFontRasterLookup -- 92 bytes; leaf frame (no stack)
// frFontRasterLookup(glyph, colour_set): the active raster slot holding glyph (+4) in colour set ((s16)+8); a
// hit refreshes its ticks to 1, marks it used (bit 0 of +0) and is returned; 0 on a miss. Blocks: entry 4; per
// slot 3, 3, hit 7, next 1; test 2; miss 1; return 2.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void frFontRasterLookup(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lh, hg::lw, hg::sh, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003b3e00: v0 = slot = the first active slot
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, gp_off(font::kRasterSlots));
    lw(v0, v0, raster_mgr::kActive);
    bool hit = false;
    for (;;) {
        // 0x003b3e48: while (slot)
        charge(ctx, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b3e10: the glyph?
        charge(ctx, 3);
        lw(v1, v0, raster_slot::kGlyph);
        if (v1 == a0) {
            // 0x003b3e1c: the colour set?
            charge(ctx, 3);
            lh(v1, v0, raster_slot::kColourSet);
            if (v1 == a1) {
                hit = true;
                break;
            }
        }
        // 0x003b3e44: slot = slot->next
        charge(ctx, 1);
        lw(v0, v0, raster_slot::kNext);
    }
    if (!hit) {
        // 0x003b3e50: a miss: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003b3e28: a hit: ticks = 1, used
        charge(ctx, 7);
        v1 = 1;
        sh(v1, v0, raster_slot::kTicks);
        lw(v1, v0, raster_slot::kFlags);
        v1 = v1 | raster_slot::kFlagUsed;
        sw(v1, v0, raster_slot::kFlags);
    }
    // 0x003b3e54: return
    charge(ctx, 2);
}

// 0x003B3DD0 frFontRasterFind -- 44 bytes; frame 0x10: ra sp+0x0
// frFontRasterFind(glyph, colour_set): frFontRasterLookup, or 0 (the original's redundant test of the result).
// Blocks: entry 6; miss 1; return 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void frFontRasterFind(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b3dd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3B3DD8u, gen::fn_frFontRasterLookup_003b3e00);
    if (v0 == 0) {
        // 0x003b3de8: a miss: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003b3dec: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points -------------------------------------------------------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
using guest::arg32;
using guest::args32;
using guest::ret32;
using guest::rets32;
void fn_frFontCreateGlyphNode_003b0620(p3fes::EEContext& ctx) {
    ret32(ctx, frFontCreateGlyphNode(ctx, arg32(ctx, 0), arg32(ctx, 1), arg32(ctx, 2), arg32(ctx, 3)));
}
void fn_frFontSetLineSpacing_003b1a80(p3fes::EEContext& ctx) { frFontSetLineSpacing(ctx, arg32(ctx, 0)); }
void fn_frFontTestTagFlags_003b2a00(p3fes::EEContext& ctx) { ret32(ctx, frFontTestTagFlags(ctx, arg32(ctx, 0))); }
void fn_frFontTagGetParam0_003af360(p3fes::EEContext& ctx) { ret32(ctx, frFontTagGetParam0(ctx)); }
void fn_frFontTagGetParam1_003af370(p3fes::EEContext& ctx) { ret32(ctx, frFontTagGetParam1(ctx)); }
void fn_frFontTagGetParam2_003af380(p3fes::EEContext& ctx) { ret32(ctx, frFontTagGetParam2(ctx)); }
void fn_frFontTagGetParam3_003af390(p3fes::EEContext& ctx) { ret32(ctx, frFontTagGetParam3(ctx)); }
}  // namespace p3fes::recomp_gen
