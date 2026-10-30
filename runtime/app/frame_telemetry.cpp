#include "frame_telemetry.h"

#include <windows.h>

#include <algorithm>
#include <cmath>
#include <intrin.h>

namespace p3fes::app {

namespace {

long long qpc_now() {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return t.QuadPart;
}

std::uint64_t thread_cycles() {
    ULONG64 c = 0;
    QueryThreadCycleTime(GetCurrentThread(), &c);
    return c;
}

bool invariant_tsc() {
    int r[4] = {};
    __cpuid(r, static_cast<int>(0x80000000u));
    if (static_cast<unsigned>(r[0]) < 0x80000007u) return false;
    __cpuid(r, static_cast<int>(0x80000007u));
    return (static_cast<unsigned>(r[3]) >> 8) & 1u;
}

// The zone profiler state of the calling (guest) thread: every read and switch of the telemetry goes through here,
// so a per-thread profiler (track C: prof::cur()) is a one-line change.
prof::State& zone_state() { return prof::g_prof; }

constexpr double kVblankMs = kGuestVblankS * 1000.0;
constexpr unsigned kPresentZone = static_cast<unsigned>(prof::Zone::Present);

// p-th percentile of a small sample (sorted copy).
double pct(std::vector<float> v, double p) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    const std::size_t i = static_cast<std::size_t>(std::ceil(p / 100.0 * static_cast<double>(v.size())));
    return v[std::min(v.size() - 1, i ? i - 1 : 0)];
}

} // namespace

FrameTelemetry::FrameTelemetry(const Options& opt) : opt_(opt) {
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    qpc_hz_ = static_cast<double>(f.QuadPart);
    // TSC rate for the zone ticks and the thread cycle counts: a 5 ms calibration now, refined as the run goes.
    qpc0_ = qpc_now();
    tsc0_ = __rdtsc();
    while (qpc_ms(qpc_now() - qpc0_) < 5.0) YieldProcessor();
    tsc_per_ms_ = static_cast<double>(__rdtsc() - tsc0_) / qpc_ms(qpc_now() - qpc0_);
    prof::State& s = zone_state();
    if (opt_.zones && !s.on) {
        // The zone profiler without a --zones recorder: only the zone times are read (p3fes/prof.h).
        s.tsc = invariant_tsc();
        s.cur = static_cast<std::uint8_t>(prof::Zone::Host);
        s.last = prof::now();
        s.on = true;
        owns_prof_ = true;
    }
    if (s.on) std::copy(std::begin(s.ticks), std::end(s.ticks), std::begin(zone_last_));
    if (!opt_.log_path.empty()) {
        log_ = std::fopen(opt_.log_path.c_str(), "w");
        if (log_) {
            log_buf_.resize(1u << 18);
            std::setvbuf(log_, log_buf_.data(), _IOFBF, log_buf_.size());
            std::fprintf(log_, "flip,vblank,guest_vblanks,slices,work_ms,cpu_ms,wait_ms,interval_ms,present_interval_ms,refreshes,late_ms,exec_ms,queue_ms,render_ms,present_call_ms,merged,"
                               "audio_waits,audio_wait_ms,underruns,resyncs,audio_queue_ms");
            for (unsigned z = 0; z < prof::kZones; ++z) std::fprintf(log_, ",%s", prof::zone_name(z));
            std::fprintf(log_, "\n");
        } else {
            std::fprintf(stderr, "p3fes: frame-time: cannot write %s\n", opt_.log_path.c_str());
        }
    }
}

FrameTelemetry::~FrameTelemetry() {
    finish();
    if (owns_prof_) zone_state().on = false;
}

double FrameTelemetry::qpc_ms(long long ticks) const { return static_cast<double>(ticks) * 1000.0 / qpc_hz_; }

double FrameTelemetry::tsc_ms(std::uint64_t ticks) const {
    return tsc_per_ms_ > 0.0 ? static_cast<double>(ticks) / tsc_per_ms_ : 0.0;
}

void FrameTelemetry::slice_begin() {
    t_begin_ = qpc_now();
    t_wait_begin_ = t_wait_end_ = 0;
    cyc_begin_ = thread_cycles();
}

