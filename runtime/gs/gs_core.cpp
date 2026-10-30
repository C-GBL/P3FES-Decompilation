// GS register file, vertex queue, CLUT buffer and image transfers. Register layouts and kick rules are the GS User's
// Manual's; PACKED-format field positions and the TEX2 field mask cross-checked against ps2-web-recomp @ c0f476e
// runtime/src/gs/gs.cpp (write, write_packed, load_clut, feed_image, local_copy; MIT).
#include "p3fes/gs/gs_core.h"

#include "gs_raster.h"
#include "p3fes/prof.h"

#include <algorithm>
#include <chrono>

namespace p3fes::gs {

namespace {

constexpr u64 kTex2Mask = 0xFFFFFFE003F00000ull; // TEX2 writes PSM (20-25) and CBP..CLD (37-63) of TEX0

constexpr bool indexed(u32 psm) noexcept { return psm == 0x13 || psm == 0x14 || psm == 0x1B || psm == 0x24 || psm == 0x2C; }
constexpr bool eight_bit_index(u32 psm) noexcept { return psm == 0x13 || psm == 0x1B; }

u32 vertices_for(u32 prim) noexcept {
    switch (prim & 7u) {
    case 0: return 1;           // point
    case 1: case 2: return 2;   // line, line strip
    case 3: case 4: case 5: return 3; // triangle, strip, fan
    case 6: return 2;           // sprite
    default: return 1;          // 7: prohibited
    }
}

} // namespace

GsCore::GsCore() = default;
GsCore::~GsCore() = default;

GsCoreState GsCore::save_state() const {
    GsCoreState s;
    s.regs = r_;
    s.queue = queue_;
    s.queued = queued_;
    s.clut = clut_;
    s.cbp0 = cbp0_;
    s.cbp1 = cbp1_;
    s.xfer_active = xfer_.active ? 1u : 0u;
    s.xfer_dir = xfer_.dir;
    s.xfer_x = xfer_.x;
    s.xfer_y = xfer_.y;
    s.xfer_bitbuf = xfer_.bitbuf;
    s.xfer_bitcount = xfer_.bitcount;
    return s;
}

void GsCore::load_state(const GsCoreState& s) {
    ++state_gen_;
    r_ = s.regs;
    queue_ = s.queue;
    queued_ = s.queued;
    clut_ = s.clut;
    cbp0_ = s.cbp0;
    cbp1_ = s.cbp1;
    xfer_.active = s.xfer_active != 0;
    xfer_.dir = s.xfer_dir;
    xfer_.x = s.xfer_x;
    xfer_.y = s.xfer_y;
    xfer_.bitbuf = s.xfer_bitbuf;
    xfer_.bitcount = s.xfer_bitcount;
}

void GsCore::reset() {
    if (sink_) sink_->on_reset();
    ++state_gen_;
    r_ = GsRegs{};
    queue_ = {};
    queued_ = 0;
    clut_ = {};
    cbp0_ = cbp1_ = 0xFFFFFFFFu;
    xfer_ = Transfer{};
}

void GsCore::write_reg_impl(u32 reg, u64 v) {
    ++stats_.reg_writes;
    {
        // Per-vertex registers (RGBAQ ST UV XYZF2 XYZ2 FOG XYZF3 XYZ3) leave the draw state alone; any other write
        // may change it (state_generation()).
        constexpr u64 kVertexRegs = (1ull << 0x01) | (1ull << 0x02) | (1ull << 0x03) | (1ull << 0x04) | (1ull << 0x05) |
                                    (1ull << 0x0A) | (1ull << 0x0C) | (1ull << 0x0D);
        const u32 r = reg & 0xFFu;
        if (r >= 64 || ((kVertexRegs >> r) & 1u) == 0) ++state_gen_;
    }
    if (reg_observer_) {
        const u32 r = reg & 0xFFu;
        if (r == reg::PRIM || (r >= reg::TEX0_1 && r != reg::FOG && r != reg::XYZF3 && r != reg::XYZ3)) reg_observer_(r, v);
    }
    switch (reg & 0xFFu) {
    case reg::PRIM:
        r_.prim = v & 0x7FFu;
        queued_ = 0;
        break;
    case reg::RGBAQ: r_.rgbaq = v; break;
    case reg::ST: r_.st = v; break;
    case reg::UV: r_.uv = v & 0x3FFF3FFFull; break;
    case reg::XYZF2: vertex(static_cast<u32>(v), static_cast<u32>(v >> 32) & 0xFFFFFFu, static_cast<u8>(v >> 56), true); break;
    case reg::XYZ2: vertex(static_cast<u32>(v), static_cast<u32>(v >> 32), static_cast<u8>(r_.fog >> 56), true); break;
    case reg::XYZF3: vertex(static_cast<u32>(v), static_cast<u32>(v >> 32) & 0xFFFFFFu, static_cast<u8>(v >> 56), false); break;
    case reg::XYZ3: vertex(static_cast<u32>(v), static_cast<u32>(v >> 32), static_cast<u8>(r_.fog >> 56), false); break;
    case reg::TEX0_1:
    case reg::TEX0_2:
        r_.ctx[reg - reg::TEX0_1].tex0 = v;
        load_clut(v);
        break;
    case reg::CLAMP_1:
    case reg::CLAMP_2: r_.ctx[reg - reg::CLAMP_1].clamp = v; break;
    case reg::FOG: r_.fog = v & 0xFF00000000000000ull; break;
    case reg::TEX1_1:
    case reg::TEX1_2: r_.ctx[reg - reg::TEX1_1].tex1 = v; break;
    case reg::TEX2_1:
    case reg::TEX2_2: {
        u64& t = r_.ctx[reg - reg::TEX2_1].tex0;
        t = (t & ~kTex2Mask) | (v & kTex2Mask);
        load_clut(t);
        break;
    }
    case reg::XYOFFSET_1:
    case reg::XYOFFSET_2: r_.ctx[reg - reg::XYOFFSET_1].xyoffset = v; break;
    case reg::PRMODECONT: r_.prmodecont = v & 1u; break;
    case reg::PRMODE: r_.prmode = v & 0x7F8u; break;
    case reg::TEXCLUT: r_.texclut = v; break;
    case reg::SCANMSK: r_.scanmsk = v & 3u; break;
    case reg::MIPTBP1_1:
    case reg::MIPTBP1_2: r_.ctx[reg - reg::MIPTBP1_1].miptbp1 = v; break;
    case reg::MIPTBP2_1:
    case reg::MIPTBP2_2: r_.ctx[reg - reg::MIPTBP2_1].miptbp2 = v; break;
    case reg::TEXA: r_.texa = v; break;
    case reg::FOGCOL: r_.fogcol = v; break;
    case reg::TEXFLUSH: break; // no texture cache in this model: every sample reads local memory
    case reg::SCISSOR_1:
    case reg::SCISSOR_2: r_.ctx[reg - reg::SCISSOR_1].scissor = v; break;
    case reg::ALPHA_1:
    case reg::ALPHA_2: r_.ctx[reg - reg::ALPHA_1].alpha = v; break;
    case reg::DIMX: r_.dimx = v; break;
    case reg::DTHE: r_.dthe = v & 1u; break;
    case reg::COLCLAMP: r_.colclamp = v & 1u; break;
    case reg::TEST_1:
    case reg::TEST_2: r_.ctx[reg - reg::TEST_1].test = v; break;
    case reg::PABE: r_.pabe = v & 1u; break;
    case reg::FBA_1:
    case reg::FBA_2: r_.ctx[reg - reg::FBA_1].fba = v & 1u; break;
    case reg::FRAME_1:
    case reg::FRAME_2: r_.ctx[reg - reg::FRAME_1].frame = v; break;
    case reg::ZBUF_1:
    case reg::ZBUF_2: r_.ctx[reg - reg::ZBUF_1].zbuf = v; break;
    case reg::BITBLTBUF: r_.bitbltbuf = v; break;
    case reg::TRXPOS: r_.trxpos = v; break;
    case reg::TRXREG: r_.trxreg = v; break;
    case reg::TRXDIR:
        r_.trxdir = v & 3u;
        start_transfer(v);
        break;
    case reg::HWREG: write_hwreg_impl(v); break;
    case reg::SIGNAL:
        if (events_) events_->on_signal(static_cast<u32>(v), static_cast<u32>(v >> 32));
        break;
    case reg::FINISH:
        if (events_) events_->on_finish();
        break;
    case reg::LABEL:
        if (events_) events_->on_label(static_cast<u32>(v), static_cast<u32>(v >> 32));
        break;
    case reg::NOP: break;
    default:
        ++stats_.unknown_reg_writes;
        break;
    }
}

void GsCore::write_packed(u32 desc, const u128& q) {
    if (sink_) sink_->on_packed(desc, q);
    switch (desc & 0xFu) {
    case 0x0: write_reg_impl(reg::PRIM, q.u64[0] & 0x7FFu); break;
    case 0x1:
        ++stats_.reg_writes;
        r_.rgbaq = (q.u32[0] & 0xFFu) | ((q.u32[1] & 0xFFu) << 8) | ((q.u32[2] & 0xFFu) << 16) |
                   (static_cast<u64>(q.u32[3] & 0xFFu) << 24) | (static_cast<u64>(r_.q_internal) << 32);
        break;
    case 0x2:
        ++stats_.reg_writes;
        r_.st = q.u64[0];
        r_.q_internal = q.u32[2];
        break;
    case 0x3:
        ++stats_.reg_writes;
        r_.uv = (q.u32[0] & 0x3FFFu) | (static_cast<u64>(q.u32[1] & 0x3FFFu) << 16);
        break;
    case 0x4: {
        ++stats_.reg_writes;
        const bool adc = ((q.u32[3] >> 15) & 1u) != 0;
        vertex((q.u32[0] & 0xFFFFu) | ((q.u32[1] & 0xFFFFu) << 16), (q.u32[2] >> 4) & 0xFFFFFFu,
               static_cast<u8>(q.u32[3] >> 4), !adc);
        break;
    }
    case 0x5: {
        ++stats_.reg_writes;
        const bool adc = ((q.u32[3] >> 15) & 1u) != 0;
        vertex((q.u32[0] & 0xFFFFu) | ((q.u32[1] & 0xFFFFu) << 16), q.u32[2], static_cast<u8>(r_.fog >> 56), !adc);
        break;
    }
    case 0x6: case 0x7: case 0x8: case 0x9: write_reg_impl(desc & 0xFu, q.u64[0]); break;
    case 0xA:
        ++stats_.reg_writes;
        r_.fog = static_cast<u64>((q.u32[3] >> 4) & 0xFFu) << 56;
        break;
    case 0xC:
        ++stats_.reg_writes;
        vertex((q.u32[0] & 0xFFFFu) | ((q.u32[1] & 0xFFFFu) << 16), (q.u32[2] >> 4) & 0xFFFFFFu,
               static_cast<u8>(q.u32[3] >> 4), false);
        break;
    case 0xD:
        ++stats_.reg_writes;
        vertex((q.u32[0] & 0xFFFFu) | ((q.u32[1] & 0xFFFFu) << 16), q.u32[2], static_cast<u8>(r_.fog >> 56), false);
        break;
    case 0xE: write_reg_impl(q.u8[8], q.u64[0]); break;
    case 0xF: break;
    default: ++stats_.unknown_reg_writes; break; // 0xB reserved
    }
}

void GsCore::vertex(u32 xy, u32 z, u8 f, bool kick) {
    const u32 prim = static_cast<u32>(r_.prim) & 7u;
    const u32 needed = vertices_for(prim);
    if (queued_ >= 3) queued_ = 2; // defensive: the queue never holds more than 3
    GsVertex& vx = queue_[queued_++];
    vx.x = xy & 0xFFFFu;
    vx.y = xy >> 16;
    vx.z = z;
    vx.r = static_cast<u8>(r_.rgbaq);
    vx.g = static_cast<u8>(r_.rgbaq >> 8);
    vx.b = static_cast<u8>(r_.rgbaq >> 16);
    vx.a = static_cast<u8>(r_.rgbaq >> 24);
    vx.q = static_cast<u32>(r_.rgbaq >> 32);
    vx.s = static_cast<u32>(r_.st);
    vx.t = static_cast<u32>(r_.st >> 32);
    vx.u = static_cast<u32>(r_.uv) & 0x3FFFu;
    vx.v = static_cast<u32>(r_.uv >> 16) & 0x3FFFu;
    vx.f = f;
    if (queued_ < needed) return;
    if (kick) draw_queue();
    switch (prim) {
    case 2: // line strip: keep the last vertex
        queue_[0] = queue_[1];
        queued_ = 1;
        break;
    case 4: // triangle strip: keep the last two
        queue_[0] = queue_[1];
        queue_[1] = queue_[2];
        queued_ = 2;
        break;
    case 5: // triangle fan: keep the first and the last
        queue_[1] = queue_[2];
        queued_ = 2;
        break;
    default: queued_ = 0; break;
    }
}

void GsCore::draw_queue() {
    const u32 prim = static_cast<u32>(r_.prim) & 7u;
    if (prim == 7) {
        ++stats_.prohibited_prims;
        return;
    }
    ++stats_.primitives;
    const u32 count = vertices_for(prim);
    if (draw_observer_) [[unlikely]] {
        u64 pixels = 0, ns = 0;
        if (software_raster_) {
            const u64 p0 = stats_.pixels_written;
            const auto t0 = std::chrono::steady_clock::now();
            detail::rasterize(mem_, clut_, detail::decode_draw_state(r_), queue_.data(), count, stats_);
            ns = static_cast<u64>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t0).count());
            pixels = stats_.pixels_written - p0;
            draw_observer_->on_draw(r_, queue_.data(), count, pixels, ns);
        } else {
            // A GPU back end records the primitive instead: its EE-side cost is what gs_raster measures then.
            const prof::Scope prof_zone(prof::Zone::GsRaster);
            draw_observer_->on_draw(r_, queue_.data(), count, pixels, ns);
            // The back end could not draw it and handed rasterisation back to the core (set_software_raster).
            if (software_raster_) [[unlikely]]
                detail::rasterize(mem_, clut_, detail::decode_draw_state(r_), queue_.data(), count, stats_);
        }
        return;
    }
    if (!software_raster_) return;
    const u64 pixels_before = stats_.pixels_written;
    const u64 ticks_before = prof::cur().ticks[static_cast<unsigned>(prof::Zone::GsRaster)];
    bool tme = false, bilinear = false;
    {
        const prof::Scope prof_zone(prof::Zone::GsRaster);
        const detail::DrawState ds = detail::decode_draw_state(r_);
        detail::rasterize(mem_, clut_, ds, queue_.data(), count, stats_);
        tme = ds.tme;
        bilinear = ds.tex.mmag_linear;
    }
    if (prof::on()) {  // workload counters (prof.h)
        prof::Work& w = prof::cur().work;
        const u64 px = stats_.pixels_written - pixels_before;
        ++w.prims[prim];
        w.prim_pixels[prim] += px;
        w.prim_ticks[prim] += prof::cur().ticks[static_cast<unsigned>(prof::Zone::GsRaster)] - ticks_before;
        if (tme) w.tex_pixels += px;
        if (tme && bilinear) w.bilinear_pixels += px;
    }
}

