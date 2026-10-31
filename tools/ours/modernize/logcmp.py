#!/usr/bin/env python3
"""Compare the modernize pass's logs (docs/MODERNIZE_PLAN.md §3, stage 0).

    python -I logcmp.py reads A.txt B.txt [--by-path]
    python -I logcmp.py scenes A.txt B.txt [--coarse]
    python -I logcmp.py dumps A.bin B.bin [--mask=FILE]
    python -I logcmp.py --selftest

reads   two --read-log files (p3fes/hle/read_log.h). Default: the same reads in the same order, every field but
        the vblank compared (lsn, n, bytes, dst, path, off, fsize, hash, err). --by-path: the same multiset of
        (path, off, bytes, hash) -- what layer 1 (native files) must deliver, whatever the LSNs, buffers and order.
scenes  two --scene-log files (runtime/app/modernize.h): the same lines in the same order, vblank ignored.
        --coarse: only the order of distinct (major, minor, kind, event), entry ignored and repeats collapsed --
        for runs whose loading takes a different number of frames, where two changes the faithful run saw a few
        vblanks apart may land in one sample.
dumps   two --vblank-dump files (runtime/app/modernize.h, layer 2's check) with the same ranges: every vblank both
        have, byte for byte. --mask=FILE leaves out the addresses of a mask file (inclusive "0xA-0xB" ranges, one
        per line, '#' comments; the tracediff --mask format). Prints the vblanks compared, the vblanks that differ
        (the first and last), the differing addresses folded into runs (the first 16), and the vblanks only one has.

Prints the counts and the first difference; exit 0 = same, 1 = different, 2 = bad input. Lines starting with '#'
are comments. Standard library only; run with -I.
"""
from __future__ import annotations

import collections
import os
import sys
import tempfile
from typing import Dict, List, Optional, Sequence, Tuple

READ_KEYS = ("lsn", "n", "bytes", "dst", "path", "off", "fsize", "hash", "err")
SCENE_KEYS = ("major", "minor", "entry", "kind", "event")


class LogError(Exception):
    pass


def parse_line(line: str, where: str) -> Tuple[int, Dict[str, str]]:
    parts = line.split()
    if not parts:
        raise LogError(f"{where}: empty line")
    try:
        vblank = int(parts[0])
    except ValueError:
        raise LogError(f"{where}: no vblank at the start: {line!r}") from None
    fields: Dict[str, str] = {}
    for p in parts[1:]:
        k, sep, v = p.partition("=")
        if not sep or not k:
            raise LogError(f"{where}: not key=value: {p!r}")
        fields[k] = v
    return vblank, fields


def load(path: str) -> List[Tuple[int, int, Dict[str, str]]]:
    """[(line number, vblank, fields)] of the non-comment lines."""
    out = []
    try:
        with open(path, "r", encoding="utf-8", errors="strict") as f:
            for no, raw in enumerate(f, 1):
                line = raw.rstrip("\r\n")
                if not line.strip() or line.lstrip().startswith("#"):
                    continue
                vb, fields = parse_line(line, f"{path}:{no}")
                out.append((no, vb, fields))
    except (OSError, UnicodeDecodeError) as e:
        raise LogError(f"{path}: {e}") from None
    return out


def key_of(fields: Dict[str, str], keys: Sequence[str]) -> Tuple[str, ...]:
    return tuple(fields.get(k, "") for k in keys)


def show(fields: Dict[str, str], keys: Sequence[str]) -> str:
    return " ".join(f"{k}={fields[k]}" for k in keys if k in fields)


def compare_ordered(a, b, keys, label, pa, pb) -> Tuple[bool, str]:
    n = min(len(a), len(b))
    for i in range(n):
        ka, kb = key_of(a[i][2], keys), key_of(b[i][2], keys)
        if ka != kb:
            return False, (f"{label}: first difference at entry {i + 1} of {len(a)} / {len(b)}\n"
                           f"  {pa}:{a[i][0]} (vblank {a[i][1]}): {show(a[i][2], keys)}\n"
                           f"  {pb}:{b[i][0]} (vblank {b[i][1]}): {show(b[i][2], keys)}")
    if len(a) != len(b):
        longer, p, extra = (a, pa, len(a) - n) if len(a) > len(b) else (b, pb, len(b) - n)
        e = longer[n]
        return False, (f"{label}: {pa} has {len(a)} entries, {pb} has {len(b)}; the first {n} match; {p} goes on "
                       f"with {extra} more, from {p}:{e[0]} (vblank {e[1]}): {show(e[2], keys)}")
    return True, f"{label}: SAME ({len(a)} entries, order and content, vblank ignored)"


