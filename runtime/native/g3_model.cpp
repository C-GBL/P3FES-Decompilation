// Semantic model of the g3 VU1 programs (g3_model.h; docs/ANALYSIS/31_native_renderer.md §2). Every step names
// the pairs of vu1_prog_042_g3_generic (code 0x6B8D4C) it stands for; vu1_prog_064_g3_skin (0x6F8B1C) runs the same
// lighting and transform code after its skinning pre-pass.
#include "g3_model.h"

#include "p3fes/vu1/vu1_interp.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <span>

namespace p3fes::native {

namespace {

struct F4 {
    float x = 0, y = 0, z = 0, w = 0;
    float& operator[](int i) { return (&x)[i]; }
    float operator[](int i) const { return (&x)[i]; }
};

F4 operator+(F4 a, F4 b) { return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }
F4 operator-(F4 a, F4 b) { return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }
F4 operator*(F4 a, F4 b) { return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}; }
F4 operator*(F4 a, float s) { return {a.x * s, a.y * s, a.z * s, a.w * s}; }

float f32(u32 v) {
    float f;
    std::memcpy(&f, &v, 4);
    return f;
}

// VU operand view of a register lane: denormals read as zero (the VU flushes them).
float vuf(u32 v) {
    if ((v & 0x7F800000u) == 0) v &= 0x80000000u;
    return f32(v);
}

F4 ld(const u8* data, u32 qw) {
    const u8* p = data + (qw & 1023u) * 16u;
    u32 w[4];
    std::memcpy(w, p, 16);
    return {vuf(w[0]), vuf(w[1]), vuf(w[2]), vuf(w[3])};
}
void ldi(const u8* data, u32 qw, s32 out[4]) { std::memcpy(out, data + (qw & 1023u) * 16u, 16); }
u32 ldw(const u8* data, u32 qw, int lane) {
    u32 v;
    std::memcpy(&v, data + (qw & 1023u) * 16u + lane * 4, 4);
    return v;
}
F4 reg(const vu1::VU1State& s, int r) { return {vuf(s.vf[r][0]), vuf(s.vf[r][1]), vuf(s.vf[r][2]), vuf(s.vf[r][3])}; }
F4 itof(const s32 v[4]) { return {float(v[0]), float(v[1]), float(v[2]), float(v[3])}; }

// FTOI0 / FTOI4: truncation, saturating.
s32 ftoi(float f, float scale) {
    const double d = double(f) * scale;
    if (!(d == d)) return 0;
    if (d >= 2147483647.0) return 0x7FFFFFFF;
    if (d <= -2147483648.0) return s32(0x80000000u);
    return s32(d);
}

float dot3(F4 a, F4 b) { return (a.x * b.x + a.z * b.z) + a.y * b.y; }

constexpr u32 kLightMat = 0x3D0, kLights = 0x3D4;
constexpr u32 kFog = 0x3F6, kTag = 0x3FA, kMatCol = 0x3FB, kLightK = 0x3FC, kClip1 = 0x3FD, kClip2 = 0x3FE, kFlags = 0x3FF;

struct VertexIn {
    F4 pos, uv, col, nrm;
};

// Skin pre-pass (064 pairs 0x4B-0x77 / 0x79-0xAD): per vertex the four bone matrices at 0x2B8 + index (the
// indices are the low 16 bits of the weight words, already multiplied by 4), blended with the weights (the whole
// float words), applied to position (with translation, row 0x2BB) and normal (rows 0x2B8..0x2BA).
void skin_vertex(const u8* d, u32 top, u32 i, VertexIn& v) {
    const u32 b = top + i * 5u;
    s32 idx[4];
    ldi(d, b + 4, idx);
    const F4 wt = ld(d, b + 4);
    F4 m[4];
    for (int r = 0; r < 4; ++r) {
        F4 acc{};
        for (int j = 0; j < 4; ++j) acc = acc + ld(d, 0x2B8u + u32(r) + (u32(idx[j]) & 0xFFFFu)) * wt[j];
        m[r] = acc;
    }
    // rows: m[0] 0x2B8 (x), m[1] 0x2B9 (y), m[2] 0x2BA (z), m[3] 0x2BB (translation)
    const F4 p = v.pos, n = v.nrm;
    v.pos = m[3] + m[0] * p.x + m[1] * p.y + m[2] * p.z;
    v.nrm = m[0] * n.x + m[1] * n.y + m[2] * n.z;
}

} // namespace

const char* to_string(G3Variant v) noexcept {
    static const char* const k[] = {"strip", "strip_fog", "list", "list_fog", "cull_strip", "cull_strip_fog",
                                    "cull_list", "cull_list_fog", "clip_strip", "clip_list", "?"};
    return k[static_cast<int>(v) < 10 ? static_cast<int>(v) : 10];
}

G3Variant g3_variant(G3Prog prog, u32 flags) noexcept {
    if (prog != G3Prog::SkinPar) return g3_variant(flags);
    const bool clip = flags & 2u, full = flags & 8u, list = flags & 4u;
    if (!clip) return list ? G3Variant::ListFog : G3Variant::StripFog;
    if (full) return list ? G3Variant::ClipList : G3Variant::ClipStrip;
    return list ? G3Variant::CullListFog : G3Variant::CullStripFog;
}

G3Variant g3_variant(u32 flags) noexcept {
    const bool clip = flags & 2u, full = flags & 8u, list = flags & 4u, fog = flags & 1u;
    if (!clip) return list ? (fog ? G3Variant::ListFog : G3Variant::List) : (fog ? G3Variant::StripFog : G3Variant::Strip);
    if (full) return list ? G3Variant::ClipList : G3Variant::ClipStrip;
    return list ? (fog ? G3Variant::CullListFog : G3Variant::CullList) : (fog ? G3Variant::CullStripFog : G3Variant::CullStrip);
}

