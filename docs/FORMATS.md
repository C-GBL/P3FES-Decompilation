# Data formats — `runtime/formats/` (Phase 1)

Parsers for the on-disc Atlus / CRI / RenderWare formats, in the priority order of
ADR-0008 §3. Library `p3fes_formats` (static, C++20, MSVC + clang-cl clean at `/W4`,
no exceptions across the API: every parser returns `Result<T>` with a `FormatError`
and a static detail string). Parsers are *views* over `std::span<const std::byte>`;
no payload is copied, so a view lives only as long as its buffer.

| Format | Header / API | Coverage | Tests (`tests/formats/`) |
|---|---|---|---|
| Atlus name-first PAK | `pak.h` `PakView` | full (entries, lookup, nested detection, terminator rules) | `test_pak.cpp`: 5 real-file cases, 3 synthetic |
| BF `FLW0` | `bf.h` `BfView` | full structure; instruction stream decoded to records (no VM) | `test_bf.cpp`: 2 real, 1 synthetic (5 subcases) |
| BMD `MSG1` | `bmd.h` `BmdView`, `bmd_tokenize` | full structure, text tokens, relocation table | `test_bmd.cpp`: 3 real, 2 synthetic |
| TMX `TMX0` | `tmx.h` `TmxView::to_rgba8` | header, palettes, pixels → RGBA8 for CT32/CT24/CT16/T8/T4 | `test_tmx.cpp`: 2 real, 2 synthetic |
| RenderWare RMD | `rmd.h` `parse_rmd` | chunk tree enumeration only | `test_rmd.cpp`: 1 real, 2 synthetic |
| CRI ADX | `adx.h` `parse_adx` | header + framing + loop block; no decoding | `test_adx.cpp`: 3 real, 1 synthetic |
| CRI AFS | `afs.h` `AfsView` | entry table + name block; no decoding | `test_afs.cpp`: 2 real, 1 synthetic |

`formats.h` adds `sniff(Bytes) -> FormatKind` (order: BF, BMD, TMX, AFS, ADX, RMD, PAK).
Real-file tests read from `extracted/` (override with `P3FES_EXTRACTED`) and **skip** with
a doctest `MESSAGE` when a file is absent (verified: 18 cases skip, suite exits 0 with an
empty directory). Not started (documented TODO, ADR-0008 order): PM1/PM2/PM3, SPD/TB,
`.BED`, `.CIN`, `.MAP`, `.TBL`, `.FLD`, `.SPR`, `.EPL`, `.FNT`.

Conventions below: "observed" = read from the named file at the named offset; "inferred"
= a rule that held across the census of all files of that kind on this disc (NTSC-U
`SLUS_216.21`, see `docs/DISC_LAYOUT.md`); "unknown" = not established.

---

## 1. Atlus name-first PAK (`.PAC .BIN .FPC .CPK .SE .PAK`, 2 extension-less)

### Layout (observed)

```
entry:  char name[252]   NUL-terminated printable ASCII; bytes after the NUL are
                         usually zero but may be leftover junk (1,036 of 12,755 entries)
        u32  size        little-endian payload size
        u8   data[size]
next entry header at align_up(end_of_payload, 64)   (pad = zero or junk)
terminator: a 256-byte header whose name[0] == 0 and size == 0
            (name bytes 1..251 are zero in 2,749 files, junk in 339)
```

Cited files:

* `DATA/FIELD/PACK/F222_001.PAC` (1,024 B): `+0x000` `f222_001.ENV`, `+0x0FC` size `0x200`,
  payload `0x100..0x300`, terminator at `0x300` (all zero), file ends at `0x400` — the
  file is exactly `terminator + 256`.
* `BTL/MODEL/PACK/BC003.PAC`: entry 0 `bc003.RMD` size `0x7983B` → payload ends `0x7993B`;
  bytes `0x7993B..0x79940` are `07 61 b8 86 4f` (junk); entry 1 `bc003.acx` header at
  `0x79940` = `align64(0x7993B)`.
* `DATA/CAMP/CAMP_FR07.PAK`: entry 1 ends at `0x2EF30` (already 16-aligned); the 16 bytes
  there read `________W1` (junk) and the real header `chara/i_camp_hum_blue_07.tmx` sits at
  `0x2EF40` = `align64(0x2EF30)`. **This rules out 16-byte alignment** and is why the
  community rule "test each 16-aligned position for a valid header" mis-parses this file
  (it accepts the junk as a name with size 0).