def compare_reads(pa: str, pb: str, by_path: bool) -> Tuple[bool, str]:
    a, b = load(pa), load(pb)
    if not by_path:
        return compare_ordered(a, b, READ_KEYS, "reads", pa, pb)
    keys = ("path", "off", "bytes", "hash")
    ca = collections.Counter(key_of(f, keys) for _, _, f in a)
    cb = collections.Counter(key_of(f, keys) for _, _, f in b)
    if ca == cb:
        return True, f"reads --by-path: SAME multiset ({len(a)} reads, {len(ca)} distinct (path, off, bytes, hash))"
    only_a, only_b = ca - cb, cb - ca

    def first(lines, missing):
        for no, vb, f in lines:
            if missing.get(key_of(f, keys)):
                return f"line {no} (vblank {vb}): " + " ".join(f"{k}={v}" for k, v in zip(keys, key_of(f, keys)))
        return "-"

    return False, (f"reads --by-path: different multisets ({len(a)} / {len(b)} reads; "
                   f"{sum(only_a.values())} only in {pa}, {sum(only_b.values())} only in {pb})\n"
                   f"  first only in {pa}: {first(a, only_a)}\n"
                   f"  first only in {pb}: {first(b, only_b)}")


def coarse(lines):
    out = []
    keys = ("major", "minor", "kind", "event")
    for no, vb, f in lines:
        k = key_of(f, keys)
        if out and key_of(out[-1][2], keys) == k:
            continue
        out.append((no, vb, {kk: f[kk] for kk in keys if kk in f}))
    return out


def compare_scenes(pa: str, pb: str, coarse_mode: bool) -> Tuple[bool, str]:
    a, b = load(pa), load(pb)
    if coarse_mode:
        return compare_ordered(coarse(a), coarse(b), ("major", "minor", "kind", "event"), "scenes --coarse", pa, pb)
    return compare_ordered(a, b, SCENE_KEYS, "scenes", pa, pb)


# ---- vblank dumps (layer 2) ----------------------------------------------------------------------------------------
DUMP_MAGIC = "# p3fes vblank dump v1: "


def load_dump(path: str) -> Tuple[List[Tuple[int, int]], Dict[int, bytes]]:
    with open(path, "rb") as f:
        data = f.read()
    nl = data.find(b"\n")
    head = data[:nl].decode("ascii", "replace") if nl >= 0 else ""
    if not head.startswith(DUMP_MAGIC):
        raise LogError(f"{path}: not a --vblank-dump file")
    ranges: List[Tuple[int, int]] = []
    for item in head[len(DUMP_MAGIC):].split(","):
        va, _, n = item.partition("+")
        try:
            ranges.append((int(va, 0), int(n, 0)))
        except ValueError:
            raise LogError(f"{path}: bad range '{item}' in the header")
    size = 8 + sum(n for _, n in ranges)
    body = data[nl + 1:]
    if len(body) % size:
        raise LogError(f"{path}: {len(body)} bytes of records is not a multiple of the record size {size}")
    recs: Dict[int, bytes] = {}
    for at in range(0, len(body), size):
        recs[int.from_bytes(body[at:at + 8], "little")] = body[at + 8:at + size]
    return ranges, recs


def load_mask(path: str) -> List[Tuple[int, int]]:
    out: List[Tuple[int, int]] = []
    with open(path, encoding="utf-8") as f:
        for num, line in enumerate(f, 1):
            line = line.split("#", 1)[0].strip()
            if not line:
                continue
            a, sep, b = line.partition("-")
            try:
                out.append((int(a, 0), int(b, 0) if sep else int(a, 0)))
            except ValueError:
                raise LogError(f"{path}:{num}: bad mask range '{line}'")
    return out


def runs_of(addrs: Sequence[int]) -> List[Tuple[int, int]]:
    runs: List[Tuple[int, int]] = []
    for a in sorted(addrs):
        if runs and a == runs[-1][1] + 1:
            runs[-1] = (runs[-1][0], a)
        else:
            runs.append((a, a))
    return runs


