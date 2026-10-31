// NativeSk: the Standard Kit sound-effect stack on native code (modernize layer 3, steps 2-3; docs/MODERNIZE_PLAN.md
// section 3, runtime/native/sound/sk/README.md). SDRDRV, SKSOUND, SKHSYNTH, SKSESQ, MODSESQ and MODHSYN run as the C++
// tools/ours/modernize/skgen.py made from the user's IRX files (sk_gen_*.cpp) instead of on the R3000 interpreter, and
// what they import runs here: libsd goes to the IOP model's libsd over the SPU2 voice model (SkPort::libsd, the same
// LibsdHle the interpreted modules drive, whose voices the mixer plays), the kernel (threads, semaphores, the hard
// timer, sysmem, sysclib, sifcmd's RPC server records) is this class, written to answer exactly as the interpreter's
// kernel (runtime/hle/sif/iop/iop_kernel_hle.cpp) does, on virtual time:
//   * Threads run to their block: a blocking import (SleepThread, WaitSema, sceSifRpcLoop) parks the thread, which
//     resumes at the instruction after it when woken. A thread readied by a running one with a higher priority runs
//     at once (strict priority, FIFO within a level), the `i*` forms from the timer handler do not preempt.
//   * The SK tick: SKSOUND's hard timer fires its handler on an interrupt context at start + compare IOP clocks
//     (EE cycles / 8) and re-arms from its return value (4,167 us); the woken tick thread then runs MODSESQ /
//     MODHSYN's ticks. advance(now) fires what is due in deadline order, telling the port the time first.
//   * RPC: sceSdRemote's request (p3fes/native/sound_service.h sd_remote) lands in SDRDRV's own receive buffer and its
//     handler (+0x588) runs on the RPC thread's stack, as sceSifRpcLoop would call it; the reply is the bytes at the
//     pointer it returns. No SIF command, no SIF DMA, no loadfile: the modules' data sections are read from the IRX
//     files at their faithful image bases (IopLayout::Pcsx2) and their start functions run when the game would have
//     loaded them (kwlnInitPS2Systems).
// Memory: the IOP RAM model (SkPort::ram), because the game's own H_Sndcom uploads the HD / SQ banks there through
// sceSifAllocSysMemory + SIF DMA and passes their IOP addresses in the bind commands; the modules' work areas and
// thread stacks come from the same kernel ranges the faithful path uses (SkPort::alloc_*), so every IOP address
// (and so every reply) is the faithful one.
#pragma once

#include <array>
#include <deque>
#include <functional>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "sk_cpu.h"

namespace p3fes {
class StateIo;
}

namespace p3fes::native::sound::sk {

// What the native SK uses of the IOP model (the host's adapter: runtime/app/game_host.cpp over IopHle).
class SkPort {
public:
    virtual ~SkPort() = default;
    virtual u8* ram() = 0;                                   // IOP RAM, kRamSize bytes
    virtual u32 alloc_at(u32 addr, u32 size) = 0;            // AllocSysMemory mode 2 (0 = refused)
    virtual u32 alloc(u32 size, u32 mode) = 0;               // the IOP heap (no ranges)
    virtual u32 alloc_in(u32 lo, u32 hi, u32 size) = 0;      // first fit inside [lo, hi)
    virtual bool free(u32 addr) = 0;
    virtual u32 libsd(u32 ordinal, const u32 (&args)[5]) = 0; // the libsd ordinal over the voice model, returns v0
    virtual void at_time(u64 ee_cycles) = 0;                 // the voice model renders up to here
    virtual void log(std::string_view line) = 0;
    // One SDRDRV request answered (the --sound-log line and the census, as the faithful server records it).
    virtual void record(u32 fno, std::span<const u8> send, s32 result, u64 ee_cycles) = 0;
};

struct NativeSkStats {
    u32 modules = 0;           // module starts run
    u64 rpc_calls = 0;         // SDRDRV handler runs
    u64 tick_runs = 0;         // hard-timer handler runs
    u64 thread_runs = 0;       // thread entries / resumptions run
    u64 libsd_calls = 0;
    u64 kernel_calls = 0;
    std::string fault;         // the first fault, empty = none
};

class NativeSk {
public:
    explicit NativeSk(SkPort& port);
    ~NativeSk();
    NativeSk(const NativeSk&) = delete;
    NativeSk& operator=(const NativeSk&) = delete;

    // Reads the six IRX files (`read(file name)`: "SDRDRV.IRX" ...), checks that each one's text is the one the code
    // was made from (sk_gen.h kModules text_sha) and keeps their relocated data sections. false + error otherwise.
    bool install(const std::function<std::optional<std::vector<u8>>(std::string_view)>& read, std::string& error);
    bool installed() const { return installed_; }

