// Flat model of the Emotion Engine's physical memory.
//
// Address-space assumptions (to be re-verified against the game's TLB usage
// in Phase 2; retail titles run with the kernel's default identity TLB):
//
//   Virtual                      Physical                 Notes
//   0x00000000-0x01FFFFFF  ->    0x00000000-0x01FFFFFF    KUSEG main RAM, cached
//   0x20000000-0x21FFFFFF  ->    0x00000000-0x01FFFFFF    KUSEG main RAM, uncached
//   0x30000000-0x31FFFFFF  ->    0x00000000-0x01FFFFFF    KUSEG main RAM, uncached accelerated
//   0x70000000-0x70003FFF  ->    (scratchpad, 16 KiB)     only reachable through this range
//   0x10000000-0x1000FFFF  ->    0x10000000-0x1000FFFF    EE hardware registers (DMAC/INTC/timers/VIF/GIF/SIF/IPU)
//   0x12000000-0x12001FFF  ->    0x12000000-0x12001FFF    GS privileged registers
//   0x1FC00000-0x1FFFFFFF  ->    0x1FC00000-0x1FFFFFFF    BIOS ROM (4 MiB)
//   0x80000000-0x9FFFFFFF  ->    addr & 0x1FFFFFFF        KSEG0 (cached) window on all of the above
//   0xA0000000-0xBFFFFFFF  ->    addr & 0x1FFFFFFF        KSEG1 (uncached) window on all of the above
//
// Caching attributes are irrelevant to a static recompile and are ignored.
// The hardware register windows are deliberately *not* backed here: `resolve()`
// returns nullptr for them and `read`/`write` count them as unmapped. `is_hw()`
// (ADR-0013) tells the rt adapter (runtime/rt/) to route such an access to the
// device models through `RtHooks::bus()` at the physical address instead.
#pragma once

#include "p3fes/ee_types.h"

#include <cstring>
#include <memory>
#include <type_traits>

namespace p3fes {

class StateIo;  // p3fes/state_io.h

class EEMemory {
public:
    static constexpr u32 kMainRamBase    = 0x00000000;
    static constexpr u32 kMainRamSize    = 32u * 1024u * 1024u;   // 32 MiB
    static constexpr u32 kScratchpadBase = 0x70000000;
    static constexpr u32 kScratchpadSize = 16u * 1024u;           // 16 KiB
    static constexpr u32 kBiosBase       = 0x1FC00000;
    static constexpr u32 kBiosSize       = 4u * 1024u * 1024u;    // 4 MiB
    static constexpr u32 kHwRegBase      = 0x10000000;
    static constexpr u32 kHwRegSize      = 0x00010000;
    static constexpr u32 kGsPrivBase     = 0x12000000;
    static constexpr u32 kGsPrivSize     = 0x00002000;

    // Fold KSEG0/KSEG1 and the KUSEG mirrors onto the 512 MiB physical window.
    // The 0x3xxxxxxx "uncached accelerated" mirror needs an explicit case:
    // `& 0x1FFFFFFF` alone would land it on the hardware-register region.
    // Not meaningful for the scratchpad; use `resolve()` for a full lookup.
    static constexpr u32 to_physical(u32 vaddr) noexcept {
        if ((vaddr >> 28) == 0x3u) {
            return vaddr & 0x0FFFFFFFu;
        }
        return vaddr & 0x1FFFFFFFu;
    }

    static constexpr bool is_scratchpad(u32 vaddr) noexcept {
        return (vaddr & ~(kScratchpadSize - 1u)) == kScratchpadBase;
    }

    // Physical hardware-register windows (ADR-0013): EE registers
    // 0x10000000-0x1000FFFF and GS privileged registers 0x12000000-0x12001FFF.
    static constexpr bool is_hw_physical(u32 paddr) noexcept {
        return (paddr - kHwRegBase) < kHwRegSize || (paddr - kGsPrivBase) < kGsPrivSize;
    }

    // Does the guest virtual address reach a hardware-register window? Only
    // through the identity KUSEG range (0x00000000-0x1FFFFFFF, the retail
    // kernel's TLB maps 0x10000000/0x12000000 one-to-one) and the KSEG0/KSEG1
    // windows (0x80000000-0xBFFFFFFF); the RAM mirrors at 0x2/0x3/0x4... and the
    // scratchpad segment never do, even where `& 0x1FFFFFFF` would fold onto a
    // register address (e.g. 0x70004000 -> 0x10004000). The physical address to
    // hand to the device is `to_physical(vaddr)`.
    static constexpr bool is_hw(u32 vaddr) noexcept {
        const u32 seg = vaddr >> 29;  // 0 = KUSEG low 512 MiB, 4 = KSEG0, 5 = KSEG1
        if (seg != 0u && seg != 4u && seg != 5u) return false;
        return is_hw_physical(vaddr & 0x1FFFFFFFu);
    }