void FrameTelemetry::wait_begin() { t_wait_begin_ = qpc_now(); }
void FrameTelemetry::wait_end() { t_wait_end_ = qpc_now(); }

void FrameTelemetry::slice_close(std::uint64_t vblank, std::uint64_t flips, const FrameEvents& ev) {
    const long long now = qpc_now();
    if (!t_begin_) return;
    // Refine the TSC rate over the whole run (> 1 s in).
    const double run_ms = qpc_ms(now - qpc0_);
    if (run_ms > 1000.0) tsc_per_ms_ = static_cast<double>(__rdtsc() - tsc0_) / run_ms;
    const double wait = (t_wait_begin_ && t_wait_end_) ? qpc_ms(t_wait_end_ - t_wait_begin_) : 0.0;
    cur_.work_ms += qpc_ms(now - t_begin_) - wait;
    cur_.wait_ms += wait;
    cur_.cpu_ms += tsc_ms(thread_cycles() - cyc_begin_);
    ++cur_.slices;
    prof::State& s = zone_state();
    if (s.on) {
        prof::switch_to(s.cur);  // charge the current zone up to now
        for (unsigned z = 0; z < prof::kZones; ++z) {
            double ms = s.tsc ? tsc_ms(s.ticks[z] - zone_last_[z]) : static_cast<double>(s.ticks[z] - zone_last_[z]) / 1e6;
            if (z == kPresentZone) ms = std::max(0.0, ms - wait);  // the pacing wait runs in the present zone
            cur_.zone_ms[z] += static_cast<float>(ms);
            zone_last_[z] = s.ticks[z];
        }
    }
    t_begin_ = 0;
    ev_now_ = ev;
    if (!ev_primed_) {
        ev_primed_ = true;
        ev_last_ = ev;
    }
    if (!have_flip_) {
        // The first slice: no frame to close yet.
        have_flip_ = true;
        last_flip_ = flips;
        last_flip_vblank_ = vblank;
        cur_ = Frame{};
        return;
    }
    if (flips == last_flip_) return;
    cur_.flip = flips;
    cur_.vblank = vblank;
    cur_.guest_vblanks = static_cast<std::uint32_t>(vblank - last_flip_vblank_);
    cur_.merged = ev.merged - ev_last_.merged;
    cur_.audio_waits = ev.audio_waits - ev_last_.audio_waits;
    cur_.audio_wait_ms = ev.audio_wait_ms - ev_last_.audio_wait_ms;
    cur_.underruns = ev.underruns - ev_last_.underruns;
    cur_.resyncs = ev.resyncs - ev_last_.resyncs;
    cur_.audio_queued_ms = ev.audio_queued_ms;
    ev_last_ = ev;
    last_flip_ = flips;
    last_flip_vblank_ = vblank;
    pending_.push_back(cur_);
    cur_ = Frame{};
    // A frame whose present never comes (software fallback, no window) is finished without one.
    while (pending_.size() > 32) {
        finalize(pending_.front());
        pending_.pop_front();
    }
}

