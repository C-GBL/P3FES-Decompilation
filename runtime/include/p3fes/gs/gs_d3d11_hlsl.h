// HLSL of the D3D11 GS back end (runtime/gs/d3d11, p3fes_gsreplay; docs/ANALYSIS/25_d3d11_gs_backend.md): the GS pixel
// pipeline of runtime/gs/gs_raster_ref.cpp (`Raster::pixel`, `sample`, `fetch`) on a GPU, with GS local memory as one
// 4 MiB raw UAV ("VRAM as a buffer"): frame/Z/texture/CLUT addressing uses the core's own swizzle tables (uploaded
// from gs::swizzle_tables()), blending/tests/format conversion are integer code, so the only differences to the
// software rasteriser are the rasterizer's attribute interpolation (float; none with EXACT) and the order of
// overlapping pixels when ROVs are unavailable (the host then splits draws so no two primitives of one draw overlap).
// Plus the CRTC merge (gs::compose) as a compute shader and the window present pass. Layouts: p3fes/gs/gs_ops.h.
#pragma once

namespace p3fes::gs::hlsl {

// Common part: resources and the memory model. `VRAM_T` is chosen per entry point.
inline constexpr const char kHlslCommon[] = R"HLSL(
ByteAddressBuffer swz : register(t0);   // swizzle tables, u32 entries (offsets below)
#define SWZ_CT32  0
#define SWZ_Z32   2048
#define SWZ_CT16  4096
#define SWZ_CT16S 8192
#define SWZ_Z16   12288
#define SWZ_Z16S  16384
#define SWZ_T8    20480
#define SWZ_T4    28672

VRAM_T vram : register(u0);

uint tab(uint i) { return swz.Load(i * 4); }
uint page_base(uint bp, uint page) { return (bp + page * 32u) * 256u; }
uint addr32(uint bp, uint bw, uint x, uint y, uint t) {
    x &= 2047u; y &= 2047u;
    uint page = (y >> 5) * bw + (x >> 6);
    return (page_base(bp, page) + tab(t + (y & 31u) * 64u + (x & 63u))) & 0x3FFFFFu;
}
uint addr16(uint bp, uint bw, uint x, uint y, uint t) {
    x &= 2047u; y &= 2047u;
    uint page = (y >> 6) * bw + (x >> 6);
    return (page_base(bp, page) + tab(t + (y & 63u) * 64u + (x & 63u))) & 0x3FFFFFu;
}
uint addr8(uint bp, uint bw, uint x, uint y) {
    x &= 2047u; y &= 2047u;
    uint page = (y >> 6) * (bw >> 1) + (x >> 7);
    return (page_base(bp, page) + tab(SWZ_T8 + (y & 63u) * 128u + (x & 127u))) & 0x3FFFFFu;
}
uint addr4(uint bp, uint bw, uint x, uint y) {  // nibble address
    x &= 2047u; y &= 2047u;
    uint page = (y >> 7) * (bw >> 1) + (x >> 7);
    return (page_base(bp, page) * 2u + tab(SWZ_T4 + (y & 127u) * 128u + (x & 127u))) & 0x7FFFFFu;
}
uint ldw(uint a) { return vram.Load(a & 0x3FFFFCu); }
uint tab16(uint psm) { return psm == 0x0Au ? SWZ_CT16S : psm == 0x32u ? SWZ_Z16 : psm == 0x3Au ? SWZ_Z16S : SWZ_CT16; }

// GsMemory::read
uint read_px(uint psm, uint bp, uint bw, uint x, uint y) {
    uint a;
    switch (psm) {
    case 0x01u: return ldw(addr32(bp, bw, x, y, SWZ_CT32)) & 0xFFFFFFu;
    case 0x30u: return ldw(addr32(bp, bw, x, y, SWZ_Z32));
    case 0x31u: return ldw(addr32(bp, bw, x, y, SWZ_Z32)) & 0xFFFFFFu;
    case 0x02u: case 0x0Au: case 0x32u: case 0x3Au:
        a = addr16(bp, bw, x, y, tab16(psm));
        return (ldw(a) >> ((a & 2u) * 8u)) & 0xFFFFu;
    case 0x13u: a = addr8(bp, bw, x, y); return (ldw(a) >> ((a & 3u) * 8u)) & 0xFFu;
    case 0x14u: a = addr4(bp, bw, x, y); return (ldw(a >> 1) >> (((a >> 1) & 3u) * 8u + (a & 1u) * 4u)) & 0xFu;
    case 0x1Bu: return ldw(addr32(bp, bw, x, y, SWZ_CT32)) >> 24;
    case 0x24u: return (ldw(addr32(bp, bw, x, y, SWZ_CT32)) >> 24) & 0xFu;
    case 0x2Cu: return ldw(addr32(bp, bw, x, y, SWZ_CT32)) >> 28;
    default: return ldw(addr32(bp, bw, x, y, SWZ_CT32));
    }
}
)HLSL";

// The draw pipeline (vertex + pixel shader).
inline constexpr const char kHlslDraw[] = R"HLSL(
ByteAddressBuffer clut : register(t1);  // 512 x u32 (low 16 bits used), the GS CLUT buffer
ByteAddressBuffer clut_tab : register(t3);  // CLUT versions resolved on the CPU: 512 x u32 each, bit 31 = inherit
static uint g_clutv = 0xFFFFFFFFu;          // the draw state's version (ps_main)
uint clut_slot(uint slot) {
    if (g_clutv != 0xFFFFFFFFu) {
        uint e = clut_tab.Load((g_clutv * 512u + slot) * 4u);
        if (e < 0x80000000u) return e;
    }
    return clut.Load(slot * 4u) & 0xFFFFu;
}

