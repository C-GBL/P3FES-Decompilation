// NativeIm2D (native_im2d.h): VU1 program 039's runs computed by the host from the game's Im2D records.
#include "native_im2d.h"

#include "p3fes/ee/fpu.h"
#include "p3fes/vu1/vu1_aot.h"
#include "vu1_aot_rt.h"  // runtime/vu1 (private): the exact VU float kernels of the compiled programs

#include <algorithm>
#include <chrono>
#include <cstring>
#include <optional>

namespace p3fes::native::graphics {

namespace fp = ::p3fes::ee::fpu;

bool g_im2d_fast = true;

namespace {

constexpr u32 kQw = vu1::kDataQwords;  // 1024

// The program's fingerprint: its first pair and FNV-1a 64 over its 376 bytes (the census image vu1_prog_039).
constexpr u64 kHead = 0x000002FF102E07F0ull;
constexpr u32 kBytes = 376;
constexpr u64 kHash = 0xB8208DE1E1872327ull;

u64 fnv(const u8* p, std::size_t n) noexcept {
    u64 h = 0xcbf29ce484222325ull;
    for (std::size_t i = 0; i < n; ++i) h = (h ^ p[i]) * 0x100000001b3ull;
    return h;
}

u8* qw(vu1::VU1State& s, u32 index) noexcept { return s.data + (index & (kQw - 1u)) * 16u; }
const u8* qw(const vu1::VU1State& s, u32 index) noexcept { return s.data + (index & (kQw - 1u)) * 16u; }

// Lanes as the interpreter numbers them: lane i = x, y, z, w for i = 0..3; `dest` bit (8 >> i).
constexpr u32 X = 8, Y = 4, Z = 2, W = 1, XY = X | Y, XYZ = X | Y | Z, XYZW = 15, YZW = Y | Z | W;
bool lane(u32 dest, int i) noexcept { return (dest & (8u >> i)) != 0; }

void load(u32 (&v)[4], const u128& q, u32 dest) noexcept {
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) v[i] = q.u32[i];
}
void load(u32 (&v)[4], const u8* q, u32 dest) noexcept {
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) std::memcpy(&v[i], q + 4 * i, 4);
}
void store(u8* q, const u32 (&v)[4], u32 dest) noexcept {
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) std::memcpy(q + 4 * i, &v[i], 4);
}
bool same(const u8* q, const u128& r, u32 dest) noexcept {  // the `dest` lanes equal (SSE2)
    const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i*>(q));
    const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&r));
    const int eq = _mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(a, b)));
    const int want = static_cast<int>(((dest >> 3) & 1u) | (((dest >> 2) & 1u) << 1) | (((dest >> 1) & 1u) << 2) | ((dest & 1u) << 3));
    return (eq & want) == want;
}

// The flag rule of every flag-setting upper op (runtime/vu1/vu1_semantics.h set_flags): MAC per destination lane
// (Z: exponent zero, S: sign, O: magnitude 0x7FFFFFFF), status Z S U O from it plus their sticky copies; I / D kept.
void set_flags(vu1::VU1State& r, const u32 (&v)[4], u32 dest) noexcept {
    u32 mac = 0;
    for (int i = 0; i < 4; ++i) {
        if (!lane(dest, i)) continue;
        const u32 bit = 3u - static_cast<u32>(i);
        const u32 x = v[i];
        if (!(x & 0x7F800000u)) mac |= 1u << bit;
        if (x & 0x80000000u) mac |= 1u << (bit + 4);
        if ((x & 0x7FFFFFFFu) == 0x7FFFFFFFu) mac |= 1u << (bit + 12);
    }
    r.mac = mac;
    u32 status = r.status & 0xFF0u;
    if (mac & 0x000Fu) status |= 0x1u;
    if (mac & 0x00F0u) status |= 0x2u;
    if (mac & 0x0F00u) status |= 0x4u;
    if (mac & 0xF000u) status |= 0x8u;
    status |= (status & 0xFu) << 6;
    r.status = (status & ~0x30u) | (r.status & 0x30u);
}

