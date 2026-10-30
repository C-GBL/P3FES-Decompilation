// The high-frame-rate interpolator on the D3D11 render thread (docs/ANALYSIS/32_high_frame_rate.md §5): plugged into
// GsD3D11Renderer (set_interpolator) under a decoupled display rate (frame pacing, docs/ANALYSIS/31 §7).
//
//  * Records per game frame: the GS memory (+ CLUT) at the frame's first list (an executor memory bank), every list
//    of the frame (copied: their native side tables are the blending input) and the display registers that show it.
//    A frame begins with the list of the slice in which the previous frame's flip happened (the flip runs at the
//    slice's first check point, before any GS work of the next frame; the host submits that slice as
//    PresentPlan::Latch tagged with the new flip count).
//  * Per display tick between two latched frames A (shown) and B (next): alpha quantised (hfr_interp.h), then
//    alpha 0 -> A as is (the renderer draws it), alpha 1 -> B's composed picture, in between -> B's lists replayed
//    from B's starting memory into a scratch bank with each matched native batch's triangles blended between A and B
//    (match_frames / blend_vertices), composed with B's display registers and drawn into the back buffer. Everything
//    that is not a native batch (2-D, sprites, Im2D / Im3D, fallback VU1 batches, transfers) is B's, in B's order.
//  * Camera cuts / nothing to blend: A until B is due (the 30 fps picture).
// Render thread only (all calls come from GsD3D11Renderer's thread), except stats() (any thread).
#pragma once

#include "hfr_interp.h"
#include "p3fes/gs/gs_d3d11.h"

#include <array>
#include <memory>
#include <mutex>
#include <string>