void GsCore::load_clut(u64 tex0) {
    const u32 cld = static_cast<u32>(tex0 >> 61) & 7u;
    const u32 cbp = static_cast<u32>(tex0 >> 37) & 0x3FFFu;
    switch (cld) {
    case 0: return;
    case 1: break;
    case 2: cbp0_ = cbp; break;
    case 3: cbp1_ = cbp; break;
    case 4:
        if (cbp == cbp0_) return;
        cbp0_ = cbp;
        break;
    case 5:
        if (cbp == cbp1_) return;
        cbp1_ = cbp;
        break;
    default: return; // 6, 7 reserved
    }
    const u32 psm = static_cast<u32>(tex0 >> 20) & 0x3Fu;
    if (!indexed(psm)) return; // inferred: the CLUT buffer is only loaded for indexed textures
    const prof::Scope prof_zone(prof::Zone::GsUpload);
    const u32 cpsm = static_cast<u32>(tex0 >> 51) & 0xFu;
    const bool csm2 = ((tex0 >> 55) & 1u) != 0;
    const u32 csa = static_cast<u32>(tex0 >> 56) & 0x1Fu;
    const bool eight = eight_bit_index(psm);
    const u32 entries = eight ? 256u : 16u;
    const u32 cbw = bits(r_.texclut, 0, 6), cou = bits(r_.texclut, 6, 6), cov = bits(r_.texclut, 12, 10);
    ++stats_.clut_loads;
    if (draw_observer_) draw_observer_->on_clut_load(tex0, r_.texclut);
    for (u32 i = 0; i < entries; ++i) {
        u32 x, y, bw;
        if (csm2) {
            x = cou * 16u + i;
            y = cov;
            bw = cbw;
        } else if (eight) {
            // CSM1 8-bit: 16 x 16 entries, index bits 3 and 4 swapped (blocks of 8 x 2 entries).
            const u32 j = (i & ~0x18u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1);
            x = j & 15u;
            y = j >> 4;
            bw = 1;
        } else {
            x = i & 7u; // CSM1 4-bit: 8 x 2 entries
            y = i >> 3;
            bw = 1;
        }
        const u32 c = mem_.read(cpsm, cbp, bw, x, y);
        if (cpsm == 0x0u || cpsm == 0x1u) {
            const u32 slot = eight ? i : ((csa & 15u) * 16u + i) & 255u;
            clut_[slot] = static_cast<u16>(c);
            clut_[slot + 256u] = static_cast<u16>(c >> 16);
        } else {
            const u32 slot = eight ? i : (csa * 16u + i) & 511u;
            clut_[slot] = static_cast<u16>(c);
        }
    }
}