void FrameTelemetry::presents(const std::vector<gs::PresentRecord>& recs) {
    for (const gs::PresentRecord& r : recs) {
        ++presents_;
        // Every present (the display rate, decoupled from the game's): intervals and the last second's count.
        if (last_any_present_qpc_) h_display_.add(qpc_ms(r.present_qpc - last_any_present_qpc_));
        last_any_present_qpc_ = r.present_qpc;
        recent_presents_.push_back(r.present_qpc);
        while (!recent_presents_.empty() && qpc_ms(r.present_qpc - recent_presents_.front()) > 1000.0) recent_presents_.pop_front();
        if (r.target_qpc) {
            ++timed_;
            if (r.late) ++late_;
        }
        if (r.tag == last_present_tag_ && new_presents_) continue;  // the same guest frame again
        last_present_tag_ = r.tag;
        ++new_presents_;
        double interval = -1.0;
        if (last_new_present_qpc_) interval = qpc_ms(r.present_qpc - last_new_present_qpc_);
        last_new_present_qpc_ = r.present_qpc;
        int refreshes = -1;
        double shown = -1.0;  // when the display showed it, since the previous new frame (DXGI)
        if (r.sync_qpc) {
            if (have_sync_) {
                refreshes = static_cast<int>(r.sync_refresh - last_sync_refresh_);
                shown = qpc_ms(r.sync_qpc - last_sync_qpc_);
                ++refresh_hist_[std::clamp(refreshes, 0, 7)];
            }
            have_sync_ = true;
            last_sync_qpc_ = r.sync_qpc;
            last_sync_refresh_ = r.sync_refresh;
        } else {
            have_sync_ = false;
        }
        if (r.target_qpc) {
            // Late: the picture was ready only after its time. On time: how precisely the render thread hit it.
            const double off = qpc_ms(r.present_qpc - r.target_qpc);
            (r.late ? h_late_ : h_timer_).add(off > 0.0 ? off : 0.0);
        }
        // Frames older than this present had none of their own (merged away, or no new frame was shown).
        while (!pending_.empty() && pending_.front().flip < r.tag) {
            finalize(pending_.front());
            pending_.pop_front();
        }
        if (!pending_.empty() && pending_.front().flip == r.tag) {
            Frame f = pending_.front();
            pending_.pop_front();
            f.presented = true;
            // What the player saw: the display's own times when the swap chain reported them, else the presents'.
            f.present_interval_ms = interval;
            f.interval_ms = shown >= 0.0 ? shown : interval;
            f.refreshes = refreshes;
            f.late_ms = (r.late && r.present_qpc > r.target_qpc) ? qpc_ms(r.present_qpc - r.target_qpc) : 0.0;
            f.ready_late = r.late;
            f.exec_ms = r.exec_ms;
            if (r.submit_qpc && r.dequeue_qpc) f.queue_ms = qpc_ms(r.dequeue_qpc - r.submit_qpc);
            if (r.dequeue_qpc && r.ready_qpc) f.render_ms = qpc_ms(r.ready_qpc - r.dequeue_qpc);
            if (r.present_qpc && r.return_qpc) f.call_ms = qpc_ms(r.return_qpc - r.present_qpc);
            finalize(f);
        } else if (interval >= 0.0) {
            h_interval_.add(shown >= 0.0 ? shown : interval);  // a present without its frame record (e.g. the first ones)
        }
        if (interval >= 0.0) h_present_.add(interval);
    }
}

std::string FrameTelemetry::classify(const Frame& f) const {
    const double budget = std::max<std::uint32_t>(2, f.guest_vblanks) * kVblankMs;
    if (f.guest_vblanks > 2 && f.interval_ms <= f.guest_vblanks * kVblankMs + 2.0) return "guest";
    if (f.resyncs) return "pacing";
    if (f.work_ms > budget) {
        const double off = f.work_ms - f.cpu_ms;
        return (off > 5.0 && off > 0.3 * f.work_ms) ? "load" : "host";
    }
    if (f.late_ms > 0.5 || f.ready_late) return "present";
    return "display";
}

