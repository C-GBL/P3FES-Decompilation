// IpuSystem on a bus: the register/FIFO windows and widths, the DMA handler contract, INTC 8 and the service, then
// end-to-end through the real kernel DMAC (runtime/hle/kernel): a toIPU source chain of REF tags (the shape of the
// game's ring), fromIPU normal mode into RAM, CSC with D_STAT ordering, and the sceIpuStopDMA / sceIpuRestartDMA
// rewind (MADR - (FP + IFC) x 16, BCLR(BP)) reproducing the bit stream exactly.
#include "ipu_test_util.h"

#include "p3fes/hle/kernel.h"
#include "p3fes_recomp_rt.h"

#include <memory>

using namespace it;

namespace {

void no_fn(EEContext&) {}
hle::GuestFn no_lookup(u32) { return &no_fn; }

constexpr u32 kDCtrl = 0x1000E000u, kDStat = 0x1000E010u;
constexpr u32 kD3 = 0x1000B000u, kD4 = 0x1000B400u;
constexpr u32 kChcr = 0x00, kMadr = 0x10, kQwc = 0x20, kTadr = 0x30;

constexpr u64 dmatag(u32 id, u32 qwc, u32 addr) { return u64{qwc} | (u64{id} << 28) | (u64{addr} << 32); }

struct KRig {
    EEMemory mem;
    EEContext ctx;
    std::vector<std::string> fatals;
    std::vector<IpuTrap> traps;
    std::unique_ptr<hle::Kernel> k;
    IpuSystem ipu;

    KRig() {
        ctx.memory = &mem;
        hle::KernelOptions o;
        o.lookup = &no_lookup;
        o.fatal_sink = [this](const hle::FatalInfo& f) { fatals.push_back(f.message); };
        o.log_sink = [](std::string_view) {};
        k = std::make_unique<hle::Kernel>(mem, ctx, std::move(o));
        ipu.attach(k->bus());
        ipu.set_trap_handler([this](const IpuTrap& t) { traps.push_back(t); });
        k->add_device_service([this] { return ipu.service(); });
        bus().write32(kDCtrl, 1u);  // DMAE (sceDmaReset)
    }
    hle::HwBus& bus() { return k->bus(); }
    void work(u64 n) {
        ctx.cycles += n;
        k->hooks().check_events(ctx);
    }
    void put(u32 pa, const void* data, std::size_t n) { std::memcpy(mem.main_ram() + pa, data, n); }
    bool ipu_busy() { return (bus().read32(kIpuCtrl) & kCtrlBusy) != 0; }
    void wait_ipu(u64 limit = 100000) {
        for (u64 i = 0; i < limit && ipu_busy(); ++i) work(7);  // the game's `lw IPU_CTRL; bltz` loop: 7 cycles
    }
    bool d_running(u32 base) { return (bus().read32(base + kChcr) & 0x100u) != 0; }
};

// MSB-first bits [pos, pos + 32) of a byte array.
u32 bits_at(const std::vector<u8>& b, std::size_t pos) {
    u32 v = 0;
    for (unsigned i = 0; i < 32; ++i) {
        const std::size_t p = pos + i;
        v = (v << 1) | ((b[p >> 3] >> (7 - (p & 7))) & 1u);
    }
    return v;
}

} // namespace

// The kernel library's default lookup (unused: KernelOptions::lookup is set) still needs a definition to link.
namespace p3fes::rt {
Fn lookup_func(std::uint32_t) { return &no_fn; }
} // namespace p3fes::rt

