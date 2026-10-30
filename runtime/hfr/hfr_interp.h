// Frame interpolation for the high-frame-rate display (track H, docs/ANALYSIS/32_high_frame_rate.md): pictures in
// between two game frames, made from the native renderer's batches. The game itself is untouched (30 fps, the
// field gate, deterministic): this code only reads op lists on the render thread.
//
// Three parts, all pure C++ (no D3D11, no guest memory):
//  * matching (match_frames): which batch of game frame N-1 is which batch of frame N. A batch is identified by its
//    native key (opaque u64, stable per geometry cluster across frames) and, when several batches share a key
//    (instances of one model), by the nearest transform (the rows' translation); plus the camera-cut decision.
//  * stage-1 blending (blend_vertices): the native renderer's converted vertices of both frames, blended per source
//    vertex in clip space (perspective-correct: positions weighted by w = 1/q), written over frame N's triangles.
//  * transform blending (blend_affine): a 4x4 camera x object (or bone) matrix blended as rotation (quaternion
//    slerp after a polar decomposition) + stretch + translation, for the native renderer's GPU stage, where an
//    in-between frame re-runs the batch with blended transform records instead of blending converted vertices.
#pragma once

#include "p3fes/gs/gs_ops.h"

#include <cstddef>
#include <span>
#include <vector>

namespace p3fes::hfr {

// What matching needs of one batch (both stages provide it).
struct BatchView {
    u64 key = 0;
    const float* rows = nullptr;  // 16 floats, row-major rows 0x3F0..0x3F3 (row 3 = translation, camera space)
    u32 nv = 0;                   // source vertices
};
std::vector<BatchView> batch_views(const gs::OpList& l);

struct InterpParams {
    // A matched batch is held at frame N (not blended) when one of its vertices moves more than this many pixels
    // between the frames (stage 1) ...
    float max_move_px = 160.0f;
    // ... or its transform turns by more than this (radians) or its origin jumps by more than this fraction of its
    // distance from the camera (both stages).
    float max_turn_rad = 0.8f;
    float max_jump_rel = 0.6f;
    // Camera cut: the whole frame is shown without blending when the held share of matched vertices exceeds
    // cut_held_share, or fewer than min_matched_share of frame N's native vertices found a partner.
    float cut_held_share = 0.4f;
    float min_matched_share = 0.3f;
    // Two instances of one key are the same object only when their origins are closer than this fraction of the
    // distance from the camera (else: unmatched, drawn as in frame N).
    float instance_rel = 0.5f;
    bool blend_colour = true;  // lighting colour lerped (else frame N's)
};

struct MatchStats {
    u32 batches = 0;        // in frame N
    u32 matched = 0;        // found a partner (blended unless held)
    u32 held = 0;           // matched, but moved too far (shown as in frame N)
    u32 unmatched = 0;      // no partner (appeared): shown as in frame N
    u32 vanished = 0;       // in N-1 only (gone in N)
    u64 verts = 0, matched_verts = 0, held_verts = 0;
    bool cut = false;       // whole frame not interpolable
    enum CutReason : u8 { CutNone, CutEmpty, CutUnmatched, CutHeld };
    CutReason cut_reason = CutNone;  // no native batch in frame N / too few matched / too many held
};

struct FrameMatch {
    std::vector<int> prev_of;  // per batch of frame N: index into frame N-1's batches, -1 = unmatched or held
    MatchStats st;
};

// Matching on keys / rows only (both stages). `prev_verts`/`next_verts` (optional, stage 1): the lists, to apply
// the screen-move test.
FrameMatch match_frames(std::span<const BatchView> prev, std::span<const BatchView> next, const InterpParams& p,
                        const gs::OpList* prev_list = nullptr, const gs::OpList* next_list = nullptr);

// One source vertex blended between frames: `a` (N-1) and `b` (N) at `alpha` (0 = a, 1 = b, > 1 extrapolates).
// Position in clip space: w = lerp(1/qa, 1/qb), xy = lerp(w*xy) / w; Z (affine in q for the g3 programs) at the
// same point in q; STQ from b's texture coordinate s/q, t/q at the blended q; colour / fog lerped (or b's). Returns
// false (out = b) when a q is not positive and finite or the blended w is not positive.
bool blend_vertex(const gs::GpuVertex& a, const gs::GpuVertex& b, float alpha, bool colour, gs::GpuVertex& out);

struct BlendStats {
    u64 batches = 0, verts = 0, refused = 0;  // refused: source vertices left as frame N (bad q)
};
// Stage 1: for every matched batch of `next`, rewrites its triangles in `verts` (a copy of next.verts) with the
// blended source vertices (flat batches: each triangle takes its third vertex's blended colour). Batches not
// matched keep frame N's vertices.
BlendStats blend_vertices(const gs::OpList& prev, const gs::OpList& next, const FrameMatch& m, float alpha,
                          const InterpParams& p, std::vector<gs::GpuVertex>& verts);

// ---- transform blending (stage 2, and the cut test) ---------------------------------------------------------------

struct Quat {
    float w = 1, x = 0, y = 0, z = 0;
};
// Polar decomposition of the upper-left 3x3 of a row-major 4x4 (rows = basis vectors): M = R * S with R a rotation
// (det +1; a reflection is kept in S) and S symmetric. false when M is singular.
bool polar3(const float m[16], float r[9], float s[9]);
Quat quat_from_rot(const float r[9]);
void rot_from_quat(const Quat& q, float r[9]);
Quat slerp(Quat a, Quat b, float t);
// Rotation angle (radians) between the rotation parts of two transforms; returns a large value when singular.
float turn_angle(const float a[16], const float b[16]);
// a -> b at t: rotation slerped, stretch and translation lerped; the w column (0 0 0 1 for affine rows) lerped.
// Falls back to an element-wise lerp when either matrix is singular.
void blend_affine(const float a[16], const float b[16], float t, float out[16]);

// Alpha for a display tick, quantised so that when the display rate is an integer multiple k of the game rate the
// in-between pictures sit at 1/k steps and every k-th tick shows the exact game frame (alpha = 1): `k` = 0 means
// no quantisation.
double quantise_alpha(double alpha, unsigned k);

} // namespace p3fes::hfr
