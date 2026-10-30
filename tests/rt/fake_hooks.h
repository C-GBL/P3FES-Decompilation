// Test doubles for the rt adapter: an RtHooks that records every call and turns RtHooks::fatal into a
// C++ exception (so a fatal path is testable and an unexpected one fails the test), and an HwBus that
// logs each access with its width and serves reads from a register map (unmapped registers read a
// pattern derived from the address).
#pragma once

#include <doctest.h>

#include "p3fes/hle/hw_bus.h"
#include "p3fes/rt/rt_adapter.h"
#include "p3fes/rt_hooks.h"

#include <map>
#include <string>
#include <vector>

namespace p3fes::rt_test {

struct FatalEvent {
    u32 pc;
    std::string what;
    const EEContext* ctx;
};

class RecordingBus final : public hle::HwBus {
public:
    struct Access {
        bool write;
        unsigned bits;
        u32 pa;
        u64 lo;
        u64 hi;
    };
    std::vector<Access> log;
    std::map<u32, u64> regs;  // pa -> value for reads (64-bit); writes store here too
    hle::Timebase tb;

    // Default read pattern for registers not in `regs`.
    static u64 pattern(u32 pa) noexcept { return (static_cast<u64>(pa ^ 0x5A5A5A5Au) << 32) | (pa ^ 0xA5A5A5A5u); }
    u64 value(u32 pa) const {
        auto it = regs.find(pa);
        return it != regs.end() ? it->second : pattern(pa);
    }

    void map(u32, u32, hle::HwDevice*) override {}
    void set_dma_handler(unsigned, hle::DmaChannelHandler*) override {}
    void raise_intc(unsigned) override {}
    void dma_complete(unsigned) override {}
    const hle::Timebase& time() const override { return tb; }

    u8 read8(u32 pa) override { log.push_back({false, 8, pa, 0, 0}); return static_cast<u8>(value(pa)); }
    u16 read16(u32 pa) override { log.push_back({false, 16, pa, 0, 0}); return static_cast<u16>(value(pa)); }
    u32 read32(u32 pa) override { log.push_back({false, 32, pa, 0, 0}); return static_cast<u32>(value(pa)); }
    u64 read64(u32 pa) override { log.push_back({false, 64, pa, 0, 0}); return value(pa); }
    u128 read128(u32 pa) override {
        log.push_back({false, 128, pa, 0, 0});
        u128 r;
        r.u64[0] = value(pa);
        r.u64[1] = ~value(pa);
        return r;
    }
    void write8(u32 pa, u8 v) override { log.push_back({true, 8, pa, v, 0}); regs[pa] = v; }
    void write16(u32 pa, u16 v) override { log.push_back({true, 16, pa, v, 0}); regs[pa] = v; }
    void write32(u32 pa, u32 v) override { log.push_back({true, 32, pa, v, 0}); regs[pa] = v; }
    void write64(u32 pa, u64 v) override { log.push_back({true, 64, pa, v, 0}); regs[pa] = v; }
    void write128(u32 pa, const u128& v) override { log.push_back({true, 128, pa, v.u64[0], v.u64[1]}); regs[pa] = v.u64[0]; }
};

class TestHooks final : public RtHooks {
public:
    RecordingBus bus_;
    int syscalls = 0;
    u32 syscall_pc = 0;
    u64 syscall_v1 = 0;
    int checks = 0;
    u64 checks_at_cycles = 0;  // ctx.cycles seen by the last check
    int traps = 0;
    u32 trap_pc = 0, trap_kind = 0xFFFFFFFFu, trap_code = 0;

    void syscall(EEContext& ctx, u32 pc) override {
        ++syscalls;
        syscall_pc = pc;
        syscall_v1 = ctx.gpr[GPR_V1].u64[0];
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;  // a result the test can observe
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        checks_at_cycles = ctx.cycles;
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32 pc, u32 kind, u32 code) override {
        ++traps;
        trap_pc = pc;
        trap_kind = kind;
        trap_code = code;
    }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { throw FatalEvent{pc, what, &ctx}; }
    std::vector<std::pair<u32, u32>> vu_control;  // vu_control_write(reg, value)
    void vu_control_write(EEContext&, u32 reg, u32 value) override { vu_control.emplace_back(reg, value); }
};

// Installs `h` for the scope and restores the aborting default afterwards.
struct HooksScope {
    explicit HooksScope(RtHooks* h) { set_hooks(h); }
    ~HooksScope() {
        set_hooks(nullptr);
        rt::bind_context(nullptr);
    }
    HooksScope(const HooksScope&) = delete;
    HooksScope& operator=(const HooksScope&) = delete;
};

} // namespace p3fes::rt_test

namespace doctest {
template <>
struct StringMaker<p3fes::rt_test::FatalEvent> {
    static String convert(const p3fes::rt_test::FatalEvent& e) { return String(e.what.c_str()); }
};
} // namespace doctest
