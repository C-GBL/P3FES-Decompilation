// HLSL of the native renderer's GPU vertex stage (docs/ANALYSIS/31_native_renderer.md §7): the semantic model of
// RenderWare's g3 VU1 programs (runtime/native/g3_model.cpp, the reference; same steps, same order) as a compute
// shader. The EE thread copies each batch's input (VU1 data memory: the object block 0x3D0-0x3FF, the vertex block,
// the bone palette) into OpList::nat_in; one thread per output triangle slot computes its three vertices (morph,
// skinning, the light list, the transform, fog), the ADC (culling) decision of the batch's variant, and writes three
// GpuVertex records (gs_ops.h layout, 10 words) into a buffer the native draw ops read as their vertex buffer. A culled
// triangle is written with zero area. The full clipper's batches stay on the CPU model.
//
// Batch record in nat_in (u32 words, qword-aligned; every offset is in qwords relative to the record start):
//   w0 n, w1 prog (1 generic, 2 skin, 3 parallel skin), w2 flags, w3 vi07
//   w4 ofx (12.4), w5 ofy, w6 uv register (u | v << 16), w7 FOG register value (8 bits)
//   w8 cullz (0x3FF.z raw), w9 vertex block offset, w10 palette offset (signed), w11 the draw state (GpuVertex::cbi)
//   q3..q7 vf28, vf29, vf30, vf31, vf02 (after the init); q8..q55 VU1 0x3D0..0x3FF
// flags: 1 XYZF2 (fog from the vertex), 2 flat shading, 4 list, 8 fog variant, 16 guard-band variant
// nat_tab: per batch {first slot, record word offset, slot count, 0}.
#pragma once

