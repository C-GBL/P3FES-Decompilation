#include "p3fes/pinned.h"

#include <windows.h>

#include <cstdio>

namespace p3fes::pinned {

namespace {
bool g_tried = false;
bool g_enabled = false;
std::size_t g_used = 0;       // bytes handed out
std::size_t g_committed = 0;  // bytes committed from the base
bool g_slot_committed[kFiberSlots] = {};
} // namespace

bool enable() {
    if (g_tried) return g_enabled;
    g_tried = true;
    void* a = VirtualAlloc(reinterpret_cast<void*>(kArenaBase), kArenaBytes, MEM_RESERVE, PAGE_NOACCESS);
    if (a != reinterpret_cast<void*>(kArenaBase)) {
        if (a) VirtualFree(a, 0, MEM_RELEASE);
        std::fprintf(stderr, "p3fes: pinned arena at 0x%llX unavailable (error %lu): machine states disabled\n",
                     static_cast<unsigned long long>(kArenaBase), GetLastError());
        return false;
    }
    void* f = VirtualAlloc(reinterpret_cast<void*>(kFiberBase), kFiberSlots * kFiberSlotStride, MEM_RESERVE, PAGE_NOACCESS);
    if (f != reinterpret_cast<void*>(kFiberBase)) {
        if (f) VirtualFree(f, 0, MEM_RELEASE);
        VirtualFree(a, 0, MEM_RELEASE);
        std::fprintf(stderr, "p3fes: pinned fiber region at 0x%llX unavailable (error %lu): machine states disabled\n",
                     static_cast<unsigned long long>(kFiberBase), GetLastError());
        return false;
    }
    g_enabled = true;
    return true;
}

bool enabled() { return g_enabled; }

void* alloc(std::size_t bytes, std::size_t align) {
    if (!g_enabled || bytes == 0) return nullptr;
    if (align < 16) align = 16;
    const std::size_t start = (g_used + align - 1) & ~(align - 1);
    if (start > kArenaBytes || bytes > kArenaBytes - start) return nullptr;
    const std::size_t end = start + bytes;
    if (end > g_committed) {
        const std::size_t want = (end + 0xFFFFu) & ~std::size_t{0xFFFFu};
        if (!VirtualAlloc(reinterpret_cast<void*>(kArenaBase + g_committed), want - g_committed, MEM_COMMIT, PAGE_READWRITE))
            return nullptr;
        g_committed = want;
    }
    g_used = end;
    return reinterpret_cast<void*>(kArenaBase + start);
}

std::size_t arena_used() { return g_used; }

bool owns(const void* p) {
    const auto a = reinterpret_cast<std::uintptr_t>(p);
    return g_enabled && a >= kArenaBase && a < kArenaBase + kArenaBytes;
}

void* fiber_slot_lo(std::size_t i) {
    if (!g_enabled || i >= kFiberSlots) return nullptr;
    void* lo = reinterpret_cast<void*>(kFiberBase + i * kFiberSlotStride + kFiberGuardBytes);
    if (!g_slot_committed[i]) {
        if (!VirtualAlloc(lo, kFiberStackBytes, MEM_COMMIT, PAGE_READWRITE)) return nullptr;
        g_slot_committed[i] = true;
    }
    return lo;
}

void* fiber_slot_hi(std::size_t i) {
    void* lo = fiber_slot_lo(i);
    return lo ? static_cast<char*>(lo) + kFiberStackBytes : nullptr;
}

} // namespace p3fes::pinned
