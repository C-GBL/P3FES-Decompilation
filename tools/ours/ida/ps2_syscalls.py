"""PS2 Emotion Engine kernel syscall numbers (EE kernel syscall table, indexed by $v1).

Authority: ps2sdk `ee/kernel/include/syscallnr.h` (`__NR_*` defines), parsed at import time from
`tools/third_party/ps2sdk/` (fetched by tools/fetch_tools.ps1; not vendored). Positive defines give
the kernel table entry; negative defines (`(-0x43)`) record libkernel's convention of invoking the
interrupt-context `i*` variants with a negated number (the kernel and PCSX2's SYSCALL handler
dispatch on the magnitude). Aliases (`#define __NR_X __NR_Y`) are ignored; the first define for a
number wins.

Fallback: a hand-typed table (PCSX2 `syscallNames[]` / ps2tek naming) used only when the header is
unavailable, and otherwise reported in a "differs from ps2sdk" column so naming disagreements are
visible (e.g. 0x3b RFU059 in ps2sdk vs JoinThread in PCSX2; 0x04 KExit vs Exit).

Observed in SLUS_216.21 (docs/ANALYSIS/02_syscalls.md): -0x67/-0x68/-0x6a wrappers sit between
the 0x66 and 0x6b wrappers at 0x503400..0x503420, matching the header's negative defines exactly.
"""
import os, re

HERE = os.path.dirname(os.path.abspath(__file__))
DEFAULT_HEADER = os.path.normpath(os.path.join(HERE, "..", "..", "third_party", "ps2sdk", "ee", "kernel", "include", "syscallnr.h"))

# Fallback / cross-check table: PCSX2 R5900OpcodeImpl.cpp syscallNames[] + ps2tek. 'H' = widely
# cross-verified, 'M' = plausible but rarely exercised.
PCSX2_TABLE = {
    0x00: "RFU000_FullReset", 0x01: "ResetEE", 0x02: "SetGsCrt", 0x03: "RFU003", 0x04: "Exit", 0x05: "RFU005",
    0x06: "LoadExecPS2", 0x07: "ExecPS2", 0x08: "RFU008", 0x09: "RFU009", 0x0A: "AddSbusIntcHandler",
    0x0B: "RemoveSbusIntcHandler", 0x0C: "Interrupt2Iop", 0x0D: "SetVTLBRefillHandler", 0x0E: "SetVCommonHandler",
    0x0F: "SetVInterruptHandler", 0x10: "AddIntcHandler", 0x11: "RemoveIntcHandler", 0x12: "AddDmacHandler",
    0x13: "RemoveDmacHandler", 0x14: "_EnableIntc", 0x15: "_DisableIntc", 0x16: "_EnableDmac", 0x17: "_DisableDmac",
    0x18: "_SetAlarm", 0x19: "_ReleaseAlarm", 0x1A: "_iEnableIntc", 0x1B: "_iDisableIntc", 0x1C: "_iEnableDmac",
    0x1D: "_iDisableDmac", 0x1E: "_iSetAlarm", 0x1F: "_iReleaseAlarm", 0x20: "CreateThread", 0x21: "DeleteThread",
    0x22: "StartThread", 0x23: "ExitThread", 0x24: "ExitDeleteThread", 0x25: "TerminateThread", 0x26: "iTerminateThread",
    0x27: "DisableDispatchThread", 0x28: "EnableDispatchThread", 0x29: "ChangeThreadPriority", 0x2A: "iChangeThreadPriority",
    0x2B: "RotateThreadReadyQueue", 0x2C: "iRotateThreadReadyQueue", 0x2D: "ReleaseWaitThread", 0x2E: "iReleaseWaitThread",
    0x2F: "GetThreadId", 0x30: "ReferThreadStatus", 0x31: "iReferThreadStatus", 0x32: "SleepThread", 0x33: "WakeupThread",
    0x34: "_iWakeupThread", 0x35: "CancelWakeupThread", 0x36: "iCancelWakeupThread", 0x37: "SuspendThread",
    0x38: "_iSuspendThread", 0x39: "ResumeThread", 0x3A: "iResumeThread", 0x3B: "JoinThread", 0x3C: "RFU060_SetupThread",
    0x3D: "RFU061_SetupHeap", 0x3E: "EndOfHeap", 0x3F: "RFU063", 0x40: "CreateSema", 0x41: "DeleteSema", 0x42: "SignalSema",
    0x43: "iSignalSema", 0x44: "WaitSema", 0x45: "PollSema", 0x46: "iPollSema", 0x47: "ReferSemaStatus", 0x48: "iReferSemaStatus",
    0x49: "RFU073_iDeleteSema", 0x4A: "SetOsdConfigParam", 0x4B: "GetOsdConfigParam", 0x4C: "GetGsHParam", 0x4D: "GetGsVParam",
    0x4E: "SetGsHParam", 0x4F: "SetGsVParam", 0x50: "RFU080_CreateEventFlag", 0x51: "RFU081_DeleteEventFlag",
    0x52: "RFU082_SetEventFlag", 0x53: "RFU083_iSetEventFlag", 0x54: "RFU084_ClearEventFlag", 0x55: "RFU085_iClearEventFlag",
    0x56: "RFU086_WaitEventFlag", 0x57: "RFU087_PollEventFlag", 0x58: "RFU088_iPollEventFlag", 0x59: "RFU089_ReferEventFlagStatus",
    0x5A: "RFU090_iReferEventFlagStatus", 0x5B: "RFU091", 0x5C: "EnableIntcHandler", 0x5D: "DisableIntcHandler",
    0x5E: "EnableDmacHandler", 0x5F: "DisableDmacHandler", 0x60: "KSeg0", 0x61: "EnableCache", 0x62: "DisableCache",
    0x63: "GetCop0", 0x64: "FlushCache", 0x65: "RFU105", 0x66: "CpuConfig", 0x67: "iGetCop0", 0x68: "iFlushCache",
    0x69: "RFU109", 0x6A: "iCpuConfig", 0x6B: "sceSifStopDma", 0x6C: "SetCPUTimerHandler", 0x6D: "SetCPUTimer",
    0x6E: "SetOsdConfigParam2", 0x6F: "GetOsdConfigParam2", 0x70: "GsGetIMR", 0x71: "GsPutIMR", 0x72: "SetPgifHandler",
    0x73: "SetVSyncFlag", 0x74: "RFU120_SetSyscall", 0x75: "RFU121__print", 0x76: "sceSifDmaStat", 0x77: "sceSifSetDma",
    0x78: "sceSifSetDChain", 0x79: "sceSifSetReg", 0x7A: "sceSifGetReg", 0x7B: "ExecOSD", 0x7C: "Deci2Call", 0x7D: "PSMode",
    0x7E: "MachineType", 0x7F: "GetMemorySize",
}

