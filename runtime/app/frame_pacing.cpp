#include "frame_pacing.h"

#include <algorithm>
#include <cmath>

namespace p3fes::app {

int display_lock_ratio(double refresh_s, double guest_vblank_s, double tol) {
    if (!(refresh_s > 0.0) || !(guest_vblank_s > 0.0)) return 0;
    const double k = guest_vblank_s / refresh_s;
    const double r = std::round(k);
    if (r < 1.0 || r > 8.0) return 0;
    return std::fabs(k - r) / r <= tol ? static_cast<int>(r) : 0;
}

double present_phase_error(double t, double vblank_t, double refresh_s) {
    if (!(refresh_s > 0.0)) return 0.0;
    double x = (t - vblank_t) / refresh_s;  // refreshes since that vblank
    x -= std::floor(x);                     // [0, 1): where in the interval
    x -= 0.5;                               // [-0.5, 0.5): 0 = the middle
    return x;
}

double FramePacer::delay(double virt_s, double wall_s) {
    if (!anchored_) {
        anchored_ = true;
        offset_ = wall_s - virt_s * scale_;
        return 0.0;
    }
    const double d = target(virt_s) - wall_s;
    if (d < -cfg_.max_debt_s) {
        // Keep exactly the limit, whatever put us there (a slow stretch or a stall): a host that stays slow runs
        // without waits (re-anchoring to zero debt would make the next light slice idle while the game is below
        // full speed), and one that recovers catches up at most max_debt_s, its presents spaced by
        // schedule_present.
        ++resyncs_;
        offset_ = wall_s - virt_s * scale_ - cfg_.max_debt_s;
        dropped_ += -d - cfg_.max_debt_s;
        return 0.0;
    }
    return d > 0.0 ? d : 0.0;
}

double FramePacer::schedule_present(double virt_s, double wall_s, std::uint64_t vblanks_since_last) {
    double at = present_at(virt_s);
    // Never closer to the previous present than the guest vblanks between them: while the host catches up a debt
    // the frames keep their cadence instead of bunching.
    // (0.1 ms short per frame: after an overload the presents drift back onto the timed grid over a few seconds.)
    if (have_last_ && vblanks_since_last)
        at = std::max(at, last_present_ + static_cast<double>(vblanks_since_last) * kGuestVblankS * scale_ - 0.0001);
    last_present_ = std::max(at, wall_s);  // a time in the past presents at once, i.e. now
    have_last_ = true;
    return at;
}

void FramePacer::set_scale(double scale, double virt_s) {
    if (!(scale > 0.0)) return;
    if (anchored_) offset_ += virt_s * (scale_ - scale);  // target(virt_s) unchanged
    scale_ = scale;
}

double PresentDelayController::add(double render_s) {
    if (recent_.size() < window_) recent_.push_back(render_s);
    else recent_[next_] = render_s;
    next_ = (next_ + 1) % window_;
    std::vector<double> v = recent_;
    const std::size_t k = std::min(v.size() - 1, (v.size() * 9) / 10);
    std::nth_element(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(k), v.end());
    const double want = base_ + std::clamp(v[k] + 0.001, 0.0, max_extra_);  // +1 ms for the Present itself
    if (want > delay_) {
        delay_ = want;
        lower_for_ = 0;
    } else if (want < delay_ - 0.002) {
        if (++lower_for_ >= hold_) {
            delay_ = want;
            lower_for_ = 0;
        }
    } else {
        lower_for_ = 0;
    }
    return delay_;
}

bool PresentGate::should_present(std::uint64_t flips, std::uint64_t vblank, bool disp_changed) {
    bool present = false;
    if (!primed_) {
        primed_ = true;
        present = true;
        last_flip_vblank_ = vblank;
    } else if (flips != flips_) {
        present = true;
        last_flip_vblank_ = vblank;
    } else if (disp_changed) {
        present = true;
    } else if (vblank - last_flip_vblank_ >= 4 && vblank - last_present_vblank_ >= 2) {
        // Not flipping (a static screen, or drawing into the shown buffer): 30 presents a second.
        present = true;
    }
    flips_ = flips;
    if (present) last_present_vblank_ = vblank;
    return present;
}

void FrameTimeHistogram::add(double ms) {
    if (!(ms >= 0.0)) ms = 0.0;
    const double i = ms * 10.0;
    const int k = i >= kBuckets ? kBuckets : static_cast<int>(i);
    ++b_[static_cast<std::size_t>(k)];
    ++n_;
    sum_ += ms;
    max_ = std::max(max_, ms);
}

double FrameTimeHistogram::percentile(double p) const {
    if (!n_) return 0.0;
    p = std::clamp(p, 0.0, 100.0);
    // The smallest bucket whose cumulative count reaches ceil(p% of n) (at least the first sample).
    const auto want = std::max<std::uint64_t>(1, static_cast<std::uint64_t>(std::ceil(p / 100.0 * static_cast<double>(n_))));
    std::uint64_t c = 0;
    for (int k = 0; k <= kBuckets; ++k) {
        c += b_[static_cast<std::size_t>(k)];
        if (c >= want) return k == kBuckets ? max_ : std::min(max_, (k + 1) / 10.0);
    }
    return max_;
}

std::uint64_t FrameTimeHistogram::above(double ms) const {
    if (ms < 0.0) return n_;
    const double i = std::ceil(ms * 10.0 - 1e-9);
    if (i > kBuckets) return 0;
    std::uint64_t c = 0;
    for (int k = static_cast<int>(i); k <= kBuckets; ++k) c += b_[static_cast<std::size_t>(k)];
    return c;
}

} // namespace p3fes::app
