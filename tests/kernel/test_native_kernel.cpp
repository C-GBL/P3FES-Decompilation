// Modernize layer 6, step 1 (runtime/native/kernel/native_kernel.h, docs/MODERNIZE_PLAN.md "Layer 6 status"): the
// game's kernel calls served as direct host calls (NativeKernel -> Kernel::direct_call, the (a) set of `--native kernel`)
// give the faithful kernel's results, scheduling, virtual time and guest memory, and with the host-only contexts of the
// (b) set (KernelOptions::context_frames off) the same results and time with nothing written below any thread's sp --
// one scenario (threads, semaphores, sleep / wakeup, priorities, a released wait, an invalid WaitSema, an i* call from
// a VBLANK handler) run three ways and compared line by line; the census counts the direct calls; configure() and the
// --native-kernel-timing names.
#include "kernel_test_util.h"
#include "native_kernel.h"

#include <cstring>
#include <string>

using namespace kt;
namespace nk = p3fes::native::kernel;

namespace {

std::vector<std::string> L;
s64 g_tid[4] = {};
s64 g_sema[2] = {};
nk::NativeKernel* g_nk = nullptr;  // set: the layer-6 path (the game's stubs call the service), else `syscall`

void lg(const std::string& s) { L.push_back(s); }

// One kernel call as a libkernel stub makes it: $v1 = num, arguments, then the instruction or the service.
s64 kcall(EEContext& c, int num, s64 a0 = 0, s64 a1 = 0, s64 a2 = 0) {
    set_reg(c, GPR_V1, num);
    set_reg(c, GPR_A0, a0);
    set_reg(c, GPR_A1, a1);
    set_reg(c, GPR_A2, a2);
    if (g_nk) g_nk->call(c, 0x00502F70u);
    else g_rig->hooks().syscall(c, 0x00502F70u);
    return static_cast<s64>(c.gpr[GPR_V0].u64[0]);
}
std::string hex(u64 v) {
    char b[24];
    std::snprintf(b, sizeof b, "%llX", static_cast<unsigned long long>(v));
    return b;
}
void note(EEContext& c, const std::string& what, s64 v) { lg(what + "=" + hex(static_cast<u64>(v)) + " @" + std::to_string(c.cycles)); }

constexpr u32 kTA = 0x00400000u, kTB = 0x00400100u, kH = 0x00401000u, kRoot = 0x00100220u;
constexpr u32 kStack = 0x01000000u, kSize = 0x1000u;
constexpr u32 kMainSp = 0x01800000u;

s64 create_thread_k(EEContext& c, u32 entry, int prio, u32 stack, int slot) {
    const u32 p = kParamVa + static_cast<u32>(slot) * 0x40u;
    for (u32 i = 0; i < 0x40; i += 4) g_rig->w32(p + i, 0);
    g_rig->w32(p + 4, entry);
    g_rig->w32(p + 8, stack);
    g_rig->w32(p + 0xC, kSize);
    g_rig->w32(p + 0x10, 0x7D2CF0u);
    g_rig->w32(p + 0x14, static_cast<u32>(prio));
    return kcall(c, kCreateThread, p);
}
s64 create_sema_k(EEContext& c, s32 init, int slot) {
    const u32 p = kParamVa + 0x1000u + static_cast<u32>(slot) * 0x20u;
    for (u32 i = 0; i < 0x20; i += 4) g_rig->w32(p + i, 0);
    g_rig->w32(p + 4, 4);
    g_rig->w32(p + 8, static_cast<u32>(init));
    return kcall(c, kCreateSema, p);
}

void register_all() {
    register_fn(kRoot, [](EEContext& c) { kcall(c, kExitThread); });
    register_fn(kTA, [](EEContext& c) {  // the waiter: blocks on sema 0, then on sema 1 (deleted under it)
        note(c, "A.s0", static_cast<s64>(c.gpr[GPR_S0].u64[0]));
        note(c, "A.a0", static_cast<s64>(c.gpr[GPR_A0].u64[0]));
        note(c, "A.wait0", kcall(c, kWaitSema, g_sema[0]));
        note(c, "A.wait1", kcall(c, kWaitSema, g_sema[1]));  // released by DeleteSema: $v0 0x00000000FFFFFFFF
        note(c, "A.sleep", kcall(c, kSleepThread));
        lg("A.end");
    });
    register_fn(kTB, [](EEContext& c) {  // a lower-priority worker spending virtual time
        for (int i = 0; i < 6; ++i) {
            c.cycles += 1'500'000;
            g_rig->hooks().check_events(c);
            note(c, "B.tick", i);
        }
        note(c, "B.prio", kcall(c, kChangeThreadPriority, 0, 40));
        note(c, "B.wake", kcall(c, kWakeupThread, 1));  // the main thread (tid 1)
    });
    register_fn(kH, [](EEContext& c) {  // a VBLANK_START handler: iWakeupThread(A) from interrupt context
        set_reg(c, GPR_V1, kiWakeupThread);
        set_reg(c, GPR_A0, g_tid[0]);
        if (g_nk) g_nk->call(c, 0x00504050u);
        else g_rig->hooks().syscall(c, 0x00504050u);
        set_reg(c, GPR_V0, 0);
    });
}

// How a scenario runs: the faithful kernel (`syscall`, BIOS frames); layer 6's (a) set (`--native kernel`: the stubs
// call the service, frames kept); and the host-only contexts of the (b) set (`--native-kernel-timing host`: no frames).
enum class Mode { Faithful, Native, HostContexts };

struct Result {
    std::vector<std::string> log;
    std::vector<u32> mem;  // the stack areas after the run
};

Result scenario(Mode mode) {
    L.clear();
    register_all();
    KernelOptions o;
    if (mode != Mode::Faithful) nk::configure(o, mode == Mode::Native ? nk::Timing::Faithful : nk::Timing::Host);
    o.dma_base_cycles = KernelOptions{}.dma_base_cycles;  // the scenario has no DMA; keep the time model the same
    o.dma_cycles_per_qword = KernelOptions{}.dma_cycles_per_qword;
    Rig r(o);
    r.k->enable_census();
    std::unique_ptr<nk::NativeKernel> svc;
    if (mode != Mode::Faithful) svc = std::make_unique<nk::NativeKernel>(*r.k);
    g_nk = svc.get();
    // Guest memory under the threads' stacks: a pattern, so a write by the kernel would show.
    for (u32 a = kStack; a < kStack + 0x3000u; a += 4) r.w32(a, 0xA5A50000u | (a & 0xFFFFu));
    for (u32 a = kMainSp - 0x1000u; a < kMainSp; a += 4) r.w32(a, 0x5A5A0000u | (a & 0xFFFFu));
    const RunResult res = r.k->run([](EEContext& c) {
        set_reg(c, GPR_SP, kMainSp);
        c.cop0[12] |= 1u << 16;  // EIE: the handler may run
        note(c, "prio", kcall(c, kChangeThreadPriority, 0, 30));
        g_sema[0] = create_sema_k(c, 0, 0);
        g_sema[1] = create_sema_k(c, 0, 1);
        g_tid[0] = create_thread_k(c, kTA, 10, kStack, 0);
        g_tid[1] = create_thread_k(c, kTB, 35, kStack + 0x1000u, 1);
        note(c, "tidA", g_tid[0]);
        note(c, "startA", kcall(c, kStartThread, g_tid[0], 0x55));  // A runs at once (higher), blocks on sema 0
        note(c, "startB", kcall(c, kStartThread, g_tid[1], 0x66));
        note(c, "bad-wait", kcall(c, kWaitSema, 300));  // invalid id: the wrapper returns $a0
        note(c, "signal0", kcall(c, kSignalSema, g_sema[0]));  // A wakes, preempts, blocks on sema 1
        note(c, "delete1", kcall(c, kDeleteSema, g_sema[1]));  // A released (-1 low word), sleeps
        note(c, "add", kcall(c, kAddIntcHandler, 2, kH, 0));
        note(c, "en", kcall(c, kEnableIntc, 2));
        note(c, "sleep-main", kcall(c, kSleepThread));  // B runs; the VBLANK handler wakes A; A ends
        lg("main.end");
    });
    if (res.status != RunStatus::MainExited) lg("status " + std::to_string(static_cast<int>(res.status)));
    for (const std::string& f : r.fatals) lg("fatal " + f);
    Result out;
    u32 changed = 0;
    for (u32 a = kStack; a < kStack + 0x2000u; a += 4) {
        out.mem.push_back(r.r32(a));
        if (r.r32(a) != (0xA5A50000u | (a & 0xFFFFu))) ++changed;
    }
    for (u32 a = kMainSp - 0x1000u; a < kMainSp; a += 4) {
        out.mem.push_back(r.r32(a));
        if (r.r32(a) != (0x5A5A0000u | (a & 0xFFFFu))) ++changed;
    }
    if (mode == Mode::HostContexts) CHECK(changed == 0);  // no BIOS frame anywhere below the stacks' tops
    else CHECK(changed > 0);                              // the BIOS frames
    if (svc) {
        CHECK(r.k->census()->direct_calls == svc->stats().total);
        CHECK(svc->stats().total > 15);
        CHECK(svc->stats().icalls[0x34] == 1);  // the handler's iWakeupThread
    } else {
        CHECK(r.k->census()->direct_calls == 0);
    }
    g_nk = nullptr;
    out.log = L;
    return out;
}

}  // namespace