void GsCore::start_transfer(u64 trxdir) {
    const prof::Scope prof_zone(prof::Zone::GsUpload);
    xfer_ = Transfer{};
    xfer_.dir = static_cast<u32>(trxdir & 3u);
    const u32 rrw = bits(r_.trxreg, 0, 12), rrh = bits(r_.trxreg, 32, 12);
    switch (xfer_.dir) {
    case 0:
    case 1:
        xfer_.active = rrw != 0 && rrh != 0;
        if (!psm_valid(bits(r_.bitbltbuf, xfer_.dir == 0 ? 56 : 24, 6))) ++stats_.invalid_psm;
        if (xfer_.dir == 1 && draw_observer_) draw_observer_->on_local_read(r_.bitbltbuf, r_.trxpos, r_.trxreg);
        break;
    case 2:
        if (draw_observer_) draw_observer_->on_local_copy(r_.bitbltbuf, r_.trxpos, r_.trxreg);
        local_copy();
        break;
    default: break;
    }
}

void GsCore::transfer_pixel_in(u32 value) {
    const u64 b = r_.bitbltbuf, p = r_.trxpos;
    const u32 dbp = bits(b, 32, 14), dbw = bits(b, 48, 6), dpsm = bits(b, 56, 6);
    const u32 dsax = bits(p, 32, 11), dsay = bits(p, 48, 11);
    const u32 rrw = bits(r_.trxreg, 0, 12), rrh = bits(r_.trxreg, 32, 12);
    const u32 x = dsax + xfer_.x, y = dsay + xfer_.y;
    mem_.write(dpsm, dbp, dbw, x, y, value);
    if (draw_observer_) {
        if (span_n_ && span_y_ == y && span_x_ + span_n_ == x) {
            ++span_n_;
        } else {
            flush_span();
            span_x_ = x;
            span_y_ = y;
            span_n_ = 1;
        }
    }
    if (++xfer_.x >= rrw) {
        xfer_.x = 0;
        if (++xfer_.y >= rrh) xfer_.active = false;
    }
}

