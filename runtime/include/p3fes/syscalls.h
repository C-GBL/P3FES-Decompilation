// EE kernel syscall numbers.
//
// Source: the public PS2 EE kernel syscall table (ps2sdk `ee/kernel` and the
// ps2tek documentation). Only entries whose numbering is well established are
// listed. The game invokes these as `addiu $v1, $zero, N; syscall`; negative
// `N` selects the interrupt-safe `i*` variant of the same service on real
// hardware (e.g. -0x33 behaves like iWakeupThread when called from a handler).
//
// PHASE 2 TODO: verify every number against the actual immediates that
// SLUS_216.21 loads into $v1 before `syscall`, and add any entries the game
// uses that are missing here. Do not rely on this table before that pass.
#pragma once

#include "p3fes/ee_types.h"

namespace p3fes {

struct EEContext;

enum class EESyscall : u8 {
    ResetEE                = 0x01,
    SetGsCrt               = 0x02,
    Exit                   = 0x04,
    LoadExecPS2            = 0x06,
    ExecPS2                = 0x07,
    AddIntcHandler         = 0x10,
    RemoveIntcHandler      = 0x11,
    AddDmacHandler         = 0x12,
    RemoveDmacHandler      = 0x13,
    EnableIntc             = 0x14,   // _EnableIntc
    DisableIntc            = 0x15,   // _DisableIntc
    EnableDmac             = 0x16,   // _EnableDmac
    DisableDmac            = 0x17,   // _DisableDmac
    SetAlarm               = 0x18,
    ReleaseAlarm           = 0x19,
    CreateThread           = 0x20,
    DeleteThread           = 0x21,
    StartThread            = 0x22,
    ExitThread             = 0x23,
    ExitDeleteThread       = 0x24,
    TerminateThread        = 0x25,
    ChangeThreadPriority   = 0x29,
    RotateThreadReadyQueue = 0x2B,
    ReleaseWaitThread      = 0x2D,
    GetThreadId            = 0x2F,
    ReferThreadStatus      = 0x30,
    SleepThread            = 0x32,
    WakeupThread           = 0x33,
    iWakeupThread          = 0x34,
    CancelWakeupThread     = 0x35,
    SuspendThread          = 0x37,
    ResumeThread           = 0x39,
    JoinThread             = 0x3B,
    InitMainThread         = 0x3C,   // RFU060 / SetupThread
    InitHeap               = 0x3D,   // RFU061 / SetupHeap
    EndOfHeap              = 0x3E,
    CreateSema             = 0x40,
    DeleteSema             = 0x41,
    SignalSema             = 0x42,
    iSignalSema            = 0x43,
    WaitSema               = 0x44,
    PollSema               = 0x45,
    iPollSema              = 0x46,
    ReferSemaStatus        = 0x47,
    FlushCache             = 0x64,
    GsGetIMR               = 0x70,
    GsPutIMR               = 0x71,
    SetVSyncFlag           = 0x73,
    SetSyscall             = 0x74,
    SifDmaStat             = 0x76,
    SifSetDma              = 0x77,
    SifSetDChain           = 0x78,
    SifSetReg              = 0x79,
    SifGetReg              = 0x7A,
    Deci2Call              = 0x7C,
    MachineType            = 0x7E,
    GetMemorySize          = 0x7F,
};

// Dispatch table indexed by the raw 8-bit syscall number. Handlers receive the
// CPU context (arguments in $a0..$a3 / $t0.., result in $v0 per the EE ABI).
// A null slot means "not implemented"; the runtime decides whether that is
// fatal or merely logged.
struct SyscallTable {
    using Handler = void (*)(EEContext& ctx);

    static constexpr u32 kCount = 0x100;
    Handler handlers[kCount] = {};

    void    set(EESyscall id, Handler h) noexcept { handlers[static_cast<u8>(id)] = h; }
    Handler get(u8 raw) const noexcept { return handlers[raw]; }
};

} // namespace p3fes
