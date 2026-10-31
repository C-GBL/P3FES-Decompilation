// Modernize layer 5, step 1 (docs/MODERNIZE_PLAN.md "Layer 5 status", ADR-0017): the host's stand-in for VU1 program
// 039 that `--native graphics` installs (runtime/native/graphics/native_im2d.h).
//
// Oracle pair test: the native run against the VU1 interpreter running the game's own program 039 from the same state
// (the microcode dump, tools/ours/vu1/vu1_dump.py: <repo>/ida/logs/vu1/005cd98c.bin, P3FES_VU1_DUMPS overrides; the
// cases skip without it): every register, flag, data word, TPC / PC and the kicked PATH1 packet, over random batches
// of 0..16 triangles with game-shaped and adversarial floats (zero / denormal / exponent-255 / huge / negative),
// random leftover memory, both TOP buffers, MSCAL 0 and MSCNT entries. Then the hook itself: matching a queued record
// (count and the lanes the program reads; the UNPACK's masked lanes ignored), dropping passed-over records, falling
// back on a stale record / another entry / no record, handing other programs to the next hook, and the check mode.
#include <doctest.h>

#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "native_im2d.h"
#include "native_g3.h"
#include "p3fes/gs/gif.h"
#include "p3fes/gs/gs_ops.h"

using namespace p3fes;
using namespace p3fes::native::graphics;

namespace {

std::optional<std::vector<u8>> program_039() {
    std::filesystem::path dir;
    if (const char* e = std::getenv("P3FES_VU1_DUMPS"); e && *e) dir = e;
    else dir = std::filesystem::path(P3FES_SOURCE_DIR) / "ida" / "logs" / "vu1";
    std::ifstream in(dir / "005cd98c.bin", std::ios::binary);
    if (!in) return std::nullopt;
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    if (v.size() != 376) return std::nullopt;
    return v;
}

#define PROGRAM_OR_SKIP(img)                                                                                  \
    const auto img = program_039();                                                                           \
    if (!img) {                                                                                               \
        MESSAGE("SKIP: VU1 program 039 dump not found (ida/logs/vu1/005cd98c.bin; set P3FES_VU1_DUMPS)");  \
        return;                                                                                               \
    }

struct Capture final : vu1::IGifSink {
    std::vector<u128> q;
    u32 kicks = 0;
    void kick(std::span<const u128> p) override {
        q.insert(q.end(), p.begin(), p.end());
        ++kicks;
    }
};

u32 f2u(float f) {
    u32 u;
    std::memcpy(&u, &f, 4);
    return u;
}

// A float the way the game's writers produce them (mostly), or an adversarial bit pattern.
u32 rand_float(std::mt19937& rng, float lo, float hi) {
    switch (rng() % 16) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng() & 0x807FFFFFu;              // denormal / zero exponent
    case 3: return (rng() & 0x807FFFFFu) | 0x7F800000u;  // exponent 255
    case 4: return rng();                              // any bits
    case 5: return f2u(static_cast<float>(rng() % 4096) * 0.0625f);  // exact on the 1/16 grid
    default: {
        const float t = static_cast<float>(rng()) / 4294967296.0f;
        return f2u(lo + (hi - lo) * t);
    }
    }
}

u128 q4(u32 x, u32 y, u32 z, u32 w) {
    u128 q;
    q.u32[0] = x;
    q.u32[1] = y;
    q.u32[2] = z;
    q.u32[3] = w;
    return q;
}

struct Batch {
    u128 head[3];
    std::vector<u128> v;
    u32 n = 0, spare = 0;
};

Batch random_batch(std::mt19937& rng, u32 n) {
    Batch b;
    b.n = n;
    // VU1 0x3F9 offset floats (the game's: 2048 - 320 and so on), 0x3FA the GIF tag (NLOOP / EOP overwritten by the
    // program: x = 3), 0x3FB the colour scale (0.5 or 1/128-ish).
    b.head[0] = q4(rand_float(rng, 1500, 2600), rand_float(rng, 1500, 2600), rng(), rng());
    const u64 prim = (rng() % 4 == 0 ? rng() & 0x7FFu : 0x5Bu) | (rng() % 2 ? 0x10u : 0u);
    const u64 tag = (static_cast<u64>(rng() & 1u) << 46) | (prim << 47) | (3ull << 60);  // PRE, PRIM, NREG 3
    b.head[1] = q4(rng(), static_cast<u32>(tag >> 32), rng() % 8 == 0 ? rng() : 0x512u, rng() % 8 == 0 ? rng() : 0u);
    b.head[2] = q4(rand_float(rng, 0, 1), rand_float(rng, 0, 1), rand_float(rng, 0, 1), rand_float(rng, 0, 1));
    b.v.resize(12u * n);
    for (u32 k = 0; k < 3u * n; ++k) {
        b.v[4 * k + 0] = q4(rand_float(rng, -64, 704), rand_float(rng, -64, 512), rand_float(rng, 0, 16777215), rng());
        b.v[4 * k + 1] = q4(rand_float(rng, 0, 1), rand_float(rng, 0, 1), rand_float(rng, 0, 1), rng());
        b.v[4 * k + 2] = q4(rand_float(rng, 0, 255), rand_float(rng, 0, 255), rand_float(rng, 0, 255), rand_float(rng, 0, 255));
        b.v[4 * k + 3] = q4(rng(), rng(), rng(), rng());
    }
    return b;
}

// Puts the batch where VIF1 leaves it: the head at 0x3F9..0x3FB, the vertices at TOP with the UNPACK mask
// 0xC000C000 (qw 1 and 3 of each vertex keep their w lane: the old memory word).
void place(vu1::VU1State& s, u32 top, const Batch& b) {
    for (u32 k = 0; k < 3; ++k) std::memcpy(s.data + (0x3F9u + k) * 16u, &b.head[k], 16);
    for (u32 i = 0; i < b.v.size(); ++i) {
        u8* d = s.data + ((top + i) & 1023u) * 16u;
        const u32 lanes = (i % 4 == 1 || i % 4 == 3) ? 3u : 4u;
        std::memcpy(d, &b.v[i], 4u * lanes);
    }
}

void random_state(vu1::VU1State& s, std::mt19937& rng) {
    for (auto& r : s.vf)
        for (u32& x : r) x = rng();
    s.vf[0][0] = s.vf[0][1] = s.vf[0][2] = 0;
    s.vf[0][3] = 0x3F800000u;
    for (u16& x : s.vi) x = static_cast<u16>(rng());
    s.vi[0] = 0;
    for (u32& x : s.acc) x = rng();
    s.q = rng();
    s.p = rng();
    s.i = rng();
    s.r = rng();
    s.mac = rng() & 0xFFFFu;
    s.status = rng() & 0xFFFu;
    s.clip = rng() & 0xFFFFFFu;
    for (u32 i = 0; i < vu1::kDataBytes; i += 4) {
        const u32 x = rng();
        std::memcpy(s.data + i, &x, 4);
    }
}

