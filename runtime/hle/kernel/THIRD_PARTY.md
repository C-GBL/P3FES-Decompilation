# Third-party provenance for `runtime/hle/kernel/`

Facts and code shapes in this directory were taken from **snuri00/ps2-web-recomp** at commit
`c0f476e6af948763c5269f55ade4ae4f9a74ab2b` (MIT License, Copyright (c) 2026 Samir Nuri), per ADR-0010 §2, from the
read-only clone at `tools/third_party/_community-eval/ps2-web-recomp` (gitignored). The EE kernel rules themselves
come from the user's BIOS (`docs/ANALYSIS/15_ee_kernel_semantics.md`); where upstream differs, `15` wins (e.g.
upstream resets `T3_MODE` to `0x183`, which would skip libkernel's alarm patch; `15` §5 and PCSX2 show CMPE clear,
so this kernel boots with `T3_MODE = 0`). Each file below carries a one-line provenance comment at its top. The
upstream MIT license text is reproduced in `runtime/include/p3fes/ee/THIRD_PARTY.md` (same project, same commit).
Rows are in the form for merging into `THIRD_PARTY_NOTICES.md`. No GPL source (PS2Recomp, PCSX2,
god-of-war-recomp, p3fes-recompiled) was opened.

| File | Upstream path(s) | Upstream commit | License | Adaptation |
|---|---|---|---|---|
| `runtime/hle/kernel/dmac.cpp` | `runtime/src/dmac.cpp` (`run_chain` tag switch, ASR push/pop, TTE tag qword with its DMAtag half zeroed, `run_from_spr_chain`, `source`/`target` RAM/SPR masking, `write` of D_STAT) | `c0f476e` | MIT | written for p3fes-port against `HwBus`/`DmaChannelHandler`: per-channel engine with stall/resume phases, completion as a timed event, SIF0 device-driven chain, traps for interleave/MFIFO/stall control and unrouted channels; no upstream text copied verbatim |
| `runtime/hle/kernel/intc_timers.cpp` | `runtime/src/hw.cpp` (`Timer`, `timer_count`, `timer_schedule`, `timer_event`, MODE write rule `(mode & 0xC00 & ~(v & 0xC00)) \| (v & 0x3FF)`, INTC_MASK `^=`) | `c0f476e` | MIT | exact-rational H-BLANK clock from the time base, lazy event processing on reads, edge-on-flag interrupt rule (inf), GATE and cause-12 traps |
| `runtime/hle/kernel/bus_timebase.cpp` | `runtime/src/hw.cpp` (`vblank_start`: VBLANK_END 22 H-lines after VBLANK_START) | `c0f476e` | MIT | one constant (`kc::kVblankLines`, inf); the bus, ring log and event loop are original |

Everything else in this directory (`kernel_core.h`, `interrupts.cpp`, `scheduler.cpp`, `syscalls.cpp`,
`kernel.cpp`, `runtime/include/p3fes/hle/kernel.h`) and the tests under `tests/kernel/` are original to p3fes-port;
their rules are cited to `docs/ANALYSIS/15` (obs from the BIOS) and the ELF (ps2dev objdump of the verified ELF).
