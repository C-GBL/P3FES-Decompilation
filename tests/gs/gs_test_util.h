// Shared helpers for tests/gs: a fake HwBus (time base, interrupt log, range routing), a GS fixture with the
// game's default draw environment, and small readers.
//
// Tags used in test names (tests/ee convention):
//   (hand: GS User's Manual)                   expected value derived by hand from the manual's definition
//   (hand: EE User's Manual)                   same, VIF chapter
//   (game: docs/ANALYSIS/..)                   register values the game writes, from the topic docs
//   (upstream behaviour, hardware-unverified)  expected value is what ps2-web-recomp @ c0f476e does
//   (model)                                    a property of this model's documented choice (README "approximate")
#pragma once

#include <doctest.h>

#include "p3fes/gs/gif_builder.h"
#include "p3fes/gs/gs_output.h"
#include "p3fes/gs/gs_system.h"

#include <memory>
#include <vector>

namespace p3fes::gs::test {

class FakeBus final : public hle::HwBus {
public:
    struct Range {
        u32 begin, end;
        hle::HwDevice* dev;
    };
    std::vector<Range> ranges;
    hle::DmaChannelHandler* dma[10] = {};
    std::vector<unsigned> intc;
    std::vector<unsigned> dma_done;
    hle::Timebase tb{};

    void map(u32 b, u32 e, hle::HwDevice* d) override { ranges.push_back({b, e, d}); }
    void set_dma_handler(unsigned ch, hle::DmaChannelHandler* h) override { dma[ch] = h; }
    void raise_intc(unsigned cause) override { intc.push_back(cause); }
    void dma_complete(unsigned ch) override { dma_done.push_back(ch); }
    const hle::Timebase& time() const override { return tb; }

    hle::HwDevice* find(u32 pa) const {
        for (const Range& r : ranges)
            if (pa >= r.begin && pa < r.end) return r.dev;
        return nullptr;
    }
    u32 read32(u32 pa) override { auto* d = find(pa); return d ? d->read32(pa) : 0; }
    void write32(u32 pa, u32 v) override { if (auto* d = find(pa)) d->write32(pa, v); }
    u64 read64(u32 pa) override { auto* d = find(pa); return d ? d->read64(pa) : 0; }
    void write64(u32 pa, u64 v) override { if (auto* d = find(pa)) d->write64(pa, v); }
    u128 read128(u32 pa) override { auto* d = find(pa); return d ? d->read128(pa) : u128{}; }
    void write128(u32 pa, const u128& v) override { if (auto* d = find(pa)) d->write128(pa, v); }
    u8 read8(u32 pa) override { auto* d = find(pa); return d ? d->read8(pa) : 0; }
    u16 read16(u32 pa) override { auto* d = find(pa); return d ? d->read16(pa) : 0; }
    void write8(u32 pa, u8 v) override { if (auto* d = find(pa)) d->write8(pa, v); }
    void write16(u32 pa, u16 v) override { if (auto* d = find(pa)) d->write16(pa, v); }

    // A VBLANK_START as the kernel/timing owner would produce it.
    void vblank() {
        ++tb.vblanks;
        tb.field ^= 1u;
        tb.hlines += 262;
    }
    std::size_t count_intc(unsigned cause) const {
        std::size_t n = 0;
        for (unsigned c : intc) n += c == cause;
        return n;
    }
};

// A GsSystem attached to a FakeBus, with helpers for the common draw setup: FRAME FBP 0 / FBW 10 / PSMCT32,
// Z PSMZ16S at ZBP 280 (masked), XYOFFSET 0, full scissor, TEST = Z always (the shape of SkyStart's environment,
// docs/ANALYSIS/10 §2.8, without the window offset so coordinates are plain pixels).
struct Fixture {
    FakeBus bus;
    std::unique_ptr<GsSystem> gs = std::make_unique<GsSystem>();

    Fixture() { gs->attach(bus); }

    GsCore& core() { return gs->core(); }
    GsMemory& mem() { return gs->mem(); }

    std::size_t send(const GifBuilder& b) { return gs->gif().path3(b.qwords()); }

    void env(u32 fpsm = 0x00, u32 fbmsk = 0, u32 fbw = 10) {
        GifBuilder b;
        b.ad({{reg::FRAME_1, gs_frame(0, fbw, fpsm, fbmsk)},
              {reg::ZBUF_1, gs_zbuf(280, 0xA, true)},
              {reg::XYOFFSET_1, 0},
              {reg::SCISSOR_1, gs_scissor(0, 2047, 0, 2047)},
              {reg::PRMODECONT, 1},
              {reg::COLCLAMP, 1},
              {reg::DTHE, 0},
              {reg::TEST_1, gs_test(false, 0, 0, 0, false, false, true, 1)},
              {reg::ALPHA_1, 0},
              {reg::FBA_1, 0},
              {reg::PABE, 0}});
        send(b);
    }
    // Axis-aligned sprite in whole pixels: [x0, x1) x [y0, y1).
    void sprite(u32 x0, u32 y0, u32 x1, u32 y1, u32 r, u32 g, u32 b, u32 a, bool abe = false, u32 z = 0) {
        GifBuilder q;
        q.ad({{reg::PRIM, gs_prim(6, false, false, false, abe)},
              {reg::RGBAQ, gs_rgbaq(r, g, b, a)},
              {reg::XYZ2, gs_xyz(x0 * 16, y0 * 16, z)},
              {reg::XYZ2, gs_xyz(x1 * 16, y1 * 16, z)}});
        send(q);
    }
    u32 px(u32 x, u32 y, u32 fbw = 10) { return mem().read(0x00, 0, fbw, x, y); }
};

inline u32 R(u32 c) { return c & 0xFFu; }
inline u32 G(u32 c) { return (c >> 8) & 0xFFu; }
inline u32 B(u32 c) { return (c >> 16) & 0xFFu; }
inline u32 A(u32 c) { return c >> 24; }

} // namespace p3fes::gs::test
