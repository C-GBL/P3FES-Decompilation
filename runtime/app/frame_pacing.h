// Frame pacing policy for the windowed host (pure C++; docs/ANALYSIS/31_frame_pacing.md). The guest is field-gated
// at 30 fps (kwlnVsyncFieldGate: one flip per two VBLANK_STARTs, docs/ANALYSIS/10 §4); the host's job is to show
// each of those frames exactly once, on a steady cadence, whatever the cost of the individual vblank slices.
//
//  * FramePacer maps virtual time to wall time: wall(v) = offset + v * scale. The host waits before running the
//    guest past v until wall(v) (never runs ahead); a host that falls behind by more than `max_debt_s` re-anchors
//    instead of running flat out to catch up (no spiral, no fast-forward burst after a load). scale = 1 is real
//    time; the display lock sets scale = k * refresh / vblank so one guest vblank lasts exactly k display refreshes
//    (60 Hz: k = 1, 120 Hz: k = 2), and `shift` phase-locks the presents to the middle of a refresh interval. The
//    re-anchor keeps the debt at the limit, so a host that stays slow never idles and one that recovers catches up
//    at most max_debt_s, with presents never closer than their guest vblanks apart (schedule_present).
//  * Presents are timed, not immediate: a guest frame that flipped in the slice ending at virtual time v is
//    presented at wall(v) + present_delay_s (default one guest vblank). A frame whose two slices fit the 33.3 ms
//    budget is then always on time, however unevenly the work splits between them (§3 of the doc).
//  * PresentGate decides which slices present at all: those that showed a new guest frame (flip or display
//    registers changed), and every second vblank while the guest is not flipping (front-buffer drawing, static
//    screens).
//  * FrameTimeHistogram: the percentiles of the telemetry (frame_telemetry.h).
//
// Nothing here reaches the guest: pacing decides only when the host runs the next slice and when the render thread
// presents (ADR-0013 §4). The guest sees the same vblank sequence whatever the host's timing.
#pragma once

#include <cstdint>
#include <vector>

namespace p3fes::app {

inline constexpr double kGuestVblankS = 1001.0 / 60000.0;  // NTSC field: 16.683 ms
inline constexpr double kGuestFrameS = 2.0 * kGuestVblankS;  // the field-gated frame: 33.367 ms

// The k for which one guest vblank lasts k display refreshes of `refresh_s` within `tol` (relative), 0 when none
// (60 / 59.94 Hz: 1, 120 Hz: 2, 240 Hz: 4; 75 or 144 Hz: 0).
int display_lock_ratio(double refresh_s, double guest_vblank_s = kGuestVblankS, double tol = 0.005);

// Where wall time `t` lies in the display's refresh interval, relative to its middle, in refreshes: in [-0.5, 0.5),
// 0 = halfway between two vblanks (the safest moment to present for the next one). `vblank_t` is any vblank.
double present_phase_error(double t, double vblank_t, double refresh_s);

class FramePacer {
public:
    struct Config {
        double max_debt_s = 2.0 * kGuestVblankS;   // behind by more than this: re-anchor to exactly this far behind
        double present_delay_s = kGuestVblankS;    // present = wall(end of the flip slice) + this
    };
    FramePacer() = default;
    explicit FramePacer(const Config& c) : cfg_(c) {}

    // Seconds to wait (>= 0) at wall time `wall_s` before running the guest past virtual time `virt_s`. The first call
    // anchors. Falling more than max_debt_s behind re-anchors to exactly max_debt_s behind (counted in resyncs();
    // the time given up in dropped_s()).
    double delay(double virt_s, double wall_s);
    // The wall deadline of virtual time `virt_s` (valid once anchored).
    double target(double virt_s) const { return offset_ + virt_s * scale_; }
    double present_at(double virt_s) const { return target(virt_s) + cfg_.present_delay_s; }
    // The present time of a frame flipped in the slice ending at `virt_s`, `vblanks_since_last` vblanks after the
    // previous present: present_at(virt_s), but never less than that many vblanks after the previous one (minus
    // 0.5 ms), so frames do not bunch while a debt is caught up. A time before `wall_s` means "at once".
    double schedule_present(double virt_s, double wall_s, std::uint64_t vblanks_since_last);
    bool anchored() const { return anchored_; }

    // Wall seconds per virtual second; target(virt_s) stays where it is (no jump at the change).
    void set_scale(double scale, double virt_s);
    double scale() const { return scale_; }
    // Moves the whole mapping later by `dt` seconds (negative: earlier); the display phase lock.
    void shift(double dt) { offset_ += dt; }
    void set_present_delay(double s) { cfg_.present_delay_s = s; }

    const Config& config() const { return cfg_; }
    std::uint64_t resyncs() const { return resyncs_; }
    double dropped_s() const { return dropped_; }

private:
    Config cfg_{};
    double offset_ = 0.0, scale_ = 1.0;
    bool anchored_ = false;
    std::uint64_t resyncs_ = 0;
    double dropped_ = 0.0;
    double last_present_ = 0.0;
    bool have_last_ = false;
};

// The present delay adapts to the render thread: a heavy list (the title's 12-layer backdrop upload: ~11 ms of
// execute + compose, obs) makes the picture ready that long after the flip slice ends, so the delay is one vblank
// plus the 90th percentile of the recent render times (capped at one more vblank). It rises at once when the
// render time grows and falls only after `hold` presents with a clearly lower need, so the grid rarely moves.
class PresentDelayController {
public:
    explicit PresentDelayController(double base_s = kGuestVblankS, double max_extra_s = kGuestVblankS, unsigned window = 60,
                                    unsigned hold = 300)
        : base_(base_s), max_extra_(max_extra_s), window_(window), hold_(hold), delay_(base_s) {}
    // One timed present's render time (taken from the queue -> executed and composed), seconds. Returns the delay.
    double add(double render_s);
    double delay() const { return delay_; }

private:
    double base_, max_extra_;
    unsigned window_, hold_;
    std::vector<double> recent_;
    std::size_t next_ = 0;
    unsigned lower_for_ = 0;
    double delay_;
};

// Which vblank slices present (see the file comment). Call once per slice, in order.
class PresentGate {
public:
    // `flips`: the guest's flip counter after the slice; `vblank`: its VBLANK_START count; `disp_changed`: the
    // display registers differ from those of the last present.
    bool should_present(std::uint64_t flips, std::uint64_t vblank, bool disp_changed);

private:
    bool primed_ = false;
    std::uint64_t flips_ = 0, last_flip_vblank_ = 0, last_present_vblank_ = 0;
};

// Frame-time histogram: 0.1 ms buckets up to 500 ms (the rest in one overflow bucket), exact count / sum / max.
class FrameTimeHistogram {
public:
    void add(double ms);
    std::uint64_t count() const { return n_; }
    double mean() const { return n_ ? sum_ / static_cast<double>(n_) : 0.0; }
    double max() const { return max_; }
    // The p-th percentile (0..100), upper bucket edge (max() for the top bucket); 0 when empty.
    double percentile(double p) const;
    // Samples strictly above `ms` (bucket resolution: those in buckets wholly above it).
    std::uint64_t above(double ms) const;
    void clear() { *this = FrameTimeHistogram{}; }

private:
    static constexpr int kBuckets = 5000;  // 0.1 ms each
    std::vector<std::uint32_t> b_ = std::vector<std::uint32_t>(kBuckets + 1, 0u);
    std::uint64_t n_ = 0;
    double sum_ = 0.0, max_ = 0.0;
};

} // namespace p3fes::app
