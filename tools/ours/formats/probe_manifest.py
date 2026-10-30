#!/usr/bin/env python3
"""Set `parser_status` / `parser` on every entry of extracted/manifest.json.

Header-level re-implementation of the identification rules in runtime/formats/
(the C++ library and tests/formats/ are authoritative for correctness; this
script only sniffs headers so a 4.5 GB extraction probes in seconds). Reads at
most a few KiB per file.

parser_status values:
  ok            structure fully covered by a runtime/formats parser (pak, bf, bmd, tmx)
  partial       header/enumeration parser only (rmd chunk walk, adx header, afs table)
  unsupported   identified or extension-known format without a parser yet
  error:<msg>   expected one of our formats (by extension/sniff) but the header failed

Usage: python -I tools/ours/formats/probe_manifest.py [--manifest PATH] [--dry-run]
"""
from __future__ import annotations

import argparse
import collections
import json
import os
import struct
import sys

PAK_EXTS = {".PAC", ".BIN", ".FPC", ".CPK", ".SE", ".PAK"}
KNOWN_UNSUPPORTED = {
    ".SFD": "sofdec-mpeg", ".PM1": "pm1", ".PM2": "pm2", ".PM3": "pm3", ".BED": "bed4",
    ".SPR": "spr0", ".EPL": "epl", ".CIN": "cin", ".TBL": "tbl", ".MAP": "map", ".FNT": "fnt",
    ".HD": "iecs-hd", ".BD": "iecs-bd", ".SQ": "iecs-sq", ".IRX": "elf-irx", ".IMG": "romdir",
    ".BVP": "bvp", ".FLD": "fld", ".ANM": "anm", ".SEQ": "text", ".TXT": "text", ".INI": "text",
    ".BAT": "text",
}


def read_head(path: str, n: int) -> bytes:
    with open(path, "rb") as f:
        return f.read(n)


def read_at(path: str, off: int, n: int) -> bytes:
    with open(path, "rb") as f:
        f.seek(off)
        return f.read(n)


def printable_name(field: bytes) -> str | None:
    nm = field.split(b"\0", 1)[0]
    if not nm or len(nm) == len(field):
        return None
    if any(c < 0x20 or c > 0x7E for c in nm):
        return None
    return nm.decode("ascii")


