# Disc & binary inventory (Phase 0)

_Observed 2026-10-18 from the user's own disc image. Nothing listed here is committed; this file records identity only._

## Disc image
| | |
|---|---|
| Path | `input/persona3fes.iso` |
| Size | 4,594,302,976 bytes (7-Zip: `Type = Iso`, `VolumeSpaceSize = 4594302976`) |
| SHA-256 | `f8b76ae4e9b9078410571947f2acbe25e4790b0314e9e58c08c69e3ac46f090f` (16 s, computed 2026-10-18) |

## `SYSTEM.CNF`
```
BOOT2=cdrom0:\SLUS_216.21;1
VER=1.00
VMODE=NTSC
```

## Main executable — `SLUS_216.21`
| | |
|---|---|
| Size | 9,096,860 bytes |
| SHA-256 | `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc` |
| SHA-1 | `3929cd7c02be944f25ec6b924e5f1eab9bc5e9cb` |
| MD5 | `9074ba25f5a100940ed233c9f8f675ab` |
| Header | `7f 45 4c 46 01 01 01 00 … 02 00 08 00 01 00 00 00` → ELF32 (`EI_CLASS=1`), little-endian (`EI_DATA=1`), `ET_EXEC` (2), `EM_MIPS` (8), `e_version` 1 |

Verification: `(Get-FileHash extracted\disc\SLUS_216.21 -Algorithm SHA256).Hash` must equal the SHA-256 above before any analysis artefact is trusted.

## Disc root (from `7z l`)
| Path | Bytes | Notes |
|---|---:|---|
| `DATA.CVM` | 3,367,428,096 | main data container (CRI ROFS) — Phase 1 |
| `BTL.CVM` | 936,579,072 | battle data container — Phase 1 |
| `BGM.CVM` | 258,899,968 | music container (not named in GOAL.md; discovered here) |
| `SLUS_216.21` | 9,096,860 | EE executable (above) |
| `SYSTEM.CNF` | 51 | boot config |
| `LIB31/IOPRP310.IMG` | 278,353 | IOP reboot image → **Sony SDK 3.1.0** |
| `LIB31/CRI_ADXI.IRX` | 75,173 | CRI ADX audio decoder (IOP) |
| `LIB31/LIBSD.IRX` | 30,085 | Sony sound driver |
| `LIB31/SDRDRV.IRX` | 9,161 | sound driver RPC |
| `LIB31/MODHSYN.IRX`, `MODMIDI.IRX`, `MODMSIN.IRX`, `MODSESQ.IRX` | 63,005 / 21,941 / 1,929 / 13,717 | Sony "MOD" sequenced-music stack (HSYN synth, MIDI, sequencer) |
| `LIB31/SKHSYNTH.IRX`, `SKMIDI.IRX`, `SKMSIN.IRX`, `SKSESQ.IRX`, `SKSOUND.IRX` | 9,601 / 12,973 / 8,317 / 10,337 / 9,717 | "SK" sound-kit RPC shims for the above |
| `LIB31/PADMAN.IRX`, `SIO2MAN.IRX`, `SIO2D.IRX` | 45,925 / 5,217 / 11,289 | controller / SIO2 |
| `LIB31/MC2_S1.IRX` | 27,981 | memory card (MC2) |
| `LIB31/DBCMAN.IRX`, `MSIFRPC.IRX` | 15,653 / 8,105 | DBC manager, SIF RPC |
| `LIB31/CVS/ENTRIES`, `ROOT`, `REPOSI~1`, `TEMPLATE` | 963 / 51 / 20 / 0 | **Atlus CVS metadata left on disc** — read for internal paths/SDK layout once extracted |

Implications for later phases: audio is a *dual* stack — CRI ADX streams (`CRI_ADXI.IRX`) plus Sony sequenced music (`MOD*`/`SK*`) — so the SPU2/IOP HLE layer must cover both RPC protocols. `MC2_S1.IRX` means the memcard path uses the MC2 (not MC) library.

## Extraction record
`7z x` of the full image → `extracted/disc/`: 28 files, 4.26 GB, `Everything is Ok`. Disk free afterwards: 60.4 GB.

## Atlus CVS metadata (observed in `LIB31/CVS/`)
```
ROOT      :pserver:tohyama@herring.dev.atlus.co.jp:/home/cvs
REPOSITORY persona3_data/lib31
ENTRIES   19 IRX/IMG entries, all revision 1.1.1.1, all dated Tue May 30 07:42:42 2006, binary (-kb)
```
**Inference:** the IOP module set is a vendor import of **Sony PS2 SDK 3.1.0** (`IOPRP310.IMG`, May-2006 timestamps) into Atlus's `persona3_data` CVS module. The EE executable was therefore almost certainly linked against SDK 3.1.x `libsce*` EE libraries — the generation to target when hunting FLIRT signatures or hand-matching `sce*` prologues. Developer handle `tohyama` is incidental; do not propagate it beyond this file.