std::string FrameTelemetry::describe(const Frame& f) const {
    char b[512];
    int n = std::snprintf(b, sizeof b, "flip %llu vblank %llu: %.1f ms (%u vblanks) -- work %.1f ms, cpu %.1f, wait %.1f",
                          static_cast<unsigned long long>(f.flip), static_cast<unsigned long long>(f.vblank), f.interval_ms,
                          f.guest_vblanks, f.work_ms, f.cpu_ms, f.wait_ms);
    // The top four zones.
    unsigned idx[prof::kZones];
    for (unsigned z = 0; z < prof::kZones; ++z) idx[z] = z;
    std::sort(idx, idx + prof::kZones, [&f](unsigned a, unsigned c) { return f.zone_ms[a] > f.zone_ms[c]; });
    for (unsigned i = 0; i < 4 && n > 0 && n < static_cast<int>(sizeof b); ++i) {
        if (f.zone_ms[idx[i]] < 0.5f) break;
        n += std::snprintf(b + n, sizeof b - n, "%s%s %.1f", i ? ", " : " | ", prof::zone_name(idx[i]), f.zone_ms[idx[i]]);
    }
    if (n > 0 && n < static_cast<int>(sizeof b) && f.late_ms > 0.0)
        n += std::snprintf(b + n, sizeof b - n, " | present late %.1f ms%s (render: queue %.1f, exec+compose %.1f, Present %.1f; lists %.1f ms)",
                           f.late_ms, f.ready_late ? ", picture ready late" : "", f.queue_ms, f.render_ms, f.call_ms, f.exec_ms);
    if (n > 0 && n < static_cast<int>(sizeof b) && f.merged)
        n += std::snprintf(b + n, sizeof b - n, " | %llu lists merged", static_cast<unsigned long long>(f.merged));
    if (n > 0 && n < static_cast<int>(sizeof b) && (f.audio_waits || f.underruns))
        n += std::snprintf(b + n, sizeof b - n, " | audio: %llu waits %.1f ms, %llu underruns", static_cast<unsigned long long>(f.audio_waits),
                           f.audio_wait_ms, static_cast<unsigned long long>(f.underruns));
    if (n > 0 && n < static_cast<int>(sizeof b) && f.resyncs) n += std::snprintf(b + n, sizeof b - n, " | pacer re-anchored");
    if (n > 0 && n < static_cast<int>(sizeof b) && f.refreshes > 0)
        std::snprintf(b + n, sizeof b - n, " | shown %d refreshes", f.refreshes);
    return b;
}

void FrameTelemetry::finalize(Frame& f) {
    ++frames_;
    h_work_.add(f.work_ms);
    h_cpu_.add(f.cpu_ms);
    ++cadence_hist_[std::min<std::uint32_t>(f.guest_vblanks, 7)];
    if (f.work_ms > std::max<std::uint32_t>(2, f.guest_vblanks) * kVblankMs) ++over_budget_;
    if (f.interval_ms >= 0.0) {
        h_interval_.add(f.interval_ms);
        if (f.interval_ms > 50.5) ++over_50_;
        if (f.interval_ms > opt_.hitch_ms) {
            ++hitch_count_;
            // Keep the 64 worst for the report.
            Hitch h{f, classify(f)};
            if (hitches_.size() < 64) {
                hitches_.push_back(h);
            } else {
                auto w = std::min_element(hitches_.begin(), hitches_.end(),
                                          [](const Hitch& a, const Hitch& c) { return a.f.interval_ms < c.f.interval_ms; });
                if (w->f.interval_ms < f.interval_ms) *w = h;
            }
        }
    }
    recent_.push_back(f);
    while (recent_.size() > 300) recent_.pop_front();
    if (log_) {
        std::fprintf(log_, "%llu,%llu,%u,%u,%.3f,%.3f,%.3f,%.3f,%.3f,%d,%.3f,%.3f,%.3f,%.3f,%.3f,%llu,%llu,%.3f,%llu,%llu,%.1f",
                     static_cast<unsigned long long>(f.flip), static_cast<unsigned long long>(f.vblank), f.guest_vblanks, f.slices,
                     f.work_ms, f.cpu_ms, f.wait_ms, f.interval_ms, f.present_interval_ms, f.refreshes, f.late_ms, f.exec_ms, f.queue_ms, f.render_ms, f.call_ms,
                     static_cast<unsigned long long>(f.merged), static_cast<unsigned long long>(f.audio_waits), f.audio_wait_ms,
                     static_cast<unsigned long long>(f.underruns), static_cast<unsigned long long>(f.resyncs), f.audio_queued_ms);
        for (unsigned z = 0; z < prof::kZones; ++z) std::fprintf(log_, ",%.2f", f.zone_ms[z]);
        std::fprintf(log_, "\n");
    }
}

