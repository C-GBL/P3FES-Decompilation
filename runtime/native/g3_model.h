// Semantic model of RenderWare's PS2 "g3" VU1 microprograms (docs/ANALYSIS/31_native_renderer.md §2): what one
// MSCNT batch of vu1_prog_042_g3_generic / vu1_prog_064_g3_skin computes from VU1 data memory, written as plain
// C++ float code instead of VU instructions. It is the reference for the native renderer's GPU vertex shader
// (runtime/native/native_hlsl.h): the same steps, the same order of operations. Host IEEE floats, so the results
// are close to, not bit-identical with, the VU's (truncating, no denormals) -- `p3fes_native_check` measures the
// difference against the exact interpreter on captured batches.
//
// Input of a batch (data memory at the MSCNT, VF registers left by the program's init at MSCAL 0):
//   TOP .. : N = ITOP vertices; generic: 4 qwords each (position xyz, uv xy, prelit colour as int32 x4, normal as
//            int32 x4 = signed 8-bit unpack), skin: 5 (the same + bone indices / weights), then (morph) N positions
//            and N normals of the second morph target
//   0x3D0..0x3D3 lighting matrix (object space), 0x3D4.. light records (type in the first qword's w; 0 ends)
//   0x3F0..0x3F3 transform rows (the init turns them into vf28..vf31), 0x3F6 fog (z scale, w near), 0x3F7 screen
//   scale, 0x3F8 screen offset, 0x3F9 offset 2, 0x3FA GIF tag (yzw), 0x3FB material colour, 0x3FC lighting
//   factors (x ambient, z directional / point / spot, w morph factor), 0x3FD/0x3FE guard-band clip scales,
//   0x3FF flags (x variant bits, y continuation, z cull mode)
// Output: one PATH1 GIF packet: the tag, then 3 qwords per vertex (STQ, RGBAQ, XYZ2 / XYZF2 with ADC in w).
#pragma once

#include "p3fes/ee_types.h"

#include <vector>

namespace p3fes::vu1 {
struct VU1State;
}

namespace p3fes::native {

// Generic = vu1_prog_042_g3_generic, Skin = vu1_prog_064_g3_skin (perspective cameras), SkinPar =
// vu1_prog_063_g3_skin (g3_skin code-array entry 3: parallel projection, the characters' shadow textures in the
// field).
enum class G3Prog : u8 { None, Generic, Skin, SkinPar };

// The transform / output part a batch runs, chosen at init from the flags word 0x3FF.x (bit 1 cull/clip, bit 3
// full clipper, bit 2 triangle list, bit 0 fog).
enum class G3Variant : u8 {
    Strip,
    StripFog,
    List,
    ListFog,
    CullStrip,     // + guard-band ADC: a triangle with a vertex outside the guard band is not drawn
    CullStripFog,
    CullList,
    CullListFog,
    ClipStrip,     // full clipper (near-plane crossing objects)
    ClipList,
    Count
};

const char* to_string(G3Variant v) noexcept;
G3Variant g3_variant(u32 flags) noexcept;
// Per program: the parallel-projection program has no fog bit (its outputs always carry fog): its variants are
// reported as the *Fog ones.
G3Variant g3_variant(G3Prog prog, u32 flags) noexcept;
bool g3_fog(G3Variant v) noexcept;
bool g3_list(G3Variant v) noexcept;

// One output vertex as the program writes it: the three GIF PACKED qwords.
struct G3OutVertex {
    float s, t, q, qw;  // STQ (qw = w lane, unspecified)
    s32 rgba[4];        // RGBAQ (ftoi0)
    s32 xyzw[4];        // XYZ2 / XYZF2 (ftoi4): x, y 12.4, z, w = fog << 4 | ADC << 15
};

struct G3Batch {
    G3Prog prog = G3Prog::None;
    G3Variant variant = G3Variant::Count;
    u32 n = 0;            // vertices
    u32 tag[4] = {};      // GIF tag qword
    std::vector<G3OutVertex> v;
    bool clipped = false; // full-clipper batch whose triangles were actually clipped (output not modelled)
    bool culled_all = false;
    u32 lights = 0;       // light-type bitmask seen: 1 ambient, 2 directional, 4 point, 8 spot, 16 soft spot
    bool morph = false;
    std::vector<float> dbg;  // diagnostics (p3fes_native_check, when want_dbg)
    bool want_dbg = false;
    // Input: clip the full clipper's crossing batches in the model (homogeneous clipping against the six guard
    // planes, triangle fans) instead of returning false. The output then lists its triangles explicitly in `tris`
    // (index triples into `v`, which gains the clip vertices) and `explicit_tris` is set; ADC words are unused.
    bool clip_in_model = false;
    bool explicit_tris = false;
    std::vector<u16> tris;
};

// The model of one batch. `s` = the VU state at the MSCNT (or right after the init of an MSCAL 0 run, pc at the
// batch start). Returns false if the batch uses something the model does not cover.
bool g3_model(G3Prog prog, const vu1::VU1State& s, G3Batch& out);

// The GPU vertex stage's input record for a batch (p3fes/gs/gs_native_hlsl.h layout; the GS-dependent header words
// 4-7 left 0) and its triangle slot count / PRIM; false for the full clipper or an unexpected tag (CPU path).
// `palq` = the bone palette rows (from VU1 0x2B8) the record needs; they are passed separately (shared between the
// batches of one object).
bool g3_gpu_record(G3Prog prog, const vu1::VU1State& s, std::vector<u32>& rec, u32& slots, u32& prim, u32& palq);

// The program's own MSCAL 0 init up to the batch start, in C++ (the registers and the 0x3FF.y word it sets).
void g3_init(G3Prog prog, vu1::VU1State& s);

// Byte pc at which the batch part of the program starts (the init of MSCAL 0 runs up to here), the TPC an MSCNT
// leaves (the pair after the E pair's delay slot), and the continuation pc stored at 0x3FF.y per variant.
u32 g3_batch_pc(G3Prog prog) noexcept;
// The g3 program resident in micro memory (16 KiB image), by its first pair and a 64-bit hash of its extent.
G3Prog g3_identify(const u8* micro) noexcept;
// FNV-1a style 64-bit hash over whole 8-byte words of the first `bytes` (program identification).
u64 micro_hash(const u8* p, u32 bytes) noexcept;
u32 g3_end_tpc(G3Prog prog) noexcept;
// vi13 / vi14 (the two output buffers) as the init leaves them.
u32 g3_out_buffer(G3Prog prog, int which) noexcept;
u32 g3_variant_pc(G3Prog prog, G3Variant v) noexcept;

} // namespace p3fes::native