// Every field but the flag pipe (reset at the start of every run) and micro memory.
std::string state_diff(const vu1::VU1State& a, const vu1::VU1State& b) {
    if (std::memcmp(a.vf, b.vf, sizeof a.vf)) return "vf";
    if (std::memcmp(a.vi, b.vi, sizeof a.vi)) return "vi";
    if (std::memcmp(a.acc, b.acc, sizeof a.acc) || a.q != b.q || a.p != b.p || a.i != b.i || a.r != b.r) return "acc/q/p/i/r";
    if (a.mac != b.mac) return "mac";
    if (a.status != b.status) return "status";
    if (a.clip != b.clip) return "clip";
    if (a.top != b.top || a.itop != b.itop) return "top/itop";
    if (a.pc != b.pc || a.npc != b.npc || a.tpc != b.tpc || a.running != b.running || a.ending != b.ending) return "pc";
    if (std::memcmp(a.vi_before, b.vi_before, sizeof a.vi_before) || a.vi_delay_live != b.vi_delay_live) return "branch view";
    for (u32 q = 0; q < vu1::kDataQwords; ++q)
        if (std::memcmp(a.data + 16 * q, b.data + 16 * q, 16)) return "data qw " + std::to_string(q);
    return "";
}

struct Rig {
    Capture exact_kicks;
    std::unique_ptr<vu1::VU1Interpreter> vu = std::make_unique<vu1::VU1Interpreter>(&exact_kicks);
    explicit Rig(const std::vector<u8>& img) { vu->load_micro(0, img); }
};

}  // namespace

TEST_CASE("native graphics: program 039 natively == the VU1 interpreter running it (registers, flags, memory, packet)") {
    PROGRAM_OR_SKIP(img);
    Rig rig(*img);
    CHECK(im2d_tri_resident(rig.vu->state().micro));
    std::mt19937 rng{0x1D039u};
    std::vector<u128> kick;
    u32 cases = 0, kicked = 0, mscnt = 0;
    for (int it = 0; it < 3000; ++it) {
        vu1::VU1State& s = rig.vu->state();
        random_state(s, rng);
        const u32 n = it < 17 ? static_cast<u32>(it) : rng() % 17;
        const u32 top = rng() % 4 == 0 ? (rng() % 0x1E2u) : (rng() % 2 ? 0x1E1u : 0u);
        const Batch b = random_batch(rng, n);
        place(s, top, b);
        rig.vu->set_tops(top, n);
        const bool from_mscal = rng() % 3 != 0;
        if (!from_mscal) {
            s.tpc = kIm2DTriEndTpc;
            ++mscnt;
        }
        std::unique_ptr<vu1::VU1State> native = std::make_unique<vu1::VU1State>(s);
        REQUIRE(im2d_inputs_match(*native, top, n, b.head, b.v.data()));
        g_im2d_fast = it % 2 == 0;  // both float paths: the SSE kernels and fp:: lane by lane
        im2d_tri_run(*native, from_mscal, b.head, b.v.data(), kick);
        g_im2d_fast = true;
        rig.exact_kicks.q.clear();
        rig.exact_kicks.kicks = 0;
        const vu1::RunResult r = from_mscal ? rig.vu->mscal(0) : rig.vu->mscnt();
        REQUIRE(r.status == vu1::RunStatus::Ended);
        INFO("case " << it << " n " << n << " top " << top << (from_mscal ? " mscal" : " mscnt"));
        CHECK(state_diff(s, *native) == "");
        CHECK(rig.exact_kicks.kicks == (n ? 1u : 0u));
        REQUIRE(rig.exact_kicks.q.size() == kick.size());
        CHECK(std::memcmp(rig.exact_kicks.q.data(), kick.data(), kick.size() * 16) == 0);
        if (n) CHECK(kick.size() == 10u * n + 1u);
        kicked += n ? 1 : 0;
        ++cases;
    }
    CHECK(cases == 3000);
    CHECK(kicked > 2500);
    CHECK(mscnt > 800);
}

TEST_CASE("native graphics: im2d_inputs_match reads exactly the lanes program 039 reads") {
    std::mt19937 rng{0x3F9u};
    std::unique_ptr<vu1::VU1State> s = std::make_unique<vu1::VU1State>();
    random_state(*s, rng);
    const Batch b = random_batch(rng, 5);
    place(*s, 0x1E1u, b);
    CHECK(im2d_inputs_match(*s, 0x1E1u, 5, b.head, b.v.data()));
    CHECK_FALSE(im2d_inputs_match(*s, 0, 5, b.head, b.v.data()));
    // Lanes the program never reads: qw 0 w (overwritten by MFIR), qw 1 w, qw 3, head 0x3F9 zw, 0x3FA x.
    const u32 unread[][2] = {{0, 3}, {1, 3}, {3, 0}, {3, 1}, {3, 2}, {3, 3}};
    for (const auto& [q, l] : unread) {
        for (u32 t = 0; t < 5; ++t) s->data[((0x1E1u + 12u * t + 4u + q) & 1023u) * 16u + 4u * l] ^= 0x5Au;
        CHECK(im2d_inputs_match(*s, 0x1E1u, 5, b.head, b.v.data()));
    }
    s->data[0x3F9u * 16u + 8u] ^= 1u;
    s->data[0x3FAu * 16u + 0u] ^= 1u;
    CHECK(im2d_inputs_match(*s, 0x1E1u, 5, b.head, b.v.data()));
    // Lanes it reads: qw 0 xyz, qw 1 xyz, qw 2 xyzw of every vertex, head 0x3F9 xy, 0x3FA yzw, 0x3FB xyzw.
    const u32 read[][2] = {{0, 0}, {0, 2}, {1, 1}, {1, 2}, {2, 0}, {2, 3}};
    for (const auto& [q, l] : read) {
        u8& x = s->data[((0x1E1u + 12u * 4u + 8u + q) & 1023u) * 16u + 4u * l];  // triangle 4, vertex 2
        x ^= 0x01u;
        CHECK_FALSE(im2d_inputs_match(*s, 0x1E1u, 5, b.head, b.v.data()));
        x ^= 0x01u;
    }
    const u32 heads[][2] = {{0x3F9u, 1}, {0x3FAu, 1}, {0x3FAu, 3}, {0x3FBu, 0}, {0x3FBu, 3}};
    for (const auto& [a, l] : heads) {
        u8& x = s->data[a * 16u + 4u * l];
        x ^= 0x80u;
        CHECK_FALSE(im2d_inputs_match(*s, 0x1E1u, 5, b.head, b.v.data()));
        x ^= 0x80u;
    }
    CHECK(im2d_inputs_match(*s, 0x1E1u, 5, b.head, b.v.data()));
}