bool g3_fog(G3Variant v) noexcept {
    return v == G3Variant::StripFog || v == G3Variant::ListFog || v == G3Variant::CullStripFog || v == G3Variant::CullListFog;
}
bool g3_list(G3Variant v) noexcept {
    return v == G3Variant::List || v == G3Variant::ListFog || v == G3Variant::CullList || v == G3Variant::CullListFog ||
           v == G3Variant::ClipList;
}

namespace {
struct Known {
    G3Prog prog;
    u32 bytes;
    u64 head;  // first pair (lower word | upper word << 32)
    u64 hash;
};
// vu1_prog_042_g3_generic (code 0x6B8D4C) and vu1_prog_064_g3_skin (0x6F8B1C) as uploaded at micro address 0
// (symbols/vu1_micro_census.json; hashes of the dumps tools/ours/vu1/vu1_dump.py writes).
constexpr Known kKnown[] = {
    {G3Prog::Generic, 14712, 0x805CE72C3F000000ull, 0xF8DA9292ECDBBEE4ull},
    {G3Prog::Skin, 15432, 0x805CE72C3F000000ull, 0x0C21DE9BA067B350ull},
    {G3Prog::SkinPar, 12616, 0x0022108701FF03F3ull, 0xFEFA4824B20A548Cull},  // vu1_prog_063_g3_skin (0x6F598C)
};
} // namespace

u64 micro_hash(const u8* p, u32 bytes) noexcept {
    u64 h = 0xCBF29CE484222325ull;
    for (u32 i = 0; i + 8 <= bytes; i += 8) {
        u64 w;
        std::memcpy(&w, p + i, 8);
        h = (h ^ w) * 0x100000001B3ull;
    }
    return h;
}

G3Prog g3_identify(const u8* micro) noexcept {
    u64 head;
    std::memcpy(&head, micro, 8);
    for (const Known& k : kKnown)
        if (head == k.head && micro_hash(micro, k.bytes) == k.hash) return k.prog;
    return G3Prog::None;
}

u32 g3_batch_pc(G3Prog prog) noexcept {
    return prog == G3Prog::None ? 0u : prog == G3Prog::SkinPar ? 0x25u * 8u : 0x33u * 8u;
}
u32 g3_out_buffer(G3Prog prog, int which) noexcept {
    if (prog == G3Prog::Generic) return which == 13 ? 0x228u : 0x2FCu;
    return which == 13 ? 0x1AEu : 0x235u;
}
u32 g3_end_tpc(G3Prog prog) noexcept {
    switch (prog) {
    case G3Prog::Generic: return 0x72Du * 8u;
    case G3Prog::Skin: return 0x787u * 8u;
    case G3Prog::SkinPar: return 0x627u * 8u;
    default: return 0;
    }
}
u32 g3_variant_pc(G3Prog prog, G3Variant v) noexcept {
    // order: Strip StripFog List ListFog CullStrip CullStripFog CullList CullListFog ClipStrip ClipList
    static const u16 generic[] = {0x1B2, 0x22A, 0x1F3, 0x282, 0x2C6, 0x34B, 0x311, 0x3B3, 0x3FF, 0x59E};
    static const u16 skin[] = {0x20C, 0x284, 0x24D, 0x2DC, 0x320, 0x3A5, 0x36B, 0x40D, 0x459, 0x5F8};
    static const u16 skinpar[] = {0x1FE, 0x1FE, 0x246, 0x246, 0x27B, 0x27B, 0x2D3, 0x2D3, 0x319, 0x4AB};
    const int i = static_cast<int>(v);
    if (i >= 10) return 0;
    return prog == G3Prog::Generic ? generic[i] : prog == G3Prog::Skin ? skin[i] : prog == G3Prog::SkinPar ? skinpar[i] : 0u;
}

namespace {
float lane(const vu1::VU1State& s, int r, int i) {
    float f;
    std::memcpy(&f, &s.vf[r][i], 4);
    return f;
}
void set_lane(vu1::VU1State& s, int r, int i, float f) { std::memcpy(&s.vf[r][i], &f, 4); }
float mem_lane(const vu1::VU1State& s, u32 qw, int i) {
    float f;
    std::memcpy(&f, s.data + (qw & 1023u) * 16u + i * 4, 4);
    return f;
}
} // namespace

