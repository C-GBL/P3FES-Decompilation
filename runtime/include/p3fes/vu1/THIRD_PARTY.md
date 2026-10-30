# Third-party provenance for `runtime/include/p3fes/vu1/` and `runtime/vu1/`

The VU1 interpreter ports semantics from **snuri00/ps2-web-recomp** at commit
`c0f476e6af948763c5269f55ade4ae4f9a74ab2b` (MIT License, Copyright (c) 2026 Samir Nuri), per ADR-0010 §2. The
upstream clone used is the read-only checkout at `tools/third_party/_community-eval/ps2-web-recomp` (gitignored).
Each ported file carries a one-line provenance comment at its top; the table below is the row-per-file form for
merging into `THIRD_PARTY_NOTICES.md`. The upstream MIT license text is reproduced in
`runtime/include/p3fes/ee/THIRD_PARTY.md` (same project, same commit). No GPL source (PS2Recomp, PCSX2) was opened.

| Ported file | Upstream path(s) | Upstream commit | License | Adaptation |
|---|---|---|---|---|
| `runtime/vu1/vu1_interp.cpp` | `runtime/src/vu_micro.cpp` (`run`, `upper`, `lower`, `commit`, `set_flags`, `mac_flags`, `xgkick`, `BranchView`, `read_q`, `q_delay_of`, `reset`); `runtime/include/ps2/vu_ops.hpp` (`FlagPipe`, `clip_value`, `u2f`/`f2u`, EFU `ERCPR` approximation); `runtime/include/ps2/vu.hpp` (`div`, `rsqrt` status handling) | `c0f476e` | MIT | `p3fes::vu1` namespace; per-instance `VU1State` instead of globals; op dispatch through our decoder's `UpperOp`/`LowerOp`; float datapath from `p3fes/ee/fpu.h` (upstream's exact path); traps instead of stderr reports for encodings outside the census set; `IGifSink` instead of `gif::transfer`; `MicroMemory` generation counter instead of `code_changed` |
| `runtime/vu1/vu1_qtiming.{h,cpp}` | `runtime/include/ps2/vu_ops.hpp` (`VfUse`, `vf_use`, `issue`, `retire`, `q_delay`, `q_unit_latency`, `waits_q`, `reads_q`, `q_read_kind`, `branch_delay_exempt`) | `c0f476e` | MIT | operates on `DecodedPair` fields instead of raw words; undefined halves contribute no operands; branch list built once per micro-memory generation |
| `runtime/vu1/vu1_decode.cpp`, `runtime/include/p3fes/vu1/vu1_decode.h` | `runtime/src/vu_micro.cpp` (`decode_upper`, `lower` opcode/funct/index tables) — cross-check only | `c0f476e` | MIT | tables written from our `tools/ours/vu1/vu1_decode.py`, itself cross-checked against upstream (docs/ANALYSIS/09 §1); no upstream text copied |
| `runtime/include/p3fes/vu1/vu1_interp.h` | `runtime/include/ps2/vu_ops.hpp` (`FlagPipe` fields) | `c0f476e` | MIT | public state/sink/interpreter API is original to p3fes-port |

Tests under `tests/vu1/` are original to p3fes-port; expected values are hand-derived from the VU/GS User's Manual
definitions where the manual defines the result, and taken from upstream's behaviour (and labelled so) where it does
not.
