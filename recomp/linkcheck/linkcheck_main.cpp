// Whole-program link check for the generated code: pulls in the dispatch table and the stubs.
// Running it is not meaningful until the runtime implements p3fes::rt (every stub aborts); the
// point is that `p3fes_recomp_linkcheck.exe` links with no unresolved symbols.
#include "p3fes_recomp_rt.h"

#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {
    std::uint32_t va = 0x100008u;  // `start`
    if (argc > 1) va = static_cast<std::uint32_t>(std::strtoul(argv[1], nullptr, 0));
    const p3fes::rt::Fn fn = p3fes::rt::lookup_func(va);
    std::printf("lookup_func(0x%08x) = %p\n", va, reinterpret_cast<void*>(fn));
    return fn ? 0 : 1;
}
