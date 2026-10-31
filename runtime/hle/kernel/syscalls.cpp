// EE syscall dispatch and the stock-kernel services (docs/ANALYSIS/15 §3-7; RUNTIME_CONTRACT §3).
//
// Dispatch (`15` §7): $v1 < 0 selects the same slot in interrupt form (no reschedule); a positive call
// in the switching set {0x21 0x22 0x25 0x29 0x2B 0x2D 0x33 0x39 0x41 0x42} reschedules at once when its
// result is >= 0; SleepThread / WaitSema block; ExitThread / ExitDeleteThread never return. A positive
// switching/blocking call from inside an interrupt handler is fatal (the real kernel would reuse the
// kernel stack the dispatcher runs on). Precedence per slot: a host SyscallFn (install_syscall) > a
// slot installed by the guest's SetSyscall (README "Installed syscalls") > the stock service.
// After every syscall the kernel runs a check point (ADR-0013 §2).
#include "kernel_core.h"

#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <string>

#include "p3fes_recomp_rt.h"

namespace p3fes::hle {

using namespace kc;

namespace {

constexpr s64 kNoResult = std::numeric_limits<s64>::min();  // void kernel call: $v0 is left as it was

bool is_switching(u32 slot) {
    switch (slot) {
    case 0x21: case 0x22: case 0x25: case 0x29: case 0x2B: case 0x2D: case 0x33: case 0x39: case 0x41: case 0x42:
        return true;
    default:
        return false;
    }
}
bool is_blocking(u32 slot) { return slot == 0x23 || slot == 0x24 || slot == 0x32 || slot == 0x44; }

// Positive calls whose BIOS wrapper starts with `jal kctx_save_on_thread_stack 0x80003680` (the context frame at
// the caller's sp - 0x280, KernelOptions::context_frames). The delay slot sets the frame's $v0: `move v0,a0`
// except ChangeThreadPriority / ExitThread / ExitDeleteThread (nop: $v0 as it was) and SleepThread
// (`move v0,k0` = the current tid) -- BIOS v02.30 0x80002FC0..0x800035C0 (obs).
bool saves_frame(u32 slot) { return is_switching(slot) || is_blocking(slot); }
bool frame_v0_is_a0(u32 slot) { return slot != 0x29 && slot != 0x23 && slot != 0x24 && slot != 0x32; }

// Slots the stock v02.30 kernel leaves undefined (`15` §1): 0x00 0x03 0x08 0x3F 0x54-0x5B, 0x81-0xFF
// (0x7C Deci2Call is intercepted before the table).
bool stock_defined(u32 slot) {
    if (slot == 0x00 || slot == 0x03 || slot == 0x08 || slot == 0x3F) return false;
    if (slot >= 0x54 && slot <= 0x5B) return false;
    return slot <= 0x80;
}

} // namespace

const char* syscall_name(u32 s) {
    switch (s) {
    case 0x00: return "RFU000_FullReset"; case 0x01: return "ResetEE"; case 0x02: return "SetGsCrt";
    case 0x03: return "RFU003"; case 0x04: return "KExit"; case 0x05: return "ResumeIntrDispatch";
    case 0x06: return "LoadExecPS2"; case 0x07: return "ExecPS2"; case 0x08: return "ResumeT3IntrDispatch";
    case 0x09: return "RFU009"; case 0x0A: return "AddSbusIntcHandler"; case 0x0B: return "RemoveSbusIntcHandler";
    case 0x0C: return "Interrupt2Iop"; case 0x0D: return "SetVTLBRefillHandler"; case 0x0E: return "SetVCommonHandler";
    case 0x0F: return "SetVInterruptHandler"; case 0x10: return "AddIntcHandler"; case 0x11: return "RemoveIntcHandler";
    case 0x12: return "AddDmacHandler"; case 0x13: return "RemoveDmacHandler"; case 0x14: return "EnableIntc";
    case 0x15: return "DisableIntc"; case 0x16: return "EnableDmac"; case 0x17: return "DisableDmac";
    case 0x18: return "SetAlarm"; case 0x19: return "ReleaseAlarm"; case 0x1A: return "iEnableIntc";
    case 0x1B: return "iDisableIntc"; case 0x1C: return "iEnableDmac"; case 0x1D: return "iDisableDmac";
    case 0x1E: return "iSetAlarm"; case 0x1F: return "iReleaseAlarm"; case 0x20: return "CreateThread";
    case 0x21: return "DeleteThread"; case 0x22: return "StartThread"; case 0x23: return "ExitThread";
    case 0x24: return "ExitDeleteThread"; case 0x25: return "TerminateThread"; case 0x26: return "iTerminateThread";
    case 0x27: return "DisableDispatchThread"; case 0x28: return "EnableDispatchThread";
    case 0x29: return "ChangeThreadPriority"; case 0x2A: return "iChangeThreadPriority";
    case 0x2B: return "RotateThreadReadyQueue"; case 0x2C: return "iRotateThreadReadyQueue";
    case 0x2D: return "ReleaseWaitThread"; case 0x2E: return "iReleaseWaitThread"; case 0x2F: return "GetThreadId";
    case 0x30: return "ReferThreadStatus"; case 0x31: return "iReferThreadStatus"; case 0x32: return "SleepThread";
    case 0x33: return "WakeupThread"; case 0x34: return "iWakeupThread"; case 0x35: return "CancelWakeupThread";
    case 0x36: return "iCancelWakeupThread"; case 0x37: return "SuspendThread"; case 0x38: return "iSuspendThread";
    case 0x39: return "ResumeThread"; case 0x3A: return "iResumeThread"; case 0x3B: return "RFU059 (JoinThread)";
    case 0x3C: return "SetupThread"; case 0x3D: return "SetupHeap"; case 0x3E: return "EndOfHeap";
    case 0x3F: return "RFU063"; case 0x40: return "CreateSema"; case 0x41: return "DeleteSema";
    case 0x42: return "SignalSema"; case 0x43: return "iSignalSema"; case 0x44: return "WaitSema";
    case 0x45: return "PollSema"; case 0x46: return "iPollSema"; case 0x47: return "ReferSemaStatus";
    case 0x48: return "iReferSemaStatus"; case 0x49: return "iDeleteSema"; case 0x4A: return "SetOsdConfigParam";
    case 0x4B: return "GetOsdConfigParam"; case 0x4C: return "GetGsHParam"; case 0x4D: return "GetGsVParam";
    case 0x4E: return "SetGsHParam"; case 0x4F: return "SetGsVParam"; case 0x50: return "CreateEventFlag";
    case 0x51: return "DeleteEventFlag"; case 0x52: return "SetEventFlag"; case 0x53: return "iSetEventFlag";
    case 0x54: return "xlaunch"; case 0x55: return "PutTLBEntry"; case 0x56: return "SetTLBEntry";
    case 0x57: return "GetTLBEntry"; case 0x58: return "ProbeTLBEntry"; case 0x59: return "ExpandScratchPad";
    case 0x5A: return "Copy"; case 0x5B: return "GetEntryAddress"; case 0x5C: return "EnableIntcHandler";
    case 0x5D: return "DisableIntcHandler"; case 0x5E: return "EnableDmacHandler"; case 0x5F: return "DisableDmacHandler";
    case 0x60: return "KSeg0"; case 0x61: return "EnableCache"; case 0x62: return "DisableCache";
    case 0x63: return "GetCop0"; case 0x64: return "FlushCache"; case 0x66: return "CpuConfig";
    case 0x67: return "iGetCop0"; case 0x68: return "iFlushCache"; case 0x6A: return "iCpuConfig";
    case 0x6B: return "sceSifStopDma"; case 0x6C: return "SetCPUTimerHandler"; case 0x6D: return "SetCPUTimer";
    case 0x6E: return "SetOsdConfigParam2"; case 0x6F: return "GetOsdConfigParam2"; case 0x70: return "GsGetIMR";
    case 0x71: return "GsPutIMR"; case 0x72: return "SetPgifHandler"; case 0x73: return "SetVSyncFlag";
    case 0x74: return "SetSyscall"; case 0x75: return "_print"; case 0x76: return "sceSifDmaStat";
    case 0x77: return "sceSifSetDma"; case 0x78: return "sceSifSetDChain"; case 0x79: return "sceSifSetReg";
    case 0x7A: return "sceSifGetReg"; case 0x7B: return "ExecOSD"; case 0x7C: return "Deci2Call";
    case 0x7D: return "PSMode"; case 0x7E: return "MachineType"; case 0x7F: return "GetMemorySize";
    case 0x80: return "_GetGsDxDyOffset"; case 0x82: return "_InitTLB"; case 0x83: return "FindAddress";
    case 0xFC: return "SetAlarm (patch)"; case 0xFD: return "iSetAlarm (patch)"; case 0xFE: return "ReleaseAlarm (patch)";
    case 0xFF: return "iReleaseAlarm (patch)";
    default: return "undefined";
    }
}

GuestFn KernelHooks::lookup(u32 va) const { return opts_.lookup ? opts_.lookup(va) : rt::lookup_func(va); }

// ---- dispatch ----------------------------------------------------------------------------------------

// Layer 6 (--native kernel): the game's libkernel stub calls the kernel directly instead of executing `syscall`. The
// service is the instruction's, so the result, the scheduling and the closing check point are the same; what the layer
// changes is the context model (KernelOptions::context_frames off: no BIOS frames in guest stacks), not this path.
void KernelHooks::direct_call(EEContext& ctx, u32 pc) {
    if (census_) ++census_->direct_calls;
    syscall(ctx, pc);
}

void KernelHooks::syscall(EEContext& ctx, u32 pc) {
    (void)ctx;  // always ctx_ (one CPU)
    const std::uint8_t prof_zone = prof::enter(prof::Zone::Kernel);  // explicit pair: the call may switch fibers (L3)
    ctx_.pc = pc;
    if (!started_) die("syscall at 0x%08X before Kernel::start", pc);
    const s32 num = static_cast<s32>(ctx_.gpr[GPR_V1].u32[0]);
    const bool neg = num < 0;
    const s64 mag = neg ? -static_cast<s64>(num) : static_cast<s64>(num);
    if (mag > 0xFF) die("syscall %d ($v1 0x%08X): number out of range", num, static_cast<u32>(num));
    const u32 slot = static_cast<u32>(mag);
    if (census_) {
        ++(neg ? census_->isyscalls : census_->syscalls)[slot];
        ++census_->syscall_sites[(static_cast<u64>(neg) << 40) | (static_cast<u64>(slot) << 32) | ctx_.gpr[GPR_RA].u32[0]];
    }
    ctx_.cycles += opts_.syscall_cycles;
    if (!neg && no_deliver_depth_ > 0) {
        if (is_switching(slot) || is_blocking(slot))
            die("positive syscall 0x%02X (%s) inside an interrupt handler: only the i* (negative) forms are legal there (`15` §7)",
                slot, syscall_name(slot));
        ++positive_in_handler_;
    }
    if (neg && is_blocking(slot))
        die("syscall -0x%02X (%s) has no interrupt form", slot, syscall_name(slot));

    if (host_syscalls_[slot]) {
        ctx_.gpr[GPR_V0].u64[0] = host_syscalls_[slot](ctx_, num);
        run_services();  // the call may have created device work with a deadline (SIF/IOP)
    } else {
        bool blocked = false;
        bool handled = false;
        s64 r = 0;
        u32 frame = 0;
        u64 frame_v0 = 0;
        // The BIOS wrapper of the switching / blocking calls saves the context (at sp - 0x280 with context frames;
        // without them -- layer 6, --native kernel -- only on the host) and its result rules apply either way.
        const bool wrapper = !neg && saves_frame(slot) && current_ != kIdleTid;
        if (wrapper) {
            u128 v0 = ctx_.gpr[GPR_V0];
            if (slot == 0x32) v0.u64[0] = static_cast<u64>(static_cast<s64>(current_));
            else if (frame_v0_is_a0(slot)) v0.u64[0] = ctx_.gpr[GPR_A0].u64[0];
            frame_v0 = v0.u64[0];
            if (opts_.context_frames) frame = frame_save(current_, ctx_, v0);
        }
        if (guest_installed_[slot]) r = installed_syscall(slot, handled);
        if (!handled) r = stock_syscall(slot, neg, blocked);
        if (wrapper && (frame || !opts_.context_frames) && !blocked) {
            // The wrapper's result path: ChangeThreadPriority and SleepThread `sd v0,32(frame)` always, the other
            // switching calls on failure; a successful switching call or WaitSema resumes from the frame's $v0.
            if (slot == 0x29 || slot == 0x32 || (is_switching(slot) && r < 0)) {
                if (frame) mem_.write<u64>(frame + 32u, static_cast<u64>(r));
            } else if (is_switching(slot) || slot == 0x44) {
                r = static_cast<s64>(frame_v0);
            }
        }
        if (!blocked && r != kNoResult) set_gpr(ctx_, GPR_V0, r);
        if (!neg && !blocked && is_switching(slot) && r >= 0) reschedule();
    }
    if (ctx_.cycles >= next_deadline_) slow_check(ctx_);  // syscalls are check points
    prof::leave(prof_zone);
}

bool KernelHooks::install_syscall(int number, SyscallFn fn) {
    const int slot = number < 0 ? -number : number;
    if (slot > 0xFF || !fn) return false;
    SyscallFn& s = host_syscalls_[static_cast<unsigned>(slot)];
    if (s) return false;
    s = std::move(fn);
    return true;
}

// Execute a game-installed handler inside the recompiled code band as the kernel would: kernel stack,
// interrupts off, arguments as the caller left them, result in $v0. Only $sp/$ra/$at are restored.
void KernelHooks::call_kernel_mode(u32 addr) {
    const u128 sp = ctx_.gpr[GPR_SP], ra = ctx_.gpr[GPR_RA], at = ctx_.gpr[GPR_AT];
    const u32 pc = ctx_.pc;
    set_gpr(ctx_, GPR_SP, static_cast<s32>(kKernelStackVa));
    set_gpr(ctx_, GPR_RA, 0);
    ctx_.pc = addr;
    ++no_deliver_depth_;
    const std::uint8_t prof_zone = prof::enter(prof::Zone::Ee);
    lookup(addr)(ctx_);
    prof::leave(prof_zone);
    --no_deliver_depth_;
    ctx_.gpr[GPR_SP] = sp;
    ctx_.gpr[GPR_RA] = ra;
    ctx_.gpr[GPR_AT] = at;
    ctx_.pc = pc;
}

s64 KernelHooks::installed_syscall(u32 slot, bool& handled) {
    const u32 a = guest_table_[slot];
    handled = true;
    if (slot == 0x5B && (a == 0x80075000u || a == 0x80076000u)) {
        // The TLB / alarm patch payloads' GetEntryAddress (obs: ELF 0x77F568 / 0x7803A0, copied to these
        // kseg0 addresses by Copy): a 6-entry {id, address} lookup at payload + 0x300 / + 0x710, 0 if absent.
        const u32 table = a == 0x80075000u ? 0x80075300u : 0x80076710u;
        const u32 id = gpr32(GPR_A0);
        for (u32 i = 0; i < 6; ++i)
            if (mem_.read<u32>(table + 8u * i) == id) return static_cast<s32>(mem_.read<u32>(table + 8u * i + 4u));
        return 0;
    }
    if ((slot >= 0x54 && slot <= 0x59) || slot == 0x08 || slot >= 0xFC)
        die("syscall 0x%02X (%s) called; installed by SetSyscall(0x%02X, 0x%08X) but never executed on the analysed paths (H-19/H-20, K-44/K-48)",
            slot, syscall_name(slot), slot, a);
    if (stock_defined(slot))
        die("syscall 0x%02X (%s): the stock handler was replaced by SetSyscall(0x%02X, 0x%08X); not modelled", slot,
            syscall_name(slot), slot, a);
    if (in_code_band(a)) {  // libkernel's kCopy* / kFindAddress: recompiled game code, run in kernel mode
        call_kernel_mode(a);
        return static_cast<s64>(ctx_.gpr[GPR_V0].u64[0]);
    }
    die("syscall 0x%02X (%s) installed at 0x%08X (outside the recompiled code band): not modelled", slot,
        syscall_name(slot), a);
}

void KernelHooks::write_args_block(u32 args) {
    // `15` §3 kthread_copy_args: {argc, argv[16], strings}.
    const std::size_t argc = std::min<std::size_t>(opts_.argv.size(), 16);
    mem_.write<u32>(args, static_cast<u32>(argc));
    u32 str = args + 4u + 16u * 4u;
    for (std::size_t i = 0; i < 16; ++i) {
        if (i < argc) {
            mem_.write<u32>(args + 4u + 4u * static_cast<u32>(i), str);
            const std::string& s = opts_.argv[i];
            for (char ch : s) mem_.write<u8>(str++, static_cast<u8>(ch));
            mem_.write<u8>(str++, 0);
        } else {
            mem_.write<u32>(args + 4u + 4u * static_cast<u32>(i), 0u);
        }
    }
}

// ---- stock services ----------------------------------------------------------------------------------

s64 KernelHooks::stock_syscall(u32 slot, bool neg, bool& blocked) {
    const u32 a0 = gpr32(GPR_A0), a1 = gpr32(GPR_A1), a2 = gpr32(GPR_A2), a3 = gpr32(GPR_A3), t0 = gpr32(GPR_T0);
    const s32 s0 = static_cast<s32>(a0), s1 = static_cast<s32>(a1), s2 = static_cast<s32>(a2);
    switch (slot) {
    // -- GS / CRT -------------------------------------------------------------------------------------
    case 0x02:  // SetGsCrt(interlace, mode, ffmd): record (K-02; `15` §6)
        gs_crt_ = {true, a0, (a1 == 0 || a1 == 1) ? 2u : a1, a2};
        return kNoResult;
    case 0x70:  // GsGetIMR: the cached copy, never the register (H-21)
        return static_cast<s64>(gs_imr_);
    case 0x71:  // GsPutIMR(imr): register (through the bus) + cache
        gs_imr_ = ctx_.gpr[GPR_A0].u64[0];
        write64(kGsImrPa, gs_imr_);
        return static_cast<s64>(gs_imr_);
    case 0x73:  // SetVSyncFlag(&flag, &csr): one-shot, serviced at the next VBLANK_START (H-06)
        vsync_flag_ptr_ = a0;
        vsync_csr_ptr_ = a1;
        return kNoResult;
    case 0x80:  // _GetGsDxDyOffset(mode, &dx1, &dy1, &dx2, &dy2) (H-23)
        if (!opts_.gs_early_model) die("_GetGsDxDyOffset: only the early-model (GS revision < 0x19) answer is modelled");
        for (u32 p : {a1, a2, a3, t0})
            if (p) mem_.write<u32>(p, 0u);
        return kNoResult;

    // -- handler lists / masks ------------------------------------------------------------------------
    case 0x10:  // AddIntcHandler(cause, handler, next, arg)
        if (s0 < 0 || s0 >= kIntcLists || s0 == 1) return -1;
        return add_handler(s0, a1, s2, a3, gpr32(GPR_GP));
    case 0x11:  // RemoveIntcHandler(cause, id)
        if (s0 < 0 || s0 >= kIntcLists) return -1;
        return remove_handler(s0, s1);
    case 0x12:  // AddDmacHandler(channel, handler, next, arg)
        if (s0 < 0 || s0 >= kDmacLists) return -1;
        return add_handler(kIntcLists + s0, a1, s2, a3, gpr32(GPR_GP));
    case 0x13:
        if (s0 < 0 || s0 >= kDmacLists) return -1;
        return remove_handler(kIntcLists + s0, s1);
    case 0x14: case 0x1A: return sc_enable_intc(s0, true);
    case 0x15: case 0x1B: return sc_enable_intc(s0, false);
    case 0x16: case 0x1C: return sc_enable_dmac(s0, true);
    case 0x17: case 0x1D: return sc_enable_dmac(s0, false);
    case 0x5C: return sc_handler_mode(false, s1, 2);
    case 0x5D: return sc_handler_mode(false, s1, 1);
    case 0x5E: return sc_handler_mode(true, s1, 2);
    case 0x5F: return sc_handler_mode(true, s1, 1);

    // -- threads --------------------------------------------------------------------------------------
    case 0x20: return sc_create_thread(a0);
    case 0x21: return sc_delete_thread(s0);
    case 0x22: return sc_start_thread(s0, a1);
    case 0x23: exit_current(false);
    case 0x24: exit_current(true);
    case 0x25: case 0x26: return sc_terminate_thread(s0);
    case 0x27: case 0x28:  // Disable/EnableDispatchThread: "not supported in this version" (`15` §3)
        log("%s: not supported in this version (returns the current tid)", syscall_name(slot));
        return current_;
    case 0x29: case 0x2A: return sc_change_priority(s0, s1);
    case 0x2B: case 0x2C: return sc_rotate(s0, neg || slot == 0x2C);
    case 0x2D: case 0x2E: return sc_release_wait(s0);
    case 0x2F: return current_;
    case 0x30: case 0x31: return sc_refer_thread(s0, a1);
    case 0x32: return sc_sleep(blocked);
    case 0x33: case 0x34: return sc_wakeup(s0);
    case 0x35: case 0x36: return sc_cancel_wakeup(s0);
    case 0x37: case 0x38: return sc_suspend(s0);
    case 0x39: case 0x3A: return sc_resume(s0);
    case 0x3C: return sc_setup_thread();
    case 0x3D: return sc_setup_heap(a0, s1);
    case 0x3E: return static_cast<s32>(tcbs_[static_cast<unsigned>(current_)].heap_end);

    // -- semaphores -----------------------------------------------------------------------------------
    case 0x40: return sc_create_sema(a0);
    case 0x41: return sc_delete_sema(s0);
    case 0x49:
        if (!neg) break;  // positive 0x49 (unknown_syscall_49): group C, K-42
        return sc_delete_sema(s0);
    case 0x42: case 0x43: return sc_signal_sema(s0);
    case 0x44: return sc_wait_sema(s0, blocked);
    case 0x45: case 0x46: return sc_poll_sema(s0);
    case 0x47: case 0x48: return sc_refer_sema(s0, a1);

    // -- kernel patching ------------------------------------------------------------------------------
    case 0x74: return sc_set_syscall(s0, a1);

    // -- configuration / misc (K-12, K-20..K-30) -------------------------------------------------------
    case 0x4A: osd_param_ = mem_.read<u32>(a0); return kNoResult;  // verbatim 32-bit word (H-22)
    case 0x4B: mem_.write<u32>(a0, osd_param_); return kNoResult;
    case 0x4C: case 0x4D: case 0x4E: case 0x4F: return 0;  // Get/SetGsH/VParam: no callers (K-24)
    case 0x60: case 0x61: case 0x62: return 0;                // KSeg0 / EnableCache / DisableCache (K-22)
    case 0x63: case 0x67: return static_cast<s32>(ctx_.cop0[a0 & 31u]);  // GetCop0 (K-21)
    case 0x64: case 0x68: return kNoResult;                   // FlushCache: host memory is coherent (H-25)
    case 0x66: case 0x6A: return 0;                           // CpuConfig (K-21)
    case 0x6B: return 0;                                      // sceSifStopDma: accept (K-29)
    case 0x6E: case 0x6F: return 0;                           // Set/GetOsdConfigParam2 (K-25)
    case 0x75: {                                              // _print(fmt, ...): log the format text (K-20)
        std::string s;
        for (u32 p = a0; s.size() < 1024; ++p) {
            const u8 c = mem_.read<u8>(p);
            if (!c) break;
            s.push_back(static_cast<char>(c));
        }
        log("_print: %s", s.c_str());
        return kNoResult;
    }
    case 0x7C: return 0;  // Deci2Call: no DECI2 host (K-30); the SIF module may install its own
    case 0x7D: machine_type_ |= 0x8000u; return kNoResult;  // PSMode (H-24)
    case 0x7E: return static_cast<s32>(machine_type_);
    case 0x7F: return static_cast<s32>(opts_.memory_size);

    // -- SIF: owned by runtime/hle/sif (install_syscall) ------------------------------------------------
    case 0x76: case 0x77: case 0x78: case 0x79: case 0x7A:
        die("syscall %s0x%02X (%s): the SIF module has not installed it", neg ? "-" : "", slot, syscall_name(slot));

    // -- stock alarms (K-48 counterpart in the stock table) --------------------------------------------
    case 0x18: case 0x19: case 0x1E: case 0x1F:
        die("syscall 0x%02X (%s): stock kernel alarms are not modelled (no caller found; libkernel uses T2)", slot,
            syscall_name(slot));
    default: break;
    }
    // Group C, never-installed slots and undefined numbers (H-19; RUNTIME_CONTRACT §3.3).
    if (!stock_defined(slot))
        die("syscall %s0x%02X (%s): slot never installed (the stock kernel prints \"# Syscall: undefined\" and corrupts its trampoline pointer)",
            neg ? "-" : "", slot, syscall_name(slot));
    die("syscall %s0x%02X (%s): group C / not modelled (no live caller in the analysis; a hit means a missed path)",
        neg ? "-" : "", slot, syscall_name(slot));
}

// ---- INTC / DMAC masks and handler modes ----------------------------------------------------------

s64 KernelHooks::sc_enable_intc(s32 cause, bool enable) {
    if (cause < 0 || cause >= kIntcLists) return -1;  // inf
    const u32 bit = 1u << static_cast<unsigned>(cause);
    const bool set = (intc_mask_ & bit) != 0;
    if (set == enable) return 0;  // H-07: 1 only when the bit changed
    set_intc_mask(enable ? (intc_mask_ | bit) : (intc_mask_ & ~bit));
    return 1;
}

s64 KernelHooks::sc_enable_dmac(s32 ch, bool enable) {
    if (ch < 0 || ch >= kDmacLists) return -1;  // inf
    const u32 bit = 1u << (16u + static_cast<unsigned>(ch));
    const bool set = (d_stat_ & bit) != 0;
    if (set == enable) return 0;
    d_stat_ ^= bit;
    force_check();
    return 1;
}

s64 KernelHooks::sc_handler_mode(bool dmac, s32 id, u32 mode) {
    if (id < 1 || id > kNodeIds)
        die("%s%sHandler(id %d): the kernel writes the node without validation; out-of-range id", mode == 2 ? "Enable" : "Disable",
            dmac ? "Dmac" : "Intc", id);
    nodes_[static_cast<unsigned>(id)].mode = mode;
    return 0;  // inf
}

// ---- threads -----------------------------------------------------------------------------------------

s64 KernelHooks::sc_create_thread(u32 p) {
    if (tcb_free_.empty()) return -1;
    const Tcb& creator = tcbs_[static_cast<unsigned>(current_)];
    const u32 root = creator.root, heap_end = creator.heap_end;
    const int tid = tcb_free_.front();
    tcb_free_.pop_front();
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (census_) ++census_->thread_creates;
    t = Tcb{};
    t.status = TStatus::Dormant;
    t.entry = mem_.read<u32>(p + 4u);
    t.stack = mem_.read<u32>(p + 8u);
    t.stack_size = mem_.read<u32>(p + 0xCu);
    t.gp = mem_.read<u32>(p + 0x10u);
    t.init_prio = t.cur_prio = static_cast<s32>(mem_.read<u32>(p + 0x14u));  // not range-checked (`15` §3)
    t.attr = mem_.read<u32>(p + 0x1Cu);
    t.option = mem_.read<u32>(p + 0x20u);
    t.root = root;          // ra = creator's root_func
    t.heap_end = heap_end;  // heap end inherited (H-14)
    build_initial_ctx(tid);
    if (opts_.context_frames) frame_init(tid);
    return tid;
}

s64 KernelHooks::sc_start_thread(s32 tid, u32 arg) {
    if (tid < 1 || tid >= kMaxThreads || tid == current_) return -1;
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (t.status != TStatus::Dormant) return -1;
    t.arg = arg;
    if (census_) ++census_->thread_starts;
    build_initial_ctx(tid);
    if (opts_.context_frames && t.frame) {
        mem_.write<u32>(t.frame + 64u, arg);  // iStartThread 0x80003FD4: `sw a1, 64(frame)` ($a0 of the new thread)
        t.start_from_frame = true;            // the registers come from the frame at the first activation
    } else if (!opts_.context_frames) {
        t.start_from_frame = true;  // layer 6: the same registers, loaded on the host (activate)
    }
    ready_insert(tid);
    return tid;
}

s64 KernelHooks::sc_terminate_thread(s32 tid) {
    if (tid < 1 || !valid_tid(tid)) return -1;
    if (tid == current_) {
        need_resched_ = true;
        return -1;
    }
    if (tcbs_[static_cast<unsigned>(tid)].status == TStatus::Dormant) return -1;
    reset_dormant(tid);
    return tid;
}

s64 KernelHooks::sc_delete_thread(s32 tid) {
    if (tid < 1 || !valid_tid(tid) || tid == current_) return -1;
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (t.status != TStatus::Dormant) return -1;
    t.status = TStatus::Free;
    tcb_free_.push_back(tid);
    return tid;
}

s64 KernelHooks::sc_change_priority(s32 tid, s32 prio) {
    if (tid == 0 && current_ == kIdleTid) die("ChangeThreadPriority(0 = self) from the idle thread");
    const s32 t = tid == 0 ? current_ : tid;
    if (!valid_tid(t) || t == kIdleTid || prio < 0 || prio > 127) return -1;
    Tcb& x = tcbs_[static_cast<unsigned>(t)];
    if (x.status == TStatus::Dormant) return -1;
    const s64 old = x.cur_prio;
    if (x.status == TStatus::Ready || x.status == TStatus::Run) {
        q_remove(t);
        x.cur_prio = prio;
        if (x.status == TStatus::Run) q_push_tail(t);  // stays RUN; a same-priority peer is now ahead (yield)
        else ready_insert(t);
    } else {
        x.cur_prio = prio;
    }
    return old;
}

s64 KernelHooks::sc_rotate(s32 prio, bool neg) {
    (void)neg;  // neither form sets the resched flag (`15` §3); the positive form picks in the dispatcher
    if (prio < 0 || prio > 127) return -1;
    const unsigned p = static_cast<unsigned>(prio);
    const int h = q_head_[p];
    if (h >= 0 && h != q_tail_[p]) {
        q_remove(h);
        q_push_tail(h);
    }
    return prio;
}

s64 KernelHooks::sc_release_wait(s32 tid) {
    if (tid < 1 || !valid_tid(tid)) return -1;
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (t.status == TStatus::Wait) {
        sema_drop_waiter(tid);
        ready_insert(tid);  // wait type stays set: the released call returns -1 when picked
    } else if (t.status == TStatus::WaitSuspend) {
        sema_drop_waiter(tid);
        t.status = TStatus::Suspend;
    } else {
        return -1;
    }
    return tid;
}

s64 KernelHooks::sc_refer_thread(s32 tid, u32 info) {
    const s32 t = tid == 0 ? current_ : tid;
    if (!valid_tid(t) || t == kIdleTid) return -1;
    const Tcb& x = tcbs_[static_cast<unsigned>(t)];
    const u32 status = static_cast<u32>(x.status);
    if (info) {
        // {status, PC, stack, stack_size, gp, init_prio, cur_prio, attr, option, waitType, waitId, wakeupCount}
        // inf: the kernel reports the resume PC (+0xC); the HLE reports the entry address.
        const u32 w[12] = {status, x.entry, x.stack, x.stack_size, x.gp, static_cast<u32>(x.init_prio),
                           static_cast<u32>(x.cur_prio), x.attr, x.option, x.wait_type, x.wait_id, x.wakeup_count};
        for (u32 i = 0; i < 12; ++i) mem_.write<u32>(info + 4u * i, w[i]);
    }
    return status;
}

s64 KernelHooks::sc_sleep(bool& blocked) {
    if (current_ == kIdleTid) die("SleepThread from the idle thread");
    Tcb& t = tcbs_[static_cast<unsigned>(current_)];
    if (t.wakeup_count > 0) {  // a pending wakeup is consumed (H-11)
        --t.wakeup_count;
        return current_;
    }
    blocked = true;
    block(kWaitSleep, 0, current_);
    return 0;
}

s64 KernelHooks::sc_wakeup(s32 tid) {
    const s32 t = tid == 0 ? current_ : tid;
    if (!valid_tid(t) || t == kIdleTid) return -1;
    if (t == current_) return -1;  // waking the RUN thread: -1 and nothing recorded (H-11)
    Tcb& x = tcbs_[static_cast<unsigned>(t)];
    switch (x.status) {
    case TStatus::Wait:
        if (x.wait_type == kWaitSleep) {
            x.wait_type = kWaitNone;
            ready_insert(t);
        } else {
            ++x.wakeup_count;
        }
        break;
    case TStatus::WaitSuspend:
        if (x.wait_type == kWaitSleep) {
            x.wait_type = kWaitNone;
            x.status = TStatus::Suspend;
        } else {
            ++x.wakeup_count;
        }
        break;
    case TStatus::Ready:
    case TStatus::Suspend: ++x.wakeup_count; break;  // unbounded
    default: return -1;
    }
    return t;
}

s64 KernelHooks::sc_cancel_wakeup(s32 tid) {
    const s32 t = tid == 0 ? current_ : tid;
    if (!valid_tid(t) || t == kIdleTid) return -1;
    Tcb& x = tcbs_[static_cast<unsigned>(t)];
    const s64 r = x.wakeup_count;
    x.wakeup_count = 0;
    return r;
}

s64 KernelHooks::sc_suspend(s32 tid) {
    if (tid < 1 || !valid_tid(tid)) return -1;
    if (tid == current_)
        die("SuspendThread(self, tid %d): the kernel does not reschedule and would leave the thread running unqueued (H-17)",
            tid);
    Tcb& x = tcbs_[static_cast<unsigned>(tid)];
    if (x.status == TStatus::Ready) {
        q_remove(tid);
        x.status = TStatus::Suspend;
    } else if (x.status == TStatus::Wait) {
        x.status = TStatus::WaitSuspend;
    } else {
        return -1;
    }
    return tid;
}

s64 KernelHooks::sc_resume(s32 tid) {
    if (tid < 1 || !valid_tid(tid) || tid == current_) return -1;
    Tcb& x = tcbs_[static_cast<unsigned>(tid)];
    if (x.status == TStatus::Suspend) ready_insert(tid);
    else if (x.status == TStatus::WaitSuspend) x.status = TStatus::Wait;
    else return -1;
    return tid;
}

s64 KernelHooks::sc_setup_thread() {
    // SetupThread(gp, stack, stack_size, args, root_func) (`15` §3, H-13)
    Tcb& t = tcbs_[static_cast<unsigned>(current_)];
    const u32 size = gpr32(GPR_A2);
    s64 stack = static_cast<s32>(gpr32(GPR_A1));
    if (stack == -1) stack = static_cast<s64>(opts_.memory_size) - 0x1000 - size;
    t.gp = gpr32(GPR_A0);
    t.stack = static_cast<u32>(stack);
    t.stack_size = size;
    t.root = gpr32(GPR_T0);
    frame_init(current_);  // SetupThread 0x800051FC
    // The returned sp IS this frame: its four words lie in the main thread's live stack (crt0 runs on from there), so
    // they are written with or without context frames. Without them (layer 6) the TCB keeps no frame.
    if (!opts_.context_frames) t.frame = 0;
    if (const u32 args = gpr32(GPR_A3)) write_args_block(args);
    return static_cast<s32>(t.stack + size - 0x2A0u);
}

s64 KernelHooks::sc_setup_heap(u32 start, s32 size) {
    Tcb& t = tcbs_[static_cast<unsigned>(current_)];
    t.heap_end = size >= 0 ? start + static_cast<u32>(size) : t.stack;  // size < 0 -> the stack base (H-14)
    return static_cast<s32>(t.heap_end);
}

// ---- semaphores (H-16) ---------------------------------------------------------------------------------

s64 KernelHooks::sc_create_sema(u32 p) {
    const s32 init = static_cast<s32>(mem_.read<u32>(p + 8u));
    if (sema_free_.empty() || init < 0) return -1;
    const int id = sema_free_.front();
    sema_free_.pop_front();
    Sema& s = semas_[static_cast<unsigned>(id)];
    s = Sema{};
    s.used = true;
    s.count = init;
    s.init = init;
    s.max = static_cast<s32>(mem_.read<u32>(p + 4u));  // recorded, never enforced
    s.attr = mem_.read<u32>(p + 0x10u);
    s.option = mem_.read<u32>(p + 0x14u);
    if (census_) {
        KernelCensus::SemaUse& u = census_->semas[id];
        if (!u.creates++) u.creator = gpr32(GPR_RA);
        u.init = init;
        u.max = s.max;
    }
    return id;
}

s64 KernelHooks::sc_delete_sema(s32 id) {
    if (!sema_valid(id)) return -1;
    if (census_) ++census_->semas[id].deletes;
    Sema& s = semas_[static_cast<unsigned>(id)];
    for (int w : s.waiters) {  // released in FIFO order; their WaitSema returns -1
        Tcb& x = tcbs_[static_cast<unsigned>(w)];
        if (x.status == TStatus::Wait) ready_insert(w);
        else if (x.status == TStatus::WaitSuspend) x.status = TStatus::Suspend;
    }
    s.waiters.clear();
    s.count = -1;
    s.used = false;
    sema_free_.push_front(id);  // LIFO free list (iDeleteSema 0x80004B7C pushes the head CreateSema pops)
    return id;
}

s64 KernelHooks::sc_signal_sema(s32 id) {
    if (!sema_valid(id)) return -1;
    if (census_) ++(no_deliver_depth_ ? census_->semas[id].isignals : census_->semas[id].signals);
    Sema& s = semas_[static_cast<unsigned>(id)];
    if (!s.waiters.empty()) {  // the unit goes to the first waiter; count unchanged
        const int w = s.waiters.front();
        s.waiters.pop_front();
        Tcb& x = tcbs_[static_cast<unsigned>(w)];
        x.wait_type = kWaitNone;
        x.wait_id = 0;
        if (x.status == TStatus::Wait) ready_insert(w);
        else if (x.status == TStatus::WaitSuspend) x.status = TStatus::Suspend;
    } else {
        ++s.count;  // no clamp to max
    }
    return id;
}

s64 KernelHooks::sc_wait_sema(s32 id, bool& blocked) {
    if (!sema_valid(id)) return -1;
    if (census_) {
        ++census_->semas[id].waits;
        if (semas_[static_cast<unsigned>(id)].count <= 0) ++census_->semas[id].blocked;
    }
    Sema& s = semas_[static_cast<unsigned>(id)];
    if (s.count > 0) {
        --s.count;
        return id;
    }
    if (current_ == kIdleTid) die("WaitSema from the idle thread");
    s.waiters.push_back(current_);
    blocked = true;
    block(kWaitSema, static_cast<u32>(id), id);
    return 0;
}

s64 KernelHooks::sc_poll_sema(s32 id) {
    if (!sema_valid(id)) return -1;
    if (census_) ++census_->semas[id].polls;
    Sema& s = semas_[static_cast<unsigned>(id)];
    if (s.count > 0) {
        --s.count;
        return id;
    }
    return -1;
}

s64 KernelHooks::sc_refer_sema(s32 id, u32 info) {
    if (!sema_valid(id)) return -1;
    const Sema& s = semas_[static_cast<unsigned>(id)];
    if (info) {  // {count, max, (init: untouched), wait_threads, attr, option}
        mem_.write<u32>(info + 0x0u, static_cast<u32>(s.count));
        mem_.write<u32>(info + 0x4u, static_cast<u32>(s.max));
        mem_.write<u32>(info + 0xCu, static_cast<u32>(s.waiters.size()));
        mem_.write<u32>(info + 0x10u, s.attr);
        mem_.write<u32>(info + 0x14u, s.option);
    }
    return id;
}

// ---- SetSyscall (H-18) ----------------------------------------------------------------------------------

s64 KernelHooks::sc_set_syscall(s32 n, u32 addr) {
    if (n >= 0 && n < 256) {
        guest_table_[static_cast<unsigned>(n)] = addr;
        guest_installed_[static_cast<unsigned>(n)] = true;
    } else {
        kernel_patches_.emplace_back(n, addr);  // kernel data (0x12C) or kernel code (negative n)
        if (n == 0x12C) cause12_dispatcher_ = addr;  // ksyscall_table + 0x4B0 = kintc_cause_dispatch_tbl[12]
    }
    if (opts_.mirror_syscall_table) {
        const u32 va = kSyscallTableVa + 4u * static_cast<u32>(n);
        if (mem_.resolve(va, 4)) mem_.write<u32>(va, addr);
    }
    return kNoResult;  // no return value
}

} // namespace p3fes::hle