def probe(path: str, size: int, ext: str) -> tuple[str, str]:
    """Returns (parser, status)."""
    if size == 0:
        return "", "unsupported"  # zero-byte file (2 BUSTUP .BINs)
    head = read_head(path, 0x400)

    # --- BF (FLW0)
    if len(head) >= 0x20 and head[8:12] == b"FLW0":
        nsec = struct.unpack_from("<I", head, 0x10)[0]
        if nsec == 0 or nsec > 64 or len(head) < 0x20 + 16 * nsec:
            return "bf", "error:section table"
        pos = 0x20 + 16 * nsec
        for i in range(nsec):
            t, es, ec, off = struct.unpack_from("<IIII", head, 0x20 + 16 * i)
            if off != pos:
                return "bf", "error:sections not contiguous"
            pos = off + es * ec
        if pos != size:
            return "bf", "error:sections do not tile file"
        return "bf", "ok"

    # --- BMD (MSG1)
    if len(head) >= 0x20 and head[8:12] == b"MSG1" and struct.unpack_from("<I", head, 0)[0] == 7:
        fsize, _, _, relpos, relsize, count, ver = struct.unpack_from("<IIIIIII", head, 4)
        if ver != 0x20000:
            return "bmd", "error:version"
        if fsize != size or relpos + relsize != size:
            return "bmd", "error:size/relocation table"
        return "bmd", "ok"

    # --- TMX
    if len(head) >= 0x40 and head[8:12] == b"TMX0" and struct.unpack_from("<H", head, 0)[0] == 2:
        fsize, = struct.unpack_from("<I", head, 4)
        npal, palfmt, w, h, pxfmt, nmip = struct.unpack_from("<BBHHBB", head, 0x10)
        bpp = {0: 32, 1: 24, 2: 16, 0x0A: 16, 0x13: 8, 0x14: 4}.get(pxfmt)
        if bpp is None or nmip:
            return "tmx", "error:unsupported psm/mipmaps"
        colours = {0x13: 256, 0x14: 16}.get(pxfmt, 0)
        palbpp = {0: 32, 2: 16, 0x0A: 16}.get(palfmt, 0) if colours else 0
        if colours and (npal == 0 or palbpp == 0):
            return "tmx", "error:palette"
        expect = 0x40 + colours * palbpp // 8 * npal + (w * h * bpp + 7) // 8
        if expect != size or fsize != size:
            return "tmx", "error:size"
        return "tmx", "ok"

    # --- AFS
    if head[:4] == b"AFS\0" and len(head) >= 8:
        count, = struct.unpack_from("<I", head, 4)
        table = read_at(path, 8, 8 * count + 8)
        if len(table) < 8 * count + 8:
            return "afs", "error:entry table"
        for i in range(count):
            off, sz = struct.unpack_from("<II", table, 8 * i)
            if off + sz > size:
                return "afs", "error:entry overrun"
        npos, nsz = struct.unpack_from("<II", table, 8 * count)
        if npos and npos + nsz > size:
            return "afs", "error:name block"
        return "afs", "partial"

    # --- ADX
    if len(head) >= 0x14 and head[:2] == b"\x80\x00":
        coff, = struct.unpack_from(">H", head, 2)
        enc, bs, bd, ch = struct.unpack_from("BBBB", head, 4)
        sr, ns = struct.unpack_from(">II", head, 8)
        ver = head[0x12]
        if coff < 0x14 or read_at(path, coff - 2, 6) != b"(c)CRI":
            return "adx", "error:(c)CRI"
        if ver not in (3, 4) or bs == 0 or ch == 0:
            return "adx", "error:header"
        if coff + 4 + ((ns + 31) // 32) * bs * ch > size:
            return "adx", "error:body overrun"
        return "adx", "partial"

    # --- RMD (RenderWare / Atlus chunk)
    if len(head) >= 12:
        t, s, lib = struct.unpack_from("<III", head, 0)
        rw_ok = lib == 0x40000000 or 0x30000 <= (((lib >> 14) & 0x3FF00) + 0x30000 + ((lib >> 16) & 0x3F)) < 0x40000
        if t not in (0, 0xFFFFFFFF) and rw_ok and ((t & 0xFFFF0000) == 0xF0F00000 or t in (0x10, 0x16, 0x1B, 0x2B)):
            if 12 + s > size:
                return "rmd", "error:first chunk overrun"
            return "rmd", "partial"

    # --- PAK (name-first container). Same rule as looks_like_pak(): the first
    # name is printable and has an extension, its payload fits, and at
    # align64(256 + size) there is another valid header, a terminator, or EOF.
    if len(head) >= 256:
        nm = printable_name(head[:252])
        psize, = struct.unpack_from("<I", head, 252)
        if nm is not None and "." in nm and 256 + psize <= size:
            nxt = (256 + psize + 63) // 64 * 64
            if nxt == size:
                return "pak", "ok"  # EOF-terminated (5 cut-in .CPKs)
            h2 = read_at(path, nxt, 256)
            if len(h2) == 256:
                s2, = struct.unpack_from("<I", h2, 252)
                if h2[0] == 0 and s2 == 0:
                    return "pak", "ok"
                n2 = printable_name(h2[:252])
                if n2 is not None and nxt + 256 + s2 <= size:
                    return "pak", "ok"
        if size == 256 and not any(head[:256]):
            return "pak", "ok"  # terminator-only pack

    if ext in PAK_EXTS:
        return "pak", "error:not a name-first PAK"
    if ext == ".RMD":
        return "rmd", "error:no RenderWare chunk header"
    if ext == ".ADX":
        return "adx", "error:not ADX"
    if ext == ".TMX":
        return "tmx", "error:not TMX0"
    if ext in (".BF", ".BMD"):
        return ext[1:].lower(), "error:bad magic"
    return KNOWN_UNSUPPORTED.get(ext, ""), "unsupported"


def main() -> int:
    ap = argparse.ArgumentParser()
    here = os.path.dirname(os.path.abspath(__file__))
    repo = os.path.abspath(os.path.join(here, "..", "..", ".."))
    ap.add_argument("--manifest", default=os.path.join(repo, "extracted", "manifest.json"))
    ap.add_argument("--dry-run", action="store_true", help="do not write the manifest back")
    args = ap.parse_args()

    with open(args.manifest, "r", encoding="utf-8") as f:
        raw = f.read()
    manifest = json.loads(raw)
    root = os.path.dirname(os.path.abspath(args.manifest))
    entries = manifest["entries"]

    by_ext: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
    errors: list[tuple[str, str]] = []
    for e in entries:
        path = os.path.join(root, e["path"].replace("/", os.sep))
        ext = e.get("ext") or os.path.splitext(e["path"])[1].upper()
        if not os.path.isfile(path):
            parser, status = "", "error:missing file"
        else:
            try:
                parser, status = probe(path, e["size"], ext)
            except (OSError, struct.error) as ex:  # noqa: PERF203
                parser, status = "", f"error:{type(ex).__name__}"
        e["parser"] = parser
        e["parser_status"] = status
        key = status.split(":", 1)[0]
        by_ext[ext or "(none)"][key] += 1
        by_ext[ext or "(none)"]["_total"] += 1
        if key == "error":
            errors.append((e["path"], status))

    if not args.dry_run:
        # Preserve the file's indentation style if it was pretty-printed.
        indent = 2 if raw[:200].count("\n") > 1 else None
        with open(args.manifest, "w", encoding="utf-8") as f:
            json.dump(manifest, f, indent=indent, ensure_ascii=False)
            if indent:
                f.write("\n")

    cols = ["_total", "ok", "partial", "unsupported", "error"]
    print(f"{'ext':<8}{'files':>7}{'ok':>7}{'partial':>9}{'unsupp.':>9}{'error':>7}")
    totals = collections.Counter()
    for ext in sorted(by_ext, key=lambda k: -by_ext[k]["_total"]):
        c = by_ext[ext]
        totals.update(c)
        print(f"{ext:<8}{c['_total']:>7}{c['ok']:>7}{c['partial']:>9}{c['unsupported']:>9}{c['error']:>7}")
    print(f"{'TOTAL':<8}{totals['_total']:>7}{totals['ok']:>7}{totals['partial']:>9}{totals['unsupported']:>9}{totals['error']:>7}")
    if errors:
        print("\nerrors:")
        for p, s in errors[:40]:
            print(f"  {p}: {s}")
        if len(errors) > 40:
            print(f"  ... {len(errors) - 40} more")
    return 0


if __name__ == "__main__":
    sys.exit(main())