    EEMemory();
    ~EEMemory();

    EEMemory(const EEMemory&) = delete;
    EEMemory& operator=(const EEMemory&) = delete;

    // Resolve a guest virtual address to host storage. Returns nullptr when
    // `len` bytes starting at `vaddr` are not fully inside one backed region.
    u8*       resolve(u32 vaddr, u32 len) noexcept;
    const u8* resolve(u32 vaddr, u32 len) const noexcept;

    // Hot path of the rt adapter (recomp/include/p3fes_recomp_rt_inline.h): host pointer for a
    // naturally aligned `len`-byte access (len a power of two <= 16) that lies in main RAM (any
    // mirror, the same folding as resolve()) or in the scratchpad; nullptr for everything else
    // (BIOS window, hardware windows, unmapped, misaligned), which resolve() / the adapter's slow
    // path then classify. Alignment plus `phys < kMainRamSize` guarantees the access never crosses
    // the end of RAM.
#if defined(_MSC_VER) && !defined(__clang__)
    __forceinline
#endif
    u8* fast_ptr(u32 vaddr, u32 len) noexcept {
        if ((vaddr & (len - 1u)) != 0) return nullptr;
        const u32 phys = to_physical(vaddr);
        if (phys < kMainRamSize) return main_ram_.get() + phys;
        if (is_scratchpad(vaddr)) return scratchpad_.get() + (vaddr - kScratchpadBase);
        return nullptr;
    }

    // Main-RAM branch of resolve(), inline: the same pointer for every access that lies wholly in main RAM (any
    // mirror; the scratchpad segment never folds below kMainRamSize), nullptr where resolve() must decide.
    u8* ram_ptr(u32 vaddr, u32 len) const noexcept {
        const u32 phys = to_physical(vaddr);
        return phys <= kMainRamSize - len ? main_ram_.get() + phys : nullptr;
    }

    template <typename T>
    T read(u32 vaddr) const noexcept {
        static_assert(std::is_trivially_copyable_v<T>);
        T v{};
        if (const u8* q = ram_ptr(vaddr, static_cast<u32>(sizeof(T)))) {
            std::memcpy(&v, q, sizeof(T));
        } else if (const u8* p = resolve(vaddr, static_cast<u32>(sizeof(T)))) {
            std::memcpy(&v, p, sizeof(T));
        } else {
            ++unmapped_accesses_;
        }
        return v;
    }

    template <typename T>
    void write(u32 vaddr, const T& v) noexcept {
        static_assert(std::is_trivially_copyable_v<T>);
        if (u8* q = ram_ptr(vaddr, static_cast<u32>(sizeof(T)))) {
            std::memcpy(q, &v, sizeof(T));
        } else if (u8* p = resolve(vaddr, static_cast<u32>(sizeof(T)))) {
            std::memcpy(p, &v, sizeof(T));
        } else {
            ++unmapped_accesses_;
        }
    }

    // Raw region access for loaders (ELF segments, BIOS image, DMA models).
    u8*       main_ram() noexcept { return main_ram_.get(); }
    const u8* main_ram() const noexcept { return main_ram_.get(); }
    u8*       scratchpad() noexcept { return scratchpad_.get(); }
    u8*       bios() noexcept { return bios_.get(); }

    // Number of reads/writes that hit no backed region since construction or
    // the last `reset_unmapped_accesses()`.
    u64  unmapped_accesses() const noexcept { return unmapped_accesses_; }
    void reset_unmapped_accesses() noexcept { unmapped_accesses_ = 0; }

    // Machine state (p3fes/state_io.h): RAM, scratchpad, BIOS window and the unmapped-access count.
    void state(StateIo& io);

private:
    // Regions come from the pinned arena when the host enabled it (p3fes/pinned.h: guest-thread frames hold
    // pointers into RAM, so a saved machine state needs RAM at the same address in every process), else new[].
    struct RegionDelete {
        void operator()(u8* p) const noexcept;
    };
    std::unique_ptr<u8[], RegionDelete> main_ram_;
    std::unique_ptr<u8[], RegionDelete> scratchpad_;
    std::unique_ptr<u8[], RegionDelete> bios_;
    mutable u64 unmapped_accesses_ = 0;
};

} // namespace p3fes