// MSCAL 0 up to the batch start (pairs 0x00-0x32 of both programs): the screen-space transform rows vf28..vf31
// from 0x3F0..0x3F3 (z lanes zeroed, vf31.z = 1, xy recentred by half of w, scaled by 0x3F7), the screen offset vf02
// (0x3F8 + 0x3F9.xy), the variant's continuation stored at 0x3FF.y, the two output buffers vi13 / vi14.
void g3_init(G3Prog p, vu1::VU1State& s) {
    if (p == G3Prog::SkinPar) {
        // 063 pairs 0x00-0x24: rows vf28..vf31 = 0x3F0..0x3F3 whole, vf31.xy - 0.5, xyz scaled by 0x3F7
        const float sx = mem_lane(s, 0x3F7, 0), sy = mem_lane(s, 0x3F7, 1), sz = mem_lane(s, 0x3F7, 2);
        for (int r = 0; r < 4; ++r) {
            const u32 qw = 0x3F0u + static_cast<u32>(r);
            float x = mem_lane(s, qw, 0), y = mem_lane(s, qw, 1);
            if (r == 3) {
                x -= 0.5f;
                y -= 0.5f;
            }
            set_lane(s, 28 + r, 0, x * sx);
            set_lane(s, 28 + r, 1, y * sy);
            set_lane(s, 28 + r, 2, mem_lane(s, qw, 2) * sz);
            set_lane(s, 28 + r, 3, mem_lane(s, qw, 3));
        }
        set_lane(s, 2, 0, mem_lane(s, 0x3F8, 0) + mem_lane(s, 0x3F9, 0));
        set_lane(s, 2, 1, mem_lane(s, 0x3F8, 1) + mem_lane(s, 0x3F9, 1));
        set_lane(s, 2, 2, mem_lane(s, 0x3F8, 2));
        set_lane(s, 2, 3, 0.0f);
    } else {
    for (int r = 0; r < 4; ++r) {
        const u32 qw = 0x3F0u + static_cast<u32>(r);
        const float x = mem_lane(s, qw, 0), y = mem_lane(s, qw, 1), w = mem_lane(s, qw, 3);
        const float hw = w * 0.5f;
        set_lane(s, 28 + r, 0, x - hw);
        set_lane(s, 28 + r, 1, y - hw);
        set_lane(s, 28 + r, 2, r == 3 ? 1.0f : 0.0f);
        set_lane(s, 28 + r, 3, w);
    }
    const float sx = mem_lane(s, 0x3F7, 0), sy = mem_lane(s, 0x3F7, 1), sz = mem_lane(s, 0x3F7, 2);
    for (int r = 28; r < 32; ++r) {
        set_lane(s, r, 0, lane(s, r, 0) * sx);
        set_lane(s, r, 1, lane(s, r, 1) * sy);
    }
    set_lane(s, 31, 2, lane(s, 31, 2) * sz);
    set_lane(s, 2, 0, mem_lane(s, 0x3F8, 0) + mem_lane(s, 0x3F9, 0));
    set_lane(s, 2, 1, mem_lane(s, 0x3F8, 1) + mem_lane(s, 0x3F9, 1));
    set_lane(s, 2, 2, mem_lane(s, 0x3F8, 2));
    set_lane(s, 2, 3, 0.0f);
    }
    u32 flags;
    std::memcpy(&flags, s.data + 0x3FFu * 16u, 4);
    const u32 vpc = g3_variant_pc(p, g3_variant(p, flags & 0xFFFFu));
    s.vi[12] = static_cast<u16>(vpc);
    const u32 y = vpc;  // ISW.y: the 16-bit value zero-extended into the word
    std::memcpy(s.data + 0x3FFu * 16u + 4, &y, 4);
    s.vi[13] = static_cast<u16>(g3_out_buffer(p, 13));
    s.vi[14] = static_cast<u16>(g3_out_buffer(p, 14));
}

