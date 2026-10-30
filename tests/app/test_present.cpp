// Presentation policy (runtime/app/present.h): letterbox rectangles, pacing, the stats readout.
#include <doctest.h>

#include <cstdlib>
#include <string>

#include "present.h"

using namespace p3fes::app;

namespace {

ViewRect R(int x, int y, int w, int h) { return {x, y, w, h}; }

// A rectangle is inside the client area and centred (to the pixel).
void check_centred(const ViewRect& r, int cw, int ch) {
    CHECK(r.x >= 0);
    CHECK(r.y >= 0);
    CHECK(r.x + r.w <= cw);
    CHECK(r.y + r.h <= ch);
    CHECK(r.x == (cw - r.w) / 2);
    CHECK(r.y == (ch - r.h) / 2);
}

} // namespace

TEST_CASE("display_rect fit: pillarbox in wide areas, letterbox in tall ones, exact at 4:3") {
    CHECK(display_rect(640, 480, 448, ScaleMode::Fit) == R(0, 0, 640, 480));
    CHECK(display_rect(1920, 1080, 448, ScaleMode::Fit) == R(240, 0, 1440, 1080));    // pillarbox
    CHECK(display_rect(800, 800, 448, ScaleMode::Fit) == R(0, 100, 800, 600));        // letterbox
    CHECK(display_rect(2560, 1440, 448, ScaleMode::Fit) == R(320, 0, 1920, 1440));
    CHECK(display_rect(1280, 1024, 448, ScaleMode::Fit) == R(0, 32, 1280, 960));
    CHECK(display_rect(641, 480, 448, ScaleMode::Fit) == R(0, 0, 640, 480));          // odd bar pixel to the right
    CHECK(display_rect(1, 1, 448, ScaleMode::Fit) == R(0, 0, 1, 0));                  // degenerate but in bounds
    // Smooth uses the same rectangle (the filter differs).
    CHECK(display_rect(1920, 1080, 448, ScaleMode::Smooth) == display_rect(1920, 1080, 448, ScaleMode::Fit));
    for (int cw : {320, 640, 799, 1024, 1366, 1920, 3840})
        for (int ch : {200, 448, 480, 768, 1080, 2160}) {
            const ViewRect r = display_rect(cw, ch, 448, ScaleMode::Fit);
            check_centred(r, cw, ch);
            CHECK((r.w == cw || r.h == ch));                     // touches two sides
            CHECK(std::abs(r.w * 3 - r.h * 4) <= 4);              // 4:3 within rounding
        }
}

TEST_CASE("display_rect integer: whole multiples of the frame height, aspect width rounded, Fit fallback") {
    // 448 lines at 4:3 is 597.33 wide.
    CHECK(display_rect(1280, 720, 448, ScaleMode::Integer) == R(341, 136, 597, 448));    // k = 1
    CHECK(display_rect(1920, 1080, 448, ScaleMode::Integer) == R(362, 92, 1195, 896));   // k = 2 (1194.67 -> 1195)
    CHECK(display_rect(2560, 1440, 448, ScaleMode::Integer) == R(384, 48, 1792, 1344));  // k = 3
    CHECK(display_rect(3840, 2160, 448, ScaleMode::Integer) == R(725, 184, 2389, 1792)); // k = 4 (2389.33)
    // Height allows k = 2 but the width does not: k drops to 1.
    CHECK(display_rect(1000, 1000, 448, ScaleMode::Integer) == R(201, 276, 597, 448));
    // Not even k = 1 fits: Fit.
    CHECK(display_rect(640, 400, 448, ScaleMode::Integer) == display_rect(640, 400, 448, ScaleMode::Fit));
    CHECK(display_rect(500, 480, 448, ScaleMode::Integer) == display_rect(500, 480, 448, ScaleMode::Fit));
    // Another frame height (e.g. a 512x224 field picture) scales by its own lines.
    CHECK(display_rect(1920, 1080, 224, ScaleMode::Integer) == R(362, 92, 1195, 896));  // k = 4
    for (int cw : {640, 1024, 1366, 1920, 2560, 3840})
        for (int ch : {448, 480, 768, 1080, 1440, 2160}) {
            const ViewRect r = display_rect(cw, ch, 448, ScaleMode::Integer);
            check_centred(r, cw, ch);
            CHECK(r.h % 448 == 0);
        }
}

