# Third-party provenance for `runtime/rt/`

No third-party code is ported into `runtime/rt/`: the adapter is original to p3fes-port and only
forwards operands to the semantics headers in `runtime/include/p3fes/ee/`, whose provenance (ported
from and cross-checked against **snuri00/ps2-web-recomp** @ `c0f476e6af948763c5269f55ade4ae4f9a74ab2b`,
MIT) is recorded per file in `runtime/include/p3fes/ee/THIRD_PARTY.md`, together with the upstream
license text.

| File | Upstream path(s) | Upstream commit | License | Relation |
|---|---|---|---|---|
| `runtime/rt/rt_mem.cpp` | `runtime/include/ps2/memory.hpp` (`fast`, `ld*`/`st*`, `slow_*`) — read while cross-checking `ee/core.h` | `c0f476e` | MIT | The RAM-first / out-of-line slow-path structure is the common one and resembles upstream's; resolution goes through our `EEMemory` and the `RtHooks` bus, fatal stops replace upstream's slow handlers. No upstream text copied. |
| all other `runtime/rt/*` | — | — | — | original |

Tests under `tests/rt/` are original to p3fes-port. The first-execution test compares recompiled
game functions against the host C runtime; no GPL source (PS2Recomp, PCSX2) was opened.
