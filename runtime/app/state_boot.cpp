// Before main(): adopt the /GS security cookie of the machine state named by --load-state (runtime/STATE.md).
//
// A state carries the host stacks of the suspended guest threads; frames compiled with /GS hold
// (__security_cookie ^ rsp) and check it when they return. The cookie is random per process, so a loading process
// must use the saver's before any frame that will be checked later exists: this dynamic initializer runs in the
// CRT's static-initialisation pass (after __security_init_cookie, before main), reads only the state file's
// header, and writes the saved cookie. It is compiled without buffer checks itself. GameHost::load_state verifies
// the cookie matches and refuses the state otherwise. In this file because a static initializer in a library
// object nothing references would be dropped by the linker.
#include <windows.h>
#include <shellapi.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "p3fes/state_io.h"

extern "C" std::uintptr_t __security_cookie;

namespace {

__declspec(safebuffers) bool adopt_state_cookie() {
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) return false;
    bool adopted = false;
    for (int i = 1; i + 1 < argc; ++i) {
        if (std::wcscmp(argv[i], L"--load-state") != 0) continue;
        std::FILE* f = _wfopen(argv[i + 1], L"rb");
        if (!f) break;
        p3fes::StateHeader* h = new p3fes::StateHeader;
        const p3fes::StateHeader ref;
        if (std::fread(h, sizeof *h, 1, f) == 1 && std::memcmp(h->magic, ref.magic, sizeof ref.magic) == 0 &&
            h->version == p3fes::kStateVersion && h->header_bytes == sizeof(p3fes::StateHeader) && h->security_cookie != 0) {
            __security_cookie = static_cast<std::uintptr_t>(h->security_cookie);
            adopted = true;
        }
        delete h;
        std::fclose(f);
        break;
    }
    LocalFree(argv);
    return adopted;
}

[[maybe_unused]] const bool g_state_cookie_adopted = adopt_state_cookie();

} // namespace
