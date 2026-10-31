// Host controller input for the guest's DUALSHOCK 2 on pad port 0 (ADR-0013 §4: input changes only at vblank edges).
//
// Three layers, all on the host thread:
//   * mapping (pure): Win32 virtual keys and an XInput-shaped gamepad state -> hle::sif::PadInput (libpad pressed
//     mask, sticks 0x00..0xFF with 0x80 centred) with a radial stick dead zone; the keyboard map is a small ini file
//     (config/input.ini, `parse_input_config`);
//   * PadFeed (pure): the state handed to PADMAN at each VBLANK_START. The windowed host samples the live devices
//     once per guest vblank, between `GameHost::run` slices, and hands the sample to `set_live`; the feed latches it at
//     the next VBLANK_START. Scripted presses (--input-script, the format P3FES_PAD_SCRIPT used) and a replay log are
//     functions of the vblank index only; a record log gets one line per change, so a replay (headless or not) hands
//     PADMAN the same sequence as the recorded run;
//   * the host hook `feed_pad_input`, called once per VBLANK_START from GameHost::host_service, i.e. after the SIF
//     service has written that vblank's PADMAN frame: the state latched at VBLANK_START N is in PADMAN's frame for
//     N + 1 (the timing GameHost's own P3FES_PAD_SCRIPT block had, so existing scripts land on the same frames).
// Nothing here reads the OS; Win32 sampling (GetAsyncKeyState, XInputGetState) is in input_win32.h.
#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include "p3fes/hle/sif/iop.h"

namespace p3fes {
class StateIo;  // p3fes/state_io.h
}

