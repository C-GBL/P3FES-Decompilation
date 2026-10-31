// The EE kernel / timing HLE (ADR-0013 §3; rules: docs/ANALYSIS/15_ee_kernel_semantics.md §8).
//
// One `Kernel` owns, for one EEContext + EEMemory:
//   * the `HwBus` (range map of the EE register windows) and the virtual time base,
//   * INTC (0x1000F000/10), timers T0-T3 (0x10000000-0x10001FFF), the DMAC register block
//     (0x10008000-0x1000EFFF, D_ENABLER/W 0x1000F520/0x1000F590) with tag chains and the SPR
//     channels 8/9 (other channels' data paths are `DmaChannelHandler`s installed by their owners),
//   * the INTC/DMAC handler chains, the EE syscalls, the fiber scheduler (one fiber per guest thread on
//     the host thread that calls `run`; runtime/hle/kernel/fiber.h), and the `RtHooks` implementation the
//     rt adapter calls (`hooks()`).
// See runtime/hle/kernel/README.md for the model, its invariants and the K-row mapping.
//
// Threading: everything is single-threaded (ADR-0013 §1). `run`/`run_until`/`~Kernel` must be called
// on the host thread from outside guest code (the "host fiber"); `hooks()` and `bus()` are called by
// guest code (recompiled functions, the adapter, device models) on guest fibers.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/rt_hooks.h"

#include <array>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace p3fes {
class StateIo;  // p3fes/state_io.h
}

namespace p3fes::hle {

// Same type as `p3fes::rt::Fn` (recomp/include/p3fes_recomp_rt.h): the entry signature of every
// recompiled function. Spelled here so this header does not depend on the adapter API.
using GuestFn = void (*)(EEContext&);

// A syscall implemented outside the kernel (the SIF module installs 0x76-0x7A and may replace
// Deci2Call 0x7C). Called for both the positive and the negative (`i*`) form of the slot;
// `number` is the signed value of $v1. Arguments are in ctx ($a0-$a3, $t0-$t3 per the EE ABI). The
// return value is stored into $v0 (low 64 bits). The function must not block, must not switch
// threads and must not call positive syscalls; it may call `bus()` (raise_intc, dma_complete) and
// read/write guest memory. The kernel never reschedules after an installed syscall.
using SyscallFn = std::function<u64(EEContext& ctx, int number)>;

// A device model's periodic work (ADR-0013 §2: devices are called back at check points, never on a host
// timer; the SIF/IOP model needs "service me at cycle T" for its reboot, CDVD latency and queued packets,
// and "after every VBLANK_START" for PADMAN frames). The function performs whatever is due at the current
// virtual time (`bus().time()`) and returns the earliest `Timebase::cycles` at which it must run again
// (UINT64_MAX: nothing timed). The kernel calls every registered service, in registration order:
//   * once at `start`,
//   * when the earliest returned deadline is reached (a time-base event: slow check points and the idle
//     loop advance to it like to any other event),
//   * right after each VBLANK_START is processed (before its INTC handlers run),
//   * after every syscall served by an installed SyscallFn (so a deadline created by the call is seen).
// Like a SyscallFn it must not block or switch threads; it may use bus() (raise_intc, dma_complete) and
// guest memory. A returned deadline <= now is taken as now + 1 (never a busy loop).
using DeviceServiceFn = std::function<u64()>;

struct FatalInfo {
    u32 pc = 0;          // ctx.pc at the time (whatever the adapter last stored)
    u32 v1 = 0;          // $v1 (the syscall number for syscall-related fatals)
    int thread = -1;     // current guest thread id (0 = idle)
    std::string message; // full text, including the three values above
};

struct KernelOptions {
    // Host stack reserved per guest-thread fiber (recompiled frames are shallow but vfprintf-class
    // recursion exists). Committed lazily by Windows.
    std::size_t fiber_stack_bytes = 1u << 20;

    // Function lookup for handler/thread entry VAs. nullptr = `p3fes::rt::lookup_func` (the generated
    // dispatch table); tests install their own table.
    GuestFn (*lookup)(u32 va) = nullptr;

    // Recompiled code band: a `SetSyscall`-installed handler inside it (libkernel's kCopy*/kFindAddress)
    // is executed as a recompiled function; outside it (the kseg0 kernel-patch payloads) it is HLE'd
    // or trapped (README "Installed syscalls").
    u32 code_begin = 0x00100000u;
    u32 code_end = 0x005A1400u;

