# Third-party provenance for `runtime/include/p3fes/ipu/` and `runtime/ipu/`

The IPU model ports one file's worth of data from **snuri00/ps2-web-recomp** at commit
`c0f476e6af948763c5269f55ade4ae4f9a74ab2b` (MIT License, Copyright (c) 2026 Samir Nuri; text in
`licenses/ps2-web-recomp.LICENSE`), per ADR-0010 §2, using the read-only checkout at
`tools/third_party/_community-eval/ps2-web-recomp` (gitignored). Upstream adapted those VLC tables from **Play!**
(BSD-2-Clause, Copyright (c) 2006-2026 Jean-Philip Desjardins); upstream's notice is reproduced **verbatim** in
`runtime/ipu/NOTICE` and `licenses/Play.LICENSE` (byte-identical to upstream `runtime/src/ipu/NOTICE`, sha256
`095eae38…6c9b`). Each file that took anything from upstream carries a provenance comment at its top; the table below
is the row-per-file form for `THIRD_PARTY_NOTICES.md`.

No GPL source was opened (PCSX2's IPU / mpeg2lib, PS2Recomp, god-of-war-recomp, p3fes-recompiled, libmpeg2,
ffmpeg). ps2sdk's AFL-2.0 `ee/mpeg/src/libmpeg_core.c` (an IPU *client*, not a hardware model) was read to
cross-check command-word field positions and the IPU_BP arithmetic; nothing from it was copied.

| File | Upstream path(s) | Upstream commit | License | What was taken / adaptation |
|---|---|---|---|---|
| `runtime/ipu/vlc_tables.cpp` | `runtime/src/ipu/tables.hpp` (`kMbAddressIncrement`, `kMbTypeI/P/B`, `kMotionCode`, `kDmVector`, `kDcSizeLuma/Chroma`, `kCodedBlockPattern`, `kDctTable0/1`) | `c0f476e` | MIT; tables BSD-2-Clause (Play!, `runtime/ipu/NOTICE`) | the table rows, unchanged (incl. the `length << 16 \| value` VDEC convention); ours: the MPEG-1/MPEG-2 split of B.1 (stuffing only with MP1), the D-picture table, the EOB entries, the lookup with NeedBits/Invalid prefix tries, the introspection API. Rows checked in `tests/ipu/test_vlc.cpp` against hand vectors from the ISO/IEC 13818-2 tables |
| `runtime/ipu/mpeg2.cpp` | `runtime/src/ipu/ipu.cpp` (`convert`, `decode_block`) — cross-check only | `c0f476e` | MIT | CSC coefficients (149, 204, 50, 104, 258, +64 >> 7) and the TH0/TH1 alpha rule agree with upstream; scans, inverse quantisation, IDCT, assembly, CSC/PACK code written from ISO/IEC 13818-2 / 11172-2; no upstream text copied |

Files not listed (`ipu_core.cpp`, `ipu_system.cpp`, all headers) and the tests under `tests/ipu/` are original to
p3fes-port.