TEST_CASE("display_rect: non-positive sizes give an empty rectangle") {
    CHECK(display_rect(0, 480, 448, ScaleMode::Fit).empty());
    CHECK(display_rect(640, 0, 448, ScaleMode::Integer).empty());
    CHECK(display_rect(640, 480, 0, ScaleMode::Fit).empty());
    CHECK(display_rect(-5, 480, 448, ScaleMode::Smooth).empty());
}

TEST_CASE("scale mode names") {
    ScaleMode m{};
    CHECK(parse_scale_mode("integer", m));
    CHECK(m == ScaleMode::Integer);
    CHECK(parse_scale_mode("smooth", m));
    CHECK(m == ScaleMode::Smooth);
    CHECK(parse_scale_mode("fit", m));
    CHECK(m == ScaleMode::Fit);
    CHECK_FALSE(parse_scale_mode("bilinear", m));
    CHECK(std::string(to_string(ScaleMode::Integer)) == "integer");
}

TEST_CASE("pacer: waits for the virtual deadline, never when behind, re-anchors after a stall") {
    Pacer p(0.25);
    CHECK(p.delay(0.0, 100.0) == 0.0);  // anchor: virtual 0 = wall 100
    const double vb = 1.0 / 59.94;
    // The guest ran one vblank in 4 ms of wall time: wait the rest.
    CHECK(p.delay(vb, 100.004) == doctest::Approx(vb - 0.004));
    // The host is behind (slow vblank): no wait, no re-anchor.
    CHECK(p.delay(2 * vb, 100.0 + 2 * vb + 0.1) == 0.0);
    CHECK(p.resyncs() == 0);
    // Back on time: the original anchor still holds (no drift).
    CHECK(p.delay(10 * vb, 100.0 + 9 * vb) == doctest::Approx(vb));
    // A 2 s stall (debugger, window drag): re-anchor instead of running flat out for 2 s.
    CHECK(p.delay(11 * vb, 100.0 + 11 * vb + 2.0) == 0.0);
    CHECK(p.resyncs() == 1);
    CHECK(p.delay(12 * vb, 100.0 + 11 * vb + 2.0 + 0.001) == doctest::Approx(vb - 0.001));
    // A long run keeps wall ~= virtual: the waits sum to virtual minus the guest's own wall time.
    Pacer q;
    double wall = 0.0, waited = 0.0;
    q.delay(0.0, wall);
    for (int v = 1; v <= 600; ++v) {
        wall += 0.005;  // 5 ms of guest work per vblank
        const double d = q.delay(v * vb, wall);
        waited += d;
        wall += d;
    }
    CHECK(wall == doctest::Approx(600 * vb));
    CHECK(waited == doctest::Approx(600 * vb - 600 * 0.005));
}

TEST_CASE("stats meter: rates over each interval, totals, guest load") {
    StatsMeter m(1.0);
    StatsReport r;
    CHECK_FALSE(m.update({10.0, 0.0, 0.0, 0, 0}, r));   // primes
    CHECK_FALSE(m.update({10.5, 0.5, 0.2, 15, 30}, r));  // under the interval
    REQUIRE(m.update({11.0, 1.001, 0.6, 30, 60}, r));
    CHECK(r.fps == doctest::Approx(30.0));
    CHECK(r.vps == doctest::Approx(60.0));
    CHECK(r.speed == doctest::Approx(1.001));
    CHECK(r.guest_load == doctest::Approx(0.6));
    CHECK(r.virt_s == doctest::Approx(1.001));
    CHECK(r.wall_s == doctest::Approx(1.0));
    REQUIRE(m.update({13.0, 2.201, 0.8, 60, 120}, r));  // a slow second interval: 2 s of wall
    CHECK(r.fps == doctest::Approx(15.0));
    CHECK(r.speed == doctest::Approx(0.6));
    CHECK(r.wall_s == doctest::Approx(3.0));
    CHECK(format_stats(r) == "15.0 fps | 30.0 vblank/s | virtual 2.201 s | wall 3.000 s | speed 60.0% | guest 10%");
}