_DEF = re.compile(r"^\s*#define\s+__NR_(\w+)\s+(\(?-?\s*(?:0x[0-9a-fA-F]+|\d+)\s*\)?)\s*(?://.*)?$")

def parse_header(path):
    """Return (pos, neg): dicts magnitude -> canonical name from the header's __NR_ defines."""
    pos, neg = {}, {}
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = _DEF.match(line)
            if not m: continue
            name, val = m.group(1), m.group(2).strip("() \t")
            n = int(val.replace(" ", ""), 0)
            tgt = neg if n < 0 else pos
            tgt.setdefault(abs(n), name)  # first define wins; aliases (__NR_X __NR_Y) never match the regex
    return pos, neg

HEADER_PATH = DEFAULT_HEADER if os.path.exists(DEFAULT_HEADER) else None
POS, NEG = parse_header(HEADER_PATH) if HEADER_PATH else ({}, {})
SOURCE = f"ps2sdk syscallnr.h ({HEADER_PATH})" if HEADER_PATH else "fallback PCSX2/ps2tek table (ps2sdk header not found)"

def name_for(num):
    """Return (name, source) for a (possibly negative) $v1 value.

    source: 'ps2sdk' (exact define, sign included), 'ps2sdk+i' (positive define exists, negative form
    inferred as its interrupt-context variant), 'pcsx2' (fallback table), 'unknown'."""
    n = abs(num)
    if num < 0 and n in NEG: return NEG[n], "ps2sdk"
    if n in POS:
        nm = POS[n]
        if num < 0 and not nm.lstrip("_").startswith("i"): return "i" + nm, "ps2sdk+i"
        return nm, "ps2sdk"
    if num > 0 and n in NEG:  # only the negative form is defined by ps2sdk (e.g. -0xfd iSetAlarm); positive use observed
        return f"unknown_syscall_{n:02X}", f"unknown (ps2sdk defines only -{n:#x} = {NEG[n]})"
    if n in PCSX2_TABLE:
        nm = PCSX2_TABLE[n]
        if num < 0 and not nm.lstrip("_").startswith("i"): nm = "i" + nm
        return nm, "pcsx2"
    return f"unknown_syscall_{n:02X}", "unknown"

def pcsx2_name(num):
    n = abs(num); return PCSX2_TABLE.get(n)

if __name__ == "__main__":
    print(SOURCE)
    for n in sorted(set(POS) | set(NEG)):
        print(f"{n:#04x} pos={POS.get(n)} neg={NEG.get(n)} pcsx2={PCSX2_TABLE.get(n)}")