namespace {
// What the game side reports for one packet of these batches (graphics_service.h).
void report(NativeIm2D& h, const std::vector<Batch>& bs) {
    std::vector<Im2DBatchView> views;
    for (const Batch& b : bs) views.push_back({b.n, std::span<const u128>(b.v.data(), b.v.size())});
    h.packet(kIm2DTriProgram, bs.front().head, views);
}

struct CountingHook final : gs::IVuRunHook {
    u32 runs = 0, after = 0;
    bool run(const gs::VuRunInfo&, vu1::VU1Interpreter&) override {
        ++runs;
        return false;
    }
    void after_exact(const gs::VuRunInfo&, vu1::VU1Interpreter&) override { ++after; }
};
}  // namespace

TEST_CASE("native graphics: the VU1 run hook -- matching, fallbacks, the next hook, the check mode") {
    PROGRAM_OR_SKIP(img);
    Capture native_kicks;
    Rig rig(*img);
    rig.vu->set_sink(&native_kicks);
    Rig oracle(*img);
    NativeIm2D h;
    h.set_check(1, stdout);
    std::mt19937 rng{0x4EC4C0u};
    // One packet of three batches with one head (the packet's), as the builder emits them.
    std::vector<Batch> bs;
    for (u32 k = 0; k < 3; ++k) {
        Batch b = random_batch(rng, k == 2 ? 3u : 16u);
        if (k) std::memcpy(b.head, bs[0].head, sizeof b.head);
        bs.push_back(std::move(b));
    }
    report(h, bs);
    CHECK(h.stats().packets == 1);
    CHECK(h.stats().batches == 3);
    CHECK(h.stats().tris == 35);
    random_state(rig.vu->state(), rng);
    std::memcpy(oracle.vu->state().data, rig.vu->state().data, vu1::kDataBytes);
    u32 top = 0;
    for (u32 k = 0; k < 3; ++k) {
        vu1::VU1State& s = rig.vu->state();
        place(s, top, bs[k]);
        rig.vu->set_tops(top, bs[k].n);
        gs::VuRunInfo ri;
        ri.op = k == 0 ? 0x15u : 0x17u;  // MSCALF 0, then MSCNT
        ri.top = top;
        ri.itop = bs[k].n;
        // the oracle: the same state, the program run exactly
        {
            vu1::VU1State& o = oracle.vu->state();
            const vu1::MicroMemory keep = o.micro;
            o = s;
            o.micro = keep;
        }
        oracle.exact_kicks.q.clear();
        const vu1::RunResult rr = k == 0 ? oracle.vu->mscalf(0) : oracle.vu->mscnt();
        REQUIRE(rr.status == vu1::RunStatus::Ended);
        native_kicks.q.clear();
        CHECK(h.run(ri, *rig.vu));
        CHECK(state_diff(oracle.vu->state(), s) == "");
        REQUIRE(native_kicks.q.size() == oracle.exact_kicks.q.size());
        CHECK(std::memcmp(native_kicks.q.data(), oracle.exact_kicks.q.data(), native_kicks.q.size() * 16) == 0);
        top = top ? 0u : 0x1E1u;
    }
    CHECK(h.stats().native == 3);
    CHECK(h.stats().native_tris == 35);
    CHECK(h.stats().checked == 3);
    CHECK(h.stats().check_bad == 0);

    // No record left: the run is the VU1's.
    vu1::VU1State& s = rig.vu->state();
    gs::VuRunInfo ri;
    ri.op = 0x17;
    ri.top = top;
    ri.itop = 3;
    place(s, top, bs[2]);
    rig.vu->set_tops(top, 3);
    CHECK_FALSE(h.run(ri, *rig.vu));
    CHECK(h.stats().fb_nomatch == 1);
    // A record whose vertices are not what VU1 memory holds is not used; a later matching one is, and the stale one
    // before it is dropped.
    Batch stale = random_batch(rng, 3), good = random_batch(rng, 3);
    report(h, {stale});
    report(h, {good});
    place(s, top, good);
    CHECK(h.run(ri, *rig.vu));
    CHECK(h.stats().dropped == 1);
    // Another entry point / TPC, an ITOP of 0: exact.
    report(h, {good});
    place(s, top, good);
    ri.op = 0x14;
    ri.imm = 3;
    CHECK_FALSE(h.run(ri, *rig.vu));
    ri.op = 0x17;
    s.tpc = 0;
    CHECK_FALSE(h.run(ri, *rig.vu));
    s.tpc = kIm2DTriEndTpc;
    rig.vu->set_tops(top, 0);
    CHECK_FALSE(h.run(ri, *rig.vu));
    CHECK(h.stats().fb_entry == 2);
    CHECK(h.stats().fb_count == 1);
    rig.vu->set_tops(top, 3);
    CHECK(h.run(ri, *rig.vu));  // the record is still queued
    CHECK(h.stats().check_bad == 0);

    // Other programs go to the next hook, and so does its after_exact.
    CountingHook next;
    h.set_next(&next);
    rig.vu->load_micro(0, std::vector<u8>(64, 0x11));
    CHECK_FALSE(h.run(ri, *rig.vu));
    h.after_exact(ri, *rig.vu);
    CHECK(next.runs == 1);
    CHECK(next.after == 1);
    CHECK(h.stats().other_runs == 1);
    // 039 again (micro memory reloaded): not forwarded.
    rig.vu->load_micro(0, *img);
    report(h, {good});
    place(s, top, good);
    CHECK(h.run(ri, *rig.vu));
    h.after_exact(ri, *rig.vu);
    CHECK(next.runs == 1);
    CHECK(next.after == 1);
    // Other programs' packets are counted, not queued.
    h.other_packet(0x5CD820u);
    CHECK(h.stats().packets_other == 1);
}

