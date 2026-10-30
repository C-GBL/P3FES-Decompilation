// Frame pacing policy (runtime/app/frame_pacing.h, docs/ANALYSIS/31_frame_pacing.md): the display lock ratio, the
// present phase, the pacer's mapping / debt / re-anchor rules, the timed-present guarantee (a frame whose two
// slices fit 33.37 ms is presented on time, whatever the split), the present gate and the histogram.
#include "doctest.h"

#include <cstdint>
#include <random>
#include <vector>

#include "frame_pacing.h"

using namespace p3fes::app;

TEST_CASE("display lock ratio: one guest vblank = k refreshes only for multiples of 59.94 Hz") {
    CHECK(display_lock_ratio(1.0 / 60.0) == 1);
    CHECK(display_lock_ratio(1001.0 / 60000.0) == 1);
    CHECK(display_lock_ratio(1.0 / 59.951) == 1);
    CHECK(display_lock_ratio(1.0 / 120.0) == 2);
    CHECK(display_lock_ratio(1.0 / 119.88) == 2);
    CHECK(display_lock_ratio(1.0 / 240.0) == 4);
    CHECK(display_lock_ratio(1.0 / 144.0) == 0);
    CHECK(display_lock_ratio(1.0 / 75.0) == 0);
    CHECK(display_lock_ratio(1.0 / 50.0) == 0);
    CHECK(display_lock_ratio(1.0 / 165.0) == 0);
    CHECK(display_lock_ratio(0.0) == 0);
    CHECK(display_lock_ratio(1.0 / 61.0) == 0);  // 1.7 % off: no lock
}

TEST_CASE("present phase error: 0 halfway between vblanks, wraps at +-0.5") {
    const double r = 1.0 / 60.0;
    CHECK(present_phase_error(10.0 + 0.5 * r, 10.0, r) == doctest::Approx(0.0));
    CHECK(present_phase_error(10.0 + 0.75 * r, 10.0, r) == doctest::Approx(0.25));
    CHECK(present_phase_error(10.0 + 0.25 * r, 10.0, r) == doctest::Approx(-0.25));
    CHECK(present_phase_error(10.0 + 7.5 * r, 10.0, r) == doctest::Approx(0.0));   // any later interval
    CHECK(present_phase_error(10.0 - 2.5 * r, 10.0, r) == doctest::Approx(0.0));   // or earlier
    CHECK(present_phase_error(10.0 + 0.001 * r, 10.0, r) == doctest::Approx(-0.499));
}

TEST_CASE("FramePacer: anchor, waits, no drift, re-anchor past the debt limit") {
    FramePacer p;  // max debt 2 vblanks
    const double vb = kGuestVblankS;
    CHECK(p.delay(0.0, 100.0) == 0.0);
    CHECK(p.delay(vb, 100.004) == doctest::Approx(vb - 0.004));
    // Behind by one vblank: no wait, no re-anchor (the debt is caught up by later light slices).
    CHECK(p.delay(2 * vb, 100.0 + 3 * vb) == 0.0);
    CHECK(p.resyncs() == 0);
    CHECK(p.delay(10 * vb, 100.0 + 9 * vb) == doctest::Approx(vb));
    // A 200 ms stall in one slice (a load, a window drag): re-anchor two vblanks behind (at most that is caught up).
    CHECK(p.delay(11 * vb, 100.0 + 11 * vb + 0.2) == 0.0);
    CHECK(p.resyncs() == 1);
    CHECK(p.dropped_s() == doctest::Approx(0.2 - 2 * vb));
    CHECK(p.target(12 * vb) == doctest::Approx(100.0 + 10 * vb + 0.2));
    // A slow slice of 4 vblanks (the game below full speed, not a stall): keep the limit, so no idle follows.
    CHECK(p.delay(12 * vb, 100.0 + 15 * vb + 0.2) == 0.0);
    CHECK(p.resyncs() == 2);
    CHECK(p.target(13 * vb) == doctest::Approx(100.0 + 14 * vb + 0.2));
}

