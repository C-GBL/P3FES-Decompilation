// Shared by the rt adapter translation units (runtime/rt/*.cpp); not installed.
#pragma once

#include "p3fes_recomp_rt.h"

#include "p3fes/ee/core.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/rt_hooks.h"

namespace p3fes::rt::detail {

// The installed hooks; never null (points at the aborting default until set_hooks()). Read
// directly by the hot entry points (check_events) to save the hooks() call.
extern RtHooks* g_hooks;

inline RtHooks& hk() noexcept { return *g_hooks; }

// The context reported by stops that receive none (bind_context), or a zeroed placeholder.
EEContext& report_context() noexcept;

// Format `fmt` and call RtHooks::fatal(ctx, pc, message). Never returns.
[[noreturn]] void fatalf(EEContext& ctx, u32 pc, const char* fmt, ...);

// After a hardware-register access (ADR-0013 §2, rt_hooks.h): a check point.
inline void after_hw(EEContext& ctx) { hk().check_events(ctx); }

} // namespace p3fes::rt::detail