TEST_CASE("native graphics: cost per batch -- the compiled program 039 vs the native run (MESSAGE only)") {
    PROGRAM_OR_SKIP(img);
    Capture sink_a, sink_b;
    Rig aot_rig(*img), nat_rig(*img);
    aot_rig.vu->set_sink(&sink_a);
    aot_rig.vu->set_mode(vu1::VU1Mode::Aot);
    nat_rig.vu->set_sink(&sink_b);
    std::mt19937 rng{7u};
    random_state(aot_rig.vu->state(), rng);
    std::memcpy(nat_rig.vu->state().data, aot_rig.vu->state().data, vu1::kDataBytes);
    std::vector<Batch> bs;
    for (int i = 0; i < 256; ++i) bs.push_back(random_batch(rng, 2));  // a sprite: two triangles, as most batches are
    NativeIm2D h;
    const int reps = 40;
    double t_aot = 0, t_nat = 0;
    for (int rep = 0; rep < reps; ++rep) {
        for (const Batch& b : bs) report(h, {b});
        auto t0 = std::chrono::steady_clock::now();
        for (const Batch& b : bs) {
            place(aot_rig.vu->state(), 0, b);
            aot_rig.vu->set_tops(0, 2);
            sink_a.q.clear();
            aot_rig.vu->mscal(0);
        }
        auto t1 = std::chrono::steady_clock::now();
        for (const Batch& b : bs) {
            place(nat_rig.vu->state(), 0, b);
            nat_rig.vu->set_tops(0, 2);
            sink_b.q.clear();
            gs::VuRunInfo ri;
            ri.op = 0x15;
            ri.itop = 2;
            h.run(ri, *nat_rig.vu);
        }
        auto t2 = std::chrono::steady_clock::now();
        t_aot += std::chrono::duration<double, std::nano>(t1 - t0).count();
        t_nat += std::chrono::duration<double, std::nano>(t2 - t1).count();
    }
    const double n = static_cast<double>(reps) * bs.size();
    MESSAGE("program 039, 2-triangle batches incl. placing the input: VU1 " << std::string(aot_rig.vu->aot_stats().compiled_runs ? "AOT" : "interpreter")
            << " " << t_aot / n << " ns, native " << t_nat / n << " ns per batch");
    CHECK(h.stats().native == static_cast<u64>(n));
}

// ---- Step 2: the host's packets without the GIF walk, the vertex UNPACK without the VIF decode -------------------

