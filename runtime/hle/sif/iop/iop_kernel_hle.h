// IOP kernel HLE for the SK/libsd modules the IOP HLE interprets (ADR-0014; docs/ANALYSIS/19 §2.1):
// module loading (irx_loader.h) on the R3000 interpreter (r3000.h), the ~40 kernel imports the six
// modules use -- thbase, thsemap, timrman, intrman, sysmem, loadcore, sysclib, stdio, sifcmd -- and the
// libsd imports (libsd_hle.h). Everything runs on the host thread, on virtual time (ADR-0013): the
// owner moves `now` (EE cycles) and the kernel fires what is due.
//
// Threads are run-to-block coroutines on the interpreter: a thread table and a scheduler that runs the
// highest-priority ready thread (FIFO within a level, like the IOP's) until it sleeps, waits on a
// semaphore, delays, blocks in sceSifRpcLoop, or exits; readying a higher-priority thread from a host
// call preempts the current one (StartThread / WakeupThread / SignalSema reschedule at once; the `i*`
// forms are called from the interrupt context here, where no thread runs). Hard timers (timrman) fire
// their handler on an interrupt context at `start + compare` IOP clocks (36.864 MHz = EE / 8) and
// re-arm by the handler's return value (SKSOUND's handler 0x1140 returns its compare count, so the SK
// tick is periodic: USec2SysClock(4,167) = 153,612 clocks = 1,228,896 EE cycles). GetSystemTime is
// EE cycles / 8. Semantics follow ps2sdk @ 329e2bb's kernel headers (AFL-2.0; names, layouts and
// documented return values only) and `15`'s IOP-side observations; `inf` where neither says.
//
// RPC (increment 2): sceSifRegisterRpc / SetRpcQueue / RpcLoop are recorded, and `rpc_dispatch` runs a
// registered handler on its own queue thread -- the thread blocked in sceSifRpcLoop is given the handler's
// frame (a0 = fno, a1 = buffer, a2 = size, ra = a host-call trampoline) and put back to its wait when the
// handler returns; the reply is `recv_size` bytes at the returned pointer, as sifrpc's rpc_request_end sends.
// A handler that blocks leaves the call pending; `rpc_poll` finishes it after more virtual time.
//
// Memory placement: the kernel's own allocations (module images, stacks, argv, the modules' AllocSysMemory)
// come from `set_alloc_ranges` (first fit, in order) so the game's heap RPC allocations keep their addresses;
// `set_fixed_base` pins a module image to the address PCSX2 loaded it at (the IOP-identity class of the
// snapshot diffs). Without ranges everything comes from the IOP heap (the unit tests' set-up).
//
// What is not here: no preemption of a running thread by a timer (the interpreter only runs between
// EE check points, when every IOP thread is blocked), no alarms, event flags, message boxes or
// pools (nothing imports them), no interrupt lines (intrman's Register/Enable are recorded only),
// no module unloading beyond freeing a module whose start returned NO_RESIDENT_END.
#pragma once

#include <deque>
#include <functional>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "iop_core.h"
#include "irx_loader.h"
#include "libsd_hle.h"
#include "r3000.h"

