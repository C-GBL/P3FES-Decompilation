// Frame-time telemetry for the windowed host (docs/ANALYSIS/31_frame_pacing.md §2): what every guest frame cost
// the host, when it was presented and shown, and why a late one was late. Cheap enough to leave on (a few QPC /
// TSC reads per vblank slice, the zone profiler's ~1 %); diagnostics only -- nothing here reaches the guest.
//
// Per guest frame (one GS flip; the field gate makes that two vblank slices at 30 fps):
//   work   host wall time of its slices minus the pacing waits (the frame's cost; the budget is 33.37 ms)
//   cpu    the guest thread's own CPU time over those slices (QueryThreadCycleTime): work >> cpu = the thread was
//          descheduled (machine load), not slow
//   zones  the zone profiler's split of the work (p3fes/prof.h: ee, vu1, vif1, gif, gs_submit, audio, cdvd, ...)
//   events render-queue merges (the render thread fell behind), audio back-pressure waits / underruns, pacer
//          re-anchors
// Per present (gs::PresentRecord from the render thread): the present-to-present interval of new guest frames, how
// late it was against its timed target, and -- from DXGI frame statistics, when the swap chain reports them -- how
// many display refreshes the frame stayed on screen.
// A hitch is a new-frame interval above `hitch_ms` (34 ms: the 33.37 ms frame plus timer slack); each is listed with
// its frame's work, CPU time, top zones and events, and classified: guest (the game itself took > 2 vblanks, as on
// the PS2), load (descheduled), host (work over budget: the zones say where), present (on time on the host side,
// late in the render thread / DXGI), pacing (re-anchor).
//
// Outputs: summary() at exit (percentiles p50 / p95 / p99 / max and the hitch list), the per-frame CSV (--frame-log
// FILE, buffered, written as frames complete), and live() for the overlay (frame_overlay.h).
#pragma once

#include <cstdint>
#include <cstdio>
#include <deque>
#include <string>
#include <vector>

#include "frame_pacing.h"
#include "p3fes/gs/gs_d3d11.h"
#include "p3fes/prof.h"

namespace p3fes::app {

// Cumulative host counters the telemetry differences per frame (main.cpp fills it each slice).
struct FrameEvents {
    std::uint64_t merged = 0;         // render-thread lists appended to a queued one
    std::uint64_t audio_waits = 0;    // XAudio2 back-pressure waits
    double audio_wait_ms = 0.0;
    std::uint64_t underruns = 0;      // XAudio2 ran dry mid-stream
    std::uint64_t resyncs = 0;        // pacer re-anchors
    double audio_queued_ms = 0.0;     // now (not cumulative)
    double audio_ratio = 1.0;         // now
};

class FrameTelemetry {
public:
    struct Options {
        bool zones = true;          // turn the zone profiler on (if --zones has not) for the per-frame split
        std::string log_path;       // per-frame CSV; empty = none
        double hitch_ms = 34.0;
        std::string pacing;         // the pacing mode, for the summary / overlay
    };
    explicit FrameTelemetry(const Options& opt);
    ~FrameTelemetry();
    FrameTelemetry(const FrameTelemetry&) = delete;
    FrameTelemetry& operator=(const FrameTelemetry&) = delete;

    // Around each vblank slice of the host loop: begin before GameHost::run, wait_begin / wait_end around the
    // pacing wait, close after it with the guest's counters and the host's cumulative events.
    void slice_begin();
    void wait_begin();
    void wait_end();
    void slice_close(std::uint64_t vblank, std::uint64_t flips, const FrameEvents& ev);
    // The render thread's presents (GsD3D11Renderer::take_present_log), in order.
    void presents(const std::vector<gs::PresentRecord>& recs);
    void set_pacing(const std::string& s) { opt_.pacing = s; }

