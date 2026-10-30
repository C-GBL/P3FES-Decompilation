#!/usr/bin/env python3
"""Re-create the 114 VU1 microcode dumps from the ELF (stdlib only).

The census (docs/ANALYSIS/09, 14 §1) was taken from `ida/logs/vu1/<code_va>.bin`, which IDA scripts wrote on an
earlier machine and which are gitignored. This script rebuilds them straight from the retail ELF: every program is a
RenderWare DMA `ret` packet at `tag_va` (symbols/vu1_micro_census.json): the tag's QWC gives the packet size, the
VIFcodes start in the tag's upper 64 bits (tag_va + 8), and the microcode is the payload of every `MPG` code
(cmd 0x4A, NUM pairs, NUM 0 = 256) concatenated in order; `NOP` codes are skipped. Each dump is checked against the
census row (`bytes` and `sha256_16`); any mismatch is an error.

Usage: python -I tools/ours/vu1/vu1_dump.py --elf <SLUS_216.21> [--repo DIR] [--out DIR]
       (default out: <repo>/ida/logs/vu1, the directory tests/vu1 reads; P3FES_VU1_DUMPS can point elsewhere)
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import struct
import sys


def load_segments(elf: bytes):
    if elf[:4] != b"\x7fELF" or elf[4] != 1 or elf[5] != 1:
        raise SystemExit("not a 32-bit little-endian ELF")
    phoff, = struct.unpack_from("<I", elf, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", elf, 0x2A)
    segs = []
    for k in range(phnum):
        p_type, p_offset, p_vaddr, _p_paddr, p_filesz = struct.unpack_from("<IIIII", elf, phoff + k * phentsize)
        if p_type == 1:
            segs.append((p_vaddr, p_offset, p_filesz))
    return segs


def va_bytes(elf: bytes, segs, va: int, n: int) -> bytes:
    for vaddr, off, size in segs:
        if vaddr <= va and va + n <= vaddr + size:
            return elf[off + va - vaddr: off + va - vaddr + n]
    raise SystemExit(f"VA 0x{va:x}+{n} outside the loaded segments")


def extract(elf: bytes, segs, tag_va: int) -> bytes:
    tag = struct.unpack("<Q", va_bytes(elf, segs, tag_va, 8))[0]
    qwc = tag & 0xFFFF
    if (tag >> 28) & 7 != 6:
        raise SystemExit(f"0x{tag_va:x}: DMA tag ID is not ret")
    end = tag_va + 16 + qwc * 16
    pos = tag_va + 8
    code = bytearray()
    while pos + 4 <= end:
        w, = struct.unpack("<I", va_bytes(elf, segs, pos, 4))
        pos += 4
        cmd = (w >> 24) & 0x7F
        if cmd == 0x00:
            continue
        if cmd != 0x4A:
            raise SystemExit(f"0x{tag_va:x}: unexpected VIFcode 0x{w:08x} at 0x{pos - 4:x}")
        num = (w >> 16) & 0xFF or 256
        addr = w & 0xFFFF
        if addr * 8 != len(code):
            raise SystemExit(f"0x{tag_va:x}: MPG piece at pair {addr}, expected {len(code) // 8}")
        code += va_bytes(elf, segs, pos, num * 8)
        pos += num * 8
    return bytes(code)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--elf", required=True)
    ap.add_argument("--repo", default=os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")))
    ap.add_argument("--out")
    a = ap.parse_args()
    out = a.out or os.path.join(a.repo, "ida", "logs", "vu1")
    with open(a.elf, "rb") as fh:
        elf = fh.read()
    segs = load_segments(elf)
    with open(os.path.join(a.repo, "symbols", "vu1_micro_census.json"), encoding="utf-8") as fh:
        census = json.load(fh)
    os.makedirs(out, exist_ok=True)
    bad = 0
    for p in census["programs"]:
        tag_va = int(p["tag_va"], 16)
        code = extract(elf, segs, tag_va)
        ok = len(code) == p["bytes"] and hashlib.sha256(code).hexdigest()[:16] == p["sha256_16"]
        if not ok:
            bad += 1
            print(f"MISMATCH {p['name']}: {len(code)} bytes, sha256 {hashlib.sha256(code).hexdigest()[:16]}")
            continue
        with open(os.path.join(out, f"{int(p['code_va'], 16):08x}.bin"), "wb") as fh:
            fh.write(code)
    print(f"vu1_dump: {len(census['programs']) - bad} of {len(census['programs'])} programs written to {out}, {bad} mismatches")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
