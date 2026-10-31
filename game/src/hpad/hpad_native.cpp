// Modernize layer 2 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the guest-buffer halves of the pad wrapper's native
// branches (game/include/p3fes/game/input_native.h). Reached only while p3fes::native::input::service() is set
// (`--native input`).
//
// What is *not* done here, on purpose: no libpad call, so libpad's own state stays untouched (its port records
// 0x96DD10, the RPC clients and buffer 0x96DCC0..0x96DF7F, the init flag 0x782748) and so do the two DMA buffers the
// game registered with scePadPortOpen (0x7E0740, 0x7E0840): the layer's exclusion mask
// (tools/ours/modernize/layer2_pad_mask.txt).
#include "p3fes/game/input_native.h"

#include <array>

#include "p3fes/ee_memory.h"

namespace p3fes::game {

namespace {
std::array<u8, 6> guest6(EEContext& ctx, u32 src) {
    std::array<u8, 6> b{};
    for (u32 i = 0; i < 6; ++i) b[i] = ctx.memory->read<u8>(src + i);
    return b;
}
}  // namespace

u32 hpad_native_read(EEContext& ctx, native::input::PadService& ps, u32 port, u32 slot, u32 dst) {
    std::array<u8, 32> data{};
    const u32 n = ps.read(port, slot, data);
    for (u32 i = 0; i < n && i < 32; ++i) ctx.memory->write<u8>(dst + i, data[i]);
    return n;
}

u32 hpad_native_act_align(EEContext& ctx, native::input::PadService& ps, u32 port, u32 slot, u32 src) {
    const std::array<u8, 6> b = guest6(ctx, src);
    return ps.set_act_align(port, slot, b);
}

u32 hpad_native_act_direct(EEContext& ctx, native::input::PadService& ps, u32 port, u32 slot, u32 src) {
    const std::array<u8, 6> b = guest6(ctx, src);
    return ps.set_act_direct(port, slot, b);
}

}  // namespace p3fes::game