    struct Live {
        double fps = 0.0;                    // new guest frames presented in the last second (game rate)
        double display_fps = 0.0;            // presents in the last second (display rate)
        double p50 = 0.0, p99 = 0.0, max = 0.0;      // new-frame interval ms, last ~5 s
        double work_p50 = 0.0, work_p95 = 0.0;       // host work per frame ms, last ~5 s
        std::uint64_t frames = 0, hitches = 0, late = 0;
        double audio_ms = 0.0, ratio = 1.0;
        std::uint64_t underruns = 0;
        std::string pacing;
        std::vector<float> intervals;        // the last <= 240 new-frame intervals (ms), oldest first
        std::vector<float> work;             // host work of the same frames (ms)
    };
    Live live() const;
    // The end-of-run report (several "p3fes: frame-time: ..." lines).
    std::string summary() const;
    void finish();  // flushes / closes the CSV

private:
    struct Frame {
        std::uint64_t flip = 0, vblank = 0;
        std::uint32_t guest_vblanks = 0, slices = 0;
        double work_ms = 0.0, cpu_ms = 0.0, wait_ms = 0.0;
        float zone_ms[prof::kZones] = {};
        std::uint64_t merged = 0, audio_waits = 0, underruns = 0, resyncs = 0;
        double audio_wait_ms = 0.0, audio_queued_ms = 0.0;
        // present side
        bool presented = false;
        double interval_ms = -1.0;   // since the previous new frame, as displayed (DXGI) or else as presented (-1: unknown)
        double present_interval_ms = -1.0;  // since the previous new-frame Present call
        int refreshes = -1;          // display refreshes the previous frame stayed (DXGI), -1 unknown
        double late_ms = 0.0;        // present_qpc - target (At), 0 when on time
        double exec_ms = 0.0;        // render-thread list execution since the previous present
        bool ready_late = false;
        double queue_ms = -1.0;      // the flip list: submitted -> taken by the render thread (-1 unknown)
        double render_ms = -1.0;     // taken -> executed and composed
        double call_ms = -1.0;       // Present() call duration (blocking = the GPU / DXGI queue is full)
    };
    struct Hitch {
        Frame f;
        std::string cls;
    };
    double qpc_ms(long long ticks) const;
    double tsc_ms(std::uint64_t ticks) const;
    void finalize(Frame& f);
    std::string describe(const Frame& f) const;
    std::string classify(const Frame& f) const;

    Options opt_;
    bool owns_prof_ = false;
    double qpc_hz_ = 1.0;
    std::uint64_t tsc0_ = 0;
    long long qpc0_ = 0;
    double tsc_per_ms_ = 0.0;
    // current slice / frame accumulation
    long long t_begin_ = 0, t_wait_begin_ = 0, t_wait_end_ = 0;
    std::uint64_t cyc_begin_ = 0;
    std::uint64_t zone_last_[prof::kZones] = {};
    Frame cur_{};
    std::uint64_t last_flip_ = 0, last_flip_vblank_ = 0;
    bool have_flip_ = false;
    FrameEvents ev_last_{};
    bool ev_primed_ = false;
    // frames waiting for their present record; finished frames (live window, hitches)
    std::deque<Frame> pending_;
    std::deque<Frame> recent_;  // last ~300 finished frames
    std::vector<Hitch> hitches_;
    std::uint64_t hitch_count_ = 0;
    // presents
    long long last_new_present_qpc_ = 0;
    std::uint64_t last_present_tag_ = 0;
    long long last_sync_qpc_ = 0;
    std::uint32_t last_sync_refresh_ = 0;
    bool have_sync_ = false;
    std::uint64_t presents_ = 0, new_presents_ = 0, timed_ = 0, late_ = 0;
    std::uint64_t refresh_hist_[8] = {};  // displayed refreshes per frame: 0..6, 7 = 7+
    std::uint64_t cadence_hist_[8] = {};  // guest vblanks per flip: 0..6, 7 = 7+
    FrameTimeHistogram h_interval_, h_present_, h_display_, h_work_, h_cpu_, h_late_, h_timer_;
    long long last_any_present_qpc_ = 0;
    std::deque<long long> recent_presents_;  // present times of the last second (display rate)
    std::uint64_t frames_ = 0, over_budget_ = 0, over_50_ = 0;
    FrameEvents ev_now_{};
    std::FILE* log_ = nullptr;
    std::vector<char> log_buf_;
};

} // namespace p3fes::app
