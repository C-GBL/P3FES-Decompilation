# `runtime/native/sound/sk/` — the SK sound-effect stack on native code

Modernize layer 3, steps 2 and 3 (`docs/MODERNIZE_PLAN.md` §3 "Layer 3 status", ADR-0017). The game's sound effects are
the Sony Standard Kit: six IOP modules (SDRDRV, SKSOUND, SKHSYNTH, SKSESQ, MODSESQ, MODHSYN; `docs/ANALYSIS/19`) that the
faithful path loads into the IOP model and runs on the R3000 interpreter (ADR-0014, `runtime/hle/sif/README.md` §9).
With `--native sound` their code runs as native C++ instead, and nothing of them is interpreted or loaded as code.

| File | What |
|---|---|
| `sk_cpu.h` | `Cpu`: the register file and the IOP RAM view the generated code runs on, with the interpreter's semantics (`r3000.cpp`: MIPS I integer set, delay slots, the LWL/LWR/SWL/SWR merges, div by zero, the RAM checks) |
| `sk_modules.h` | `ModuleImage` (file, Pcsx2 base, entry, gp, text/data/bss sizes, the text's FNV-1a 64), `FnEntry` |
| `sk_imports.h` / `sk_imports.cpp` | the 71 imports the six modules call, `imp_<library>_<name>`: libsd by ordinal to the IOP model's libsd (`iop/libsd_hle.h libsd_call`, the same LibsdHle and SPU2 voice model the interpreted modules drive, so the mixer plays the same voices), the kernel ones on `NativeSk` with the interpreter kernel's answers (`iop_kernel_hle.cpp`) |
| `sk_host.h` / `sk_host.cpp` | `NativeSk`: module start, the run-to-block thread scheduler, semaphores, SKSOUND's hard timer (the 240 Hz SK tick on virtual time), sysmem placement in the kernel ranges, SDRDRV's RPC entry, faults, machine state; `SkPort` (what it needs of the IOP model) |
| build dir `sk_gen/sk_gen.h`, `sk_gen_<module>.cpp` | **generated at build time** (below) |

## Generated code

`tools/ours/modernize/skgen.py` reads the six IRX files from `P3FES_LIB31_DIR` (CMake cache, default
`<source>/extracted/disc/LIB31`) and writes one C++ function per IOP function (301; one statement per instruction, the
way p3fes_handgen writes the EE game code) into the build tree. It is derived from game data, so like `recomp/generated`
it is never committed; without the files (or without Python, `P3FES_PYTHON`) the library gets an empty table and
`--native sound` keeps the interpreted modules.

* Functions: module entries, exports, jal targets and every text address held in a `lui/addiu` pair or an `R_MIPS_32`
  word (handlers, thread entries, callbacks), to a fixed point; a body is what its branches, `j` and its jump tables
  (eight, bounded by their `sltiu`) reach; a `j` to another function is a tail call.
* Addresses are the relocated ones at the faithful image bases (IopLayout::Pcsx2), so every constant is the faithful one.
* Calls: a `jal` to an import stub becomes the exporting module's function (the libraries the six export to each other)
  or a host import; `jalr` and indirect jumps go through `call_address` (the address table `kFunctions`). `jr $ra`
  returns and checks that `$ra` is the one the function was entered with.
* Threads: an import that blocks (SleepThread, WaitSema, sceSifRpcLoop) parks the running thread and the callers return
  at once; a thread entry gets a resume label after each such call, where the scheduler continues it when it is woken
  (its registers restored). A block deeper than the entry is a fault (none happens).
* The IRX files are read for their initialised data only (relocated as the loader would); the code areas of the images
  in IOP RAM stay zero, and `NativeSk::install` refuses a file whose text is not the one the code was made from.

## How the game reaches it (`--native-sk`, with `--native sound`)

* `sif` (default): the game's own libsdr is unchanged -- `sceSdRemote` sends its RPCs to SDRDRV (0x80000701) and loadfile
  its module loads; SDRDRV's server in the IOP model (`srv_sdr.cpp`) starts the native modules at the loads' instants
  and hands every request to SDRDRV's native handler on its RPC thread, as the interpreter's kernel would. The output
  is the interpreter's byte for byte (the sound log with every cycle, the mix, eeMemory, gsMemory and frames on the five
  routes; `tests/sif/test_sk_native.cpp`).
* `direct`: `kwlnInitPS2Systems`' module loads and `sceSdRemote`'s three `sceSifCallRpc` calls go to the service
  (`game/src/cri/sdr_native.cpp`), no SIF. Each faithful call blocks the calling EE thread until the RPC end, and other
  threads run meanwhile; without that the battle recording desyncs (MODERNIZE_PLAN "Layer 3 status").
* `off`: the interpreted modules (step 1 only), for A/B.

## Tests

`tests/sif/test_sk_native.cpp` (needs the user's LIB31 and `DATA/SOUND/SPU`): the generated code matches its files (a
changed bit is refused, every function found by its address); the native stack and the interpreted modules side by
side over their own RAM and libsd -- the H_Sndcom bring-up with both banks and the menu SEs, then 1,500 random plays,
stops, status queries and volume changes on both ports at random instants: every reply, every libsd event with its
instant, the block maps and every block's bytes identical. `tests/game/test_sound_native.cpp`: the direct branch of
`sceSdRemote` on the ELF's code.
