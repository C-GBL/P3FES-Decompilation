// XInput-shaped gamepad mapping and the radial dead zone (runtime/app/input.h).
#include <doctest.h>

#include <cmath>

#include "input.h"

using namespace p3fes::app;
namespace pb = p3fes::hle::sif::pad_button;
namespace xb = p3fes::app::xinput_button;

namespace {

double mag(const StickXY& s) { return std::sqrt(s.x * s.x + s.y * s.y); }

GamepadState pad(std::uint16_t buttons = 0) {
    GamepadState g;
    g.connected = true;
    g.buttons = buttons;
    return g;
}

} // namespace

TEST_CASE("axis_to_byte: -1 -> 0x00, 0 -> 0x80, +1 -> 0xFF, halves, clamping") {
    CHECK(axis_to_byte(-1.0) == 0x00);
    CHECK(axis_to_byte(0.0) == 0x80);
    CHECK(axis_to_byte(-0.0) == 0x80);
    CHECK(axis_to_byte(1.0) == 0xFF);
    CHECK(axis_to_byte(-0.5) == 0x40);
    CHECK(axis_to_byte(0.5) == 0xC0);  // 128 + 63.5 rounds half up
    CHECK(axis_to_byte(2.0) == 0xFF);
    CHECK(axis_to_byte(-7.0) == 0x00);
    // Monotonic over the whole range.
    int prev = -1;
    for (int i = -1000; i <= 1000; ++i) {
        const int b = axis_to_byte(i / 1000.0);
        CHECK(b >= prev);
        prev = b;
    }
}

TEST_CASE("radial dead zone: inside reads zero, outside rescales from the edge, direction kept") {
    const double dz = 0.24;
    CHECK(mag(apply_radial_deadzone(0, 0, dz)) == 0.0);
    CHECK(mag(apply_radial_deadzone(7000, 0, dz)) == 0.0);              // 0.2136
    CHECK(mag(apply_radial_deadzone(5000, -5000, dz)) == 0.0);          // 0.2158 diagonal
    CHECK(mag(apply_radial_deadzone(7864, 0, dz)) == 0.0);              // 0.23999, at the edge
    const StickXY just = apply_radial_deadzone(7900, 0, dz);            // 0.24109
    CHECK(just.x > 0.0);
    CHECK(just.x < 0.01);                                               // continuous at the edge
    const StickXY full = apply_radial_deadzone(32767, 0, dz);
    CHECK(full.x == doctest::Approx(1.0));
    CHECK(full.y == doctest::Approx(0.0));
    CHECK(apply_radial_deadzone(-32768, 0, dz).x == doctest::Approx(-1.0));  // -32768 clamps to -1
    CHECK(apply_radial_deadzone(0, 32767, dz).y == doctest::Approx(1.0));
    // Halfway between the edge and full deflection reads one half.
    const auto half = static_cast<std::int16_t>(std::lround((dz + (1.0 - dz) * 0.5) * 32767.0));
    CHECK(apply_radial_deadzone(half, 0, dz).x == doctest::Approx(0.5).epsilon(1e-4));
    // Radial, not per axis: equal magnitudes give equal outputs in every direction.
    const StickXY axial = apply_radial_deadzone(20000, 0, dz);
    const StickXY diag = apply_radial_deadzone(14142, 14142, dz);
    CHECK(mag(axial) == doctest::Approx(mag(diag)).epsilon(1e-4));
    CHECK(diag.x == doctest::Approx(diag.y));
    // A small deflection on one axis is not cut when the other axis is far out (an axial dead zone would).
    const StickXY mostly_x = apply_radial_deadzone(30000, 4000, dz);
    CHECK(mostly_x.y > 0.0);
    // Full diagonal deflection is clamped to the unit circle.
    const StickXY corner = apply_radial_deadzone(32767, 32767, dz);
    CHECK(mag(corner) == doctest::Approx(1.0));
    CHECK(corner.x == doctest::Approx(std::sqrt(0.5)));
    // No dead zone: the identity on the normalised values.
    CHECK(apply_radial_deadzone(16384, 0, 0.0).x == doctest::Approx(16384.0 / 32767.0));
}

