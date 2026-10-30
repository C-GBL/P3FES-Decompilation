// Internal: the one class behind p3fes::hle::Kernel. It is the RtHooks implementation (KernelHooks),
// the HwBus, the time base, INTC/timers/DMAC, the handler chains, the syscalls and the fiber scheduler.
// Split over several .cpp files by concern (bus_timebase, intc_timers, dmac, interrupts, scheduler,
// syscalls, kernel). Rules cited as `15` §n / H-nn are docs/ANALYSIS/15_ee_kernel_semantics.md.
#pragma once

#include "fiber.h"
#include "p3fes/hle/kernel.h"
#include "p3fes/pinned.h"
#include "p3fes/prof.h"
#include "p3fes/state_io.h"

#include <array>
#include <cstdarg>
#include <deque>
#include <string>
#include <vector>

namespace p3fes::hle {

namespace kc {

inline constexpr u64 kNever = ~0ull;

// ---- Time base (exact rationals; ADR-0013 §2) ------------------------------------------------------
// EE 294,912,000 cycles/s; NTSC field rate 60000/1001 Hz (59.94); 262.5 H-lines per field
// (15,734.27 H-lines/s). cycles per H-line = 294912000*1001/60000/262.5 = 21086208/1125 = 18,743.296;
// cycles per field = 24600576/5 = 4,920,115.2.
inline constexpr u64 kEeHz = 294'912'000ull;
inline constexpr u64 kHlineNum = 21'086'208ull, kHlineDen = 1'125ull;
inline constexpr u64 kFieldNum = 24'600'576ull, kFieldDen = 5ull;
static_assert(kHlineNum * 525ull * kFieldDen == kFieldNum * kHlineDen * 2ull, "262.5 H-lines per field");
static_assert(kFieldNum * 60000ull == kEeHz * 1001ull * kFieldDen, "60000/1001 fields per second");
// inf: vertical blanking lasts 22 H-lines (VBLANK_END = VBLANK_START + 22 lines); unused by the game.
inline constexpr u64 kVblankLines = 22;

// H-lines elapsed at cycle c (valid while c * 1125 < 2^64, i.e. ~630 virtual days).
constexpr u64 hlines_at(u64 c) noexcept { return c * kHlineDen / kHlineNum; }
// First cycle at which hlines_at() >= h.
constexpr u64 hline_start(u64 h) noexcept { return (h * kHlineNum + kHlineDen - 1) / kHlineDen; }
// Cycle of VBLANK_START number k (k >= 1): the end of field k.
constexpr u64 vblank_start_cycle(u64 k) noexcept { return (k * kFieldNum + kFieldDen - 1) / kFieldDen; }

// ---- Events ----------------------------------------------------------------------------------------
enum Event : int {
    kEvVblankStart = 0,
    kEvVblankEnd,
    kEvTimer0,  // .. kEvTimer0 + 3
    kEvDma0 = kEvTimer0 + 4,  // .. kEvDma0 + 9: channel completion
    kEvDmaRetry = kEvDma0 + 10,
    kEvService,  // earliest deadline returned by the device services (Kernel::add_device_service)
    kEvCount
};

// ---- Fixed kernel addresses (obs, `15`) ------------------------------------------------------------
inline constexpr u32 kSyscallTableVa = 0x80015500u;  // ksyscall_table (`15` §1)
inline constexpr u32 kKernelStackVa = 0x80019440u;   // kernel stack used by positive syscalls (`15` §7)
inline constexpr u32 kIntrStackVa = 0x00081FC0u;     // user-mode handler stack (EENULL trampoline, `15` §0)
inline constexpr u32 kIntrReturnVa = 0x00081FECu;    // $ra after `jalr $v1` in the trampoline (inf: shape of the 0x82000 stub)
inline constexpr u32 kGsCsrPa = 0x12001000u;
inline constexpr u32 kGsImrPa = 0x12001010u;

// COP0 Status bits.
inline constexpr u32 kStIe = 1u << 0, kStExl = 1u << 1, kStErl = 1u << 2, kStEie = 1u << 16;

enum class TStatus : u32 { Free = 0, Run = 1, Ready = 2, Wait = 4, Suspend = 8, WaitSuspend = 0xC, Dormant = 0x10 };
enum WaitType : u32 { kWaitNone = 0, kWaitSleep = 1, kWaitSema = 2 };

inline constexpr int kIdleTid = 0;
inline constexpr int kMainTid = 1;
inline constexpr int kMaxThreads = 256;
inline constexpr int kMaxSemas = 256;
inline constexpr int kPrioLevels = 129;  // 0..127 user, 128 idle (`15` §3)

struct Tcb {
    TStatus status = TStatus::Free;
    u32 entry = 0, stack = 0, stack_size = 0, gp = 0, root = 0, attr = 0, option = 0, heap_end = 0;
    int init_prio = 0, cur_prio = 0;
    u32 wait_type = kWaitNone, wait_id = 0;
    u32 wakeup_count = 0;
    u32 arg = 0;
    int q_prev = -1, q_next = -1;
    bool queued = false;
    GuestFn host_entry = nullptr;  // the main thread runs a host function, not a guest VA
    u32 frame = 0;                 // saved-context pointer (BIOS TCB +0x10): the context frame in guest memory
    bool start_from_frame = false; // StartThread: the first activation loads the registers from `frame`
    Fiber* fiber = nullptr;  // created on first activation (L2)
    EEContext saved{};  // context while not loaded into the CPU
};

struct Sema {
    bool used = false;
    s32 count = -1, max = 0, init = 0;
    u32 attr = 0, option = 0;
    std::deque<int> waiters;  // FIFO, attr ignored (H-16)
    void state(StateIo& io) { io(used, count, max, init, attr, option, waiters); }
};

// Handler node pool (`15` §2.2): ids 1..128 shared by INTC and DMAC, one sentinel per list.
inline constexpr int kNodeIds = 128;
inline constexpr int kIntcLists = 15;  // causes 0..14
inline constexpr int kDmacLists = 16;  // channels 0..15
inline constexpr int kIntcSentinel0 = kNodeIds + 1;
inline constexpr int kDmacSentinel0 = kIntcSentinel0 + kIntcLists;
inline constexpr int kNodeCount = kDmacSentinel0 + kDmacLists;
struct HNode {
    int L = 0, R = 0;
    u32 handler = 0, gp = 0, arg = 0, mode = 0;  // mode 2 enabled user handler, 1 disabled
    bool used = false;
    int list = -1;  // 0..14 INTC cause, 15..30 DMAC channel
};

struct Timer {
    u32 mode = 0, comp = 0, hold = 0;
    u32 count_base = 0;  // count at tick_base
    u64 tick_base = 0;   // tick (in this timer's clock) where count_base applied
};

struct DmaChan {
    u128 tagqw{};  // TTE: the tag qword handed to the data path (DMAtag half zeroed)
    u32 chcr = 0, madr = 0, qwc = 0, tadr = 0, asr0 = 0, asr1 = 0, sadr = 0;
    // engine
    bool active = false;   // STR seen 0->1 and not completed
    bool held = false;     // STR set while DMAE == 0 or D_ENABLEW.CPND: started on release
    bool stalled = false;  // the data path consumed less than offered; retried at a later check point
    bool device_driven = false;  // SIF0 destination chain: completed by the SIF module's dma_complete(5)
    bool in_pump = false;
    enum class Phase : u8 { Data, NeedTag, TagQw, Done } phase = Phase::Data;
    bool end_after = false;
    u64 tag = 0;
    u64 qw_total = 0;
};

struct UnhandledRing {
    std::array<UnhandledAccess, 256> e{};
    u64 total = 0;
};

} // namespace kc

class KernelHooks;
namespace kc {
// The kernel's own register devices (defined in intc_timers.cpp / dmac.cpp).
std::unique_ptr<HwDevice> make_intc_device(KernelHooks& k);
std::unique_ptr<HwDevice> make_timer_device(KernelHooks& k);
std::unique_ptr<HwDevice> make_dmac_device(KernelHooks& k);
std::unique_ptr<HwDevice> make_denable_device(KernelHooks& k);
} // namespace kc

class KernelHooks final : public RtHooks, public HwBus {
public:
    KernelHooks(EEMemory& mem, EEContext& ctx, KernelOptions options);
    ~KernelHooks() override;
    // In the pinned arena when the host enabled it (p3fes/pinned.h): guest-thread frames hold `this`.
    static void* operator new(std::size_t n);
    static void operator delete(void* p) noexcept;

