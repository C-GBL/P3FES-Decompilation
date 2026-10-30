// Private: PADMAN (sids 0x80000100 / 0x80000101). Every libpad call is fn 1 with a 128-byte buffer
// in both directions, word0 = function (obs, `12` §2.1); the result word differs per function (obs
// in each wrapper): PortOpen/PortClose/Init2/End/GetPortMax/GetSlotMax/GetModVersion +12,
// SetMainMode/SetActAlign +20, SetButtonInfo +16, SetVrefParam +28, SetWarningLevel +8.
//
// Pad data reaches the EE the way PADMAN delivers it: every vblank the IOP DMAs a 128-byte
// pad_data_new frame (ps2sdk ee/rpc/pad/src/libpad.c @ 329e2bb layout; obs offsets in the game's
// libpad: +88 frame counter (scePadGetDmaStr 0x511830 picks the newer of +88/+216), +96 length
// (scePadRead 0x5119E0), +100 modeConfig, +101 modeCurId, +104 nrOfModes, +105 modeCurOffs,
// +106 nrOfActuators, +107 numActComb, +112 state, +113 reqState, +114 currentTask (InfoMode/
// InfoAct require 1), +48 actData, +64 combData, +80 modeTable) alternately into the two halves of
// the 256-byte buffer the game registered with scePadPortOpen.
#pragma once

#include <array>

#include "iop_core.h"

namespace p3fes::hle::sif::detail {

namespace pad_sid {
inline constexpr u32 kMain = 0x80000100u;
inline constexpr u32 kSecond = 0x80000101u;
}  // namespace pad_sid

namespace pad_frame {
inline constexpr std::size_t kSize = 128;
inline constexpr std::size_t kData = 0;
inline constexpr std::size_t kActData = 48;
inline constexpr std::size_t kCombData = 64;
inline constexpr std::size_t kModeTable = 80;
inline constexpr std::size_t kFrame = 88;
inline constexpr std::size_t kLength = 96;
inline constexpr std::size_t kModeConfig = 100;
inline constexpr std::size_t kModeCurId = 101;
inline constexpr std::size_t kModel = 102;
inline constexpr std::size_t kButtonDataReady = 103;
inline constexpr std::size_t kNrOfModes = 104;
inline constexpr std::size_t kModeCurOffs = 105;
inline constexpr std::size_t kNrOfActuators = 106;
inline constexpr std::size_t kNumActComb = 107;
inline constexpr std::size_t kMode = 109;
inline constexpr std::size_t kLock = 110;
inline constexpr std::size_t kState = 112;
inline constexpr std::size_t kReqState = 113;
inline constexpr std::size_t kCurrentTask = 114;
}  // namespace pad_frame

namespace pad_state {
inline constexpr u8 kDisconnected = 0x00;
inline constexpr u8 kExecCmd = 0x05;
inline constexpr u8 kStable = 0x06;
inline constexpr u8 kReqComplete = 0x00;
inline constexpr u8 kReqBusy = 0x02;
}  // namespace pad_state

// Mode ids (id byte = type << 4 | halfwords of button data).
inline constexpr u8 kPadIdDigital = 0x41;
inline constexpr u8 kPadIdDualShock = 0x73;  // DUALSHOCK(2) analog without pressure mode

// Encodes one frame (pure; tested). `counter` goes to +88.
struct PadPortState {
    bool open = false;
    u32 ee_buffer = 0;  // 256 bytes, 64-byte aligned (scePadPortOpen checks, obs 0x5115B4)
    u32 iop_buffer = 0; // where _send_to_iop 0x511478 DMAs actuator packets
    u32 counter = 0;
    u8 mode_id = kPadIdDigital;
    u8 mode_offs = 0;
    u8 lock = 0;
    u8 req_state = pad_state::kReqComplete;
    u32 busy_frames = 0;  // frames left reporting reqState BUSY after a mode/act request
    PadInput input{};
};
std::array<u8, pad_frame::kSize> encode_pad_frame(const PadPortState& p);

class PadmanServer final : public RpcServer {
public:
    std::string_view name() const override { return "padman"; }
    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) override;
    void tick(IopCore& core, u64 now, const Timebase& tb) override;
    void reboot() override;
    void state(StateIo& io, IopCore& core) override;
    void set_input(unsigned port, const PadInput& in);

private:
    std::array<PadPortState, 2> ports_{};
    std::array<PadInput, 2> inputs_{PadInput{}, PadInput{false}};  // inf: one controller plugged
    u64 last_vblank_ = ~0ull;
    void write_frame(IopCore& core, PadPortState& p);
};

}  // namespace p3fes::hle::sif::detail