// The draw states of a D3D draw call (GpuDrawCB, 512 bytes each): the executor binds up to 128 consecutive blocks of
// the list and the primitive's vertex names its block (merged draws, gs_ops.h GpuOp::merge). The state's fields are
// read through the macros below as dcb[g_ci].m_<field>, with g_ci set at the start of ps_main.
struct DrawCB {
    uint m_tme, m_fge, m_abe, m_fst;
    uint m_iip, m_sprite, m_fbp, m_fbw;
    uint m_fpsm, m_fbmsk, m_zbp, m_zpsm;
    uint m_zmsk, m_ate, m_atst, m_aref;
    uint m_afail, m_date, m_datm, m_ztst;
    uint m_ba, m_bb, m_bc, m_bd;
    uint m_fix, m_pabe, m_fba, m_colclamp;
    uint m_dthe, m_scanmsk, m_fogcol, m_zmax;
    int4 m_dimx[4];
    uint m_tpsm, m_tcc, m_tfx, m_cpsm;
    uint m_csa, m_wms, m_wmt, m_minu;
    uint m_maxu, m_minv, m_maxv, m_ta0;
    uint m_ta1, m_aem, m_mmag_linear, m_mmin;
    uint m_mxl, m_lcm, m_lshift, m_prim_base;
    int m_k16, m_pad1, m_pad2, m_pad3;
    uint4 m_lv[7];   // tbp, tbw, tw, th per level
    int4 m_sc;       // scissor left, top, right, bottom (exclusive)
    uint m_clutv, m_pad4, m_pad5, m_pad6;
    uint4 m_tail[5];
};
cbuffer Draw : register(b0) { DrawCB dcb[128]; };
cbuffer Group : register(b1) { uint g_cb_base, g_prim_base, g_pad0, g_pad1; };
static uint g_ci = 0;
#define tme dcb[g_ci].m_tme
#define fge dcb[g_ci].m_fge
#define abe dcb[g_ci].m_abe
#define fst dcb[g_ci].m_fst
#define iip dcb[g_ci].m_iip
#define sprite dcb[g_ci].m_sprite
#define fbp dcb[g_ci].m_fbp
#define fbw dcb[g_ci].m_fbw
#define fpsm dcb[g_ci].m_fpsm
#define fbmsk dcb[g_ci].m_fbmsk
#define zbp dcb[g_ci].m_zbp
#define zpsm dcb[g_ci].m_zpsm
#define zmsk dcb[g_ci].m_zmsk
#define ate dcb[g_ci].m_ate
#define atst dcb[g_ci].m_atst
#define aref dcb[g_ci].m_aref
#define afail dcb[g_ci].m_afail
#define date_ dcb[g_ci].m_date
#define datm dcb[g_ci].m_datm
#define ztst dcb[g_ci].m_ztst
#define ba dcb[g_ci].m_ba
#define bb dcb[g_ci].m_bb
#define bc dcb[g_ci].m_bc
#define bd dcb[g_ci].m_bd
#define fix dcb[g_ci].m_fix
#define pabe dcb[g_ci].m_pabe
#define fba dcb[g_ci].m_fba
#define colclamp dcb[g_ci].m_colclamp
#define dthe dcb[g_ci].m_dthe
#define scanmsk dcb[g_ci].m_scanmsk
#define fogcol dcb[g_ci].m_fogcol
#define zmax dcb[g_ci].m_zmax
#define dimx dcb[g_ci].m_dimx
#define tpsm dcb[g_ci].m_tpsm
#define tcc dcb[g_ci].m_tcc
#define tfx dcb[g_ci].m_tfx
#define cpsm dcb[g_ci].m_cpsm
#define csa dcb[g_ci].m_csa
#define wms dcb[g_ci].m_wms
#define wmt dcb[g_ci].m_wmt
#define minu dcb[g_ci].m_minu
#define maxu dcb[g_ci].m_maxu
#define minv dcb[g_ci].m_minv
#define maxv dcb[g_ci].m_maxv
#define ta0 dcb[g_ci].m_ta0
#define ta1 dcb[g_ci].m_ta1
#define aem dcb[g_ci].m_aem
#define mmag_linear dcb[g_ci].m_mmag_linear
#define mmin dcb[g_ci].m_mmin
#define mxl dcb[g_ci].m_mxl
#define lcm dcb[g_ci].m_lcm
#define lshift dcb[g_ci].m_lshift
#define k16 dcb[g_ci].m_k16
#define lv dcb[g_ci].m_lv

struct VSIn {
    int2 xy : POS;
    float z : ZV;
    uint4 col : COL;    // R8G8B8A8_UINT
    float3 stq : STQ;
    uint2 uv : UV;      // R16G16_UINT
    uint f : FOG;
    uint cbi : CBI;     // the primitive's draw state (OpList::cbs index)
};
struct PSIn {
    float4 pos : SV_Position;
    noperspective float4 col : COL;
    nointerpolation float4 colf : COLF;
    noperspective float z : ZV;
    nointerpolation float zf : ZF;
    noperspective float3 stq : STQ;
    noperspective float2 uv : UV;
    noperspective float f : FOG;
    nointerpolation float ff : FOGF;
    nointerpolation uint cbi : CBI;
};

