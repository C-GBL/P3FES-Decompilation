#include "host_crash.h"

#include <windows.h>
// dbghelp.h needs windows.h first.
#include <dbghelp.h>

#include <cstdio>
#include <cstring>

#include "host_backtrace.h"

namespace p3fes::app {

namespace {

CrashContextFn g_ctx_fn = nullptr;
void* g_ctx_user = nullptr;
LONG g_entered = 0;

const char* code_name(DWORD c) {
    switch (c) {
    case EXCEPTION_ACCESS_VIOLATION: return "access violation";
    case EXCEPTION_STACK_OVERFLOW: return "stack overflow";
    case EXCEPTION_ILLEGAL_INSTRUCTION: return "illegal instruction";
    case EXCEPTION_INT_DIVIDE_BY_ZERO: return "integer divide by zero";
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "array bounds exceeded";
    case EXCEPTION_IN_PAGE_ERROR: return "in-page error";
    case 0xC0000409: return "stack buffer overrun / fail fast";
    case 0xC0000374: return "heap corruption";
    default: return "exception";
    }
}

// "module+0xRVA [symbol+0xdisp]" for a host address.
void describe(DWORD64 a, char* out, std::size_t n) {
    HMODULE mod = nullptr;
    char path[MAX_PATH] = "?";
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<LPCSTR>(a), &mod) &&
        mod)
        GetModuleFileNameA(mod, path, MAX_PATH);
    const char* base = std::strrchr(path, '\\');
    base = base ? base + 1 : path;
    alignas(SYMBOL_INFO) char buf[sizeof(SYMBOL_INFO) + 512];
    auto* si = reinterpret_cast<SYMBOL_INFO*>(buf);
    std::memset(buf, 0, sizeof buf);
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen = 511;
    DWORD64 disp = 0;
    const auto rva = static_cast<unsigned long long>(a - reinterpret_cast<DWORD64>(mod));
    if (SymFromAddr(GetCurrentProcess(), a, &disp, si))
        std::snprintf(out, n, "%s+0x%llX [%s+0x%llX]", base, rva, si->Name, static_cast<unsigned long long>(disp));
    else
        std::snprintf(out, n, "%s+0x%llX", base, rva);
}

LONG WINAPI on_unhandled(EXCEPTION_POINTERS* ep) {
    if (InterlockedExchange(&g_entered, 1) != 0) return EXCEPTION_CONTINUE_SEARCH;  // a crash inside the report
    std::fflush(stdout);
    const EXCEPTION_RECORD& er = *ep->ExceptionRecord;
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_FAIL_CRITICAL_ERRORS);
    SymInitialize(GetCurrentProcess(), nullptr, TRUE);  // harmless if host_backtrace already did
    char where[768];
    describe(reinterpret_cast<DWORD64>(er.ExceptionAddress), where, sizeof where);
    std::fprintf(stderr, "p3fes: HOST CRASH: %s (0x%08lX) at %s\n", code_name(er.ExceptionCode),
                 static_cast<unsigned long>(er.ExceptionCode), where);
    if (er.ExceptionCode == EXCEPTION_ACCESS_VIOLATION && er.NumberParameters >= 2)
        std::fprintf(stderr, "p3fes:   %s of address 0x%016llX\n",
                     er.ExceptionInformation[0] == 0 ? "read" : er.ExceptionInformation[0] == 1 ? "write" : "execute",
                     static_cast<unsigned long long>(er.ExceptionInformation[1]));
    if (g_ctx_fn) std::fprintf(stderr, "p3fes:   guest: %s\n", g_ctx_fn(g_ctx_user).c_str());

    CONTEXT c = *ep->ContextRecord;
    STACKFRAME64 f{};
    f.AddrPC.Offset = c.Rip;
    f.AddrPC.Mode = AddrModeFlat;
    f.AddrFrame.Offset = c.Rbp;
    f.AddrFrame.Mode = AddrModeFlat;
    f.AddrStack.Offset = c.Rsp;
    f.AddrStack.Mode = AddrModeFlat;
    std::fprintf(stderr, "p3fes:   host stack (innermost first):\n");
    for (int i = 0; i < 48; ++i) {
        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, GetCurrentProcess(), GetCurrentThread(), &f, &c, nullptr,
                         SymFunctionTableAccess64, SymGetModuleBase64, nullptr) ||
            f.AddrPC.Offset == 0)
            break;
        describe(i == 0 ? f.AddrPC.Offset : f.AddrPC.Offset - 1, where, sizeof where);
        std::fprintf(stderr, "p3fes:     #%02d %s\n", i, where);
    }
    const auto bt = guest_backtrace_from_context(ep->ContextRecord, 24);
    if (!bt.empty()) {
        std::fprintf(stderr, "p3fes:   recompiled guest frames (innermost first):\n");
        for (const GuestFrame& g : bt) std::fprintf(stderr, "p3fes:     0x%08X %s\n", g.va, g.host_name.c_str());
    }
    std::fflush(stderr);
    return EXCEPTION_CONTINUE_SEARCH;
}

} // namespace

void install_crash_reporter() { SetUnhandledExceptionFilter(on_unhandled); }

void set_crash_context(CrashContextFn fn, void* user) {
    g_ctx_fn = fn;
    g_ctx_user = user;
}

} // namespace p3fes::app