void GsCore::flush_span() {
    if (span_n_ && draw_observer_) {
        const u64 b = r_.bitbltbuf;
        draw_observer_->on_transfer_span(bits(b, 56, 6), bits(b, 32, 14), bits(b, 48, 6), span_x_, span_y_, span_n_);
    }
    span_n_ = 0;
}

// 32-bit transfer data on a qword boundary: the buffer fields are decoded once per call, whole rows at a time.
void GsCore::image32(std::span<const u128> qwords) {
    const u64 b = r_.bitbltbuf, p = r_.trxpos;
    const u32 dbp = bits(b, 32, 14), dbw = bits(b, 48, 6), dpsm = bits(b, 56, 6);
    const u32 dsax = bits(p, 32, 11), dsay = bits(p, 48, 11);
    const u32 rrw = bits(r_.trxreg, 0, 12), rrh = bits(r_.trxreg, 32, 12);
    std::size_t qi = 0;
    u32 wi = 0;  // next word of qwords[qi]
    while (qi < qwords.size()) {
        if (!xfer_.active) {
            stats_.image_qwords_ignored += qwords.size() - qi;
            return;
        }
        const u32 y = dsay + xfer_.y, x0 = dsax + xfer_.x;
        const u32 run = std::min<u32>(rrw - xfer_.x, static_cast<u32>((qwords.size() - qi) * 4u - wi));
        if (dpsm == 0x00 || dpsm == 0x30) {
            // Full 32-bit words (CT32 / Z32): GsMemory::addr32 with the row's swizzle row and page row taken once.
            const SwizzleTables& tab = swizzle_tables();
            const u16* row = (dpsm == 0x30 ? tab.z32 : tab.ct32)[y & 31u].data();
            const u32 prow = ((y & 2047u) >> 5) * dbw;
            u8* m = mem_.data();
            for (u32 k = 0; k < run; ++k) {
                if (wi == 0) ++stats_.image_qwords_in;
                const u32 x = (x0 + k) & 2047u;
                const u32 a = ((dbp + (prow + (x >> 6)) * kBlocksPerPage) * kBlockBytes + row[x & 63u]) & kVramMask;
                std::memcpy(m + a, &qwords[qi].u32[wi], 4);
                if (++wi == 4) {
                    wi = 0;
                    ++qi;
                }
            }
        } else {
            for (u32 k = 0; k < run; ++k) {
                if (wi == 0) ++stats_.image_qwords_in;
                mem_.write(dpsm, dbp, dbw, x0 + k, y, qwords[qi].u32[wi]);
                if (++wi == 4) {
                    wi = 0;
                    ++qi;
                }
            }
        }
        if (draw_observer_ && run) {
            flush_span();
            draw_observer_->on_transfer_span(dpsm, dbp, dbw, x0, y, run);
        }
        xfer_.x += run;
        if (xfer_.x >= rrw) {
            xfer_.x = 0;
            if (++xfer_.y >= rrh) xfer_.active = false;
        }
        if (!xfer_.active && wi != 0) {  // the rest of a partly used qword is padding
            wi = 0;
            ++qi;
        }
    }
}

