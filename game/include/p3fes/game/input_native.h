// Modernize layer 2 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of the game's pad wrapper, taken only
// while the host has installed a native pad service (`--native input`, p3fes/native/input_service.h). The faithful
// bodies swap each libpad call for the service's answer and otherwise run unchanged:
//   H_Pad_Init 0x103000 (field8_sys.cpp): scePadInit and the two scePadPortOpen -> PadService::open
//   H_Pad_UpdateWorkPad 0x103110 (sweep5a.cpp): scePadGetState, scePadGetReqState, scePadInfoAct, scePadSetMainMode
//     -> the service's values; scePadRead, scePadSetActAlign, scePadSetActDirect -> the helpers below (guest buffers)
// Those are the game's only libpad callers: H_Pad_UpdateAll 0x103580 runs H_Pad_UpdateWorkPad for both ports every
// frame and everything else reads the work records it fills (0x7E09B0, 54 bytes per port).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/ee_types.h"
#include "p3fes/native/input_service.h"

namespace p3fes::game {

// scePadRead(port, slot, dst): the newest report's button data copied to guest `dst` (its length in bytes; the rest
// of the 32-byte buffer is left as it was). Returns the length (scePadRead's $v0).
u32 hpad_native_read(EEContext& ctx, native::input::PadService& ps, u32 port, u32 slot, u32 dst);
// scePadSetActAlign(port, slot, src) / scePadSetActDirect(port, slot, src): the 6 bytes at guest `src`.
u32 hpad_native_act_align(EEContext& ctx, native::input::PadService& ps, u32 port, u32 slot, u32 src);
u32 hpad_native_act_direct(EEContext& ctx, native::input::PadService& ps, u32 port, u32 slot, u32 src);

}  // namespace p3fes::game
