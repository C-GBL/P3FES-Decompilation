// The threaded graphics pipeline (p3fes/gs/gs_pipeline.h) against the synchronous model: one scripted stream of
// VIF1 / GIF / privileged-register traffic -- MPG + UNPACK + MSCAL drawing through PATH1, PATH2 DIRECT, PATH3, a
// PATH1 packet queued behind an open PATH3 packet (GIF_STAT.P1Q), SIGNAL / FINISH / LABEL written by PATH1 and by
// PATH3, CSR / SIGLBLID / GIF_STAT / GIF TAG reads, IMR unmasking SIGNAL (the interrupt raised at the run), a local ->
// host read, a VU1 reset, a VU1 trap -- run synchronously and with the pipeline inline (0), on one worker (1) and on
// two workers (2), several times each. Every value the EE reads, the interrupt log, the traps, GS local memory and
// the VU1 state must be identical (model: the pipeline's sync rules).
#include "gs_test_util.h"

#include "../vu1/vu1_test_util.h"

#include <cstring>
#include <functional>

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;
namespace vt = p3fes::vu1::test;

namespace {

struct Words {
    std::vector<u32> w;
    Words& c(u32 v) {
        w.push_back(v);
        return *this;
    }
    Words& q(const u128& x) {
        w.insert(w.end(), x.u32, x.u32 + 4);
        return *this;
    }
    std::vector<u128> qw() const {
        std::vector<u32> x = w;
        while (x.size() % 4) x.push_back(0);
        std::vector<u128> out(x.size() / 4);
        std::memcpy(out.data(), x.data(), x.size() * 4);
        return out;
    }
};

constexpr u32 unpack_v4_32(u32 num, u32 addr, bool flg) {
    return (0x6Cu << 24) | ((num & 0xFFu) << 16) | (flg ? 0x8000u : 0u) | (addr & 0x3FFu);
}
constexpr u32 STCYCL(u32 cl, u32 wl) { return 0x01000000u | (wl << 8) | cl; }
constexpr u32 OFFSET(u32 v) { return 0x02000000u | v; }
constexpr u32 BASE(u32 v) { return 0x03000000u | v; }
constexpr u32 MSCAL(u32 v) { return 0x14000000u | v; }
constexpr u32 MPG(u32 num, u32 addr) { return 0x4A000000u | ((num & 0xFFu) << 16) | addr; }
constexpr u32 DIRECT(u32 qwc) { return 0x50000000u | qwc; }

std::vector<u32> program(std::initializer_list<vt::Pair> pairs) {
    std::vector<u8> img = vt::image(pairs);
    std::vector<u32> w(img.size() / 4);
    std::memcpy(w.data(), img.data(), img.size());
    return w;
}

// What the EE observed, in order.
struct Trace {
    std::vector<u64> v;
    void add(u64 x) { v.push_back(x); }
};

struct Run {
    Trace trace;
    std::vector<u8> vram;
    std::vector<u8> vu_data;
    std::vector<u32> vu_regs;
    std::vector<unsigned> intc;
    std::size_t traps = 0;
};

u64 hash_bytes(const u8* p, std::size_t n) {
    u64 h = 1469598103934665603ull;
    for (std::size_t i = 0; i < n; ++i) h = (h ^ p[i]) * 1099511628211ull;
    return h;
}

// mode: -1 synchronous, else the pipeline's thread count.
Run scenario(int mode) {
    Fixture f;
    Run out;
    f.gs->set_trap_handler([&](const VifTrap&) { ++out.traps; });
    f.env();
    // local -> host source data, written before the pipeline starts
    for (u32 i = 0; i < 8; ++i) f.mem().write(0x00, 0x2000, 1, i, 0, 0xA0000000u + i);
    if (mode >= 0) {
        GsPipelineOptions o;
        o.threads = static_cast<unsigned>(mode);
        o.batch_bytes = 4096;  // many hand-offs
        f.gs->start_pipeline(o);
    }
    auto feed = [&](const Words& w) {
        std::vector<u128> q = w.qw();
        out.trace.add(f.bus.dma[1]->transfer(q.data(), q.size(), 0));
    };
    auto csr = [&] {
        out.trace.add(f.bus.read64(0x12001000) & 0xFFFFu);
        out.trace.add(f.bus.read64(0x12001080));  // SIGLBLID
        out.trace.add(out.traps);
        out.trace.add(f.bus.intc.size());
    };
    // xtop vi1 ; xgkick vi1 (E) ; nop   -- kicks the packet at TOP
    const std::vector<u32> prog = program({{vt::UNOP, vt::l_xtop(1)}, {vt::UNOP | vt::E_BIT, vt::l_xgkick(1)}, {vt::UNOP, vt::LNOP}});
    // a SQRT (defined, uncensused): traps
    const std::vector<u32> bad = program({{vt::UNOP, vt::l_sqrt(1, vt::bx)}, {vt::UNOP | vt::E_BIT, vt::LNOP}, {vt::UNOP, vt::LNOP}});
    {
        Words w;
        w.c(STCYCL(4, 4)).c(BASE(0x20)).c(OFFSET(0x100));
        w.c(MPG(3, 0));
        for (u32 x : prog) w.c(x);
        w.c(0).c(MPG(3, 8));
        for (u32 x : bad) w.c(x);
        feed(w);
    }
    auto draw_p1 = [&](u32 x, u32 y, u32 r, std::initializer_list<std::pair<u32, u64>> extra = {}) {
        GifBuilder pkt;
        std::vector<std::pair<u32, u64>> ad = {{reg::PRIM, gs_prim(6)},
                                               {reg::RGBAQ, gs_rgbaq(r, 255 - r, x, 0x80)},
                                               {reg::XYZ2, gs_xyz(x * 16, y * 16, 0)},
                                               {reg::XYZ2, gs_xyz((x + 6) * 16, (y + 5) * 16, 0)}};
        ad.insert(ad.end(), extra.begin(), extra.end());
        pkt.tag(static_cast<u32>(ad.size()), true, 0, 1, 0xE);
        for (const auto& [areg, v] : ad) pkt.raw(v, areg);
        Words w;
        w.c(unpack_v4_32(static_cast<u32>(pkt.qwords().size()), 0, true));
        for (const u128& q : pkt.qwords()) w.q(q);
        w.c(MSCAL(0));
        feed(w);
    };
    // 1. many PATH1 draws (double-buffered input)
    for (u32 i = 0; i < 40; ++i) draw_p1((i * 7) % 600, (i * 11) % 400, i * 6);
    csr();
    // 2. PATH1 SIGNAL / FINISH / LABEL (IMR masks them: no interrupt), seen by the next CSR / SIGLBLID read
    draw_p1(10, 10, 200, {{reg::SIGNAL, (0xFFull << 32) | 0x55u}, {reg::FINISH, 0}, {reg::LABEL, (0xF0ull << 32) | 0xA0u}});
    csr();
    f.bus.write64(0x12001000, 3);  // clear SIGNAL / FINISH
    csr();
    // 3. a PATH3 packet left open (NLOOP 2, one data qword) owns the GIF: the next VU1 run's kick queues (P1Q)
    {
        std::vector<u128> p3(2);
        p3[0].u64[0] = 2u | (1ull << 60) | (1ull << 15);  // NLOOP 2, EOP, PACKED, NREG 1
        p3[0].u64[1] = 0xE;                                 // A+D
        p3[1].u64[0] = gs_prim(6);
        p3[1].u64[1] = reg::PRIM;
        out.trace.add(f.gs->gif().path3(p3));
        draw_p1(100, 100, 77);
        out.trace.add(f.bus.read32(0x10003020));  // GIF_STAT: P1Q, OPH, APATH
        std::vector<u128> rest(1);
        rest[0].u64[0] = gs_rgbaq(9, 9, 9, 0x80);
        rest[0].u64[1] = reg::RGBAQ;
        out.trace.add(f.gs->gif().path3(rest));     // EOP: the queued PATH1 packet runs
        out.trace.add(f.bus.read32(0x10003020));
        for (u32 off = 0x40; off <= 0x80; off += 0x10) out.trace.add(f.bus.read32(0x10003000 + off));  // TAG0-3, CNT
    }
    // 4. PATH2 DIRECT sprite and a PATH3 SIGNAL after pending PATH1 work
    {
        GifBuilder g;
        g.ad({{reg::PRIM, gs_prim(6)}, {reg::RGBAQ, gs_rgbaq(5, 6, 7, 0x80)}, {reg::XYZ2, gs_xyz(300 * 16, 20 * 16, 0)},
              {reg::XYZ2, gs_xyz(320 * 16, 40 * 16, 0)}});
        Words w;
        w.c(0).c(0).c(0).c(DIRECT(static_cast<u32>(g.qwords().size())));
        for (const u128& q : g.qwords()) w.q(q);
        feed(w);
        draw_p1(400, 300, 33);
        GifBuilder s;
        s.ad({{reg::SIGNAL, (0xFull << 32) | 0x3u}});
        out.trace.add(f.send(s));
        csr();
    }
    // 5. IMR lets SIGNAL interrupt: the PATH1 SIGNAL raises INTC 0 at its run
    f.bus.write64(0x12001000, 1);
    f.bus.write64(0x12001010, 0x7E00);
    draw_p1(50, 300, 99, {{reg::SIGNAL, (0xFFull << 32) | 0x77u}});
    out.trace.add(f.bus.intc.size());  // read before any CSR access: the run itself raised it
    f.bus.write64(0x12001010, 0x7F00);
    csr();
    // 6. VU1 reset in order with queued work, then more draws; a trapping run
    for (u32 i = 0; i < 10; ++i) draw_p1(500, (i * 13) % 400, 250 - i);
    f.gs->vu1_reset();
    draw_p1(200, 200, 123);
    feed(Words{}.c(MSCAL(8)));
    csr();
    // 7. local -> host: the GS memory as every command left it
    {
        GifBuilder g;
        g.ad({{reg::BITBLTBUF, gs_bitbltbuf(0x2000, 1, 0x00, 0, 0, 0)}, {reg::TRXPOS, 0}, {reg::TRXREG, gs_trxreg(8, 1)}, {reg::TRXDIR, 1}});
        out.trace.add(f.send(g));
        f.bus.write64(0x12001040, 1);
        const u128 q0 = f.bus.read128(0x10005000);
        out.trace.add(q0.u64[0]);
        out.trace.add(q0.u64[1]);
        f.bus.write64(0x12001040, 0);
    }
    // 8. more work left in flight when the run ends
    for (u32 i = 0; i < 20; ++i) draw_p1((i * 29) % 600, (i * 17) % 400, i);
    f.gs->quiesce();
    out.intc = f.bus.intc;
    out.vram.assign(f.mem().data(), f.mem().data() + kVramBytes);
    const vu1::VU1State& s = f.gs->vu1().state();
    out.vu_data.assign(s.data, s.data + vu1::kDataBytes);
    for (const auto& r : s.vf) out.vu_regs.insert(out.vu_regs.end(), r, r + 4);
    out.vu_regs.insert(out.vu_regs.end(), s.vi, s.vi + 16);
    out.vu_regs.push_back(s.tpc);
    out.trace.add(f.gs->vif1().stats().vu_runs);
    out.trace.add(f.gs->vif1().stats().vu_pairs);
    out.trace.add(f.gs->gif().stat());
    f.gs->stop_pipeline();
    out.trace.add(f.gs->gif().stats().qwords[1]);  // PATH1 counters folded back into the GIF
    return out;
}

} // namespace