def compare_dumps(pa: str, pb: str, mask_path: Optional[str]) -> Tuple[bool, str]:
    ra, a = load_dump(pa)
    rb, b = load_dump(pb)
    if ra != rb:
        raise LogError(f"the two dumps have different ranges ({pa}: {ra}, {pb}: {rb})")
    mask = load_mask(mask_path) if mask_path else []
    # the record offset of every guest address, masked ones left out
    offsets: List[Tuple[int, int]] = []  # (record offset, va)
    at = 0
    masked = 0
    for va, n in ra:
        for i in range(n):
            x = va + i
            if any(lo <= x <= hi for lo, hi in mask):
                masked += 1
            else:
                offsets.append((at + i, x))
        at += n
    common = sorted(set(a) & set(b))
    differ: List[int] = []
    addrs = set()
    for v in common:
        ka, kb = a[v], b[v]
        if ka == kb:
            continue
        bad = [x for off, x in offsets if ka[off] != kb[off]]
        if bad:
            differ.append(v)
            addrs.update(bad)
    only_a, only_b = len(set(a) - set(b)), len(set(b) - set(a))
    span = f"vblanks {common[0]}..{common[-1]}" if common else "no common vblank"
    lines = [f"dumps: {len(common)} vblanks compared ({span}), {len(offsets)} bytes each"
             + (f" ({masked} masked)" if masked else "")
             + f"; {only_a} only in {pa}, {only_b} only in {pb}"]
    if not differ:
        lines.insert(0, f"SAME ({len(common)} vblanks)")
        return True, "\n".join(lines)
    runs = runs_of(sorted(addrs))
    lines.insert(0, f"DIFFERENT: {len(differ)} of {len(common)} vblanks differ (first {differ[0]}, last {differ[-1]}); "
                    f"{len(addrs)} bytes in {len(runs)} runs")
    for lo, hi in runs[:16]:
        lines.append(f"  0x{lo:06X}-0x{hi:06X} ({hi - lo + 1} B)")
    return False, "\n".join(lines)


