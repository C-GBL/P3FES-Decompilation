// NativeSk (sk_host.h): module start, the scheduler, the SK tick, the RPC entry, faults and machine state. The kernel's
// rules are the interpreter kernel's (runtime/hle/sif/iop/iop_kernel_hle.cpp), so the native stack keys the same
// voices at the same instants; the imports are in sk_imports.cpp.
#include "sk_host.h"

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

#include "p3fes/state_io.h"
#include "sk_gen.h"

namespace p3fes::native::sound::sk {

namespace {

constexpr u32 kKernelRanges[][2] = {{0x0009B900u, 0x000B0700u}, {0x000B2200u, 0x000BD400u}, {0x001F0000u, 0x001FF000u}};
constexpr u32 kModuleStartStack = 0x1000u;
constexpr int kModuleStartPriority = 8;
constexpr u32 kSdrdrvSid = 0x80000701u;

u32 rd32(std::span<const u8> d, std::size_t off) {
    u32 v = 0;
    if (off + 4 <= d.size()) std::memcpy(&v, d.data() + off, 4);
    return v;
}
u16 rd16(std::span<const u8> d, std::size_t off) {
    u16 v = 0;
    if (off + 2 <= d.size()) std::memcpy(&v, d.data() + off, 2);
    return v;
}

std::string hex32(u32 v) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%08X", v);
    return b;
}

// "cdrom0:\LIB31\SDRDRV.IRX;1" -> "SDRDRV.IRX"
std::string file_name_of(std::string_view path) {
    std::string n(path);
    if (const auto slash = n.find_last_of("\\/"); slash != std::string::npos) n = n.substr(slash + 1);
    if (const auto semi = n.find(';'); semi != std::string::npos) n = n.substr(0, semi);
    for (char& ch : n) ch = static_cast<char>(ch >= 'a' && ch <= 'z' ? ch - 32 : ch);
    return n;
}

// The relocated load image of an IRX at `base` (irx_loader.cpp's rules: R_MIPS_32 / 26 / HI16 + the next LO16).
bool relocate(std::span<const u8> f, u32 base, const ModuleImage& m, std::vector<u8>& img, std::string& error) {
    if (f.size() < 52 || std::memcmp(f.data(), "\x7f" "ELF", 4) != 0 || rd16(f, 18) != 8) {
        error = "not a MIPS ELF";
        return false;
    }
    const u32 phoff = rd32(f, 28), shoff = rd32(f, 32);
    const u16 phentsize = rd16(f, 42), phnum = rd16(f, 44), shentsize = rd16(f, 46), shnum = rd16(f, 48);
    u32 load_off = 0, load_size = 0, load_mem = 0;
    bool have = false;
    for (u32 i = 0; i < phnum; ++i) {
        const std::size_t ph = phoff + static_cast<std::size_t>(i) * phentsize;
        if (rd32(f, ph) == 1 && !have) {
            have = true;
            load_off = rd32(f, ph + 4);
            load_size = rd32(f, ph + 16);
            load_mem = rd32(f, ph + 20);
        }
    }
    if (!have || load_off + static_cast<u64>(load_size) > f.size()) {
        error = "no PT_LOAD";
        return false;
    }
    const u32 size = std::max(m.text + m.data + m.bss, std::max(load_size, load_mem));  // irx_image_size
    img.assign(size, 0);
    std::memcpy(img.data(), f.data() + load_off, load_size);
    // the text the code was made from (before relocation)
    u64 h = 0xCBF29CE484222325ull;
    for (u32 i = 0; i < m.text && i < img.size(); ++i) h = (h ^ img[i]) * 0x100000001B3ull;
    if (h != m.text_fnv) {
        error = std::string(m.file) + ": its code is not the one runtime/native/sound/sk was generated from";
        return false;
    }
    auto word = [&](u32 off) {
        u32 v = 0;
        if (off + 4 <= img.size()) std::memcpy(&v, img.data() + off, 4);
        return v;
    };
    auto put = [&](u32 off, u32 v) {
        if (off + 4 <= img.size()) std::memcpy(img.data() + off, &v, 4);
    };
    for (u32 i = 0; i < shnum; ++i) {
        const std::size_t sh = shoff + static_cast<std::size_t>(i) * shentsize;
        if (rd32(f, sh + 4) != 9) continue;  // SHT_REL
        const u32 off = rd32(f, sh + 16), n = rd32(f, sh + 20) / 8;
        bool have_hi = false;
        u32 hi_at = 0, hi_word = 0;
        for (u32 k = 0; k < n; ++k) {
            const u32 at = rd32(f, off + k * 8), type = rd32(f, off + k * 8 + 4) & 0xFFu;
            const u32 insn = word(at);
            switch (type) {
            case 2: put(at, insn + base); break;
            case 4: put(at, (insn & ~0x03FFFFFFu) | (((insn & 0x03FFFFFFu) + (base >> 2)) & 0x03FFFFFFu)); break;
            case 5:
                have_hi = true;
                hi_at = at;
                hi_word = insn;
                break;
            case 6: {
                const u32 lo = static_cast<u32>(static_cast<s32>(static_cast<s16>(insn & 0xFFFFu)));
                if (!have_hi) {
                    put(at, (insn & ~0xFFFFu) | ((lo + base) & 0xFFFFu));
                    break;
                }
                u32 v = lo + (hi_word << 16) + base;
                put(at, (insn & ~0xFFFFu) | (v & 0xFFFFu));
                if (v & 0x8000u) v += 0x10000u;
                put(hi_at, (hi_word & ~0xFFFFu) | (v >> 16));
                have_hi = false;
                break;
            }
            default: error = "relocation type " + std::to_string(type); return false;
            }
        }
    }
    return true;
}

}  // namespace

