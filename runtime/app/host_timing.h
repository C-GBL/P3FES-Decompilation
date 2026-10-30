// Win32 timing services for frame pacing (windowed runs; docs/ANALYSIS/31_frame_pacing.md): the display's refresh
// timing from DWM, the system timer resolution and the guest thread's scheduling. Diagnostics and host policy
// only; nothing here reaches the guest.
#pragma once

#include <string>

namespace p3fes::app {

struct DisplayTiming {
    bool valid = false;
    double refresh_s = 0.0;    // one refresh (DWM's qpcRefreshPeriod)
    double vblank_s = 0.0;     // a recent vblank, QPC seconds (the clock of main.cpp's wall_now)
    double rate_hz = 0.0;      // nominal refresh rate (rateRefresh)
};
// DwmGetCompositionTimingInfo for the desktop (the clock windowed flip-model presents follow).
DisplayTiming query_display_timing();

// timeBeginPeriod(1) for the process (Sleep / timer granularity 1 ms instead of 15.6 ms); undone by the destructor.
class TimerResolution {
public:
    explicit TimerResolution(bool on);
    ~TimerResolution();
    TimerResolution(const TimerResolution&) = delete;
    TimerResolution& operator=(const TimerResolution&) = delete;
    bool active() const { return on_; }

private:
    bool on_ = false;
};

// The calling (guest) thread above normal priority: the host machine's other work (builds, a browser) preempts it
// less often. Returns a description for the log.
std::string boost_guest_thread();

} // namespace p3fes::app