TEST_CASE("IpuSystem::attach: ranges, DMA channels 3/4, 64-bit IPU_CMD/IPU_TOP, FIFO windows, traps, INTC 8") {
    FakeBus bus;
    IpuSystem ipu;
    std::vector<IpuTrap> traps;
    ipu.set_trap_handler([&](const IpuTrap& t) { traps.push_back(t); });
    ipu.attach(bus);
    REQUIRE(bus.ranges.size() == 2);
    CHECK((bus.ranges[0].b == 0x10002000u && bus.ranges[0].e == 0x10002040u));
    CHECK((bus.ranges[1].b == 0x10007000u && bus.ranges[1].e == 0x10007020u));
    CHECK(bus.dma[3] == &ipu.dma_from_ipu());
    CHECK(bus.dma[4] == &ipu.dma_to_ipu());

    bus.tb.cycles = 100;
    u8 b[16] = {0x00, 0x00, 0x01, 0xB3, 0x28, 0x01, 0xC0, 0xC4};  // a sequence header start (the M2 log's stream)
    bus.write128(kInFifo, qw_bytes(b));
    CHECK(bus.read64(kIpuTop) == 0x000001B3u);
    CHECK(bus.read32(kIpuTop + 4) == 0);
    bus.write32(kIpuCmd, fdec(32));
    CHECK((bus.read64(kIpuCmd) >> 63) == 1);
    CHECK(bus.read32(kIpuCmd + 4) == 0x80000000u);
    CHECK(ipu.service() == 116);
    bus.tb.cycles = 116;
    CHECK(ipu.service() == ~u64{0});
    CHECK(bus.intc == std::vector<unsigned>{8});
    CHECK(bus.read64(kIpuCmd) == 0x2801C0C4u);
    CHECK(bus.read32(kIpuCmd) == 0x2801C0C4u);
    CHECK(bus.read32(kIpuBp) == ((1u << kBpFpShift) | 32u));
    // output FIFO window and the channel-3 handler: nothing produced
    u128 out[4];
    CHECK(bus.dma[3]->transfer(out, 4, 0) == 0);
    // toIPU with no command: the input side takes 10 qwords (it already holds 1)
    std::vector<u128> in(20);
    CHECK(bus.dma[4]->transfer(in.data(), in.size(), 0) == 9);
    CHECK(traps.empty());
    bus.read32(kInFifo);        // 32-bit FIFO access: not modelled
    bus.write32(kIpuBp, 1);     // read-only register
    bus.read32(0x10002008u);    // a hole
    bus.write8(kIpuCmd, 1);     // byte write to a register
    bus.read128(kInFifo);       // the input FIFO is write-only
    CHECK(traps.size() == 5);
    for (const IpuTrap& t : traps) CHECK(t.kind == IpuTrap::Kind::ReservedRegister);
}

TEST_CASE("kernel DMAC: BDEC fed by a toIPU REF-tag chain, RAW16 out through fromIPU into RAM; D_STAT 3/4, INTC 8") {
    KRig r;
    Bits b;
    put_dc_only_blocks(b);
    put_dc_only_blocks(b);  // a second macroblock (DCR again: same values)
    const std::vector<u128> q = b.qwords(2);
    REQUIRE(q.size() == 3);
    r.put(0x00200000u, q.data(), 16 * q.size());
    // the game's chain shape: REF tags over a buffer (here 1 qword each), the last one REFE
    const u64 tags[3] = {dmatag(3, 1, 0x00200000u), dmatag(3, 1, 0x00200010u), dmatag(0, 1, 0x00200020u)};
    for (int i = 0; i < 3; ++i) r.mem.write<u64>(0x00210000u + 16u * static_cast<u32>(i), tags[i]);

    r.bus().write32(kIpuCtrl, mode(1));
    for (int mb = 0; mb < 2; ++mb) {
        const u32 dst = 0x00300000u + 0x400u * static_cast<u32>(mb);
        r.bus().write32(kD3 + kMadr, dst);  // receiveDataFromIPU: D3 first, then the command
        r.bus().write32(kD3 + kQwc, 48);
        r.bus().write32(kD3 + kChcr, 0x100u);
        r.bus().write32(kIpuCmd, bdec(true, true, false, 1));
        if (mb == 0) {  // _sendDataToIPU: TADR, QWC 0, CHCR 0x105 (chain, from memory, STR)
            r.bus().write32(kD4 + kTadr, 0x00210000u);
            r.bus().write32(kD4 + kQwc, 0);
            r.bus().write32(kD4 + kChcr, 0x105u);
        }
        for (int i = 0; i < 1000 && (r.bus().read32(kD3 + kQwc) != 0 || r.d_running(kD3)); ++i) r.work(16);
        CHECK(r.bus().read32(kD3 + kQwc) == 0);
        CHECK_FALSE(r.d_running(kD3));
        CHECK_FALSE(r.ipu_busy());
        const u8* ram = r.mem.main_ram() + dst;
        for (unsigned y = 0; y < 16; ++y)
            for (unsigned x = 0; x < 16; ++x) {
                s16 v = 0;
                std::memcpy(&v, ram + 2 * (y * 16 + x), 2);
                CHECK(v == kDcY[(y / 8) * 2 + x / 8]);
            }
        s16 cb = 0, cr = 0;
        std::memcpy(&cb, ram + 512, 2);
        std::memcpy(&cr, ram + 640 + 126, 2);
        CHECK(cb == kDcCb);
        CHECK(cr == kDcCr);
    }
    for (int i = 0; i < 100 && r.d_running(kD4); ++i) r.work(64);
    CHECK((r.bus().read32(kDStat) & 0x18u) == 0x18u);  // CIS 3 and 4
    CHECK((r.k->intc_stat() & (1u << kIntcIpu)) != 0);
    CHECK(r.k->unhandled_accesses() == 0);
    CHECK(r.fatals.empty());
    CHECK(r.traps.empty());
}