    // Machine state (runtime/STATE.md; kernel_state.cpp): every field below plus each live fiber's stack.
    // Saving: only between run_until calls (on the host side) after a Stopped result. Loading: into a kernel
    // that was constructed and wired like the saver's and never started; the next run_until resumes the
    // fiber that stopped. false + io.fail() when the kernel cannot be saved/loaded (see the reasons).
    bool state(StateIo& io);

    // ---- RtHooks -------------------------------------------------------------------------------
    void syscall(EEContext& ctx, u32 pc) override;
    void check_events(EEContext& ctx) override {
        if (ctx.cycles < next_deadline_) return;  // the hot path: one compare
        slow_check(ctx);
    }
    const u64* deadline_ptr() const override { return &next_deadline_; }  // the adapter inlines the compare
    HwBus& bus() override { return *this; }
    void trap(EEContext& ctx, u32 pc, u32 kind, u32 code) override;
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override;
    void vu_control_write(EEContext& ctx, u32 reg, u32 value) override;

    // ---- HwBus ---------------------------------------------------------------------------------
    void map(u32 pa_begin, u32 pa_end, HwDevice* dev) override;
    void set_dma_handler(unsigned ch, DmaChannelHandler* h) override;
    void raise_intc(unsigned cause) override;
    void dma_complete(unsigned ch) override;
    const Timebase& time() const override;
    u32 read32(u32 pa) override;
    void write32(u32 pa, u32 v) override;
    u64 read64(u32 pa) override;
    void write64(u32 pa, u64 v) override;
    u128 read128(u32 pa) override;
    void write128(u32 pa, const u128& v) override;
    u8 read8(u32 pa) override;
    u16 read16(u32 pa) override;
    void write8(u32 pa, u8 v) override;
    void write16(u32 pa, u16 v) override;

