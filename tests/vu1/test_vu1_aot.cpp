// Differential tests of the ahead-of-time compiled VU1 programs against the interpreter (the oracle;
// runtime/include/p3fes/vu1/vu1_aot.h, docs/ANALYSIS/24_vu1_acceleration.md). Every comparison covers the whole
// outcome of a run: registers, Q/P/I/R, MAC/status/clip flags, the pair counter and the Q pipe, pc/npc/tpc, the
// branch-VI snapshot, all of data memory, the kicked GIF packets, run status, step count, trap and statistics (the
// MAC / clip rings hold only the entries a reader can see: see differs()).
//
// Inputs: (1) randomised states (random vf/vi/ACC/Q/I, random data memory, small random TOP/ITOP) for every compiled
// program from MSCAL 0 and from each MSCNT resume point, chained the way the game chains batches; (2) real run
// inputs captured on the battle route (`p3fes --vu1-stats F --vu1-stats-at ... --vu1-capture DIR N`), read from
// P3FES_VU1_CAPTURES; (3) Mode::Diff through the public API. The compiled table exists only in builds with
// P3FES_VU1_AOT=ON; elsewhere the AOT cases check the empty table and skip.
#include "vu1_test_util.h"

#include "p3fes/vu1/vu1_aot.h"
#include "p3fes/vu1/vu1_profile.h"
#include "vu1_aot_rt.h"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <map>
#include <random>

using namespace p3fes;
using namespace p3fes::vu1;
using namespace p3fes::vu1::test;

