// Kernel construction/destruction, diagnostics (trap / fatal / log) and the public facade.
#include "kernel_core.h"

#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>

namespace p3fes::hle {

using namespace kc;

KernelHooks::KernelHooks(EEMemory& mem, EEContext& ctx, KernelOptions options)
    : mem_(mem), ctx_(ctx), opts_(std::move(options)) {
    if (!ctx_.memory) ctx_.memory = &mem_;
    deadline_.fill(kNever);
    deadline_[kEvVblankStart] = vblank_start_cycle(1);
    next_deadline_ = 0;
    // Handler lists: every sentinel links to itself; node ids 1..128 on the FIFO free list.
    for (int i = 0; i < kNodeCount; ++i) nodes_[static_cast<unsigned>(i)].L = nodes_[static_cast<unsigned>(i)].R = i;
    for (int id = 1; id <= kNodeIds; ++id) node_free_.push_back(id);
    q_head_.fill(-1);
    q_tail_.fill(-1);
    // Thread ids: 0 idle, 1 main (ExecPS2 keeps the caller's tid), 2.. FIFO (inf: fast boot gives 2 first).
    for (int t = 2; t < kMaxThreads; ++t) tcb_free_.push_back(t);
    for (int s = 0; s < kMaxSemas; ++s) sema_free_.push_back(s);  // ids restart at 0 after ExecPS2 (H-15)
    osd_param_ = opts_.osd_config_param;
    machine_type_ = opts_.machine_type;
    intc_dev_ = make_intc_device(*this);
    timer_dev_ = make_timer_device(*this);
    dmac_dev_ = make_dmac_device(*this);
    denable_dev_ = make_denable_device(*this);
    const bool ok = try_map(0x10000000u, 0x10002000u, timer_dev_.get()) &&
                    try_map(0x10008000u, 0x1000F000u, dmac_dev_.get()) &&
                    try_map(0x1000F000u, 0x1000F020u, intc_dev_.get()) &&
                    try_map(0x1000F520u, 0x1000F530u, denable_dev_.get()) &&
                    try_map(0x1000F590u, 0x1000F5A0u, denable_dev_.get());
    if (!ok) {
        std::fputs("p3fes kernel: internal register map failed\n", stderr);
        std::abort();
    }
}

KernelHooks::~KernelHooks() {
    // L4: only from the host side; every fiber is deleted.
    if (cur_fiber_ != &host_fiber_) {
        std::fputs("p3fes kernel: ~Kernel called from guest code\n", stderr);
        std::abort();
    }
    // Every fiber is referenced by a TCB, the zombie list and/or resume_fiber_; delete each exactly once.
    std::vector<Fiber*> all(zombies_.begin(), zombies_.end());
    for (Tcb& t : tcbs_) {
        if (t.fiber) all.push_back(t.fiber);
        t.fiber = nullptr;
    }
    if (resume_fiber_) all.push_back(resume_fiber_);
    std::sort(all.begin(), all.end());
    all.erase(std::unique(all.begin(), all.end()), all.end());
    for (Fiber* f : all) delete_fiber(f);
    zombies_.clear();
    resume_fiber_ = nullptr;
}

void* KernelHooks::operator new(std::size_t n) {
    if (void* p = pinned::alloc(n, 64)) return p;
    return ::operator new(n);
}

void KernelHooks::operator delete(void* p) noexcept {
    if (!pinned::owns(p)) ::operator delete(p);
}

ThreadView KernelHooks::thread_view(int tid) const {
    ThreadView v;
    if (tid < 0 || tid >= kMaxThreads) return v;
    const Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    v.status = static_cast<u32>(t.status);
    v.init_priority = t.init_prio;
    v.priority = t.cur_prio;
    v.wakeup_count = t.wakeup_count;
    v.wait_type = t.wait_type;
    v.wait_id = t.wait_id;
    v.heap_end = t.heap_end;
    v.has_fiber = t.fiber != nullptr;
    v.entry = t.entry;
    v.stack = t.stack;
    v.stack_size = t.stack_size;
    v.frame = t.frame;
    return v;
}

bool KernelHooks::snapshot_eemem(const std::string& path) const {
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) return false;
    const std::size_t n = std::fwrite(mem_.main_ram(), 1, EEMemory::kMainRamSize, f);
    const bool ok = std::fclose(f) == 0 && n == EEMemory::kMainRamSize;
    return ok;
}

// ---- diagnostics ---------------------------------------------------------------------------------

void KernelHooks::log(const char* fmt, ...) {
    char buf[1536];
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    if (opts_.log_sink) opts_.log_sink(buf);
    else std::fprintf(stderr, "p3fes kernel: %s\n", buf);
}

