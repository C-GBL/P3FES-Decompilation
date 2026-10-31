// Modernize layer 2 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the host's DUALSHOCK 2 the game's pad wrapper asks under
// `--native input` (runtime/native/input/native_pad.h), on its own and fed from the host input mapping (input.h):
// libpad's answers and their report latency, button mapping, sticks, mode change, actuators and rumble,
// connect / disconnect, two ports, machine state.
#include <doctest.h>

#include <array>
#include <vector>

#include "input.h"
#include "native_pad.h"
#include "p3fes/state_io.h"

using namespace p3fes;
using namespace p3fes::native::input;

namespace {

std::array<u8, 32> read32(NativePad& p, u32 port, u32* n = nullptr) {
    std::array<u8, 32> d{};
    d.fill(0xEE);
    const u32 got = p.read(port, 0, d);
    if (n) *n = got;
    return d;
}

PadState from_host(const app::PadInput& in) { return PadState{in.connected, in.buttons, in.rx, in.ry, in.lx, in.ly}; }

// The game's start-up on a fresh pad: open, the first report at the second VBLANK_START, digital mode.
void open_and_settle(NativePad& p, u32 port) {
    REQUIRE(p.open(port, 0) == 1);
    p.vblank();
    p.vblank();
}

}  // namespace

TEST_CASE("native input: libpad's answers before the port opens and while the first reports arrive") {
    NativePad p;
    CHECK(p.get_state(0, 0) == 99);  // not open
    CHECK(p.get_req_state(0, 0) == 0);
    u32 n = 7;
    read32(p, 0, &n);
    CHECK(n == 0);
    CHECK(p.info_act(0, 0, -1, 0) == 0);
    CHECK(p.open(2, 0) == 0);  // no third port
    CHECK(p.open(0, 1) == 0);  // no multitap
    CHECK(p.get_state(0, 1) == 99);

    REQUIRE(p.open(0, 0) == 1);
    CHECK(p.open(0, 0) == 0);  // already open
    // Prepared as scePadPortOpen prepares its buffer: "executing", a request busy, no data.
    CHECK(p.get_state(0, 0) == 5);
    CHECK(p.get_req_state(0, 0) == 2);
    read32(p, 0, &n);
    CHECK(n == 0);
    CHECK(p.info_act(0, 0, -1, 0) == 0);
    // The first report goes to the second slot with counter 0: a tie, the prepared slot still answers.
    p.vblank();
    CHECK(p.get_state(0, 0) == 5);
    // The second report (counter 1) is the newer one: a stable digital pad.
    p.vblank();
    CHECK(p.get_state(0, 0) == 6);
    CHECK(p.get_req_state(0, 0) == 0);
    const auto d = read32(p, 0, &n);
    CHECK(n == 32);
    CHECK(d[0] == 0x00);
    CHECK(d[1] == kModeDigital);
    CHECK(d[2] == 0xFF);  // no button pressed (active low)
    CHECK(d[3] == 0xFF);
    for (int i = 4; i < 32; ++i) CHECK(d[i] == 0);  // digital: no sticks; no pressure bytes ever
    CHECK(p.stats().reports == 2);
}

TEST_CASE("native input: buttons and sticks, one report after the host hands them in") {
    NativePad p;
    open_and_settle(p, 0);
    REQUIRE(p.set_main_mode(0, 0, 1, 3) == 1);  // analog, locked (what H_Pad_UpdateWorkPad asks)
    p.vblank();
    p.vblank();
    REQUIRE(p.mode_id(0) == kModeDualShock);

    PadState in;
    in.buttons = 0x4000 | 0x0010 | 0x0800;  // Cross, Up, R1
    in.lx = 0x00;
    in.ly = 0xFF;
    in.rx = 0x12;
    in.ry = 0xC0;
    p.set_input(0, in);
    // Not before the next report (the faithful latency: latched at VBLANK_START N, in PADMAN's frame for N + 1).
    auto d = read32(p, 0);
    CHECK(d[2] == 0xFF);
    CHECK(d[3] == 0xFF);
    CHECK(d[6] == 0x80);
    p.vblank();
    d = read32(p, 0);
    CHECK(d[1] == kModeDualShock);
    CHECK(d[2] == static_cast<u8>(~0x10));          // Up (low byte)
    CHECK(d[3] == static_cast<u8>(~(0x48)));        // Cross 0x4000, R1 0x0800 (high byte)
    CHECK(d[4] == 0x12);  // right x
    CHECK(d[5] == 0xC0);  // right y
    CHECK(d[6] == 0x00);  // left x
    CHECK(d[7] == 0xFF);  // left y
    // What H_Pad_UpdateWorkPad makes of it: held = ~(d[2] << 8 | d[3]) as libpad's pressed mask, byte-swapped.
    const u16 held = static_cast<u16>(~((d[2] << 8) | d[3]));
    CHECK(held == ((0x0010 << 8) | (0x4800 >> 8)));
}