// ---- the generated code's helpers ------------------------------------------------------------------------------

Fn function_at(u32 addr) {
    const auto* b = std::begin(kFunctions);
    const auto* e = std::end(kFunctions);
    const auto* it = std::lower_bound(b, e, addr, [](const FnEntry& f, u32 a) { return f.addr < a; });
    return it != e && it->addr == addr && addr != 0 ? it->fn : nullptr;
}

void call_address(Cpu& c, u32 addr) {
    if (const Fn f = function_at(addr & 0x1FFFFFFFu)) return f(c);
    c.host->fail("call to " + hex32(addr) + ", which is no SK function");
    c.parked = true;  // unwind: the native stack has faulted
}

u32 Cpu::fault_load(u32 a) {
    host->fail("load from " + hex32(a) + " (misaligned or outside IOP RAM)");
    return 0;
}
void Cpu::fault_store(u32 a) { host->fail("store to " + hex32(a) + " (misaligned or outside IOP RAM)"); }
void Cpu::trap(u32 pc, const char* what) {
    host->fail(std::string(what) + " at " + hex32(pc));
    parked = true;
}
void Cpu::bad_return(u32 fn, u32 ra) { host->fail("function " + hex32(fn) + " returned to " + hex32(ra) + ", not to its caller"); }
void Cpu::bad_jump(u32 at, u32 target) {
    host->fail("jump at " + hex32(at) + " to " + hex32(target) + ", which is no label of its function");
    parked = true;
}
void Cpu::fell_off(u32 fn) { host->fail("function " + hex32(fn) + " ran past its last instruction"); }

// ---- NativeSk ------------------------------------------------------------------------------------------------------

NativeSk::NativeSk(SkPort& port) : port_(port) {
    c_.ram = port_.ram();
    c_.host = this;
}
NativeSk::~NativeSk() = default;

void NativeSk::fail(std::string what) {
    if (st_.fault.empty()) {
        st_.fault = what;
        port_.log("[native-sk] fault: " + what);
    }
}

bool NativeSk::install(const std::function<std::optional<std::vector<u8>>(std::string_view)>& read, std::string& error) {
    if (!kGenerated) {
        error = "the native SK code was not generated (no LIB31 when the build was configured: P3FES_LIB31_DIR)";
        return false;
    }
    for (std::size_t i = 0; i < std::size(kModules); ++i) {
        const ModuleImage& m = kModules[i];
        const auto bytes = read(m.file);
        if (!bytes) {
            error = std::string(m.file) + " is not readable";
            return false;
        }
        std::vector<u8> img;
        if (!relocate(*bytes, m.base, m, img, error)) return false;
        images_[i].data.assign(img.begin() + m.text, img.begin() + m.text + m.data);
        images_[i].size = static_cast<u32>(img.size());
    }
    installed_ = true;
    return true;
}

u32 NativeSk::gp_for(u32 addr) const {
    for (const ModuleImage& m : kModules)
        if (addr >= m.base && addr < m.base + m.text + m.data + m.bss) return m.gp;
    return 0;
}

