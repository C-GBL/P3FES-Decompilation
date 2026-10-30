#include "host_backtrace.h"

#include <windows.h>
// dbghelp.h needs windows.h first.
#include <dbghelp.h>

#include <cstdlib>
#include <cstring>

namespace p3fes::app {

namespace {

bool g_sym_ready = false;
bool g_sym_tried = false;

bool ensure_symbols() {
    if (!g_sym_tried) {
        g_sym_tried = true;
        SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_FAIL_CRITICAL_ERRORS);
        g_sym_ready = SymInitialize(GetCurrentProcess(), nullptr, TRUE) != FALSE;
    }
    return g_sym_ready;
}

bool is_hex8(const char* p) {
    for (int i = 0; i < 8; ++i)
        if (!((p[i] >= '0' && p[i] <= '9') || (p[i] >= 'a' && p[i] <= 'f'))) return false;
    return true;
}

// fn_<name>_<addr8>, fn_<name>_<addr8>_entry, fn_<name>_<addr8>_at_<pc8> -> the entry VA.
bool parse_generated(const char* sym, std::uint32_t& va) {
    const char* p = std::strstr(sym, "recomp_gen::fn_");
    if (!p) return false;
    p += std::strlen("recomp_gen::");
    std::string s(p);
    if (const auto at = s.rfind("_at_"); at != std::string::npos && s.size() >= at + 12 && is_hex8(s.c_str() + at + 4)) {
        va = static_cast<std::uint32_t>(std::strtoul(s.substr(at + 4, 8).c_str(), nullptr, 16));
        return true;
    }
    if (s.size() > 6 && s.compare(s.size() - 6, 6, "_entry") == 0) s.resize(s.size() - 6);
    if (s.size() < 9 || s[s.size() - 9] != '_' || !is_hex8(s.c_str() + s.size() - 8)) return false;
    va = static_cast<std::uint32_t>(std::strtoul(s.c_str() + s.size() - 8, nullptr, 16));
    return true;
}

// Adds the recompiled function containing return address `ret` (if any) to `out`.
void add_frame(std::vector<GuestFrame>& out, DWORD64 ret) {
    alignas(SYMBOL_INFO) char buf[sizeof(SYMBOL_INFO) + 512];
    auto* si = reinterpret_cast<SYMBOL_INFO*>(buf);
    std::memset(buf, 0, sizeof buf);
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen = 511;
    DWORD64 disp = 0;
    if (!SymFromAddr(GetCurrentProcess(), ret - 1, &disp, si)) return;
    std::uint32_t va = 0;
    if (!parse_generated(si->Name, va)) return;
    if (!out.empty() && out.back().va == va) return;  // entry-form body + its one-line wrapper
    out.push_back({va, si->Name});
}

} // namespace

std::vector<GuestFrame> guest_backtrace(unsigned max_frames) {
    std::vector<GuestFrame> out;
    if (!ensure_symbols()) return out;
    void* frames[128];
    const USHORT n = CaptureStackBackTrace(1, 128, frames, nullptr);
    for (USHORT i = 0; i < n && out.size() < max_frames; ++i) add_frame(out, reinterpret_cast<DWORD64>(frames[i]));
    return out;
}

std::vector<GuestFrame> guest_backtrace_from_context(const void* win32_context, unsigned max_frames) {
    std::vector<GuestFrame> out;
    if (!ensure_symbols()) return out;
    CONTEXT c = *static_cast<const CONTEXT*>(win32_context);
    STACKFRAME64 f{};
    f.AddrPC.Offset = c.Rip;
    f.AddrPC.Mode = AddrModeFlat;
    f.AddrFrame.Offset = c.Rbp;
    f.AddrFrame.Mode = AddrModeFlat;
    f.AddrStack.Offset = c.Rsp;
    f.AddrStack.Mode = AddrModeFlat;
    // The faulting instruction itself first (+1: add_frame looks up ret - 1).
    add_frame(out, c.Rip + 1);
    for (int i = 0; i < 128 && out.size() < max_frames; ++i) {
        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, GetCurrentProcess(), GetCurrentThread(), &f, &c, nullptr,
                         SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
            break;
        if (i > 0) add_frame(out, f.AddrPC.Offset);
    }
    return out;
}

} // namespace p3fes::app