namespace p3fes::hfr {

struct HfrOptions {
    // Alpha steps per game frame: 0 = automatic (the display ticks per game frame when that is within 4 % of an
    // integer, else none); 1 = never blend (a game-rate picture on a fast display); k > 1 = steps of 1/k.
    unsigned steps = 0;
    // Low latency: when the next frame is not there yet, extrapolate from the two before (alpha > 1, at most
    // 1 + max_extrapolate), instead of showing the newest frame as is.
    bool extrapolate = false;
    float max_extrapolate = 0.5f;
    bool linear = false;  // bilinear scaling of the picture (else point, as the renderer's default)
    bool gpu_timing = true;  // timestamp queries around each replay (read back a few ticks later, no stall)
    // Automatic steps only: the in-between pictures of one game frame may cost at most this share of it in GPU time
    // (measured per replay); beyond that the steps drop (120 Hz -> 60 Hz in-betweens, ...). 0 = no limit.
    double gpu_budget = 0.5;
    InterpParams params;
    // Diagnostics: replay even frame pairs judged a cut / without native batches (the in-between picture is then
    // frame B replayed: it must equal B's own picture); dump A / in-between / B pictures of every `dump_every`-th
    // game frame (at most dump_max) as PNGs into dump_dir.
    bool force_replay = false;
    std::string dump_dir;
    u32 dump_every = 30, dump_max = 0;
    u64 dump_from = 0;  // first game frame (flip count) to dump
};

struct HfrStats {
    u64 frames = 0;        // game frames recorded
    u64 ticks = 0;         // draw() calls
    u64 interpolated = 0;  // ticks drawn as an in-between picture
    u64 extrapolated = 0;
    u64 exact_next = 0;    // alpha quantised to 1: B as composed
    u64 shown_prev = 0;    // alpha 0, cut, missing record: A as is (by the renderer)
    u64 no_next = 0;       // A as is because the next frame was not latched yet (the game ran late)
    u64 cuts = 0;          // frame pairs judged a camera cut / nothing to blend
    u64 cut_empty = 0, cut_unmatched = 0, cut_held = 0;  // ... because frame N has no native batch / few matched / many held
    u64 no_record = 0;     // a tick whose frames have no complete record (start-up, a state load, a merged list)
    u64 pairs = 0;         // frame pairs matched
    u64 batches = 0, matched = 0, held = 0, unmatched = 0;  // summed over pairs
    u64 verts = 0, matched_verts = 0;
    double cpu_ms_sum = 0.0, cpu_ms_max = 0.0;  // render-thread time per interpolated tick (copy, blend, issue)
    double copy_ms_sum = 0.0, blend_ms_sum = 0.0, issue_ms_sum = 0.0;  // its parts (copy: once per game frame)
    double gpu_ms_sum = 0.0, gpu_ms_max = 0.0;  // GPU time per interpolated tick (replay + compose + draw)
    u64 gpu_samples = 0;
    unsigned steps = 0;  // the alpha steps in use
    u64 gpu_capped = 0;  // ticks whose steps the GPU budget lowered
};

class HfrInterpolator final : public gs::IFrameInterpolator {
public:
    explicit HfrInterpolator(const HfrOptions& o);
    ~HfrInterpolator() override;
    void before_execute(gs::GsD3D11Executor& ex, const gs::OpList& ops, const gs::DisplayRegs& disp, const gs::PresentPlan& plan) override;
    void on_reset() override;
    bool draw(gs::GsD3D11Executor& ex, const gs::DisplayTick& tick) override;
    HfrStats stats() const;
    // One line for logs / the overlay: "hfr 60/30: 1432 in-between, cut 3, matched 97.1 %, gpu 1.9 ms (max 3.4)".
    std::string summary() const;
    // Short form for the frame-time overlay, over the ticks since the previous call: "hfr: 51% in-between, 1.9 ms gpu".
    std::string overlay_line();

private:
    struct Frame {
        bool valid = false;
        u64 tag = 0;
        long long due = 0;
        u32 bank = 0;
        gs::OpList ops;
        gs::DisplayRegs disp{};
        bool tainted = false;  // a reset_memory or anything that makes the replay inexact
    };
    struct Gpu;
    Frame* find(u64 tag);
    bool ensure_gpu(gs::GsD3D11Executor& ex, const gs::DisplayTick& t);
    bool draw_srv(const gs::DisplayTick& t, ID3D11ShaderResourceView* srv);
    bool replay(gs::GsD3D11Executor& ex, const gs::DisplayTick& t, Frame& a, Frame& b, float alpha);
    unsigned steps_for(const gs::DisplayTick& t, const Frame& a, const Frame& b);
    void collect_gpu_times(ID3D11DeviceContext* ctx);
    void dump_pair(gs::GsD3D11Executor& ex, const gs::DisplayTick& t, Frame& a, Frame& b, float alpha);
    void replay_to_png(gs::GsD3D11Executor& ex, const Frame& f, const gs::OpList& l, const std::string& path);

    HfrOptions o_;
    static constexpr u32 kFrames = 6;  // the renderer latches 4; one open, one spare
    std::array<Frame, kFrames> f_{};
    int open_ = -1;          // the frame being recorded
    u64 last_tag_ = 0;
    bool have_last_tag_ = false;
    bool banks_ok_ = false;
    u32 scratch_bank_ = kFrames;
    // Cached pair work: the match of (a_tag, b_tag) and B's list copy whose matched ranges are rewritten per tick.
    u64 m_a_ = ~0ull, m_b_ = ~0ull;
    FrameMatch match_;
    gs::OpList work_;
    u64 work_tag_ = ~0ull;
    long long last_tick_ = 0;
    double tick_ema_ = 0.0;  // display tick interval (QPC ticks)
    double gpu_ema_ms_ = 0.0;  // GPU ms per in-between picture (recent; drives the GPU budget)
    std::unique_ptr<Gpu> g_;
    u32 dumped_ = 0;
    u64 dump_last_ = ~0ull;
    HfrStats overlay_last_{};
    mutable std::mutex m_;
    HfrStats st_{};
};

} // namespace p3fes::hfr