    // ExecPS2 argument vector copied by SetupThread into crt0's args block (`15` §3). inf: EELOAD passes
    // the SYSTEM.CNF BOOT2 path; PCSX2's exact string is unverified.
    std::vector<std::string> argv = {"cdrom0:\\SLUS_216.21;1"};

    // COP0 Status of the main thread at `start` and of every created thread (inf: crt0 executes `ei`
    // at 0x1001F8, so the main thread is taken to start with EIE clear; created threads with EIE set).
    // Bits: IE 0, KSU=user 3-4, IM2 10, IM3 11, EIE 16, EDI 17, CU0-2 28-30.
    u32 main_status = 0x70020C11u;
    u32 thread_status = 0x70030C11u;

    // Virtual-time costs of modelled work (ADR-0013 §2; first estimates, to be re-weighted from PCSX2).
    u64 syscall_cycles = 0;
    u64 dma_base_cycles = 64;      // per channel start -> completion
    u64 dma_cycles_per_qword = 2;  // BUSCLK = EE/2, one qword per bus cycle (inf)
    u64 dma_stall_retry_cycles = 64;
    // While an interrupt is deliverable but the CPU has it masked (DI / Status), the next check point at
    // least this many cycles later re-tests it (the adapter is not required to call check_events after EI).
    u64 masked_poll_cycles = 64;
    // No runnable thread and nothing woke one within this much virtual time -> fatal (deadlock).
    u64 idle_limit_cycles = 294'912'000ull * 30;

    // Values the kernel reports.
    u32 osd_config_param = 0;  // initial Get/SetOsdConfigParam word (H-22); inf
    u32 machine_type = 0;      // H-24 (ROM word 0xBFC001F8 = 0 in the user's dump)
    u32 memory_size = 0x02000000u;
    bool gs_early_model = true;  // H-23 / Q-03: GS revision < 0x19 -> _GetGsDxDyOffset reports 0 offsets
    // SetSyscall also stores the word into the kernel's table image in guest RAM at 0x80015500 + 4n,
    // as the real kernel does (`15` §7), so libkernel's FindAddress finds it (tracediff fidelity).
    bool mirror_syscall_table = true;
    // Thread context frames in guest memory, as the BIOS kernel keeps them (`15` §3; BIOS 0x80003680 save /
    // 0x80003800 restore, 0x280 bytes: SA, FCSR, ACC, GPRs 1-25 at 16*r, HI/HI1/LO/LO1, gp/sp/fp/ra, FPRs): the
    // positive switching set, SleepThread, WaitSema, ExitThread(Delete) and an interrupt-exit preemption save
    // the full context at the thread's sp - 0x280 (and the kernel's later `sd v0` / `sw -1` patches of it);
    // CreateThread, SetupThread and a reset to DORMANT write gp/sp/fp/ra at stack+size-0x2A0, StartThread its
    // argument, and a thread starts from that frame. false: the context lives only in the host TCB (the guest
    // stack bytes below sp then differ from hardware).
    bool context_frames = true;