namespace {
// A GS front end the way the d3d11 back end runs it (rasterisation off, the op recorder observing) or the software GS.
struct Front {
    gs::GsCore core;
    gs::Gif gif{core};
    std::unique_ptr<gs::GsOpRecorder> rec;
    u64 prim_obs = 0, obs_hash = 0xcbf29ce484222325ull;
    explicit Front(bool gpu) {
        if (gpu) {
            rec = std::make_unique<gs::GsOpRecorder>(core, false, true);
            core.set_draw_observer(rec.get());
            core.set_software_raster(false);
        }
        core.set_reg_observer([this](u32 r, u64 v) {
            if (r == gs::reg::PRIM) ++prim_obs;
            obs_hash = (obs_hash ^ (static_cast<u64>(r) << 56) ^ v) * 0x100000001b3ull;
        });
    }
};

std::string core_diff(const gs::GsCore& a, const gs::GsCore& b) {
    const gs::GsCoreState x = a.save_state(), y = b.save_state();
    if (std::memcmp(&x.regs, &y.regs, offsetof(gs::GsRegs, q_internal) + sizeof(u32)) != 0) return "regs";  // (no tail padding)
    if (x.queued != y.queued) return "queued";
    for (u32 i = 0; i < x.queued; ++i) {
        const gs::GsVertex &p = x.queue[i], &q = y.queue[i];
        if (p.x != q.x || p.y != q.y || p.z != q.z || p.r != q.r || p.g != q.g || p.b != q.b || p.a != q.a || p.q != q.q ||
            p.s != q.s || p.t != q.t || p.u != q.u || p.v != q.v || p.f != q.f)
            return "queue " + std::to_string(i);
    }
    const gs::GsCoreStats &s = a.stats(), &t = b.stats();
    if (s.reg_writes != t.reg_writes || s.primitives != t.primitives || s.pixels_written != t.pixels_written ||
        s.unknown_reg_writes != t.unknown_reg_writes)
        return "stats";
    if (std::memcmp(a.mem().data(), b.mem().data(), gs::kVramBytes) != 0) return "local memory";
    return "";
}

template <class T>
bool same_vec(const std::vector<T>& a, const std::vector<T>& b) {
    return a.size() == b.size() && (a.empty() || std::memcmp(a.data(), b.data(), a.size() * sizeof(T)) == 0);
}

std::string ops_diff(gs::OpList& a, gs::OpList& b) {
    if (a.ops.size() != b.ops.size()) return "op count " + std::to_string(a.ops.size()) + " vs " + std::to_string(b.ops.size());
    for (std::size_t i = 0; i < a.ops.size(); ++i) {
        const gs::GpuOp &p = a.ops[i], &q = b.ops[i];
        if (p.kind != q.kind || p.merge != q.merge || p.first != q.first || p.count != q.count || p.prim_base != q.prim_base ||
            p.cb != q.cb || p.sc.left != q.sc.left || p.sc.top != q.sc.top || p.sc.right != q.sc.right ||
            p.sc.bottom != q.sc.bottom || p.b != q.b || p.p != q.p || p.rg != q.rg || p.native != q.native)
            return "op " + std::to_string(i);
    }
    if (!same_vec(a.verts, b.verts)) return "verts";
    if (!same_vec(a.prims, b.prims)) return "prims";
    if (!same_vec(a.cbs, b.cbs)) return "cbs";
    if (!same_vec(a.words, b.words) || !same_vec(a.pages, b.pages) || !same_vec(a.clut_tab, b.clut_tab)) return "transfers";
    return "";
}

// A PATH1 packet in program 039's form: n triangles, each the same tag + ST / RGBAQ / XYZ x 3, then the closing tag
// (x = 0x8000, the rest leftover memory: sometimes PRE with another PRIM, any FLG).
std::vector<u128> im2d_packet(std::mt19937& rng, u32 n, u32 prim, bool fogged) {
    std::vector<u128> q;
    const u64 lo = 3u | (1ull << 46) | (static_cast<u64>(prim & 0x7FFu) << 47) | (3ull << 60);
    const u128 tag = q4(static_cast<u32>(lo), static_cast<u32>(lo >> 32), fogged ? 0x412u : 0x512u, rng() % 4 ? 0u : rng());
    for (u32 k = 0; k < n; ++k) {
        q.push_back(tag);
        for (u32 v = 0; v < 3; ++v) {
            q.push_back(q4(rand_float(rng, 0, 1), rand_float(rng, 0, 1), rand_float(rng, 0.001f, 1), rng()));
            q.push_back(q4(rng() % 256, rng() % 256, rng() % 256, rng() % 2 ? 0x80u : rng() % 256));
            const u32 w = rng() % 8 == 0 ? (rng() & 0xFFFFu) : 0x0FF0u;  // ADC bit 15 sometimes
            q.push_back(q4(0x6C00u + rng() % 0x2C00u, 0x7900u + rng() % 0x1E00u, rng(), w));
        }
    }
    q.push_back(q4(0x8000u, rng() % 3 == 0 ? rng() : 0u, rng(), rng()));
    return q;
}

// A PATH1 packet in the g3 programs' form: 1..3 tags of NLOOP vertices (STQ RGBAQ XYZF2|XYZ2, a strip or list PRIM
// with PRE on the first, sometimes on the later ones), EOP on the last; sometimes a closing tag without data.
std::vector<u128> g3_packet(std::mt19937& rng) {
    std::vector<u128> q;
    const u32 tags = 1 + rng() % 3;
    const bool closing = rng() % 4 == 0;
    for (u32 k = 0; k < tags; ++k) {
        const u32 n = 1 + rng() % 40;
        const u32 prim = (rng() % 2 ? 4u : 3u) | (rng() % 2 ? 0x18u : 0x08u) | (rng() % 4 == 0 ? 0x40u : 0u);
        const bool pre = k == 0 || rng() % 3 == 0;
        const bool eop = k + 1 == tags && !closing;
        const u64 lo = n | (eop ? 0x8000ull : 0) | (pre ? 1ull << 46 : 0) | (static_cast<u64>(prim) << 47) | (3ull << 60);
        q.push_back(q4(static_cast<u32>(lo), static_cast<u32>(lo >> 32), rng() % 2 ? 0x412u : 0x512u, 0));
        for (u32 v = 0; v < n; ++v) {
            q.push_back(q4(rand_float(rng, 0, 1), rand_float(rng, 0, 1), rand_float(rng, 0.001f, 1), rng()));
            q.push_back(q4(rng() % 256, rng() % 256, rng() % 256, 0x80u));
            const u32 adc = rng() % 6 == 0 ? 0x8000u : 0u;
            q.push_back(q4(0x6C00u + rng() % 0x2C00u, 0x7900u + rng() % 0x1E00u, rng(), adc | ((rng() & 0xFFu) << 4)));
        }
    }
    if (closing) q.push_back(q4(0x8000u, 0, 0, 0));
    return q;
}

// Draw state between packets: what the RW driver's A+D packets set (frame, Z, test, alpha, texture, scissor, offset).
void random_state_writes(gs::GsCore& a, gs::GsCore& b, std::mt19937& rng) {
    const auto both = [&](u32 r, u64 v) {
        a.write_reg(r, v);
        b.write_reg(r, v);
    };
    if (rng() % 2) both(gs::reg::FRAME_1, (rng() % 4) | (10ull << 16) | (static_cast<u64>(rng() % 2 ? 0 : 2) << 24));
    if (rng() % 2) both(gs::reg::ZBUF_1, 0x100 | (static_cast<u64>(rng() % 2) << 32) | (0x3Aull << 24));
    if (rng() % 2) both(gs::reg::TEST_1, rng() & 0x7FFFFu);
    if (rng() % 2) both(gs::reg::ALPHA_1, (rng() & 0xFFu) | (static_cast<u64>(rng() & 0xFFu) << 32));
    if (rng() % 3 == 0) both(gs::reg::TEX0_1, (0x2000ull) | (10ull << 14) | (8ull << 26) | (8ull << 30) | (1ull << 34));
    if (rng() % 5 == 0)  // T8 with a CLUT load (CLD 1): the recorder's CLUT versions between packets
        both(gs::reg::TEX0_1, 0x1000ull | (4ull << 14) | (0x13ull << 20) | (7ull << 26) | (7ull << 30) | (1ull << 34) |
                                  (static_cast<u64>(0x3000u + rng() % 64) << 37) | (1ull << 61));
    if (rng() % 4 == 0) both(gs::reg::SCISSOR_1, (rng() % 64) | (639ull << 16) | (static_cast<u64>(rng() % 64) << 32) | (447ull << 48));
    if (rng() % 4 == 0) both(gs::reg::XYOFFSET_1, (0x6C00ull + rng() % 64) | (0x7900ull << 32));
    if (rng() % 4 == 0) both(gs::reg::FOG, static_cast<u64>(rng() & 0xFFu) << 56);
}
}  // namespace

TEST_CASE("native graphics steps 2-3: host packets (Gif::path1_host) == the GIF walk -- GS state, draws, op lists, GIF") {
    for (const bool gpu : {true, false}) {
        INFO(std::string(gpu ? "d3d11 op recorder" : "software GS"));
        Front walk(gpu), host(gpu);
        std::mt19937 rng{gpu ? 0x5EC2u : 0x5EC3u};
        u32 applied = 0, refused = 0;
        for (int it = 0; it < (gpu ? 600 : 120); ++it) {
            random_state_writes(walk.core, host.core, rng);
            const u32 prims[] = {0x3u, 0x4u, 0x5u, 0x5Bu, 0x5Cu, 0x13u, 0x1Du, 0x7Fu & 0x7Bu, 0x6u, 0x1u};
            const u32 prim = prims[rng() % 10] | (rng() % 3 == 0 ? 0x100u : 0u);
            const u32 n = 1 + rng() % 16;
            std::vector<u128> pkt = it % 3 == 2 ? g3_packet(rng) : im2d_packet(rng, n, prim, rng() % 4 != 0);
            if (it % 37 == 5 && it % 3 != 2) pkt[10 * (n / 2)].u32[2] ^= 1u;   // one tag differs: not the form
            if (it % 41 == 7 && it % 3 != 2) pkt.back().u32[0] = 0x8001u;      // the closing tag has a NLOOP: not the form
            if (it % 43 == 8 && it % 3 == 2) pkt[0].u32[2] = 0xEu;             // A+D data: not the form
            walk.gif.path1(pkt);
            if (host.gif.path1_host(pkt)) ++applied;
            else {
                ++refused;
                host.gif.path1(pkt);
            }
            INFO("packet " << it << " n " << n << " prim " << prim);
            REQUIRE(core_diff(walk.core, host.core) == "");
            for (u32 off = 0x40; off <= 0x70; off += 0x10) REQUIRE(walk.gif.read_reg(off) == host.gif.read_reg(off));
            REQUIRE(walk.gif.stat() == host.gif.stat());
            REQUIRE(std::memcmp(walk.gif.stats().tags, host.gif.stats().tags, sizeof walk.gif.stats().tags) == 0);
            REQUIRE(std::memcmp(walk.gif.stats().qwords, host.gif.stats().qwords, sizeof walk.gif.stats().qwords) == 0);
            REQUIRE(walk.prim_obs == host.prim_obs);
            REQUIRE(walk.obs_hash == host.obs_hash);
            if (gpu && it % 50 == 49) {
                gs::OpList a, b;
                walk.rec->take(a);
                host.rec->take(b);
                REQUIRE(ops_diff(a, b) == "");
                CHECK(a.verts.size() > 0);
            }
        }
        if (gpu) {
            gs::OpList a, b;
            walk.rec->take(a);
            host.rec->take(b);
            CHECK(ops_diff(a, b) == "");
            CHECK(walk.rec->stats().tris == host.rec->stats().tris);
        }
        CHECK(applied > (gpu ? 500u : 100u));
        CHECK(refused > (gpu ? 20u : 4u));
        CHECK(host.gif.host_packets() == applied);
    }
}