namespace {
// vu1_prog_063_g3_skin's output part (0x1FE strip, 0x246 list, 0x27B / 0x2D3 guard band, 0x319 / 0x4AB clipper):
// parallel projection, screen = vf31 + vf02 + M p without division, STQ = (u, v, 1), fog = clamp(fs (w - near))
// in every variant, the guard band judged against +-1, ADC = cross-product sign != cull mode (raw 0x3FF.z).
bool g3_par_output(const vu1::VU1State& s, const u8* d, G3Batch& out, const VertexIn* v, u32 n) {
    const G3Variant var = out.variant;
    const bool list = g3_list(var);
    const bool cull = var == G3Variant::CullStripFog || var == G3Variant::CullListFog;
    const bool clipper = var == G3Variant::ClipStrip || var == G3Variant::ClipList;
    if (var == G3Variant::ClipList) return false;
    const F4 r28 = reg(s, 28), r29 = reg(s, 29), r30 = reg(s, 30), r31 = reg(s, 31), off = reg(s, 2);
    const F4 fg = ld(d, kFog);
    const float fs = fg.z, fnear = fg.w * fs;
    const F4 c1 = ld(d, kClip1), c2 = ld(d, kClip2);
    const u32 cullz = ldw(d, kFlags, 2) & 0xFFFFu;
    out.tag[0] = 0x8000u | n;
    out.tag[1] = ldw(d, kTag, 1);
    out.tag[2] = ldw(d, kTag, 2);
    out.tag[3] = ldw(d, kTag, 3);
    out.v.resize(n);
    thread_local std::vector<F4> scr_buf;
    thread_local std::vector<u32> clipf_buf;
    thread_local std::vector<float> fogw_buf;
    scr_buf.resize(n);
    clipf_buf.resize(n);
    fogw_buf.resize(n);
    u32 all_out = 0x3F, any_out = 0;
    for (u32 i = 0; i < n; ++i) {
        const F4 p = v[i].pos;
        F4 c;  // vf31 + M p (all four lanes)
        c.x = r31.x + r28.x * p.x + r29.x * p.y + r30.x * p.z;
        c.y = r31.y + r28.y * p.x + r29.y * p.y + r30.y * p.z;
        c.z = r31.z + r28.z * p.x + r29.z * p.y + r30.z * p.z;
        c.w = r31.w + r28.w * p.x + r29.w * p.y + r30.w * p.z;
        scr_buf[i] = F4{c.x + off.x, c.y + off.y, c.z + off.z, 0};
        float fw;
        if (cull) {
            fw = std::min(std::max(c.w * fs, fnear), fnear + 255.0f) - fnear;
        } else {
            fw = std::max(std::min((r31.w * fs - fnear) + (r28.w * fs) * p.x + (r29.w * fs) * p.y + (r30.w * fs) * p.z, 255.0f), 0.0f);
        }
        if (clipper) fw = std::max(std::min(c.w * fs - fnear, 255.0f), 0.0f);
        fogw_buf[i] = fw;
        if (cull || clipper) {
            const F4 t{c.x * c1.y, c.y * c2.y, c1.z + c2.z * c.w, 1.0f};
            u32 f = 0;
            if (t.x > 1.0f) f |= 1;
            if (t.x < -1.0f) f |= 2;
            if (t.y > 1.0f) f |= 4;
            if (t.y < -1.0f) f |= 8;
            if (t.z > 1.0f) f |= 16;
            if (t.z < -1.0f) f |= 32;
            clipf_buf[i] = f;
            all_out &= f;
            any_out |= f;
        }
        G3OutVertex& o = out.v[i];
        o.s = v[i].uv.x;
        o.t = v[i].uv.y;
        o.q = 1.0f;
        o.qw = 0;
        for (int j = 0; j < 4; ++j) o.rgba[j] = ftoi(v[i].col[j], 1.0f);
        o.xyzw[0] = ftoi(scr_buf[i].x, 16.0f);
        o.xyzw[1] = ftoi(scr_buf[i].y, 16.0f);
        o.xyzw[2] = ftoi(scr_buf[i].z, 16.0f);
        o.xyzw[3] = 0;
    }
    if (clipper) {
        if (all_out) {
            out.culled_all = true;
            out.v.clear();
            return true;
        }
        if (any_out) {
            out.clipped = true;
            return false;
        }
    }
    const auto cz = [](F4 a, F4 b) { return a.x * b.y - b.x * a.y; };
    const F4* sv = scr_buf.data();
    for (u32 i = 0; i < n; ++i) {
        bool judged = false, neg = false;
        if (i >= 2) {
            if (list) {
                if (i % 3 == 2) {
                    neg = std::signbit(cz(sv[i] - sv[i - 2], sv[i - 1] - sv[i - 2]));
                    judged = true;
                }
            } else {
                neg = (i & 1u) == 0 ? std::signbit(cz(sv[i - 1] - sv[i - 2], sv[i - 1] - sv[i]))
                                    : std::signbit(cz(sv[i] - sv[i - 1], sv[i - 2] - sv[i - 1]));
                judged = true;
            }
        }
        const u32 sflag = neg ? 0x20u : 0u;
        bool adc = false;
        if (judged) {
            const bool outside = cull && (clipf_buf[i] | clipf_buf[i - 1] | clipf_buf[i - 2]) != 0;
            adc = (cull ? (outside ? 1u : 0u) + sflag : sflag) != cullz;
        }
        const float bump = !adc ? 0.0f : cull ? 2048.5f : 2048.0f;
        out.v[i].xyzw[3] = ftoi(fogw_buf[i] + bump, 16.0f);
    }
    return true;
}
} // namespace