    // Fatal sink: called with the diagnostic; the run then ends with RunStatus::Fatal (the guest fiber is
    // abandoned). nullptr = print to stderr and std::abort().
    std::function<void(const FatalInfo&)> fatal_sink;
    // Log sink for _print and kernel warnings; nullptr = stderr.
    std::function<void(std::string_view)> log_sink;
};

enum class RunStatus {
    MainExited,  // the main thread returned from its entry or called ExitThread/ExitDeleteThread
    Fatal,       // a fatal/trap with a sink installed (sticky: later runs return Fatal at once)
    Stopped,     // run_until's predicate became true (resumable)
};
struct RunResult {
    RunStatus status = RunStatus::MainExited;
    std::string message;
};

// Read-only views for tests and tools.
struct ThreadView {
    u32 status = 0;  // 0 free, 1 RUN, 2 READY, 4 WAIT, 8 SUSPEND, 0xC WAITSUSPEND, 0x10 DORMANT (`15` §3)
    int init_priority = 0;
    int priority = 0;
    u32 wakeup_count = 0;
    u32 wait_type = 0;  // 0 none, 1 sleep, 2 semaphore
    u32 wait_id = 0;
    u32 heap_end = 0;
    bool has_fiber = false;
    u32 entry = 0, stack = 0, stack_size = 0;  // CreateThread / SetupThread parameters
    u32 frame = 0;                             // context frame in guest memory (KernelOptions::context_frames)
    u32 saved_sp = 0;  // $sp of the context the TCB holds (while not running; the start sp before the first run)
};
struct UnhandledAccess {
    u32 pa = 0;
    u32 width = 0;  // bits: 8, 16, 32, 64, 128
    bool write = false;
    u64 value = 0;  // low 64 bits of the written value (0 for reads)
    u32 pc = 0;     // ctx.pc at the access
};
struct GsCrtSetting {
    bool set = false;
    u32 interlace = 0, mode = 0, ffmd = 0;  // mode after 0/1 -> NTSC (2) resolution
};

// Layer 6's inventory (docs/MODERNIZE_PLAN.md "Layer 6 status"; `--kernel-census FILE`): what one run asks of the
// kernel and its timing devices, and who asks. Host-side counters only (Kernel::enable_census): nothing the guest
// sees changes, and with the census off (the default) the kernel runs exactly as before. "Caller" is $ra at the
// call (the libkernel stubs are leaves, so $ra is the game function that called the stub).
struct KernelCensus {
    struct Count2 {
        u64 reads = 0, writes = 0;
    };
    struct SemaUse {
        u64 creates = 0, waits = 0, blocked = 0, signals = 0, isignals = 0, polls = 0, deletes = 0;
        s32 init = 0, max = 0;
        u32 creator = 0;  // $ra of the first CreateSema that returned this id
    };
    std::array<u64, 256> syscalls{}, isyscalls{};  // by slot; isyscalls = the negative (i*) form
    std::map<u64, u64> syscall_sites;              // (neg << 40 | slot << 32 | caller) -> calls
    std::array<u64, 15> intc_chains{};             // handler chains run, by cause
    std::array<u64, 16> dmac_chains{};             // by channel
    std::map<u32, u64> handler_runs;               // enabled handler VA -> calls
    std::array<u64, 10> dma_starts{}, dma_chain_starts{}, dma_qwords{}, dma_stalls{}, dma_rearms{}, dma_busy_polls{};
    std::array<Count2, 4> timer_regs{};            // T0-T3 register accesses
    std::array<u64, 4> timer_irqs{};
    Count2 intc_regs{}, dmac_ctrl_regs{};          // INTC_STAT/MASK; D_CTRL/D_STAT/D_PCR/...
    u64 thread_creates = 0, thread_starts = 0, thread_exits = 0;
    u64 switches = 0;        // fiber switches (a different thread runs)
    u64 preemptions = 0;     // interrupt-exit reschedules (an i* call inside a chain readied a higher thread)
    u64 idle_steps = 0, idle_cycles = 0;  // the idle thread's virtual-time jumps
    u64 direct_calls = 0;  // kernel calls served through Kernel::direct_call (layer 6, --native kernel) instead of `syscall`
    u64 slow_checks = 0, masked_polls = 0, services = 0, vblanks = 0;
    std::map<s32, SemaUse> semas;
    std::map<u32, Count2> bus;                     // every guest access to a hardware register, by 16-byte register
    std::map<u64, u64> bus_sites;                  // (pa16 << 32 | caller) -> accesses
};

class KernelHooks;  // implementation (runtime/hle/kernel/kernel_core.h)

// The kernel's name for syscall slot 0..255 (ps2sdk numbering, `02`; "undefined" for empty slots), for
// diagnostics and traces.
const char* syscall_name(u32 slot);

class Kernel {
public:
    Kernel(EEMemory& mem, EEContext& ctx, KernelOptions options = {});
    ~Kernel();
    Kernel(const Kernel&) = delete;
    Kernel& operator=(const Kernel&) = delete;

    HwBus& bus();
    RtHooks& hooks();
    // Layer 6 (--native kernel, p3fes/native/kernel_service.h): a kernel call the game makes through its libkernel stub
    // ($v1 = the call number as the stub set it, arguments in $a0..; `pc` = the stub's syscall address), served as a
    // direct host call: the same service, $v0, scheduling and closing check point as the `syscall` instruction's
    // (hooks().syscall), so the guest sees the same result at the same virtual time. With KernelOptions::context_frames
    // off (what the layer sets) no call writes a BIOS context frame into the guest stack.
    void direct_call(EEContext& ctx, u32 pc);
    // HwBus::map without the fatal: false when [b, e) is not 16-byte aligned, leaves the EE/GS register
    // windows, or overlaps an existing mapping (nothing is mapped then).
    bool try_map(u32 pa_begin, u32 pa_end, HwDevice* dev);