TEST_CASE("kernel DMAC: CSC as _sceMpegCscStoreRefImage drives it; the IPU is idle before D3 completes") {
    KRig r;
    std::vector<u8> raw(3 * 384);
    for (std::size_t i = 0; i < raw.size(); ++i) raw[i] = static_cast<u8>((i * 71 + 5) & 0xFF);
    r.put(0x00200000u, raw.data(), raw.size());
    r.bus().write32(kIpuCmd, 0);  // BCLR
    r.wait_ipu();
    r.bus().write32(kD4 + kMadr, 0x00200000u);
    r.bus().write32(kD4 + kQwc, 72);
    r.bus().write32(kD4 + kChcr, 0x101u);
    r.wait_ipu();
    r.bus().write32(kD3 + kMadr, 0x00400000u);
    r.bus().write32(kD3 + kQwc, 3 * 64);
    r.bus().write32(kD3 + kChcr, 0x100u);
    r.bus().write32(kIpuCmd, kCmdCsc | 3u);
    bool busy_at_d3_completion = false;
    for (int i = 0; i < 20000 && r.d_running(kD3); ++i) {
        r.work(8);
        if (!r.d_running(kD3) && r.ipu_busy()) busy_at_d3_completion = true;
    }
    CHECK_FALSE(r.d_running(kD3));
    CHECK_FALSE(busy_at_d3_completion);  // _ch3dmaCSC issues the next CSC from the D3 handler without polling
    CHECK((r.bus().read32(kDStat) & 0x8u) != 0);
    u8 ref[1024];
    for (int mb = 0; mb < 3; ++mb) {
        mpeg2::csc(raw.data() + 384 * mb, mpeg2::CscParams{}, ref);
        CHECK(std::memcmp(r.mem.main_ram() + 0x00400000u + 1024u * static_cast<u32>(mb), ref, 1024) == 0);
    }
    CHECK(r.k->unhandled_accesses() == 0);
    CHECK(r.traps.empty());
}