TEST_CASE("native input: the keyboard and XInput mapping reach the report (input.h -> PadState)") {
    const app::InputConfig cfg = app::default_input_config();
    app::GamepadState g;
    g.connected = true;
    g.buttons = app::xinput_button::kA | app::xinput_button::kStart | app::xinput_button::kDpadLeft;
    g.lx = 0;
    g.ly = -32768;  // left stick full down
    g.rx = 32767;   // right stick full right
    app::KeyState keys;
    keys.set(static_cast<std::size_t>(app::key_from_name("I")));  // Triangle on the default map
    const app::PadInput host = app::merge_inputs(app::map_keyboard(cfg, keys), app::map_gamepad(cfg, g));

    NativePad p;
    open_and_settle(p, 0);
    REQUIRE(p.set_main_mode(0, 0, 1, 3) == 1);
    p.vblank();
    p.set_input(0, from_host(host));
    p.vblank();
    const auto d = read32(p, 0);
    const u16 pressed = static_cast<u16>(~(d[2] | (d[3] << 8)));
    CHECK(pressed == (hle::sif::pad_button::kCross | hle::sif::pad_button::kStart | hle::sif::pad_button::kLeft |
                      hle::sif::pad_button::kTriangle));
    CHECK(d[6] == 0x80);  // left x centred
    CHECK(d[7] == 0xFF);  // left y: down (PS2 0xFF = down, XInput -y)
    CHECK(d[4] == 0xFF);  // right x: right
    CHECK(d[5] == 0x80);  // right y centred
}

TEST_CASE("native input: SetMainMode -- busy for one report, then complete; GetState says 5 while busy") {
    NativePad p;
    open_and_settle(p, 0);
    REQUIRE(p.get_state(0, 0) == 6);
    REQUIRE(p.set_main_mode(0, 0, 1, 3) == 1);
    CHECK(p.get_state(0, 0) == 5);      // scePadSetReqState(BUSY) on the newest report: stable + busy
    CHECK(p.get_req_state(0, 0) == 2);
    p.vblank();                         // this report says BUSY
    CHECK(p.get_req_state(0, 0) == 2);
    CHECK(p.get_state(0, 0) == 5);
    CHECK(read32(p, 0)[1] == kModeDualShock);  // the new mode is in it already
    p.vblank();                         // and this one COMPLETE
    CHECK(p.get_req_state(0, 0) == 0);
    CHECK(p.get_state(0, 0) == 6);
    CHECK(p.set_main_mode(0, 0, 0, 0) == 1);  // back to digital
    p.vblank();
    p.vblank();
    CHECK(read32(p, 0)[1] == kModeDigital);
    CHECK(p.stats().mode_changes == 2);
}