* `DATA/BUSTUP/I_B_0315A.BIN` (256 B): terminator only — a valid, empty PAK (6 such files).

### Rules (inferred, census of 3,109 files with PAK extensions)

* **Alignment is 64 bytes** from file start: with `next = align64(header + 256 + size)` all
  3,088 real PAKs walk to a terminator or EOF; 4,929 entries have non-zero pad bytes.
* **Terminator**: `name[0] == 0 && size == 0`. Nothing follows it (0 trailing bytes in all
  3,094 terminated files).
* **EOF-terminated**: 5 files (`DATA/CUTIN/SHAPE/C01_3101.CPK`, `C02_1102`, `C04_3101`,
  `C05_1101`, `C06_3101.CPK`) have no terminator; the file ends exactly at the aligned end
  of the last payload. `PakView::eof_terminated()` reports this.
* **Size-0 entries**: none in real PAKs (the 24 found by a loose walk are junk inside the
  table `DATA/FIELD/TABLE/COMUTBL.BIN`). The parser accepts them anyway.
* **Every real entry name has an extension** (12,755 entries, 0 exceptions). `looks_like_pak()`
  therefore requires a `.` in the first name **and** a valid header / terminator / EOF at
  the second entry position; this rejects the `.BED` (`BED400\0`), `.MAP` (`3\0`), `.CIN`
  (`CIN\0`), `IOPRP300.IMG` (`RESET\0`) and 15 raw-table `.BIN` files that pass a
  first-header-only sniff. `PakView::parse` stays permissive (printable name only).
* **Nested PAKs**: 1,687 entries are themselves PAKs (`.cpk` 643, `.cin`-named 528, `.se`
  336, `.bed` 163, `.bin` 15, `.rws` 2 — by *entry* name). `is_nested_pak()` tests the payload's
  first header. Max 71 entries per file.
* Names may contain `/` (`chara/i_cha07.spr`, `EQUIP/...`) and are case-mixed; `find()` is
  case-insensitive by default.

### Unknown
* Whether the game's loader uses the 64-byte rule or scans for the next header (Phase 2:
  find the `pakfile`-consumer in the ELF). The 15 `.BIN` raw tables (`CARD/GC_BASIC.BIN`,
  `BRP_BASE.BIN`, `SFL_GROUND.BIN`, `FIELD/TABLE/*.BIN`…) use a `{u32 0x64, count, offsets…}`
  layout per the community notes — not parsed.

---

## 2. BF flow script (`FLW0`, 40 files)

### Layout (observed, `DATA/FIELD/SCRIPT/DUNGEONAT00.BF`, 519 B)

```
+00 u32 0            +04 u32 0x117 (= offset of section 4)   +08 "FLW0"   +0C u32 0
+10 u32 5 sections   +14 u32 0 (varies per community survey)  +18 u32 0   +1C u32 0
+20 5 × { u32 type, u32 element_size, u32 element_count, u32 offset }
    0,0x20,1,0x70   procedure labels   { char name[24] "dng_init_00", u32 insn index 0, u32 0 }
    1,0x20,0,0x90   jump labels        (same 32-byte layout)
    2,4,3,0x90      instructions       07 00 00 00 | 09 00 00 00 | 09 00 00 00  (PROC 0, END, END)
    3,1,0x7B,0x9C   message data       07 00 00 00 7B 00 00 00 "MSG1" … (a complete BMD, §3)
    4,1,0xF0,0x117  string table       0x117 + 0xF0 = 0x207 = file size
```
`DATA/FIELD/SCRIPT/LMAP.BF` (2,822 B): sections `(0,32,7,112) (1,32,10,336) (2,4,449,656)
(3,1,130,2452) (4,1,240,2582)`, header `+04` = 2582.

### Rules (inferred, all 40 top-level `.BF`)
* Sections are always types 0–4 in order, contiguous, element sizes 32/32/4/1/1, and tile
  the file exactly; header `+04` equals the string-section offset (so it moves with the
  message data). `BfView::parse` requires the sizes by *type* (not position).