TEST_CASE("pipeline: inline, one worker and two workers give the synchronous model's results (model)") {
    const Run ref = scenario(-1);
    // sanity: the scenario exercises what it claims
    REQUIRE(ref.traps == 1u);
    REQUIRE(ref.intc.size() >= 1u);
    for (int mode : {0, 1, 2}) {
        for (int rep = 0; rep < (mode == 0 ? 1 : 4); ++rep) {
            CAPTURE(mode);
            CAPTURE(rep);
            const Run r = scenario(mode);
            CHECK(r.trace.v == ref.trace.v);
            CHECK(r.intc == ref.intc);
            CHECK(r.traps == ref.traps);
            CHECK(r.vu_regs == ref.vu_regs);
            CHECK(hash_bytes(r.vu_data.data(), r.vu_data.size()) == hash_bytes(ref.vu_data.data(), ref.vu_data.size()));
            CHECK(hash_bytes(r.vram.data(), r.vram.size()) == hash_bytes(ref.vram.data(), ref.vram.size()));
        }
    }
}

TEST_CASE("pipeline: a PATH1 SIGNAL is visible at the next CSR read, never earlier or later (model)") {
    for (int mode : {-1, 2}) {
        Fixture f;
        if (mode >= 0) f.gs->start_pipeline(GsPipelineOptions{});
        const std::vector<u32> prog = program({{vt::UNOP, vt::l_xtop(1)}, {vt::UNOP | vt::E_BIT, vt::l_xgkick(1)}, {vt::UNOP, vt::LNOP}});
        Words w;
        w.c(STCYCL(4, 4)).c(BASE(0x20)).c(OFFSET(0x100)).c(MPG(3, 0));
        for (u32 x : prog) w.c(x);
        GifBuilder pkt;
        pkt.ad({{reg::SIGNAL, (0xFFull << 32) | 0x42u}});
        w.c(unpack_v4_32(static_cast<u32>(pkt.qwords().size()), 0, true));
        for (const u128& q : pkt.qwords()) w.q(q);
        CHECK((f.bus.read64(0x12001000) & 1u) == 0u);
        w.c(MSCAL(0));
        std::vector<u128> q = w.qw();
        f.bus.dma[1]->transfer(q.data(), q.size(), 0);
        CHECK((f.bus.read64(0x12001000) & 1u) == 1u);
        CHECK((f.bus.read64(0x12001080) & 0xFFu) == 0x42u);
        f.gs->stop_pipeline();
    }
}