// 16-bit transfer data (CT16 / CT16S / Z16 / Z16S) on a qword boundary: eight pixels per qword, whole rows at a time,
// the swizzle row and page row taken once per row (the byte packer's result: pixels never straddle a qword).
void GsCore::image16(std::span<const u128> qwords) {
    const u64 b = r_.bitbltbuf, p = r_.trxpos;
    const u32 dbp = bits(b, 32, 14), dbw = bits(b, 48, 6), dpsm = bits(b, 56, 6);
    const u32 dsax = bits(p, 32, 11), dsay = bits(p, 48, 11);
    const u32 rrw = bits(r_.trxreg, 0, 12), rrh = bits(r_.trxreg, 32, 12);
    const SwizzleTables& tab = swizzle_tables();
    const auto& t16 = dpsm == 0x0A ? tab.ct16s : dpsm == 0x32 ? tab.z16 : dpsm == 0x3A ? tab.z16s : tab.ct16;
    u8* m = mem_.data();
    std::size_t qi = 0;
    u32 hi = 0;  // next halfword of qwords[qi]
    while (qi < qwords.size()) {
        if (!xfer_.active) {
            stats_.image_qwords_ignored += qwords.size() - qi;
            return;
        }
        const u32 y = dsay + xfer_.y, x0 = dsax + xfer_.x;
        const u32 run = std::min<u32>(rrw - xfer_.x, static_cast<u32>((qwords.size() - qi) * 8u - hi));
        const u16* row = t16[y & 63u].data();
        const u32 prow = ((y & 2047u) >> 6) * dbw;
        for (u32 k = 0; k < run; ++k) {
            if (hi == 0) ++stats_.image_qwords_in;
            const u32 x = (x0 + k) & 2047u;
            const u32 a = ((dbp + (prow + (x >> 6)) * kBlocksPerPage) * kBlockBytes + row[x & 63u]) & kVramMask;
            std::memcpy(m + a, &qwords[qi].u8[hi * 2u], 2);
            if (++hi == 8) {
                hi = 0;
                ++qi;
            }
        }
        if (draw_observer_ && run) {
            flush_span();
            draw_observer_->on_transfer_span(dpsm, dbp, dbw, x0, y, run);
        }
        xfer_.x += run;
        if (xfer_.x >= rrw) {
            xfer_.x = 0;
            if (++xfer_.y >= rrh) xfer_.active = false;
        }
        if (!xfer_.active && hi != 0) {  // the rest of a partly used qword is padding
            hi = 0;
            ++qi;
        }
    }
}