// Viewport (-4096, -4096) 8192 x 8192: NDC = viewport position / 4096. A GS window coordinate X (12.4) samples
// pixel px at X = 16 px; D3D samples at px + 0.5, hence the half-pixel shift. Both are exact in float.
PSIn vs_main(VSIn v) {
    PSIn o;
    float2 p = float2(v.xy) / 16.0 + 0.5;
    o.pos = float4(p.x / 4096.0, -p.y / 4096.0, 0.5, 1.0);
    float4 col = float4(v.col);  // exact: integers below 2^24
    o.col = col; o.colf = col;
    o.z = v.z; o.zf = v.z;
    o.stq = v.stq; o.uv = float2(v.uv);
    o.f = float(v.f); o.ff = o.f;
    o.cbi = v.cbi;
    return o;
}

int clamp255(int v) { return clamp(v, 0, 255); }

uint expand16(uint c) {
    uint r = (c & 0x1Fu) << 3, g = ((c >> 5) & 0x1Fu) << 3, b = ((c >> 10) & 0x1Fu) << 3;
    uint a = (c & 0x8000u) ? ta1 : ((aem != 0u && (c & 0x7FFFu) == 0u) ? 0u : ta0);
    return r | (g << 8) | (b << 16) | (a << 24);
}
uint clut_entry(uint index, bool eight) {
    if (cpsm == 0u || cpsm == 1u) {
        uint slot = eight ? (index & 255u) : (((csa & 15u) * 16u + index) & 255u);
        return clut_slot(slot) | (clut_slot(slot + 256u) << 16);
    }
    uint slot = eight ? (index & 255u) : ((csa * 16u + index) & 511u);
    return expand16(clut_slot(slot));
}
int wrap_coord(int v, uint size, uint mode, uint lo, uint hi) {
    if (mode == 0u) return v & int(size - 1u);
    if (mode == 1u) return (int(size) - 1 < v) ? int(size) - 1 : (v < 0 ? 0 : v);
    if (mode == 2u) return (int(hi) < v) ? int(hi) : (v < int(lo) ? int(lo) : v);
    return int((uint(v) & lo) | hi);
}
uint fetch(uint level, int x, int y) {
    uint4 L = lv[level];
    x = wrap_coord(x, 1u << L.z, wms, minu >> level, maxu >> level);
    y = wrap_coord(y, 1u << L.w, wmt, minv >> level, maxv >> level);
    uint raw = read_px(tpsm, L.x, L.y, uint(x), uint(y));
    switch (tpsm) {
    case 0x00u: case 0x30u: return raw;
    case 0x01u: case 0x31u: return (raw & 0xFFFFFFu) | (((aem != 0u && (raw & 0xFFFFFFu) == 0u) ? 0u : ta0) << 24);
    case 0x02u: case 0x0Au: case 0x32u: case 0x3Au: return expand16(raw);
    case 0x13u: case 0x1Bu: return clut_entry(raw, true);
    case 0x14u: case 0x24u: case 0x2Cu: return clut_entry(raw, false);
    default: return raw;
    }
}
uint bilinear(uint level, int u16, int v16) {
    int uu = u16 - 8, vv = v16 - 8;
    int x0 = uu >> 4, y0 = vv >> 4;
    uint fx = uint(uu & 15), fy = uint(vv & 15);
    uint c00 = fetch(level, x0, y0), c10 = fetch(level, x0 + 1, y0);
    uint c01 = fetch(level, x0, y0 + 1), c11 = fetch(level, x0 + 1, y0 + 1);
    uint w00 = (16u - fx) * (16u - fy), w10 = fx * (16u - fy), w01 = (16u - fx) * fy, w11 = fx * fy;
    uint o = 0u;
    [unroll] for (uint sh = 0u; sh < 32u; sh += 8u) {
        uint v = (((c00 >> sh) & 0xFFu) * w00 + ((c10 >> sh) & 0xFFu) * w10 + ((c01 >> sh) & 0xFFu) * w01 +
                  ((c11 >> sh) & 0xFFu) * w11) >> 8;
        o |= (v & 0xFFu) << sh;
    }
    return o;
}
uint sample_level(int u16, int v16, bool use_lin, uint level) {
    int u = u16 >> level, v = v16 >> level;
    return use_lin ? bilinear(level, u, v) : fetch(level, u >> 4, v >> 4);
}
uint lerp_rgba(uint a, uint b, uint w256) {
    uint o = 0u;
    [unroll] for (uint sh = 0u; sh < 32u; sh += 8u) {
        uint x = (a >> sh) & 0xFFu, y = (b >> sh) & 0xFFu;
        o |= (((x * (256u - w256) + y * w256) >> 8) & 0xFFu) << sh;
    }
    return o;
}
uint sample_tex(int u16, int v16, float q) {
    float lod;
    if (lcm != 0u) lod = float(k16) / 16.0;
    else {
        float aq = abs(q);
        lod = (aq > 0.0 ? log2(1.0 / aq) : 0.0) * float(1u << lshift) + float(k16) / 16.0;
    }
    if (lod <= 0.0) return sample_level(u16, v16, mmag_linear != 0u, 0u);
    uint mx = min(mxl, 6u);
    if (mmin == 1u) return sample_level(u16, v16, true, 0u);
    if (mmin == 2u || mmin == 4u) {
        uint level = min(uint(floor(lod + 0.5)), mx);
        return sample_level(u16, v16, mmin == 4u, level);
    }
    if (mmin == 3u || mmin == 5u) {
        uint lo = min(uint(floor(lod)), mx), hi = min(lo + 1u, mx);
        uint w = uint((lod - floor(lod)) * 256.0);
        bool lin = mmin == 5u;
        uint a = sample_level(u16, v16, lin, lo);
        if (hi == lo) return a;
        return lerp_rgba(a, sample_level(u16, v16, lin, hi), min(w, 256u));
    }
    return sample_level(u16, v16, false, 0u);
}