TEST_CASE("native graphics step 2: path1_host refuses a busy GIF and keeps a stream recording's calls") {
    std::mt19937 rng{0xB05Cu};
    // Busy: PATH2 owns the GIF mid-packet (a tag with data still to come): the packet must queue behind it.
    gs::GsCore core;
    gs::Gif gif{core};
    const u128 p2tag = q4(2u, (1u << 28) >> 0, 0xEu, 0);  // NLOOP 2, A+D, no EOP
    REQUIRE(gif.path2(std::span<const u128>(&p2tag, 1)) == 1);
    REQUIRE(gif.active_path() == 2);
    const std::vector<u128> pkt = im2d_packet(rng, 4, 0x5Bu, true);
    CHECK_FALSE(gif.path1_host(pkt));
    CHECK(gif.host_packets() == 0);
    // A stream sink sees the packet path's calls (on_gif_tag, PRIM, the PACKED writes) one by one.
    struct Count final : gs::IGsStreamSink {
        u64 regs = 0, packed = 0, tags = 0;
        void on_reg(u32, u64) override { ++regs; }
        void on_packed(u32, const u128&) override { ++packed; }
        void on_gif_tag() override { ++tags; }
        void on_image(std::span<const u128>) override {}
        void on_hwreg(u64) override {}
        void on_read_image(std::size_t) override {}
        void on_reset() override {}
    } a, b;
    gs::GsCore c1, c2;
    gs::Gif g1{c1}, g2{c2};
    c1.set_stream_sink(&a);
    c2.set_stream_sink(&b);
    g1.path1(pkt);
    REQUIRE(g2.path1_host(pkt));
    CHECK(a.regs == b.regs);
    CHECK(a.packed == b.packed);
    CHECK(a.tags == b.tags);
    CHECK(a.packed == 4u * 9u);
    CHECK(core_diff(c1, c2) == "");
}

TEST_CASE("native graphics step 2: the Im2D vertex UNPACK written by the host == vif_unpack") {
    NativeIm2D h;
    std::mt19937 rng{0x7C00u};
    std::unique_ptr<vu1::VU1State> a = std::make_unique<vu1::VU1State>(), b = std::make_unique<vu1::VU1State>();
    u32 taken = 0;
    for (int it = 0; it < 2000; ++it) {
        random_state(*a, rng);
        std::memcpy(b->data, a->data, vu1::kDataBytes);
        gs::UnpackArgs u;
        const u32 num = rng() % 8 == 0 ? 0u : 12u * (1u + rng() % 16);  // 0 = 256 vectors
        const bool form = it % 5 != 0;
        u.code = (0x7Cu << 24) | (num << 16) | 0x8000u | (rng() % 1024u);
        u.cycle = 0x0404u;
        u.mask = 0xC000C000u;
        u.mode = 0;
        u.tops = rng() % 1024u;
        for (u32 j = 0; j < 4; ++j) {
            u.row[j] = rng();
            u.col[j] = rng();
        }
        if (!form) switch (rng() % 5) {
            case 0: u.mask = rng(); break;
            case 1: u.cycle = 0x0104u; break;
            case 2: u.mode = 1u + rng() % 2; break;
            case 3: u.code = (u.code & ~(0x7Fu << 24)) | (0x6Cu << 24); break;  // unmasked
            default: u.code &= ~0x8000u; break;                                   // no TOPS: still the form
            }
        const u32 vec = num ? num : 256u;
        std::vector<u32> words(4u * vec);
        for (u32& w : words) w = rng();
        u32 row_a[4], row_b[4];
        std::memcpy(row_a, u.row, sizeof row_a);
        std::memcpy(row_b, u.row, sizeof row_b);
        u32 vectors = 0;
        const bool took = h.unpack(u, words.data(), words.size(), b->data, row_b, vectors);
        if (!took) gs::vif_unpack(u, words.data(), words.size(), b->data, row_b);
        else {
            ++taken;
            CHECK(vectors == vec);
        }
        const u32 expect = gs::vif_unpack(u, words.data(), words.size(), a->data, row_a);
        (void)expect;
        INFO("case " << it);
        REQUIRE(std::memcmp(a->data, b->data, vu1::kDataBytes) == 0);
        REQUIRE(std::memcmp(row_a, row_b, sizeof row_a) == 0);
    }
    CHECK(taken > 1500u);
    CHECK(h.stats().unpacks == taken);
    // Step 1 behaviour on request: nothing taken.
    h.set_direct(false);
    gs::UnpackArgs u;
    u.code = (0x7Cu << 24) | (12u << 16);
    u.cycle = 0x0404u;
    u.mask = 0xC000C000u;
    std::vector<u32> words(48, 1u);
    u32 row[4] = {}, vectors = 0;
    CHECK_FALSE(h.unpack(u, words.data(), words.size(), a->data, row, vectors));
}

// ---- Step 3: the g3 programs at the PS2All bridge seam ------------------------------------------------------------