TEST_CASE("FramePacer: sustained overload keeps the debt at the limit and never waits") {
    FramePacer p;
    const double vb = kGuestVblankS;
    double wall = 0.0, waited = 0.0;
    p.delay(0.0, wall);
    for (int v = 1; v <= 600; ++v) {
        wall += 1.6 * vb;  // every slice 60 % over its budget
        const double d = p.delay(v * vb, wall);
        waited += d;
        wall += d;
    }
    CHECK(waited == 0.0);
    CHECK(p.resyncs() > 0);
    CHECK(wall - p.target(600 * vb) == doctest::Approx(2 * vb));  // exactly the limit behind
    // Recovered (light slices): the two vblanks of debt are caught up, then the waits resume.
    for (int v = 601; v <= 603; ++v) {
        wall += 0.2 * vb;
        wall += p.delay(v * vb, wall);
    }
    CHECK(wall == doctest::Approx(p.target(603 * vb)));
}

TEST_CASE("FramePacer: a scale change keeps the current deadline; shift moves the mapping") {
    FramePacer p;
    p.delay(0.0, 50.0);
    const double v = 1.0;
    const double before = p.target(v);
    p.set_scale(1.001, v);
    CHECK(p.target(v) == doctest::Approx(before));
    CHECK(p.target(v + 1.0) - p.target(v) == doctest::Approx(1.001));
    p.shift(0.002);
    CHECK(p.target(v) == doctest::Approx(before + 0.002));
    CHECK(p.present_at(v) == doctest::Approx(before + 0.002 + kGuestVblankS));
}

namespace {

// The host loop of main.cpp in virtual form: per guest frame a non-flip slice (cost a) and a flip slice (cost b);
// the flip slice submits its list at its end and the present is timed at present_at(end of that slice).
struct SimResult {
    int late = 0;
    std::vector<double> presents;
};
SimResult simulate(const std::vector<std::pair<double, double>>& frames, FramePacer& p, double start = 1000.0) {
    SimResult r;
    double wall = start, virt = 0.0;
    p.delay(virt, wall);
    for (const auto& [a, b] : frames) {
        wall += a;
        virt += kGuestVblankS;
        wall += p.delay(virt, wall);
        wall += b;
        virt += kGuestVblankS;
        const double submit = wall;
        const double wait = p.delay(virt, wall);  // main.cpp computes the wait first, then the present time
        const double at = p.schedule_present(virt, submit, r.presents.empty() ? 0 : 2);
        if (submit > at + 1e-9) ++r.late;
        r.presents.push_back(at > submit ? at : submit);
        wall += wait;
    }
    return r;
}

} // namespace

TEST_CASE("timed presents: every frame within 33.37 ms is on time, however the work splits; the cadence is exact") {
    std::mt19937 rng(12345);
    std::uniform_real_distribution<double> total(0.0, 0.0333), split(0.0, 1.0);
    std::vector<std::pair<double, double>> frames;
    for (int i = 0; i < 20000; ++i) {
        const double t = total(rng), s = split(rng);
        frames.emplace_back(t * s, t * (1.0 - s));
    }
    // Adversarial splits too: all the work in one slice, alternating.
    for (int i = 0; i < 2000; ++i) frames.emplace_back(i & 1 ? 0.0333 : 0.0, i & 1 ? 0.0 : 0.0333);
    FramePacer p;
    const SimResult r = simulate(frames, p);
    CHECK(r.late == 0);
    CHECK(p.resyncs() == 0);
    for (std::size_t i = 1; i < r.presents.size(); ++i) REQUIRE(r.presents[i] - r.presents[i - 1] == doctest::Approx(kGuestFrameS).epsilon(1e-6));
}

TEST_CASE("timed presents: a stall re-anchors once, then the cadence resumes without a fast-forward burst") {
    std::vector<std::pair<double, double>> frames(300, {0.005, 0.010});
    frames[50] = {0.005, 0.300};  // a 300 ms load in the flip slice
    FramePacer p;
    const SimResult r = simulate(frames, p);
    CHECK(p.resyncs() == 1);
    // The stalled frame presents late (at once); two vblanks of the debt are caught up by the light frames after it,
    // no two presents are ever closer than one guest frame (less the 0.1 ms drift allowance), and the cadence ends
    // exactly on the grid again.
    CHECK(r.late == 1);
    int long_intervals = 0;
    for (std::size_t i = 1; i < r.presents.size(); ++i) {
        const double d = r.presents[i] - r.presents[i - 1];
        CHECK(d >= kGuestFrameS - 0.00011);
        if (d > kGuestFrameS + 0.001) {
            ++long_intervals;
            CHECK(d > 0.29);
        }
    }
    CHECK(long_intervals == 1);
    for (std::size_t i = r.presents.size() - 20; i < r.presents.size(); ++i)
        CHECK(r.presents[i] - r.presents[i - 1] == doctest::Approx(kGuestFrameS).epsilon(1e-6));
}