bool is16(uint p) { return p == 0x02u || p == 0x0Au || p == 0x32u || p == 0x3Au; }
bool is24(uint p) { return p == 0x01u || p == 0x31u; }

uint read_frame(uint x, uint y) {
    uint raw = read_px(fpsm, fbp, fbw, x, y);
    if (is16(fpsm))
        return ((raw & 0x1Fu) << 3) | (((raw >> 5) & 0x1Fu) << 11) | (((raw >> 10) & 0x1Fu) << 19) | ((raw & 0x8000u) ? 0x80000000u : 0u);
    if (is24(fpsm)) return (raw & 0xFFFFFFu) | 0x80000000u;
    return raw;
}

// A masked store into one 32-bit word. Sub-word stores use two atomics so neighbouring pixels that share the word
// (16/8/4-bit formats) never lose each other's bits.
void store_masked(uint a, uint keep, uint v) {
    a &= 0x3FFFFCu;
    if (keep == 0u) { vram.Store(a, v); return; }
    uint o;
    vram.InterlockedAnd(a, keep, o);
    vram.InterlockedOr(a, v & ~keep, o);
}
// GsMemory::write
void write_px(uint psm, uint bp, uint bw, uint x, uint y, uint v) {
    uint a, sh;
    switch (psm) {
    case 0x01u: store_masked(addr32(bp, bw, x, y, SWZ_CT32), 0xFF000000u, v); break;
    case 0x30u: store_masked(addr32(bp, bw, x, y, SWZ_Z32), 0u, v); break;
    case 0x31u: store_masked(addr32(bp, bw, x, y, SWZ_Z32), 0xFF000000u, v); break;
    case 0x02u: case 0x0Au: case 0x32u: case 0x3Au:
        a = addr16(bp, bw, x, y, tab16(psm)); sh = (a & 2u) * 8u;
        store_masked(a, ~(0xFFFFu << sh), (v & 0xFFFFu) << sh); break;
    case 0x13u: a = addr8(bp, bw, x, y); sh = (a & 3u) * 8u; store_masked(a, ~(0xFFu << sh), (v & 0xFFu) << sh); break;
    case 0x14u: a = addr4(bp, bw, x, y); sh = ((a >> 1) & 3u) * 8u + (a & 1u) * 4u;
        store_masked(a >> 1, ~(0xFu << sh), (v & 0xFu) << sh); break;
    case 0x1Bu: store_masked(addr32(bp, bw, x, y, SWZ_CT32), 0x00FFFFFFu, v << 24); break;
    case 0x24u: store_masked(addr32(bp, bw, x, y, SWZ_CT32), 0xF0FFFFFFu, (v & 0xFu) << 24); break;
    case 0x2Cu: store_masked(addr32(bp, bw, x, y, SWZ_CT32), 0x0FFFFFFFu, (v & 0xFu) << 28); break;
    default: store_masked(addr32(bp, bw, x, y, SWZ_CT32), 0u, v); break;
    }
}
)HLSL";

inline constexpr const char kHlslPixel[] = R"HLSL(
#define EPS (1.0 / 256.0)

// Per-pixel inputs of the GS pipeline (gs_raster_ref.cpp PixelIn).
struct PixIn {
    int4 c;        // r g b a
    uint z;        // already clamped to zmax
    int f;
    int u16, v16;  // FST: 1/16 texel
    float s, t, q; // STQ
};

#ifdef EXACT
// Exact mode: the primitive's GS vertices come from a structured buffer (one record per D3D triangle) and the
// attributes are evaluated as gs_raster_ref.cpp does -- integer plane equations with floor division (in doubles,
// exact below 2^53), Z in double with the reciprocal area, STQ in float from the same double weights, and the
// float division s/q done in double and rounded (equal to an IEEE float division). Needs doubles with the
// extended instructions (ddiv, dtoi, dtof).
struct PrimRec {
    int4 xy01;   // triangle: X0 Y0 X1 Y1 (original vertex order); sprite: x0 y0 x1 y1 after the min/max swap
    int4 xy2k;   // X2 Y2 kind (0 triangle, 1 sprite) pad
    uint4 rgba;  // rgba8 per vertex (sprite: [1] = v1)
    uint4 zf;    // Z0 Z1 Z2, fog f0 | f1 << 8 | f2 << 16
    uint4 uv;    // u | v << 16 per vertex (sprite: [0] = u0 v0, [1] = u1 v1)
    float4 s, t, q;
};
ByteAddressBuffer prims_raw : register(t2);  // GpuPrimRec[], 128 bytes each
PrimRec load_prim(uint i) {
    uint a = i * 128u;
    PrimRec p;
    p.xy01 = asint(prims_raw.Load4(a));
    p.xy2k = asint(prims_raw.Load4(a + 16u));
    p.rgba = prims_raw.Load4(a + 32u);
    p.zf = prims_raw.Load4(a + 48u);
    p.uv = prims_raw.Load4(a + 64u);
    p.s = asfloat(prims_raw.Load4(a + 80u));
    p.t = asfloat(prims_raw.Load4(a + 96u));
    p.q = asfloat(prims_raw.Load4(a + 112u));
    return p;
}

