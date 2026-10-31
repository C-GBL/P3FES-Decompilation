// Modernize layer 2 (docs/MODERNIZE_PLAN.md §3, ADR-0017; runtime/hle/sif/README.md §10): the host's DUALSHOCK 2
// for the game's pad wrapper under `--native input` (p3fes/native/input_service.h).
//
// The model is the controller as libpad reports it, kept on the host:
//   * per port a controller: connected or not, the mode (digital 0x41 until the game asks for analog, then DUALSHOCK
//     0x73; the game never enters pressure mode, so 0x79 never appears), the request state (one report BUSY after
//     SetMainMode / SetActAlign, then COMPLETE), the actuator map (SetActAlign) and the host input;
//   * per port two report slots, written alternately once per VBLANK_START (`vblank()`), the newer one answering:
//     the latency of the faithful path, where PADMAN DMAs one frame per vblank into the halves of the game's buffer
//     (srv_padman.h) and libpad reads the newer one. Opening a port prepares both slots the way scePadPortOpen
//     prepares its buffer (state 5, request BUSY, no data), so the first report answers at the second VBLANK_START
//     after the open, as on the faithful path;
//   * the host input handed in with `set_input` at VBLANK_START N appears in the report taken at N + 1 (the feed
//     latches after the report, as feed_pad_input does after PADMAN's frame).
// So for the same input the game sees the same answers at the same calls in both modes. Pure C++20, no OS calls: the
// rumble goes to a sink the host sets (XInput in the windowed host).
#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <span>

#include "p3fes/native/input_service.h"

namespace p3fes {
class StateIo;  // p3fes/state_io.h
}

namespace p3fes::native::input {

inline constexpr u32 kPorts = 2;
inline constexpr u8 kModeDigital = 0x41;
inline constexpr u8 kModeDualShock = 0x73;

// The actuator values of one port after a SetActDirect, through the SetActAlign map: the DUALSHOCK's small motor
// (on / off: any non-zero value is on) and its large motor (0..255).
struct Rumble {
    u8 small_motor = 0;
    u8 large_motor = 0;
};

struct NativePadStats {
    std::uint64_t reports = 0;       // reports taken (open ports x VBLANK_STARTs)
    std::uint64_t reads = 0;         // read() calls that returned data
    std::uint64_t mode_changes = 0;  // set_main_mode calls accepted
    std::uint64_t act_direct = 0;    // set_act_direct calls accepted
    std::uint64_t rumble_on = 0;     // of those, with a motor on
};

class NativePad final : public PadService {
public:
    NativePad();

    // PadService (libpad's answers).
    u32 open(u32 port, u32 slot) override;
    u32 get_state(u32 port, u32 slot) override;
    u32 get_req_state(u32 port, u32 slot) override;
    u32 info_act(u32 port, u32 slot, s32 actno, u32 term) override;
    u32 set_act_align(u32 port, u32 slot, std::span<const u8, 6> align) override;
    u32 set_main_mode(u32 port, u32 slot, u32 mode, u32 lock) override;
    u32 read(u32 port, u32 slot, std::span<u8, 32> out) override;
    u32 set_act_direct(u32 port, u32 slot, std::span<const u8, 6> direct) override;

    // The host side. `vblank()` once per VBLANK_START takes each open port's report from its controller; then
    // `set_input` hands in the host's state for the next one. Port 0 starts connected and neutral, port 1
    // disconnected (one controller plugged in, as PADMAN's default).
    void vblank();
    void set_input(u32 port, const PadState& in);
    const PadState& input(u32 port) const { return ports_[port < kPorts ? port : 0].input; }

    // Called on every accepted SetActDirect (the game sends one only when a value changes) and when a port's pad is
    // disconnected or closed (both motors off). nullptr = none.
    void set_rumble_sink(std::function<void(u32 port, Rumble)> sink) { rumble_sink_ = std::move(sink); }
    Rumble rumble(u32 port) const { return ports_[port < kPorts ? port : 0].rumble; }
    bool is_open(u32 port) const { return port < kPorts && ports_[port].open; }
    u8 mode_id(u32 port) const { return ports_[port < kPorts ? port : 0].mode_id; }
    const NativePadStats& stats() const { return stats_; }

    // Machine state (runtime/STATE.md): everything but the sink.
    void state(StateIo& io);

private:
    // What a report says (the fields libpad reads from a pad frame).
    struct Report {
        u32 counter = 0;
        u8 state = 0;         // 0 disconnected, 5 exec (prepared at open), 6 stable
        u8 req_state = 0;     // 0 complete, 2 busy
        u8 current_task = 0;  // 1 = extended commands possible (InfoAct / SetActDirect need it)
        u8 mode_config = 0;   // >= 2 = DUALSHOCK extended (InfoAct needs it)
        u8 nr_act = 0;        // actuators
        u32 length = 0;       // bytes of button data (32, 0 = none)
        std::array<u8, 32> data{};
    };
    struct Port {
        bool open = false;
        u32 counter = 0;
        u8 mode_id = kModeDigital;
        u8 lock = 0;
        u8 req_state = 0;
        u32 busy_reports = 0;
        std::array<u8, 6> align{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        Rumble rumble{};
        PadState input{};
        std::array<Report, 2> slots{};
    };

    Port* port_of(u32 port, u32 slot);
    const Report& newest(const Port& p) const;
    Report& newest(Port& p);
    Report take_report(const Port& p) const;
    void request_busy(Port& p);
    void set_rumble(u32 port, Port& p, Rumble r);

    std::array<Port, kPorts> ports_{};
    std::function<void(u32, Rumble)> rumble_sink_;
    NativePadStats stats_{};
};

// The actuator description InfoAct reports for the DUALSHOCK's two motors ({function, sub-function, size, current}
// per actuator, the bytes PADMAN reports on the faithful path).
inline constexpr std::array<u8, 8> kActuatorInfo{1, 0, 0, 1, 1, 1, 8, 1};

}  // namespace p3fes::native::input