namespace p3fes::app {

using hle::sif::PadInput;

// ---- controls and keys --------------------------------------------------------------------------------------

enum class PadControl : std::uint8_t {
    Up, Down, Left, Right, Triangle, Circle, Cross, Square, L1, L2, R1, R2, L3, R3, Start, Select,
    LStickUp, LStickDown, LStickLeft, LStickRight, RStickUp, RStickDown, RStickLeft, RStickRight,
    Count
};
inline constexpr std::size_t kPadControlCount = static_cast<std::size_t>(PadControl::Count);

// The ini / script name of a control ("up", "cross", "lstick_left", ...).
std::string_view control_name(PadControl c);
// libpad pressed-mask bit of a button control (hle::sif::pad_button); 0 for a stick direction.
std::uint16_t control_button(PadControl c);
// Button controls by name (the 16 buttons only; sticks are not buttons). 0 when unknown. Case-insensitive.
std::uint16_t button_from_name(std::string_view name);

// Win32 virtual-key codes by name: A-Z, 0-9, F1-F24, NUMPAD0-NUMPAD9, UP DOWN LEFT RIGHT, ENTER SPACE BACKSPACE
// TAB ESCAPE, SHIFT CTRL ALT and their L/R forms, INSERT DELETE HOME END PAGEUP PAGEDOWN, punctuation (SEMICOLON
// EQUALS COMMA MINUS PERIOD SLASH GRAVE LBRACKET BACKSLASH RBRACKET APOSTROPHE) and NUMPAD_ADD/SUBTRACT/MULTIPLY/
// DIVIDE/DECIMAL. Case-insensitive; -1 when unknown.
int key_from_name(std::string_view name);
// The canonical name of a virtual key ("VK_0xNN" when it has none).
std::string key_name(int vk);

// ---- configuration (config/input.ini) -----------------------------------------------------------------------

struct InputConfig {
    std::array<std::vector<std::uint8_t>, kPadControlCount> keys{};  // virtual keys per control (any held = pressed)
    int gamepad_index = -1;            // XInput user 0..3; -1 = the first connected one
    double deadzone_left = 0.24;       // radial, fraction of full deflection (XInput's 7849/32767 is 0.2395)
    double deadzone_right = 0.265;     // (XInput's 8689/32767 is 0.2652)
    std::uint8_t trigger_threshold = 30;  // L2/R2 from LT/RT: pressed above this (XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
    std::uint8_t screenshot_key = 0x7B;   // F12 (--screenshot KEY overrides)
    std::uint8_t fullscreen_key = 0x7A;   // F11 (Alt+Enter always toggles as well)
};

// The built-in map (the same as the shipped config/input.ini):
//   D-pad arrows; Triangle I, Circle L, Cross K, Square J; L1 Q, R1 E, L2 1, R2 3, L3 2, R3 4; Start ENTER,
//   Select BACKSPACE; left stick W/A/S/D; right stick T/F/G/H; screenshot F12, full screen F11 / Alt+Enter.
InputConfig default_input_config();

// Applies ini text over `cfg`: sections [keyboard] (control = KEY[, KEY...]; empty = unbound), [gamepad]
// (index = auto|0..3, deadzone_left/right = 0..0.95, trigger_threshold = 0..255) and [hotkeys] (screenshot,
// fullscreen = KEY). '#' and ';' start comments. false + "line N: ..." on any unknown section, key or value.
bool parse_input_config(std::string_view text, InputConfig& cfg, std::string& error);
// Reads `path` and applies it. A missing file is an error unless `missing_ok`.
bool load_input_config(const std::filesystem::path& path, InputConfig& cfg, bool missing_ok, std::string& error);
// The ini text of `cfg` (parse_input_config(format_input_config(c)) == c).
std::string format_input_config(const InputConfig& cfg);
bool same_config(const InputConfig& a, const InputConfig& b);

// ---- mapping (pure) -----------------------------------------------------------------------------------------

using KeyState = std::bitset<256>;  // held virtual keys

// Keyboard -> pad: a button is pressed when any of its keys is held; a stick axis goes to 0x00/0xFF while one of
// its two directions is held and stays at 0x80 when both or neither are.
PadInput map_keyboard(const InputConfig& cfg, const KeyState& held);

// An XInput-shaped controller state (XINPUT_GAMEPAD's fields and button bits; no <xinput.h> here).
struct GamepadState {
    bool connected = false;
    std::uint16_t buttons = 0;
    std::uint8_t left_trigger = 0, right_trigger = 0;
    std::int16_t lx = 0, ly = 0, rx = 0, ry = 0;  // -32768..32767, +y = up
};
namespace xinput_button {
inline constexpr std::uint16_t kDpadUp = 0x0001, kDpadDown = 0x0002, kDpadLeft = 0x0004, kDpadRight = 0x0008;
inline constexpr std::uint16_t kStart = 0x0010, kBack = 0x0020, kLeftThumb = 0x0040, kRightThumb = 0x0080;
inline constexpr std::uint16_t kLeftShoulder = 0x0100, kRightShoulder = 0x0200;
inline constexpr std::uint16_t kA = 0x1000, kB = 0x2000, kX = 0x4000, kY = 0x8000;
}  // namespace xinput_button

struct StickXY {
    double x = 0.0, y = 0.0;  // -1..1, XInput orientation (+y = up)
};
// Radial dead zone: a deflection of magnitude m <= deadzone reads (0, 0); beyond it the magnitude is rescaled
// linearly from 0 at the dead-zone edge to 1 at full deflection (clamped), the direction is kept.
StickXY apply_radial_deadzone(std::int16_t x, std::int16_t y, double deadzone);
// The DUALSHOCK 2's output shape: its axes are read independently and saturate, so a full diagonal reaches the
// square's corner (0x00 / 0xFF on both axes; PCSX2's pad, with its 1.33 axis scale, does the same). The field code
// relies on it: K_VPad_UpdateTask zeroes each stick axis inside +-48 and runs only when the remaining vector is at least
// 125 long (else it walks at 13), so on the unit circle every full deflection 10..22 degrees off an axis walked (its
// minor component zeroed, the major one 127 cos(angle) < 125). This keeps the direction, maps the magnitude to
// min(m / full_at, 1) (full deflection from `full_at` on: a pad's stick rarely reads exactly 1.0 at the rim) and
// stretches it to the square: the larger component carries the magnitude. map_gamepad passes the raw kStickFullAt
// rescaled by the dead zone.
StickXY stick_to_square(const StickXY& s, double full_at);
inline constexpr double kStickFullAt = 0.9;  // raw stick magnitude (0..1) from which a deflection reads as full
// -1 -> 0x00, 0 -> 0x80, +1 -> 0xFF (round half up on each side; clamped).
std::uint8_t axis_to_byte(double v);
// Gamepad -> pad (Xbox layout onto the DUALSHOCK 2): A Cross, B Circle, X Square, Y Triangle, LB L1, RB R1, LT L2,
// RT R2, LS L3, RS R3, Start Start, Back Select, D-pad D-pad; sticks with the dead zone, onto the square
// (stick_to_square, full from kStickFullAt), Y flipped (PS2 0x00 = up).
// A disconnected state maps to the neutral pad.
PadInput map_gamepad(const InputConfig& cfg, const GamepadState& g);
// Keyboard and gamepad together: buttons OR'ed; each stick from the keyboard while the keyboard deflects it,
// otherwise from the gamepad.
PadInput merge_inputs(const PadInput& keyboard, const PadInput& gamepad);

bool same_pad(const PadInput& a, const PadInput& b);

// ---- scripts and logs ---------------------------------------------------------------------------------------

// A scripted press: `buttons` held (and optional stick values) for the VBLANK_STARTs [vblank, vblank + frames).
struct ScriptPress {
    std::uint64_t vblank = 0, frames = 4;
    std::uint16_t buttons = 0;
    std::int16_t lx = -1, ly = -1, rx = -1, ry = -1;  // -1 = not set
};
// "V:BUTTONS[:N]" items separated by ','. BUTTONS: '+'-joined button names (up down left right triangle circle
// cross square l1 l2 r1 r2 l3 r3 start select) and stick values lx=B ly=B rx=B ry=B (0..255, C integer syntax).
// N (default 4) >= 1. Appends to `out`; false + error on a malformed entry.
bool parse_input_script(std::string_view text, std::vector<ScriptPress>& out, std::string& error);
// "BUTTONS@V[:N]" (the --press form of one script entry).
bool parse_press(std::string_view text, std::vector<ScriptPress>& out, std::string& error);

// One record-log line: the state handed to PADMAN from VBLANK_START `vblank` on.
struct InputEvent {
    std::uint64_t vblank = 0;
    PadInput pad{};
};
// Log text: '#' comment lines; "VBLANK BUTTONS LX LY RX RY" with a decimal vblank, a 4-digit hex libpad pressed
// mask and 2-digit hex sticks; vblanks strictly increasing. false + "line N: ..." otherwise.
bool parse_input_log(std::string_view text, std::vector<InputEvent>& out, std::string& error);
bool load_input_log(const std::filesystem::path& path, std::vector<InputEvent>& out, std::string& error);
std::string format_input_event(const InputEvent& e);  // one line, no newline
inline constexpr std::string_view kInputLogHeader =
    "# p3fes input log v1: pad port 0, one line per change of the state handed to PADMAN from that VBLANK_START on\n"
    "# vblank buttons(libpad pressed mask) lx ly rx ry (hex; sticks 0x80 = centre)\n";

// ---- the per-vblank feed ------------------------------------------------------------------------------------

class PadFeed {
public:
    PadFeed() = default;
    ~PadFeed();
    PadFeed(const PadFeed&) = delete;
    PadFeed& operator=(const PadFeed&) = delete;

