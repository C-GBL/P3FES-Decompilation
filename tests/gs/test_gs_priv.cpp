// GS privileged registers: CSR (FIELD from the time base, revision, W1C flags, RESET), IMR and the GS interrupt,
// SIGNAL/FINISH/LABEL, 32-bit halves, and flip detection on DISPFB writes.
#include "gs_test_util.h"

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;

namespace {
constexpr u32 kCsr = 0x12001000u, kImr = 0x12001010u, kSiglblid = 0x12001080u;
constexpr u32 kPmode = 0x12000000u, kSmode2 = 0x12000020u, kDispfb1 = 0x12000070u, kDisplay1 = 0x12000080u,
              kDispfb2 = 0x12000090u, kDisplay2 = 0x120000A0u, kBgcolor = 0x120000E0u;

// sceGsPutDispEnv's write sequence (docs/ANALYSIS/10 §2.13), then the circuit-1 copies RW's VBLANK handler adds
// (§3.1), for frame buffer `fbp`.
void put_disp_env(FakeBus& bus, u32 fbp) {
    bus.write64(kPmode, 0x8067);
    bus.write64(kSmode2, 0x1);
    bus.write64(kDispfb2, gs_dispfb(fbp, 10, 0, 0, 1));
    bus.write64(kDisplay2, 0x001BE9FF0183227Cull);
    bus.write64(kBgcolor, 0);
}
void rw_flip(FakeBus& bus, u32 fbp) {
    put_disp_env(bus, fbp);
    bus.write64(kDispfb1, gs_dispfb(fbp, 10, 0));
    bus.write64(kDisplay1, 0x001BF9FF0183227Cull);
}
} // namespace

TEST_CASE("CSR: ID 0x55 / REV 0x1B, FIFO empty, FIELD and NFIELD follow the time base (game: GParam+6 in PCSX2's first_flip state)") {
    Fixture f;
    u64 csr = f.bus.read64(kCsr);
    CHECK(((csr >> 24) & 0xFFu) == 0x55u);
    CHECK(((csr >> 16) & 0xFFu) == 0x1Bu);
    CHECK(((csr >> 14) & 3u) == 1u);
    CHECK(((csr >> 13) & 1u) == 0u);
    f.bus.vblank();
    csr = f.bus.read64(kCsr);
    CHECK(((csr >> 13) & 1u) == 1u);
    CHECK(((csr >> 12) & 1u) == 1u);
    f.bus.vblank();
    CHECK(((f.bus.read64(kCsr) >> 13) & 1u) == 0u);
    // sceGsResetGraph reads CSR byte 2 after RESET: the revision (10 §2.5).
    f.bus.write64(kCsr, 0x200);
    CHECK(((f.bus.read64(kCsr) >> 16) & 0xFFu) == 0x1Bu);
    // 32-bit read of the low half (kwlnVsyncFieldGate reads the FIELD bit with lw).
    f.bus.vblank();
    CHECK(((f.bus.read32(kCsr) >> 13) & 1u) == 1u);
}

TEST_CASE("CSR: VSINT/HSINT from the time base, write-1-to-clear (hand: GS User's Manual)") {
    Fixture f;
    CHECK((f.bus.read64(kCsr) & 0x8u) == 0u);
    f.bus.vblank();
    CHECK((f.bus.read64(kCsr) & 0x8u) != 0u);
    CHECK((f.bus.read64(kCsr) & 0x4u) != 0u);
    f.bus.write64(kCsr, 0x8);
    CHECK((f.bus.read64(kCsr) & 0x8u) == 0u);
    CHECK((f.bus.read64(kCsr) & 0x4u) != 0u);
    f.bus.write64(kCsr, 0x4);
    CHECK((f.bus.read64(kCsr) & 0x4u) == 0u);
}