* Instruction word: `u16 opcode | u16 operand`; opcodes 0 (`PUSHI`) and 1 (`PUSHF`) are
  followed by one 32-bit value word. Every procedure label points at a `PROC` whose operand
  is the label's index (checked in `test_bf.cpp` on LMAP.BF); every jump label is in range;
  no opcode > 34 occurs. Opcode names in `BfOpcode` are the community's descriptive names;
  semantics are Phase 2/5 (the 35-way dispatch at `0x30FDF0`/table `0x7B90A0` and the
  502-entry COMM table at `0x7B92B0` per ADR-0009's MIT source — not yet verified in IDA).
* Section 3 parses with `BmdView` unchanged (`DUNGEONAT00`: one selection message
  `YESNO_SEL` with options `Yes` / `No`).

### Unknown
* Header word `+14` (0 in all 40 top-level files; community reports 1…117 in the 470 BFs
  nested in PAKs — likely a local-variable count). String-table internals (240 bytes of
  zeros in both cited files). BFs inside `.FPC`/`.PAC` packs were not censused here.

---

## 3. BMD message file (`MSG1`, 11 files + every BF section 3)

### Layout (observed, `DATA/HELP/DATTUTORIAL.BMD`, 110 B; pointers are relative to +0x20)

```
+00 u32 7       +04 u32 0x6E size   +08 "MSG1"   +0C u32 0
+10 u32 0x6C reloc offset   +14 u32 2 reloc size   +18 u32 1 message   +1C u32 0x00020000
+20 { u32 type 0, u32 ptr 0x18 }                      → message at 0x38
+28 { u32 speaker table ptr 0x4C, u32 speaker count 0, u32 0, u32 0 }
+38 char name[24] "tutorial_000"
+50 u16 1 line   u16 0xFFFF speaker   +54 u32 line ptr 0x3C (→0x5C)   +58 u32 text size 0x10
+5C f2 08 ff ff f1 3f "Tutorial" 0a 00            (text, zero-padded to 4)
+6C 07 16                                          relocation table
```
Selection message (observed in `DUNGEONAT00.BF` §3 and `DATA/FACILITY/TEST.BMD`):
`char name[24], u16 0, u16 option count, u32 ?, u32 ptr[count], u32 text size`; each option
is NUL-terminated (`"Yes\0"`). `BmdView` strips trailing NULs from every line.

### Rules (inferred, all 11 `.BMD` parse; `DATQUESTHELP`/`DATGLOSSARYHELP`/`DATMYTH` 200
messages each, `DATCOMUHELP` 444, `BP_TUTORIAL` 12 dialogue + 8 selection)
* Relocation table (last bytes of the file, `reloc offset + size == file size` in all 11):
  position starts at 0x20; byte `v` even → next pointer field is `2·v` bytes ahead;
  `v & 7 == 7` → run of `(v >> 3) + 2` consecutive words; `v & 3 == 1` → two-byte delta
  `(v16 >> 2)·4`; `v & 7 == 3` → three-byte delta (not observed; from PersonaEditor's writer).
  Decoding `07 16` gives `0x24, 0x28, 0x54` = entry ptr, speaker-table ptr, line ptr — i.e.
  exactly the pointer fields; `DATQUESTHELP` yields 401 = 200 + 1 + 200, `MSG_QUEST` 402
  (+1 speaker name).
* Text tokens (`bmd_tokenize`): `0x20–0x7E` ASCII, `0x0A` newline, `0xF1–0xFF` control code
  of total length `2 × low nibble` (F1 = 2 B … FF = 30 B; second byte = function), `0x80–0xEF xx`
  two-byte glyph. Lines almost always start `F2 08 FF FF F1 3F` and end `F1 04`.
* Glyph index (PersonaEditor convention): `(b1 − 0x81)·0x80 + b2 + 0x20`; `80 B2` → 0x52 `R`,
  so indices < 0x80 are the ASCII set in the wide font. `bmd_line_to_text` renders those
  as letters and others as `{G:xxxx}`; control codes as `{F2 08 FF FF}` (lossless).

### Unknown
* The character table for glyph indices ≥ 0x80 (kana/kanji/symbols): PersonaEditor loads
  it from an external `*.FNTMAP` that is **not** in `tools/third_party/PersonaEditor`; the
  glyph order must come from `DATA/FONT/*.FNT`. The selection message's u32 after the
  counts; what each control function does (community has guesses only).

---

## 4. TMX texture (`TMX0`, 645 top-level + many inside PAKs)

### Layout (observed, `DATA/CARD/PERSONA/I_PRC001.TMX`, 66,624 B)

```
+00 u16 2   +02 u16 0   +04 u32 0x10440 file size   +08 "TMX0"   +0C u32 0
+10 u8 1 palette   +11 u8 0 palette PSM (CT32)   +12 u16 256 w   +14 u16 256 h
+16 u8 0x13 pixel PSM (T8)   +17 u8 0 mips   +18 u8 0 K   +19 u8 0 L   +1A u16 0xFF00 wrap
+1C u32 0 texture id   +20 u32 0 clut id   +24 char comment[28] (zeros)
+40 palette 256 × RGBA (1,024 B; first entries 00 00 00 00 | 00 00 00 80 | 06 06 06 80 …)
+440 pixels 256×256 indices;  0x40 + 1024 + 65536 = 66,624 = file size
```
`DATA/CUTIN/SHAPE/C01_3101.CPK` entry 1 (`c01_301010.tmx`, at `0x5440`, 0x10080 B) is a
PSMT4 texture (16-colour palette, 64 B) that converts cleanly.

### Rules (inferred, all 645 top-level files)
* Only two header variants exist at top level: `(T8, 1 CT32 palette)` × 580 and
  `(T4, 1 CT32 palette)` × 65; always `id 2`, `wrap 0xFF00`, no mipmaps, `file size ==
  0x40 + palettes + w·h·bpp/8` (645/645). Community survey of PAK-nested TMX adds 2 CT32 files.
* **T8 CLUT swizzle (PS2 CSM1)**: within every 32-colour group, 8-colour blocks 1 and 2 are
  swapped (`tmx_unswizzle_clut8`, identical to PersonaEditor's `TilePalette`). T4 palettes
  are linear. T4 pixels: low nibble first. Alpha: `0x80` = opaque → `to_rgba8` maps
  `a ≥ 0x80 → 255`, else `a·2`.
* `to_rgba8` supports CT32, CT24 (alpha 255), CT16/CT16S (5:5:5:1), T8, T4; T8H/T4HL/T4HH
  return `Unsupported` (not on disc).

### Unknown
* Semantics of `texture id`/`clut id`/`comment` (all zero in the cited files); whether the
  game uses the `wrap` field or the GS register defaults.

---

## 5. RenderWare RMD stream (3,234 files)

### Layout (observed, `BTL/MODEL/WEAPON/WP017.RMD`, 11,937 B)

```
+00  type F0F000F0  size 2      lib 40000000   payload 16 00          (Atlus scene tag)
+0E  type F0F000E0  size 0x484  lib 40000000                          (Atlus setup; unaligned start)
+49E 00 00                                                            (2 pad bytes)
+4A0 type 0x16 TexDictionary  lib 1C020037  → children 0x01 Struct, 0x15 TextureNative…
     then 0x10 Clump (0x01 Struct, 0x0E FrameList, 0x1A GeometryList{0x0F Geometry…}, 0x14 Atomic, 0x03 Extension)
     then trailing F0F00004 / F0F00005 / F0F00001 / F0F00080 / 0x1B AnimAnimation chunks
```
`DATA/FIELD/RMD/M005_001.RMD`: `F0F000E0` ends at `0xC2E`, 2 zero bytes, `0x1B` at `0xC30`.
`DATA/FIELD/GRMD/FOBJ002.RMD`: `F0F000E0` ends at `0xA114`, 12 bytes of `FF` junk, then
`F0F00005` at `0xA120`.

### Rules (inferred, census of all 3,234 files: 132,696 top-level chunks)
* Header `{u32 type, u32 size, u32 libraryID}`; libraryIDs: `0x40000000` on every Atlus
  `F0F0xxxx` chunk, `0x1C020037` (RW 3.7.0.2 build 0x37; `rw::version()`) on RW chunks,
  `0x1C02002D` in 14 files. **Note**: RW ids are Clump `0x10`, FrameList `0x0E`, GeometryList
  `0x1A`, Geometry `0x0F`, Atomic `0x14` (the task brief's `0x0E Atomic / 0x14 Frame List`
  is swapped relative to the RW SDK numbering, which the files follow).
* Chunks are contiguous **except** after an Atlus chunk, where the next header may be padded
  to a 16-byte boundary with zero *or junk* bytes (103 files, all after `F0F000E0`). Rule
  implemented: if the header at the current offset is implausible (type 0/`FFFFFFFF`, libraryID
  not Atlus and not decoding to RW 3.x, or size overrun) and a plausible header exists at
  `align16(offset)`, skip to it. With this all 3,234 files walk to EOF.
* Containers (Clump, FrameList, GeometryList, Geometry, Atomic, MaterialList, Material,
  Texture, TexDictionary, TextureNative, Extension, AnimAnimation, UVAnimDict) are recursed
  only when their children tile the payload exactly; otherwise kept as a leaf.
* Top-level census: `F0F00004` 43,681 · `F0F00005` 26,802 · `F0F00001` 13,451 · `0x1B` 13,223 ·
  `F0F00080` 13,139 · `F0F00003` 8,586 · Clump 3,131 · `F0F000F0` 3,104 · TexDictionary 3,028 ·
  `F0F00006` 1,722 · `0x2B` 1,534 · `F0F000E1` 1,033 · `F0F00070` 246 · `F0F000E0` 16.

### Unknown
* Contents of every Atlus chunk (`F0F000F0` 2-byte value, `F0F000E0/E1` float/name setup,
  `F0F0000x`/`80`/`70` trailing data) and the 0x1B/0x2B animation payloads; geometry, PS2
  native texture (`0x15`) and skin/HAnim decoding are not attempted (Phase 2 topic: which RW
  pipelines the ELF uses).

---

## 6. CRI ADX (601 files; all big-endian)

### Layout (observed, `BGM/0501.ADX`, 99,022 B)

```
+00 80 00   +02 u16 0x24 copyright offset   +04 u8 3 encoding   +05 u8 18 block size
+06 u8 4 bit depth   +07 u8 2 channels   +08 u32 48000   +0C u32 0x15783 samples
+10 u16 500 highpass   +12 u8 4 version   +13 u8 0 flags   +14 u32 0 pad
+18 history 4 B/channel (00 00 00 00 | 00 05 00 05 in SOUND2/BATTLE/BOKO.ADX)
+22 "(c)CRI"  (= copyright offset − 2)      +28 data (= copyright offset + 4)
```
`DATA/SOUND2/EVENT/EVE_149.ADX` (copyright 0x7C, data 0x80, stereo v4): loop block at `0x20`
= `{align 1, enabled 1, begin sample 154,624, begin byte 174,080, end sample 298,496, end byte
335,936}`; `174,080 = 0x80 + (154,624/32)·18·2` confirms the field order.
`DATA/SOUND/VOICE/V000.ADX`: version 3, mono, copyright 0x20 (data 0x24; no room for loop data).

### Rules (inferred, all 601)
* Always encoding 3, block 18, depth 4, highpass 500, flags 0 (no encryption); rates 24,000
  (v3 mono 30 files, v4 mono 32, v4 stereo 420) and 48,000 (v4 stereo 110 + 4 looped). Versions
  3 (30) and 4 (571).
* Frames = ⌈samples/32⌉; body = frames·18·channels. `data + body` lands exactly on an `80 01`
  end block in all 601 (409 files have exactly 18 trailing bytes; the rest are padded further).
* Loop block offset: v3 `0x14`; v4 `0x18 + 4·channels`; present iff `data ≥ loop + 0x18`
  (192 files, all v4 stereo). `AdxHeader::loop` is `nullopt` otherwise.

### Unknown
* v4 **mono** loop layout (vgmstream pads mono history to 8 bytes; no such file on disc) and
  v3 loops (none on disc). ADPCM coefficients/decoding are Phase 3+ (`ADXT/PS2EE Ver.9.44`
  in the ELF).

---

## 7. CRI AFS (366 files; little-endian)

### Layout (observed, `DATA/SOUND/V185002.AFS`, 32,768 B)

```
+00 "AFS\0"   +04 u32 1 count   +08 { u32 0x800 offset, u32 0x69C4 size }
+10 { u32 0x7800 name block offset, u32 0x30 name block size }      (= 8 + 8·count)
+800  member 0: ADX, mono 24 kHz v4
+7800 name record: char name[32] "000_000000_00_", u16 2006,1,18,15,12,12 (Y M D h m s),
      u32 1 (unknown)                                                (48 B per entry)
```

### Rules (inferred, all 366)
* Members are 2048-aligned (all 12,191 members across the 366 archives start `80 00` = ADX); the name-block descriptor
  sits right after the entry table (never at `0x7F8` — that slot holds entry #254 when the
  table is long); the name block starts at `align2048(end of last member)` in 366/366 and is
  `48·count` bytes.

### Unknown
* The u32 at name record `+44` (`AfsEntry::name_record_tail`): 1 in `V185002`; values like
  27,076 / 2,048 / 30,720 recur elsewhere — not the member size or offset of the same entry.

---

## 8. Manifest probe (`tools/ours/formats/probe_manifest.py`)

Stdlib Python; header-level re-implementation of the sniff rules (reads ≤ 1 KiB + one
second-header read per file; 12,019 files in 2.8 s). Writes `parser` and `parser_status` ∈
{`ok`, `partial`, `unsupported`, `error:<msg>`} into `extracted/manifest.json` (gitignored):
`ok` = structure fully parsed by `p3fes_formats` (pak/bf/bmd/tmx, with the file-size /
tiling checks above), `partial` = enumeration/header parser only (rmd/adx/afs),
`unsupported` = no parser yet. Run: `python -I tools/ours/formats/probe_manifest.py`.

```
ext       files     ok  partial  unsupp.  error
.RMD       3234      0     3234        0      0
.PM2       1058      0        0     1058      0
.PM1       1048      0        0     1048      0
.PM3       1042      0        0     1042      0
.PAC        964    964        0        0      0
.BIN        853    836        0        2     15
.TMX        645    645        0        0      0
.ADX        601      0      601        0      0
.BED        581      0        0      581      0
.SE         465    465        0        0      0
.FPC        401    401        0        0      0
.AFS        366      0      366        0      0
.CPK        344    344        0        0      0
.PAK         89     89        0        0      0
.MAP         54      0        0       54      0
.SFD         42      0        0       42      0
.EPL         41      0        0       41      0
.BF          40     40        0        0      0
.SPR         31      0        0       31      0
.IRX         30      0        0       30      0
.SEQ         16      0        0       16      0
.TBL         13      0        0       13      0
.BMD         11     11        0        0      0
.CIN         10      0        0       10      0
(other)      44      2        1       41      0   (.TXT .FNT .BD .HD .SQ .INI .BAT .BVP .FLD .IMG .ANM, 3 no-ext)
TOTAL     12019   3797     4202     4005     15
```
The 15 `error:not a name-first PAK` entries are the known raw `.BIN` tables
(`CARD/GC_BASIC.BIN`, `CARD/PB.BIN`, `EVENT/*TBL.BIN`, `EVENT/AEGIS_SEQ.BIN`, `EVENT/COMUTABLE.BIN`,
`FACILITY/PS_MODEL.BIN`, `FIELD/TABLE/*.BIN`, `BTL/BATTLE/RESULT/BRP_BASE.BIN`,
`BTL/BATTLE/SHUFFLE/SFL_GROUND.BIN`); the 2 `unsupported` `.BIN` are the zero-byte
`BUSTUP/I_B_07CA.BIN` / `I_B_08C8.BIN`. By bytes, `ok + partial` covers everything except
Sofdec video, PM1/2/3 cutscene data and the small table formats.

## 9. Build and test record (2026-10-18)

Run from a VS 2022 x64 developer shell (`VsDevCmd.bat -arch=x64 -host_arch=x64`, Ninja and
CMake on `PATH`), via a batch wrapper:

| Command | Exit |
|---|---|
| `cmake --preset msvc-x64-debug` | 0 |
| `cmake --build --preset msvc-x64-debug` | 0 (no warnings at `/W4`) |
| `ctest --preset msvc-x64-debug` | 0 — `100% tests passed, 0 tests failed out of 1` |
| `build\msvc-x64-debug\bin\p3fes_tests.exe` | 39 test cases, 8,210 assertions, 0 failed, 0 skipped |
| `P3FES_EXTRACTED=<empty dir> p3fes_tests.exe -tc=*PAK*,…` | 0 — 29 cases pass, 9 skipped, 18 fixture `MESSAGE`s |
| `cmake --preset clangcl-x64-debug` / `--build` / `ctest` | 0 / 0 (no warnings) / 0 |
| `python -I tools/ours/formats/probe_manifest.py` | 0 |

Sources: `runtime/include/p3fes/formats/*.h` + `runtime/formats/*.cpp` (1,655 lines),
`tests/formats/*` (995 lines), `tools/ours/formats/probe_manifest.py`. Knowledge sources:
real files above; `tools/third_party/PersonaEditor` (MIT: TMX header, CLUT tiling, BMD/BF
layouts, glyph-index formula) and `tools/third_party/_community-eval/fes-pc-recomp/docs/formats.md`
+ `text-codes.md` (MIT). No code or docs from `Atlus-Script-Tools` (GPL-3) or
`AtlusFileSystemLibrary` (GPL-2) were read.
