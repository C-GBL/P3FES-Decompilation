// IOP kernel HLE (iop_kernel_hle.h).
#include "iop_kernel_hle.h"

#include "p3fes/prof.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

namespace p3fes::hle::sif::iop {

namespace {

constexpr s32 kKeError = -1;
constexpr s32 kKeNoMemory = -400;         // KE_NO_MEMORY
constexpr s32 kKeIllegalThid = -407;      // KE_UNKNOWN_THID
constexpr s32 kKeIllegalSemid = -409;     // KE_UNKNOWN_SEMID
constexpr s32 kKeSemaZero = -419;         // KE_SEMA_ZERO (PollSema)
constexpr s32 kKeLibraryFound = -213;     // KE_LIBRARY_FOUND (RegisterLibraryEntries twice)
constexpr s32 kKeCpuDi = -102;            // KE_CPUDI (CpuSuspendIntr while already disabled)

u64 usec_to_ee(u64 usec) { return usec * kEeCyclesPerUsec / 1'000'000ull; }
u64 ee_to_iop(u64 ee) { return ee / kIopClocksPerEeCycle; }

// ps2sdk sysclib ctype flags (iop/system/sysclib/src/nonstd/ctype.c @ 329e2bb: 0x01 upper, 0x02 lower,
// 0x04 digit, 0x08 space, 0x10 punct/print, 0x20 control, 0x40 hex letter).
u32 ctype_flags(u32 ch) {
    ch &= 0xFFu;
    if (ch >= 0x80) return 0;
    if (ch < 0x20) return (ch >= 9 && ch <= 13) ? 0x08u : 0x20u;
    if (ch == 0x7F) return 0x20u;
    if (ch == ' ') return 0x18u;
    if (ch >= '0' && ch <= '9') return 0x04u;
    if (ch >= 'A' && ch <= 'Z') return ch <= 'F' ? 0x41u : 0x01u;
    if (ch >= 'a' && ch <= 'z') return ch <= 'f' ? 0x42u : 0x02u;
    return 0x10u;
}

}  // namespace

IopKernel::IopKernel(detail::IopRam& ram, LibsdHle& libsd, std::function<void(std::string_view)> log)
    : ram_(ram), libsd_(libsd), log_(std::move(log)), cpu_(ram) {
    if (!log_) log_ = [](std::string_view) {};
    trap_id_ = cpu_.register_host_call("<unresolved import>", [this](R3000& c) {
        fail("unresolved import called from " + detail::hex32(c.state().r[31]));
        c.set_result(0);
        c.request_stop();
    });
    install_calls();
    install_libsd_calls(cpu_, libsd_, ram_, host_calls_);
    rpc_return_id_ = cpu_.register_host_call("<rpc return>", [this](R3000& c) { rpc_return(c); });
}

u32 IopKernel::alloc(u32 size) {  // the modules' work areas: the ranges in order
    if (ranges_.empty()) return ram_.alloc(size, 0, 0);
    for (const auto& [lo, hi] : ranges_)
        if (const u32 a = ram_.alloc_in(lo, hi, size)) return a;
    return 0;
}

u32 IopKernel::alloc_kernel(u32 size) {  // stacks, argv, the interrupt stack: the last range first
    if (ranges_.empty()) return ram_.alloc(size, 0, 0);
    for (auto it = ranges_.rbegin(); it != ranges_.rend(); ++it)
        if (const u32 a = ram_.alloc_in(it->first, it->second, size)) return a;
    return 0;
}

void IopKernel::ensure_setup() {
    if (!intr_stack_) intr_stack_ = alloc_kernel(0x1000);
    if (!rpc_return_addr_) {
        rpc_return_addr_ = alloc_kernel(16);
        if (rpc_return_addr_) {
            cpu_.write32(rpc_return_addr_, (kHleOpcode << 26) | rpc_return_id_);
            cpu_.write32(rpc_return_addr_ + 4, 0);
        }
    }
    if (!intr_stack_ || !rpc_return_addr_) fail("no IOP memory for the kernel's interrupt stack / RPC trampoline");
}

void IopKernel::fail(std::string what) {
    if (fault_.empty()) fault_ = what;
    log_("[iop-kernel] fault: " + what);
}

void IopKernel::def(const char* library, u16 ordinal, const char* name, R3000::HostCall fn) {
    host_calls_[{library, ordinal}] = cpu_.register_host_call(std::string(library) + "." + name, std::move(fn));
}

// ---- threads ---------------------------------------------------------------------------------------

KernelThread* IopKernel::current() {
    if (current_ == 0) return nullptr;
    const auto it = threads_.find(current_);
    return it == threads_.end() ? nullptr : &it->second;
}

int IopKernel::create_thread(u32 attr, u32 option, u32 entry, u32 stack_size, int priority, std::string_view owner) {
    const u32 size = std::max<u32>(stack_size, 0x200u);
    const u32 stack = alloc_kernel(size);
    if (!stack) return kKeNoMemory;
    KernelThread t;
    t.id = next_thread_id_++;
    t.owner = std::string(owner);
    t.attr = attr;
    t.option = option;
    t.entry = entry;
    t.stack = stack;
    t.stack_size = size;
    t.gp = gp_for(entry);
    t.init_priority = t.priority = priority;
    threads_[t.id] = t;
    return t.id;
}

bool IopKernel::start_thread(int id, u32 a0, u32 a1) {
    const auto it = threads_.find(id);
    if (it == threads_.end() || it->second.status != ThreadStatus::Dormant) return false;
    KernelThread& t = it->second;
    t.ctx = R3000State{};
    t.ctx.r[4] = a0;
    t.ctx.r[5] = a1;
    t.ctx.r[28] = t.gp;
    t.ctx.r[29] = (t.stack + t.stack_size - 16u) & ~7u;
    t.ctx.r[31] = kExitSentinel;
    t.ctx.pc = t.entry;
    t.ctx.npc = t.entry + 4;
    t.wakeups = 0;
    t.wait = WaitKind::None;
    make_ready(t);
    return true;
}

void IopKernel::make_ready(KernelThread& t) {
    t.status = ThreadStatus::Ready;
    t.wait = WaitKind::None;
    t.ready_seq = ++ready_counter_;
}

KernelThread* IopKernel::pick_ready() {
    KernelThread* best = nullptr;
    for (auto& [id, t] : threads_) {
        if (t.status != ThreadStatus::Ready) continue;
        if (!best || t.priority < best->priority || (t.priority == best->priority && t.ready_seq < best->ready_seq)) best = &t;
    }
    return best;
}

void IopKernel::block_current(WaitKind kind, int id) {
    KernelThread* t = current();
    if (!t) {
        fail("blocking call outside a thread");
        cpu_.request_stop();
        return;
    }
    t->status = ThreadStatus::Wait;
    t->wait = kind;
    t->wait_id = id;
    cpu_.request_stop();
}

// A readied thread of higher priority than the running one takes the CPU at once (strict-priority
// scheduler); the running thread goes back to Ready keeping its place in its level.
void IopKernel::preempt_if_needed() {
    KernelThread* cur = current();
    if (!cur || in_handler_) return;
    for (const auto& [id, t] : threads_)
        if (t.status == ThreadStatus::Ready && t.priority < cur->priority) {
            cur->status = ThreadStatus::Ready;
            cpu_.request_stop();
            return;
        }
}

void IopKernel::run_until_idle() {
    while (fault_.empty()) {
        KernelThread* t = pick_ready();
        if (!t) break;
        t->status = ThreadStatus::Run;
        current_ = t->id;
        cpu_.state() = t->ctx;
        const u64 before = cpu_.instructions();
        const R3000::Result r = cpu_.run(kSliceBudget);
        ++t->runs;
        t->instructions += cpu_.instructions() - before;
        if (prof::on()) prof::g_prof.work.iop_insns += cpu_.instructions() - before;
        t->ctx = cpu_.state();
        current_ = 0;
        switch (r.stop) {
        case R3000::Stop::Sentinel:  // the entry function returned
            t->status = ThreadStatus::Dormant;
            t->exit_value = t->ctx.r[2];
            break;
        case R3000::Stop::HostStop:  // blocked or preempted; the host call set the status
            if (t->status == ThreadStatus::Run) t->status = ThreadStatus::Ready;
            break;
        case R3000::Stop::Budget:
            fail("thread " + std::to_string(t->id) + " (" + t->owner + ") ran " + std::to_string(kSliceBudget) + " instructions without blocking, pc " +
                 detail::hex32(t->ctx.pc));
            t->status = ThreadStatus::Dormant;
            break;
        case R3000::Stop::Trap:
            fail("thread " + std::to_string(t->id) + " (" + t->owner + "): " + r.what + " at " + detail::hex32(r.pc) + " word " +
                 detail::hex32(r.word) + " (" + std::string(module_at(r.pc)) + ")");
            t->status = ThreadStatus::Dormant;
            break;
        }
    }
}

u32 IopKernel::run_handler(u32 fn, u32 a0, u32 gp) {
    ensure_setup();
    const R3000State saved = cpu_.state();
    const int saved_current = current_;
    const bool saved_in = in_handler_;
    current_ = 0;
    in_handler_ = true;
    R3000State s{};
    s.r[4] = a0;
    s.r[28] = gp;
    s.r[29] = (intr_stack_ + 0x1000u - 16u) & ~7u;
    s.r[31] = kExitSentinel;
    s.pc = fn;
    s.npc = fn + 4;
    cpu_.state() = s;
    const u64 before = cpu_.instructions();
    const R3000::Result r = cpu_.run(kSliceBudget);
    if (prof::on()) prof::g_prof.work.iop_insns += cpu_.instructions() - before;
    u32 ret = cpu_.state().r[2];
    if (r.stop != R3000::Stop::Sentinel) {
        fail("interrupt handler " + detail::hex32(fn) + " did not return: " + (r.what.empty() ? std::string("blocked or ran out of budget") : r.what));
        ret = 0;
    }
    cpu_.state() = saved;
    current_ = saved_current;
    in_handler_ = saved_in;
    return ret;
}

std::optional<u32> IopKernel::call(u32 fn, std::span<const u32> args, std::string& error) {
    const int id = create_thread(0x02000000u, 0, fn, 0x1000, 1, "host call");
    if (id <= 0) {
        error = "no memory for the call thread";
        return std::nullopt;
    }
    KernelThread& t = threads_[id];
    start_thread(id, args.size() > 0 ? args[0] : 0u, args.size() > 1 ? args[1] : 0u);
    if (args.size() > 2) t.ctx.r[6] = args[2];
    if (args.size() > 3) t.ctx.r[7] = args[3];
    for (std::size_t i = 4; i < args.size(); ++i) {
        u8* p = ram_.at(t.ctx.r[29] + 4u * static_cast<u32>(i), 4);
        if (p) std::memcpy(p, &args[i], 4);
    }
    run_until_idle();
    const KernelThread done = threads_[id];
    ram_.free(done.stack);
    threads_.erase(id);
    if (!fault_.empty()) {
        error = fault_;
        return std::nullopt;
    }
    if (done.status != ThreadStatus::Dormant) {
        error = "the called function blocked";
        return std::nullopt;
    }
    return done.exit_value;
}

// ---- time ------------------------------------------------------------------------------------------

u64 IopKernel::next_deadline() const {
    u64 d = detail::kNever;
    for (const auto& [id, t] : timers_)
        if (t.running) d = std::min(d, t.deadline);
    for (const auto& [id, t] : threads_)
        if (t.status == ThreadStatus::Wait && t.wait == WaitKind::Delay) d = std::min(d, t.wait_until);
    return d;
}

u64 IopKernel::advance_to(u64 ee_cycles) {
    u64 runs = 0;
    run_until_idle();
    while (fault_.empty()) {
        const u64 d = next_deadline();
        if (d > ee_cycles) break;
        now_ = std::max(now_, d);
        if (time_hook_) time_hook_(now_);
        // Delays first (they are thread-level), then timer handlers (interrupt context).
        for (auto& [id, t] : threads_)
            if (t.status == ThreadStatus::Wait && t.wait == WaitKind::Delay && t.wait_until <= now_) make_ready(t);
        for (auto& [id, t] : timers_) {
            if (!t.running || t.deadline > now_) continue;
            ++t.fired;
            ++handler_runs_;
            ++runs;
            const u32 ret = t.handler ? run_handler(t.handler, t.common, gp_for(t.handler)) : 0;
            if (ret != 0) {
                t.deadline += static_cast<u64>(ret) * kIopClocksPerEeCycle;  // re-armed from the previous deadline: no drift
            } else {
                t.running = false;
            }
        }
        run_until_idle();
    }
    now_ = std::max(now_, ee_cycles);
    if (time_hook_) time_hook_(now_);
    return runs;
}

// ---- RPC -------------------------------------------------------------------------------------------

const RpcServerRecord* IopKernel::rpc_server(u32 sid) const {
    for (const RpcServerRecord& r : rpc_servers_)
        if (r.sid == sid && r.func != 0) return &r;
    return nullptr;
}
bool IopKernel::has_rpc_server(u32 sid) const { return rpc_server(sid) != nullptr; }

std::optional<u32> IopKernel::rpc_dispatch(u32 sid, u32 fno, u32 buf, u32 size, std::string& error) {
    ensure_setup();
    if (!fault_.empty()) { error = fault_; return std::nullopt; }
    if (rpc_.active) { error = "an RPC handler is still pending"; return std::nullopt; }
    const RpcServerRecord* r = rpc_server(sid);
    if (!r) { error = "no RPC server registered for " + detail::hex32(sid); return std::nullopt; }
    const auto it = threads_.find(r->queue_thread);
    if (it == threads_.end()) { error = "the RPC queue thread does not exist"; return std::nullopt; }
    KernelThread& t = it->second;
    if (t.status != ThreadStatus::Wait || t.wait != WaitKind::Rpc) { error = "the RPC queue thread is not in sceSifRpcLoop"; return std::nullopt; }
    rpc_ = RpcFrame{};
    rpc_.active = true;
    rpc_.thread = t.id;
    rpc_.saved = t.ctx;
    rpc_.saved_wait_id = t.wait_id;
    // The handler frame: sifrpc calls func(fno, buffer, size) from the loop; its stack grows below the loop's.
    t.ctx.r[4] = fno;
    t.ctx.r[5] = buf;
    t.ctx.r[6] = size;
    t.ctx.r[29] = (rpc_.saved.r[29] - 32u) & ~7u;
    t.ctx.r[31] = rpc_return_addr_;
    t.ctx.pc = r->func;
    t.ctx.npc = r->func + 4;
    make_ready(t);
    ++rpc_calls_;
    run_until_idle();
    if (!fault_.empty()) { error = fault_; rpc_ = RpcFrame{}; return std::nullopt; }
    if (!rpc_.done) { ++rpc_pending_runs_; return std::nullopt; }
    const u32 result = rpc_.result;
    rpc_ = RpcFrame{};
    return result;
}

std::optional<u32> IopKernel::rpc_poll() {
    if (!rpc_.active || !rpc_.done) return std::nullopt;
    const u32 result = rpc_.result;
    rpc_ = RpcFrame{};
    return result;
}

void IopKernel::rpc_return(R3000& c) {
    KernelThread* t = current();
    if (!t || !rpc_.active || t->id != rpc_.thread) {
        fail("RPC return trampoline reached outside the RPC queue thread");
        c.request_stop();
        return;
    }
    rpc_.result = c.state().r[2];
    rpc_.done = true;
    // Back into sceSifRpcLoop's wait, as the loop would sleep again until the next request.
    t->ctx = rpc_.saved;
    c.state() = rpc_.saved;
    t->status = ThreadStatus::Wait;
    t->wait = WaitKind::Rpc;
    t->wait_id = rpc_.saved_wait_id;
    c.request_stop();
}

// ---- modules ---------------------------------------------------------------------------------------

u32 IopKernel::gp_for(u32 addr) const {
    for (const LoadedIrx& m : modules_)
        if (addr >= m.info.base && addr < m.info.base + m.info.image_size) return m.info.gp;
    return 0;
}

const char* IopKernel::module_at(u32 addr) const {
    for (const LoadedIrx& m : modules_)
        if ((addr & 0x1FFFFFFFu) >= m.info.base && (addr & 0x1FFFFFFFu) < m.info.base + m.info.image_size) return m.info.name.c_str();
    return "no module";
}

ImportTarget IopKernel::resolve(std::string_view library, u16 ordinal) {
    for (const GuestLibrary& lib : libraries_)
        if (lib.name == library) {
            if (ordinal < lib.functions.size() && lib.functions[ordinal] != 0) return {ImportTarget::Kind::Guest, lib.functions[ordinal]};
            return {};
        }
    const auto it = host_calls_.find({std::string(library), ordinal});
    if (it != host_calls_.end()) return {ImportTarget::Kind::Host, it->second};
    return {};
}

void IopKernel::rebind_library(const GuestLibrary& lib) {
    for (LoadedIrx& m : modules_) {
        if (m.unresolved.empty()) continue;
        bool any = false;
        for (const UnresolvedImport& u : m.unresolved)
            if (u.library == lib.name) any = true;
        if (!any) continue;
        m.unresolved = bind_imports(ram_, m.info, *this, trap_id_);
    }
}

std::optional<LoadedIrx> IopKernel::load_module(std::span<const u8> file, std::string_view path, std::string_view args, std::string& error) {
    ensure_setup();
    const std::optional<u32> size = irx_image_size(file, error);
    if (!size) return std::nullopt;
    // loadcore places the image 0x30 bytes into its allocation, after the ModuleInfo record (ps2sdk
    // loadcore.h; PCSX2's IOP RAM shows every SK module at block + 0x30). A pinned base wins when free.
    std::string file_name(path);
    if (const auto slash = file_name.find_last_of("\\/"); slash != std::string::npos) file_name = file_name.substr(slash + 1);
    if (const auto semi = file_name.find(';'); semi != std::string::npos) file_name = file_name.substr(0, semi);
    for (char& ch : file_name) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    u32 block = 0;
    if (const auto fb = fixed_bases_.find(file_name); fb != fixed_bases_.end() && fb->second >= 0x30u)
        block = ram_.alloc(*size + 0x30u, 2, fb->second - 0x30u);
    if (!block) block = alloc(*size + 0x30u);
    if (!block) {
        error = "no IOP memory for the module image";
        return std::nullopt;
    }
    const u32 base = block + 0x30u;
    std::optional<IrxModule> info = load_irx(ram_, file, base, error);
    if (!info) {
        ram_.free(block);
        return std::nullopt;
    }
    LoadedIrx m;
    m.id = next_module_id_++;
    m.path = std::string(path);
    m.info = std::move(*info);
    m.block = block;
    m.unresolved = bind_imports(ram_, m.info, *this, trap_id_);
    {
        // ModuleInfo {next, name, version, newflags, id, flags, entry, gp, text_start, text_size, data_size, bss_size}
        const u32 words[12] = {0, 0, static_cast<u32>(m.info.version), (static_cast<u32>(m.id) & 0xFFFFu) | (3u << 16),
                               m.info.entry, m.info.gp, m.info.base, m.info.text_size, m.info.data_size, m.info.bss_size, 0, 0};
        for (u32 i = 0; i < 12; ++i) cpu_.write32(block + 4u * i, words[i]);
    }

    // argv: path, then the NUL-separated args (loadcore passes argc/argv to _start).
    std::vector<std::string> argv{std::string(path)};
    for (std::size_t s = 0; s < args.size();) {
        const std::size_t e = args.find('\0', s);
        const std::string a(args.substr(s, e == std::string_view::npos ? std::string_view::npos : e - s));
        if (!a.empty()) argv.push_back(a);
        if (e == std::string_view::npos) break;
        s = e + 1;
    }
    u32 argv_size = 4u * static_cast<u32>(argv.size() + 1);
    for (const std::string& a : argv) argv_size += static_cast<u32>(a.size() + 1);
    m.argv = alloc_kernel(argv_size);
    if (!m.argv) {
        error = "no IOP memory for argv";
        return std::nullopt;
    }
    {
        u32 text = m.argv + 4u * static_cast<u32>(argv.size() + 1);
        for (std::size_t i = 0; i < argv.size(); ++i) {
            cpu_.write32(m.argv + 4u * static_cast<u32>(i), text);
            for (char ch : argv[i]) cpu_.write8(text++, static_cast<u8>(ch));
            cpu_.write8(text++, 0);
        }
        cpu_.write32(m.argv + 4u * static_cast<u32>(argv.size()), 0);
    }

    modules_.push_back(m);
    LoadedIrx& rec = modules_.back();
    const int tid = create_thread(0x02000000u, 0, rec.info.entry, kModuleStartStack, kModuleStartPriority, rec.info.name);
    if (tid <= 0) {
        error = "no IOP memory for the start thread";
        return std::nullopt;
    }
    rec.start_thread = tid;
    const u64 before = cpu_.instructions();
    start_thread(tid, static_cast<u32>(argv.size()), m.argv);
    run_until_idle();
    rec.start_instructions = cpu_.instructions() - before;
    const KernelThread& t = threads_[tid];
    if (t.status == ThreadStatus::Dormant) {
        rec.start_returned = true;
        rec.start_result = static_cast<s32>(t.exit_value);
        if (rec.start_result == 1) {  // MODULE_NO_RESIDENT_END: loadcore frees the image (the duplicate SKHSYNTH)
            rec.resident = false;
            ram_.free(rec.block);
        }
        // The module-start thread is transient (loadcore deletes it once the entry returned): its stack goes back.
        ram_.free(t.stack);
        threads_.erase(tid);
        rec.start_thread = 0;
    }
    if (!fault_.empty()) {
        error = fault_;
        return std::nullopt;
    }
    return rec;
}

// ---- printf -----------------------------------------------------------------------------------------

std::string IopKernel::format(u32 fmt, unsigned first_arg) {
    std::string out;
    unsigned ai = first_arg;
    const std::string f = cpu_.c_string(fmt, 1024);
    for (std::size_t i = 0; i < f.size(); ++i) {
        if (f[i] != '%') {
            out.push_back(f[i]);
            continue;
        }
        std::string spec = "%";
        ++i;
        while (i < f.size() && std::strchr("-+ #0123456789.", f[i])) spec.push_back(f[i++]);
        while (i < f.size() && (f[i] == 'l' || f[i] == 'h')) ++i;  // all ints are 32-bit here
        if (i >= f.size()) break;
        const char conv = f[i];
        char buf[64];
        switch (conv) {
        case 'd': case 'i':
            std::snprintf(buf, sizeof buf, (spec + "d").c_str(), static_cast<int>(cpu_.arg(ai++)));
            out += buf;
            break;
        case 'u': case 'x': case 'X': case 'o': case 'c':
            std::snprintf(buf, sizeof buf, (spec + conv).c_str(), cpu_.arg(ai++));
            out += buf;
            break;
        case 'p':
            std::snprintf(buf, sizeof buf, "%08X", cpu_.arg(ai++));
            out += buf;
            break;
        case 's':
            out += cpu_.c_string(cpu_.arg(ai++), 512);
            break;
        case '%':
            out.push_back('%');
            break;
        default:
            out += spec;
            out.push_back(conv);
            break;
        }
    }
    return out;
}

// ---- the kernel libraries -----------------------------------------------------------------------------

void IopKernel::install_calls() {
    // ---- thbase ----
    def("thbase", 4, "CreateThread", [this](R3000& c) {
        const u32 p = c.arg(0);
        const int id = create_thread(c.read32(p), c.read32(p + 4), c.read32(p + 8), c.read32(p + 12), static_cast<int>(c.read32(p + 16)),
                                     module_at(c.read32(p + 8)));
        c.set_result(static_cast<u32>(id));
    });
    def("thbase", 5, "DeleteThread", [this](R3000& c) {
        const auto it = threads_.find(static_cast<int>(c.arg(0)));
        if (it == threads_.end()) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        if (it->second.status != ThreadStatus::Dormant) { c.set_result(static_cast<u32>(kKeError)); return; }
        ram_.free(it->second.stack);
        threads_.erase(it);
        c.set_result(0);
    });
    def("thbase", 6, "StartThread", [this](R3000& c) {
        if (!start_thread(static_cast<int>(c.arg(0)), c.arg(1), 0)) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        c.set_result(0);
        preempt_if_needed();
    });
    def("thbase", 7, "StartThreadArgs", [this](R3000& c) {
        if (!start_thread(static_cast<int>(c.arg(0)), c.arg(1), c.arg(2))) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        c.set_result(0);
        preempt_if_needed();
    });
    auto exit_thread = [this](R3000& c) {
        KernelThread* t = current();
        if (!t) { fail("ExitThread outside a thread"); c.request_stop(); return; }
        t->status = ThreadStatus::Dormant;
        t->exit_value = 0;
        c.request_stop();
    };
    def("thbase", 8, "ExitThread", exit_thread);
    def("thbase", 9, "ExitDeleteThread", exit_thread);
    auto terminate = [this](R3000& c) {
        const auto it = threads_.find(static_cast<int>(c.arg(0)));
        if (it == threads_.end()) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        for (auto& [sid, s] : semas_) std::erase(s.waiters, it->first);
        it->second.status = ThreadStatus::Dormant;
        it->second.wait = WaitKind::None;
        c.set_result(0);
        if (it->first == current_) c.request_stop();
    };
    def("thbase", 10, "TerminateThread", terminate);
    def("thbase", 11, "iTerminateThread", terminate);
    auto change_priority = [this](R3000& c) {
        int id = static_cast<int>(c.arg(0));
        if (id == 0) id = current_;
        const auto it = threads_.find(id);
        if (it == threads_.end()) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        it->second.priority = static_cast<int>(c.arg(1));
        if (it->second.status == ThreadStatus::Ready) it->second.ready_seq = ++ready_counter_;
        c.set_result(0);
        preempt_if_needed();
    };
    def("thbase", 14, "ChangeThreadPriority", change_priority);
    def("thbase", 15, "iChangeThreadPriority", change_priority);
    def("thbase", 20, "GetThreadId", [this](R3000& c) { c.set_result(static_cast<u32>(current_)); });
    auto refer = [this](R3000& c) {
        int id = static_cast<int>(c.arg(0));
        if (id == 0) id = current_;
        const auto it = threads_.find(id);
        if (it == threads_.end()) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        const KernelThread& t = it->second;
        const u32 p = c.arg(1);
        u32 status = 0x10;
        switch (t.status) {
        case ThreadStatus::Run: status = 0x01; break;
        case ThreadStatus::Ready: status = 0x02; break;
        case ThreadStatus::Wait: status = 0x04; break;
        case ThreadStatus::Dormant: status = 0x10; break;
        }
        u32 wait_type = 0;
        switch (t.wait) {
        case WaitKind::Sleep: wait_type = 1; break;
        case WaitKind::Delay: wait_type = 2; break;
        case WaitKind::Sema: wait_type = 3; break;
        case WaitKind::Rpc: wait_type = 1; break;  // the RPC loop sleeps in the real kernel
        case WaitKind::None: break;
        }
        const u32 words[13] = {t.attr, t.option, status, t.entry, t.stack, t.stack_size, t.gp,
                               static_cast<u32>(t.init_priority), static_cast<u32>(t.priority), wait_type,
                               static_cast<u32>(t.wait_id), static_cast<u32>(t.wakeups), 0};
        for (u32 i = 0; i < 13; ++i) c.write32(p + 4u * i, words[i]);
        c.set_result(0);
    };
    def("thbase", 22, "ReferThreadStatus", refer);
    def("thbase", 23, "iReferThreadStatus", refer);
    def("thbase", 24, "SleepThread", [this](R3000& c) {
        KernelThread* t = current();
        c.set_result(0);
        if (!t) { fail("SleepThread outside a thread"); c.request_stop(); return; }
        if (t->wakeups > 0) { --t->wakeups; return; }
        block_current(WaitKind::Sleep, 0);
    });
    auto wakeup = [this](R3000& c) {
        const auto it = threads_.find(static_cast<int>(c.arg(0)));
        if (it == threads_.end()) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        KernelThread& t = it->second;
        if (t.status == ThreadStatus::Wait && t.wait == WaitKind::Sleep) {
            make_ready(t);
            preempt_if_needed();
        } else if (t.status != ThreadStatus::Dormant) {
            ++t.wakeups;
        }
        c.set_result(0);
    };
    def("thbase", 25, "WakeupThread", wakeup);
    def("thbase", 26, "iWakeupThread", wakeup);
    auto cancel_wakeup = [this](R3000& c) {
        int id = static_cast<int>(c.arg(0));
        if (id == 0) id = current_;
        const auto it = threads_.find(id);
        if (it == threads_.end()) { c.set_result(static_cast<u32>(kKeIllegalThid)); return; }
        c.set_result(static_cast<u32>(it->second.wakeups));
        it->second.wakeups = 0;
    };
    def("thbase", 27, "CancelWakeupThread", cancel_wakeup);
    def("thbase", 28, "iCancelWakeupThread", cancel_wakeup);
    def("thbase", 33, "DelayThread", [this](R3000& c) {
        KernelThread* t = current();
        c.set_result(0);
        if (!t) { fail("DelayThread outside a thread"); c.request_stop(); return; }
        t->wait_until = now_ + std::max<u64>(1, usec_to_ee(c.arg(0)));
        block_current(WaitKind::Delay, 0);
    });
    def("thbase", 34, "GetSystemTime", [this](R3000& c) {
        const u64 clk = iop_clock();
        c.write32(c.arg(0), static_cast<u32>(clk));
        c.write32(c.arg(0) + 4, static_cast<u32>(clk >> 32));
        c.set_result(0);
    });
    def("thbase", 39, "USec2SysClock", [](R3000& c) {
        const u64 clk = static_cast<u64>(c.arg(0)) * 36864ull / 1000ull;  // 36.864 MHz sysclock
        c.write32(c.arg(1), static_cast<u32>(clk));
        c.write32(c.arg(1) + 4, static_cast<u32>(clk >> 32));
        c.set_result(0);
    });
    def("thbase", 40, "SysClock2USec", [](R3000& c) {
        const u64 clk = static_cast<u64>(c.read32(c.arg(0))) | (static_cast<u64>(c.read32(c.arg(0) + 4)) << 32);
        const u64 usec = clk * 1000ull / 36864ull;
        c.write32(c.arg(1), static_cast<u32>(usec / 1'000'000ull));
        c.write32(c.arg(2), static_cast<u32>(usec % 1'000'000ull));
        c.set_result(0);
    });
    def("thbase", 41, "GetSystemStatusFlag", [](R3000& c) { c.set_result(0); });

    // ---- thsemap ----
    def("thsemap", 4, "CreateSema", [this](R3000& c) {
        const u32 p = c.arg(0);
        KernelSema s;
        s.id = next_sema_id_++;
        s.attr = c.read32(p);
        s.option = c.read32(p + 4);
        s.count = static_cast<int>(c.read32(p + 8));
        s.max = static_cast<int>(c.read32(p + 12));
        semas_[s.id] = s;
        c.set_result(static_cast<u32>(s.id));
    });
    def("thsemap", 5, "DeleteSema", [this](R3000& c) {
        const auto it = semas_.find(static_cast<int>(c.arg(0)));
        if (it == semas_.end()) { c.set_result(static_cast<u32>(kKeIllegalSemid)); return; }
        for (int w : it->second.waiters) {
            const auto t = threads_.find(w);
            if (t != threads_.end()) { make_ready(t->second); t->second.ctx.r[2] = static_cast<u32>(-425); }  // KE_WAIT_DELETE
        }
        semas_.erase(it);
        c.set_result(0);
        preempt_if_needed();
    });
    auto signal = [this](R3000& c) {
        const auto it = semas_.find(static_cast<int>(c.arg(0)));
        if (it == semas_.end()) { c.set_result(static_cast<u32>(kKeIllegalSemid)); return; }
        KernelSema& s = it->second;
        c.set_result(0);
        while (!s.waiters.empty()) {
            const int w = s.waiters.front();
            s.waiters.pop_front();
            const auto t = threads_.find(w);
            if (t != threads_.end() && t->second.status == ThreadStatus::Wait && t->second.wait == WaitKind::Sema) {
                make_ready(t->second);
                t->second.ctx.r[2] = 0;
                preempt_if_needed();
                return;
            }
        }
        ++s.count;  // `max` is not enforced (`15`: the EE kernel never does either; inf for the IOP)
    };
    def("thsemap", 6, "SignalSema", signal);
    def("thsemap", 7, "iSignalSema", signal);
    def("thsemap", 8, "WaitSema", [this](R3000& c) {
        const auto it = semas_.find(static_cast<int>(c.arg(0)));
        if (it == semas_.end()) { c.set_result(static_cast<u32>(kKeIllegalSemid)); return; }
        KernelSema& s = it->second;
        c.set_result(0);
        if (s.count > 0) { --s.count; return; }
        s.waiters.push_back(current_);
        block_current(WaitKind::Sema, s.id);
    });
    def("thsemap", 9, "PollSema", [this](R3000& c) {
        const auto it = semas_.find(static_cast<int>(c.arg(0)));
        if (it == semas_.end()) { c.set_result(static_cast<u32>(kKeIllegalSemid)); return; }
        if (it->second.count > 0) { --it->second.count; c.set_result(0); return; }
        c.set_result(static_cast<u32>(kKeSemaZero));
    });
    auto refer_sema = [this](R3000& c) {
        const auto it = semas_.find(static_cast<int>(c.arg(0)));
        if (it == semas_.end()) { c.set_result(static_cast<u32>(kKeIllegalSemid)); return; }
        const KernelSema& s = it->second;
        const u32 p = c.arg(1);
        c.write32(p, s.attr);
        c.write32(p + 4, s.option);
        c.write32(p + 8, static_cast<u32>(s.count));
        c.write32(p + 12, static_cast<u32>(s.max));
        c.write32(p + 16, static_cast<u32>(s.count));
        c.write32(p + 20, static_cast<u32>(s.waiters.size()));
        c.set_result(0);
    };
    def("thsemap", 11, "ReferSemaStatus", refer_sema);
    def("thsemap", 12, "iReferSemaStatus", refer_sema);

    // ---- timrman ----
    def("timrman", 4, "AllocHardTimer", [this](R3000& c) {
        HardTimer t;
        t.id = next_timer_id_++;
        t.source = c.arg(0);
        t.size = c.arg(1);
        t.prescale = c.arg(2);
        timers_[t.id] = t;
        c.set_result(static_cast<u32>(t.id));
    });
    def("timrman", 5, "ReferHardTimer", [this](R3000& c) {
        HardTimer t;
        t.id = next_timer_id_++;
        t.source = c.arg(0);
        t.size = c.arg(1);
        t.mode = c.arg(2);
        timers_[t.id] = t;
        c.set_result(static_cast<u32>(t.id));
    });
    def("timrman", 6, "FreeHardTimer", [this](R3000& c) {
        c.set_result(timers_.erase(static_cast<int>(c.arg(0))) ? 0u : static_cast<u32>(kKeError));
    });
    def("timrman", 7, "SetTimerMode", [this](R3000& c) {
        const auto it = timers_.find(static_cast<int>(c.arg(0)));
        if (it != timers_.end()) it->second.mode = c.arg(1);
        c.set_result(0);
    });
    def("timrman", 10, "GetTimerCounter", [this](R3000& c) {
        const auto it = timers_.find(static_cast<int>(c.arg(0)));
        if (it == timers_.end()) { c.set_result(0); return; }
        const u64 elapsed = ee_to_iop(now_ - std::min(now_, it->second.start));
        const u64 scaled = it->second.prescale > 1 ? elapsed / it->second.prescale : elapsed;
        c.set_result(it->second.size == 16 ? static_cast<u32>(scaled & 0xFFFFu) : static_cast<u32>(scaled));
    });
    def("timrman", 11, "SetTimerCompare", [this](R3000& c) {
        const auto it = timers_.find(static_cast<int>(c.arg(0)));
        if (it != timers_.end()) it->second.compare = c.arg(1);
        c.set_result(0);
    });
    def("timrman", 16, "GetHardTimerIntrCode", [](R3000& c) { c.set_result(14); });  // INUM_RTC3 (inf: which timer)
    def("timrman", 20, "SetTimerHandler", [this](R3000& c) {
        const auto it = timers_.find(static_cast<int>(c.arg(0)));
        if (it == timers_.end()) { c.set_result(static_cast<u32>(kKeError)); return; }
        it->second.compare = c.arg(1);
        it->second.handler = c.arg(2);
        it->second.common = c.arg(3);
        if (it->second.running) it->second.deadline = now_ + static_cast<u64>(it->second.compare) * kIopClocksPerEeCycle;
        c.set_result(0);
    });
    def("timrman", 22, "SetupHardTimer", [this](R3000& c) {
        const auto it = timers_.find(static_cast<int>(c.arg(0)));
        if (it == timers_.end()) { c.set_result(static_cast<u32>(kKeError)); return; }
        it->second.source = c.arg(1);
        it->second.mode = c.arg(2);
        it->second.prescale = c.arg(3);
        c.set_result(0);
    });
    def("timrman", 23, "StartHardTimer", [this](R3000& c) {
        const auto it = timers_.find(static_cast<int>(c.arg(0)));
        if (it == timers_.end()) { c.set_result(static_cast<u32>(kKeError)); return; }
        it->second.running = true;
        it->second.start = now_;
        it->second.deadline = now_ + static_cast<u64>(std::max<u32>(it->second.compare, 1)) * kIopClocksPerEeCycle;
        c.set_result(0);
    });
    def("timrman", 24, "StopHardTimer", [this](R3000& c) {
        const auto it = timers_.find(static_cast<int>(c.arg(0)));
        if (it == timers_.end()) { c.set_result(static_cast<u32>(kKeError)); return; }
        it->second.running = false;
        c.set_result(0);
    });

    // ---- intrman ----
    def("intrman", 4, "RegisterIntrHandler", [](R3000& c) { c.set_result(0); });
    def("intrman", 5, "ReleaseIntrHandler", [](R3000& c) { c.set_result(0); });
    def("intrman", 6, "EnableIntr", [](R3000& c) { c.set_result(0); });
    def("intrman", 7, "DisableIntr", [](R3000& c) {
        if (c.arg(1)) c.write32(c.arg(1), c.arg(0));
        c.set_result(0);
    });
    def("intrman", 8, "CpuDisableIntr", [this](R3000& c) {
        c.set_result(suspend_depth_ > 0 ? static_cast<u32>(kKeCpuDi) : 0u);
        ++suspend_depth_;
    });
    def("intrman", 9, "CpuEnableIntr", [this](R3000& c) {
        if (suspend_depth_ > 0) --suspend_depth_;
        c.set_result(0);
    });
    def("intrman", 17, "CpuSuspendIntr", [this](R3000& c) {
        // *state receives the old SR (interrupts on = 0x401, inf) -- CpuResumeIntr takes it back.
        if (c.arg(0)) c.write32(c.arg(0), suspend_depth_ > 0 ? 0x400u : 0x401u);
        c.set_result(suspend_depth_ > 0 ? static_cast<u32>(kKeCpuDi) : 0u);
        ++suspend_depth_;
    });
    def("intrman", 18, "CpuResumeIntr", [this](R3000& c) {
        if (suspend_depth_ > 0) --suspend_depth_;
        c.set_result(0);
    });
    def("intrman", 23, "QueryIntrContext", [this](R3000& c) { c.set_result(in_handler_ ? 1u : 0u); });

    // ---- sysmem ----
    def("sysmem", 4, "AllocSysMemory", [this](R3000& c) {
        // The modules' work areas: from the kernel's ranges when placement is configured (mode 2 "at
        // address" is honoured as asked), so the game's heap RPC allocations keep their addresses.
        const u32 mode = c.arg(0), size = c.arg(1), addr = c.arg(2);
        const u32 got = ranges_.empty() || mode == 2 ? ram_.alloc(size, mode, addr) : alloc(size);
        if (!got) log_("[iop-kernel] AllocSysMemory(" + std::to_string(mode) + ", " + std::to_string(size) + ", " + detail::hex32(addr) + ") failed in " +
                       std::string(module_at(c.state().r[31])));
        c.set_result(got);
    });
    def("sysmem", 5, "FreeSysMemory", [this](R3000& c) { c.set_result(ram_.free(c.arg(0)) ? 0u : static_cast<u32>(kKeError)); });
    def("sysmem", 6, "QueryMemSize", [](R3000& c) { c.set_result(detail::kIopRamSize); });
    def("sysmem", 7, "QueryMaxFreeMemSize", [this](R3000& c) { c.set_result(ram_.free_max()); });
    def("sysmem", 8, "QueryTotalFreeMemSize", [this](R3000& c) { c.set_result(ram_.free_total()); });
    def("sysmem", 9, "QueryBlockTopAddress", [this](R3000& c) { c.set_result(ram_.block_size(c.arg(0)) ? c.arg(0) : 0u); });
    def("sysmem", 10, "QueryBlockSize", [this](R3000& c) { c.set_result(ram_.block_size(c.arg(0))); });
    def("sysmem", 14, "Kprintf", [this](R3000& c) {
        const std::string s = format(c.arg(0), 1);
        printf_log_.push_back(s);
        log_("[iop-kprintf] " + s);
        c.set_result(static_cast<u32>(s.size()));
    });

    // ---- loadcore ----
    def("loadcore", 4, "FlushIcache", [](R3000& c) { c.set_result(0); });
    def("loadcore", 5, "FlushDcache", [](R3000& c) { c.set_result(0); });
    def("loadcore", 6, "RegisterLibraryEntries", [this](R3000& c) {
        const u32 table = c.arg(0);
        if (c.read32(table) != kExportMagic) { c.set_result(static_cast<u32>(kKeError)); return; }
        GuestLibrary lib;
        lib.table = table;
        lib.version = static_cast<u16>(c.read32(table + 8));
        for (u32 i = 0; i < 8; ++i) {
            const u8 ch = c.read8(table + 12 + i);
            if (!ch) break;
            lib.name.push_back(static_cast<char>(ch));
        }
        for (const GuestLibrary& have : libraries_)
            if (have.name == lib.name) { c.set_result(static_cast<u32>(kKeLibraryFound)); return; }
        for (u32 a = table + 20; c.read32(a) != 0; a += 4) lib.functions.push_back(c.read32(a));
        lib.order = libraries_.size();
        for (const LoadedIrx& m : modules_)
            if (table >= m.info.base && table < m.info.base + m.info.image_size) lib.module_id = m.id;
        libraries_.push_back(lib);
        rebind_library(lib);
        c.set_result(0);
    });
    def("loadcore", 7, "ReleaseLibraryEntries", [this](R3000& c) {
        const u32 table = c.arg(0);
        const auto it = std::find_if(libraries_.begin(), libraries_.end(), [&](const GuestLibrary& l) { return l.table == table; });
        if (it == libraries_.end()) { c.set_result(static_cast<u32>(kKeError)); return; }
        libraries_.erase(it);
        c.set_result(0);
    });
    def("loadcore", 11, "QueryLibraryEntryTable", [this](R3000& c) {
        std::string name;
        for (u32 i = 0; i < 8; ++i) {
            const u8 ch = c.read8(c.arg(0) + 12 + i);
            if (!ch) break;
            name.push_back(static_cast<char>(ch));
        }
        for (const GuestLibrary& l : libraries_)
            if (l.name == name) { c.set_result(l.table + 20); return; }
        c.set_result(0);
    });
    def("loadcore", 12, "QueryBootMode", [](R3000& c) { c.set_result(0); });

    // ---- sysclib ----
    def("sysclib", 6, "_toupper", [](R3000& c) {
        const u32 ch = c.arg(0) & 0xFFu;
        c.set_result(ch >= 'a' && ch <= 'z' ? ch - 32u : ch);
    });
    def("sysclib", 7, "_tolower", [](R3000& c) {
        const u32 ch = c.arg(0) & 0xFFu;
        c.set_result(ch >= 'A' && ch <= 'Z' ? ch + 32u : ch);
    });
    def("sysclib", 8, "look_ctype_table", [](R3000& c) { c.set_result(ctype_flags(c.arg(0))); });
    def("sysclib", 10, "memchr", [](R3000& c) {
        const u32 p = c.arg(0), ch = c.arg(1) & 0xFFu, n = c.arg(2);
        for (u32 i = 0; i < n; ++i)
            if (c.read8(p + i) == ch) { c.set_result(p + i); return; }
        c.set_result(0);
    });
    def("sysclib", 11, "memcmp", [](R3000& c) {
        const u32 a = c.arg(0), b = c.arg(1), n = c.arg(2);
        for (u32 i = 0; i < n; ++i) {
            const int d = static_cast<int>(c.read8(a + i)) - static_cast<int>(c.read8(b + i));
            if (d) { c.set_result(static_cast<u32>(d)); return; }
        }
        c.set_result(0);
    });
    auto copy = [](R3000& c, u32 dst, u32 src, u32 n) {
        if (dst <= src) for (u32 i = 0; i < n; ++i) c.write8(dst + i, c.read8(src + i));
        else for (u32 i = n; i-- > 0;) c.write8(dst + i, c.read8(src + i));
    };
    def("sysclib", 12, "memcpy", [copy](R3000& c) { copy(c, c.arg(0), c.arg(1), c.arg(2)); c.set_result(c.arg(0)); });
    def("sysclib", 13, "memmove", [copy](R3000& c) { copy(c, c.arg(0), c.arg(1), c.arg(2)); c.set_result(c.arg(0)); });
    def("sysclib", 14, "memset", [](R3000& c) {
        const u32 p = c.arg(0), n = c.arg(2);
        const u8 v = static_cast<u8>(c.arg(1));
        for (u32 i = 0; i < n; ++i) c.write8(p + i, v);
        c.set_result(p);
    });
    def("sysclib", 15, "bcmp", [](R3000& c) {
        const u32 a = c.arg(0), b = c.arg(1), n = c.arg(2);
        for (u32 i = 0; i < n; ++i)
            if (c.read8(a + i) != c.read8(b + i)) { c.set_result(1); return; }
        c.set_result(0);
    });
    def("sysclib", 16, "bcopy", [copy](R3000& c) { copy(c, c.arg(1), c.arg(0), c.arg(2)); c.set_result(0); });
    def("sysclib", 17, "bzero", [](R3000& c) {
        const u32 p = c.arg(0), n = c.arg(1);
        for (u32 i = 0; i < n; ++i) c.write8(p + i, 0);
        c.set_result(0);
    });
    def("sysclib", 19, "sprintf", [this](R3000& c) {
        const std::string s = format(c.arg(1), 2);
        u32 p = c.arg(0);
        for (char ch : s) c.write8(p++, static_cast<u8>(ch));
        c.write8(p, 0);
        c.set_result(static_cast<u32>(s.size()));
    });
    def("sysclib", 21, "strchr", [](R3000& c) {
        const u32 ch = c.arg(1) & 0xFFu;
        for (u32 p = c.arg(0);; ++p) {
            const u8 v = c.read8(p);
            if (v == ch) { c.set_result(p); return; }
            if (!v) { c.set_result(0); return; }
        }
    });
    def("sysclib", 22, "strcmp", [](R3000& c) {
        u32 a = c.arg(0), b = c.arg(1);
        for (;; ++a, ++b) {
            const u8 x = c.read8(a), y = c.read8(b);
            if (x != y || !x) { c.set_result(static_cast<u32>(static_cast<int>(x) - static_cast<int>(y))); return; }
        }
    });
    def("sysclib", 23, "strcpy", [](R3000& c) {
        u32 d = c.arg(0), s = c.arg(1);
        for (;; ++d, ++s) {
            const u8 v = c.read8(s);
            c.write8(d, v);
            if (!v) break;
        }
        c.set_result(c.arg(0));
    });
    def("sysclib", 27, "strlen", [](R3000& c) {
        u32 n = 0;
        while (c.read8(c.arg(0) + n)) ++n;
        c.set_result(n);
    });
    def("sysclib", 29, "strncmp", [](R3000& c) {
        u32 a = c.arg(0), b = c.arg(1);
        for (u32 n = c.arg(2); n > 0; --n, ++a, ++b) {
            const u8 x = c.read8(a), y = c.read8(b);
            if (x != y || !x) { c.set_result(static_cast<u32>(static_cast<int>(x) - static_cast<int>(y))); return; }
        }
        c.set_result(0);
    });
    def("sysclib", 30, "strncpy", [](R3000& c) {
        const u32 d = c.arg(0), s = c.arg(1), n = c.arg(2);
        bool end = false;
        for (u32 i = 0; i < n; ++i) {
            const u8 v = end ? 0 : c.read8(s + i);
            if (!v) end = true;
            c.write8(d + i, v);
        }
        c.set_result(d);
    });
    auto strto = [](R3000& c, bool is_signed) {
        const std::string s = c.c_string(c.arg(0), 64);
        char* end = nullptr;
        const int base = static_cast<int>(c.arg(2));
        const unsigned long long v = is_signed ? static_cast<unsigned long long>(std::strtoll(s.c_str(), &end, base)) : std::strtoull(s.c_str(), &end, base);
        if (c.arg(1)) c.write32(c.arg(1), c.arg(0) + static_cast<u32>(end - s.c_str()));
        c.set_result(static_cast<u32>(v));
    };
    def("sysclib", 36, "strtol", [strto](R3000& c) { strto(c, true); });
    def("sysclib", 38, "strtoul", [strto](R3000& c) { strto(c, false); });

    // ---- stdio ----
    def("stdio", 4, "printf", [this](R3000& c) {
        const std::string s = format(c.arg(0), 1);
        printf_log_.push_back(s);
        log_("[iop-printf] " + s);
        c.set_result(static_cast<u32>(s.size()));
    });
    def("stdio", 6, "putchar", [this](R3000& c) {
        printf_log_.push_back(std::string(1, static_cast<char>(c.arg(0))));
        c.set_result(c.arg(0));
    });
    def("stdio", 7, "puts", [this](R3000& c) {
        const std::string s = c.c_string(c.arg(0), 512);
        printf_log_.push_back(s);
        log_("[iop-printf] " + s);
        c.set_result(1);
    });

    // ---- sifcmd (SDRDRV's RPC thread 0x4E0: InitRpc, GetThreadId, SetRpcQueue, RegisterRpc, RpcLoop) ----
    def("sifcmd", 12, "sceSifSendCmd", [](R3000& c) { c.set_result(0); });
    def("sifcmd", 14, "sceSifInitRpc", [](R3000& c) { c.set_result(0); });
    def("sifcmd", 15, "sceSifBindRpc", [](R3000& c) {
        // The callback thread (0xE620 path) binds the EE's 0x80000704 in a retry loop (`16` §9.5; SDRDRV
        // 0x1004-0x1054: bind, a 10,000-iteration busy wait, then `lw cd+36` until it is non-zero): mark
        // the client bound -- SifRpcClientData_t.server at +36 (sifrpc-common.h) -- so the loop ends;
        // nothing is sent to the EE (its server data address is not modelled: a marker value).
        c.write32(c.arg(0) + 36, 0x0000FFF0u);
        c.write32(c.arg(0) + 20, 0);
        c.set_result(0);
    });
    def("sifcmd", 16, "sceSifCallRpc", [](R3000& c) { c.set_result(0); });
    def("sifcmd", 17, "sceSifRegisterRpc", [this](R3000& c) {
        RpcServerRecord r;
        r.sd = c.arg(0);
        r.sid = c.arg(1);
        r.func = c.arg(2);
        r.buf = c.arg(3);
        r.cfunc = c.arg(4);
        r.cbuf = c.arg(5);
        r.queue = c.arg(6);
        for (const RpcServerRecord& q : rpc_servers_)
            if (q.queue == r.queue) r.queue_thread = q.queue_thread;
        c.write32(r.sd + 4, r.sid);  // SifRpcServerData_t.sid (ps2sdk sifrpc.h layout)
        rpc_servers_.push_back(r);
        c.set_result(r.sd);
    });
    def("sifcmd", 19, "sceSifSetRpcQueue", [this](R3000& c) {
        RpcServerRecord q;
        q.queue = c.arg(0);
        q.queue_thread = static_cast<int>(c.arg(1));
        rpc_servers_.push_back(q);  // a queue record (sid 0) until RegisterRpc fills a server on it
        c.set_result(0);
    });
    def("sifcmd", 22, "sceSifRpcLoop", [this](R3000& c) {
        // Serves requests forever: the thread sleeps until a request is queued on `qd`. Increment 2
        // hands EE calls to the registered function on this thread; until then it stays blocked.
        c.set_result(0);
        block_current(WaitKind::Rpc, static_cast<int>(c.arg(0)));
    });
    def("sifcmd", 24, "sceSifRemoveRpc", [](R3000& c) { c.set_result(0); });
    def("sifcmd", 25, "sceSifRemoveRpcQueue", [](R3000& c) { c.set_result(0); });
}

}  // namespace p3fes::hle::sif::iop