TEST_CASE("SIGNAL / FINISH / LABEL: CSR flags, SIGLBLID, GS interrupt only when IMR unmasks it (hand: GS User's Manual)") {
    Fixture f;
    // Reset state masks everything (the game also writes GsPutIMR(0xFF00), 10 §2.5).
    GifBuilder g;
    g.ad({{reg::SIGNAL, 0x0000FFFF'00001234ull}, {reg::FINISH, 0}, {reg::LABEL, 0xFFFFFFFF'0000BEEFull}});
    f.send(g);
    u64 csr = f.bus.read64(kCsr);
    CHECK((csr & 1u) != 0u);
    CHECK((csr & 2u) != 0u);
    CHECK(f.bus.read64(kSiglblid) == ((0xBEEFull << 32) | 0x1234ull));
    CHECK(f.bus.count_intc(0) == 0u);
    // Unmasking FINISH with the flag pending raises the interrupt.
    f.bus.write64(kImr, 0xFD00);
    CHECK(f.bus.count_intc(0) == 1u);
    f.bus.write64(kCsr, 0x3); // W1C both
    CHECK((f.bus.read64(kCsr) & 3u) == 0u);
    GifBuilder h;
    h.ad({{reg::FINISH, 0}, {reg::SIGNAL, 0x0000000F'00000005ull}});
    f.send(h);
    CHECK(f.bus.count_intc(0) == 2u); // FINISH unmasked, SIGNAL masked
    CHECK((f.bus.read64(kSiglblid) & 0xFFFFFFFFu) == 0x1235u); // only the masked ID bits change
}

TEST_CASE("CSR.RESET resets the drawing state but keeps local memory (model)") {
    Fixture f;
    f.env();
    f.sprite(0, 0, 2, 2, 7, 7, 7, 0x80);
    f.bus.write64(kCsr, 0x200);
    CHECK(f.core().regs().ctx[0].frame == 0u);
    CHECK(f.core().regs().prmodecont == 1u);
    CHECK(R(f.px(1, 1)) == 7u);
    CHECK(f.gs->priv().stats().resets == 1u);
}

TEST_CASE("privileged: 64-bit registers, 32-bit halves, BUSDIR, unhandled offsets counted (hand: GS User's Manual)") {
    Fixture f;
    f.bus.write64(kDisplay2, 0x001BF9FF0183227Cull);
    CHECK(f.bus.read64(kDisplay2) == 0x001BF9FF0183227Cull);
    f.bus.write32(kDisplay2 + 4, 0x001BE9FFu); // DH 447 -> 446 through the high half
    CHECK(f.bus.read64(kDisplay2) == 0x001BE9FF0183227Cull);
    CHECK(f.bus.read32(kDisplay2) == 0x0183227Cu);
    f.bus.write64(0x12001040, 1);
    CHECK(f.gs->priv().busdir() == 1u);
    f.bus.write64(0x12000008, 5);
    f.bus.read64(0x12000F00);
    CHECK(f.gs->priv().stats().unhandled_writes == 1u);
    CHECK(f.gs->priv().stats().unhandled_reads == 1u);
}

TEST_CASE("flip detection: SkyStart's display setup, then one flip per RW VBLANK flip (game: 10 §2.13, §3.1)") {
    Fixture f;
    std::vector<FlipEvent> events;
    f.gs->priv().set_flip_callback([&](const FlipEvent& e) { events.push_back(e); });
    // sceGsSwapDBuffDc -> sceGsPutDispEnv(disp[0]): FBP 0, the first write after SMODE2 -> flip 1.
    put_disp_env(f.bus, 0);
    CHECK(f.gs->flip_count() == 1u);
    // Next vblank: RW's handler shows disp[1] (FBP 140) on both circuits -> exactly one flip.
    f.bus.vblank();
    rw_flip(f.bus, 140);
    CHECK(f.gs->flip_count() == 2u);
    CHECK(events.back().fbp == 140u);
    CHECK(events.back().circuit == 1u);
    // A second DISPFB write in the same vblank interval does not count again.
    f.bus.write64(kDispfb1, gs_dispfb(0, 10, 0));
    CHECK(f.gs->flip_count() == 2u);
    // Next field: DISPFB rewritten with the same FBP and no SMODE2 write: no flip.
    f.bus.vblank();
    f.bus.write64(kDispfb2, gs_dispfb(140, 10, 0, 0, 1));
    CHECK(f.gs->flip_count() == 2u);
    // Two fields later RW flips back to FBP 0.
    f.bus.vblank();
    rw_flip(f.bus, 0);
    CHECK(f.gs->flip_count() == 3u);
    CHECK(events.size() == 3u);
    CHECK(events.back().vblank == 3u);
    CHECK(f.gs->priv().stats().dispfb_writes == 7u);
}