int4 unpack8(uint v) { return int4(int(v & 0xFFu), int((v >> 8) & 0xFFu), int((v >> 16) & 0xFFu), int(v >> 24)); }
// floor(n / d) for d > 0 (both exact integers in doubles)
int floor_div_d(double n, double d) {
    double qd = n / d;
    int q = int(qd);
    if (double(q) * d > n) q -= 1;
    return q;
}
int floor_div_i(int n, int d) {  // d > 0
    if (n >= 0) return int(uint(n) / uint(d));
    return -int((uint(-n) + uint(d) - 1u) / uint(d));
}
float fdiv_ieee(float a, float b) { return float(double(a) / double(b)); }

PixIn exact_inputs(PrimRec p, uint px, uint py) {
    PixIn o;
    o.u16 = 0; o.v16 = 0; o.s = 0.0; o.t = 0.0; o.q = 1.0; o.f = 255;
    if (p.xy2k.z == 1) {
        // Sprite (Raster::sprite).
        int x0 = p.xy01.x, y0 = p.xy01.y, x1 = p.xy01.z, y1 = p.xy01.w;
        int dx = x1 - x0, dy = y1 - y0;
        int ox = int(px) * 16 - x0, oy = int(py) * 16 - y0;
        int u0 = int(p.uv.x & 0xFFFFu), v0 = int(p.uv.x >> 16), u1 = int(p.uv.y & 0xFFFFu), v1 = int(p.uv.y >> 16);
        o.c = unpack8(p.rgba.y);
        o.z = min(p.zf.y, zmax);
        o.f = int((p.zf.w >> 8) & 0xFFu);
        o.v16 = dy != 0 ? v0 + floor_div_i(oy * (v1 - v0), dy) : v0;
        o.u16 = dx != 0 ? u0 + floor_div_i(ox * (u1 - u0), dx) : u0;
        precise float ry = dy != 0 ? float(double(oy) / double(dy)) : 0.0;
        precise float rx = dx != 0 ? float(double(ox) / double(dx)) : 0.0;
        precise float tt = p.t.x + (p.t.y - p.t.x) * ry;
        precise float ss = p.s.x + (p.s.y - p.s.x) * rx;
        precise float qq = p.q.x + (p.q.y - p.q.x) * rx;
        o.t = dy != 0 ? tt : p.t.x;
        o.s = dx != 0 ? ss : p.s.x;
        o.q = dx != 0 ? qq : p.q.y;
        return o;
    }
    // Triangle (Raster::triangle): make the area positive by swapping vertices 1 and 2.
    double X0 = p.xy01.x, Y0 = p.xy01.y, X1 = p.xy01.z, Y1 = p.xy01.w, X2 = p.xy2k.x, Y2 = p.xy2k.y;
    uint i1 = 1u, i2 = 2u;
    double area = (X1 - X0) * (Y2 - Y0) - (X2 - X0) * (Y1 - Y0);
    if (area < 0.0) {
        double tx = X1; X1 = X2; X2 = tx;
        double ty = Y1; Y1 = Y2; Y2 = ty;
        i1 = 2u; i2 = 1u;
        area = -area;
    }
    double sx = double(px) * 16.0, sy = double(py) * 16.0;
    double w1 = (X0 - X2) * (sy - Y2) - (Y0 - Y2) * (sx - X2);
    double w2 = (X1 - X0) * (sy - Y0) - (Y1 - Y0) * (sx - X0);
    uint rgb1 = i1 == 1u ? p.rgba.y : p.rgba.z, rgb2 = i1 == 1u ? p.rgba.z : p.rgba.y;
    int4 c0 = unpack8(p.rgba.x), c1 = unpack8(rgb1), c2 = unpack8(rgb2);
    if (iip != 0u) {
        o.c.x = c0.x + floor_div_d(w1 * double(c1.x - c0.x) + w2 * double(c2.x - c0.x), area);
        o.c.y = c0.y + floor_div_d(w1 * double(c1.y - c0.y) + w2 * double(c2.y - c0.y), area);
        o.c.z = c0.z + floor_div_d(w1 * double(c1.z - c0.z) + w2 * double(c2.z - c0.z), area);
        o.c.w = c0.w + floor_div_d(w1 * double(c1.w - c0.w) + w2 * double(c2.w - c0.w), area);
    } else {
        o.c = unpack8(p.rgba.z);  // the kicking vertex (original order)
    }
    int f0 = int(p.zf.w & 0xFFu), fa = int((p.zf.w >> 8) & 0xFFu), fb = int((p.zf.w >> 16) & 0xFFu);
    int f1 = i1 == 1u ? fa : fb, f2 = i1 == 1u ? fb : fa;
    o.f = f0 + floor_div_d(w1 * double(f1 - f0) + w2 * double(f2 - f0), area);
    uint z1 = i1 == 1u ? p.zf.y : p.zf.z, z2 = i1 == 1u ? p.zf.z : p.zf.y;
    precise double inv_area = 1.0 / area;
    precise double dz1 = double(z1) - double(p.zf.x), dz2 = double(z2) - double(p.zf.x);
    precise double zz = double(p.zf.x) + (w1 * dz1 + w2 * dz2) * inv_area;
    o.z = zz <= 0.0 ? 0u : (zz >= 4294967295.0 ? 0xFFFFFFFFu : uint(zz));
    o.z = min(o.z, zmax);
    uint uv1 = i1 == 1u ? p.uv.y : p.uv.z, uv2 = i1 == 1u ? p.uv.z : p.uv.y;
    int u0 = int(p.uv.x & 0xFFFFu), v0 = int(p.uv.x >> 16);
    o.u16 = u0 + floor_div_d(w1 * double(int(uv1 & 0xFFFFu) - u0) + w2 * double(int(uv2 & 0xFFFFu) - u0), area);
    o.v16 = v0 + floor_div_d(w1 * double(int(uv1 >> 16) - v0) + w2 * double(int(uv2 >> 16) - v0), area);
    precise float l1 = float(w1 * inv_area), l2 = float(w2 * inv_area);
    float s1 = i1 == 1u ? p.s.y : p.s.z, s2 = i1 == 1u ? p.s.z : p.s.y;
    float t1 = i1 == 1u ? p.t.y : p.t.z, t2 = i1 == 1u ? p.t.z : p.t.y;
    float q1 = i1 == 1u ? p.q.y : p.q.z, q2 = i1 == 1u ? p.q.z : p.q.y;
    precise float ds1 = s1 - p.s.x, ds2 = s2 - p.s.x, dt1 = t1 - p.t.x, dt2 = t2 - p.t.x, dq1 = q1 - p.q.x, dq2 = q2 - p.q.x;
    precise float ss = p.s.x + ds1 * l1 + ds2 * l2;
    precise float tt = p.t.x + dt1 * l1 + dt2 * l2;
    precise float qq = p.q.x + dq1 * l1 + dq2 * l2;
    o.s = ss; o.t = tt; o.q = qq;
    return o;
}
#endif

