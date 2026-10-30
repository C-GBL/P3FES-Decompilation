// Shared rig for the kernel HLE tests. "Recompiled functions" are host functions with the rt::Fn
// signature that read/write the context; they are registered at synthetic VAs in a test-only lookup table
// (also exported as p3fes::rt::lookup_func so the kernel library links without recomp/generated).
#pragma once

#include "p3fes/hle/kernel.h"

#include <doctest.h>

#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace kt {

using namespace p3fes;
using namespace p3fes::hle;

GuestFn test_lookup(u32 va);
void register_fn(u32 va, GuestFn fn);

struct Rig;
extern Rig* g_rig;

// A device that records accesses and answers reads with a programmable value.
struct RecDevice final : HwDevice {
    struct Access {
        u32 pa;
        u32 width;
        bool write;
        u64 value;
    };
    std::vector<Access> log;
    u64 answer = 0;
    u32 read32(u32 pa) override { log.push_back({pa, 32, false, 0}); return static_cast<u32>(answer); }
    void write32(u32 pa, u32 v) override { log.push_back({pa, 32, true, v}); }
    u64 read64(u32 pa) override { log.push_back({pa, 64, false, 0}); return answer; }
    void write64(u32 pa, u64 v) override { log.push_back({pa, 64, true, v}); }
    u128 read128(u32 pa) override { log.push_back({pa, 128, false, 0}); return u128::from_u64(answer); }
    void write128(u32 pa, const u128& v) override { log.push_back({pa, 128, true, v.lo()}); }
    u8 read8(u32 pa) override { log.push_back({pa, 8, false, 0}); return static_cast<u8>(answer); }
    u16 read16(u32 pa) override { log.push_back({pa, 16, false, 0}); return static_cast<u16>(answer); }
    void write8(u32 pa, u8 v) override { log.push_back({pa, 8, true, v}); }
    void write16(u32 pa, u16 v) override { log.push_back({pa, 16, true, v}); }
};

// GS privileged registers as far as the kernel's tests need them: CSR.FIELD from the time base, IMR storage.
struct FakeGs final : HwDevice {
    HwBus* bus = nullptr;
    u64 imr = 0;
    std::vector<u64> imr_writes;
    u64 read64(u32 pa) override {
        if (pa == 0x12001000u) return static_cast<u64>(bus->time().field) << 13;
        if (pa == 0x12001010u) return imr;
        return 0;
    }
    void write64(u32 pa, u64 v) override {
        if (pa == 0x12001010u) {
            imr = v;
            imr_writes.push_back(v);
        }
    }
    u32 read32(u32 pa) override { return static_cast<u32>(read64(pa & ~7u) >> ((pa & 4u) * 8u)); }
};

struct Rig {
    EEMemory mem;
    EEContext ctx;
    std::vector<std::string> fatals;
    std::vector<std::string> logs;
    FakeGs gs;
    std::unique_ptr<Kernel> k;

    explicit Rig(KernelOptions o = {}) {
        ctx.memory = &mem;
        o.lookup = &test_lookup;
        o.fatal_sink = [this](const FatalInfo& f) { fatals.push_back(f.message); };
        o.log_sink = [this](std::string_view s) { logs.emplace_back(s); };
        k = std::make_unique<Kernel>(mem, ctx, std::move(o));
        gs.bus = &k->bus();
        k->bus().map(0x12001000u, 0x12001020u, &gs);
        g_rig = this;
    }
    ~Rig() {
        k.reset();
        if (g_rig == this) g_rig = nullptr;
    }
    RtHooks& hooks() { return k->hooks(); }
    HwBus& bus() { return k->bus(); }

    u32 r32(u32 va) const { return mem.read<u32>(va); }
    void w32(u32 va, u32 v) { mem.write<u32>(va, v); }
};

inline void set_reg(EEContext& c, unsigned r, s64 v) { c.gpr[r].u64[0] = static_cast<u64>(v); }