u32 NativeSk::alloc_module(u32 size) {
    for (const auto& r : kKernelRanges)
        if (const u32 a = port_.alloc_in(r[0], r[1], size)) return a;
    return 0;
}
u32 NativeSk::alloc_kernel(u32 size) {
    for (auto it = std::rbegin(kKernelRanges); it != std::rend(kKernelRanges); ++it)
        if (const u32 a = port_.alloc_in((*it)[0], (*it)[1], size)) return a;
    return 0;
}

void NativeSk::ensure_setup() {
    // The interpreter's kernel takes its interrupt stack and its RPC-return trampoline at the first module load: the
    // same two blocks here keep every later allocation (stacks, work areas) at the faithful address.
    if (!intr_stack_) intr_stack_ = alloc_kernel(0x1000);
    if (!rpc_return_) rpc_return_ = alloc_kernel(16);
    if (!intr_stack_ || !rpc_return_) fail("no IOP memory for the interrupt stack / RPC return");
}

// ---- threads -----------------------------------------------------------------------------------------------------

NativeSk::Thread* NativeSk::thread(int id) {
    const auto it = threads_.find(id);
    return it == threads_.end() ? nullptr : &it->second;
}
NativeSk::Thread* NativeSk::current() { return current_ ? thread(current_) : nullptr; }