// MULz.xy vd, vs, vs.z ; ADD.xy vd, vs, vt ; MUL.xyzw vd, vs, vt ; FTOI4 / FTOI0: the datapath of compute_upper
// (ee/fpu.h). Two equal implementations: fp:: lane by lane, and the compiled programs' SSE kernels (vu1_aot_rt.h:
// host MULPS / ADDPS under round toward zero + FTZ + DAZ, which equal fp::mul / fp::add except on lanes of magnitude
// >= 0x7F7FFFFF, redone with fp::), used when the CPU has what the compiled programs need (vu1::aot_cpu_ok).
namespace aot = ::p3fes::vu1::aot;
thread_local bool g_fast = false;

void mulz_xy(vu1::VU1State& s, u32 (&d)[4]) noexcept {
    u32 o[4] = {0, 0, 0, 0};
    if (g_fast) {
        u32 st = 0;
        const aot::V a = aot::ld(d);
        const aot::Lanes r = aot::lanes_of(aot::vmul<XY>(a, aot::bc<2>(a), st, 0));
        o[0] = r.v[0];
        o[1] = r.v[1];
    } else {
        o[0] = fp::mul(d[0], d[2]);
        o[1] = fp::mul(d[1], d[2]);
    }
    d[0] = o[0];
    d[1] = o[1];
    set_flags(s, o, XY);
}
void add_xy(vu1::VU1State& s, u32 (&d)[4], const u32 (&t)[4]) noexcept {
    u32 o[4] = {0, 0, 0, 0};
    if (g_fast) {
        u32 st = 0;
        const aot::Lanes r = aot::lanes_of(aot::vadd<XY>(aot::ld(d), aot::ld(t), st, 0));
        o[0] = r.v[0];
        o[1] = r.v[1];
    } else {
        o[0] = fp::add(d[0], t[0]);
        o[1] = fp::add(d[1], t[1]);
    }
    d[0] = o[0];
    d[1] = o[1];
    set_flags(s, o, XY);
}
void mul_xyzw(vu1::VU1State& s, u32 (&d)[4], const u32 (&t)[4]) noexcept {
    u32 o[4];
    if (g_fast) {
        u32 st = 0;
        aot::st(o, aot::vmul<XYZW>(aot::ld(d), aot::ld(t), st, 0));
    } else {
        for (int i = 0; i < 4; ++i) o[i] = fp::mul(d[i], t[i]);
    }
    std::memcpy(d, o, sizeof o);
    set_flags(s, o, XYZW);
}
template <int Frac>
void ftoi(u32 (&d)[4], u32 dest) noexcept {
    if (g_fast) {
        u32 o[4];
        aot::st(o, aot::vftoi<Frac>(aot::ld(d)));
        for (int i = 0; i < 4; ++i)
            if (lane(dest, i)) d[i] = o[i];
        return;
    }
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) d[i] = fp::to_fixed(d[i], Frac);
}
u32 mfir(u16 vi) noexcept { return static_cast<u32>(static_cast<s32>(static_cast<s16>(vi))); }