TEST_CASE("layer 6: direct kernel calls give the faithful results, memory and virtual time; host-only contexts the same results") {
    const Result faithful = scenario(Mode::Faithful);
    const Result native = scenario(Mode::Native);
    const Result host = scenario(Mode::HostContexts);
    CHECK(native.log == faithful.log);
    CHECK(native.mem == faithful.mem);  // (a): byte for byte, frames included
    CHECK(host.log == faithful.log);    // (b)'s host-only contexts: the same results at the same time ...
    CHECK(host.mem != faithful.mem);    // ... but not the bytes the game could read back from dead stack
    // The rules the scenario pins: A's start registers come from its fresh frame's slot, the invalid WaitSema returns
    // its id, the released wait the low word -1, the handler's wakeup ends A.
    auto has = [&](const std::string& prefix) {
        for (const std::string& s : faithful.log)
            if (s.rfind(prefix, 0) == 0) return true;
        return false;
    };
    CHECK(has("A.s0=A5A50E64A5A50E60"));  // the fresh frame at kStack + 0x1000 - 0x2A0 = 0x01000D60, $s0 at +0x100
    CHECK(has("A.a0=A5A50DA400000055"));  // +0x40: StartThread's word over the pattern
    CHECK(has("bad-wait=12C"));
    CHECK(has("A.wait1=FFFFFFFF"));
    CHECK(has("A.end"));
    CHECK(has("main.end"));
    for (std::size_t i = 0; i < faithful.log.size() && i < host.log.size(); ++i)
        if (faithful.log[i] != host.log[i]) MESSAGE("first difference at " << i << ": " << faithful.log[i] << " | " << host.log[i]);
}