    // Creates the main thread (tid 1, priority 0 - ExecPS2 semantics, `15` §3) running `main_fn` on its
    // own fiber, with the register state currently in ctx. Does not run it.
    void start(GuestFn main_fn);
    // start(main_fn) + run_until(nullptr): runs until the main thread exits or a fatal is raised.
    RunResult run(GuestFn main_fn);
    // Resumes guest execution (after `start`, or a previous Stopped result) until `stop` returns true at a
    // thread-level check point / syscall exit / idle event step, the main thread exits, or a fatal.
    // `stop == nullptr` runs to completion. The first call converts the host thread to a fiber.
    RunResult run_until(std::function<bool()> stop);
    // run_until(the next time-base event has been processed).
    RunResult step_to_next_event();

    // The 32 MiB physical RAM image (ADR-0013 §4 `--snapshot-at`, PCSX2 eeMemory.bin layout; RAM only).
    bool snapshot_eemem(const std::string& path) const;

    // Machine state (runtime/STATE.md): the kernel's whole dynamic state and the host stack of every live
    // guest-thread fiber. Save between run_until calls after a Stopped result; load into a freshly built, never
    // started kernel (same wiring and options), then run_until resumes where the saver stopped. Needs the pinned
    // regions (p3fes/pinned.h) enabled before the kernel was constructed. false + io.fail(reason) otherwise.
    bool state(StateIo& io);

    // Registers an out-of-kernel syscall for slot `number` (0..255; a negative number names the same
    // slot). Returns false if the slot already has an installed SyscallFn. See SyscallFn.
    bool install_syscall(int number, SyscallFn fn);
    // Registers a device service (see DeviceServiceFn). Call before `start`.
    void add_device_service(DeviceServiceFn fn);
    // Host-side stop without a per-check-point predicate: the running `run_until` returns
    // RunStatus::Stopped at the next thread-level check point (before that point's interrupt delivery
    // when requested from a device service or a time-base event, after the chain when requested from
    // inside a handler chain, e.g. a GS flip callback). Resumable like any Stopped result.
    void request_stop();
    // Retry a stalled DMA channel now instead of at the next stall-retry event: a data path that just
    // became able to accept data (the GIF after VIF1's `MSKPATH3 off`, runtime/gs) calls this so the
    // transfer proceeds inside the window the guest's packet opened for it. No-op unless the channel is
    // active and stalled; safe from inside another channel's data path (per-channel re-entrancy guard).
    void retry_dma_now(int ch);
    // COP2 control writes that address the VU1 side (CTC2 to vi28 FBRST; RtHooks::vu_control_write) go to
    // this handler (runtime/gs owns VU1). nullptr: ignored.
    void set_vu_control_handler(std::function<void(u32 reg, u32 value)> fn);

    // Layer 6's inventory (KernelCensus): start counting (idempotent); census() is null until then.
    void enable_census();
    const KernelCensus* census() const;

    // Inspection.
    const Timebase& time() const;
    int current_thread() const;
    ThreadView thread(int tid) const;
    u32 intc_stat() const;
    u32 intc_mask() const;
    u32 d_stat() const;
    u64 events_processed() const;
    u64 unhandled_accesses() const;
    std::vector<UnhandledAccess> unhandled_log() const;  // oldest first, at most 256 entries
    bool syscall_installed(int slot) const;               // recorded by the guest's SetSyscall
    u32 syscall_address(int slot) const;
    u32 cause12_dispatcher() const;                       // SetSyscall(0x12C, x) -> x (0 = never)
    GsCrtSetting gs_crt() const;
    u64 gs_imr() const;
    int handler_count(bool dmac, int cause_or_channel) const;
    // Address of the next event deadline in cycles; `check_events` returns at once while
    // ctx.cycles < *deadline. An adapter may inline this compare before the virtual call.
    const u64* next_deadline() const;

private:
    std::unique_ptr<KernelHooks> core_;
};

} // namespace p3fes::hle