// The interpreter's XGKICK walk (vu1_interp.cpp): tags and their data from `start` up to the first EOP tag's data,
// addresses wrapping at 1024 qwords, at most 1024 qwords.
// The loop 0B..24 (once per triangle, vi12 times) on SSE registers with the compiled programs' kernels: the same values
// as the pair-by-pair version below; the flags are folded once at the end (every flag-setting op of the loop leaves
// MAC = its own lanes' flags, status Z S U O = those of the last op, the sticky bits the OR over all of them).
void tri_loop_fast(vu1::VU1State& s, const u128* in, u32 n) noexcept {
    using aot::V;
    const auto ldq = [](const u128& q) noexcept { return _mm_loadu_si128(reinterpret_cast<const __m128i*>(&q)); };
    const V v28 = aot::ld(s.vf[28]), v29 = aot::ld(s.vf[29]), v31 = aot::ld(s.vf[31]);
    V v15 = aot::ld(s.vf[15]), v16 = aot::ld(s.vf[16]), v17 = aot::ld(s.vf[17]);
    V v8 = aot::ld(s.vf[8]), v9 = aot::ld(s.vf[9]), v10 = aot::ld(s.vf[10]);
    V v22 = aot::ld(s.vf[22]), v23 = aot::ld(s.vf[23]), v24 = aot::ld(s.vf[24]);
    const V w14 = aot::splat(mfir(s.vi[14]));
    u32 st = 0, mac = s.mac, any = 0;
    u32 o = s.vi[11];
    for (u32 t = 0; t < n; ++t, in += 12, o += 10u) {
        v15 = aot::blend<XYZ>(v15, ldq(in[1]));                                // 0B..0E
        v16 = aot::blend<XYZ>(v16, ldq(in[5]));
        v17 = aot::blend<XYZ>(v17, ldq(in[9]));
        v8 = ldq(in[0]);
        v9 = ldq(in[4]);
        v10 = ldq(in[8]);
        v22 = ldq(in[2]);
        v23 = ldq(in[6]);
        v24 = ldq(in[10]);
        v15 = aot::blend<XY>(v15, aot::vmul<XY>(v15, aot::bc<2>(v15), st, 0));  // 0F..11 mulz.xy
        any |= aot::mac_of(v15, XY);
        v16 = aot::blend<XY>(v16, aot::vmul<XY>(v16, aot::bc<2>(v16), st, 0));
        any |= aot::mac_of(v16, XY);
        v17 = aot::blend<XY>(v17, aot::vmul<XY>(v17, aot::bc<2>(v17), st, 0));
        any |= aot::mac_of(v17, XY);
        v8 = aot::blend<XY>(v8, aot::vadd<XY>(v8, v29, st, 0));                  // 12..14 add.xy
        any |= aot::mac_of(v8, XY);
        v9 = aot::blend<XY>(v9, aot::vadd<XY>(v9, v29, st, 0));
        any |= aot::mac_of(v9, XY);
        v10 = aot::blend<XY>(v10, aot::vadd<XY>(v10, v29, st, 0));
        any |= aot::mac_of(v10, XY);
        v22 = aot::vmul<XYZW>(v22, v28, st, 0);                                  // 15..17 mul.xyzw
        any |= aot::mac_of(v22, XYZW);
        v23 = aot::vmul<XYZW>(v23, v28, st, 0);
        any |= aot::mac_of(v23, XYZW);
        v24 = aot::vmul<XYZW>(v24, v28, st, 0);
        mac = aot::mac_of(v24, XYZW);
        any |= mac;
        v8 = aot::blend<XYZ>(w14, aot::vftoi<4>(v8));                            // 16..1A mfir.w, ftoi4.xyz
        v9 = aot::blend<XYZ>(w14, aot::vftoi<4>(v9));
        v10 = aot::blend<XYZ>(w14, aot::vftoi<4>(v10));
        v22 = aot::vftoi<0>(v22);                                                // 1B..1D ftoi0
        v23 = aot::vftoi<0>(v23);
        v24 = aot::vftoi<0>(v24);
        aot::sq<XYZW>(qw(s, o + 0u), v31);                                       // 19..22
        aot::sq<XYZ>(qw(s, o + 1u), v15);
        aot::sq<XYZ>(qw(s, o + 4u), v16);
        aot::sq<XYZ>(qw(s, o + 7u), v17);
        aot::sq<XYZW>(qw(s, o + 3u), v8);
        aot::sq<XYZW>(qw(s, o + 6u), v9);
        aot::sq<XYZW>(qw(s, o + 9u), v10);
        aot::sq<XYZW>(qw(s, o + 2u), v22);
        aot::sq<XYZW>(qw(s, o + 5u), v23);
        aot::sq<XYZW>(qw(s, o + 8u), v24);
    }
    aot::st(s.vf[15], v15);
    aot::st(s.vf[16], v16);
    aot::st(s.vf[17], v17);
    aot::st(s.vf[8], v8);
    aot::st(s.vf[9], v9);
    aot::st(s.vf[10], v10);
    aot::st(s.vf[22], v22);
    aot::st(s.vf[23], v23);
    aot::st(s.vf[24], v24);
    s.vi[10] = static_cast<u16>(s.vi[10] + 12u * n);
    s.vi[11] = static_cast<u16>(o);
    s.vi[12] = 0;
    s.mac = mac;
    s.status = (s.status & 0xFF0u) | (aot::status_low(any) << 6) | aot::status_low(mac);
}

