# R5900 semantics test vectors

`pcsx2_vectors.json` holds 3,443 vectors for the EE semantics headers
(`runtime/include/p3fes/ee/{hilo,mmi,fpu,vu0,core}.h`) **observed on PCSX2 2.8.2**:
a generated R5900 test program (`tools/ours/eevec/gen_vectors.py`) ran under PCSX2
twice — EE recompiler (`obs`) and EE interpreter (`obs_int`, stored only where it
differs) — and every architectural result was read back over PINE
(`tools/ours/eevec/run_pcsx2.py`). `tests/ee/test_pcsx2_vectors.cpp` (in `p3fes_tests`)
replays each vector through our headers (lane-parallel MMI ops on both the scalar and
the SSE2 path) and compares field by field; the per-vector `status` stored in the JSON
must equal the one the test computes. Regeneration, slot layout and the status classes
are documented in `tools/ours/eevec/README.md`; results and the PCSX2 engine
differences in `docs/PCSX2.md` "EE semantics vectors (PCSX2 observed)".

The hand-written vectors in `tests/ee/test_*.cpp` stay: they document intent. Each
expectation there carries one of these provenance tags:

| Tag | Meaning |
|---|---|
| `(hand: EE Core User's Manual semantics)` | The manual defines the result (lane layout, saturation bounds, flush-to-zero, round-toward-zero, address masking). The value was computed by hand from that definition. |
| `(PCSX2 2.8.2 observed: <id>)` | Settled by the vector `<id>` of `pcsx2_vectors.json`: both PCSX2 engines (or the interpreter, where they differ) produce this value and our header reproduces it. |
| `(upstream behaviour, hardware-unverified)` | The manual leaves the result undefined or does not go to that level of detail and the vectors do not exercise it; the test pins the behaviour of `snuri00/ps2-web-recomp @ c0f476e`. |
| `(upstream behaviour, deliberate disagreement)` | PCSX2 does something else and we keep ours on purpose; the vector status says `disagree:<class>` and the class is explained in `docs/PCSX2.md`. |

Rules the vectors settled (header changed, each with the driving vector in the header comment):
FCR31 D+SD / I+SI flag rules for DIV/SQRT/RSQRT (fpu.h); macro-mode MAC/STATUS updates,
I/D with sticky bits on the Q pipe, read-only MAC (vu0.h).

Rules kept as deliberate disagreements: ADD/SUB alignment (upstream's 25-binade rule = the
EE recompiler's; the interpreter and the VU path are exact round-toward-zero; lead decision
per ADR-0012), the EE's exponent-255 range and ±0x7FFFFFFF clamp (PCSX2 clamps to IEEE
±FLT_MAX), DIV.S round-to-nearest (integration decision 1; the interpreter truncates), SA held in bits (PCSX2: bytes), `PHMADH`/`PHMSBH` odd words
left unchanged, reserved `PMFHL` formats as `.SH`, MAX/MIN ±0 ordering, CTC2 CLIP/CMSAR0
widths, VRSQRT evaluated in one double-precision expression.

## SSE2-vs-scalar equivalence

`tests/ee/test_mmi_paths.cpp` is independent of any oracle. It runs all 49
three-operand, 12 two-operand and 6 shift-by-immediate MMI lane operations
(plus `QFSRV` for every SA byte count) through `p3fes::ee::mmi::scalar::*`
and `p3fes::ee::mmi::sse2::*` on 4,000 random quadwords per operation, where
each lane is drawn from a mix of random bits and the saturation/sign
boundaries (`0`, `0xFFFFFFFF`, `0x80000000`, `0x7FFFFFFF`, `0x80008000`,
`0x7FFF7FFF`, `0x80808080`, `0x7F7F7F7F`), and fails on the first mismatch
with both inputs printed. Operations the SSE2 namespace re-exports from the
scalar one are listed too so the table is the complete instruction set and a
later SSE2 implementation is automatically covered. The default path is chosen
by `P3FES_EE_MMI_USE_SSE2` (1 unless defined otherwise); the last test case
checks that `mmi::` resolves to the configured path. `test_pcsx2_vectors.cpp`
additionally requires both paths to agree on every PCSX2 vector.