bool g3_model(G3Prog prog, const vu1::VU1State& s, G3Batch& out) {
    out.prog = G3Prog::None;
    out.variant = G3Variant::Count;
    out.n = 0;
    out.clipped = out.culled_all = out.morph = false;
    out.lights = 0;
    out.v.clear();
    out.dbg.clear();
    out.explicit_tris = false;
    out.tris.clear();
    out.prog = prog;
    if (prog == G3Prog::None) return false;
    const u8* d = s.data;
    const u32 flags = ldw(d, kFlags, 0);
    out.variant = g3_variant(prog, flags & 0xFFFFu);
    const bool par = prog == G3Prog::SkinPar;
    const u32 top = s.top & 1023u;
    const u32 n = s.itop & 1023u;
    out.n = n;
    if (n == 0 || n > 256) return false;

    // ---- vertex input and morph (generic 0x3E-0x81 / 0x186-0x1AF; skin 0x3E-0xAD)
    const F4 k = ld(d, kLightK);        // vf03: x ambient, z directional/point, w morph factor
    const bool morph = k.w != 0.0f;     // the Z flag of `addx.w vf24, vf03, vf00x` (0x42), read by fmand at 0x46
    out.morph = morph;
    const u32 lights_type0 = ldw(d, kLights, 3) & 0xFFFFu;
    const bool lit = lights_type0 != 0;
    const bool skin = prog == G3Prog::Skin || prog == G3Prog::SkinPar;
    const u32 stride = skin ? 5u : 4u;
    // scratch reused across batches (one model call at a time per thread)
    thread_local std::vector<VertexIn> v_buf;
    thread_local std::vector<F4> scr_buf, sq_buf, cc_buf;
    thread_local std::vector<u32> clipf_buf;
    thread_local std::vector<float> fogw_buf;
    v_buf.resize(n);
    VertexIn* const v = v_buf.data();
    const std::span<VertexIn> vv(v, n);
    const float inv128 = 0.0078125f;
    for (u32 i = 0; i < n; ++i) {
        const u32 b = top + i * stride;
        VertexIn& x = v[i];
        x.pos = ld(d, b + 0);
        x.uv = ld(d, b + 1);
        s32 ci[4], ni[4];
        ldi(d, b + 2, ci);
        ldi(d, b + 3, ni);
        x.col = itof(ci);
        const F4 nf = itof(ni);
        if (morph) {
            const float w1 = 1.0f - k.w, w2 = k.w;  // vf27 = (w, ., ., 1 - w)
            const u32 m = top + n * stride;         // second target: N positions, then N normals
            x.pos = x.pos * w1 + ld(d, m + i) * w2;
            s32 n2[4];
            ldi(d, m + n + i, n2);
            x.nrm = nf * (w1 * inv128) + itof(n2) * (w2 * inv128);
        } else {
            x.nrm = nf * inv128;
        }
        if (skin) skin_vertex(d, top, i, x);
    }

    // ---- lights (0x82-0x185): accumulate into the colour, then clamp to 255 and scale by the material colour
    const F4 matcol = ld(d, kMatCol);
    if (lit) {
        const F4 m0 = ld(d, kLightMat + 0), m1 = ld(d, kLightMat + 1), m2 = ld(d, kLightMat + 2), m3 = ld(d, kLightMat + 3);
        const auto xf3 = [&](F4 a) { return m0 * a.x + m1 * a.y + m2 * a.z; };
        u32 p = kLights;
        for (int guard = 0; guard < 64; ++guard) {
            const u32 type = ldw(d, p, 3) & 0xFFFFu;
            F4 lc = ld(d, p);
            const F4 r1 = ld(d, p + 1), r2 = ld(d, p + 2);
            if (type == 2) {  // ambient (0xA2)
                out.lights |= 1;
                lc = lc * k.x;
                for (auto& x : vv) {
                    x.col.x += lc.x;
                    x.col.y += lc.y;
                    x.col.z += lc.z;
                }
                p += 1;
            } else if (type == 1) {  // directional (0xB3): dir' = M3 dir * -m3.w
                out.lights |= 2;
                const F4 dir = xf3(r1) * (-m3.w);
                lc = lc * k.z;
                for (auto& x : vv) {
                    const float dt = std::max(dot3(x.nrm, dir), 0.0f);
                    x.col.x += lc.x * dt;
                    x.col.y += lc.y * dt;
                    x.col.z += lc.z * dt;
                }
                p += 2;
            } else if (type == 0x80 || type == 0x81 || type == 0x82) {  // point (0xD7), spot (0x106), soft spot (0x143)
                out.lights |= type == 0x80 ? 4 : type == 0x81 ? 8 : 16;
                F4 lp = xf3(r1) + m3;  // M4 position
                const float rinv = 1.0f / (r1.w * m0.w);
                lc = lc * k.z;
                const F4 sdir = xf3(r2) * m3.w;
                const float cone = r2.w * m3.w;
                for (auto& x : vv) {
                    const F4 dv = lp - x.pos;
                    const float len2 = dot3(dv, dv);
                    const float il = 1.0f / std::sqrt(len2);
                    const float dn = std::max(dot3(dv, x.nrm), 0.0f);
                    const float f = dn * (il - rinv);
                    F4 c{lc.x * f, lc.y * f, lc.z * f, 0};
                    if (type == 0x80) {
                        x.col.x = std::max(x.col.x + c.x, x.col.x);
                        x.col.y = std::max(x.col.y + c.y, x.col.y);
                        x.col.z = std::max(x.col.z + c.z, x.col.z);
                    } else if (type == 0x81) {
                        const float cs = dot3(dv, sdir) * il;
                        if (!(cone - cs < 0.0f)) {
                            x.col.x += std::max(c.x, 0.0f);
                            x.col.y += std::max(c.y, 0.0f);
                            x.col.z += std::max(c.z, 0.0f);
                        }
                    } else {
                        const float s11 = m3.w;
                        const float pinv = 1.0f / (s11 + r2.w * s11);
                        const float accw = cone * pinv;
                        const float cs = dot3(dv, sdir) * il;
                        const float fall = std::max(accw - pinv * cs, 0.0f);
                        x.col.x += std::max(c.x, 0.0f) * fall;
                        x.col.y += std::max(c.y, 0.0f) * fall;
                        x.col.z += std::max(c.z, 0.0f) * fall;
                    }
                }
                p += type == 0x80 ? 2u : 3u;
            } else {
                break;  // end of the list (any other type: 0x8F)
            }
        }
        for (auto& x : vv) x.col = F4{std::min(x.col.x, 255.0f), std::min(x.col.y, 255.0f), std::min(x.col.z, 255.0f),
                                     std::min(x.col.w, 255.0f)} * matcol;
    } else {
        for (auto& x : vv) x.col = x.col * matcol;
    }

    // ---- transform and output (0x1B2 ...)
    const G3Variant var = out.variant;
    const bool fog = g3_fog(var), list = g3_list(var);
    const bool cull = var == G3Variant::CullStrip || var == G3Variant::CullStripFog || var == G3Variant::CullList ||
                      var == G3Variant::CullListFog;
    if (par) return g3_par_output(s, d, out, v, n);
    const bool clipper = var == G3Variant::ClipStrip || var == G3Variant::ClipList;
    if (var == G3Variant::ClipList) return false;  // not modelled yet (never seen on the routes so far)
    const F4 r28 = reg(s, 28), r29 = reg(s, 29), r30 = reg(s, 30), r31 = reg(s, 31), off = reg(s, 2);
    const F4 fg = ld(d, kFog);
    const float fs = fg.z;
    const float fnear = fg.w * fs, ffar = 255.0f + fg.w * fs;
    const F4 c1 = ld(d, kClip1), c2 = ld(d, kClip2);
    const F4 cs{c1.y, c2.y, c2.z, 1.0f};  // vf26 of the cull variants, vf25 of the clipper
    const u32 cullz = ldw(d, kFlags, 2) & 0xFFFFu;
    const u32 vi07 = ((cullz + 0x7FE0u) | 0x7FE0u) & 0xFFFFu;

    out.tag[0] = 0x8000u | n;
    if (cull && list) out.tag[0] = (0x8000u + 0x20u) | n;  // 0x311: vi03 = 0x7FE0 + 0x20 + 0x20 ... see doc
    out.tag[1] = ldw(d, kTag, 1);
    out.tag[2] = ldw(d, kTag, 2);
    out.tag[3] = ldw(d, kTag, 3);
    out.v.resize(n);
    scr_buf.resize(n);
    sq_buf.resize(n);
    cc_buf.resize(n);
    clipf_buf.resize(n);
    fogw_buf.resize(n);
    F4* const scr = scr_buf.data();
    F4* const sq = sq_buf.data();
    F4* const cc = cc_buf.data();
    u32* const clipf = clipf_buf.data();
    float* const fogw = fogw_buf.data();
    const auto clip_flags = [&](F4 c) {
        const F4 t{c.x * cs.x, c.y * cs.y, c1.z + cs.z * c.w, c.w * cs.w};
        const float aw = std::fabs(t.w);
        u32 f = 0;
        if (t.x > aw) f |= 1;
        if (t.x < -aw) f |= 2;
        if (t.y > aw) f |= 4;
        if (t.y < -aw) f |= 8;
        if (t.z > aw) f |= 16;
        if (t.z < -aw) f |= 32;
        return f;
    };
    u32 all_out = 0x3F, any_out = 0;
    for (u32 i = 0; i < n; ++i) {
        const VertexIn& x = v[i];
        F4 c;
        c.x = r31.x + r28.x * x.pos.x + r29.x * x.pos.y + r30.x * x.pos.z;
        c.y = r31.y + r28.y * x.pos.x + r29.y * x.pos.y + r30.y * x.pos.z;
        c.z = r31.z + r30.z * x.pos.z;
        c.w = r31.w + r28.w * x.pos.x + r29.w * x.pos.y + r30.w * x.pos.z;
        float q;
        if (clipper) {  // 0x3FF: clip space (X, Y, W, W); fog from W after the cull decision
            cc[i] = F4{c.x, c.y, c.w, c.w};
            clipf[i] = clip_flags(c);
            all_out &= clipf[i];
            any_out |= clipf[i];
            q = 1.0f / c.w;
            fogw[i] = std::min(std::max(c.w * fs - fnear, 0.0f), 255.0f);
            c.z = r31.z;  // vf03.z = vf31.z (the Z scale)
        } else if (fog) {
            const float wf = (r31.w * fs) + (r28.w * fs) * x.pos.x + (r29.w * fs) * x.pos.y + (r30.w * fs) * x.pos.z;
            q = fs / wf;
            fogw[i] = std::min(std::max(wf, fnear), ffar) - fnear;
        } else {
            q = 1.0f / c.w;
        }
        sq[i] = F4{c.x * q, c.y * q, c.z * q, 0};
        scr[i] = F4{off.x + sq[i].x, off.y + sq[i].y, off.z + sq[i].z, 0};
        if (cull) clipf[i] = clip_flags(c);
        G3OutVertex& o = out.v[i];
        o.s = x.uv.x * q;
        o.t = x.uv.y * q;
        o.q = q;
        o.qw = 0;
        for (int j = 0; j < 4; ++j) o.rgba[j] = ftoi(x.col[j], 1.0f);
        o.xyzw[0] = ftoi(scr[i].x, 16.0f);
        o.xyzw[1] = ftoi(scr[i].y, 16.0f);
        o.xyzw[2] = ftoi(scr[i].z, 16.0f);
        o.xyzw[3] = 0;
    }
    if (clipper && (n & 1u)) {
        // The transform loop runs in pairs up to ((4N + 4) & ~7) qwords: with N odd it also transforms and judges the
        // qword quadruple after the last vertex (whatever the buffer holds there, the skin pre-pass does not
        // rewrite it), and that judgement takes part in the all-outside / any-outside decision.
        const F4 p = ld(d, top + 4u * n);
        F4 c;
        c.x = r31.x + r28.x * p.x + r29.x * p.y + r30.x * p.z;
        c.y = r31.y + r28.y * p.x + r29.y * p.y + r30.y * p.z;
        c.w = r31.w + r28.w * p.x + r29.w * p.y + r30.w * p.z;
        const u32 f = clip_flags(c);
        all_out &= f;
        any_out |= f;
    }
    if (clipper) {
        if (all_out) {  // 0x43D: every vertex outside one plane: nothing is kicked
            out.culled_all = true;
            out.v.clear();
            return true;
        }
        if (any_out) {  // 0x464: the clipping path
            out.clipped = true;
            if (!out.clip_in_model || list) return false;
            // Homogeneous clipping of every strip triangle against the planes the VU1 tests (t = (X c1.y, Y c2.y,
            // c1.z + c2.z W) within +-W), attributes interpolated in clip space, the polygon drawn as a fan. Culling:
            // the clipped polygon's screen orientation under the clipper's rule (odd triangles inverted).
            struct HV {
                float x, y, w, u, v, r, g, b, a;
            };
            const auto dist = [&](const HV& h, int pl) {
                const float tx = h.x * cs.x, ty = h.y * cs.y, tz = c1.z + cs.z * h.w;
                switch (pl) {
                case 0: return h.w - tx;
                case 1: return h.w + tx;
                case 2: return h.w - ty;
                case 3: return h.w + ty;
                case 4: return h.w - tz;
                default: return h.w + tz;
                }
            };
            const auto mk = [&](u32 i) {
                const VertexIn& x = v[i];
                return HV{cc[i].x, cc[i].y, cc[i].w, x.uv.x, x.uv.y, x.col.x, x.col.y, x.col.z, x.col.w};
            };
            const auto lerp = [](const HV& p, const HV& q, float t) {
                return HV{p.x + (q.x - p.x) * t, p.y + (q.y - p.y) * t, p.w + (q.w - p.w) * t, p.u + (q.u - p.u) * t,
                          p.v + (q.v - p.v) * t, p.r + (q.r - p.r) * t, p.g + (q.g - p.g) * t, p.b + (q.b - p.b) * t,
                          p.a + (q.a - p.a) * t};
            };
            const auto emit_vertex = [&](const HV& h) {
                G3OutVertex o{};
                const float q = 1.0f / h.w;
                o.s = h.u * q;
                o.t = h.v * q;
                o.q = q;
                const float col[4] = {h.r, h.g, h.b, h.a};
                for (int j = 0; j < 4; ++j) o.rgba[j] = ftoi(col[j], 1.0f);
                o.xyzw[0] = ftoi(off.x + h.x * q, 16.0f);
                o.xyzw[1] = ftoi(off.y + h.y * q, 16.0f);
                o.xyzw[2] = ftoi(off.z + r31.z * q, 16.0f);
                o.xyzw[3] = ftoi(std::min(std::max(h.w * fs - fnear, 0.0f), 255.0f), 16.0f);
                out.v.push_back(o);
                return static_cast<u16>(out.v.size() - 1);
            };
            for (u32 i = 0; i < n; ++i) out.v[i].xyzw[3] = ftoi(fogw[i], 16.0f);
            HV poly[2][12];
            for (u32 k = 2; k < n; ++k) {
                const u32 a = k - 2, b = k - 1, c = k;
                if (clipf[a] & clipf[b] & clipf[c]) continue;
                u16 ids[12];
                int m = 0;
                if ((clipf[a] | clipf[b] | clipf[c]) == 0) {
                    ids[0] = static_cast<u16>(a);
                    ids[1] = static_cast<u16>(b);
                    ids[2] = static_cast<u16>(c);
                    m = 3;
                } else {
                    int cur = 0, cnt = 3;
                    poly[0][0] = mk(a);
                    poly[0][1] = mk(b);
                    poly[0][2] = mk(c);
                    for (int pl = 0; pl < 6 && cnt >= 3; ++pl) {
                        int o = 0;
                        for (int e = 0; e < cnt; ++e) {
                            const HV& p = poly[cur][e];
                            const HV& q = poly[cur][(e + 1) % cnt];
                            const float dp = dist(p, pl), dq = dist(q, pl);
                            if (dp >= 0.0f && o < 11) poly[cur ^ 1][o++] = p;
                            if ((dp >= 0.0f) != (dq >= 0.0f) && o < 11) poly[cur ^ 1][o++] = lerp(p, q, dp / (dp - dq));
                        }
                        cur ^= 1;
                        cnt = o;
                    }
                    if (cnt < 3) continue;
                    for (int e = 0; e < cnt; ++e) ids[e] = emit_vertex(poly[cur][e]);
                    m = cnt;
                }
                // orientation of the (clipped) polygon on screen, the clipper's cull rule
                double area2 = 0;
                for (int e = 0; e < m; ++e) {
                    const G3OutVertex& p = out.v[ids[e]];
                    const G3OutVertex& q = out.v[ids[(e + 1) % m]];
                    area2 += double(p.xyzw[0]) * q.xyzw[1] - double(q.xyzw[0]) * p.xyzw[1];
                }
                const u32 sflag = area2 > 0.0 ? 0x20u : 0u;
                const u32 flip = (k & 1u) ? 0x8000u : 0u;
                if ((vi07 + sflag + flip) & 0x8000u) continue;
                for (int e = 1; e + 1 < m; ++e) {
                    out.tris.push_back(ids[0]);
                    out.tris.push_back(ids[e]);
                    out.tris.push_back(ids[e + 1]);
                }
            }
            out.explicit_tris = true;
            return true;
        }
    }
    // ADC per kicking vertex. Strips: every vertex from the third on judges the triangle it closes; lists: every
    // third. The sign is the S flag of the cross product (z lane; -0 counts), with the operand order of the code.
    const auto cz = [](F4 a, F4 b) { return a.x * b.y - b.x * a.y; };
    const auto dot3s = [](F4 a, F4 b) { return (a.z + a.x) + b.z * a.y; };  // addax.z + maddy.z with b = (1,1,1)
    const auto cross = [](F4 a, F4 b) {  // OPMULA a,b + OPMSUB b,a (xyz)
        return F4{a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y, 0};
    };
    const F4* const sv = (fog && !clipper) ? sq : scr;
    for (u32 i = 0; i < n; ++i) {
        bool judged = false, neg = false;
        if (i >= 2) {
            if (clipper) {
                const F4 one{1, 1, 1, 1};
                F4 t = (i & 1u) == 0 ? cross(cc[i], cc[i - 1]) * cc[i - 2] : cross(cc[i - 1], cc[i - 2]) * cc[i];
                neg = std::signbit(dot3s(t, one));
                if (out.want_dbg) out.dbg.push_back(dot3s(t, one));
                judged = true;
            } else if (list) {
                if (i % 3 == 2) {
                    neg = std::signbit(cz(sv[i] - sv[i - 2], sv[i - 1] - sv[i - 2]));
                    judged = true;
                }
            } else {
                neg = (i & 1u) == 0 ? std::signbit(cz(sv[i - 1] - sv[i - 2], sv[i - 1] - sv[i]))
                                    : std::signbit(cz(sv[i] - sv[i - 1], sv[i - 2] - sv[i - 1]));
                judged = true;
            }
        }
        const u32 sflag = neg ? 0x20u : 0u;
        const bool outside = cull && judged && (clipf[i] | clipf[i - 1] | clipf[i - 2]) != 0;
        G3OutVertex& o = out.v[i];
        if (clipper) {
            // 0x430-0x431 (even) / 0x437-0x439 (odd: one more + 0x8000, the strip's alternating winding)
            const u32 flip = (i & 1u) ? 0x8000u : 0u;
            const bool adc = judged && (((vi07 + sflag + flip) & 0x8000u) != 0);
            o.xyzw[3] = ftoi(fogw[i] + (adc ? 2048.0f : 0.0f), 16.0f);
        } else if (fog) {
            bool adc = false;
            if (judged) adc = (cull ? (outside ? 1u : 0u) + sflag : sflag) != cullz;
            o.xyzw[3] = ftoi(fogw[i] - 0.0f + (adc ? 2048.5f : 0.0f), 16.0f);
        } else if (judged) {
            u32 w = (vi07 + sflag) & 0xFFFFu;
            if (cull) w |= outside ? 0x8000u : 0x7FFFu;
            o.xyzw[3] = static_cast<s32>(static_cast<s16>(static_cast<u16>(w)));
        }
    }
    return true;
}