TEST_CASE("kernel DMAC: sceIpuStopDMA / sceIpuRestartDMA rewind reproduces the bit stream (FP + IFC invariant)") {
    KRig r;
    std::vector<u8> src(64 * 16);
    u32 x = 0x12345678u;
    for (u8& c : src) {
        x = x * 1664525u + 1013904223u;
        c = static_cast<u8>(x >> 24);
    }
    r.put(0x00200000u, src.data(), src.size());
    r.bus().write32(kD4 + kMadr, 0x00200000u);
    r.bus().write32(kD4 + kQwc, 64);
    r.bus().write32(kD4 + kChcr, 0x101u);
    std::size_t pos = 0;
    auto fdec_wait = [&](unsigned fb) {
        r.bus().write32(kIpuCmd, fdec(fb));
        r.wait_ipu();
        pos += fb;
        return static_cast<u32>(r.bus().read64(kIpuCmd));
    };
    for (int i = 0; i < 11; ++i) CHECK(fdec_wait(63) == bits_at(src, pos));  // 693 bits: several qwords retired
    CHECK(fdec_wait(5) == bits_at(src, pos));
    // sceIpuStopDMA: D4 CHCR = 1 (stop), save D4, wait OFC == 0, save IPU_BP / IPU_CTRL
    r.bus().write32(kD4 + kChcr, 1u);
    const u32 madr = r.bus().read32(kD4 + kMadr), qwc = r.bus().read32(kD4 + kQwc);
    CHECK(((r.bus().read32(kIpuCtrl) >> 4) & 0xFu) == 0);
    const u32 bp = r.bus().read32(kIpuBp);
    const u32 held = ((bp >> 8) & 0xFu) + ((bp >> 16) & 3u);
    CHECK(held > 0);
    CHECK(held <= kInCapacityQw);
    CHECK(madr - 0x00200000u == (64 - qwc) * 16);
    // someone else uses the IPU meanwhile (BCLR + SETVQ of other data)
    r.bus().write32(kIpuCmd, 0);
    r.wait_ipu();
    r.bus().write128(kInFifo, u128{});
    r.bus().write128(kInFifo, u128{});
    r.bus().write32(kIpuCmd, kCmdSetvq);
    r.wait_ipu();
    // sceIpuRestartDMA: BCLR(BP), MADR - (FP + IFC) * 16, QWC + FP + IFC, CHCR | STR
    r.bus().write32(kIpuCmd, bp & 0x7Fu);
    r.wait_ipu();
    r.bus().write32(kD4 + kMadr, madr - held * 16);
    r.bus().write32(kD4 + kQwc, qwc + held);
    r.bus().write32(kD4 + kChcr, 0x101u);
    CHECK(fdec_wait(0) == bits_at(src, pos));
    for (int i = 0; i < 40; ++i) CHECK(fdec_wait(17) == bits_at(src, pos));
    CHECK(r.traps.empty());
    CHECK(r.k->unhandled_accesses() == 0);
}

TEST_CASE("kernel bus: the boot sequence of sceIpuInit (M2 log item 1) leaves no unhandled access") {
    KRig r;
    r.bus().write32(kIpuCtrl, kCtrlRst);
    r.wait_ipu();
    r.bus().write32(kIpuCmd, 0);
    r.wait_ipu();
    u8 m[16];
    for (int i = 0; i < 16; ++i) m[i] = 16;
    for (int i = 0; i < 8; ++i) r.bus().write128(kInFifo, qw_bytes(m));
    r.bus().write32(kIpuCmd, kCmdSetiqIntra);
    r.wait_ipu();
    r.bus().write32(kIpuCmd, kCmdSetiqNonIntra);
    r.wait_ipu();
    r.bus().write128(kInFifo, qw_bytes(m));
    r.bus().write128(kInFifo, qw_bytes(m));
    r.bus().write32(kIpuCmd, kCmdSetvq);
    r.wait_ipu();
    r.bus().write32(kIpuCmd, kCmdSetth);
    r.wait_ipu();
    r.bus().write32(kIpuCtrl, kCtrlRst);
    r.wait_ipu();
    r.bus().write32(kIpuCmd, 0);
    r.wait_ipu();
    CHECK(r.k->unhandled_accesses() == 0);
    CHECK(r.traps.empty());
    CHECK(r.bus().read32(kIpuBp) == 0);
    CHECK(r.ipu.core().intra_matrix()[0] == 16);
    CHECK(r.ipu.core().stats().commands[5] == 2);
}

