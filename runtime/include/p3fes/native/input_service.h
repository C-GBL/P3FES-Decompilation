// Modernize pass, layer 2: input (docs/MODERNIZE_PLAN.md §3, ADR-0017; runtime/hle/sif/README.md §10).
//
// The seam between the game's own pad wrapper and the host. With `--native input` the host installs a PadService
// (runtime/native/input/native_pad.h) in `g_service`; the game's pad layer then asks it instead of libpad, so no SIF
// RPC reaches PADMAN, no pad frame is DMA'd into the game's buffers and SIO2 is never involved:
//   H_Pad_Init 0x103000           scePadInit + scePadPortOpen(0 / 1, 0, buffer)  -> open(port, slot)
//   H_Pad_UpdateWorkPad 0x103110  scePadGetState / GetReqState / InfoAct / SetActAlign / SetMainMode / Read /
//                                 SetActDirect                                    -> the calls below
// These two are the game's only libpad callers (every pad read of the game goes through H_Pad_UpdateWorkPad, once per
// port per frame from H_Pad_UpdateAll 0x103580). The answers are libpad's: the same values for the same controller,
// with the same report latency (a report is taken once per VBLANK_START), so the game's pad work is identical in both
// modes. With `g_service == nullptr` (the default, `--native` without `input`) every call site runs its faithful jal.
// The game library depends on headers only, so this is an interface plus an inline pointer.
#pragma once

#include <array>
#include <span>

#include "p3fes/ee_types.h"

namespace p3fes::native::input {

// One controller as the host sees it at a VBLANK_START (the same shape as the host feed's hle::sif::PadInput):
// `buttons` is libpad's pressed mask (bit set = pressed: Select 0x1, L3 0x2, R3 0x4, Start 0x8, Up 0x10, Right 0x20,
// Down 0x40, Left 0x80, L2 0x100, R2 0x200, L1 0x400, R1 0x800, Triangle 0x1000, Circle 0x2000, Cross 0x4000,
// Square 0x8000); sticks 0x00..0xFF, 0x80 centred, PS2 orientation (0x00 = left / up).
struct PadState {
    bool connected = true;
    u16 buttons = 0;
    u8 rx = 0x80, ry = 0x80, lx = 0x80, ly = 0x80;
};

// libpad's answers, port 0..1, slot 0 (no multitap). Every method is called on the EE fiber.
class PadService {
public:
    virtual ~PadService() = default;

    // scePadInit + scePadPortOpen(port, slot, buffer): 1 opened, 0 not (bad port / slot, already open).
    virtual u32 open(u32 port, u32 slot) = 0;
    // scePadGetState: 99 not open; else the newest report's state (0 disconnected, 6 stable; 5 while a request is
    // busy on a stable pad, or before the first report after the port opened).
    virtual u32 get_state(u32 port, u32 slot) = 0;
    // scePadGetReqState: 0 complete, 1 failed, 2 busy (0 when not open).
    virtual u32 get_req_state(u32 port, u32 slot) = 0;
    // scePadInfoAct(port, slot, actno, term): actno -1 = the number of actuators; else byte `term` (1..4) of
    // actuator `actno`'s description; 0 when the pad is not in extended mode or `actno` is out of range.
    virtual u32 info_act(u32 port, u32 slot, s32 actno, u32 term) = 0;
    // scePadSetActAlign(port, slot, align[6]): which actuator each byte of a SetActDirect packet drives; 1 accepted.
    virtual u32 set_act_align(u32 port, u32 slot, std::span<const u8, 6> align) = 0;
    // scePadSetMainMode(port, slot, mode, lock): 1 = analog (DUALSHOCK), 0 = digital; 1 accepted.
    virtual u32 set_main_mode(u32 port, u32 slot, u32 mode, u32 lock) = 0;
    // scePadRead: copies the newest report's button data (its length, 32 bytes for a connected pad, 0 before the
    // first report) to `out` and returns that length; 0 when not open.
    virtual u32 read(u32 port, u32 slot, std::span<u8, 32> out) = 0;
    // scePadSetActDirect(port, slot, direct[6]): the actuator values (through the SetActAlign map); 1 sent, 0 when
    // the pad is not in extended mode.
    virtual u32 set_act_direct(u32 port, u32 slot, std::span<const u8, 6> direct) = 0;
};

// Installed by the host (GameHost) while `--native input` is on; nullptr = the faithful path.
inline PadService* g_service = nullptr;
inline PadService* service() noexcept { return g_service; }

}  // namespace p3fes::native::input
