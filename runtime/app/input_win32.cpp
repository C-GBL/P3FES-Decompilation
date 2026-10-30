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

PadInput HostInputSampler::sample(bool accept) {
    if (!accept) return PadInput{};
    KeyState held;
    for (std::uint8_t vk : keys_)
        if (GetAsyncKeyState(vk) & 0x8000) held.set(vk);
    return merge_inputs(map_keyboard(cfg_, held), map_gamepad(cfg_, poll_gamepad()));
}

} // namespace p3fes::app