    // Non-aborting form of map(): false on misalignment (16-byte granularity), a range outside the two
    // windows, or an overlap with an existing mapping.
    bool try_map(u32 pa_begin, u32 pa_end, HwDevice* dev);
    void report_unhandled(u32 pa, u32 width, bool write, u64 value);

    // ---- harness (Kernel forwards here) --------------------------------------------------------
    void start(GuestFn main_fn);
    RunResult run_until(std::function<bool()> stop);
    bool snapshot_eemem(const std::string& path) const;
    bool install_syscall(int number, SyscallFn fn);
    void add_device_service(DeviceServiceFn fn) { services_.push_back(std::move(fn)); }
    void request_stop() {
        stop_requested_ = true;
        force_check();
    }
    void retry_dma_now(int ch);  // dmac.cpp: pump a stalled channel now (Kernel::retry_dma_now)
    void set_vu_control_handler(std::function<void(u32, u32)> fn) { vu_control_ = std::move(fn); }

    // inspection
    int current_thread() const { return current_; }
    ThreadView thread_view(int tid) const;
    u32 intc_stat() const { return intc_stat_; }
    u32 intc_mask() const { return intc_mask_; }
    u32 d_stat() const { return d_stat_; }
    u64 events_processed() const { return events_processed_; }
    u64 unhandled_total() const { return unhandled_.total; }
    std::vector<UnhandledAccess> unhandled_log() const;
    bool syscall_installed(int slot) const { return slot >= 0 && slot < 256 && guest_installed_[static_cast<unsigned>(slot)]; }
    u32 syscall_address(int slot) const { return (slot >= 0 && slot < 256) ? guest_table_[static_cast<unsigned>(slot)] : 0u; }
    u32 cause12_dispatcher() const { return cause12_dispatcher_; }
    GsCrtSetting gs_crt() const { return gs_crt_; }
    u64 gs_imr() const { return gs_imr_; }
    int handler_count(bool dmac, int idx) const;
    const u64* next_deadline_ptr() const { return &next_deadline_; }