TEST_CASE("layer 6: configure() and the --native-kernel-timing names") {
    KernelOptions o;
    nk::configure(o, nk::Timing::Faithful);
    CHECK(o.context_frames);  // (a): the frames stay (the game reads them back)
    CHECK(o.dma_base_cycles == KernelOptions{}.dma_base_cycles);
    CHECK(o.dma_cycles_per_qword == KernelOptions{}.dma_cycles_per_qword);
    KernelOptions h;
    nk::configure(h, nk::Timing::Host);
    CHECK_FALSE(h.context_frames);
    CHECK(h.dma_base_cycles == 0);
    CHECK(h.dma_cycles_per_qword == 0);
    nk::Timing t = nk::Timing::Host;
    CHECK(nk::parse_timing("faithful", t));
    CHECK(t == nk::Timing::Faithful);
    CHECK(nk::parse_timing("host", t));
    CHECK(t == nk::Timing::Host);
    CHECK_FALSE(nk::parse_timing("fast", t));
    CHECK(std::strcmp(nk::to_string(nk::Timing::Host), "host") == 0);
    CHECK(std::strcmp(nk::to_string(nk::Timing::Faithful), "faithful") == 0);
}

TEST_CASE("layer 6: the census counts what a run asks of the kernel and changes nothing") {
    L.clear();
    register_all();
    Rig r;
    r.k->enable_census();
    r.k->enable_census();  // idempotent
    REQUIRE(r.k->census() != nullptr);
    r.k->run([](EEContext& c) {
        g_sema[0] = create_sema_k(c, 1, 0);
        kcall(c, kWaitSema, g_sema[0]);
        kcall(c, kPollSema, g_sema[0]);
        kcall(c, kSignalSema, g_sema[0]);
        g_rig->bus().read32(0x1000F000u);  // INTC_STAT
        while (g_rig->k->time().vblanks < 2) work(c, 100'000);
    });
    const KernelCensus& k = *r.k->census();
    CHECK(k.syscalls[0x40] == 1);
    CHECK(k.syscalls[0x44] == 1);
    CHECK(k.syscalls[0x45] == 1);
    CHECK(k.syscalls[0x42] == 1);
    REQUIRE(k.semas.count(static_cast<s32>(g_sema[0])) == 1);
    const KernelCensus::SemaUse& u = k.semas.at(static_cast<s32>(g_sema[0]));
    CHECK(u.creates == 1);
    CHECK(u.waits == 1);
    CHECK(u.blocked == 0);
    CHECK(u.polls == 1);
    CHECK(u.signals == 1);
    CHECK(k.vblanks == 2);
    CHECK(k.intc_regs.reads == 1);
    CHECK(k.bus.at(0x1000F000u).reads == 1);
    CHECK(k.slow_checks > 0);
}
