// doctest runner for the kernel HLE tests (runtime/hle/kernel) plus the test-only function table.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "kernel_test_util.h"

#include "p3fes_recomp_rt.h"

namespace kt {

Rig* g_rig = nullptr;

namespace {
std::map<u32, GuestFn>& table() {
    static std::map<u32, GuestFn> t;
    return t;
}
void missing(EEContext& c) { g_rig->hooks().fatal(c, c.pc, "test lookup: no function registered at this VA"); }
} // namespace

void register_fn(u32 va, GuestFn fn) { table()[va] = fn; }

GuestFn test_lookup(u32 va) {
    const auto it = table().find(va);
    if (it == table().end()) {
        g_rig->ctx.pc = va;
        return &missing;
    }
    return it->second;
}

} // namespace kt

// The kernel library's default lookup (KernelOptions::lookup == nullptr) links against this.
namespace p3fes::rt {
Fn lookup_func(std::uint32_t va) { return kt::test_lookup(va); }
} // namespace p3fes::rt