namespace p3fes::hle::sif::iop {

inline constexpr u64 kIopClocksPerEeCycle = 8;             // EE 294,912,000 / IOP 36,864,000
inline constexpr u64 kEeCyclesPerUsec = 294'912'000ull;    // / 1,000,000 (applied in the helpers)
inline constexpr int kModuleStartPriority = 8;             // loadcore starts module entries at 8 (inf)
inline constexpr u32 kModuleStartStack = 0x1000u;
inline constexpr u64 kSliceBudget = 50'000'000ull;         // instructions one scheduler slice may run (runaway guard)

enum class ThreadStatus { Dormant, Ready, Run, Wait };
enum class WaitKind { None, Sleep, Delay, Sema, Rpc };

struct KernelThread {
    int id = 0;
    std::string owner;      // module name the entry belongs to (diagnostics)
    u32 attr = 0, option = 0, entry = 0, stack = 0, stack_size = 0, gp = 0;
    int init_priority = 0, priority = 0;
    ThreadStatus status = ThreadStatus::Dormant;
    WaitKind wait = WaitKind::None;
    int wait_id = 0;
    u64 wait_until = 0;     // EE cycles (Delay)
    int wakeups = 0;
    u64 ready_seq = 0;      // FIFO order within a priority level
    R3000State ctx{};
    u32 exit_value = 0;
    u64 runs = 0;           // times scheduled
    u64 instructions = 0;   // retired on this thread
};

struct KernelSema {
    int id = 0;
    u32 attr = 0, option = 0;
    int count = 0, max = 0;
    std::deque<int> waiters;
};

struct HardTimer {
    int id = 0;
    u32 source = 0, size = 0, prescale = 0, mode = 0;
    u32 compare = 0, handler = 0, common = 0;
    bool running = false;
    u64 start = 0;          // EE cycles at StartHardTimer
    u64 deadline = 0;       // EE cycles of the next handler run
    u64 fired = 0;
};

struct GuestLibrary {
    std::string name;
    u16 version = 0;
    u32 table = 0;
    std::vector<u32> functions;
    int module_id = 0;
    u64 order = 0;          // registration order
};

struct RpcServerRecord {   // sceSifRegisterRpc; rpc_dispatch routes EE calls through these
    u32 sd = 0, sid = 0, func = 0, buf = 0, cfunc = 0, cbuf = 0, queue = 0;
    int queue_thread = 0;
};

struct LoadedIrx {
    int id = 0;
    std::string path;
    IrxModule info;
    std::vector<UnresolvedImport> unresolved;
    int start_thread = 0;
    s32 start_result = 0;        // 0 RESIDENT_END, 1 NO_RESIDENT_END, 2 REMOVABLE_RESIDENT_END
    bool start_returned = false;
    u64 start_instructions = 0;  // interpreted during _start (all threads it ran)
    u32 argv = 0;
    u32 block = 0;               // allocation start (the 0x30-byte ModuleInfo precedes the image at base)
    bool resident = true;        // false: start returned NO_RESIDENT_END and the image was freed
};

class IopKernel final : public ImportBinder {
public:
    IopKernel(detail::IopRam& ram, LibsdHle& libsd, std::function<void(std::string_view)> log = {});

    // ---- placement -----------------------------------------------------------------------------------------
    // Where the kernel's own allocations go (tried in order, first fit); empty = the IOP heap.
    void set_alloc_ranges(std::vector<std::pair<u32, u32>> ranges) { ranges_ = std::move(ranges); }
    // Pins the image of the module whose file name (upper case, e.g. "SDRDRV.IRX") is `file` to `base`.
    void set_fixed_base(std::string file, u32 base) { fixed_bases_[std::move(file)] = base; }
    // Called whenever the kernel's clock moves (each deadline in advance_to, and its end), before anything
    // runs at that instant: the voice model renders up to there (p3fes/audio/spu2_voice.h).
    void set_time_hook(std::function<void(u64 ee_cycles)> hook) { time_hook_ = std::move(hook); }

    // ---- time (EE cycles; virtual) ---------------------------------------------------------------------
    u64 now() const { return now_; }
    u64 iop_clock() const { return now_ / kIopClocksPerEeCycle; }
    // Fires every timer / delay due up to `ee_cycles` in deadline order, running the threads they ready
    // to their next block each time, then sets now. Returns the number of hard-timer handler runs.
    u64 advance_to(u64 ee_cycles);
    u64 next_deadline() const;  // kNever when nothing is armed

    // ---- modules -------------------------------------------------------------------------------------
    // Loads `file` (an IRX image) into the IOP heap, binds its imports, runs its entry on a module-start
    // thread until it returns (or everything blocks) and records its result. nullopt + `error` on a load
    // failure; an unresolved import is not a failure (listed in LoadedIrx::unresolved, trapped if called).
    std::optional<LoadedIrx> load_module(std::span<const u8> file, std::string_view path, std::string_view args, std::string& error);

    // ---- running -------------------------------------------------------------------------------------
    void run_until_idle();  // runs ready threads until none is ready or a fault occurs
    // Calls a guest function from the host on a transient top-priority thread (a0..a3 = args) and returns
    // v0 once it returns; nullopt + `error` if it blocked or faulted (tests, direct export calls).
    std::optional<u32> call(u32 fn, std::span<const u32> args, std::string& error);
    // Runs the handler registered for `sid` on its queue thread with (fno, buf, size); returns the handler's
    // result (the reply pointer) when it returned within this run. nullopt: pending (rpc_pending() true,
    // finish with rpc_poll after advance_to) or an error (`error` set, rpc_pending() false).
    std::optional<u32> rpc_dispatch(u32 sid, u32 fno, u32 buf, u32 size, std::string& error);
    bool rpc_pending() const { return rpc_.active && !rpc_.done; }
    std::optional<u32> rpc_poll();  // the result once a pending handler returned
    bool has_rpc_server(u32 sid) const;
    const RpcServerRecord* rpc_server(u32 sid) const;

