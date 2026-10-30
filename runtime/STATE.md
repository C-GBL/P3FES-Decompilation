# Machine states (`--save-state-at` / `--load-state`)

_Since 2026-10-21. A complete, versioned image of the whole machine at a vblank boundary, resumable in a fresh
process: `p3fes --save-state-at vblank:N FILE` (also `flip:N`, `sky:N`, `cycles:N`; repeatable, ends the run like
`--snapshot-at`) and `p3fes --load-state FILE` (then `--snapshot-at`, `--frames`, ... as usual)._

## Security: machine states are a dev-only build option

A state file holds raw host stacks: return addresses into `p3fes.exe`, saved registers, the /GS cookie. **Loading a
state is equivalent to running code from whoever wrote it.** Making states resumable also costs two of the
executable's exploit mitigations, so the support is a CMake option, **`P3FES_MACHINE_STATES`, default OFF**:

* **ON** (the gate's tree, slice trees, segment runs; local development only): `p3fes.exe` links with
  `/DYNAMICBASE:NO` (no ASLR for the image), guest RAM / the EEContext / the kernel object come from a fixed-address
  arena, and `runtime/app/state_boot.cpp` replaces the process's /GS cookie, before `main`, with the one stored in
  the state named by `--load-state`. `--save-state-at` / `--load-state` work.
* **OFF** (play builds; later the multiplayer client and server; anything that is shipped or run on someone
  else's machine): a normal ASLR executable with its own random /GS cookie and the normal allocator;
  `--save-state-at` / `--load-state` refuse ("built without machine states"). The kernel's own fibers are the same
  in both (they need neither).

Rules: never ship an ON build; never load a state file you did not make yourself on this machine. These
trade-offs apply to this local dev build only.

## What is in a state

| Part | Where (`state()` / `state_io`) |
|---|---|
| EE context (128-bit GPRs, HI/LO, SA, FPU + ACC/FCR31, COP0, VU0 regs), main RAM, scratchpad, BIOS window | `KernelHooks::state` (live context), `EEMemory::state` |
| Kernel: time base + events, INTC, timers, DMAC channels (incl. mid-chain, stalled, held), handler chains, threads (TCBs + saved contexts), semaphores, installed syscalls, run status | `runtime/hle/kernel/kernel_state.cpp` |
| Every live guest-thread fiber: its host stack from the saved `rsp` to the top (the suspended recompiled call chain) | `kernel_state.cpp` (see "Why the same executable") |
| GS core + 4 MiB local memory, privileged registers (flip count, CSR, IMR), GIF paths + queued PATH1 packets + FIFO, VIF1 (mid-code, backlog), VIF0 stub, VU1 registers + flag pipeline + micro/data memory | `runtime/gs/gs_state.cpp`, `VU1Interpreter::state` (decode caches and the AOT residency index are rebuilt from micro memory) |
| IPU (FIFOs, decoder position, tables, command timing) | `IpuCore::state` |
| SIF registers, queued SIF0 packets, RPC bindings + pending calls; IOP RAM + heap; servers: fileio (open files), CDVD (an in-flight read, its staging buffer), PADMAN, DBCMAN + MC2_S1, CRI_ADXI (DTX/SJX/RNA/PSM), SDRDRV with the interpreted SK modules (R3000, IOP kernel threads/semaphores/timers/modules, libsd, SPU2 voices + 2 MiB SPU2 RAM), the SPU2 mixer rings, the memory card image (copy-on-write pages not yet flushed included) | `runtime/hle/sif/iop/iop_state.cpp`, `SifHle::state` |
| Audio fingerprint (the NullSink hash capture.json reports) | `NullSink::state` |
| Host counters capture.json reports (flips, markers, GS census), the pad feed (replay log, script, latch) | `runtime/app/game_state.cpp`, `PadFeed::state` |

Not in a state: host outputs (window, XAudio2, `--dump-wav` files, `--sound-log`, `--record-input`), diagnostics
(`--zones`, `--profile`, `--gs-census/record`, `--vu1-stats`), the host's choices (GS backend, VU1 engine). The
D3D11 back end syncs GS memory into the CPU copy before a save and uploads it to the GPU after a load
(`GsD3D11Renderer::reset_memory`), so states move freely between software and `--gs-backend d3d11 --gs-exact`,
and between `--vu1 interp` and `aot` (all exact).

File: a fixed `StateHeader` (version, executable hash + size + image base, the /GS cookie, ELF SHA-256, the
behaviour-relevant configuration -- `--sk`, `--iop-layout`, `--spu2-interp`, disc kind -- and the save point) and
the payload with long zero runs elided (`p3fes/state_io.h`). Measured 2026-10-21 on the five routes and the climb:
22-37 MiB; save 0.24-0.30 s on the software GS, 0.3-2 s typical with the D3D11 back end (up to 16 s when its render
thread is far behind: the save first drains it into the CPU copy of GS memory); load 0.07-0.6 s. Every component section carries a tag the reader checks, so an asymmetric `state()` fails at its
boundary by name; trailing data fails the load.

## Why the same executable (and what that costs)

Recompiled functions are C++ functions and guest calls are host calls: a guest thread suspended in `WaitSema` or
preempted at a check point is a host call stack (the recompiled chain + kernel frames) on its fiber. A state can
only resume those stacks in the executable that wrote them. So:

* the kernel's fibers are its own (`runtime/hle/kernel/fiber.h`, a MASM stack switch; Win32 fibers before):
  plain-data contexts on fixed stack slots (`p3fes/pinned.h`);
* the objects those frames point into -- guest RAM, the EEContext, the kernel object -- come from a fixed-address
  arena, allocated in the same order in every process; thread/semaphore tables are arrays inside the kernel object;
* `p3fes.exe` links with `/DYNAMICBASE:NO` (same image base every run) and adopts the saver's /GS cookie before
  `main` (`runtime/app/state_boot.cpp`; the state must be named with `--load-state`);
* the loader refuses a state from another `p3fes.exe` (file hash), another ELF or configuration.

Consequence: a state written by the separately built zero-replacement program cannot seed another build. Reference
mode (below) puts the zero-replacement program inside every build, so one executable makes both the reference
states and the hand-code runs.

## Reference mode (`--reference-mode`)

Every build keeps the recompiled body of each function `game/replaced.txt` replaces, as `fn_<name>_<addr8>__recomp`.
Since 2026-10-21 every generated call to a replaced function and every dispatch row (indirect calls, `jalr`, thread
entries, handlers through `rt::lookup_func`) goes through a selector the emitter writes:

    inline void fn_X__sel(EEContext& ctx) { if (rt::g_reference_<addr8>) fn_X__recomp(ctx); else fn_X(ctx); }

(declared per generated unit for the replaced functions it calls, so `functions.h` stays independent of
`--replace`; the flags and `rt::set_reference_mode` are defined in `dispatch.cpp`). `--reference-mode` sets every flag:
the executable then runs the zero-replacement program -- hand code is never entered, since every entry into it is a
shim reached through a call site or the dispatch table (hand-to-hand C++ calls happen only inside hand code). Checked
2026-10-21 on all six routes with D3D11 exact: battle, fusion, shop and the climb give eeMemory.bin, gsMemory.bin
and frame.png byte-identical to the zero-replacement references; dorm and M1 equal a fresh norep2 run byte for byte
(their stored references predate the current dead-stack bytes; with the dead stack excluded they are 0 bytes off
too). So slice agents and bisects need no separate norep build. `p3fes_recomp --no-selectors` emits plain calls
(the cost baseline; `--reference-mode` then does nothing).

The mode is read at every call: with `--load-state`, the loading run's mode applies from the loaded point on, and
frames suspended in the state finish in the body they entered.

## Segments (`gate.ps1 -Segments`)

The same executable runs a route in reference mode from boot, saving a state and a snapshot at each mark; each
segment [S, E) then runs in **hand mode** from the reference state at S (segment 0 from boot) to E, and must equal
the reference snapshot at E. Frames suspended at S are `__recomp` frames, which finish as originals; every new call
goes to hand code -- so a segment tests exactly the hand code that runs inside it, a difference shows up in the
segment that causes it (not in every later one), and the segments run in parallel as the reference run passes their
marks. The reference run's end snapshot is also compared with the zero-replacement reference. Wall time is bounded
by the reference run from boot (a state is only valid for the executable that wrote it, so each build must make its
own): segments localise and isolate, they do not shorten a fresh build's gate. The from-boot routes against the
norep references remain the authoritative merge gate.

## Checks

* `tools/ours/state/state_roundtrip.ps1 -Exe build\<tree>\bin\p3fes.exe -Route dorm -Points 1000,3000 [-Gs software]`:
  straight to M vs save at N + load in a fresh process + run to M; eeMemory.bin, gsMemory.bin, frame.png and
  capture.json must be identical (also checks that saving perturbs nothing).
* `gate.ps1 -StateCheck`: every replay route saves mid-way; a fresh process resumes and must equal the route
  (the resumed runs overlap the long battle route: +6 s on a 229 s replay phase, 2026-10-21).
* `tools/ours/state/state_segments.ps1 -Exe ... -Route climb -Marks 10000,20000,30000 -Make`, then without `-Make`:
  one run from boot leaves states and snapshots at the marks; the segments then re-run in parallel from those
  states and must equal the snapshots (same executable). Climb, D3D11, 2026-10-21: from boot with the states and
  snapshots 1310 s; the four segments (0-10000 from boot, three from states, -Jobs 4) 482 s wall, all identical --
  the shape and the payoff (~2.7x) of a segmented gate, once reference states can seed candidate builds.
* `P3FES_STATE_AUDIT=1` (or `2`, with return addresses as exe offsets): classifies every pointer-like value on the
  saved fiber stacks (executable, pinned regions, own stack, other private memory). Dorm route at vblank 2000:
  7 fibers of 880-2048 bytes; the only "private" values were guest addresses held as integers and the stale bytes
  of a moved-from std::string in switch_to_host (its destructor sees the empty small-string state).
* Round trips run on 2026-10-21 (all four files identical): dorm 1000/2500/3000/4000/4850 (d3d11) and 2500/4000
  (software); M1 200/300; battle 1040 (mid-FMV)/3000/4700/5500 (mid-battle)/6100 (d3d11) and 3000/5500 (software);
  fusion 1500/3500/5000/6200; shop 1000/2500/3500/4050; the climb 5000/15000/25000/35000/39000 to 39820; a dorm
  state saved on D3D11 resumed on the software GS and the reverse. No save point had a CD read in flight (the CDVD
  HLE completes a read within its service step), so that path -- the pending read's destination re-pointed into the
  loaded staging buffer -- is implemented but was not exercised.
* `gate.ps1 -FastGs -Segments` (2026-10-21, all six routes, 17 segments, -SegmentJobs 8): every reference run equal
  to the norep references (0 bytes). Before the faithfulness-audit merge (2ccab12) two segments differed -- dorm
  0-2500 (6 heap bytes, 0x013A8300 / 0x013AE770, hand code the from-boot gate at 4900 does not see) and climb
  6500-13000 (597 heap bytes from 0x00A4AD3E on, the transient climb difference); at 2ccab12 all 17 segments are
  0 bytes (replay phase 1127 s wall). A planted difference (the datSetFlag shim bumping a RAM byte between vblanks 19600 and 25900) was
  reported in climb 19500-26000 only (1 byte), every later segment clean. Note the gate's eeMemory comparison masks
  the kernel area below 0x00100000 (tracediff), so a difference there is invisible to every mode. Wall time: the
  -Segments replay phase took 1127 s at 2ccab12 (bounded by the climb's reference run, 1126 s, with up to 8 game
  processes sharing the machine), the from-boot gate's replay phase 1239 s (climb route 874 s, overlapping both
  compilers' suites) -- the same order, as expected: segments
  localise, they do not save a fresh build's from-boot pass.
* A new component with machine state must get a `state(StateIo&)` and a place in its owner's: the round trip
  catches what is missing.
