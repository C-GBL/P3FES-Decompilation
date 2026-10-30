#include "p3fes/ee_memory.h"

#include "p3fes/pinned.h"
#include "p3fes/state_io.h"

namespace p3fes {

namespace {
// The pinned arena (zero-filled, never freed) when the host enabled it, else the heap.
u8* region(std::size_t bytes) {
    if (void* p = pinned::alloc(bytes, 4096)) return static_cast<u8*>(p);
    return new u8[bytes]();
}
} // namespace

void EEMemory::RegionDelete::operator()(u8* p) const noexcept {
    if (!pinned::owns(p)) delete[] p;
}

EEMemory::EEMemory()
    : main_ram_(region(kMainRamSize)),
      scratchpad_(region(kScratchpadSize)),
      bios_(region(kBiosSize)) {}

void EEMemory::state(StateIo& io) {
    io.section("ee-memory");
    io.raw(main_ram_.get(), kMainRamSize);
    io.raw(scratchpad_.get(), kScratchpadSize);
    io.raw(bios_.get(), kBiosSize);
    io(unmapped_accesses_);
}

EEMemory::~EEMemory() = default;

const u8* EEMemory::resolve(u32 vaddr, u32 len) const noexcept {
    // Scratchpad is only reachable through its dedicated virtual range and is
    // not part of the physical window, so check it before masking.
    if (is_scratchpad(vaddr)) {
        const u32 off = vaddr - kScratchpadBase;
        if (len <= kScratchpadSize - off) {
            return scratchpad_.get() + off;
        }
        return nullptr;
    }

    const u32 phys = to_physical(vaddr);

    if (phys < kMainRamSize) {
        if (len <= kMainRamSize - phys) {
            return main_ram_.get() + phys;
        }
        return nullptr;
    }

    if (phys >= kBiosBase && phys - kBiosBase < kBiosSize) {
        const u32 off = phys - kBiosBase;
        if (len <= kBiosSize - off) {
            return bios_.get() + off;
        }
        return nullptr;
    }

    // Hardware registers / GS privileged registers: not backed by flat memory.
    // The rt adapter checks `is_hw()` after a failed resolve and routes the
    // access to RtHooks::bus() (ADR-0013); `read`/`write` count it as unmapped.
    return nullptr;
}

u8* EEMemory::resolve(u32 vaddr, u32 len) noexcept {
    return const_cast<u8*>(static_cast<const EEMemory*>(this)->resolve(vaddr, len));
}

} // namespace p3fes