TEST_CASE("pipeline: a VU1 run hook draws through emit_gs at its place in the stream (model)") {
    // The hook replaces every MSCAL 0 with a sprite drawn on the GS stage (track E's native renderer shape); PATH3
    // sprites between the runs overlap them, so the order of the two is visible in GS memory.
    auto run = [](int mode) {
        Fixture f;
        f.env();
        GsPipeline* pipe = nullptr;
        if (mode >= 0) {
            GsPipelineOptions o;
            o.threads = static_cast<unsigned>(mode);
            o.batch_bytes = 4096;
            f.gs->start_pipeline(o);
            pipe = f.gs->pipeline();
        }
        u32 n = 0;
        GsCore& core = f.core();
        auto draw = [&core](u32 i) {
            core.write_reg(reg::PRIM, gs_prim(6));
            core.write_reg(reg::RGBAQ, gs_rgbaq(i * 9, 255 - i * 9, 7, 0x80));
            core.write_reg(reg::XYZ2, gs_xyz((i * 10) * 16, 0, 0));
            core.write_reg(reg::XYZ2, gs_xyz((i * 10 + 15) * 16, 15 * 16, 0));
        };
        struct Hook final : IVuRunHook {
            std::function<bool(const VuRunInfo&)> fn;
            bool run(const VuRunInfo& r, vu1::VU1Interpreter&) override { return fn(r); }
        } hook;
        hook.fn = [&](const VuRunInfo& r) {
            if (r.imm != 0) return false;
            const u32 i = n++;
            if (pipe) pipe->emit_gs([draw, i] { draw(i); });
            else draw(i);
            return true;
        };
        f.gs->vif1().set_run_hook(&hook);
        for (u32 i = 0; i < 20; ++i) {
            std::vector<u128> q = Words{}.c(MSCAL(0)).qw();
            f.bus.dma[1]->transfer(q.data(), q.size(), 0);
            GifBuilder g;
            g.ad({{reg::PRIM, gs_prim(6)},
                  {reg::RGBAQ, gs_rgbaq(200, i, 100, 0x80)},
                  {reg::XYZ2, gs_xyz((i * 10 + 5) * 16, 5 * 16, 0)},
                  {reg::XYZ2, gs_xyz((i * 10 + 20) * 16, 20 * 16, 0)}});
            f.send(g);
        }
        f.gs->quiesce();
        f.gs->stop_pipeline();
        CHECK(f.gs->vif1().hooked_runs() == 20u);
        f.gs->vif1().set_run_hook(nullptr);
        return hash_bytes(f.mem().data(), kVramBytes);
    };
    const u64 ref = run(-1);
    for (int mode : {0, 1, 2}) {
        CAPTURE(mode);
        CHECK(run(mode) == ref);
    }
}