# ---- self-test ---------------------------------------------------------------------------------------------------
def selftest() -> None:
    checks = 0
    tmp = tempfile.mkdtemp(prefix="logcmp_")

    def write(name: str, text: str) -> str:
        p = os.path.join(tmp, name)
        with open(p, "w", encoding="ascii", newline="\n") as f:
            f.write(text)
        return p

    def expect(result: Tuple[bool, str], same: bool, needle: str = "") -> None:
        nonlocal checks
        ok, msg = result
        assert ok == same, msg
        assert needle in msg, (needle, msg)
        checks += 1

    hdr = "# p3fes read log v1\n# index: 4 outer files, 5 CVM members\n"
    r1 = "10 lsn=100 n=2 bytes=4096 dst=00A00000 path=DATA.CVM:\\A.BIN off=0 fsize=5000 hash=00000000000000AA\n"
    r2 = "12 lsn=300 n=1 bytes=2048 dst=00A08000 path=SLUS_216.21 off=0 fsize=9096860 hash=00000000000000BB\n"
    r3 = "13 lsn=7 n=1 bytes=2048 dst=00A04000 path=- off=14336 fsize=0 hash=- err=48\n"
    base = write("a.txt", hdr + r1 + r2 + r3)
    expect(compare_reads(base, base, False), True, "SAME (3 entries")
    # vblanks differ: still the same
    shifted = write("b.txt", hdr + r1.replace("10 ", "500 ", 1) + r2.replace("12 ", "900 ", 1) + r3.replace("13 ", "901 ", 1))
    expect(compare_reads(base, shifted, False), True)
    # a different hash: reported at entry 2
    badhash = write("c.txt", hdr + r1 + r2.replace("hash=00000000000000BB", "hash=00000000000000BC") + r3)
    expect(compare_reads(base, badhash, False), False, "first difference at entry 2")
    # reordered: different in order, same by path
    swapped = write("d.txt", hdr + r2 + r1 + r3)
    expect(compare_reads(base, swapped, False), False, "entry 1")
    expect(compare_reads(base, swapped, True), True, "SAME multiset (3 reads")
    # other LSN and buffer, same path / off / bytes / hash: same by path, different in order mode
    moved = write("e.txt", hdr + r1.replace("lsn=100", "lsn=4194403").replace("dst=00A00000", "dst=01000000") + r2 + r3)
    expect(compare_reads(base, moved, False), False, "lsn=4194403")
    expect(compare_reads(base, moved, True), True)
    # a missing read
    short = write("f.txt", hdr + r1 + r2)
    expect(compare_reads(base, short, False), False, "has 3 entries")
    expect(compare_reads(base, short, True), False, "1 only in")
    # a duplicated read counts in the multiset
    dup = write("g.txt", hdr + r1 + r1 + r2 + r3)
    expect(compare_reads(base, dup, True), False, "0 only in")

    s = ("# p3fes scene log v1\n"
         "0 major=-1 minor=-1 entry=- kind=none\n"
         "1595 major=32 minor=2 entry=- kind=field\n"
         "1600 major=32 minor=2 entry=1 kind=field\n"
         "2631 major=51 minor=1 entry=0 kind=event event=139\n"
         "4700 major=251 minor=1 entry=0 kind=battle\n")
    sa = write("s1.txt", s)
    sb = write("s2.txt", s.replace("1595 ", "40 ").replace("4700 ", "4000 "))
    expect(compare_scenes(sa, sb, False), True, "SAME (5 entries")
    sc = write("s3.txt", s.replace("event=139", "event=140"))
    expect(compare_scenes(sa, sc, False), False, "entry 4")
    # the entry appearing in the same sample as the scene: different exactly, same coarse
    sd = write("s4.txt", s.replace("1595 major=32 minor=2 entry=- kind=field\n", ""))
    expect(compare_scenes(sa, sd, False), False)
    expect(compare_scenes(sa, sd, True), True, "SAME (4 entries")
    # scenes in another order: different even coarse
    se = write("s5.txt", "0 major=-1 minor=-1 entry=- kind=none\n2631 major=51 minor=1 entry=0 kind=event event=139\n"
                         "3000 major=32 minor=2 entry=1 kind=field\n4700 major=251 minor=1 entry=0 kind=battle\n")
    expect(compare_scenes(sa, se, True), False, "entry 2")
    # malformed input
    bad = write("bad.txt", "x lsn=1\n")
    try:
        load(bad)
        raise AssertionError("malformed line accepted")
    except LogError as e:
        assert "no vblank" in str(e)
        checks += 1

    def dump(name: str, ranges: str, recs: Sequence[Tuple[int, bytes]]) -> str:
        p = os.path.join(tmp, name)
        with open(p, "wb") as f:
            f.write((DUMP_MAGIC + ranges + "\n").encode("ascii"))
            for v, body in recs:
                f.write(v.to_bytes(8, "little") + body)
        return p

    rng = "0x100+4,0x200+2"
    da = dump("d1.bin", rng, [(1, bytes([1, 2, 3, 4, 5, 6])), (2, bytes([1, 2, 3, 4, 5, 6]))])
    expect(compare_dumps(da, da, None), True, "SAME (2 vblanks)")
    db = dump("d2.bin", rng, [(1, bytes([1, 2, 3, 4, 5, 6])), (2, bytes([1, 9, 9, 4, 5, 7])), (3, bytes(6))])
    expect(compare_dumps(da, db, None), False, "first 2, last 2")
    expect(compare_dumps(da, db, None), False, "0x000101-0x000102 (2 B)")
    expect(compare_dumps(da, db, None), False, "0x000201-0x000201")
    expect(compare_dumps(da, db, None), False, "1 only in")
    mask = write("m.txt", "# comment\n0x101-0x102\n0x201\n")
    expect(compare_dumps(da, db, mask), True, "(3 masked)")
    other = dump("d3.bin", "0x100+6", [(1, bytes(6))])
    try:
        compare_dumps(da, other, None)
        raise AssertionError("different ranges accepted")
    except LogError as e:
        assert "different ranges" in str(e)
        checks += 1
    print(f"logcmp selftest: {checks} checks passed")


def main(argv: List[str]) -> int:
    if argv == ["--selftest"]:
        selftest()
        return 0
    mask = None
    for a in argv:
        if a.startswith("--mask="):
            mask = a[len("--mask="):]
    flags = {a.split("=", 1)[0] for a in argv if a.startswith("--")}
    args = [a for a in argv if not a.startswith("--")]
    if len(args) != 3 or args[0] not in ("reads", "scenes", "dumps"):
        print("usage:\n" + "\n".join(__doc__.strip().splitlines()[2:6]), file=sys.stderr)
        return 2
    allowed = {"reads": {"--by-path"}, "scenes": {"--coarse"}, "dumps": {"--mask"}}[args[0]]
    if flags - allowed:
        print(f"logcmp: unknown option(s) for {args[0]}: {' '.join(sorted(flags - allowed))}", file=sys.stderr)
        return 2
    try:
        if args[0] == "reads":
            ok, msg = compare_reads(args[1], args[2], "--by-path" in flags)
        elif args[0] == "scenes":
            ok, msg = compare_scenes(args[1], args[2], "--coarse" in flags)
        else:
            ok, msg = compare_dumps(args[1], args[2], mask)
    except LogError as e:
        print(f"logcmp: {e}", file=sys.stderr)
        return 2
    print(msg)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
