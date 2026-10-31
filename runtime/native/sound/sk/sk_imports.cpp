// The imports the generated SK code calls (sk_gen.h `imp_*`), on NativeSk (sk_host.h). Each one answers as the
// interpreter's host call of the same library and ordinal does (runtime/hle/sif/iop/iop_kernel_hle.cpp for the kernel,
// libsd_hle.cpp for libsd: here forwarded to the IOP model's libsd by ordinal, SkPort::libsd), reading a0..a3 and the
// stack and writing v0, so the native modules see the same answers.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "sk_gen.h"
#include "sk_host.h"

namespace p3fes::native::sound::sk {

namespace {

constexpr s32 kKeError = -1, kKeIllegalThid = -406, kKeIllegalSemid = -408, kKeCpuDi = -102;

NativeSk& K(Cpu& c) { return *c.host; }
void ret(Cpu& c, u32 v) { c.r[2] = v; }
u8 rd8(Cpu& c, u32 a) { return c.ram[Cpu::off(a)]; }
void wr8(Cpu& c, u32 a, u8 v) { c.ram[Cpu::off(a)] = v; }
u32 rd32(Cpu& c, u32 a) { return c.raw32(a); }
void wr32(Cpu& c, u32 a, u32 v) { c.put32(a, v); }

std::string c_string(Cpu& c, u32 a, std::size_t max) {
    std::string s;
    for (std::size_t i = 0; i < max; ++i) {
        const char ch = static_cast<char>(rd8(c, a + static_cast<u32>(i)));
        if (!ch) break;
        s.push_back(ch);
    }
    return s;
}

// printf's formatting, as the interpreter kernel's (IopKernel::format).
std::string format(Cpu& c, u32 fmt, unsigned first_arg) {
    std::string out;
    unsigned ai = first_arg;
    const std::string f = c_string(c, fmt, 1024);
    for (std::size_t i = 0; i < f.size(); ++i) {
        if (f[i] != '%') {
            out.push_back(f[i]);
            continue;
        }
        std::string spec = "%";
        ++i;
        while (i < f.size() && std::strchr("-+ #0123456789.", f[i])) spec.push_back(f[i++]);
        while (i < f.size() && (f[i] == 'l' || f[i] == 'h')) ++i;
        if (i >= f.size()) break;
        const char conv = f[i];
        char buf[64];
        switch (conv) {
        case 'd': case 'i':
            std::snprintf(buf, sizeof buf, (spec + "d").c_str(), static_cast<int>(c.arg(ai++)));
            out += buf;
            break;
        case 'u': case 'x': case 'X': case 'o': case 'c':
            std::snprintf(buf, sizeof buf, (spec + conv).c_str(), c.arg(ai++));
            out += buf;
            break;
        case 'p':
            std::snprintf(buf, sizeof buf, "%08X", c.arg(ai++));
            out += buf;
            break;
        case 's': out += c_string(c, c.arg(ai++), 512); break;
        case '%': out.push_back('%'); break;
        default:
            out += spec;
            out.push_back(conv);
            break;
        }
    }
    return out;
}

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

void libsd(Cpu& c, u32 ordinal) { ret(c, static_cast<u32>(K(c).libsd_call(ordinal))); }

void wakeup(Cpu& c) {
    NativeSk& k = K(c);
    k.count_kernel();
    NativeSk::Thread* t = k.thread(static_cast<int>(c.arg(0)));
    if (!t) return ret(c, static_cast<u32>(kKeIllegalThid));
    ret(c, 0);
    if (t->status == NativeSk::Status::Wait && t->wait == NativeSk::Wait::Sleep) {
        t->regs[2] = 0;
        k.make_ready(*t);
        k.preempt();
    } else if (t->status != NativeSk::Status::Dormant) {
        ++t->wakeups;
    }
}

}  // namespace

u64 NativeSk::libsd_call(u32 ordinal) {
    ++st_.libsd_calls;
    const u32 a[5] = {c_.arg(0), c_.arg(1), c_.arg(2), c_.arg(3), c_.arg(4)};
    return port_.libsd(ordinal, a);
}

// ---- libsd: the IOP model's libsd over the SPU2 voice model, by ordinal -------------------------------------------
void imp_libsd_sceSdInit(Cpu& c) { libsd(c, 4); }
void imp_libsd_sceSdSetParam(Cpu& c) { libsd(c, 5); }
void imp_libsd_sceSdGetParam(Cpu& c) { libsd(c, 6); }
void imp_libsd_sceSdSetSwitch(Cpu& c) { libsd(c, 7); }
void imp_libsd_sceSdGetSwitch(Cpu& c) { libsd(c, 8); }
void imp_libsd_sceSdSetAddr(Cpu& c) { libsd(c, 9); }
void imp_libsd_sceSdGetAddr(Cpu& c) { libsd(c, 10); }
void imp_libsd_sceSdSetCoreAttr(Cpu& c) { libsd(c, 11); }
void imp_libsd_sceSdGetCoreAttr(Cpu& c) { libsd(c, 12); }
void imp_libsd_sceSdNote2Pitch(Cpu& c) { libsd(c, 13); }
void imp_libsd_sceSdPitch2Note(Cpu& c) { libsd(c, 14); }
void imp_libsd_sceSdProcBatch(Cpu& c) { libsd(c, 15); }
void imp_libsd_sceSdProcBatchEx(Cpu& c) { libsd(c, 16); }
void imp_libsd_sceSdVoiceTrans(Cpu& c) { libsd(c, 17); }
void imp_libsd_sceSdBlockTrans(Cpu& c) { libsd(c, 18); }
void imp_libsd_sceSdVoiceTransStatus(Cpu& c) { libsd(c, 19); }
void imp_libsd_sceSdBlockTransStatus(Cpu& c) { libsd(c, 20); }
void imp_libsd_sceSdSetEffectAttr(Cpu& c) { libsd(c, 23); }
void imp_libsd_sceSdGetEffectAttr(Cpu& c) { libsd(c, 24); }
void imp_libsd_sceSdClearEffectWorkArea(Cpu& c) { libsd(c, 25); }
void imp_libsd_sceSdSetTransIntrHandler(Cpu& c) { libsd(c, 26); }
void imp_libsd_sceSdSetSpu2IntrHandler(Cpu& c) { libsd(c, 27); }
void imp_libsd_sceSdStopTrans(Cpu& c) { libsd(c, 30); }
void imp_libsd_sceSdCleanEffectWorkArea(Cpu& c) { libsd(c, 31); }
void imp_libsd_sceSdSetEffectMode(Cpu& c) { libsd(c, 32); }
void imp_libsd_sceSdSetEffectModeParams(Cpu& c) { libsd(c, 33); }

// ---- intrman ------------------------------------------------------------------------------------------------------
void imp_intrman_CpuSuspendIntr(Cpu& c) {
    // *state receives the old SR (interrupts on = 0x401) -- CpuResumeIntr takes it back.
    int& depth = K(c).suspend_depth();
    if (c.arg(0)) wr32(c, c.arg(0), depth > 0 ? 0x400u : 0x401u);
    ret(c, depth > 0 ? static_cast<u32>(kKeCpuDi) : 0u);
    ++depth;
}
void imp_intrman_CpuResumeIntr(Cpu& c) {
    int& depth = K(c).suspend_depth();
    if (depth > 0) --depth;
    ret(c, 0);
}

// ---- loadcore: every library is registered once natively (the game's duplicate SKHSYNTH does not run) -----------
void imp_loadcore_RegisterLibraryEntries(Cpu& c) { ret(c, 0); }
void imp_loadcore_ReleaseLibraryEntries(Cpu& c) { ret(c, 0); }

// ---- sifcmd: SDRDRV's server records; nothing goes to the EE ---------------------------------------------------------
void imp_sifcmd_sceSifInitRpc(Cpu& c) { ret(c, 0); }
void imp_sifcmd_sceSifBindRpc(Cpu& c) {
    // The callback thread binds the EE's 0x80000704 in a retry loop until SifRpcClientData_t.server (+36) is set: as
    // the interpreter's kernel, a marker value, nothing sent.
    wr32(c, c.arg(0) + 36, 0x0000FFF0u);
    wr32(c, c.arg(0) + 20, 0);
    ret(c, 0);
}
void imp_sifcmd_sceSifCallRpc(Cpu& c) { ret(c, 0); }
void imp_sifcmd_sceSifRegisterRpc(Cpu& c) {
    NativeSk& k = K(c);
    NativeSk::RpcServer r;
    r.sd = c.arg(0);
    r.sid = c.arg(1);
    r.func = c.arg(2);
    r.buf = c.arg(3);
    r.cfunc = c.arg(4);
    r.cbuf = c.arg(5);
    r.queue = c.arg(6);
    for (const NativeSk::RpcServer& q : k.rpc_servers())
        if (q.queue == r.queue) r.queue_thread = q.queue_thread;
    wr32(c, r.sd + 4, r.sid);
    k.rpc_servers().push_back(r);
    ret(c, r.sd);
}
void imp_sifcmd_sceSifSetRpcQueue(Cpu& c) {
    NativeSk::RpcServer q;
    q.queue = c.arg(0);
    q.queue_thread = static_cast<int>(c.arg(1));
    K(c).rpc_servers().push_back(q);
    ret(c, 0);
}
void imp_sifcmd_sceSifRpcLoop(Cpu& c) {
    ret(c, 0);
    K(c).block_current(NativeSk::Wait::Rpc, static_cast<int>(c.arg(0)));
}
void imp_sifcmd_sceSifRemoveRpc(Cpu& c) { ret(c, 0); }
void imp_sifcmd_sceSifRemoveRpcQueue(Cpu& c) { ret(c, 0); }

// ---- stdio / sysmem / sysclib ------------------------------------------------------------------------------------
void imp_stdio_printf(Cpu& c) {
    const std::string s = format(c, c.arg(0), 1);
    K(c).port().log("[iop-printf] " + s);
    ret(c, static_cast<u32>(s.size()));
}
void imp_sysmem_Kprintf(Cpu& c) {
    const std::string s = format(c, c.arg(0), 1);
    K(c).port().log("[iop-kprintf] " + s);
    ret(c, static_cast<u32>(s.size()));
}
void imp_sysmem_AllocSysMemory(Cpu& c) {
    // The modules' work areas come from the kernel ranges (mode 2 "at address" as asked), so the game's heap
    // allocations keep their addresses -- the interpreter kernel's rule.
    NativeSk& k = K(c);
    k.count_kernel();
    const u32 mode = c.arg(0), size = c.arg(1), addr = c.arg(2);
    const u32 got = mode == 2 ? k.port().alloc_at(addr, size) : k.alloc_module(size);
    if (!got) k.port().log("[native-sk] AllocSysMemory(" + std::to_string(mode) + ", " + std::to_string(size) + ") failed");
    ret(c, got);
}
void imp_sysmem_FreeSysMemory(Cpu& c) { ret(c, K(c).port().free(c.arg(0)) ? 0u : static_cast<u32>(kKeError)); }
void imp_sysclib_look_ctype_table(Cpu& c) { ret(c, ctype_flags(c.arg(0))); }
void imp_sysclib_memset(Cpu& c) {
    const u32 p = c.arg(0), n = c.arg(2);
    const u8 v = static_cast<u8>(c.arg(1));
    for (u32 i = 0; i < n; ++i) wr8(c, p + i, v);
    ret(c, p);
}
void imp_sysclib_bzero(Cpu& c) {
    const u32 p = c.arg(0), n = c.arg(1);
    for (u32 i = 0; i < n; ++i) wr8(c, p + i, 0);
    ret(c, 0);
}
void imp_sysclib_strlen(Cpu& c) {
    u32 n = 0;
    while (rd8(c, c.arg(0) + n)) ++n;
    ret(c, n);
}
void imp_sysclib_strncmp(Cpu& c) {
    u32 a = c.arg(0), b = c.arg(1);
    for (u32 n = c.arg(2); n > 0; --n, ++a, ++b) {
        const u8 x = rd8(c, a), y = rd8(c, b);
        if (x != y || !x) return ret(c, static_cast<u32>(static_cast<int>(x) - static_cast<int>(y)));
    }
    ret(c, 0);
}
void imp_sysclib_strtol(Cpu& c) {
    const std::string s = c_string(c, c.arg(0), 64);
    char* end = nullptr;
    const auto v = static_cast<unsigned long long>(std::strtoll(s.c_str(), &end, static_cast<int>(c.arg(2))));
    if (c.arg(1)) wr32(c, c.arg(1), c.arg(0) + static_cast<u32>(end - s.c_str()));
    ret(c, static_cast<u32>(v));
}

// ---- thbase -------------------------------------------------------------------------------------------------------
void imp_thbase_CreateThread(Cpu& c) {
    NativeSk& k = K(c);
    k.count_kernel();
    const u32 p = c.arg(0);
    ret(c, static_cast<u32>(k.create_thread(rd32(c, p), rd32(c, p + 4), rd32(c, p + 8), rd32(c, p + 12), static_cast<int>(rd32(c, p + 16)))));
}
void imp_thbase_DeleteThread(Cpu& c) {
    NativeSk& k = K(c);
    const int id = static_cast<int>(c.arg(0));
    NativeSk::Thread* t = k.thread(id);
    if (!t) return ret(c, static_cast<u32>(kKeIllegalThid));
    if (t->status != NativeSk::Status::Dormant) return ret(c, static_cast<u32>(kKeError));
    k.port().free(t->stack);
    k.threads().erase(id);
    ret(c, 0);
}
void imp_thbase_StartThread(Cpu& c) {
    NativeSk& k = K(c);
    k.count_kernel();
    if (!k.start_thread(static_cast<int>(c.arg(0)), c.arg(1), 0)) return ret(c, static_cast<u32>(kKeIllegalThid));
    ret(c, 0);
    k.preempt();
}
void imp_thbase_TerminateThread(Cpu& c) {
    NativeSk& k = K(c);
    NativeSk::Thread* t = k.thread(static_cast<int>(c.arg(0)));
    if (!t) return ret(c, static_cast<u32>(kKeIllegalThid));
    for (auto& [sid, s] : k.semas()) std::erase(s.waiters, t->id);
    t->status = NativeSk::Status::Dormant;
    t->wait = NativeSk::Wait::None;
    ret(c, 0);
    if (t->id == k.current_id()) {
        k.fail("a thread terminated itself");  // the interpreter stops it there; nothing on the SK path does this
        c.parked = true;
    }
}
void imp_thbase_ChangeThreadPriority(Cpu& c) {
    NativeSk& k = K(c);
    int id = static_cast<int>(c.arg(0));
    if (id == 0) id = k.current_id();
    NativeSk::Thread* t = k.thread(id);
    if (!t) return ret(c, static_cast<u32>(kKeIllegalThid));
    t->priority = static_cast<int>(c.arg(1));
    if (t->status == NativeSk::Status::Ready) k.make_ready(*t);
    ret(c, 0);
    k.preempt();
}
void imp_thbase_GetThreadId(Cpu& c) { ret(c, static_cast<u32>(K(c).current_id())); }
void imp_thbase_ReferThreadStatus(Cpu& c) {
    NativeSk& k = K(c);
    int id = static_cast<int>(c.arg(0));
    if (id == 0) id = k.current_id();
    NativeSk::Thread* t = k.thread(id);
    if (!t) return ret(c, static_cast<u32>(kKeIllegalThid));
    u32 status = 0x10;
    switch (t->status) {
    case NativeSk::Status::Run: status = 0x01; break;
    case NativeSk::Status::Ready: status = 0x02; break;
    case NativeSk::Status::Wait: status = 0x04; break;
    case NativeSk::Status::Dormant: status = 0x10; break;
    }
    u32 wait_type = 0;
    switch (t->wait) {
    case NativeSk::Wait::Sleep: wait_type = 1; break;
    case NativeSk::Wait::Sema: wait_type = 3; break;
    case NativeSk::Wait::Rpc: wait_type = 1; break;
    case NativeSk::Wait::None: break;
    }
    const u32 words[13] = {t->attr, t->option, status, t->entry, t->stack, t->stack_size, t->gp, static_cast<u32>(t->init_priority),
                           static_cast<u32>(t->priority), wait_type, static_cast<u32>(t->wait_id), static_cast<u32>(t->wakeups), 0};
    for (u32 i = 0; i < 13; ++i) wr32(c, c.arg(1) + 4u * i, words[i]);
    ret(c, 0);
}
void imp_thbase_SleepThread(Cpu& c) {
    NativeSk& k = K(c);
    k.count_kernel();
    NativeSk::Thread* t = k.current();
    ret(c, 0);
    if (!t) {
        k.fail("SleepThread outside a thread");
        c.parked = true;
        return;
    }
    if (t->wakeups > 0) {
        --t->wakeups;
        return;
    }
    k.block_current(NativeSk::Wait::Sleep, 0);
}
void imp_thbase_iWakeupThread(Cpu& c) { wakeup(c); }
void imp_thbase_iCancelWakeupThread(Cpu& c) {
    NativeSk& k = K(c);
    int id = static_cast<int>(c.arg(0));
    if (id == 0) id = k.current_id();
    NativeSk::Thread* t = k.thread(id);
    if (!t) return ret(c, static_cast<u32>(kKeIllegalThid));
    ret(c, static_cast<u32>(t->wakeups));
    t->wakeups = 0;
}
void imp_thbase_GetSystemTime(Cpu& c) {
    const u64 clk = K(c).now() / 8u;  // the IOP clock: EE cycles / 8
    wr32(c, c.arg(0), static_cast<u32>(clk));
    wr32(c, c.arg(0) + 4, static_cast<u32>(clk >> 32));
    ret(c, 0);
}
void imp_thbase_USec2SysClock(Cpu& c) {
    const u64 clk = static_cast<u64>(c.arg(0)) * 36864ull / 1000ull;
    wr32(c, c.arg(1), static_cast<u32>(clk));
    wr32(c, c.arg(1) + 4, static_cast<u32>(clk >> 32));
    ret(c, 0);
}
void imp_thbase_SysClock2USec(Cpu& c) {
    const u64 clk = static_cast<u64>(rd32(c, c.arg(0))) | (static_cast<u64>(rd32(c, c.arg(0) + 4)) << 32);
    const u64 usec = clk * 1000ull / 36864ull;
    wr32(c, c.arg(1), static_cast<u32>(usec / 1'000'000ull));
    wr32(c, c.arg(2), static_cast<u32>(usec % 1'000'000ull));
    ret(c, 0);
}

// ---- thsemap ------------------------------------------------------------------------------------------------------
void imp_thsemap_CreateSema(Cpu& c) {
    NativeSk& k = K(c);
    const u32 p = c.arg(0);
    NativeSk::Sema s;
    s.id = k.next_sema_id();
    s.attr = rd32(c, p);
    s.option = rd32(c, p + 4);
    s.count = static_cast<int>(rd32(c, p + 8));
    s.max = static_cast<int>(rd32(c, p + 12));
    k.semas()[s.id] = s;
    ret(c, static_cast<u32>(s.id));
}
void imp_thsemap_DeleteSema(Cpu& c) {
    NativeSk& k = K(c);
    const auto it = k.semas().find(static_cast<int>(c.arg(0)));
    if (it == k.semas().end()) return ret(c, static_cast<u32>(kKeIllegalSemid));
    for (int w : it->second.waiters)
        if (NativeSk::Thread* t = k.thread(w)) {
            k.make_ready(*t);
            t->regs[2] = static_cast<u32>(-425);  // KE_WAIT_DELETE
        }
    k.semas().erase(it);
    ret(c, 0);
    k.preempt();
}
void imp_thsemap_SignalSema(Cpu& c) {
    NativeSk& k = K(c);
    k.count_kernel();
    const auto it = k.semas().find(static_cast<int>(c.arg(0)));
    if (it == k.semas().end()) return ret(c, static_cast<u32>(kKeIllegalSemid));
    NativeSk::Sema& s = it->second;
    ret(c, 0);
    while (!s.waiters.empty()) {
        const int w = s.waiters.front();
        s.waiters.pop_front();
        NativeSk::Thread* t = k.thread(w);
        if (t && t->status == NativeSk::Status::Wait && t->wait == NativeSk::Wait::Sema) {
            k.make_ready(*t);
            t->regs[2] = 0;
            k.preempt();
            return;
        }
    }
    ++s.count;
}
void imp_thsemap_WaitSema(Cpu& c) {
    NativeSk& k = K(c);
    k.count_kernel();
    const auto it = k.semas().find(static_cast<int>(c.arg(0)));
    if (it == k.semas().end()) return ret(c, static_cast<u32>(kKeIllegalSemid));
    NativeSk::Sema& s = it->second;
    ret(c, 0);
    if (s.count > 0) {
        --s.count;
        return;
    }
    s.waiters.push_back(k.current_id());
    k.block_current(NativeSk::Wait::Sema, s.id);
}

// ---- timrman ------------------------------------------------------------------------------------------------------
namespace {
NativeSk::Timer* timer(Cpu& c) {
    const auto it = K(c).timers().find(static_cast<int>(c.arg(0)));
    return it == K(c).timers().end() ? nullptr : &it->second;
}
}  // namespace
void imp_timrman_AllocHardTimer(Cpu& c) {
    NativeSk& k = K(c);
    NativeSk::Timer t;
    t.id = k.next_timer_id();
    t.source = c.arg(0);
    t.size = c.arg(1);
    t.prescale = c.arg(2);
    k.timers()[t.id] = t;
    ret(c, static_cast<u32>(t.id));
}
void imp_timrman_FreeHardTimer(Cpu& c) { ret(c, K(c).timers().erase(static_cast<int>(c.arg(0))) ? 0u : static_cast<u32>(kKeError)); }
void imp_timrman_SetTimerHandler(Cpu& c) {
    NativeSk::Timer* t = timer(c);
    if (!t) return ret(c, static_cast<u32>(kKeError));
    t->compare = c.arg(1);
    t->handler = c.arg(2);
    t->common = c.arg(3);
    if (t->running) t->deadline = K(c).now() + static_cast<u64>(t->compare) * 8u;
    ret(c, 0);
}
void imp_timrman_SetupHardTimer(Cpu& c) {
    NativeSk::Timer* t = timer(c);
    if (!t) return ret(c, static_cast<u32>(kKeError));
    t->source = c.arg(1);
    t->mode = c.arg(2);
    t->prescale = c.arg(3);
    ret(c, 0);
}
void imp_timrman_StartHardTimer(Cpu& c) {
    NativeSk::Timer* t = timer(c);
    if (!t) return ret(c, static_cast<u32>(kKeError));
    t->running = true;
    t->start = K(c).now();
    t->deadline = K(c).now() + static_cast<u64>(std::max<u32>(t->compare, 1)) * 8u;
    ret(c, 0);
}
void imp_timrman_StopHardTimer(Cpu& c) {
    NativeSk::Timer* t = timer(c);
    if (!t) return ret(c, static_cast<u32>(kKeError));
    t->running = false;
    ret(c, 0);
}

}  // namespace p3fes::native::sound::sk