    // Used by the device classes (intc_timers.cpp, dmac.cpp).
    u64 now() const { return ctx_.cycles; }
    void schedule(int ev, u64 at) {
        deadline_[static_cast<unsigned>(ev)] = at;
        if (at < next_deadline_) next_deadline_ = at;
    }
    void force_check() { next_deadline_ = 0; }
    [[noreturn]] void die(const char* fmt, ...);
    void log(const char* fmt, ...);

    // INTC / timers (intc_timers.cpp)
    u32 intc_read(u32 pa);
    void intc_write(u32 pa, u32 v);
    void set_intc_mask(u32 new_mask);
    u32 timer_read(u32 pa);
    void timer_write(u32 pa, u32 v);
    void timer_event(int n);

    // DMAC (dmac.cpp)
    u32 dmac_read(u32 pa);
    void dmac_write(u32 pa, u32 v);
    u32 denable_read(u32 pa);
    void denable_write(u32 pa, u32 v);
    void dma_complete_event(int ch);
    void dma_retry_event();

private:
    // bus_timebase.cpp
    HwDevice* device_at(u32 pa) const;
    void vblank_start_event();
    void vblank_end_event();
    void process_due_events(u64 now);
    void recompute_deadline(const EEContext& ctx);
    void slow_check(EEContext& ctx);
    void run_services();
    bool stop_due() const { return stop_requested_ || (stop_ && stop_()); }
    void take_stop(const char* where);

    // intc_timers.cpp
    u64 timer_ticks(const kc::Timer& t, u64 cycle) const;
    u64 timer_tick_cycle(const kc::Timer& t, u64 tick) const;
    void timer_advance(int n, u64 cycle);
    void timer_reschedule(int n);
    u32 timer_count(int n, u64 cycle) const;

    // dmac.cpp
    void dma_start(int ch);
    void dma_pump(int ch);
    void dma_finish(int ch);
    void dma_spr_chain(int ch);
    std::size_t dma_sink(int ch, u128* data, std::size_t qwc, u64 tag);
    u8* dma_resolve(u32 addr, std::size_t& max_qw);
    void dma_release_held();
    void dma_schedule_retry();
    bool dma_channel_routed(int ch) const;

    // interrupts.cpp
    bool cpu_can_deliver(const EEContext& ctx) const;
    u32 dmac_pending() const { return (d_stat_ & 0xFFFFu) & ((d_stat_ >> 16) | 0x8000u); }
    u32 intc_pending() const { return intc_stat_ & intc_mask_ & 0x7FFFu; }
    bool deliver_one();
    void run_chain(int list, u32 code);
    s64 add_handler(int list, u32 handler, s32 next, u32 arg, u32 gp);
    s64 remove_handler(int list, s32 id);
    void service_vsync_flag();