bool GsCore::transfer_pixel_out(u32& value) {
    if (!local_to_host_active()) return false;
    const u64 b = r_.bitbltbuf, p = r_.trxpos;
    const u32 sbp = bits(b, 0, 14), sbw = bits(b, 16, 6), spsm = bits(b, 24, 6);
    const u32 ssax = bits(p, 0, 11), ssay = bits(p, 16, 11);
    const u32 rrw = bits(r_.trxreg, 0, 12), rrh = bits(r_.trxreg, 32, 12);
    value = mem_.read(spsm, sbp, sbw, ssax + xfer_.x, ssay + xfer_.y);
    if (++xfer_.x >= rrw) {
        xfer_.x = 0;
        if (++xfer_.y >= rrh) xfer_.active = false;
    }
    return true;
}

void GsCore::write_image(std::span<const u128> qwords) {
    if (sink_) sink_->on_image(qwords);
    const prof::Scope prof_zone(prof::Zone::GsUpload);
    if (!host_to_local_active()) {
        stats_.image_qwords_ignored += qwords.size();
        return;
    }
    const u32 bpp = psm_transfer_bits(bits(r_.bitbltbuf, 56, 6));
    if (bpp == 32 && xfer_.bitcount == 0) {
        image32(qwords);
        flush_span();
        return;
    }
    const u32 dpsm = bits(r_.bitbltbuf, 56, 6);
    if (bpp == 16 && xfer_.bitcount == 0 && (dpsm == 0x02 || dpsm == 0x0A || dpsm == 0x32 || dpsm == 0x3A)) {
        image16(qwords);
        flush_span();
        return;
    }
    const u64 mask = (1ull << bpp) - 1ull;
    for (const u128& q : qwords) {
        if (!xfer_.active) {
            ++stats_.image_qwords_ignored;
            continue;
        }
        ++stats_.image_qwords_in;
        for (u32 i = 0; i < 16 && xfer_.active; ++i) {
            xfer_.bitbuf |= static_cast<u64>(q.u8[i]) << xfer_.bitcount;
            xfer_.bitcount += 8;
            while (xfer_.bitcount >= bpp && xfer_.active) {
                transfer_pixel_in(static_cast<u32>(xfer_.bitbuf & mask));
                xfer_.bitbuf >>= bpp;
                xfer_.bitcount -= bpp;
            }
        }
    }
    flush_span();
}