TEST_CASE("native input: InfoAct, SetActAlign and SetActDirect drive the rumble sink") {
    NativePad p;
    std::vector<std::pair<u32, Rumble>> sent;
    p.set_rumble_sink([&sent](u32 port, Rumble r) { sent.emplace_back(port, r); });
    REQUIRE(p.open(0, 0) == 1);
    const std::array<u8, 6> direct{1, 200, 0, 0, 0, 0};
    CHECK(p.set_act_direct(0, 0, direct) == 0);  // no report yet: not in extended mode
    p.vblank();
    p.vblank();
    CHECK(p.info_act(0, 0, -1, 0) == 2);  // two motors
    CHECK(p.info_act(0, 0, 0, 1) == 1);
    CHECK(p.info_act(0, 0, 0, 2) == 0);
    CHECK(p.info_act(0, 0, 0, 3) == 0);
    CHECK(p.info_act(0, 0, 0, 4) == 1);
    CHECK(p.info_act(0, 0, 1, 1) == 1);
    CHECK(p.info_act(0, 0, 1, 2) == 1);
    CHECK(p.info_act(0, 0, 1, 3) == 8);
    CHECK(p.info_act(0, 0, 1, 4) == 1);
    CHECK(p.info_act(0, 0, 1, 5) == 0);
    CHECK(p.info_act(0, 0, 2, 1) == 0);  // no third actuator
    const std::array<u8, 6> align{0, 1, 0xFF, 0xFF, 0xFF, 0xFF};
    CHECK(p.set_act_align(0, 0, align) == 1);
    CHECK(p.get_req_state(0, 0) == 2);
    p.vblank();
    p.vblank();
    CHECK(p.get_req_state(0, 0) == 0);
    CHECK(p.set_act_direct(0, 0, direct) == 1);
    REQUIRE(sent.size() == 1);
    CHECK(sent[0].first == 0);
    CHECK(sent[0].second.small_motor == 1);
    CHECK(sent[0].second.large_motor == 200);
    // A swapped map swaps the motors.
    const std::array<u8, 6> swapped{1, 0, 0xFF, 0xFF, 0xFF, 0xFF};
    CHECK(p.set_act_align(0, 0, swapped) == 1);
    CHECK(p.set_act_direct(0, 0, direct) == 1);
    REQUIRE(sent.size() == 2);
    CHECK(sent[1].second.small_motor == 200);
    CHECK(sent[1].second.large_motor == 1);
    CHECK(p.stats().act_direct == 2);
    CHECK(p.stats().rumble_on == 2);
    // Unplugging stops the motors.
    PadState off;
    off.connected = false;
    p.set_input(0, off);
    REQUIRE(sent.size() == 3);
    CHECK(sent[2].second.small_motor == 0);
    CHECK(sent[2].second.large_motor == 0);
}

TEST_CASE("native input: disconnect and reconnect") {
    NativePad p;
    open_and_settle(p, 0);
    PadState off;
    off.connected = false;
    p.set_input(0, off);
    p.vblank();
    CHECK(p.get_state(0, 0) == 0);  // disconnected
    u32 n = 1;
    const auto d = read32(p, 0, &n);
    CHECK(n == 0);
    CHECK(d[0] == 0xEE);  // nothing copied
    CHECK(p.info_act(0, 0, -1, 0) == 0);
    PadState on;
    on.buttons = 0x0008;  // Start
    p.set_input(0, on);
    p.vblank();
    CHECK(p.get_state(0, 0) == 6);
    CHECK(read32(p, 0)[2] == static_cast<u8>(~0x08));
}

TEST_CASE("native input: two ports -- port 1 starts unplugged, each port its own controller") {
    NativePad p;
    open_and_settle(p, 0);
    open_and_settle(p, 1);
    CHECK(p.get_state(0, 0) == 6);
    CHECK(p.get_state(1, 0) == 0);  // nothing plugged into port 2 (PADMAN's default)
    PadState two;
    two.buttons = 0x2000;  // Circle
    p.set_input(1, two);
    p.vblank();
    CHECK(p.get_state(1, 0) == 6);
    CHECK(read32(p, 1)[3] == static_cast<u8>(~0x20));
    CHECK(read32(p, 0)[3] == 0xFF);  // port 1 untouched
    CHECK(p.set_main_mode(1, 0, 1, 3) == 1);
    CHECK(p.get_state(1, 0) == 5);
    CHECK(p.get_state(0, 0) == 6);
}

TEST_CASE("native input: machine state round trip") {
    NativePad a;
    open_and_settle(a, 0);
    REQUIRE(a.set_main_mode(0, 0, 1, 3) == 1);
    PadState in;
    in.buttons = 0x1000;
    in.lx = 3;
    a.set_input(0, in);
    a.vblank();
    StateIo w;
    a.state(w);
    NativePad b;
    StateIo r(w.buffer().data(), w.buffer().size());
    b.state(r);
    REQUIRE(r.ok());
    CHECK(b.get_state(0, 0) == a.get_state(0, 0));
    CHECK(b.get_req_state(0, 0) == a.get_req_state(0, 0));
    CHECK(read32(b, 0) == read32(a, 0));
    a.vblank();
    b.vblank();
    CHECK(read32(b, 0) == read32(a, 0));
    CHECK(b.get_state(0, 0) == 6);
    CHECK(b.stats().reports == a.stats().reports);
}