[[noreturn]] void KernelHooks::die(const char* fmt, ...) {
    char what[1024];
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(what, sizeof what, fmt, ap);
    va_end(ap);
    FatalInfo info;
    info.pc = ctx_.pc;
    info.v1 = ctx_.gpr[GPR_V1].u32[0];
    info.thread = current_;
    char full[1280];
    std::snprintf(full, sizeof full, "%s (pc 0x%08X, $v1 0x%08X, thread %d)", what, info.pc, info.v1, info.thread);
    info.message = full;
    if (!opts_.fatal_sink) {
        std::fprintf(stderr, "p3fes kernel fatal: %s\n", full);
        std::fflush(stderr);
        std::abort();
    }
    opts_.fatal_sink(info);
    // End the run: back to the host fiber, this guest fiber is abandoned (never resumed).
    if (cur_fiber_ != &host_fiber_) {
        switch_to_host(RunStatus::Fatal, info.message);
    }
    std::fprintf(stderr, "p3fes kernel fatal (host side): %s\n", full);
    std::fflush(stderr);
    std::abort();
}

void KernelHooks::trap(EEContext& ctx, u32 pc, u32 kind, u32 code) {
    (void)ctx;
    ctx_.pc = pc;
    // The game installs no break handler (no SetVCommonHandler/SetVInterruptHandler caller), so a `break`
    // is a guest bug or an unmodelled path: report and stop.
    if (kind == 0) die("break 0x%05X at 0x%08X (no guest break handler)", code, pc);
    die("undecodable instruction word 0x%08X at 0x%08X", code, pc);
}

[[noreturn]] void KernelHooks::fatal(EEContext& ctx, u32 pc, const char* what) {
    (void)ctx;
    ctx_.pc = pc;
    die("%s", what ? what : "fatal");
}

void KernelHooks::vu_control_write(EEContext& ctx, u32 reg, u32 value) {
    (void)ctx;
    if (vu_control_) vu_control_(reg, value);
}

// ---- facade ------------------------------------------------------------------------------------------

Kernel::Kernel(EEMemory& mem, EEContext& ctx, KernelOptions options)
    : core_(std::make_unique<KernelHooks>(mem, ctx, std::move(options))) {}
Kernel::~Kernel() = default;

HwBus& Kernel::bus() { return *core_; }
RtHooks& Kernel::hooks() { return *core_; }
bool Kernel::try_map(u32 b, u32 e, HwDevice* dev) { return core_->try_map(b, e, dev); }
void Kernel::start(GuestFn main_fn) { core_->start(main_fn); }
RunResult Kernel::run(GuestFn main_fn) {
    core_->start(main_fn);
    return core_->run_until(nullptr);
}
RunResult Kernel::run_until(std::function<bool()> stop) { return core_->run_until(std::move(stop)); }
RunResult Kernel::step_to_next_event() {
    const u64 n0 = core_->events_processed();
    KernelHooks* const k = core_.get();
    return core_->run_until([k, n0] { return k->events_processed() > n0; });
}
bool Kernel::snapshot_eemem(const std::string& path) const { return core_->snapshot_eemem(path); }
bool Kernel::state(StateIo& io) { return core_->state(io); }
bool Kernel::install_syscall(int number, SyscallFn fn) { return core_->install_syscall(number, std::move(fn)); }
void Kernel::add_device_service(DeviceServiceFn fn) { core_->add_device_service(std::move(fn)); }
void Kernel::request_stop() { core_->request_stop(); }
void Kernel::retry_dma_now(int ch) { core_->retry_dma_now(ch); }
void Kernel::set_vu_control_handler(std::function<void(u32, u32)> fn) { core_->set_vu_control_handler(std::move(fn)); }
const Timebase& Kernel::time() const { return core_->time(); }
int Kernel::current_thread() const { return core_->current_thread(); }
ThreadView Kernel::thread(int tid) const { return core_->thread_view(tid); }
u32 Kernel::intc_stat() const { return core_->intc_stat(); }
u32 Kernel::intc_mask() const { return core_->intc_mask(); }
u32 Kernel::d_stat() const { return core_->d_stat(); }
u64 Kernel::events_processed() const { return core_->events_processed(); }
u64 Kernel::unhandled_accesses() const { return core_->unhandled_total(); }
std::vector<UnhandledAccess> Kernel::unhandled_log() const { return core_->unhandled_log(); }
bool Kernel::syscall_installed(int slot) const { return core_->syscall_installed(slot); }
u32 Kernel::syscall_address(int slot) const { return core_->syscall_address(slot); }
u32 Kernel::cause12_dispatcher() const { return core_->cause12_dispatcher(); }
GsCrtSetting Kernel::gs_crt() const { return core_->gs_crt(); }
u64 Kernel::gs_imr() const { return core_->gs_imr(); }
int Kernel::handler_count(bool dmac, int idx) const { return core_->handler_count(dmac, idx); }
const u64* Kernel::next_deadline() const { return core_->next_deadline_ptr(); }

} // namespace p3fes::hle