void walk_kick(const vu1::VU1State& s, u32 start, std::vector<u128>& out) {
    out.clear();
    u32 q = start & (kQw - 1u), count = 0;
    bool done = false;
    while (!done && count < kQw) {
        u128 tag;
        std::memcpy(&tag, qw(s, q), 16);
        out.push_back(tag);
        ++count;
        q = (q + 1u) & (kQw - 1u);
        const u64 t0 = tag.u64[0];
        const u32 nloop = static_cast<u32>(t0 & 0x7FFFu);
        const bool eop = ((t0 >> 15) & 1u) != 0;
        const u32 flg = static_cast<u32>(t0 >> 58) & 3u;
        u32 nreg = static_cast<u32>(t0 >> 60) & 0xFu;
        if (!nreg) nreg = 16;
        const u32 body = flg == 0 ? nloop * nreg : flg == 1 ? (nloop * nreg + 1u) / 2u : nloop;
        for (u32 k = 0; k < body && count < kQw; ++k) {
            u128 d;
            std::memcpy(&d, qw(s, q), 16);
            out.push_back(d);
            ++count;
            q = (q + 1u) & (kQw - 1u);
        }
        done = eop;
    }
}

}  // namespace

bool im2d_tri_resident(const vu1::MicroMemory& m) noexcept {
    const u8* b = m.bytes().data();
    u64 head;
    std::memcpy(&head, b, 8);
    return head == kHead && fnv(b, kBytes) == kHash;
}

bool im2d_inputs_match(const vu1::VU1State& s, u32 top, u32 n, const u128 (&head)[3], const u128* verts) noexcept {
    if (!same(qw(s, 1017), head[0], XY) || !same(qw(s, 1018), head[1], YZW) || !same(qw(s, 1019), head[2], XYZW))
        return false;
    for (u32 t = 0; t < n; ++t)
        for (u32 v = 0; v < 3; ++v) {
            const u32 k = 12u * t + 4u * v;
            if (!same(qw(s, top + k), verts[k], XYZ) || !same(qw(s, top + k + 1u), verts[k + 1u], XYZ) ||
                !same(qw(s, top + k + 2u), verts[k + 2u], XYZW))
                return false;
        }
    return true;
}