TEST_CASE("kernel DMAC: an MPEG-1 I-slice driven the way _slice0 / _decMB0 do (FDEC, VDEC, BDEC, D3 polling)") {
    KRig r;
    Bits b;
    b.byte(0).byte(0).byte(1).byte(0x01);  // slice_start_code
    b.v(4, 5).s("0");                      // quantizer_scale 4, extra_bit_slice 0
    b.s("1").s("1");                       // MB 1: macroblock_address_increment 1, macroblock_type intra
    put_dc_only_blocks(b);
    b.s("1").s("01").v(6, 5);              // MB 2: increment 1, intra + quant, quantizer_scale 6
    for (int blk = 0; blk < 4; ++blk) b.s("100 10");
    b.s("00 10").s("00 10");
    b.start_code(0xB7);                    // sequence_end_code
    const std::vector<u128> q = b.qwords(2);
    r.put(0x00200000u, q.data(), 16 * q.size());
    for (u32 i = 0; i < q.size(); ++i)  // one REF tag per qword, the last one REFE
        r.mem.write<u64>(0x00210000u + 16u * i, dmatag(i + 1 == q.size() ? 0u : 3u, 1, 0x00200000u + 16u * i));
    r.bus().write32(kIpuCtrl, kCtrlMp1 | (1u << kCtrlPctShift));
    r.bus().write32(kD4 + kTadr, 0x00210000u);
    r.bus().write32(kD4 + kQwc, 0);
    r.bus().write32(kD4 + kChcr, 0x105u);
    auto cmd64 = [&](u32 c) {  // the command, then _sceMpegWaitIpuIdle64's 64-bit IPU_CMD poll
        r.wait_ipu();
        r.bus().write32(kIpuCmd, c);
        u64 v = 0;
        for (int i = 0; i < 100000 && ((v = r.bus().read64(kIpuCmd)) >> 63); ++i) r.work(7);
        return static_cast<u32>(v);
    };
    auto next_bits = [&](unsigned n) {  // _sceMpegNextBit: FDEC 0 for the window, FDEC n to advance
        const u32 w = cmd64(fdec(0));
        cmd64(fdec(n));
        return n ? w >> (32 - n) : 0u;
    };
    CHECK(cmd64(fdec(0)) == 0x00000101u);
    cmd64(fdec(32));
    CHECK(next_bits(5) == 4);
    CHECK(next_bits(1) == 0);
    for (int mb = 0; mb < 2; ++mb) {
        CHECK(cmd64(vdec(0)) == 0x00010001u);  // increment 1
        const u32 t = cmd64(vdec(1));
        CHECK((t & 0xFFFFu & mpeg2::kMbIntra) != 0);
        unsigned qsc = 4;
        if (t & mpeg2::kMbQuant) qsc = next_bits(5);
        CHECK(qsc == (mb == 0 ? 4u : 6u));
        const u32 dst = 0x00300000u + 0x400u * static_cast<u32>(mb);
        r.bus().write32(kD3 + kMadr, dst);
        r.bus().write32(kD3 + kQwc, 48);
        r.bus().write32(kD3 + kChcr, 0x100u);
        r.wait_ipu();
        r.bus().write32(kIpuCmd, bdec(true, mb == 0, false, qsc));
        for (int i = 0; i < 10000 && r.bus().read32(kD3 + kQwc) != 0; ++i) r.work(16);  // _slice0's wait
        REQUIRE(r.bus().read32(kD3 + kQwc) == 0);
        // The kernel DMAC keeps CHCR.STR set until its completion event (64 + 2 x 48 cycles after the data); a
        // restart written inside that window is taken as a write to a running channel and lost (README "Open
        // questions" 4). The game restarts D3 after only D3_QWC == 0; this test waits for STR to stay clear of it.
        for (int i = 0; i < 1000 && r.d_running(kD3); ++i) r.work(16);
        const u8* ram = r.mem.main_ram() + dst;
        s16 y0 = 0, y3 = 0, cb = 0, cr = 0;
        std::memcpy(&y0, ram, 2);
        std::memcpy(&y3, ram + 2 * (15 * 16 + 15), 2);
        std::memcpy(&cb, ram + 512, 2);
        std::memcpy(&cr, ram + 640, 2);
        CHECK(y0 == (mb == 0 ? kDcY[0] : kDcY[3]));
        CHECK(y3 == kDcY[3]);
        CHECK(cb == kDcCb);
        CHECK(cr == kDcCr);
    }
    // end of slice: _sceMpegPeepBit(23) == 0, then flushByteBoundary and the next start code
    CHECK((cmd64(fdec(0)) >> 9) == 0);
    const unsigned bp = r.bus().read32(kIpuBp) & 0x7Fu;
    cmd64(fdec((8 - (bp & 7u)) & 7u));
    CHECK(cmd64(fdec(0)) == 0x000001B7u);
    CHECK(r.traps.empty());
    CHECK(r.fatals.empty());
    CHECK(r.k->unhandled_accesses() == 0);
}
