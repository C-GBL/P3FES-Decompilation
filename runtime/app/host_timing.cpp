#include "host_timing.h"

#include <windows.h>
#include <dwmapi.h>
#include <timeapi.h>

namespace p3fes::app {

DisplayTiming query_display_timing() {
    DisplayTiming t;
    DWM_TIMING_INFO info{};
    info.cbSize = sizeof info;
    if (FAILED(DwmGetCompositionTimingInfo(nullptr, &info)) || info.qpcRefreshPeriod == 0) return t;
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    const double hz = static_cast<double>(f.QuadPart);
    t.refresh_s = static_cast<double>(info.qpcRefreshPeriod) / hz;
    t.vblank_s = static_cast<double>(info.qpcVBlank) / hz;
    t.rate_hz = info.rateRefresh.uiDenominator ? static_cast<double>(info.rateRefresh.uiNumerator) / info.rateRefresh.uiDenominator : 0.0;
    t.valid = t.refresh_s > 0.001 && t.refresh_s < 0.1;
    return t;
}

TimerResolution::TimerResolution(bool on) {
    if (on) on_ = timeBeginPeriod(1) == TIMERR_NOERROR;
}

TimerResolution::~TimerResolution() {
    if (on_) timeEndPeriod(1);
}

std::string boost_guest_thread() {
    if (SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL)) return "guest thread above normal";
    return "guest thread priority unchanged";
}

} // namespace p3fes::app
