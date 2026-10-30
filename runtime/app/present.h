// Presentation policy for the windowed host (pure; host_display.h applies it, gs::D3D11Backend draws):
// where the composed GS frame goes in the window, how wall time is paced to virtual time, and the --stats readout.
// None of it reaches the guest: pacing only decides how long the host waits between run slices (ADR-0013 §4).
#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace p3fes::app {

// fit: largest 4:3 rectangle, point-sampled (the default); integer: whole multiples of the frame height, point-
// sampled; smooth: largest 4:3 rectangle, bilinear.
enum class ScaleMode : std::uint8_t { Fit, Integer, Smooth };
bool parse_scale_mode(std::string_view s, ScaleMode& out);
const char* to_string(ScaleMode m);

struct ViewRect {
    int x = 0, y = 0, w = 0, h = 0;
    bool empty() const { return w <= 0 || h <= 0; }
    friend bool operator==(const ViewRect&, const ViewRect&) = default;
};

// Where a frame `src_h` lines tall, shown at the display aspect aspect_w:aspect_h whatever its buffer width (the
// PS2's 640x448 is a 4:3 picture), goes in a client_w x client_h area. Fit/Smooth: the largest rectangle of that
// aspect, centred (pillarbox or letterbox bars). Integer: the largest whole multiple k of the frame height that fits
// with its aspect width round(k * src_h * aspect), so every guest line covers exactly k output lines (the width
// cannot also be whole for a non-square pixel aspect); falls back to Fit when k = 1 does not fit. Empty when a size
// is not positive.
ViewRect display_rect(int client_w, int client_h, int src_h, ScaleMode mode, int aspect_w = 4, int aspect_h = 3);

// Wall-clock pacing: before resuming the guest at virtual time `virt_s`, the host waits until that time's wall
// deadline. The first call anchors virtual time to the wall clock. Falling more than `max_lag_s` behind (a debugger
// break, a window drag, a slow stretch) re-anchors instead of running flat out to catch up.
class Pacer {
public:
    explicit Pacer(double max_lag_s = 0.25) : max_lag_(max_lag_s) {}
    // Seconds to wait (>= 0) at wall time `wall_s` (any fixed origin).
    double delay(double virt_s, double wall_s);
    std::uint64_t resyncs() const { return resyncs_; }

private:
    double max_lag_;
    double offset_ = 0.0;  // wall - virt at the anchor
    bool anchored_ = false;
    std::uint64_t resyncs_ = 0;
};

// The --stats readout: rates over the last interval of wall time.
struct StatsSample {
    double wall_s = 0.0;        // host wall clock (any fixed origin)
    double virt_s = 0.0;        // guest virtual time
    double guest_wall_s = 0.0;  // host time spent running guest code so far (GameHost::wall_seconds)
    std::uint64_t flips = 0, vblanks = 0;
};
struct StatsReport {
    double fps = 0.0;         // GS flips per wall second
    double vps = 0.0;         // VBLANK_STARTs per wall second
    double speed = 0.0;       // virtual seconds per wall second
    double guest_load = 0.0;  // fraction of wall time spent in guest code
    double virt_s = 0.0;  // guest virtual time (since reset)
    double wall_s = 0.0;  // wall time since the first sample
};
class StatsMeter {
public:
    explicit StatsMeter(double interval_s = 1.0) : interval_(interval_s) {}
    // Primes on the first call; afterwards true + `out` whenever at least the interval has passed since the last
    // report.
    bool update(const StatsSample& s, StatsReport& out);

private:
    double interval_;
    bool primed_ = false;
    StatsSample first_{}, last_{};
};
// "30.0 fps | 59.9 vblank/s | virtual 12.345 s | wall 12.351 s | speed 100.0% | guest 62%"
std::string format_stats(const StatsReport& r);

} // namespace p3fes::app
