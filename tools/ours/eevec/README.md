# eevec — EE semantics vectors observed on PCSX2 2.8.2

Compiled test vectors for `runtime/include/p3fes/ee/{hilo,mmi,fpu,vu0,core}.h` (GOAL.md Phase 4 "unit-test the
MMI/FPU translations against PCSX2", ADR-0006 item 5). A small R5900 program runs every vector on PCSX2 and stores
the architectural results in RAM; the same vectors are replayed through our headers by a doctest and compared
field by field. Results and the regeneration recipe are documented in `docs/PCSX2.md` "EE semantics vectors".

| File | Role |
|---|---|
| `gen_vectors.py` | the vector tables (single source of truth) and the generator: emits `eevec.s` + `layout.json`, `--build` assembles/links `eevec.elf` with the ps2dev toolchain (`$PS2DEV/ee/bin`) |
| `run_pcsx2.py` | boots the ELF under PCSX2 (`tools/ours/pcsx2/run_pcsx2.ps1 -KeepRunning -FastBoot`), waits for the marker words over PINE, reads the results table, decodes each slot and writes the JSON; `--ee-mode int` repeats the run with the EE interpreter (`EnableEE=false`, restored afterwards) and `--merge` stores it as `obs_int` |
| `annotate.py` | writes the per-vector `status` computed by the doctest (`P3FES_EEVEC_REPORT`) back into the JSON and rebuilds `meta.summary` |
| `tests/ee/vectors/pcsx2_vectors.json` | the committed observations (our own program's output, no game data): inputs, `obs` (recompiler), `obs_int` where the interpreter differs, `status`, `ours` for the disagreeing fields |
| `tests/ee/test_pcsx2_vectors.cpp` | the replay/compare test (part of `p3fes_tests`) |

Build products (`eevec.s/.o/.elf`, `layout.json`, reports) live under `build/<tree>/eevec/`, never under `tools/`.

## Regenerate

```powershell
. .\tools\env.ps1
& $env:P3FES_PYTHON -I tools\ours\eevec\gen_vectors.py --out build\eevec-msvc\eevec --build
& $env:P3FES_PYTHON -I tools\ours\eevec\run_pcsx2.py --elf build\eevec-msvc\eevec\eevec.elf --layout build\eevec-msvc\eevec\layout.json --out tests\ee\vectors\pcsx2_vectors.json --ee-mode rec
& $env:P3FES_PYTHON -I tools\ours\eevec\run_pcsx2.py --elf build\eevec-msvc\eevec\eevec.elf --layout build\eevec-msvc\eevec\layout.json --out tests\ee\vectors\pcsx2_vectors.json --merge tests\ee\vectors\pcsx2_vectors.json --ee-mode int
cmake --build build\eevec-msvc --target p3fes_tests
$env:P3FES_EEVEC_REPORT = "$PWD\build\eevec-msvc\eevec\report.jsonl"; .\build\eevec-msvc\bin\p3fes_tests.exe -tc="pcsx2 vectors*"
& $env:P3FES_PYTHON -I tools\ours\eevec\annotate.py --report build\eevec-msvc\eevec\report.jsonl
.\build\eevec-msvc\bin\p3fes_tests.exe -tc="pcsx2 vectors*"      # now green: stored status == computed status
```

`run_pcsx2.py` refuses to start unless `PCSX2.ini` is in the oracle configuration (`capture.py check_ini`) and prints
the normalized ini hash after the run; it must read `2630dac3…2a59` (docs/PCSX2.md §9).

## How a vector is observed

Each vector is a straight-line block: load the operands (`lq`/`ld`/`lw` from a `.data` table), preset HI/LO
(`pmthi`/`pmtlo`), SA, FCR31 (`ctc1`), ACC (`adda.s` / `vaddax`), the VU0 control registers (`ctc2`), run the
instruction, then store rd (`sq`), HI/LO (`pmfhi`/`pmflo`), FCR31 (`cfc1`), the VU0 STATUS/MAC/CLIP/Q (`cfc2`, before
and after) and an ACC probe (`madd.s` / `vmaddx` with a zero product) into a 96-byte slot at
`0x01000000 + 64 + 96 * i`. A progress word is bumped after every vector; the magic word `0x50334645` is written
after the last "safe" vector and a tail marker after the vectors that may trap on hardware (ADD/SUB/ADDI/DADD
overflow, reserved PMFHL formats). Under the EE recompiler everything completes; the EE interpreter raises the
Integer Overflow exception on the first ADD vector, so `obs_int` is absent for the tail.

## Status values (`tests/ee/test_pcsx2_vectors.cpp`)

Per field the test accepts the interpreter's value, else the recompiler's (noted), else it must be explained:

- `agree` — every field equals the interpreter (or the common value).
- `agree-rec:<class>` — equals the recompiler where the interpreter differs; `<class>` names the interpreter
  shortcut (`int-ctc2-status-writes-live-bits`, `int-drops-64bit-carry`, `int-ee-range`, `int-fcr0`, ...).
- `disagree:<class>[+<class>]` — a documented difference from both engines; the observed value must match what the
  class predicts (`ee-range-input`, `ee-range-clamp`, `div-rounding`, `fcr31-cause-clear`, `maxmin-zero-order`,
  `sqrt-negative-zero`, `rsqrt-intermediate-rounding`, `rsqrt-negative-zero-sign`, `sa-units`, `pmfhl-reserved`,
  `phmadh-odd-words`, `ctc2-width`).
- `mismatch` — fails the test.