PixIn fast_inputs(PSIn i) {
    PixIn o;
    o.c = iip != 0u ? int4(floor(i.col + EPS)) : int4(i.colf);
    float zin = sprite != 0u ? i.zf : floor(i.z + EPS);
    o.z = zin <= 0.0 ? 0u : (zin >= 4294967040.0 ? 0xFFFFFFFFu : uint(zin));
    o.z = min(o.z, zmax);
    o.f = sprite != 0u ? int(i.ff) : int(floor(i.f + EPS));
    o.u16 = int(floor(i.uv.x + EPS));
    o.v16 = int(floor(i.uv.y + EPS));
    o.s = i.stq.x; o.t = i.stq.y; o.q = i.stq.z;
    return o;
}

void ps_main(PSIn i, uint pid : SV_PrimitiveID) {
    uint x = uint(i.pos.x), y = uint(i.pos.y);
    g_ci = i.cbi - g_cb_base;
    int4 sc = dcb[g_ci].m_sc;  // the draw's scissor (a merged draw call's hardware scissor is the union)
    if (int(x) < sc.x || int(y) < sc.y || int(x) >= sc.z || int(y) >= sc.w) return;
    g_clutv = dcb[g_ci].m_clutv;
    if (scanmsk == 2u && (y & 1u) == 0u) return;
    if (scanmsk == 3u && (y & 1u) == 1u) return;
#ifdef EXACT
    PixIn in_ = exact_inputs(load_prim(g_prim_base + pid), x, y);
#else
    PixIn in_ = fast_inputs(i);
#endif
    int r = in_.c.x, g = in_.c.y, b = in_.c.z, a = in_.c.w;
    if (tme != 0u) {
        int u16, v16;
        float q = 1.0;
        if (fst != 0u) {
            u16 = in_.u16;
            v16 = in_.v16;
        } else {
            q = in_.q;
            float qq = q != 0.0 ? q : 1.0e-30;
#ifdef EXACT
            u16 = int(floor(fdiv_ieee(in_.s, qq) * float(1u << lv[0].z) * 16.0));
            v16 = int(floor(fdiv_ieee(in_.t, qq) * float(1u << lv[0].w) * 16.0));
#else
            u16 = int(floor((in_.s / qq) * float(1u << lv[0].z) * 16.0));
            v16 = int(floor((in_.t / qq) * float(1u << lv[0].w) * 16.0));
#endif
        }
        uint tc = sample_tex(u16, v16, q);
        int tr = int(tc & 0xFFu), tg = int((tc >> 8) & 0xFFu), tb = int((tc >> 16) & 0xFFu), ta = int(tc >> 24);
        if (tfx == 0u) {
            r = clamp255((tr * r) >> 7); g = clamp255((tg * g) >> 7); b = clamp255((tb * b) >> 7);
            a = tcc != 0u ? clamp255((ta * a) >> 7) : a;
        } else if (tfx == 1u) {
            r = tr; g = tg; b = tb; a = tcc != 0u ? ta : a;
        } else if (tfx == 2u) {
            r = clamp255(((tr * r) >> 7) + a); g = clamp255(((tg * g) >> 7) + a); b = clamp255(((tb * b) >> 7) + a);
            a = tcc != 0u ? clamp255(ta + a) : a;
        } else {
            r = clamp255(((tr * r) >> 7) + a); g = clamp255(((tg * g) >> 7) + a); b = clamp255(((tb * b) >> 7) + a);
            a = tcc != 0u ? ta : a;
        }
    }
    if (fge != 0u) {
        int f = in_.f;
        int fr = int(fogcol & 0xFFu), fg = int((fogcol >> 8) & 0xFFu), fb = int((fogcol >> 16) & 0xFFu);
        r = (f * r + (255 - f) * fr) >> 8; g = (f * g + (255 - f) * fg) >> 8; b = (f * b + (255 - f) * fb) >> 8;
    }
    bool write_fb = true, write_z = zmsk == 0u, write_alpha = true;
    if (ate != 0u) {
        uint av = uint(a);
        bool apass;
        switch (atst) {
        case 0u: apass = false; break;
        case 1u: apass = true; break;
        case 2u: apass = av < aref; break;
        case 3u: apass = av <= aref; break;
        case 4u: apass = av == aref; break;
        case 5u: apass = av >= aref; break;
        case 6u: apass = av > aref; break;
        default: apass = av != aref; break;
        }
        if (!apass) {
            if (afail == 0u) return;
            if (afail == 1u) write_z = false;
            else if (afail == 2u) write_fb = false;
            else { write_z = false; write_alpha = false; }
        }
    }
    uint dst = 0u;
    bool have_dst = false;
    if (date_ != 0u) {
        dst = read_frame(x, y);
        have_dst = true;
        if (((dst >> 31) & 1u) != datm) return;
    }
    uint z = in_.z;
    if (ztst != 1u) {
        uint old = read_px(zpsm, zbp, fbw, x, y) & zmax;
        bool zpass = ztst == 0u ? false : (ztst == 2u ? z >= old : z > old);
        if (!zpass) return;
    }
    if (write_fb) {
        int3 o = int3(r, g, b);
        if (abe != 0u && (pabe == 0u || (a & 0x80) != 0)) {
            if (!have_dst) dst = read_frame(x, y);
            int3 cs = int3(r, g, b);
            int3 cd = int3(int(dst & 0xFFu), int((dst >> 8) & 0xFFu), int((dst >> 16) & 0xFFu));
            int ad = int(dst >> 24);
            int cc = bc == 0u ? a : (bc == 1u ? ad : int(fix));
            int3 va = ba == 0u ? cs : (ba == 1u ? cd : int3(0, 0, 0));
            int3 vb = bb == 0u ? cs : (bb == 1u ? cd : int3(0, 0, 0));
            int3 vd = bd == 0u ? cs : (bd == 1u ? cd : int3(0, 0, 0));
            o = (((va - vb) * cc) >> 7) + vd;
        }
        bool fb16 = is16(fpsm);
        if (dthe != 0u && fb16) o += dimx[y & 3u][x & 3u];
        o = colclamp != 0u ? clamp(o, 0, 255) : (o & 0xFF);
        uint alpha = uint(a) & 0xFFu;
        if (fba != 0u) alpha |= 0x80u;
        if (fb16) {
            uint value = (uint(o.x) >> 3) | ((uint(o.y) >> 3) << 5) | ((uint(o.z) >> 3) << 10) | ((alpha >> 7) << 15);
            uint m = fbmsk;
            uint m16 = ((m >> 3) & 0x1Fu) | (((m >> 11) & 0x1Fu) << 5) | (((m >> 19) & 0x1Fu) << 10) | (((m >> 31) & 1u) << 15);
            if (!write_alpha) m16 |= 0x8000u;
            if (m16 != 0u) value = (value & ~m16) | (read_px(fpsm, fbp, fbw, x, y) & m16);
            write_px(fpsm, fbp, fbw, x, y, value);
        } else {
            uint value = uint(o.x) | (uint(o.y) << 8) | (uint(o.z) << 16) | (alpha << 24);
            uint m = fbmsk;
            if (!write_alpha || is24(fpsm)) m |= 0xFF000000u;
            if (m != 0u) value = (value & ~m) | (read_px(fpsm, fbp, fbw, x, y) & m);
            write_px(fpsm, fbp, fbw, x, y, value);
        }
    }
    if (write_z) write_px(zpsm, zbp, fbw, x, y, z);
}
)HLSL";