int NativeSk::create_thread(u32 attr, u32 option, u32 entry, u32 stack_size, int priority) {
    const u32 size = std::max<u32>(stack_size, 0x200u);
    const u32 stack = alloc_kernel(size);
    if (!stack) return -400;  // KE_NO_MEMORY
    Thread t;
    t.id = next_thread_id_++;
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

bool NativeSk::start_thread(int id, u32 a0, u32 a1) {
    Thread* t = thread(id);
    if (!t || t->status != Status::Dormant) return false;
    std::fill(std::begin(t->regs), std::end(t->regs), 0u);
    t->hi = t->lo = 0;
    t->regs[4] = a0;
    t->regs[5] = a1;
    t->regs[28] = t->gp;
    t->regs[29] = (t->stack + t->stack_size - 16u) & ~7u;
    t->regs[31] = kExitSentinel;
    t->resume = 0;
    t->wakeups = 0;
    t->wait = Wait::None;
    make_ready(*t);
    return true;
}

void NativeSk::make_ready(Thread& t) {
    t.status = Status::Ready;
    t.wait = Wait::None;
    t.ready_seq = ++ready_counter_;
}

NativeSk::Thread* NativeSk::pick_ready(int above) {
    Thread* best = nullptr;
    for (auto& [id, t] : threads_) {
        if (t.status != Status::Ready || t.priority >= above) continue;
        if (!best || t.priority < best->priority || (t.priority == best->priority && t.ready_seq < best->ready_seq)) best = &t;
    }
    return best;
}

void NativeSk::block_current(Wait kind, int id) {
    Thread* t = current();
    if (!t) {
        fail("a blocking call outside a thread");
        c_.parked = true;
        return;
    }
    t->status = Status::Wait;
    t->wait = kind;
    t->wait_id = id;
    t->resume = c_.r[31];  // the instruction after the jal (the import's $ra)
    c_.parked = true;
}

// Runs `t` (Ready) until it blocks or its entry returns. A nested run (a thread readied by the running one) keeps the
// running thread's registers and gives them back afterwards, as the interpreter kernel's context switch does.
void NativeSk::run(Thread& t) {
    const Fn entry = function_at(t.entry);
    if (!entry) {
        fail("thread entry " + hex32(t.entry) + " is no SK function");
        t.status = Status::Dormant;
        return;
    }
    const int prev = current_;
    u32 saved[32];
    std::memcpy(saved, c_.r, sizeof saved);
    const u32 shi = c_.hi, slo = c_.lo;
    if (Thread* p = thread(prev)) p->status = Status::Ready;  // preempted: back in its level, keeping its place

    current_ = t.id;
    t.status = Status::Run;
    std::memcpy(c_.r, t.regs, sizeof t.regs);
    c_.hi = t.hi;
    c_.lo = t.lo;
    c_.parked = false;
    c_.resume = t.resume;
    c_.resume_ra0 = kExitSentinel;
    ++st_.thread_runs;
    entry(c_);
    Thread* self = thread(t.id);
    if (self) {
        if (c_.parked) {
            std::memcpy(self->regs, c_.r, sizeof c_.r);
            self->hi = c_.hi;
            self->lo = c_.lo;
            if (self->status == Status::Run) self->status = Status::Ready;  // parked by a fault, not a block
        } else {
            self->status = Status::Dormant;
            self->exit_value = c_.r[2];
            self->resume = 0;
        }
    }
    c_.parked = false;
    c_.resume = 0;
    std::memcpy(c_.r, saved, sizeof saved);
    c_.hi = shi;
    c_.lo = slo;
    current_ = prev;
    if (Thread* p = thread(prev)) p->status = Status::Run;
}

void NativeSk::preempt() {
    Thread* cur = current();
    if (!cur || in_handler_) return;
    while (!faulted()) {
        Thread* t = pick_ready(cur->priority);
        if (!t) break;
        run(*t);
        cur = current();
        if (!cur) break;
    }
}

void NativeSk::run_until_idle() {
    while (!faulted()) {
        Thread* t = pick_ready(INT_MAX);
        if (!t) break;
        run(*t);
    }
}

u32 NativeSk::run_handler(u32 fn, u32 a0, u32 gp) {
    ensure_setup();
    const Fn f = function_at(fn);
    if (!f) {
        fail("interrupt handler " + hex32(fn) + " is no SK function");
        return 0;
    }
    u32 saved[32];
    std::memcpy(saved, c_.r, sizeof saved);
    const u32 shi = c_.hi, slo = c_.lo;
    const int prev = current_;
    const bool prev_in = in_handler_;
    current_ = 0;
    in_handler_ = true;
    std::fill(std::begin(c_.r), std::end(c_.r), 0u);
    c_.hi = c_.lo = 0;
    c_.r[4] = a0;
    c_.r[28] = gp;
    c_.r[29] = (intr_stack_ + 0x1000u - 16u) & ~7u;
    c_.r[31] = kExitSentinel;
    c_.parked = false;
    f(c_);
    const u32 ret = c_.parked ? 0u : c_.r[2];
    if (c_.parked && !faulted()) fail("interrupt handler " + hex32(fn) + " blocked");
    c_.parked = false;
    std::memcpy(c_.r, saved, sizeof saved);
    c_.hi = shi;
    c_.lo = slo;
    current_ = prev;
    in_handler_ = prev_in;
    return ret;
}

// ---- time -------------------------------------------------------------------------------------------------------

u64 NativeSk::next_deadline() const {
    u64 d = ~0ull;
    for (const auto& [id, t] : timers_)
        if (t.running) d = std::min(d, t.deadline);
    return d;
}

void NativeSk::advance(u64 now) {
    if (!started_) return;
    run_until_idle();
    while (!faulted()) {
        const u64 d = next_deadline();
        if (d > now) break;
        now_ = std::max(now_, d);
        port_.at_time(now_);
        for (auto& [id, t] : timers_) {
            if (!t.running || t.deadline > now_) continue;
            ++t.fired;
            ++st_.tick_runs;
            const u32 ret = t.handler ? run_handler(t.handler, t.common, gp_for(t.handler)) : 0;
            if (ret != 0) {
                t.deadline += static_cast<u64>(ret) * 8u;  // re-armed from the previous deadline (EE = IOP clock x 8)
            } else {
                t.running = false;
            }
        }
        run_until_idle();
    }
    now_ = std::max(now_, now);
    port_.at_time(now_);
}

// ---- modules ------------------------------------------------------------------------------------------------------

// loadcore's argv block (kernel memory): the path, then the NUL-separated arguments; returns its address (0: no memory).
u32 NativeSk::write_argv(std::string_view path, std::string_view args, u32* argc) {
    std::vector<std::string> argv{std::string(path)};
    for (std::size_t s = 0; s < args.size();) {
        const std::size_t e = args.find('\0', s);
        const std::string a(args.substr(s, e == std::string_view::npos ? std::string_view::npos : e - s));
        if (!a.empty()) argv.push_back(a);
        if (e == std::string_view::npos) break;
        s = e + 1;
    }
    u32 size = 4u * static_cast<u32>(argv.size() + 1);
    for (const std::string& a : argv) size += static_cast<u32>(a.size() + 1);
    const u32 av = alloc_kernel(size);
    if (!av) return 0;
    u8* ram = port_.ram();
    u32 text = av + 4u * static_cast<u32>(argv.size() + 1);
    for (std::size_t i = 0; i < argv.size(); ++i) {
        c_.put32(av + 4u * static_cast<u32>(i), text);
        for (char ch : argv[i]) ram[Cpu::off(text++)] = static_cast<u8>(ch);
        ram[Cpu::off(text++)] = 0;
    }
    c_.put32(av + 4u * static_cast<u32>(argv.size()), 0);
    if (argc) *argc = static_cast<u32>(argv.size());
    return av;
}

s32 NativeSk::load_module(u64 now, std::string_view path, std::string_view args, s32* start_result) {
    if (start_result) *start_result = 0;
    if (!installed_) return -1;
    const s32 id = next_module_id_++;  // loadfile's id; >= 0 even after a fault (the game retries a failed load forever)
    if (faulted()) return id;
    const std::string name = file_name_of(path);
    std::size_t idx = std::size(kModules);
    for (std::size_t i = 0; i < std::size(kModules); ++i)
        if (name == kModules[i].file) idx = i;
    if (idx == std::size(kModules)) return id;  // LIBSD.IRX / MODMSIN.IRX: HLE'd entries, nothing runs
    started_ = true;
    advance(now);  // the module starts at virtual `now` (its timer, GetSystemTime)
    ensure_setup();
    const ModuleImage& m = kModules[idx];
    const u32 image = images_[idx].size;
    if (loaded_[idx]) {
        // The game's second SKHSYNTH: the interpreter loads it at another address (its pinned base is taken), its start
        // finds the library registered and returns NO_RESIDENT_END, and its image and start stack are freed; only its
        // argv block stays allocated. The same blocks are taken here (so every later address is the faithful one);
        // nothing runs.
        if (start_result) *start_result = 1;
        const u32 block = alloc_module(image + 0x30u);
        const u32 av = write_argv(path, args, nullptr);
        const u32 stack = alloc_kernel(std::max<u32>(kModuleStartStack, 0x200u));
        ++next_thread_id_;  // its start thread had an id
        if (block) port_.free(block);
        if (stack) port_.free(stack);
        if (!block || !av || !stack) fail("no IOP memory for the second SKHSYNTH's blocks");
        return id;
    }
    const u32 block = port_.alloc_at(m.base - 0x30u, image + 0x30u);
    if (block != m.base - 0x30u) {
        fail(std::string(m.file) + ": its image block at " + hex32(m.base - 0x30u) + " is not free");
        return id;
    }
    u8* ram = port_.ram();
    std::memset(ram + m.base, 0, image);  // text stays zero: its code is sk_gen_*.cpp
    std::memcpy(ram + m.base + m.text, images_[idx].data.data(), images_[idx].data.size());
    loaded_[idx] = true;

    u32 argc = 0;
    const u32 av = write_argv(path, args, &argc);
    if (!av) {
        fail("no IOP memory for argv");
        return id;
    }

    const int tid = create_thread(0x02000000u, 0, m.entry, kModuleStartStack, kModuleStartPriority);
    if (tid <= 0) {
        fail("no IOP memory for the start thread");
        return id;
    }
    start_thread(tid, argc, av);
    run_until_idle();
    ++st_.modules;
    Thread* t = thread(tid);
    if (t && t->status == Status::Dormant) {
        const s32 r = static_cast<s32>(t->exit_value);
        if (start_result) *start_result = r;
        if (r == 1) port_.free(block);  // MODULE_NO_RESIDENT_END
        port_.free(t->stack);
        threads_.erase(tid);
    }
    return id;
}

// ---- RPC ----------------------------------------------------------------------------------------------------------

std::optional<std::vector<u8>> NativeSk::rpc(u64 now, u32 fno, std::span<const u8> send, u32 recv_size) {
    if (!installed_ || faulted()) return std::nullopt;
    advance(now);  // ticks due before this request run first
    const RpcServer* srv = nullptr;
    for (const RpcServer& r : rpc_servers_)
        if (r.sid == kSdrdrvSid && r.func != 0) srv = &r;
    if (!srv) {
        fail("SDRDRV's RPC server is not registered");
        return std::nullopt;
    }
    Thread* t = thread(srv->queue_thread);
    const Fn handler = function_at(srv->func);
    if (!t || t->status != Status::Wait || t->wait != Wait::Rpc || !handler) {
        fail("SDRDRV's RPC thread is not in sceSifRpcLoop");
        return std::nullopt;
    }
    // The request lands in the server's receive buffer (what the SIF DMA does on the faithful path).
    u8* ram = port_.ram();
    std::memmove(ram + Cpu::off(srv->buf), send.data(), std::min<std::size_t>(send.size(), kRamSize - Cpu::off(srv->buf)));
    // The handler frame below the loop's: (fno, buffer, size), returning to the RPC-return trampoline.
    const Thread saved = *t;
    current_ = t->id;
    t->status = Status::Run;
    std::memcpy(c_.r, t->regs, sizeof c_.r);
    c_.hi = t->hi;
    c_.lo = t->lo;
    c_.r[4] = fno;
    c_.r[5] = srv->buf;
    c_.r[6] = static_cast<u32>(send.size());
    c_.r[29] = (t->regs[29] - 32u) & ~7u;
    c_.r[31] = rpc_return_;
    c_.parked = false;
    ++st_.rpc_calls;
    handler(c_);
    const bool blocked = c_.parked;
    const u32 result = c_.r[2];
    c_.parked = false;
    current_ = 0;
    if (Thread* back = thread(saved.id)) {  // back into sceSifRpcLoop's wait (rpc_return: the context and the wait only)
        std::memcpy(back->regs, saved.regs, sizeof saved.regs);
        back->hi = saved.hi;
        back->lo = saved.lo;
        back->status = Status::Wait;
        back->wait = Wait::Rpc;
        back->wait_id = saved.wait_id;
        back->resume = saved.resume;
    }
    if (blocked) {
        if (!faulted()) fail("SDRDRV's handler blocked for fno " + hex32(fno));
        return std::nullopt;
    }
    run_until_idle();
    std::vector<u8> reply(std::max<u32>(recv_size, 16u), 0);
    if (result) std::memcpy(reply.data(), ram + Cpu::off(result), std::min<std::size_t>(reply.size(), kRamSize - Cpu::off(result)));
    return reply;
}

void NativeSk::sd_remote(u64 now, u32 fno, std::span<const u8> send, std::span<u8> recv) {
    const auto reply = rpc(now, fno, send, static_cast<u32>(recv.size()));
    std::fill(recv.begin(), recv.end(), u8{0});
    s32 result = 0;
    if (reply) {
        std::memcpy(recv.data(), reply->data(), std::min(recv.size(), reply->size()));
        std::memcpy(&result, reply->data(), 4);
    }
    port_.record(fno, send, result, now);
}

// ---- machine state ----------------------------------------------------------------------------------------------

namespace {
template <class F>
void each_thread_field(NativeSk::Thread& t, F&& f) {
    f(t.id), f(t.attr), f(t.option), f(t.entry), f(t.stack), f(t.stack_size), f(t.gp), f(t.init_priority), f(t.priority);
    f(t.status), f(t.wait), f(t.wait_id), f(t.wakeups), f(t.ready_seq), f(t.regs), f(t.hi), f(t.lo), f(t.resume), f(t.exit_value);
}
}  // namespace

void NativeSk::state(StateIo& io) {
    io(loaded_);
    io(started_);
    io(next_module_id_);
    io(now_);
    u32 n = static_cast<u32>(threads_.size());
    io(n);
    if (io.loading()) threads_.clear();
    auto it = threads_.begin();
    for (u32 i = 0; i < n; ++i) {
        Thread t = io.loading() ? Thread{} : (it++)->second;
        each_thread_field(t, [&](auto& v) { io(v); });
        if (io.loading()) threads_[t.id] = t;
    }
    io(next_thread_id_);
    io(ready_counter_);
    u32 ns = static_cast<u32>(semas_.size());
    io(ns);
    if (io.loading()) semas_.clear();
    auto si = semas_.begin();
    for (u32 i = 0; i < ns; ++i) {
        Sema s = io.loading() ? Sema{} : (si++)->second;
        io(s.id), io(s.attr), io(s.option), io(s.count), io(s.max), io(s.waiters);
        if (io.loading()) semas_[s.id] = s;
    }
    io(next_sema_id_);
    u32 nt = static_cast<u32>(timers_.size());
    io(nt);
    if (io.loading()) timers_.clear();
    auto ti = timers_.begin();
    for (u32 i = 0; i < nt; ++i) {
        Timer t = io.loading() ? Timer{} : (ti++)->second;
        io(t);
        if (io.loading()) timers_[t.id] = t;
    }
    io(next_timer_id_);
    io(suspend_depth_);
    io(rpc_servers_);
    io(intr_stack_);
    io(rpc_return_);
    io(st_.modules), io(st_.rpc_calls), io(st_.tick_runs), io(st_.thread_runs), io(st_.libsd_calls), io(st_.kernel_calls), io(st_.fault);
}

}  // namespace p3fes::native::sound::sk