TEST_CASE("timed presents: after sustained overload the presents drift back onto the grid without bunching") {
    std::vector<std::pair<double, double>> frames(100, {0.025, 0.025});  // 50 ms frames: the game below full speed
    frames.insert(frames.end(), 300, {0.005, 0.010});
    FramePacer p;
    const SimResult r = simulate(frames, p);
    for (std::size_t i = 1; i < r.presents.size(); ++i) CHECK(r.presents[i] - r.presents[i - 1] >= kGuestFrameS - 0.00011);
    for (std::size_t i = r.presents.size() - 20; i < r.presents.size(); ++i)
        CHECK(r.presents[i] - r.presents[i - 1] == doctest::Approx(kGuestFrameS).epsilon(1e-6));
}

TEST_CASE("PresentDelayController: one vblank + the render p90, up at once, down only after the hold") {
    PresentDelayController c(kGuestVblankS, kGuestVblankS, 60, 300);
    for (int i = 0; i < 60; ++i) c.add(0.001);
    CHECK(c.delay() == doctest::Approx(kGuestVblankS + 0.002));
    // The title's heavy backdrop: 11 ms renders. Ten of sixty are enough to raise the p90 at once.
    for (int i = 0; i < 10; ++i) c.add(0.011);
    CHECK(c.delay() == doctest::Approx(kGuestVblankS + 0.012));
    // Capped at one more vblank.
    for (int i = 0; i < 60; ++i) c.add(0.050);
    CHECK(c.delay() == doctest::Approx(2 * kGuestVblankS));
    // Light again: held for 300 presents, then down in one step.
    for (int i = 0; i < 299 + 54; ++i) c.add(0.001);
    CHECK(c.delay() == doctest::Approx(2 * kGuestVblankS));
    for (int i = 0; i < 10; ++i) c.add(0.001);
    CHECK(c.delay() == doctest::Approx(kGuestVblankS + 0.002));
}

TEST_CASE("PresentGate: one present per guest frame, 30 Hz while the guest does not flip") {
    PresentGate g;
    CHECK(g.should_present(0, 1, false));  // the first slice
    // 30 fps: flips every second vblank.
    std::uint64_t flips = 0;
    int presents = 0;
    for (std::uint64_t vb = 2; vb < 202; ++vb) {
        if (vb % 2 == 1) ++flips;
        presents += g.should_present(flips, vb, false) ? 1 : 0;
    }
    CHECK(presents == 100);
    // The guest stops flipping (a static screen): a present every second vblank from the fourth on.
    int still = 0;
    for (std::uint64_t vb = 202; vb < 242; ++vb) still += g.should_present(flips, vb, false) ? 1 : 0;
    CHECK(still == 19);  // vblanks 205, 207, ..., 241 (the last flip was at 201)
    // A display-register change presents at once.
    CHECK(g.should_present(flips, 243, true));
}

TEST_CASE("FrameTimeHistogram percentiles") {
    FrameTimeHistogram h;
    CHECK(h.percentile(50) == 0.0);
    for (int i = 0; i < 98; ++i) h.add(33.36);
    h.add(50.0);
    h.add(700.0);  // overflow bucket
    CHECK(h.count() == 100);
    CHECK(h.percentile(50) == doctest::Approx(33.4));
    CHECK(h.percentile(98) == doctest::Approx(33.4));
    CHECK(h.percentile(99) == doctest::Approx(50.1));
    CHECK(h.percentile(100) == doctest::Approx(700.0));
    CHECK(h.max() == doctest::Approx(700.0));
    CHECK(h.above(34.0) == 2);
    CHECK(h.above(60.0) == 1);
    CHECK(h.mean() == doctest::Approx((98 * 33.36 + 750.0) / 100.0));
}
