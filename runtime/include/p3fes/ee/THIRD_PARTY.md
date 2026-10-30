# Third-party provenance for `runtime/include/p3fes/ee/`

The four headers `hilo.h`, `mmi.h`, `fpu.h` and `vu0.h` port R5900 semantics from
**snuri00/ps2-web-recomp** at commit `c0f476e6af948763c5269f55ade4ae4f9a74ab2b`
(MIT License, Copyright (c) 2026 Samir Nuri), per ADR-0010 §2. The upstream clone
used for the port is the read-only checkout at
`tools/third_party/_community-eval/ps2-web-recomp` (gitignored). Each header
carries a one-line provenance comment at its top; the table below is the
row-per-file form for merging into `THIRD_PARTY_NOTICES.md`.

| Ported file | Upstream path(s) | Upstream commit | License | Adaptation |
|---|---|---|---|---|
| `runtime/include/p3fes/ee/hilo.h` | `runtime/include/ps2/mmi.hpp` (`set_hilo`, `hilo`, `mult`, `multu`, `madd`, `maddu`, `div`, `divu`); `recomp/codegen.cpp` (`Mfhi`/`Mflo`/`Mthi`/`Mtlo`[1], `Mfsa`/`Mtsa`/`Mtsab`/`Mtsah` emit rules) | `c0f476e` | MIT | `p3fes::ee` namespace; `EEContext`/`u128` for `Cpu`/`Reg128`; SA held in hardware bit units (upstream: bytes); named `*1` pipe wrappers |
| `runtime/include/p3fes/ee/mmi.h` | `runtime/include/ps2/mmi.hpp` (all lane ops, `pmfhl`, `pmthl`, `pmult*`/`pmadd*`/`pmsub*`/`phmadh`/`phmsbh`/`pdiv*`, `qfsrv`, `plzcw`); `recomp/codegen.cpp` (`Lq`/`Sq` `& ~15u` masking, `Pmfhi`/`Pmflo`/`Pmthi`/`Pmtlo`) | `c0f476e` | MIT | `p3fes::ee::mmi` namespace; GNU `vector_size` types removed; scalar lane-loop path (`mmi::scalar`) kept as the upstream text plus an SSE2 `<emmintrin.h>` path (`mmi::sse2`) selected by `P3FES_EE_MMI_USE_SSE2`; `std::memcpy` for `__builtin_memcpy`; PMULTH/PMADDW/PHMADH mode parameters exposed as named functions |
| `runtime/include/p3fes/ee/fpu.h` | `runtime/include/ps2/fpu.hpp` (entire file); `runtime/include/ps2/generated.hpp` (`fpu_compare`, `fpu_div`, `fpu_rsqrt`); `runtime/src/cop.cpp` (`cfc1`, `ctc1`); `recomp/codegen.cpp` (COP1 emit rules) | `c0f476e` | MIT | `p3fes::ee::fpu` namespace; FPR/ACC held as raw `u32` bit patterns in `EEContext`; per-instruction wrappers (`add_s` … `ctc1`); `std::swap` replaced by explicit swaps |
| `runtime/include/p3fes/ee/vu0.h` | `runtime/include/ps2/vu.hpp` (entire file); `runtime/include/ps2/vu_ops.hpp` (`flags` → `update_mac_flags`); `runtime/src/cop.cpp` (`cfc2`, `ctc2`, `vu0_wait`); `recomp/codegen.cpp` (COP2 emit rules: broadcast/Q/I selection, interlock, `Viadd`/`Visub`/`Viand`/`Vior`/`Viaddi`, `Lqc2`/`Sqc2`) | `c0f476e` | MIT | `p3fes::ee::vu0` namespace; `VU0State` (`u32` bit-pattern storage) for `Vu0Regs`; `EEMemory` for LQC2/SQC2; named `_bc`/`_q`/`_i` wrappers; VU memory / micro-program entry points not ported |
| `runtime/include/p3fes/ee/core.h` | `runtime/include/ps2/memory.hpp` (`lwl`, `lwr`, `ldl`, `ldr`, `swl`, `swr`, `sdl`, `sdr`) consulted as a cross-check only | `c0f476e` | MIT | Written for p3fes-port from the MIPS III / EE Core Instruction Set Manual (integer ALU, shifts, extension, GPR write rule, addressing, unaligned merges as mask formulas); upstream was read to confirm the little-endian merge shifts and its LWR partial-load choice (bits 32..63 unchanged), which `core.h` adopts and tags as hardware-unverified. No upstream text copied. |
| `runtime/include/p3fes/ee/cop0.h` | `runtime/src/kernel.cpp` (`mfc0`, `mtc0`, `eret`, `set_interrupts`), `runtime/src/cop.cpp` (`cpcond0`) consulted as a cross-check only | `c0f476e` | MIT | Written for p3fes-port from the EE Core User's Manual (Status EIE/EXL/ERL, ERET) and the EE User's Manual (DMAC D_PCR.CPC / D_STAT.CIS for CPCOND0); the EI/DI/ERET bit rules agree with upstream. Upstream returns CPCOND0 = true unconditionally; `cop0.h` computes it from the two registers instead. No upstream text copied. |

**Semantics changed after the port (2026-10-19, PCSX2 2.8.2 compiled test vectors, `docs/PCSX2.md` section 11):**
`fpu.h` raises the FCR31 D+SD / I+SI flag pairs (upstream: `0x30000`) and distinguishes
`zero_divide`/`invalid_op` in `Result`; `vu0.h` updates MAC/STATUS in macro mode (upstream: micro-programs only),
sets I/D with their sticky bits on the Q pipe and treats MAC as read-only through CTC2. The upstream text for the
unchanged rules is still as listed above.

Tests under `tests/ee/` are original to p3fes-port; their expected values are
hand-derived from the EE Core User's Manual where the manual defines the
result, and copied from upstream's behaviour (and labelled so) where it does
not. No code from GPL projects (`PS2Recomp`, PCSX2) was consulted or copied.

Upstream license text (MIT):

```
MIT License

Copyright (c) 2026 Samir Nuri

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