void GsCore::write_hwreg_impl(u64 value) {
    const prof::Scope prof_zone(prof::Zone::GsUpload);
    if (!host_to_local_active()) {
        ++stats_.image_qwords_ignored;
        return;
    }
    // Feed the 8 bytes through the same packer as IMAGE data (a half qword).
    const u32 bpp = psm_transfer_bits(bits(r_.bitbltbuf, 56, 6));
    const u64 mask = (1ull << bpp) - 1ull;
    for (u32 i = 0; i < 8 && xfer_.active; ++i) {
        xfer_.bitbuf |= ((value >> (i * 8u)) & 0xFFu) << xfer_.bitcount;
        xfer_.bitcount += 8;
        while (xfer_.bitcount >= bpp && xfer_.active) {
            transfer_pixel_in(static_cast<u32>(xfer_.bitbuf & mask));
            xfer_.bitbuf >>= bpp;
            xfer_.bitcount -= bpp;
        }
    }
    flush_span();
}

void GsCore::read_image(std::span<u128> out) {
    if (sink_) sink_->on_read_image(out.size());
    const prof::Scope prof_zone(prof::Zone::GsUpload);
    const u32 bpp = psm_transfer_bits(bits(r_.bitbltbuf, 24, 6));
    for (u128& q : out) {
        q = u128{};
        if (local_to_host_active() || xfer_.bitcount) ++stats_.image_qwords_out;
        for (u32 i = 0; i < 16; ++i) {
            while (xfer_.bitcount < 8) {
                u32 v;
                if (!transfer_pixel_out(v)) break;
                xfer_.bitbuf |= static_cast<u64>(v & ((1ull << bpp) - 1ull)) << xfer_.bitcount;
                xfer_.bitcount += bpp;
            }
            if (xfer_.bitcount == 0) break;
            q.u8[i] = static_cast<u8>(xfer_.bitbuf);
            xfer_.bitbuf >>= 8;
            xfer_.bitcount = xfer_.bitcount >= 8 ? xfer_.bitcount - 8 : 0;
        }
    }
}