// Program 039, pair by pair (the listing: tools/ours/vu1/vu1_decode.py on its dump). Each pair's upper op reads the
// registers before its lower op writes and vice versa; no pair of this program has an upper and a lower op touching
// the same register, so program order is the pairs' order. Line numbers = pair indices.
void im2d_tri_run(vu1::VU1State& s, bool from_mscal, const u128 (&head)[3], const u128* verts, std::vector<u128>& kick) {
    kick.clear();
    auto& vf = s.vf;
    auto& vi = s.vi;
    if (from_mscal) vi[14] = 0x0FF0;      // 00 iaddiu vi14, vi00, 0xff0   (MSCNT: 2D b 0x1 skips it)
    vi[10] = static_cast<u16>(s.top);     // 01 xtop vi10
    vi[12] = static_cast<u16>(s.itop);    // 02 xitop vi12
    vi[11] = static_cast<u16>(vi[10] + kIm2DOutOffset);  // 03 iaddiu vi11, vi10, 0xc0
    const u32 out0 = vi[11];               // 04 ibeq vi12, vi00 -> 2B
    {
        const u32 w[4] = {0, 0, 0, vi[11]};  // 05 isw.w vi11, 1023(vi00)   (the branch's delay slot)
        store(qw(s, 1023), w, W);
    }
    if (vi[12] != 0) {
        static const bool fast_ok = vu1::aot_cpu_ok();
        g_fast = fast_ok && g_im2d_fast;
        std::optional<aot::CsrScope> csr;  // the VU float model for the arithmetic only (the kick runs in the host's)
        if (g_fast) csr.emplace();
        load(vf[28], head[2], XYZW);       // 06 lq.xyzw vf28, 1019(vi00)
        load(vf[29], head[0], XY);         // 07 lq.xy vf29, 1017(vi00)
        load(vf[31], head[1], YZW);        // 08 lq.yzw vf31, 1018(vi00)
        vi[13] = 3;                        // 09 iaddiu vi13, vi00, 3
        vf[31][0] = mfir(vi[13]);          // 0A mfir.x vf31, vi13
        const u128* in = verts;
        if (g_fast) {
            tri_loop_fast(s, in, vi[12]);
        } else do {                               // 0B..24, once per triangle
            load(vf[15], in[1], XYZ);      // 0B lq.xyz vf15, 1(vi10)
            load(vf[16], in[5], XYZ);      // 0C
            load(vf[17], in[9], XYZ);      // 0D
            load(vf[8], in[0], XYZW);      // 0E lq.xyzw vf08, 0(vi10)
            mulz_xy(s, vf[15]);            // 0F mulz.xy vf15, vf15, vf15z | lq vf09, 4(vi10)
            load(vf[9], in[4], XYZW);
            mulz_xy(s, vf[16]);            // 10 | lq vf10, 8(vi10)
            load(vf[10], in[8], XYZW);
            mulz_xy(s, vf[17]);            // 11 | lq vf22, 2(vi10)
            load(vf[22], in[2], XYZW);
            add_xy(s, vf[8], vf[29]);      // 12 add.xy vf08, vf08, vf29 | lq vf23, 6(vi10)
            load(vf[23], in[6], XYZW);
            add_xy(s, vf[9], vf[29]);      // 13 | lq vf24, 10(vi10)
            load(vf[24], in[10], XYZW);
            add_xy(s, vf[10], vf[29]);     // 14 | isubiu vi12, vi12, 1
            vi[12] = static_cast<u16>(vi[12] - 1u);
            mul_xyzw(s, vf[22], vf[28]);   // 15 mul.xyzw vf22, vf22, vf28 | iaddiu vi10, vi10, 0xc
            vi[10] = static_cast<u16>(vi[10] + 12u);
            mul_xyzw(s, vf[23], vf[28]);   // 16 | mfir.w vf08, vi14
            vf[8][3] = mfir(vi[14]);
            mul_xyzw(s, vf[24], vf[28]);   // 17 | mfir.w vf09, vi14
            vf[9][3] = mfir(vi[14]);
            ftoi<4>(vf[8], XYZ);           // 18 ftoi4.xyz vf08 | mfir.w vf10, vi14
            vf[10][3] = mfir(vi[14]);
            const u32 o = vi[11];
            ftoi<4>(vf[9], XYZ);           // 19 | sq.xyzw vf31, 0(vi11)
            store(qw(s, o + 0u), vf[31], XYZW);
            ftoi<4>(vf[10], XYZ);          // 1A | sq.xyz vf15, 1(vi11)
            store(qw(s, o + 1u), vf[15], XYZ);
            ftoi<0>(vf[22], XYZW);         // 1B ftoi0 vf22 | sq.xyz vf16, 4(vi11)
            store(qw(s, o + 4u), vf[16], XYZ);
            ftoi<0>(vf[23], XYZW);         // 1C | sq.xyz vf17, 7(vi11)
            store(qw(s, o + 7u), vf[17], XYZ);
            ftoi<0>(vf[24], XYZW);         // 1D | sq.xyzw vf08, 3(vi11)
            store(qw(s, o + 3u), vf[8], XYZW);
            store(qw(s, o + 6u), vf[9], XYZW);   // 1E
            store(qw(s, o + 9u), vf[10], XYZW);  // 1F
            store(qw(s, o + 2u), vf[22], XYZW);  // 20
            store(qw(s, o + 5u), vf[23], XYZW);  // 21
            store(qw(s, o + 8u), vf[24], XYZW);  // 22
            vi[11] = static_cast<u16>(vi[11] + 10u);  // 23 iaddiu vi11, vi11, 0xa
            in += 12;
        } while (static_cast<s16>(vi[12]) > 0);  // 24 ibgtz vi12, 0xb
        vi[1] = 0x4000;                          // 26 iaddiu vi01, vi00, 0x4000
        vi[1] = static_cast<u16>(vi[1] + vi[1]); // 27 iadd vi01, vi01, vi01
        {
            const u32 w[4] = {vi[1], 0, 0, 0};   // 28 iswr.x vi01, (vi11)
            store(qw(s, vi[11]), w, X);
        }
        csr.reset();
        u16 v13;                                 // 29 ilw.w vi13, 1023(vi00)
        std::memcpy(&v13, qw(s, 1023) + 12, 2);
        vi[13] = v13;
        walk_kick(s, vi[13], kick);              // 2A xgkick vi13
    }
    (void)out0;
    // 2B [E] nop, 2C nop: the unit stops with TPC at 2D. The interpreter's bookkeeping of the last pair: vi_before
    // holds the vi file before pair 2C (unchanged since), the branch-delay view is live (2C's lower op is a NOP).
    s.pc = kIm2DTriEndTpc;
    s.npc = kIm2DTriEndTpc + 8u;
    s.tpc = kIm2DTriEndTpc;
    s.running = false;
    s.ending = false;
    std::memcpy(s.vi_before, s.vi, sizeof s.vi_before);
    s.vi_delay_live = true;
}