namespace {
std::optional<std::vector<u8>> dump(const char* name) {
    std::filesystem::path dir;
    if (const char* e = std::getenv("P3FES_VU1_DUMPS"); e && *e) dir = e;
    else dir = std::filesystem::path(P3FES_SOURCE_DIR) / "ida" / "logs" / "vu1";
    std::ifstream in(dir / name, std::ios::binary);
    if (!in) return std::nullopt;
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    if (v.empty() || v.size() % 8 || v.size() > vu1::kMicroBytes) return std::nullopt;
    return v;
}

// The kicks a sink receives, ordinary or as host packets.
struct HostCapture final : vu1::IGifSink {
    std::vector<std::vector<u128>> pk;
    u32 host = 0, plain = 0;
    void kick(std::span<const u128> q) override {
        pk.emplace_back(q.begin(), q.end());
        ++plain;
    }
    void kick_host(std::span<const u128> q) override {
        pk.emplace_back(q.begin(), q.end());
        ++host;
    }
};

// A g3 batch the way the RW driver leaves VU1 memory (docs/ANALYSIS/31 §2.1), with random contents: N vertices of
// 4 (generic) or 5 (skin) qwords at TOP, a bone palette, the light block (ambient, directional, point; 0 ends it),
// the transform rows, fog / screen constants, the GIF tag (PRE, a strip or list PRIM, STQ RGBAQ XYZF2), the material
// colour, the lighting factors, guard-band scales and the flags word (variant bits, cull mode).
void g3_state(vu1::VU1State& s, std::mt19937& rng, u32 top, u32 n, bool skin) {
    random_state(s, rng);
    const auto f = [&](float lo, float hi) { return f2u(lo + (hi - lo) * (static_cast<float>(rng()) / 4294967296.0f)); };
    const auto put = [&](u32 qa, u128 v) { std::memcpy(s.data + (qa & 1023u) * 16u, &v, 16); };
    const u32 stride = skin ? 5u : 4u;
    for (u32 k = 0; k < n; ++k) {
        const u32 a = top + stride * k;
        put(a + 0, q4(f(-50, 50), f(-50, 50), f(-50, 50), f(-1, 1)));
        put(a + 1, q4(f(0, 1), f(0, 1), f(0, 1), 0));
        put(a + 2, q4(rng() % 256, rng() % 256, rng() % 256, rng() % 256));
        put(a + 3, q4(static_cast<u32>(static_cast<s32>(rng() % 255) - 127), static_cast<u32>(static_cast<s32>(rng() % 255) - 127),
                      static_cast<u32>(static_cast<s32>(rng() % 255) - 127), 0));
        if (skin) {
            u128 w;
            for (u32 j = 0; j < 4; ++j) w.u32[j] = (f2u(j == 0 ? 0.7f : 0.1f) & ~0xFFFFu) | (4u * (rng() % 8));
            put(a + 4, w);
        }
    }
    for (u32 b = 0; b < 32 * 4; ++b) put(0x2B8u + b, q4(f(-1, 1), f(-1, 1), f(-1, 1), b % 4 == 3 ? f(-5, 5) : 0));
    for (u32 r = 0; r < 4; ++r) put(0x3D0u + r, q4(f(-1, 1), f(-1, 1), f(-1, 1), f(0.5f, 2)));
    const u32 types[] = {2u, 1u, 0x80u};
    u32 l = 0x3D4u;
    for (u32 k = 0; k < 1 + rng() % 3; ++k) {
        put(l, q4(f(0, 1), f(0, 1), f(0, 1), types[rng() % 3]));
        put(l + 1, q4(f(-10, 10), f(-10, 10), f(-10, 10), f(1, 50)));
        put(l + 2, q4(f(-1, 1), f(-1, 1), f(-1, 1), f(0, 1)));
        l += 3;
    }
    put(l, q4(0, 0, 0, 0));
    for (u32 r = 0; r < 4; ++r) put(0x3F0u + r, q4(f(-2, 2), f(-2, 2), f(-2, 2), r == 3 ? f(50, 200) : f(-0.1f, 0.1f)));
    put(0x3F6u, q4(0, 0, f(1, 100), f(1, 10)));
    put(0x3F7u, q4(f(200, 400), f(200, 400), f(1000, 100000), 0));
    put(0x3F8u, q4(f2u(2048.0f), f2u(2048.0f), f(0, 1000), 0));
    put(0x3F9u, q4(f2u(8.0f), f2u(8.0f), 0, 0));
    const u64 prim = (rng() % 2 ? 4u : 3u) | 0x18u;
    const u64 tag = (1ull << 46) | (prim << 47) | (3ull << 60);
    put(0x3FAu, q4(0, static_cast<u32>(tag >> 32), rng() % 2 ? 0x412u : 0x512u, 0));
    put(0x3FBu, q4(f(0, 1), f(0, 1), f(0, 1), f(0, 1)));
    put(0x3FCu, q4(f(0, 1), 0, f(0, 1), rng() % 4 ? 0 : f(0, 1)));
    put(0x3FDu, q4(f(1, 4), f(1, 4), f(1, 4), 0));
    put(0x3FEu, q4(f(1, 4), f(1, 4), f(1, 4), 0));
    put(0x3FFu, q4(rng() % 16, 0, rng() % 3, 0));
}
}  // namespace

