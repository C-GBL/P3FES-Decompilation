# Third-party provenance for `runtime/include/p3fes/gs/` and `runtime/gs/`

Parts of the GS/GIF/VIF1 model were consulted from or cross-checked against **snuri00/ps2-web-recomp** at commit
`c0f476e6af948763c5269f55ade4ae4f9a74ab2b` (MIT License, Copyright (c) 2026 Samir Nuri), per ADR-0010 §2, using the
read-only checkout at `tools/third_party/_community-eval/ps2-web-recomp` (gitignored). Register layouts, pixel
storage formats and VIFcode definitions are the GS / EE User's Manuals'; game-side values are from
`docs/ANALYSIS/10` and `14`. Each file that took anything from upstream carries a one-line provenance comment at its
top; the table below is the row-per-file form for merging into `THIRD_PARTY_NOTICES.md`. The upstream MIT license
text is reproduced in `runtime/include/p3fes/ee/THIRD_PARTY.md` (same project, same commit). No GPL source
(PCSX2/GSdx, PS2Recomp, god-of-war-recomp, p3fes-recompiled) was opened; PCSX2's `.gs.zst` dumps and `GS.bin`
save-state entries were not parsed (only PCSX2's `eeMemory.bin` and `Screenshot.png` outputs were read).

| File | Upstream path(s) | Upstream commit | License | What was taken / adaptation |
|---|---|---|---|---|
| `runtime/gs/gs_mem.cpp` | `runtime/src/gs/gs.cpp` (`build_tables`, `kColumnWord`) | `c0f476e` | MIT | the arrangement of the PSMT8/PSMT4 column formula; block tables written from the manual; tables checked in `tests/gs` against the manual's literal column tables |
| `runtime/gs/gs_core.cpp` | `runtime/src/gs/gs.cpp` (`write`, `write_packed`, `load_clut`, `feed_image`, `local_copy`) | `c0f476e` | MIT | cross-check of PACKED field positions and the TEX2 field mask; register file, CLUT buffer model (16-bit halves, CSA, CBP0/CBP1), bit-stream transfers and DIR-ordered local copies are our own |
| `runtime/gs/gs_raster.cpp` | `runtime/src/gs/raster.cpp` (`plot`, `expand16`, `fetch`) | `c0f476e` | MIT | cross-check of the TFX, fog and blend arithmetic and TEXA expansion; coverage (top-left rule), interpolation, LOD/mipmaps, dithering and FBMSK handling are our own |
| `runtime/gs/gif.cpp` | `runtime/src/gs/gif.cpp` (`walk`) | `c0f476e` | MIT | cross-check of the tag-walking loop; arbitration, PATH1 queue and GIF registers are our own |
| `runtime/gs/vif1.cpp` | `runtime/src/vif.cpp` (`unpack_words`, `run_vu`, `unpack`, `execute`) | `c0f476e` | MIT | UNPACK data length, write-cycle/mask/mode rules, the MSCAL TOP/ITOP/DBF/TOPS update; upstream behaviour kept and labelled for the manual's "indeterminate" lanes (V2 `x,y,x,y`, V3 `w = 0`) and unmasked fill writes (row register); the word-stream state machine, stalls and backlog are our own |

Files not listed (`gs_priv.cpp`, `gs_output.cpp`, `gs_system.cpp`, `gs_selftest.cpp`, `tools/gscmp.cpp`, all
headers, `runtime/src/gs/d3d11_backend.cpp`) and the tests under `tests/gs/` are original to p3fes-port.