// ---------------------------------------------------------------------------------------------------------------

struct NativeIm2D::Checker final : vu1::IGifSink {
    vu1::VU1Interpreter vu{this};
    u64 gen = 0;
    std::vector<u128> kicked;
    void kick(std::span<const u128> q) override { kicked.insert(kicked.end(), q.begin(), q.end()); }
};

NativeIm2D::NativeIm2D() = default;
NativeIm2D::~NativeIm2D() = default;

void NativeIm2D::set_check(u32 every, std::FILE* log) {
    check_every_ = every;
    log_ = log;
    if (every && !chk_) chk_ = std::make_unique<Checker>();
}

void NativeIm2D::clear_queue() {
    std::lock_guard<std::mutex> l(m_);
    while (!q_.empty()) {
        spare_.push_back(std::move(q_.front().qw));
        q_.pop_front();
    }
}

void NativeIm2D::other_packet(u32) noexcept { ++st_.packets_other; }

void NativeIm2D::packet(u32 program, const u128 (&head)[3], std::span<const Im2DBatchView> batches) {
    if (program != kIm2DTriProgram) {
        ++st_.packets_other;
        return;
    }
    ++st_.packets;
    std::lock_guard<std::mutex> l(m_);
    for (const Im2DBatchView& b : batches) {
        ++st_.batches;
        st_.tris += b.n;
        if (b.n == 0 || b.n > kIm2DMaxTris || b.qw.size() != 12u * b.n) continue;  // a run of it falls back
        if (q_.size() >= (1u << 16)) {
            spare_.push_back(std::move(q_.front().qw));
            q_.pop_front();
            ++st_.overflow;
        }
        Rec r;
        r.n = b.n;
        std::memcpy(r.head, head, sizeof r.head);
        if (!spare_.empty()) {
            r.qw = std::move(spare_.back());
            spare_.pop_back();
        }
        r.qw.assign(b.qw.begin(), b.qw.end());
        q_.push_back(std::move(r));
    }
}

bool NativeIm2D::take(const vu1::VU1State& s, u32 top, u32 n, Rec& out) {
    std::lock_guard<std::mutex> l(m_);
    const std::size_t look = std::min<std::size_t>(q_.size(), 64);
    for (std::size_t k = 0; k < look; ++k) {
        const Rec& r = q_[k];
        if (r.n != n || !im2d_inputs_match(s, top, n, r.head, r.qw.data())) continue;
        for (std::size_t d = 0; d < k; ++d) {
            spare_.push_back(std::move(q_.front().qw));
            q_.pop_front();
            ++st_.dropped;
        }
        spare_.push_back(std::move(out.qw));
        out = std::move(q_.front());
        q_.pop_front();
        return true;
    }
    return false;
}

bool NativeIm2D::run(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) {
    vu1::VU1State& s = vu.state();
    forwarded_ = false;
    if (s.micro.generation() != micro_gen_) {
        micro_gen_ = s.micro.generation();
        resident_ = im2d_tri_resident(s.micro);
    }
    if (!resident_) {
        ++st_.other_runs;
        forwarded_ = next_ != nullptr;
        return next_ ? next_->run(r, vu) : false;
    }
    const auto t0 = std::chrono::steady_clock::now();
    ++st_.runs;
    const bool mscal = r.op == 0x14 || r.op == 0x15;
    if ((mscal && r.imm != 0) || (!mscal && s.tpc != kIm2DTriEndTpc)) {
        ++st_.fb_entry;
        return false;
    }
    const u32 n = s.itop;
    if (n == 0 || n > kIm2DMaxTris) {
        ++st_.fb_count;
        return false;
    }
    if (!take(s, s.top, n, cur_)) {
        ++st_.fb_nomatch;
        return false;
    }
    const bool checking = check_every_ != 0 && (check_seq_++ % check_every_) == 0;
    std::unique_ptr<vu1::VU1State> before;
    if (checking) before = std::make_unique<vu1::VU1State>(s);
    im2d_tri_run(s, mscal, cur_.head, cur_.qw.data(), kick_);
    if (checking) check(r, *before, s);
    const auto t1 = std::chrono::steady_clock::now();
    st_.ns += static_cast<u64>(std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count());
    if (!kick_.empty())
        if (vu1::IGifSink* sink = vu.sink()) {
            if (direct_) {
                sink->kick_host(kick_);
                ++st_.kick_host;
            } else {
                sink->kick(kick_);
            }
        }
    st_.kick_ns += static_cast<u64>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t1).count());
    ++st_.native;
    st_.native_tris += n;
    st_.native_kick_qw += kick_.size();
    return true;
}