    // scheduler.cpp
    kc::Fiber* create_fiber();
    void delete_fiber(kc::Fiber* f);
    void delete_fiber_or_zombie(kc::Fiber* f);
    void reap_zombies();
    void switch_fiber(kc::Fiber* to);
    static void fiber_entry(void* self);
    [[noreturn]] void thread_fiber_main();
    // Returns only for RunStatus::Stopped (when the host resumes this fiber).
    void switch_to_host(RunStatus st, std::string msg);
    void save_loaded();
    void load(int tid);
    void q_push_tail(int tid);
    void q_remove(int tid);
    int q_top() const;
    void ready_insert(int tid);
    int pick() const;
    void activate(int next);
    void reschedule();
    void idle_step();
    void block(u32 wait_type, u32 wait_id, s64 normal_result);
    [[noreturn]] void exit_current(bool del);
    void reset_dormant(int tid);
    void build_initial_ctx(int tid);
    // Context frames in guest memory (KernelOptions::context_frames; scheduler.cpp).
    u32 frame_save(int tid, const EEContext& c, const u128& v0);  // full context at c.sp - 0x280
    void frame_init(int tid);                                     // gp/sp/fp/ra at stack+size-0x2A0
    void frame_load(int tid, EEContext& c) const;                 // the BIOS restore (0x80003800)
    bool valid_tid(s32 tid) const { return tid >= 0 && tid < kc::kMaxThreads && tcbs_[static_cast<unsigned>(tid)].status != kc::TStatus::Free; }
    bool sema_valid(s32 id) const { return id >= 0 && id < kc::kMaxSemas && semas_[static_cast<unsigned>(id)].used; }
    void sema_drop_waiter(int tid);

    // syscalls.cpp
    s64 stock_syscall(u32 slot, bool neg, bool& blocked);
    s64 installed_syscall(u32 slot, bool& handled);
    void call_kernel_mode(u32 addr);
    s64 sc_create_thread(u32 p);
    s64 sc_start_thread(s32 tid, u32 arg);
    s64 sc_terminate_thread(s32 tid);
    s64 sc_delete_thread(s32 tid);
    s64 sc_change_priority(s32 tid, s32 prio);
    s64 sc_rotate(s32 prio, bool neg);
    s64 sc_release_wait(s32 tid);
    s64 sc_refer_thread(s32 tid, u32 info);
    s64 sc_sleep(bool& blocked);
    s64 sc_wakeup(s32 tid);
    s64 sc_cancel_wakeup(s32 tid);
    s64 sc_suspend(s32 tid);
    s64 sc_resume(s32 tid);
    s64 sc_setup_thread();
    s64 sc_setup_heap(u32 start, s32 size);
    s64 sc_create_sema(u32 p);
    s64 sc_delete_sema(s32 id);
    s64 sc_signal_sema(s32 id);
    s64 sc_wait_sema(s32 id, bool& blocked);
    s64 sc_poll_sema(s32 id);
    s64 sc_refer_sema(s32 id, u32 info);
    s64 sc_set_syscall(s32 n, u32 addr);
    s64 sc_enable_intc(s32 cause, bool enable);
    s64 sc_enable_dmac(s32 ch, bool enable);
    s64 sc_handler_mode(bool dmac, s32 id, u32 mode);
    void write_args_block(u32 args);
    u32 gpr32(unsigned r) const { return ctx_.gpr[r].u32[0]; }
    static void set_gpr(EEContext& c, unsigned r, s64 v) { c.gpr[r].u64[0] = static_cast<u64>(v); }
    GuestFn lookup(u32 va) const;
    bool in_code_band(u32 va) const { return va >= opts_.code_begin && va < opts_.code_end; }

    // ---- state -----------------------------------------------------------------------------------
    EEMemory& mem_;
    EEContext& ctx_;
    KernelOptions opts_;

    // time base + events
    mutable Timebase tb_{};
    u64 next_deadline_ = 0;
    std::array<u64, kc::kEvCount> deadline_{};
    u64 vblank_index_ = 0;  // number of VBLANK_STARTs processed
    u64 events_processed_ = 0;