FrameTelemetry::Live FrameTelemetry::live() const {
    Live l;
    l.frames = frames_;
    l.hitches = hitch_count_;
    l.late = late_;
    l.audio_ms = ev_now_.audio_queued_ms;
    l.ratio = ev_now_.audio_ratio;
    l.underruns = ev_now_.underruns;
    l.pacing = opt_.pacing;
    l.display_fps = recent_presents_.size() > 1
                        ? static_cast<double>(recent_presents_.size() - 1) * 1000.0 / std::max(1.0, qpc_ms(recent_presents_.back() - recent_presents_.front()))
                        : 0.0;
    const std::size_t from = recent_.size() > 240 ? recent_.size() - 240 : 0;
    std::vector<float> iv, wk;
    double t = 0.0;
    std::size_t in_last_s = 0;
    for (std::size_t i = from; i < recent_.size(); ++i) {
        l.intervals.push_back(static_cast<float>(std::max(0.0, recent_[i].interval_ms)));
        l.work.push_back(static_cast<float>(recent_[i].work_ms));
    }
    // Last ~5 s for the percentiles, the newest frames up to 1 s for the rate.
    double t_rate = 0.0;
    for (std::size_t i = recent_.size(); i-- > 0;) {
        const Frame& f = recent_[i];
        if (f.interval_ms < 0.0) continue;
        if (t < 1000.0) {
            ++in_last_s;
            t_rate = t + f.interval_ms;
        }
        t += f.interval_ms;
        iv.push_back(static_cast<float>(f.interval_ms));
        wk.push_back(static_cast<float>(f.work_ms));
        if (t >= 5000.0) break;
    }
    if (!iv.empty()) {
        l.p50 = pct(iv, 50);
        l.p99 = pct(iv, 99);
        l.max = *std::max_element(iv.begin(), iv.end());
        l.work_p50 = pct(wk, 50);
        l.work_p95 = pct(wk, 95);
        l.fps = t_rate > 0.0 ? static_cast<double>(in_last_s) * 1000.0 / t_rate : 0.0;
    }
    return l;
}

