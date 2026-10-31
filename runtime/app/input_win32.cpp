#include "input_win32.h"

#include <windows.h>
#include <xinput.h>

#include <algorithm>

namespace p3fes::app {

HostInputSampler::HostInputSampler(const InputConfig& cfg) : cfg_(cfg) {
    for (const auto& list : cfg_.keys)
        for (std::uint8_t vk : list)
            if (std::find(keys_.begin(), keys_.end(), vk) == keys_.end()) keys_.push_back(vk);
}

GamepadState HostInputSampler::poll_gamepad() {
    GamepadState g;
    auto read = [&g](DWORD user) {
        XINPUT_STATE s = {};
        if (XInputGetState(user, &s) != ERROR_SUCCESS) return false;
        g.connected = true;
        g.buttons = s.Gamepad.wButtons;
        g.left_trigger = s.Gamepad.bLeftTrigger;
        g.right_trigger = s.Gamepad.bRightTrigger;
        g.lx = s.Gamepad.sThumbLX;
        g.ly = s.Gamepad.sThumbLY;
        g.rx = s.Gamepad.sThumbRX;
        g.ry = s.Gamepad.sThumbRY;
        return true;
    };
    if (user_ >= 0) {
        if (read(static_cast<DWORD>(user_))) return g;
        user_ = -1;  // unplugged: probe again
        probe_countdown_ = 0;
    }
    if (probe_countdown_ > 0) {
        --probe_countdown_;
        return g;
    }
    probe_countdown_ = kProbeInterval;
    if (cfg_.gamepad_index >= 0) {
        if (read(static_cast<DWORD>(cfg_.gamepad_index))) user_ = cfg_.gamepad_index;
        return g;
    }
    for (DWORD u = 0; u < XUSER_MAX_COUNT; ++u)
        if (read(u)) {
            user_ = static_cast<int>(u);
            break;
        }
    return g;
}

HostInputSampler::~HostInputSampler() { rumble(false, 0); }

void HostInputSampler::rumble(bool small_on, std::uint8_t large) {
    const std::uint16_t left = static_cast<std::uint16_t>(large * 257u);
    const std::uint16_t right = small_on ? 0xFFFFu : 0u;
    if (user_ == rumble_user_ && left == rumble_left_ && right == rumble_right_) return;
    // A user that changed (unplugged and another found) is stopped first.
    if (rumble_user_ >= 0 && rumble_user_ != user_) {
        XINPUT_VIBRATION off = {};
        XInputSetState(static_cast<DWORD>(rumble_user_), &off);
        rumble_user_ = -1;
        rumble_left_ = rumble_right_ = 0;
    }
    if (user_ < 0) return;
    XINPUT_VIBRATION v = {};
    v.wLeftMotorSpeed = left;
    v.wRightMotorSpeed = right;
    if (XInputSetState(static_cast<DWORD>(user_), &v) == ERROR_SUCCESS) {
        rumble_user_ = user_;
        rumble_left_ = left;
        rumble_right_ = right;
    }
}

PadInput HostInputSampler::sample(bool accept) {
    if (!accept) return PadInput{};
    KeyState held;
    for (std::uint8_t vk : keys_)
        if (GetAsyncKeyState(vk) & 0x8000) held.set(vk);
    return merge_inputs(map_keyboard(cfg_, held), map_gamepad(cfg_, poll_gamepad()));
}

} // namespace p3fes::app