    // ---- ImportBinder ---------------------------------------------------------------------------------
    ImportTarget resolve(std::string_view library, u16 ordinal) override;

    // ---- inspection -------------------------------------------------------------------------------------
    const std::string& fault() const { return fault_; }  // first fatal problem; empty = none
    const std::vector<LoadedIrx>& modules() const { return modules_; }
    const std::map<int, KernelThread>& threads() const { return threads_; }
    const std::map<int, KernelSema>& semas() const { return semas_; }
    const std::map<int, HardTimer>& timers() const { return timers_; }
    const std::vector<GuestLibrary>& libraries() const { return libraries_; }  // registration order
    const std::vector<RpcServerRecord>& rpc_servers() const { return rpc_servers_; }
    const std::vector<std::string>& printf_log() const { return printf_log_; }
    u64 timer_handler_runs() const { return handler_runs_; }
    u64 instructions() const { return cpu_.instructions(); }
    R3000& cpu() { return cpu_; }
    detail::IopRam& ram() { return ram_; }
    LibsdHle& libsd() { return libsd_; }
    // Host-call ids by (library, ordinal); the kernel's own libraries plus libsd.
    const std::map<std::pair<std::string, u16>, u32>& host_calls() const { return host_calls_; }
    int current_thread() const { return current_; }
    u64 rpc_calls() const { return rpc_calls_; }
    u64 rpc_pending_runs() const { return rpc_pending_runs_; }
    void state(StateIo& io);  // machine state (iop_state.cpp); host calls / options are wiring

private:
    detail::IopRam& ram_;
    LibsdHle& libsd_;
    std::function<void(std::string_view)> log_;
    R3000 cpu_;
    std::map<std::pair<std::string, u16>, u32> host_calls_;
    u32 trap_id_ = 0;  // "unresolved import" host call

    u64 now_ = 0;
    std::string fault_;
    std::vector<std::string> printf_log_;

    std::map<int, KernelThread> threads_;
    int next_thread_id_ = 1;
    int current_ = 0;        // running thread id, 0 = none (interrupt context or idle)
    u64 ready_counter_ = 0;
    bool in_handler_ = false;

    std::map<int, KernelSema> semas_;
    int next_sema_id_ = 1;
    std::map<int, HardTimer> timers_;
    int next_timer_id_ = 1;
    u64 handler_runs_ = 0;
    int suspend_depth_ = 0;

    std::vector<GuestLibrary> libraries_;
    std::vector<LoadedIrx> modules_;
    int next_module_id_ = 1;
    std::vector<RpcServerRecord> rpc_servers_;
    u32 intr_stack_ = 0;     // interrupt-context stack (allocated on first use)

    std::vector<std::pair<u32, u32>> ranges_;
    std::map<std::string, u32> fixed_bases_;
    std::function<void(u64)> time_hook_;

    struct RpcFrame {
        bool active = false, done = false;
        int thread = 0;
        R3000State saved{};
        int saved_wait_id = 0;
        u32 result = 0;
    } rpc_;
    u32 rpc_return_id_ = 0;    // host call the handler returns to
    u32 rpc_return_addr_ = 0;  // its trampoline word in IOP RAM (allocated on first use)
    u64 rpc_calls_ = 0, rpc_pending_runs_ = 0;

    // threads
    int create_thread(u32 attr, u32 option, u32 entry, u32 stack_size, int priority, std::string_view owner);
    bool start_thread(int id, u32 a0, u32 a1);
    KernelThread* pick_ready();
    void make_ready(KernelThread& t);
    void block_current(WaitKind kind, int id);
    void preempt_if_needed();
    KernelThread* current();
    u32 run_handler(u32 fn, u32 a0, u32 gp);
    void fail(std::string what);

    // helpers
    u32 alloc(u32 size);        // the modules' AllocSysMemory: the ranges in order, else the heap
    u32 alloc_kernel(u32 size); // stacks, argv, the interrupt stack: the last range first (the top of RAM, as the IOP kernel does)
    void ensure_setup();       // interrupt stack + RPC trampoline
    void rpc_return(R3000& c);
    std::string format(u32 fmt, unsigned first_arg);
    void def(const char* library, u16 ordinal, const char* name, R3000::HostCall fn);
    void install_calls();
    void rebind_library(const GuestLibrary& lib);
    u32 gp_for(u32 addr) const;
    const char* module_at(u32 addr) const;
};

}  // namespace p3fes::hle::sif::iop