namespace p3fes::gs::hlsl {

inline constexpr const char kHlslNative[] = R"HLSL(
ByteAddressBuffer nin : register(t0);
ByteAddressBuffer ntab : register(t1);
RWByteAddressBuffer nout : register(u0);
cbuffer NativeCB : register(b0) { uint nbatches, total_slots, cb_pad0, cb_pad1; };

static uint g_rec;  // record start, in words
float4 ldq(uint q) { return asfloat(nin.Load4((g_rec + q * 4u) * 4u)); }
int4 ldqi(uint q) { return asint(nin.Load4((g_rec + q * 4u) * 4u)); }
uint ldw(uint w) { return nin.Load((g_rec + w) * 4u); }
#define CQ(a) (8u + (a) - 0x3D0u)

float dot3(float4 a, float4 b) { return (a.x * b.x + a.z * b.z) + a.y * b.y; }

struct V {
    float3 scr;   // screen x, y (pixels), z (as the VU computes it, before FTOI4)
    float4 col;
    float2 st;
    float q;
    float fog;
    uint clipf;
};

uint clip_flags(float4 t, float lim) {
    uint f = 0u;
    if (t.x > lim) f |= 1u;
    if (t.x < -lim) f |= 2u;
    if (t.y > lim) f |= 4u;
    if (t.y < -lim) f |= 8u;
    if (t.z > lim) f |= 16u;
    if (t.z < -lim) f |= 32u;
    return f;
}

V vertex(uint i, uint n, uint prog, uint flags, bool lit) {
    V o;
    const bool skin = prog != 1u;
    const uint stride = skin ? 5u : 4u;
    const uint vin = ldw(9);
    const uint b = vin + i * stride;
    float4 pos = ldq(b), uv = ldq(b + 1u);
    float4 col = float4(ldqi(b + 2u));
    float4 nf = float4(ldqi(b + 3u));
    float4 k = ldq(CQ(0x3FCu));
    float4 nrm;
    if (k.w != 0.0) {
        uint m = vin + n * stride;
        pos = pos * (1.0 - k.w) + ldq(m + i) * k.w;
        nrm = nf * ((1.0 - k.w) * 0.0078125) + float4(ldqi(m + n + i)) * (k.w * 0.0078125);
    } else {
        nrm = nf * 0.0078125;
    }
    if (skin) {
        int4 idx = ldqi(b + 4u);
        float4 wt = ldq(b + 4u);
        uint pal = uint(int(ldw(10)));
        float4 mr0 = 0, mr1 = 0, mr2 = 0, mr3 = 0;
        [unroll] for (uint j = 0; j < 4; ++j) {
            // VU1 data addresses wrap at 1024 qwords: the index word's high bits (the weight's mantissa) vanish
            uint ix = uint(idx[j]) & 0xFFFFu;
            mr0 += ldq(pal + (((0x2B8u + ix) & 1023u) - 0x2B8u)) * wt[j];
            mr1 += ldq(pal + (((0x2B9u + ix) & 1023u) - 0x2B8u)) * wt[j];
            mr2 += ldq(pal + (((0x2BAu + ix) & 1023u) - 0x2B8u)) * wt[j];
            mr3 += ldq(pal + (((0x2BBu + ix) & 1023u) - 0x2B8u)) * wt[j];
        }
        float4 p = pos, nn = nrm;
        pos = mr3 + mr0 * p.x + mr1 * p.y + mr2 * p.z;
        nrm = mr0 * nn.x + mr1 * nn.y + mr2 * nn.z;
    }
    float4 matcol = ldq(CQ(0x3FBu));
    uint type0 = asuint(ldq(CQ(0x3D4u)).w) & 0xFFFFu;
    if (!lit) {
        // position / clip flags only (the neighbours whose ADC words decide this triangle's fog bits)
    } else if (type0 != 0u) {
        float4 m0 = ldq(CQ(0x3D0u)), m1 = ldq(CQ(0x3D1u)), m2 = ldq(CQ(0x3D2u)), m3 = ldq(CQ(0x3D3u));
        uint p = 0x3D4u;
        [loop] for (uint g = 0; g < 16u && p < 0x3F0u; ++g) {
            float4 lc = ldq(CQ(p));
            uint type = asuint(lc.w) & 0xFFFFu;
            float4 r1 = ldq(CQ(p + 1u)), r2 = ldq(CQ(p + 2u));
            if (type == 2u) {
                col.xyz += lc.xyz * k.x;
                p += 1u;
            } else if (type == 1u) {
                float4 dir = (m0 * r1.x + m1 * r1.y + m2 * r1.z) * (-m3.w);
                col.xyz += (lc.xyz * k.z) * max(dot3(nrm, dir), 0.0);
                p += 2u;
            } else if (type >= 0x80u && type <= 0x82u) {
                float4 lp = (m0 * r1.x + m1 * r1.y + m2 * r1.z) + m3;
                float rinv = 1.0 / (r1.w * m0.w);
                float4 dv = lp - pos;
                float il = 1.0 / sqrt(dot3(dv, dv));
                float f = max(dot3(dv, nrm), 0.0) * (il - rinv);
                float3 c = (lc.xyz * k.z) * f;
                if (type == 0x80u) {
                    col.xyz = max(col.xyz + c, col.xyz);
                } else {
                    float4 sdir = (m0 * r2.x + m1 * r2.y + m2 * r2.z) * m3.w;
                    float cs = dot3(dv, sdir) * il;
                    float cone = r2.w * m3.w;
                    if (type == 0x81u) {
                        if (!(cone - cs < 0.0)) col.xyz += max(c, 0.0);
                    } else {
                        float pinv = 1.0 / (m3.w + r2.w * m3.w);
                        col.xyz += max(c, 0.0) * max(cone * pinv - pinv * cs, 0.0);
                    }
                }
                p += type == 0x80u ? 2u : 3u;
            } else {
                break;
            }
        }
        col = min(col, 255.0) * matcol;
    } else {
        col = col * matcol;
    }
    float4 r28 = ldq(3), r29 = ldq(4), r30 = ldq(5), r31 = ldq(6), off = ldq(7);
    float4 fg = ldq(CQ(0x3F6u));
    float fs = fg.z, fnear = fg.w * fs;
    float4 c1 = ldq(CQ(0x3FDu)), c2 = ldq(CQ(0x3FEu));
    o.clipf = 0u;
    o.fog = 0.0;
    if (prog == 3u) {  // parallel projection (063)
        float4 c = r31 + r28 * pos.x + r29 * pos.y + r30 * pos.z;
        o.scr = c.xyz + off.xyz;
        o.q = 1.0;
        o.st = uv.xy;
        if ((flags & 16u) != 0u) {
            o.fog = min(max(c.w * fs, fnear), fnear + 255.0) - fnear;
            o.clipf = clip_flags(float4(c.x * c1.y, c.y * c2.y, c1.z + c2.z * c.w, 1.0), 1.0);
        } else {
            o.fog = max(min((r31.w * fs - fnear) + (r28.w * fs) * pos.x + (r29.w * fs) * pos.y + (r30.w * fs) * pos.z, 255.0), 0.0);
        }
    } else {
        float4 c;
        c.x = r31.x + r28.x * pos.x + r29.x * pos.y + r30.x * pos.z;
        c.y = r31.y + r28.y * pos.x + r29.y * pos.y + r30.y * pos.z;
        c.z = r31.z + r30.z * pos.z;
        c.w = r31.w + r28.w * pos.x + r29.w * pos.y + r30.w * pos.z;
        float q;
        if ((flags & 8u) != 0u) {
            float wf = (r31.w * fs) + (r28.w * fs) * pos.x + (r29.w * fs) * pos.y + (r30.w * fs) * pos.z;
            q = fs / wf;
            o.fog = min(max(wf, fnear), fnear + 255.0) - fnear;
        } else {
            q = 1.0 / c.w;
        }
        o.scr = off.xyz + c.xyz * q;
        o.q = q;
        o.st = uv.xy * q;
        if ((flags & 16u) != 0u) {
            float4 t = float4(c.x * c1.y, c.y * c2.y, c1.z + c2.z * c.w, c.w);
            o.clipf = clip_flags(t, abs(t.w));
        }
    }
    o.col = col;
    return o;
}

int ftoi16(float f) { return int(clamp(f * 16.0, -2147483520.0, 2147483520.0)); }
int ftoi1(float f) { return int(clamp(f, -2147483520.0, 2147483520.0)); }

void store_vertex(uint slot_vtx, V v, float4 colsrc, uint flags, int ofx, int ofy, uint uvreg, float f, bool zero_area, uint cbi) {
    int X = ftoi16(v.scr.x), Y = ftoi16(v.scr.y);
    int x = (X & 0xFFFF) - ofx, y = (Y & 0xFFFF) - ofy;
    if (zero_area) { x = -1073741824; y = -1073741824; }  // culled: zero area, far outside the scissor
    uint Z = uint(ftoi16(v.scr.z));
    float z = (flags & 1u) != 0u ? float((Z >> 4) & 0xFFFFFFu) : float(Z);
    const uint rgba = (uint(ftoi1(colsrc.x)) & 0xFFu) | ((uint(ftoi1(colsrc.y)) & 0xFFu) << 8) |
                      ((uint(ftoi1(colsrc.z)) & 0xFFu) << 16) | ((uint(ftoi1(colsrc.w)) & 0xFFu) << 24);
    uint a = slot_vtx * 40u;
    nout.Store2(a, uint2(asuint(x), asuint(y)));
    nout.Store4(a + 8u, uint4(asuint(z), rgba, asuint(v.st.x), asuint(v.st.y)));
    nout.Store4(a + 24u, uint4(asuint(v.q), (uvreg & 0x3FFFu) | (((uvreg >> 16) & 0x3FFFu) << 16), uint(f), cbi));
}

float cz(float3 a, float3 b) {  // no FMA contraction: the sign of an exact zero must follow the CPU model
    precise float p0 = a.x * b.y;
    precise float p1 = b.x * a.y;
    precise float r = p0 - p1;
    return r;
}
bool negz(float v) { return (asuint(v) & 0x80000000u) != 0u; }

// The judgement of the triangle that vertex j closes (vertices p0, p1, p2 = j-2, j-1, j): its ADC and its W word
// (the GS takes F from bits 4-11 of that word for XYZF2: the fog, or the sign-extended ADC word of non-fog variants).
struct Judge { bool adc; float fogbits; };
Judge judge(V p0, V p1, V p2, uint j, bool list, uint prog, uint flags, uint vi07, uint cullz) {
    bool neg;
    if (list) neg = negz(cz(p2.scr - p0.scr, p1.scr - p0.scr));
    else if ((j & 1u) == 0u) neg = negz(cz(p1.scr - p0.scr, p1.scr - p2.scr));
    else neg = negz(cz(p2.scr - p1.scr, p0.scr - p1.scr));
    const uint sflag = neg ? 0x20u : 0u;
    const bool cull = (flags & 16u) != 0u;
    const bool outside = cull && (p0.clipf | p1.clipf | p2.clipf) != 0u;
    Judge r;
    if (prog == 3u || (flags & 8u) != 0u) {
        r.adc = ((cull ? (outside ? 1u : 0u) : 0u) + sflag) != cullz;
        const float bump = !r.adc ? 0.0 : (cull || prog != 3u) ? 2048.5 : 2048.0;
        r.fogbits = float((uint(ftoi16(p2.fog + bump)) >> 4) & 0xFFu);
    } else {
        uint w = (vi07 + sflag) & 0xFFFFu;
        if (cull) w |= outside ? 0x8000u : 0x7FFFu;
        r.adc = (w & 0x8000u) != 0u;
        r.fogbits = float((w >> 4) & 0xFFu);
    }
    return r;
}

[numthreads(64, 1, 1)]
void cs_native(uint3 tid : SV_DispatchThreadID) {
    const uint slot = tid.x;
    if (slot >= total_slots) return;
    uint lo = 0u, hi = nbatches;  // the batch holding this slot: last first_slot <= slot
    while (hi - lo > 1u) {
        uint mid = (lo + hi) >> 1;
        if (ntab.Load(mid * 16u) <= slot) lo = mid; else hi = mid;
    }
    uint4 te = ntab.Load4(lo * 16u);
    g_rec = te.y;
    const uint t = slot - te.x;
    const uint n = ldw(0), prog = ldw(1), flags = ldw(2), vi07 = ldw(3);
    const int ofx = int(ldw(4)), ofy = int(ldw(5));
    const uint uvreg = ldw(6), fogreg = ldw(7), cullz = ldw(8);
    const bool list = (flags & 4u) != 0u;
    const bool xyzf = (flags & 1u) != 0u;
    const uint i0 = list ? 3u * t : t;
    V a = vertex(i0, n, prog, flags, true), b = vertex(i0 + 1u, n, prog, flags, true), c = vertex(i0 + 2u, n, prog, flags, true);
    const Judge jc = judge(a, b, c, i0 + 2u, list, prog, flags, vi07, cullz);  // this triangle (kicked by c)
    float fa = float(fogreg), fb = float(fogreg), fc = float(fogreg);
    if (xyzf) {
        // F of each vertex: from its own W word (strips: the triangle each vertex closes; the first two of a strip
        // and the first two of each list triangle carry W = 0 or the plain fog)
        const bool fogvar = prog == 3u || (flags & 8u) != 0u;
        fc = jc.fogbits;
        if (list) {
            fa = fogvar ? float((uint(ftoi16(a.fog)) >> 4) & 0xFFu) : 0.0;
            fb = fogvar ? float((uint(ftoi16(b.fog)) >> 4) & 0xFFu) : 0.0;
        } else {
            if (t >= 1u) {
                V m1 = vertex(t - 1u, n, prog, flags, false);
                fb = judge(m1, a, b, t + 1u, false, prog, flags, vi07, cullz).fogbits;
                if (t >= 2u) {
                    V m2 = vertex(t - 2u, n, prog, flags, false);
                    fa = judge(m2, m1, a, t, false, prog, flags, vi07, cullz).fogbits;
                } else {
                    fa = fogvar ? float((uint(ftoi16(a.fog)) >> 4) & 0xFFu) : 0.0;
                }
            } else {
                fa = fogvar ? float((uint(ftoi16(a.fog)) >> 4) & 0xFFu) : 0.0;
                fb = fogvar ? float((uint(ftoi16(b.fog)) >> 4) & 0xFFu) : 0.0;
            }
        }
    }
    const bool flat = (flags & 2u) != 0u;
    const uint base = slot * 3u;
    const uint cbi = ldw(11);
    store_vertex(base, a, flat ? c.col : a.col, flags, ofx, ofy, uvreg, fa, jc.adc, cbi);
    store_vertex(base + 1u, b, flat ? c.col : b.col, flags, ofx, ofy, uvreg, fb, jc.adc, cbi);
    store_vertex(base + 2u, c, c.col, flags, ofx, ofy, uvreg, fc, jc.adc, cbi);
}
)HLSL";

} // namespace p3fes::gs::hlsl
