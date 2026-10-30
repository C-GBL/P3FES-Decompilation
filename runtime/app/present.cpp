#include "present.h"

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace p3fes::app {

bool parse_scale_mode(std::string_view s, ScaleMode& out) {
    if (s == "fit") out = ScaleMode::Fit;
    else if (s == "integer") out = ScaleMode::Integer;
    else if (s == "smooth") out = ScaleMode::Smooth;
    else return false;
    return true;
}

const char* to_string(ScaleMode m) {
    switch (m) {
    case ScaleMode::Fit: return "fit";
    case ScaleMode::Integer: return "integer";
    case ScaleMode::Smooth: return "smooth";
    }
    return "?";
}

namespace {

ViewRect fit_rect(int cw, int ch, int aw, int ah) {
    ViewRect r;
    // Compare cw/ch with aw/ah in integers: the wider side gets the bars.
    if (static_cast<long long>(cw) * ah > static_cast<long long>(ch) * aw) {
        r.h = ch;
        r.w = static_cast<int>(static_cast<long long>(ch) * aw / ah);
    } else {
        r.w = cw;
        r.h = static_cast<int>(static_cast<long long>(cw) * ah / aw);
    }
    r.x = (cw - r.w) / 2;
    r.y = (ch - r.h) / 2;
    return r;
}

} // namespace

ViewRect display_rect(int client_w, int client_h, int src_h, ScaleMode mode, int aspect_w, int aspect_h) {
    if (client_w <= 0 || client_h <= 0 || src_h <= 0 || aspect_w <= 0 || aspect_h <= 0) return {};
    if (mode == ScaleMode::Integer) {
        for (int k = client_h / src_h; k >= 1; --k) {
            const int h = k * src_h;
            // round(h * aw / ah), half up, in integers
            const int w = static_cast<int>((2LL * h * aspect_w + aspect_h) / (2LL * aspect_h));
            if (w <= client_w) return {(client_w - w) / 2, (client_h - h) / 2, w, h};
        }
    }
    return fit_rect(client_w, client_h, aspect_w, aspect_h);
}

double Pacer::delay(double virt_s, double wall_s) {
    if (!anchored_) {
        anchored_ = true;
        offset_ = wall_s - virt_s;
        return 0.0;
    }
    const double d = virt_s + offset_ - wall_s;
    if (d < -max_lag_) {
        offset_ = wall_s - virt_s;
        ++resyncs_;
        return 0.0;
    }
    return d > 0.0 ? d : 0.0;
}

bool StatsMeter::update(const StatsSample& s, StatsReport& out) {
    if (!primed_) {
        primed_ = true;
        first_ = last_ = s;
        return false;
    }
    const double dw = s.wall_s - last_.wall_s;
    if (dw < interval_ || dw <= 0.0) return false;
    out.fps = static_cast<double>(s.flips - last_.flips) / dw;
    out.vps = static_cast<double>(s.vblanks - last_.vblanks) / dw;
    out.speed = (s.virt_s - last_.virt_s) / dw;
    out.guest_load = std::clamp((s.guest_wall_s - last_.guest_wall_s) / dw, 0.0, 1.0);
    out.virt_s = s.virt_s;
    out.wall_s = s.wall_s - first_.wall_s;
    last_ = s;
    return true;
}

std::string format_stats(const StatsReport& r) {
    char b[192];
    std::snprintf(b, sizeof b, "%.1f fps | %.1f vblank/s | virtual %.3f s | wall %.3f s | speed %.1f%% | guest %.0f%%", r.fps, r.vps,
                  r.virt_s, r.wall_s, r.speed * 100.0, r.guest_load * 100.0);
    return b;
}

} // namespace p3fes::app