// Step 2: the builders' vertex UNPACK (STCYCL 4,4; STMASK 0xC000C000; UNPACK V4-32 masked, MODE 0; render_im2d.cpp's
// report_native_packet checks the same words) written as an image: per vertex of 4 qwords, qwords 0 and 2 whole and
// qwords 1 and 3 without their w lane (mask rows 1 and 3, lane w = 3: write-protected). That is vif_unpack's result
// for this form, element for element (no ROW / COL lane, no filling write, no MODE addition).
bool NativeIm2D::unpack(const gs::UnpackArgs& a, const u32* words, std::size_t n, u8* mem, u32*, u32& vectors) {
    if (!direct_ || ((a.code >> 24) & 0x7Fu) != 0x7Cu || a.cycle != 0x0404u || a.mask != 0xC000C000u || a.mode != 0 || !mem)
        return false;
    u32 num = (a.code >> 16) & 0xFFu;
    if (num == 0) num = 256;
    if (n < 4u * num) return false;  // a short payload: the generic path's zero fill
    u32 addr = (a.code & 0x3FFu) + (((a.code >> 15) & 1u) ? a.tops : 0u);
    for (u32 i = 0; i < num; ++i, ++addr, words += 4)
        std::memcpy(mem + (addr & (kQw - 1u)) * 16u, words, (i & 1u) ? 12u : 16u);
    vectors = num;
    ++st_.unpacks;
    st_.unpack_qw += num;
    return true;
}

void NativeIm2D::after_exact(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) {
    if (forwarded_ && next_) next_->after_exact(r, vu);
    forwarded_ = false;
}

// The exact run from `before` on the scratch interpreter (the oracle), compared with what the native run left.
void NativeIm2D::check(const gs::VuRunInfo& r, const vu1::VU1State& before, const vu1::VU1State& after) {
    Checker& c = *chk_;
    vu1::VU1State& x = c.vu.state();
    if (c.gen != before.micro.generation()) {
        c.vu.load_micro(0, before.micro.bytes());
        c.gen = before.micro.generation();
    }
    const vu1::MicroMemory keep = x.micro;
    x = before;
    x.micro = keep;
    c.kicked.clear();
    const bool mscal = r.op == 0x14 || r.op == 0x15;
    const vu1::RunResult rr = mscal ? c.vu.mscal(r.imm) : c.vu.mscnt();
    ++st_.checked;
    const char* what = nullptr;
    if (rr.status != vu1::RunStatus::Ended) what = "the exact run did not end";
    else if (std::memcmp(x.vf, after.vf, sizeof x.vf) != 0) what = "vf";
    else if (std::memcmp(x.vi, after.vi, sizeof x.vi) != 0) what = "vi";
    else if (std::memcmp(x.acc, after.acc, sizeof x.acc) != 0 || x.q != after.q || x.p != after.p || x.i != after.i ||
             x.r != after.r)
        what = "acc/q/p/i/r";
    else if (x.mac != after.mac || x.status != after.status || x.clip != after.clip) what = "flags";
    else if (x.pc != after.pc || x.npc != after.npc || x.tpc != after.tpc || x.running != after.running ||
             x.ending != after.ending || x.top != after.top || x.itop != after.itop)
        what = "pc/tpc";
    else if (std::memcmp(x.vi_before, after.vi_before, sizeof x.vi_before) != 0 || x.vi_delay_live != after.vi_delay_live)
        what = "branch view";
    else if (std::memcmp(x.data, after.data, sizeof x.data) != 0) what = "data memory";
    else if (c.kicked.size() != kick_.size() ||
             (!kick_.empty() && std::memcmp(c.kicked.data(), kick_.data(), kick_.size() * sizeof(u128)) != 0))
        what = "kicked packet";
    if (what) {
        ++st_.check_bad;
        if (log_ && st_.check_bad <= 8)
            std::fprintf(log_, "p3fes: native graphics check: run %llu (op %02X, top %03X, %u triangles): %s differs\n",
                         static_cast<unsigned long long>(st_.runs), r.op, before.top, before.itop, what);
    }
}

}  // namespace p3fes::native::graphics