std::string FrameTelemetry::summary() const {
    std::string s;
    char b[512];
    auto line = [&](const char* fmt, auto... args) {
        std::snprintf(b, sizeof b, fmt, args...);
        s += "p3fes: frame-time: ";
        s += b;
        s += "\n";
    };
    line("%llu guest frames, %llu presents (%llu of new frames; %llu timed, %llu late), pacing %s",
         static_cast<unsigned long long>(frames_), static_cast<unsigned long long>(presents_),
         static_cast<unsigned long long>(new_presents_), static_cast<unsigned long long>(timed_), static_cast<unsigned long long>(late_),
         opt_.pacing.c_str());
    const FrameTimeHistogram& h = h_interval_;
    line("new-frame interval ms (as displayed, DXGI; else as presented): p50 %.1f  p95 %.1f  p99 %.1f  max %.1f  mean %.2f | hitches (> %.1f ms) %llu, > 50.5 ms %llu",
         h.percentile(50), h.percentile(95), h.percentile(99), h.max(), h.mean(), opt_.hitch_ms,
         static_cast<unsigned long long>(hitch_count_), static_cast<unsigned long long>(over_50_));
    line("present-to-present ms (render thread): p50 %.1f  p95 %.1f  p99 %.1f  max %.1f | > %.1f ms: %llu", h_present_.percentile(50),
         h_present_.percentile(95), h_present_.percentile(99), h_present_.max(), opt_.hitch_ms,
         static_cast<unsigned long long>(h_present_.above(opt_.hitch_ms + 0.05)));
    std::uint64_t shown = 0;
    for (std::uint64_t c : refresh_hist_) shown += c;
    if (shown)
        line("display refreshes per frame (DXGI frame statistics, %llu frames): 1: %llu  2: %llu  3: %llu  4: %llu  5+: %llu",
             static_cast<unsigned long long>(shown), static_cast<unsigned long long>(refresh_hist_[1]),
             static_cast<unsigned long long>(refresh_hist_[2]), static_cast<unsigned long long>(refresh_hist_[3]),
             static_cast<unsigned long long>(refresh_hist_[4]),
             static_cast<unsigned long long>(refresh_hist_[5] + refresh_hist_[6] + refresh_hist_[7]));
    else
        line("display refreshes per frame: unknown (the swap chain reported no frame statistics)");
    line("host work per frame ms: p50 %.1f  p95 %.1f  p99 %.1f  max %.1f | over budget %llu | guest-thread cpu ms: p50 %.1f  p95 %.1f  p99 %.1f",
         h_work_.percentile(50), h_work_.percentile(95), h_work_.percentile(99), h_work_.max(),
         static_cast<unsigned long long>(over_budget_), h_cpu_.percentile(50), h_cpu_.percentile(95), h_cpu_.percentile(99));
    line("display (every present, the display rate): %llu presents, interval ms p50 %.1f  p95 %.1f  p99 %.1f  max %.1f",
         static_cast<unsigned long long>(presents_), h_display_.percentile(50), h_display_.percentile(95), h_display_.percentile(99),
         h_display_.max());
    line("15 ms budget (the 60 fps target): host work per frame over 15 ms in %llu of %llu frames (%.1f %%), p99 %.1f ms",
         static_cast<unsigned long long>(h_work_.above(15.0)), static_cast<unsigned long long>(h_work_.count()),
         h_work_.count() ? 100.0 * static_cast<double>(h_work_.above(15.0)) / static_cast<double>(h_work_.count()) : 0.0,
         h_work_.percentile(99));
    line("guest vblanks per flip: 1: %llu  2: %llu  3: %llu  4: %llu  5+: %llu (above 2 = the game's own slow frames, as on the PS2)",
         static_cast<unsigned long long>(cadence_hist_[1]), static_cast<unsigned long long>(cadence_hist_[2]),
         static_cast<unsigned long long>(cadence_hist_[3]), static_cast<unsigned long long>(cadence_hist_[4]),
         static_cast<unsigned long long>(cadence_hist_[5] + cadence_hist_[6] + cadence_hist_[7]));
    if (h_late_.count())
        line("late presents (picture ready after its time): %llu, by ms p50 %.1f  p99 %.1f  max %.1f",
             static_cast<unsigned long long>(h_late_.count()), h_late_.percentile(50), h_late_.percentile(99), h_late_.max());
    if (h_timer_.count())
        line("on-time presents fire after their time by ms: p50 %.2f  p99 %.2f  max %.2f (render-thread timer precision)",
             h_timer_.percentile(50), h_timer_.percentile(99), h_timer_.max());
    line("audio: queue %.0f ms, ratio %.4f, underruns %llu, back-pressure waits %llu (%.1f ms); pacer re-anchors %llu",
         ev_now_.audio_queued_ms, ev_now_.audio_ratio, static_cast<unsigned long long>(ev_now_.underruns),
         static_cast<unsigned long long>(ev_now_.audio_waits), ev_now_.audio_wait_ms, static_cast<unsigned long long>(ev_now_.resyncs));
    if (!hitches_.empty()) {
        std::vector<Hitch> hs = hitches_;
        std::sort(hs.begin(), hs.end(), [](const Hitch& a, const Hitch& c) { return a.f.interval_ms > c.f.interval_ms; });
        std::uint64_t by[6] = {};
        static const char* kCls[6] = {"guest", "pacing", "load", "host", "present", "display"};
        for (const Hitch& x : hs)
            for (int i = 0; i < 6; ++i)
                if (x.cls == kCls[i]) ++by[i];
        line("worst %zu hitches by cause: guest %llu, pacing %llu, load %llu, host %llu, present %llu, display %llu", hs.size(),
             static_cast<unsigned long long>(by[0]), static_cast<unsigned long long>(by[1]), static_cast<unsigned long long>(by[2]),
             static_cast<unsigned long long>(by[3]), static_cast<unsigned long long>(by[4]), static_cast<unsigned long long>(by[5]));
        for (std::size_t i = 0; i < hs.size() && i < 20; ++i) line("  [%s] %s", hs[i].cls.c_str(), describe(hs[i].f).c_str());
    }
    return s;
}

void FrameTelemetry::finish() {
    while (!pending_.empty()) {
        finalize(pending_.front());
        pending_.pop_front();
    }
    if (log_) {
        std::fclose(log_);
        log_ = nullptr;
    }
}

} // namespace p3fes::app