// Compute shaders: CLUT load (GsCore::load_clut) and the transfer scatter (merged word writes).
inline constexpr const char kHlslCompute[] = R"HLSL(
cbuffer ClutCB : register(b0) { uint cbp, cpsm, csm2, csa, eight, cbw, cou, cov; };
RWByteAddressBuffer clut_out : register(u1);
[numthreads(256, 1, 1)]
void cs_clut(uint3 id : SV_DispatchThreadID) {
    uint i = id.x;
    uint entries = eight != 0u ? 256u : 16u;
    if (i >= entries) return;
    uint x, y, bw;
    if (csm2 != 0u) { x = cou * 16u + i; y = cov; bw = cbw; }
    else if (eight != 0u) {
        uint j = (i & ~0x18u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1);
        x = j & 15u; y = j >> 4; bw = 1u;
    } else { x = i & 7u; y = i >> 3; bw = 1u; }
    uint c = read_px(cpsm, cbp, bw, x, y);
    if (cpsm == 0u || cpsm == 1u) {
        uint slot = eight != 0u ? i : (((csa & 15u) * 16u + i) & 255u);
        clut_out.Store(slot * 4u, c & 0xFFFFu);
        clut_out.Store((slot + 256u) * 4u, c >> 16);
    } else {
        uint slot = eight != 0u ? i : ((csa * 16u + i) & 511u);
        clut_out.Store(slot * 4u, c & 0xFFFFu);
    }
}

// The GPU CLUT buffer := CLUT version cbp (GpuOpKind::ClutResolve); inherited slots keep their value.
ByteAddressBuffer clut_tab_cs : register(t4);
[numthreads(512, 1, 1)]
void cs_clut_resolve(uint3 id : SV_DispatchThreadID) {
    uint e = clut_tab_cs.Load((cbp * 512u + id.x) * 4u);
    if (e < 0x80000000u) clut_out.Store(id.x * 4u, e);
}