namespace {

struct Outcome {
    RunResult r;
    Trap trap;
    VU1Stats stats;
    std::vector<std::vector<u128>> packets;
};

// First differing field, or nullptr.
const char* differs(const VU1State& a, const VU1State& b) {
#define CMP(field)                                                                                                    \
    if (std::memcmp(&a.field, &b.field, sizeof a.field) != 0) return #field;
    CMP(vf) CMP(vi) CMP(acc) CMP(q) CMP(p) CMP(i) CMP(r) CMP(mac) CMP(status) CMP(clip) CMP(top) CMP(itop) CMP(pc)
    CMP(npc) CMP(tpc) CMP(running) CMP(ending) CMP(vi_before) CMP(vi_delay_live) CMP(pipe.t) CMP(pipe.q_value)
    CMP(pipe.q_ready) CMP(pipe.q_pending) CMP(data)
#undef CMP
    // The MAC / clip rings are not compared (the compiled code keeps only the entries a reader can see; see
    // same_state in vu1_interp.cpp): what a reader takes from them lands in a vi register, compared above.
    if (std::memcmp(a.micro.bytes().data(), b.micro.bytes().data(), kMicroBytes) != 0) return "micro";
    return nullptr;
}

const char* differs(const Outcome& a, const Outcome& b) {
    if (a.r.status != b.r.status) return "run status";
    if (a.r.steps != b.r.steps) return "steps";
    if (a.trap.kind != b.trap.kind || a.trap.pc != b.trap.pc) return "trap";
    if (a.stats.pairs != b.stats.pairs || a.stats.kicks != b.stats.kicks || a.stats.kick_qwords != b.stats.kick_qwords)
        return "stats";
    if (a.packets.size() != b.packets.size()) return "kick count";
    for (std::size_t k = 0; k < a.packets.size(); ++k)
        if (a.packets[k].size() != b.packets[k].size() ||
            std::memcmp(a.packets[k].data(), b.packets[k].data(), a.packets[k].size() * sizeof(u128)) != 0)
            return "kicked packet";
    return nullptr;
}

// Two engines on identical states.
struct Pair2 {
    CaptureSink sa, sb;
    std::unique_ptr<VU1Interpreter> a = std::make_unique<VU1Interpreter>(&sa);
    std::unique_ptr<VU1Interpreter> b = std::make_unique<VU1Interpreter>(&sb);
    Pair2() { b->set_mode(VU1Mode::Aot); }
    void set(const VU1State& s) {
        a->state() = s;
        b->state() = s;
    }
    // One MSCAL (start_pc = imm * 8) or MSCNT (resume) on both; returns the first difference or nullptr.
    const char* step(bool mscnt, u32 imm, u64 limit) {
        sa.packets.clear();
        sb.packets.clear();
        a->reset_stats();
        b->reset_stats();
        Outcome oa, ob;
        oa.r = mscnt ? a->mscnt(limit) : a->mscal(imm, limit);
        ob.r = mscnt ? b->mscnt(limit) : b->mscal(imm, limit);
        oa.trap = a->trap();
        ob.trap = b->trap();
        oa.stats = a->stats();
        ob.stats = b->stats();
        oa.packets = sa.packets;
        ob.packets = sb.packets;
        if (const char* w = differs(oa, ob)) return w;
        return differs(a->state(), b->state());
    }
};

// Random 32-bit patterns biased towards ordinary floats (most lanes), with zeros, denormals, exponent-255 values
// and small integers mixed in.
u32 random_word(std::mt19937& g) {
    std::uniform_int_distribution<int> kind(0, 15);
    std::uniform_real_distribution<float> f(-4096.0f, 4096.0f);
    switch (kind(g)) {
    case 0: return 0u;
    case 1: return static_cast<u32>(g()) & 0x807FFFFFu;               // denormal / zero
    case 2: return (static_cast<u32>(g()) & 0x807FFFFFu) | 0x7F800000u; // exponent 255
    case 3: return static_cast<u32>(g()) & 0xFFu;                     // small integer
    case 4: return static_cast<u32>(g());
    default: return f2u(f(g));
    }
}

VU1State random_state(std::mt19937& g, std::span<const u8> image) {
    VU1State s;
    s.micro.write(0, image);
    for (u32 r = 1; r < 32; ++r)
        for (u32 l = 0; l < 4; ++l) s.vf[r][l] = random_word(g);
    for (u32 r = 1; r < 16; ++r) s.vi[r] = static_cast<u16>(g() & 0x3FFu);
    for (u32 l = 0; l < 4; ++l) s.acc[l] = random_word(g);
    s.q = random_word(g);
    s.i = random_word(g);
    s.p = random_word(g);
    s.mac = g() & 0xF0FFu;
    s.clip = g() & 0xFFFFFFu;
    // ZS / SS set as in any session after its first runs (compiled runs need them, vu1_aot_rt.h sticky_zs_set); one
    // state in four without them (the interpreter takes those runs)
    s.status = (g() & 0x3Fu) | ((g() & 3u) ? 0xC0u : 0u);
    for (u32 b = 0; b < kDataBytes; b += 4) {
        const u32 w = random_word(g);
        std::memcpy(s.data + b, &w, 4);
    }
    // TOP/ITOP as VIF sets them: a buffer base and a small vertex/batch count
    s.top = g() & 0x3FFu;
    s.itop = g() & 0x1Fu;
    return s;
}

std::vector<u32> resume_points(const AotProgram& p) {
    std::vector<u32> out;
    for (u32 k = 0; k + 2 <= p.pairs; ++k) {
        u32 hi;
        std::memcpy(&hi, p.image + k * 8 + 4, 4);
        if (hi & kFlagE) out.push_back(k + 2);
    }
    return out;
}

} // namespace

TEST_CASE("vu1 aot: compiled table matches the dumps") {
    const std::size_t n = aot_program_count();
#if !defined(P3FES_VU1_AOT)
    CHECK(n == 0u);
    MESSAGE("built without P3FES_VU1_AOT: no compiled programs");
#else
    REQUIRE(n > 0u);
    std::size_t checked = 0;
    for (std::size_t k = 0; k < n; ++k) {
        const AotProgram& p = aot_programs()[k];
        const auto dump = read_file(dump_path(p.code_va));
        if (!dump) continue;
        CHECK(dump->size() / 8 == p.pairs);
        CHECK(std::memcmp(dump->data(), p.image, p.pairs * 8u) == 0);
        ++checked;
    }
    MESSAGE(checked << " of " << n << " compiled programs checked against their dumps");
#endif
}

