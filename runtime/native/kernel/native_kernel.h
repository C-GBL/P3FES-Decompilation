// Modernize layer 6, step 1: kernel and timing (docs/MODERNIZE_PLAN.md "Layer 6 status", ADR-0017,
// p3fes/native/kernel_service.h). The host's answer to the game's kernel calls under `--native kernel`.
//
// The (a) set -- nothing the game observes per vblank changes, so the user's recordings stay valid:
//   * the call path: the game's libkernel stubs call the host kernel directly (hle::Kernel::direct_call) instead of
//     executing `syscall` -- the same service, $v0, scheduling and closing check point, so the same guest memory and
//     virtual time byte for byte (the six old routes' gates).
// The (b) set (`--native-kernel-timing host`, configure()) changes what the game observes on purpose and needs
// re-recorded routes:
//   * the thread contexts on the host only (KernelOptions::context_frames off): the BIOS context frames the faithful
//     kernel writes at a waiting thread's sp - 0x280 are not written. The game reads them back -- uninitialised stack
//     slots of its functions, copied whole into its records (the CD cache sCdvdCache 0x7D6F80 first) -- so its memory
//     differs from vblank 20 on and the battle route desyncs;
//   * no DMA completion latency (a channel completes when its data phase ends), the native movie decode instant
//     (layer 4's per-call cycle model off), the native SK sound stack called by sceSdRemote without SIF (layer 3's
//     `--native-sk direct`).
// What stays in both: the scheduler (fibers, ADR-0013), virtual time, INTC / DMAC / timers and the handler chains.
#pragma once

#include <array>
#include <cstdint>

#include "p3fes/hle/kernel.h"
#include "p3fes/native/kernel_service.h"

namespace p3fes::native::kernel {

// --native-kernel-timing: faithful (the default: the (a) set only) or host (the (b) set too; see the file comment).
enum class Timing : std::uint8_t { Faithful, Host };
bool parse_timing(const char* s, Timing& out);  // "faithful" | "host"
const char* to_string(Timing t);

// The kernel options the layer sets before the kernel is built: nothing for Timing::Faithful; for Timing::Host no
// context frames and no DMA completion latency.
void configure(hle::KernelOptions& o, Timing t);

class NativeKernel final : public KernelService {
public:
    explicit NativeKernel(hle::Kernel& k) : k_(k) {}
    void call(EEContext& ctx, u32 pc) override;

    // Calls served, by call number (|$v1|, 0..255) and form.
    struct Stats {
        std::array<u64, 256> calls{}, icalls{};
        u64 total = 0;
    };
    const Stats& stats() const { return stats_; }

private:
    hle::Kernel& k_;
    Stats stats_{};
};

}  // namespace p3fes::native::kernel