cbuffer ScatterCB : register(b1) { uint scatter_count, scatter_first, s_pad1, s_pad2; };
ByteAddressBuffer writes_raw : register(t2);  // (word index, mask of bits written, value) triples
[numthreads(64, 1, 1)]
void cs_scatter(uint3 id : SV_DispatchThreadID) {
    if (id.x >= scatter_count) return;
    uint3 w = writes_raw.Load3((scatter_first + id.x) * 12u);
    uint a = w.x * 4u;
    vram.Store(a, (vram.Load(a) & ~w.y) | (w.z & w.y));
}

// Whole pages from full-word transfers (gs_ops.h kPageRecordWords): 2048 threads per page, a word goes up when its
// bit is set.
cbuffer PagesCB : register(b2) { uint pages_count, pages_first, p_pad1, p_pad2; };
ByteAddressBuffer pages_raw : register(t3);
[numthreads(64, 1, 1)]
void cs_pages(uint3 id : SV_DispatchThreadID) {
    uint p = id.x >> 11, i = id.x & 2047u;
    if (p >= pages_count) return;
    uint rec = (pages_first + p) * 2113u * 4u;
    uint page = pages_raw.Load(rec);
    uint b = pages_raw.Load(rec + 4u + (i >> 5) * 4u);
    if (((b >> (i & 31u)) & 1u) == 0u) return;
    vram.Store((page * 2048u + i) * 4u, pages_raw.Load(rec + 260u + i * 4u));
}
)HLSL";

// The CRTC merge (gs::compose in gs_output.cpp, integer for integer) into an RGBA8 texture. Compiled with
// kHlslCommon (VRAM at u0).
inline constexpr const char kHlslCrtc[] = R"HLSL(
cbuffer Crtc : register(b0) {
    uint4 ca[2];   // on, x, y, w      (x, y: placement after MAGH/MAGV)
    uint4 cb[2];   // h, fbp (blocks), fbw, psm
    uint4 cc[2];   // dbx, dby, -, -
    int4 geo;      // out_w, out_h, x0, y0
    uint4 mode;    // interlaced FRAME mode, mmod, slbg, alp
    uint4 mode2;   // bgcolor rgb, -, -, -
};
RWTexture2D<unorm float4> crtc_out : register(u1);

uint display_px(uint c, uint x, uint y) {
    uint psm = cb[c].w, fbp = cb[c].y, fbw = cb[c].z;
    if (psm == 0x01u || psm == 0x12u) return (read_px(0x01u, fbp, fbw, x, y) & 0xFFFFFFu) | 0x80000000u;
    if (psm == 0x02u || psm == 0x0Au) {
        uint v = read_px(psm, fbp, fbw, x, y);
        return ((v & 0x1Fu) << 3) | (((v >> 5) & 0x1Fu) << 11) | (((v >> 10) & 0x1Fu) << 19) | ((v & 0x8000u) ? 0x80000000u : 0u);
    }
    return read_px(0x00u, fbp, fbw, x, y);
}
bool fetch_c(uint c, int ox, int oy, out uint px) {
    px = 0u;
    if (ca[c].x == 0u) return false;
    int lx = ox + geo.z - int(ca[c].y), ly = oy + geo.w - int(ca[c].z);
    if (lx < 0 || ly < 0 || lx >= int(ca[c].w) || ly >= int(cb[c].x)) return false;
    uint row = mode.x != 0u ? uint(ly) / 2u : uint(ly);
    px = display_px(c, cc[c].x + uint(lx), cc[c].y + row);
    return true;
}
[numthreads(8, 8, 1)]
void cs_crtc(uint3 id : SV_DispatchThreadID) {
    if (int(id.x) >= geo.x || int(id.y) >= geo.y) return;
    uint p1, p2;
    bool h1 = fetch_c(0u, int(id.x), int(id.y), p1);
    bool h2 = fetch_c(1u, int(id.x), int(id.y), p2);
    uint under = (mode.z == 0u && h2) ? (p2 & 0xFFFFFFu) : mode2.x;
    uint rgb = under;
    if (h1) {
        uint a = mode.y != 0u ? mode.w : (p1 >> 24);
        rgb = 0u;
        [unroll] for (uint sh = 0u; sh < 24u; sh += 8u) {
            uint c1 = (p1 >> sh) & 0xFFu, c2 = (under >> sh) & 0xFFu;
            uint v = min((c1 * a + c2 * (255u - min(a, 255u)) + 127u) / 255u, 255u);
            rgb |= v << sh;
        }
    }
    crtc_out[id.xy] = float4(float(rgb & 0xFFu), float((rgb >> 8) & 0xFFu), float((rgb >> 16) & 0xFFu), 255.0) / 255.0;
}
)HLSL";

// Window present: the composed frame as one quad into the letterbox rectangle (viewport), point or bilinear.
inline constexpr const char kHlslPresent[] = R"HLSL(
Texture2D<float4> frame_tex : register(t0);
SamplerState frame_smp : register(s0);
struct VSOut { float4 pos : SV_Position; float2 uv : TEXCOORD0; };
VSOut vs_present(uint id : SV_VertexID) {
    VSOut o;
    float2 uv = float2(id & 1, id >> 1);
    o.pos = float4(uv.x * 2.0 - 1.0, 1.0 - uv.y * 2.0, 0.0, 1.0);
    o.uv = uv;
    return o;
}
float4 ps_present(VSOut i) : SV_Target { return float4(frame_tex.Sample(frame_smp, i.uv).rgb, 1.0); }
)HLSL";

} // namespace p3fes::gs::hlsl