TEST_CASE("native graphics step 3: g3 runs through the seam == the VU1 interpreter running the game's g3 programs") {
    struct P {
        const char* file;
        G3Family fam;
        bool skin;
    };
    const P progs[] = {{"006b8d4c.bin", G3Family::Generic, false}, {"006f8b1c.bin", G3Family::Skin, true},
                       {"006f598c.bin", G3Family::Skin, true}};
    u32 found = 0;
    for (const P& pr : progs) {
        const auto img = dump(pr.file);
        if (!img) continue;
        ++found;
        INFO("program " << std::string(pr.file));
        HostCapture out, oracle_out;
        auto vu = std::make_unique<vu1::VU1Interpreter>(&out);
        auto oracle = std::make_unique<vu1::VU1Interpreter>(&oracle_out);
        vu->load_micro(0, *img);
        oracle->load_micro(0, *img);
        vu->set_mode(vu1::VU1Mode::Aot);  // the compiled program where this build has it (the game's fast path)
        NativeG3Seam h;
        h.add_program(*img, pr.fam);
        h.set_check(1, stdout);
        std::mt19937 rng{0x6300u + found};
        u32 ended = 0, kicked = 0;
        for (int it = 0; it < 120; ++it) {
            vu1::VU1State& s = vu->state();
            const u32 n = 3 + rng() % 40, top = rng() % 2 ? 0u : 0x10Cu;
            g3_state(s, rng, top, n, pr.skin);
            {
                vu1::VU1State& o = oracle->state();
                const vu1::MicroMemory keep = o.micro;
                o = s;
                o.micro = keep;
            }
            vu->set_tops(top, n);
            oracle->set_tops(top, n);
            gs::VuRunInfo ri;
            ri.op = 0x14;  // MSCAL 0: the init, then the batch
            ri.top = top;
            ri.itop = n;
            out.pk.clear();
            oracle_out.pk.clear();
            CHECK_FALSE(h.run(ri, *vu));  // the program runs; its kicks are the hook's
            const vu1::RunResult r = vu->mscal(0, 400000);
            h.after_exact(ri, *vu);
            const vu1::RunResult ro = oracle->mscal(0, 400000);
            REQUIRE(r.status == ro.status);
            if (r.status != vu1::RunStatus::Ended) continue;
            ++ended;
            INFO("case " << it << " n " << n);
            CHECK(state_diff(oracle->state(), vu->state()) == "");
            REQUIRE(out.pk.size() == oracle_out.pk.size());
            for (std::size_t k = 0; k < out.pk.size(); ++k) {
                REQUIRE(out.pk[k].size() == oracle_out.pk[k].size());
                CHECK(std::memcmp(out.pk[k].data(), oracle_out.pk[k].data(), out.pk[k].size() * 16) == 0);
            }
            CHECK(out.plain == 0);
            kicked += out.pk.empty() ? 0 : 1;
        }
        CHECK(ended > 60u);
        CHECK(kicked > 30u);
        CHECK(h.stats().runs == 120u);
        CHECK(h.stats().family[static_cast<int>(pr.fam)] == 120u);
        CHECK(h.stats().checked == ended);
        CHECK(h.stats().check_bad == 0u);
        CHECK(h.stats().host_kicks == out.host);
        MESSAGE(std::string(pr.file) << ": " << ended << " runs ended, " << kicked << " kicked, " << h.stats().kick_qw << " qw; "
                        << std::string(vu->aot_stats().compiled_runs ? "compiled program" : "interpreter"));
    }
    if (!found) MESSAGE("SKIP: no g3 program dump (ida/logs/vu1/006b8d4c.bin ...; set P3FES_VU1_DUMPS)");
}

TEST_CASE("native graphics step 3: the seam's mesh records, other programs and the next hook") {
    NativeG3Seam h;
    std::vector<u8> img(64);
    for (std::size_t i = 0; i < img.size(); ++i) img[i] = static_cast<u8>(i * 7 + 1);
    h.add_program(img, G3Family::Generic);
    HostCapture out;
    auto vu = std::make_unique<vu1::VU1Interpreter>(&out);
    vu->load_micro(0, img);
    std::mt19937 rng{0x3FAu};
    const auto rec = [&](u32 salt) {
        G3MeshRecord m;
        m.block[0] = q4(rng(), 0x3D000000u + salt, 0x412u, 0);
        m.block[1] = q4(f2u(0.5f), f2u(0.25f), salt, f2u(1));
        m.block[2] = q4(salt, 0, f2u(0.75f), 0);
        return m;
    };
    const G3MeshRecord a = rec(1), b = rec(2), c = rec(3);
    h.mesh(a);
    h.mesh(b);
    h.mesh(c);
    CHECK(h.stats().meshes == 3);
    const auto show = [&](const G3MeshRecord& m) {  // VU1 memory as the bridge's UNPACK leaves it (0x3FA x: any)
        std::memcpy(vu->state().data + 0x3FAu * 16u, &m.block[0], 48);
        vu->state().data[0x3FAu * 16u] ^= 0xFFu;
    };
    gs::VuRunInfo ri;
    ri.op = 0x17;
    show(a);
    CHECK_FALSE(h.run(ri, *vu));
    h.after_exact(ri, *vu);
    CHECK_FALSE(h.run(ri, *vu));  // the mesh's second cluster: the same record
    h.after_exact(ri, *vu);
    CHECK(h.stats().matched == 2);
    show(c);  // b's clusters were not drawn (culled): passed over
    CHECK_FALSE(h.run(ri, *vu));
    h.after_exact(ri, *vu);
    CHECK(h.stats().matched == 3);
    CHECK(h.stats().dropped == 2);
    G3MeshRecord d = rec(4);
    show(d);  // not reported: unmatched, and its next cluster too (the cached answer)
    CHECK_FALSE(h.run(ri, *vu));
    h.after_exact(ri, *vu);
    CHECK_FALSE(h.run(ri, *vu));
    h.after_exact(ri, *vu);
    CHECK(h.stats().unmatched == 2);
    h.mesh(d);  // reported now: the next run with that block matches it
    CHECK_FALSE(h.run(ri, *vu));
    h.after_exact(ri, *vu);
    CHECK(h.stats().unmatched == 2);
    CHECK(h.stats().matched == 4);
    CHECK(h.stats().runs == 6);
    // the kicks of a run go to the sink as host packets (or kicks with direct off)
    out.pk.clear();
    CHECK_FALSE(h.run(ri, *vu));
    const std::vector<u128> p1 = {q4(0x8001u, 0x10000000u | (0x4Cu << 15), 0x412u, 0), q4(1, 2, 3, 4), q4(5, 6, 7, 8), q4(9, 10, 11, 12)};
    vu->sink()->kick(p1);
    vu->sink()->kick(p1);
    h.after_exact(ri, *vu);
    CHECK(vu->sink() == &out);
    CHECK(out.host == 2);
    CHECK(h.stats().kicks == 2);
    h.set_direct(false);
    CHECK_FALSE(h.run(ri, *vu));
    vu->sink()->kick(p1);
    h.after_exact(ri, *vu);
    CHECK(out.plain == 1);
    // another program: the next hook's, with its after_exact
    CountingHook next;
    h.set_next(&next);
    vu->load_micro(0, std::vector<u8>(64, 0x11));
    CHECK_FALSE(h.run(ri, *vu));
    h.after_exact(ri, *vu);
    CHECK(next.runs == 1);
    CHECK(next.after == 1);
    // with a next hook installed (the play-mode renderer) the g3 runs are its too
    vu->load_micro(0, img);
    CHECK_FALSE(h.run(ri, *vu));
    h.after_exact(ri, *vu);
    CHECK(next.runs == 2);
    CHECK(h.stats().other_runs == 2);
    CHECK(g3_family_of("vu1_prog_064_g3_skin") == G3Family::Skin);
    CHECK(g3_family_of("vu1_prog_101_g3_skin_matfx") == G3Family::SkinMatFx);
    CHECK(g3_family_of("vu1_prog_093_g3_matfx") == G3Family::MatFx);
    CHECK(g3_family_of("vu1_prog_042_g3_generic") == G3Family::Generic);
    CHECK(g3_family_of("vu1_prog_039_im2d_tri") == G3Family::None);
    CHECK(g3_family_of("vu1_prog_120_g3_skspt_uva") == G3Family::None);
}