TEST_CASE("vu1 aot: resident check needs the exact image and rejects outside jumps into analysed pcs") {
    if (aot_program_count() == 0) return;
    const AotProgram& p = aot_programs()[0];
    MicroMemory m;
    AotIndex idx;
    CHECK(idx.resident(m) == nullptr);
    m.write(0, std::span<const u8>(p.image, p.pairs * 8u));
    CHECK(idx.resident(m) != nullptr);
    // one flipped bit inside the image: not resident
    std::vector<u8> bad(p.image, p.image + p.pairs * 8u);
    bad[bad.size() / 2] ^= 1u;
    m.write(0, bad);
    const AotProgram* r = idx.resident(m);
    CHECK((r == nullptr || r != &p));
    // a branch outside the image targeting a pair the Q analysis enumerated rejects the program
    m.write(0, std::span<const u8>(p.image, p.pairs * 8u));
    u32 target = kMicroPairs;
    for (u32 k = 0; k < p.pairs && target == kMicroPairs; ++k)
        if ((p.expanded[k / 64] >> (k % 64)) & 1u) target = k;
    if (target != kMicroPairs && p.pairs + 1 < kMicroPairs) {
        const u32 at = p.pairs + 1; // byte pc at*8; b offset in pairs relative to at+1
        const s32 off = static_cast<s32>(target) - static_cast<s32>(at + 1);
        const auto img = image({{UNOP, l_b(off)}});
        m.write(at * 8u, img);
        CHECK(idx.resident(m) == nullptr);
        CHECK(idx.rejected_footprint() >= 1u);
    }
}

