// Win32 sampling of the live controllers for the windowed host (main.cpp): the mapped keyboard keys through
// GetAsyncKeyState and one XInput gamepad, mapped by input.h. Called once per guest vblank between run slices, never
// on the guest path; the result goes to PadFeed::set_live.
#pragma once

#include <cstdint>
#include <vector>

#include "input.h"

namespace p3fes::app {

class HostInputSampler {
public:
    explicit HostInputSampler(const InputConfig& cfg);

    // The keyboard + gamepad state now. `accept` false (the window is not in the foreground and
    // --background-input is off) returns the neutral pad without reading any device.
    PadInput sample(bool accept);

    int gamepad_user() const { return user_; }  // XInput user in use, -1 = none connected

    // The pad's motors (--native input: the game's vibration): the DUALSHOCK's small motor (on / off) on XInput's
    // right, high-frequency motor, its large motor (0..255) on the left, low-frequency one. Sent only on a change, to
    // the XInput user in use; the destructor stops both.
    void rumble(bool small_on, std::uint8_t large);
    ~HostInputSampler();
    HostInputSampler(const HostInputSampler&) = delete;
    HostInputSampler& operator=(const HostInputSampler&) = delete;

private:
    GamepadState poll_gamepad();

    InputConfig cfg_;
    std::vector<std::uint8_t> keys_;  // distinct mapped virtual keys
    int user_ = -1;
    // XInputGetState on an empty slot is slow (device enumeration), so free slots are probed only every
    // kProbeInterval samples (2 s of vblanks) while no pad is connected.
    static constexpr unsigned kProbeInterval = 120;
    unsigned probe_countdown_ = 0;
    int rumble_user_ = -1;
    std::uint16_t rumble_left_ = 0, rumble_right_ = 0;
};

} // namespace p3fes::app