// Issue a syscall from guest code: $v1 = num, $a0..$a3, $t0, then the kernel; returns $v0.
inline s64 sys(EEContext& c, int num, s64 a0 = 0, s64 a1 = 0, s64 a2 = 0, s64 a3 = 0, s64 t0 = 0) {
    set_reg(c, GPR_V1, num);
    set_reg(c, GPR_A0, a0);
    set_reg(c, GPR_A1, a1);
    set_reg(c, GPR_A2, a2);
    set_reg(c, GPR_A3, a3);
    set_reg(c, GPR_T0, t0);
    g_rig->hooks().syscall(c, 0x00001000u);
    return static_cast<s64>(c.gpr[GPR_V0].u64[0]);
}

// Spend `n` cycles of "guest work" and pass a check point (a loop back-edge in generated code).
inline void work(EEContext& c, u64 n) {
    c.cycles += n;
    g_rig->hooks().check_events(c);
}

// Guest memory layout used by the tests (all well inside RAM, away from 0x0-0x80000 kernel area).
inline constexpr u32 kParamVa = 0x00200000u;  // CreateThread / CreateSema parameter blocks
inline constexpr u32 kScratchVa = 0x00210000u;

// CreateThread(param) with entry VA, stack, size, gp, priority (param block at kParamVa + slot*0x40).
inline s64 create_thread(EEContext& c, u32 entry, int prio, u32 stack, u32 size = 0x1000, u32 gp = 0x7D2CF0u,
                         int slot = 0) {
    const u32 p = kParamVa + static_cast<u32>(slot) * 0x40u;
    Rig& r = *g_rig;
    for (u32 i = 0; i < 0x40; i += 4) r.w32(p + i, 0);
    r.w32(p + 4, entry);
    r.w32(p + 8, stack);
    r.w32(p + 0xC, size);
    r.w32(p + 0x10, gp);
    r.w32(p + 0x14, static_cast<u32>(prio));
    return sys(c, 0x20, p);
}

inline s64 create_sema(EEContext& c, s32 init, s32 max, u32 attr = 0, int slot = 0) {
    const u32 p = kParamVa + 0x1000u + static_cast<u32>(slot) * 0x20u;
    Rig& r = *g_rig;
    r.w32(p + 0, 0);
    r.w32(p + 4, static_cast<u32>(max));
    r.w32(p + 8, static_cast<u32>(init));
    r.w32(p + 0xC, 0);
    r.w32(p + 0x10, attr);
    r.w32(p + 0x14, 0);
    return sys(c, 0x40, p);
}

// Syscall numbers used by the tests (ps2sdk syscallnr.h numbering, docs/ANALYSIS/02).
enum Sc : int {
    kAddIntcHandler = 0x10, kRemoveIntcHandler = 0x11, kAddDmacHandler = 0x12, kRemoveDmacHandler = 0x13,
    kEnableIntc = 0x14, kDisableIntc = 0x15, kEnableDmac = 0x16, kDisableDmac = 0x17,
    kCreateThread = 0x20, kDeleteThread = 0x21, kStartThread = 0x22, kExitThread = 0x23, kExitDeleteThread = 0x24,
    kTerminateThread = 0x25, kChangeThreadPriority = 0x29, kRotateThreadReadyQueue = 0x2B,
    kReleaseWaitThread = 0x2D, kGetThreadId = 0x2F, kReferThreadStatus = 0x30, kSleepThread = 0x32,
    kWakeupThread = 0x33, kiWakeupThread = -0x34, kCancelWakeupThread = 0x35, kSuspendThread = 0x37,
    kResumeThread = 0x39, kSetupThread = 0x3C, kSetupHeap = 0x3D, kEndOfHeap = 0x3E,
    kCreateSema = 0x40, kDeleteSema = 0x41, kSignalSema = 0x42, kiSignalSema = -0x43, kWaitSema = 0x44,
    kPollSema = 0x45, kReferSemaStatus = 0x47, kSetVSyncFlag = 0x73, kSetSyscall = 0x74,
};

} // namespace kt