TEST_CASE("vu1 aot: randomised states, every compiled program, MSCAL 0 then the MSCNT chain") {
    const std::size_t n = aot_program_count();
    if (n == 0) return;
    const char* env = std::getenv("P3FES_VU1_AOT_ITERATIONS");
    const int iters = env ? std::atoi(env) : 6;
    std::mt19937 g(20261020u);
    u64 runs = 0, mismatches = 0, compiled = 0;
    for (std::size_t k = 0; k < n; ++k) {
        const AotProgram& p = aot_programs()[k];
        const std::vector<u32> resumes = resume_points(p);
        for (int it = 0; it < iters; ++it) {
            Pair2 e;
            e.set(random_state(g, std::span<const u8>(p.image, p.pairs * 8u)));
            // MSCAL 0, then MSCNT as long as the program ends normally (the game's batch chain), with fresh TOP/ITOP
            // and new input data per batch; plus a direct MSCAL at every resume point.
            bool ok = true;
            for (int batch = 0; batch < 4 && ok; ++batch) {
                const char* w = e.step(batch > 0, 0, 200'000);
                ++runs;
                if (w) {
                    ++mismatches;
                    ok = false;
                    FAIL_CHECK(std::string(p.name) << " iteration " << it << " batch " << batch << ": " << std::string(w));
                    break;
                }
                if (e.a->state().running) break; // step limit: both stopped identically
                const u32 top = g() & 0x3FFu, itop = g() & 0x1Fu;
                e.a->set_tops(top, itop);
                e.b->set_tops(top, itop);
                for (int q = 0; q < 64; ++q) {
                    const u32 at = g() & 0x3FFu, w2 = random_word(g);
                    std::memcpy(e.a->state().data + at * 16 + (q & 3) * 4, &w2, 4);
                    std::memcpy(e.b->state().data + at * 16 + (q & 3) * 4, &w2, 4);
                }
            }
            for (u32 r : resumes) {
                if (r >= p.pairs) continue;
                Pair2 e2;
                e2.set(random_state(g, std::span<const u8>(p.image, p.pairs * 8u)));
                const char* w = e2.step(false, r, 200'000);
                ++runs;
                if (w) {
                    ++mismatches;
                    FAIL_CHECK(std::string(p.name) << " MSCAL at resume pair " << r << ": " << std::string(w));
                }
            }
            compiled += e.b->aot_stats().compiled_runs;
        }
    }
    MESSAGE(runs << " run pairs compared over " << n << " programs, " << compiled << " entered compiled code, "
                 << mismatches << " mismatches");
    CHECK(mismatches == 0u);
    CHECK(compiled > 0u);
}

TEST_CASE("vu1 aot: step limits stop both engines at the same pair") {
    if (aot_program_count() == 0) return;
    std::mt19937 g(7u);
    const AotProgram& p = aot_programs()[aot_program_count() - 1];
    for (u64 limit : {1ull, 2ull, 3ull, 7ull, 50ull, 333ull}) {
        Pair2 e;
        e.set(random_state(g, std::span<const u8>(p.image, p.pairs * 8u)));
        const char* w = e.step(false, 0, limit);
        CHECK_MESSAGE(w == nullptr, std::string(p.name) << " limit " << limit << ": " << std::string(w ? w : ""));
        if (e.a->state().running) {
            const char* w2 = e.step(true, 0, 1'000'000); // MSCNT resumes at TPC: not meaningful mid-run, but must agree
            CHECK_MESSAGE(w2 == nullptr, std::string(p.name) << " after limit " << limit << ": " << std::string(w2 ? w2 : ""));
        }
    }
}

TEST_CASE("vu1 aot: real run inputs captured on the battle route (P3FES_VU1_CAPTURES)") {
    const char* dir = std::getenv("P3FES_VU1_CAPTURES");
    if (!dir || !*dir || aot_program_count() == 0) {
        MESSAGE("P3FES_VU1_CAPTURES not set or no compiled programs: skipped");
        return;
    }
    std::vector<std::filesystem::path> files;
    std::error_code ec;
    for (const auto& de : std::filesystem::directory_iterator(dir, ec))
        if (de.path().extension() == ".vu1in") files.push_back(de.path());
    std::sort(files.begin(), files.end());
    u64 runs = 0, compiled = 0, mismatches = 0, bails = 0;
    std::map<std::string, std::pair<u64, u64>> per_program; // program -> (runs, runs that entered compiled code)
    for (const auto& f : files) {
        VU1State s;
        u32 pc = 0;
        std::string prog;
        REQUIRE(load_run_input(f.string(), s, pc, prog));
        Pair2 e;
        e.set(s);
        // replay as MSCAL at the recorded pc (MSCNT starts at TPC, which equals pc for resumes)
        const char* w = e.step(false, pc / 8u, 1'000'000);
        ++runs;
        compiled += e.b->aot_stats().compiled_runs;
        bails += e.b->aot_stats().bails;
        auto& pp = per_program[prog];
        ++pp.first;
        pp.second += e.b->aot_stats().compiled_runs;
        if (w) {
            ++mismatches;
            FAIL_CHECK(f.filename().string() << ": " << std::string(w));
        }
    }
    std::string detail;
    for (const auto& [name, c] : per_program)
        detail += " " + name + ":" + std::to_string(c.second) + "/" + std::to_string(c.first);
    MESSAGE(runs << " captured runs replayed, " << compiled << " entered compiled code (" << bails << " bailed out), "
                 << mismatches << " mismatches; per program compiled/runs:" << detail);
    CHECK(mismatches == 0u);
}

TEST_CASE("vu1 aot: Mode::Diff keeps the interpreter's outcome and counts no mismatch") {
    if (aot_program_count() == 0) return;
    std::mt19937 g(99u);
    const AotProgram& p = aot_programs()[0];
    CaptureSink s1, s2;
    auto ref = std::make_unique<VU1Interpreter>(&s1);
    auto dif = std::make_unique<VU1Interpreter>(&s2);
    dif->set_mode(VU1Mode::Diff);
    const VU1State st = random_state(g, std::span<const u8>(p.image, p.pairs * 8u));
    ref->state() = st;
    dif->state() = st;
    const RunResult a = ref->mscal(0, 200'000);
    const RunResult b = dif->mscal(0, 200'000);
    CHECK(a.status == b.status);
    CHECK(a.steps == b.steps);
    CHECK(differs(ref->state(), dif->state()) == nullptr);
    CHECK(s1.packets.size() == s2.packets.size());
    CHECK(dif->aot_stats().diff_runs == 1u);
    CHECK(dif->aot_stats().diff_mismatches == 0u);
}


namespace {
// Biased random lanes for the kernel test: every alignment of fp::add, near and exact cancellation, extreme exponents
// (overflow, underflow), zero / denormal / exponent-255 operands.
void kernel_operands(std::mt19937_64& g, u64 k, u32 (&a)[4], u32 (&b)[4], u32 (&c)[4]) {
    for (int i = 0; i < 4; ++i) {
        const u64 r = g();
        a[i] = static_cast<u32>(r);
        b[i] = static_cast<u32>(r >> 32);
        c[i] = static_cast<u32>(g());
        switch ((k + static_cast<u64>(i)) % 7) {
        case 0: break; // any patterns
        case 1: {      // b's exponent within +-30 of a's
            const int ea = static_cast<int>((a[i] >> 23) & 0xFF);
            const int eb = std::clamp(ea + static_cast<int>(g() % 61) - 30, 0, 255);
            b[i] = (b[i] & 0x807FFFFFu) | (static_cast<u32>(eb) << 23);
            // c near the product's magnitude: cancellation in MADD / MSUB
            const int ec = std::clamp(ea + eb - 127 + static_cast<int>(g() % 5) - 2, 0, 255);
            c[i] = (c[i] & 0x807FFFFFu) | (static_cast<u32>(ec) << 23);
            break;
        }
        case 2: b[i] = (k & 8) ? (a[i] ^ 0x80000000u) : ((a[i] & 0x7FFFFF80u) | (b[i] & 0x8000007Fu)); break;
        case 3: // near overflow / underflow exponents
            a[i] = (a[i] & 0x807FFFFFu) | ((g() & 1) ? (0xF0u + static_cast<u32>(g() % 16)) << 23 : (1u + static_cast<u32>(g() % 16)) << 23);
            b[i] = (b[i] & 0x807FFFFFu) | ((g() & 1) ? (0x80u + static_cast<u32>(g() % 127)) << 23 : (1u + static_cast<u32>(g() % 127)) << 23);
            break;
        case 4: // zero / denormal / exponent-255 operands
            a[i] = (g() & 1) ? (a[i] & 0x807FFFFFu) : (a[i] | 0x7F800000u);
            break;
        case 5: // ordinary floats in a game-like range
            a[i] = f2u(static_cast<float>(static_cast<s32>(r % 200001) - 100000) / 64.0f);
            b[i] = f2u(static_cast<float>(static_cast<s32>((r >> 20) % 2001) - 1000) / 1024.0f);
            c[i] = f2u(static_cast<float>(static_cast<s32>((r >> 40) % 20001) - 10000) / 16.0f);
            break;
        case 6: // integers for FTOI / ITOF, large magnitudes
            a[i] = static_cast<u32>(r) >> (g() % 32);
            if (g() & 1) a[i] = 0u - a[i];
            break;
        }
    }
}
aot::V vec(const u32 (&x)[4]) { return _mm_loadu_si128(reinterpret_cast<const __m128i*>(x)); }
u32 at(aot::V v, int i) {
    alignas(16) u32 o[4];
    _mm_store_si128(reinterpret_cast<__m128i*>(o), v);
    return o[i];
}
} // namespace

// The round-3 kernels (host SSE under round toward zero + FTZ/DAZ, slow path through fp::) against fp:: and the
// interpreter's semantics, lane by lane; the O bit the slow path reports for the status register; a dest-masked form.
TEST_CASE("vu1 aot: SSE kernels equal fp:: and the interpreter's semantics lane by lane") {
    const char* env = std::getenv("P3FES_VU1_FP_ITERATIONS");
    const u64 iters = (env ? std::strtoull(env, nullptr, 0) : 4'000'000ull) / 4;
    std::mt19937_64 g(0xC0FFEE26u);
    u64 bad[17] = {};
    u32 first_a = 0, first_b = 0;
    int first_op = -1;
    const u64 slow0 = aot_slow_ops();
    const auto divst = std::make_unique<VU1State>();
    const aot::CsrScope csr;
    for (u64 k = 0; k < iters; ++k) {
        u32 a[4], b[4], c[4];
        kernel_operands(g, k, a, b, c);
        const aot::V A = vec(a), B = vec(b), C = vec(c);
        u32 o_mul = 0, o_add = 0, o_sub = 0, o_madd = 0, o_msub = 0, o_x = 0;
        const aot::V rm = aot::vmul<15u>(A, B, o_mul, 0), ra = aot::vadd<15u>(A, B, o_add, 0), rs = aot::vsub<15u>(A, B, o_sub, 0);
        const aot::V rma = aot::vmadd<15u>(C, A, B, o_madd, 0), rms = aot::vmsub<15u>(C, A, B, o_msub, 0);
        const aot::V rx = aot::vmul<8u>(A, B, o_x, 0); // x only: lane 0 committed and flagged
        const aot::V rmax = aot::vmax(A, B), rmin = aot::vmin(A, B);
        const aot::V f0 = aot::vftoi<0>(A), f4 = aot::vftoi<4>(A), f12 = aot::vftoi<12>(A), f15 = aot::vftoi<15>(A);
        const aot::V i0 = aot::vitof<0>(A), i4 = aot::vitof<4>(A), i12 = aot::vitof<12>(A), i15 = aot::vitof<15>(A);
        u32 exp_o[5] = {};
        u32 mul_v[4], madd_v[4];
        for (int i = 0; i < 4; ++i) {
            const u32 em = ee::fpu::mul(a[i], b[i]), ea = ee::fpu::add(a[i], b[i]), es = ee::fpu::sub(a[i], b[i]);
            const u32 ema = ee::fpu::add(c[i], em), ems = ee::fpu::sub(c[i], em);
            mul_v[i] = em;
            madd_v[i] = ema;
            const u32 got[] = {at(rm, i), at(ra, i), at(rs, i), at(rma, i), at(rms, i), at(rmax, i), at(rmin, i), at(f0, i),
                               at(f4, i), at(f12, i), at(f15, i), at(i0, i), at(i4, i), at(i12, i), at(i15, i)};
            const u32 want[] = {em, ea, es, ema, ems, ee::fpu::max(a[i], b[i]), ee::fpu::min(a[i], b[i]),
                                ee::fpu::to_fixed(a[i], 0), ee::fpu::to_fixed(a[i], 4), ee::fpu::to_fixed(a[i], 12),
                                ee::fpu::to_fixed(a[i], 15), ee::fpu::from_fixed(static_cast<s32>(a[i]), 0),
                                ee::fpu::from_fixed(static_cast<s32>(a[i]), 4), ee::fpu::from_fixed(static_cast<s32>(a[i]), 12),
                                ee::fpu::from_fixed(static_cast<s32>(a[i]), 15)};
            for (int op = 0; op < 15; ++op)
                if (got[op] != want[op]) {
                    if (first_op < 0) first_op = op, first_a = a[i], first_b = b[i];
                    ++bad[op];
                }
            const u32 vals[5] = {em, ea, es, ema, ems};
            for (int op = 0; op < 5; ++op)
                if ((vals[op] & 0x7FFFFFFFu) == 0x7FFFFFFFu) exp_o[op] = 0x200u;
        }
        if (at(rx, 0) != mul_v[0]) ++bad[15];
        // the sticky OS bit (0x200) of the status register: set exactly when a dest lane overflowed
        const u32 got_o[5] = {o_mul, o_add, o_sub, o_madd, o_msub};
        for (int op = 0; op < 5; ++op)
            if (got_o[op] != exp_o[op]) ++bad[15];
        if (o_x != (((mul_v[0] & 0x7FFFFFFFu) == 0x7FFFFFFFu) ? 0x200u : 0u)) ++bad[15];
        // MAC flags and CLIP as the interpreter computes them
        const u32 dest = static_cast<u32>(k & 15u);
        if (aot::mac_of(vec(madd_v), dest) != sem::mac_flags(madd_v, dest)) ++bad[15];
        const u32 hist = static_cast<u32>(g()) & 0xFFFFFFu;
        if (aot::vclip(hist, A, b[3]) != sem::clip_value(hist, a, b[3])) ++bad[15];
        // the generator's vf00-lane forms (MUL by 1.0 / +0, ADD / SUB of +0, MADD / MSUB by 1.0)
        const aot::V fl = aot::vflush(A), az = aot::vaddz(A), sz = _mm_and_si128(A, aot::kSignV());
        for (int i = 0; i < 4; ++i) {
            if (at(fl, i) != ee::fpu::mul(a[i], ee::fpu::kOne) || at(fl, i) != ee::fpu::sub(a[i], 0u)) ++bad[15];
            if (at(az, i) != ee::fpu::add(a[i], 0u) || at(sz, i) != ee::fpu::mul(a[i], 0u)) ++bad[15];
            if (ee::fpu::add(c[i], ee::fpu::mul(a[i], ee::fpu::kOne)) != ee::fpu::add(c[i], a[i])) ++bad[15];
            if (ee::fpu::sub(c[i], ee::fpu::mul(a[i], ee::fpu::kOne)) != ee::fpu::sub(c[i], a[i])) ++bad[15];
        }
        // DIV (the Q pipe's value and the I/D status bit)
        for (int i = 0; i < 4; ++i) {
            divst->status = 0x3Fu;
            divst->pipe.q_pending = false;
            aot::div_q(*divst, 0, a[i], b[i], 0);
            const ee::fpu::Result want = ee::fpu::div(a[i], b[i]);
            if (divst->pipe.q_value != want.value || (divst->status & 0x30u) != (want.invalid ? 0x20u : 0u)) {
                if (first_op < 0) first_op = 16, first_a = a[i], first_b = b[i];
                ++bad[16];
            }
        }
    }
    const char* names[17] = {"mul", "add", "sub", "madd", "msub", "max", "min", "ftoi0", "ftoi4", "ftoi12", "ftoi15",
                             "itof0", "itof4", "itof12", "itof15", "dest/O-bit/MAC/CLIP", "div"};
    std::string detail;
    u64 total = 0;
    for (int op = 0; op < 17; ++op) {
        total += bad[op];
        if (bad[op]) detail += std::string(" ") + names[op] + "=" + std::to_string(bad[op]);
    }
    MESSAGE(iters << " vectors x 26 checks; mismatches " << total << detail << " (first: " << std::string(first_op >= 0 ? names[first_op] : "-")
                  << " a=" << first_a << " b=" << first_b << "); slow-path ops " << (aot_slow_ops() - slow0));
    CHECK(total == 0u);
}

// The step-limit hand-over at a block entry: the interpreter finishing the run from there must give the oracle's
// outcome (the compiled code dropped only flag-ring entries no reader on the interpreter's paths can see).
TEST_CASE("vu1 aot: runs stopped at a step limit and continued agree with the interpreter") {
    if (aot_program_count() == 0) return;
    std::mt19937 g(11u);
    u64 cases = 0, bad = 0;
    for (std::size_t n = 0; n < aot_program_count(); ++n) {
        const AotProgram& p = aot_programs()[n];
        for (u64 limit : {5ull, 40ull, 300ull, 1200ull}) {
            Pair2 e;
            e.set(random_state(g, std::span<const u8>(p.image, p.pairs * 8u)));
            e.a->reset_stats();
            e.b->reset_stats();
            const RunResult ra = e.a->mscal(0, limit), rb = e.b->mscal(0, limit);
            if (ra.status != rb.status || ra.steps != rb.steps) ++bad;
            const RunResult ca = e.a->run(1'000'000), cb = e.b->run(1'000'000);
            if (ca.status != cb.status || ca.steps != cb.steps || differs(e.a->state(), e.b->state())) {
                ++bad;
                FAIL_CHECK(std::string(p.name) << " limit " << limit << ": "
                                               << std::string(differs(e.a->state(), e.b->state()) ? differs(e.a->state(), e.b->state()) : "status"));
            }
            if (e.sa.packets.size() != e.sb.packets.size()) ++bad;
            ++cases;
        }
    }
    MESSAGE(cases << " limited runs continued to the end, " << bad << " mismatches");
    CHECK(bad == 0u);
}

// Throughput of both engines on the captured battle-route runs (P3FES_VU1_CAPTURES; P3FES_VU1_BENCH=rounds turns it
// on). Not a correctness check: prints ns per pair for each engine, overall and per program.
TEST_CASE("vu1 aot: benchmark on captured runs (P3FES_VU1_BENCH)") {
    const char* dir = std::getenv("P3FES_VU1_CAPTURES");
    const char* b = std::getenv("P3FES_VU1_BENCH");
    if (!dir || !b || aot_program_count() == 0) return;
    const int rounds = std::max(1, std::atoi(b));
    struct Input {
        std::unique_ptr<VU1State> st;
        u32 pc;
        std::string prog;
    };
    std::vector<Input> inputs;
    std::error_code ec;
    for (const auto& de : std::filesystem::directory_iterator(dir, ec)) {
        if (de.path().extension() != ".vu1in") continue;
        auto st = std::make_unique<VU1State>();
        u32 pc = 0;
        std::string prog;
        if (!load_run_input(de.path().string(), *st, pc, prog)) continue;
        // only runs of programs in the compiled table, so both engines run the same work
        AotIndex idx;
        if (const AotProgram* p = idx.resident(st->micro)) inputs.push_back({std::move(st), pc, p->name});
    }
    REQUIRE(!inputs.empty());
    struct NullSink final : IGifSink {
        void kick(std::span<const u128>) override {}
    } sink;
    std::map<std::string, std::pair<double, double>> per_prog; // program -> (interp ns, aot ns)
    std::map<std::string, u64> per_pairs;
    // One engine per input: assigning a VU1State copies MicroMemory's generation, so a shared engine would keep a
    // decode cache (and resident program) from another input with the same generation number. The two engines
    // alternate per round so that load changes on a shared machine hit both alike.
    std::vector<std::unique_ptr<VU1Interpreter>> vus[2];
    for (int variant = 0; variant < 2; ++variant)
        for (std::size_t k = 0; k < inputs.size(); ++k) {
            vus[variant].push_back(std::make_unique<VU1Interpreter>(&sink));
            vus[variant].back()->set_mode(variant == 0 ? VU1Mode::Interp : VU1Mode::Aot);
        }
    u64 pairs[2] = {}, slow = 0;
    double secs[2] = {}, first[2] = {};
    for (int r = 0; r <= rounds; ++r) // round 0 (decode cache / resident check per input) timed separately
        for (int variant = 0; variant < 2; ++variant) {
            const u64 slow0 = aot_slow_ops();
            for (std::size_t k = 0; k < inputs.size(); ++k) {
                VU1Interpreter& vu = *vus[variant][k];
                vu.state() = *inputs[k].st;
                const u64 t0 = vu1_now_ns();
                const RunResult res = vu.mscal(inputs[k].pc / 8u, 1'000'000);
                const double dt = static_cast<double>(vu1_now_ns() - t0) * 1e-9;
                if (r == 0) {
                    first[variant] += dt;
                    continue;
                }
                secs[variant] += dt;
                pairs[variant] += res.steps;
                (variant == 0 ? per_prog[inputs[k].prog].first : per_prog[inputs[k].prog].second) += dt;
                if (variant == 0) per_pairs[inputs[k].prog] += res.steps;
            }
            if (variant == 1 && r > 0) slow += aot_slow_ops() - slow0;
        }
    for (int variant = 0; variant < 2; ++variant) {
        const std::string label = variant == 0 ? "interp" : "aot";
        MESSAGE(label << " first round (cold caches, " << inputs.size() << " runs): " << first[variant] * 1e3 << " ms");
        MESSAGE(label << ": " << pairs[variant] << " pairs, " << secs[variant] * 1e3 << " ms, "
                      << secs[variant] * 1e9 / static_cast<double>(pairs[variant]) << " ns/pair");
    }
    MESSAGE("speed-up " << secs[0] / secs[1] << "x; slow-path FMAC ops " << slow << " (one per "
                        << static_cast<double>(pairs[1]) / static_cast<double>(slow ? slow : 1) << " pairs)");    for (const auto& [prog, t] : per_prog) {
        const double np = static_cast<double>(per_pairs[prog]);
        MESSAGE(prog << ": " << per_pairs[prog] << " pairs; interp " << t.first * 1e9 / np << " ns/pair, aot "
                     << t.second * 1e9 / np << " ns/pair, " << t.first / t.second << "x");
    }
}