    // Sources. Live input is ignored while a replay is set; script presses apply on top of either.
    void set_live(const PadInput& in) { live_ = in; }
    void add_script(const std::vector<ScriptPress>& presses);
    void set_replay(std::vector<InputEvent> events);
    bool replaying() const { return replay_set_; }
    bool scripted() const { return !script_.empty(); }
    // Writes the header now and one line per change of the latched state from the next latch on.
    bool open_record(const std::filesystem::path& path, std::string& error);
    bool recording() const { return record_ != nullptr; }

    // Latches the state for VBLANK_START `vblank` the first time it is called with that vblank; true when it did
    // (later calls with the same vblank change nothing). The state is a function of `vblank`, the script, the
    // replay log and the last `set_live` value only.
    bool latch(std::uint64_t vblank);
    const PadInput& current() const { return current_; }
    std::uint64_t current_vblank() const { return latched_vblank_; }

    std::uint64_t latches() const { return latches_; }
    std::uint64_t changes() const { return changes_; }
    std::uint64_t replay_last_vblank() const { return replay_.empty() ? 0 : replay_.back().vblank; }
    bool record_failed() const { return record_failed_; }
    void close_record();
    // Machine state (runtime/STATE.md): the replay log and script, the latch, the counters, the live sample.
    // The recording file is not part of it.
    void state(StateIo& io);

private:
    PadInput compute(std::uint64_t vblank) const;

    PadInput live_{};
    std::vector<ScriptPress> script_;
    std::vector<InputEvent> replay_;
    bool replay_set_ = false;
    std::FILE* record_ = nullptr;
    bool record_failed_ = false;
    bool have_latch_ = false;
    std::uint64_t latched_vblank_ = 0;
    PadInput current_{};
    PadInput last_written_{};
    bool written_any_ = false;
    std::uint64_t latches_ = 0, changes_ = 0;
};

// ---- the host hook ------------------------------------------------------------------------------------------

// GameHost::host_service calls this in its once-per-VBLANK_START branch (`t.vblanks != last_vblank_seen_`):
//     feed_pad_input(t.vblanks, sif_->iop());
// The kernel runs device services in registration order right after each VBLANK_START, before its INTC handlers:
// the SIF service first (PADMAN writes vblank N's frame from the state it holds), then the host's, which latches
// vblank N's state here for PADMAN's next frame. Repeated calls with the same vblank do nothing; without an active
// feed nothing happens (PADMAN keeps its own state).
void feed_pad_input(std::uint64_t vblank, hle::sif::IopHle& iop);
// main.cpp: the feed `feed_pad_input` consults (not owned; nullptr = none).
void set_active_pad_feed(PadFeed* feed);
PadFeed* active_pad_feed();

} // namespace p3fes::app