void GsCore::local_copy() {
    const u64 b = r_.bitbltbuf, p = r_.trxpos;
    const u32 sbp = bits(b, 0, 14), sbw = bits(b, 16, 6), spsm = bits(b, 24, 6);
    const u32 dbp = bits(b, 32, 14), dbw = bits(b, 48, 6), dpsm = bits(b, 56, 6);
    const u32 ssax = bits(p, 0, 11), ssay = bits(p, 16, 11), dsax = bits(p, 32, 11), dsay = bits(p, 48, 11);
    const u32 dir = bits(p, 59, 2);
    const u32 rrw = bits(r_.trxreg, 0, 12), rrh = bits(r_.trxreg, 32, 12);
    ++stats_.local_copies;
    if (!psm_valid(spsm) || !psm_valid(dpsm) || psm_bits(spsm) != psm_bits(dpsm)) ++stats_.invalid_psm;
    // DIR: 0 upper-left -> lower-right, 1 lower-left -> upper-right, 2 upper-right -> lower-left, 3 lower-right ->
    // upper-left. Copying pixel by pixel in that order reproduces the overlap behaviour the order exists for.
    for (u32 j = 0; j < rrh; ++j) {
        const u32 y = (dir & 1u) ? rrh - 1u - j : j;
        for (u32 i = 0; i < rrw; ++i) {
            const u32 x = (dir & 2u) ? rrw - 1u - i : i;
            mem_.write(dpsm, dbp, dbw, dsax + x, dsay + y, mem_.read(spsm, sbp, sbw, ssax + x, ssay + y));
        }
    }
}

} // namespace p3fes::gs
