// Modernize layer 6, step 1 (native_kernel.h).
#include "native_kernel.h"

#include <cstring>

namespace p3fes::native::kernel {

bool parse_timing(const char* s, Timing& out) {
    if (std::strcmp(s, "faithful") == 0) {
        out = Timing::Faithful;
        return true;
    }
    if (std::strcmp(s, "host") == 0) {
        out = Timing::Host;
        return true;
    }
    return false;
}

const char* to_string(Timing t) { return t == Timing::Host ? "host" : "faithful"; }

void configure(hle::KernelOptions& o, Timing t) {
    // The (a) set keeps the BIOS context frames: the game reads them back. Uninitialised stack slots of its functions
    // (struct temporaries copied whole, e.g. into the CD cache's records sCdvdCache 0x7D6F80) carry what the frames
    // left there, so without the frames the m1 route's guest memory differs from vblank 20 on and the battle route
    // desyncs (docs/MODERNIZE_PLAN.md "Layer 6 status"). Host-only contexts are therefore part of the (b) set.
    if (t == Timing::Host) {
        o.context_frames = false;
        o.dma_base_cycles = 0;
        o.dma_cycles_per_qword = 0;
    }
}

void NativeKernel::call(EEContext& ctx, u32 pc) {
    const s32 n = static_cast<s32>(ctx.gpr[GPR_V1].u32[0]);
    const u32 slot = static_cast<u32>(n < 0 ? -static_cast<s64>(n) : n) & 0xFFu;
    ++(n < 0 ? stats_.icalls : stats_.calls)[slot];
    ++stats_.total;
    k_.direct_call(ctx, pc);
}

}  // namespace p3fes::native::kernel