    // bus
    std::array<HwDevice*, 0x10000 / 16> ee_slots_{};
    std::array<HwDevice*, 0x2000 / 16> gs_slots_{};
    kc::UnhandledRing unhandled_{};
    std::array<DmaChannelHandler*, 10> dma_handlers_{};
    std::unique_ptr<HwDevice> intc_dev_, timer_dev_, dmac_dev_, denable_dev_;

    // INTC + timers
    u32 intc_stat_ = 0, intc_mask_ = 0;
    std::array<kc::Timer, 4> timers_{};

    // DMAC
    std::array<kc::DmaChan, 10> dch_{};
    u32 d_ctrl_ = 0, d_stat_ = 0, d_pcr_ = 0, d_sqwc_ = 0, d_rbsr_ = 0, d_rbor_ = 0, d_stadr_ = 0;
    u32 d_enable_ = 0x1201u;  // inf: D_ENABLER reset value

    // handler chains
    std::array<kc::HNode, kc::kNodeCount> nodes_{};
    std::array<int, kc::kIntcLists + kc::kDmacLists> counts_{};
    std::deque<int> node_free_;
    bool need_resched_ = false;
    int no_deliver_depth_ = 0;  // > 0 inside handler chains and kernel-mode calls (IE = 0)
    u32 vsync_flag_ptr_ = 0, vsync_csr_ptr_ = 0;

    // threads (arrays inside this object, not heap vectors: with the object pinned, a Tcb& held by a suspended
    // frame stays valid in a restored process)
    std::array<kc::Tcb, kc::kMaxThreads> tcbs_{};
    std::array<int, kc::kPrioLevels> q_head_{}, q_tail_{};
    std::deque<int> tcb_free_;
    int current_ = kc::kIdleTid;  // RUN thread (0 = idle)
    int loaded_tid_ = -1;         // thread whose live state is in ctx_ (-1: ctx_ is scratch)
    u64 idle_since_ = kc::kNever;
    std::array<kc::Sema, kc::kMaxSemas> semas_{};
    std::deque<int> sema_free_;

    // fibers / harness (fiber.h). host_fiber_ is the host thread's own stack (its ctx is filled when a guest
    // fiber is entered); cur_fiber_ is the executing one. With the pinned regions, guest fibers are slots_[i]
    // on the fixed stack slots; otherwise heap Fibers on VirtualAlloc'd stacks.
    kc::Fiber host_fiber_{};
    kc::Fiber* cur_fiber_ = &host_fiber_;
    std::array<kc::Fiber, pinned::kFiberSlots> slots_{};
    std::array<bool, pinned::kFiberSlots> slot_used_{};
    kc::Fiber* resume_fiber_ = nullptr;  // guest fiber to resume from the host
    std::vector<kc::Fiber*> zombies_;
    int fiber_slot_index(const kc::Fiber* f) const;  // -1: none / not a slot
    kc::Fiber* fiber_at_slot(int i);
    bool started_ = false;
    bool dead_ = false;
    RunResult last_{};
    std::function<bool()> stop_;
    bool stop_requested_ = false;  // request_stop(): taken at the next thread-level check point

    // device services (Kernel::add_device_service) and the VU1-side COP2 control handler
    std::vector<DeviceServiceFn> services_;
    bool in_services_ = false;
    std::function<void(u32, u32)> vu_control_;

    // syscalls
    std::array<u32, 256> guest_table_{};
    std::array<bool, 256> guest_installed_{};
    std::vector<std::pair<s32, u32>> kernel_patches_;  // SetSyscall with n outside 0..255
    u32 cause12_dispatcher_ = 0;
    std::array<SyscallFn, 256> host_syscalls_{};
    GsCrtSetting gs_crt_{};
    u64 gs_imr_ = 0;
    u32 osd_param_ = 0;
    u32 machine_type_ = 0;
    u64 positive_in_handler_ = 0;
};

} // namespace p3fes::hle