TEST_CASE("map_gamepad: Xbox layout onto the DUALSHOCK 2") {
    const InputConfig c = default_input_config();
    const struct {
        std::uint16_t x;
        std::uint16_t ps2;
    } cases[] = {
        {xb::kA, pb::kCross},          {xb::kB, pb::kCircle},          {xb::kX, pb::kSquare},     {xb::kY, pb::kTriangle},
        {xb::kLeftShoulder, pb::kL1},  {xb::kRightShoulder, pb::kR1},  {xb::kLeftThumb, pb::kL3}, {xb::kRightThumb, pb::kR3},
        {xb::kStart, pb::kStart},      {xb::kBack, pb::kSelect},       {xb::kDpadUp, pb::kUp},    {xb::kDpadDown, pb::kDown},
        {xb::kDpadLeft, pb::kLeft},    {xb::kDpadRight, pb::kRight},
    };
    std::uint16_t all_x = 0, all_ps2 = 0;
    for (const auto& t : cases) {
        const PadInput p = map_gamepad(c, pad(t.x));
        CHECK(p.buttons == t.ps2);
        CHECK(p.lx == 0x80);
        CHECK(p.ly == 0x80);
        all_x = static_cast<std::uint16_t>(all_x | t.x);
        all_ps2 = static_cast<std::uint16_t>(all_ps2 | t.ps2);
    }
    CHECK(map_gamepad(c, pad(all_x)).buttons == all_ps2);
    // Triggers: pressed strictly above the threshold.
    GamepadState g = pad();
    g.left_trigger = 30;
    g.right_trigger = 31;
    CHECK(map_gamepad(c, g).buttons == pb::kR2);
    g.left_trigger = 255;
    CHECK(map_gamepad(c, g).buttons == (pb::kL2 | pb::kR2));
    // Disconnected: the neutral pad whatever the fields say.
    GamepadState off = pad(xb::kA);
    off.connected = false;
    off.lx = 32767;
    const PadInput n = map_gamepad(c, off);
    CHECK(n.buttons == 0);
    CHECK(n.lx == 0x80);
}

TEST_CASE("map_gamepad: sticks through the dead zone with Y flipped to the PS2's orientation") {
    const InputConfig c = default_input_config();
    GamepadState g = pad();
    g.ly = 32767;  // XInput up
    CHECK(map_gamepad(c, g).ly == 0x00);
    g.ly = -32768;  // down
    CHECK(map_gamepad(c, g).ly == 0xFF);
    g.ly = 0;
    g.lx = 32767;
    CHECK(map_gamepad(c, g).lx == 0xFF);
    g.lx = -32768;
    CHECK(map_gamepad(c, g).lx == 0x00);
    g.lx = 6000;  // inside the left dead zone
    g.rx = 6000;  // diagonal magnitude 0.259: inside the right dead zone (0.265), outside the left one (0.24)
    g.ry = -6000;
    const PadInput p = map_gamepad(c, g);
    CHECK(p.lx == 0x80);
    CHECK(p.rx == 0x80);
    CHECK(p.ry == 0x80);
    InputConfig tight = c;
    tight.deadzone_right = 0.1;
    const PadInput q = map_gamepad(tight, g);
    CHECK(q.rx > 0x80);
    CHECK(q.ry > 0x80);  // XInput down -> PS2 larger
}

TEST_CASE("merge_inputs: buttons OR'ed, each stick from the keyboard only while it deflects it") {
    PadInput kb, gp;
    kb.buttons = pb::kCross;
    gp.buttons = pb::kStart;
    gp.lx = 0x10;
    gp.ly = 0x20;
    gp.rx = 0xE0;
    gp.ry = 0xF0;
    PadInput m = merge_inputs(kb, gp);
    CHECK(m.buttons == (pb::kCross | pb::kStart));
    CHECK(m.lx == 0x10);
    CHECK(m.ly == 0x20);
    CHECK(m.rx == 0xE0);
    kb.lx = 0xFF;  // keyboard deflects the left stick only
    m = merge_inputs(kb, gp);
    CHECK(m.lx == 0xFF);
    CHECK(m.ly == 0x80);  // the whole stick comes from the keyboard
    CHECK(m.rx == 0xE0);
    CHECK(m.ry == 0xF0);
    CHECK(m.connected);
}