bool g3_gpu_record(G3Prog p, const vu1::VU1State& s, std::vector<u32>& rec, u32& slots_out, u32& prim_out, u32& palq_out) {
    const u8* d = s.data;
    u32 flags_word, cullz, tagw[4];
    std::memcpy(&flags_word, d + 0x3FFu * 16u, 4);
    std::memcpy(&cullz, d + 0x3FFu * 16u + 8, 4);
    std::memcpy(tagw, d + 0x3FAu * 16u, 16);
    const G3Variant var = g3_variant(p, flags_word & 0xFFFFu);
    if (var == G3Variant::ClipStrip || var == G3Variant::ClipList || var == G3Variant::Count) return false;
    const u32 tag_hi = tagw[1];
    const bool pre = (tag_hi >> 14) & 1u;
    const u32 prim = (tag_hi >> 15) & 0x7FFu;
    const u32 flg = (tag_hi >> 26) & 3u, nreg = (tag_hi >> 28) & 0xFu;
    const u64 regs = static_cast<u64>(tagw[2]) | (static_cast<u64>(tagw[3]) << 32);
    const u32 r0 = regs & 0xF, r1 = (regs >> 4) & 0xF, r2 = (regs >> 8) & 0xF;
    if (flg != 0 || nreg != 3 || !pre || r0 != 0x2 || r1 != 0x1 || (r2 != 0x4 && r2 != 0x5)) return false;
    const u32 type = prim & 7u;
    if (type != 3 && type != 4) return false;
    const u32 n = s.itop & 1023u, top = s.top & 1023u;
    if (n < 3 || n > 256) return false;
    const bool list = g3_list(var);
    const u32 slots = list ? n / 3u : n - 2u;
    const bool skin = p != G3Prog::Generic;
    const u32 stride = skin ? 5u : 4u;
    float kw;
    std::memcpy(&kw, d + 0x3FCu * 16u + 12, 4);
    const u32 vq = n * stride + (kw != 0.0f ? 2u * n : 0u);
    u32 palq = 0;
    if (skin) {  // the bone palette rows the weights index (indices are x4 qword offsets from 0x2B8)
        u32 maxi = 0;
        for (u32 i = 0; i < n; ++i) {
            u32 idx[4];
            std::memcpy(idx, d + ((top + i * stride + 4u) & 1023u) * 16u, 16);
            for (u32 j = 0; j < 4; ++j) {
                const u32 a = (0x2BBu + (idx[j] & 0xFFFFu)) & 1023u;  // the last row read, as VU1 addresses wrap
                if (a < 0x2BBu) return false;                          // wraps below the palette: CPU path
                maxi = std::max(maxi, a - 0x2BBu);
            }
        }
        palq = std::min<u32>(maxi + 4u, 1024u - 0x2B8u);
    }
    const u32 hdr_q = 3u + 5u + 48u;
    rec.resize(static_cast<std::size_t>(hdr_q + vq) * 4u);
    u32* h = rec.data();
    std::memset(h, 0, 12 * 4);
    const bool cull = var == G3Variant::CullStrip || var == G3Variant::CullStripFog || var == G3Variant::CullList ||
                      var == G3Variant::CullListFog;
    h[0] = n;
    h[1] = p == G3Prog::Generic ? 1u : p == G3Prog::Skin ? 2u : 3u;
    h[2] = (r2 == 0x4 ? 1u : 0u) | (((prim >> 3) & 1u) == 0 ? 2u : 0u) | (list ? 4u : 0u) | (g3_fog(var) ? 8u : 0u) |
           (cull ? 16u : 0u);
    h[3] = ((cullz & 0xFFFFu) + 0x7FE0u | 0x7FE0u) & 0xFFFFu;
    h[8] = cullz & 0xFFFFu;
    h[9] = hdr_q;
    h[10] = hdr_q + vq;  // the palette right after the record; GsOpRecorder::on_native_gpu_batch may point it at an equal one
    std::memcpy(h + 12, s.vf[28], 4 * 16);
    std::memcpy(h + 28, s.vf[2], 16);
    std::memcpy(h + 32, d + 0x3D0u * 16u, 48 * 16);
    u32* vb = h + hdr_q * 4u;
    for (u32 q = 0; q < vq; ++q) std::memcpy(vb + q * 4u, d + ((top + q) & 1023u) * 16u, 16);
    palq_out = palq;  // rows from VU1 0x2B8 (the caller copies them)
    slots_out = slots;
    prim_out = prim;
    return true;
}

} // namespace p3fes::native