    // The game loads `path` (with loadfile's NUL-separated `args`) at virtual `now`: for one of the six modules the
    // image's data goes to its base and its start function runs (all threads it readies run to their block); the
    // result is what loadfile answers (>= 0: the module id; the start's return value in `start_result`). A file that
    // is not one of the six (LIBSD.IRX, MODMSIN.IRX: libsd and the MIDI synth's placeholder, HLE'd entries on the
    // faithful path too) only gets an id. -1 after a fault.
    s32 load_module(u64 now, std::string_view path, std::string_view args, s32* start_result = nullptr);
    // SDRDRV's RPC 0x80000701 at virtual `now`: `send` lands in its receive buffer, the handler runs with (fno,
    // buffer, size); returns the reply (max(recv_size, 16) bytes at the pointer the handler returned), nullopt when
    // the native stack cannot answer (not loaded, faulted).
    std::optional<std::vector<u8>> rpc(u64 now, u32 fno, std::span<const u8> send, u32 recv_size);
    // sceSdRemote's call: rpc() plus the --sound-log line; the reply goes to `recv` (zeros when the stack cannot answer,
    // after a fault, which is logged once). The game takes this path only while the stack is installed.
    void sd_remote(u64 now, u32 fno, std::span<const u8> send, std::span<u8> recv);
    // Fires every timer due up to `now` (EE cycles) in deadline order, running the threads it wakes (nothing before
    // the first module start: the faithful kernel exists from then on).
    void advance(u64 now);
    u64 next_deadline() const;  // ~0 when nothing is armed
    u64 now() const { return now_; }
    // The RPC handler's return address (the interpreter's kernel keeps a host-call trampoline word there; natively it
    // is only an address the handler returns to).
    u32 rpc_return_address() const { return rpc_return_; }

    const NativeSkStats& stats() const { return st_; }
    void fail(std::string what);
    bool faulted() const { return !st_.fault.empty(); }
    // Machine state (runtime/STATE.md): the kernel's threads, semaphores, timers and the CPU; IOP RAM and libsd are
    // the IOP model's (saved with it).
    void state(StateIo& io);

    // ---- the imports (sk_host.cpp; one per HOST entry skgen.py binds) -------------------------------------------
    Cpu& cpu() { return c_; }
    SkPort& port() { return port_; }
    u64 libsd_call(u32 ordinal);   // a0..a3 + stack -> v0
    void count_kernel() { ++st_.kernel_calls; }

    enum class Status : u8 { Dormant, Ready, Run, Wait };
    enum class Wait : u8 { None, Sleep, Sema, Rpc };
    struct Thread {
        int id = 0;
        u32 attr = 0, option = 0, entry = 0, stack = 0, stack_size = 0, gp = 0;
        int init_priority = 0, priority = 0;
        Status status = Status::Dormant;
        Wait wait = Wait::None;
        int wait_id = 0;
        int wakeups = 0;
        u64 ready_seq = 0;
        u32 regs[32]{};
        u32 hi = 0, lo = 0;
        u32 resume = 0;      // 0: start at the entry; else the instruction after the blocking call
        u32 exit_value = 0;
    };
    struct Sema {
        int id = 0;
        u32 attr = 0, option = 0;
        int count = 0, max = 0;
        std::deque<int> waiters;
    };
    struct Timer {
        int id = 0;
        u32 source = 0, size = 0, prescale = 0, mode = 0, compare = 0, handler = 0, common = 0;
        bool running = false;
        u64 start = 0, deadline = 0, fired = 0;
    };
    struct RpcServer {
        u32 sd = 0, sid = 0, func = 0, buf = 0, cfunc = 0, cbuf = 0, queue = 0;
        int queue_thread = 0;
    };

    // kernel services the imports use
    int create_thread(u32 attr, u32 option, u32 entry, u32 stack_size, int priority);
    bool start_thread(int id, u32 a0, u32 a1);
    Thread* thread(int id);
    Thread* current();
    int current_id() const { return current_; }
    bool in_handler() const { return in_handler_; }
    void make_ready(Thread& t);
    void block_current(Wait kind, int id);  // parks the running thread (the generated code unwinds)
    void preempt();                          // runs every ready thread of a higher priority than the current one
    u32 alloc_module(u32 size);              // AllocSysMemory without an address: the kernel ranges in order
    u32 alloc_kernel(u32 size);              // stacks, argv, the interrupt stack: the last range first
    std::map<int, Thread>& threads() { return threads_; }
    std::map<int, Sema>& semas() { return semas_; }
    std::map<int, Timer>& timers() { return timers_; }
    std::vector<RpcServer>& rpc_servers() { return rpc_servers_; }
    const std::vector<RpcServer>& rpc_servers() const { return rpc_servers_; }
    int& suspend_depth() { return suspend_depth_; }
    int next_sema_id() { return next_sema_id_++; }
    int next_timer_id() { return next_timer_id_++; }
    u32 gp_for(u32 addr) const;

private:
    SkPort& port_;
    Cpu c_{};
    bool installed_ = false;
    bool started_ = false;  // the first of the six modules started (the kernel's clock runs from there)
    struct Image {
        std::vector<u8> data;  // the relocated [text, text + data) bytes
        u32 size = 0;          // the image (irx_image_size: text + data + bss or the load segment)
    };
    std::array<Image, 6> images_{};
    std::array<bool, 6> loaded_{};
    int next_module_id_ = 1;

    u64 now_ = 0;
    std::map<int, Thread> threads_;
    int next_thread_id_ = 1;
    int current_ = 0;
    u64 ready_counter_ = 0;
    bool in_handler_ = false;
    std::map<int, Sema> semas_;
    int next_sema_id_ = 1;
    std::map<int, Timer> timers_;
    int next_timer_id_ = 1;
    int suspend_depth_ = 0;
    std::vector<RpcServer> rpc_servers_;
    u32 intr_stack_ = 0, rpc_return_ = 0;
    NativeSkStats st_{};

    void ensure_setup();
    u32 write_argv(std::string_view path, std::string_view args, u32* argc);
    Thread* pick_ready(int above_priority);  // the best ready thread with priority < above (INT_MAX: any)
    void run(Thread& t);                     // runs t to its block / return (nested runs keep the caller's registers)
    void run_until_idle();
    u32 run_handler(u32 fn, u32 a0, u32 gp);
};

}  // namespace p3fes::native::sound::sk
