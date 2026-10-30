#!/usr/bin/env python3
"""Name the differing runs of two EE RAM images with symbols/p3fes.sym (data/bss bands), for the
snapshot-diff write-ups (docs/INTEGRATION_LOG.md). Not a replacement for `tracediff snapshot`: this is the
"which globals differ" view that the per-band totals do not give.

  python -I tools/ours/tracediff/classify_runs.py REF.bin OURS.bin [--sym symbols/p3fes.sym]
         [--lo 0x5A1400] [--hi 0x9ACC80] [--dead-stack capture.json] [--top 60]

Compares [lo, hi) (default: the ELF's data + bss bands), skips the kernel area and, with --dead-stack, each
thread's stack below its saved frame (same rule as tracediff --dead-stack), merges differing bytes into runs,
attributes each run to the nearest preceding named data symbol (D rows of p3fes.sym; F rows for code), and prints
the runs grouped by symbol with byte totals.
"""
import argparse
import bisect
import json
import re
import sys

KSEG_MASK = 0x1FFFFFFF


def load_syms(path):
    rows = []
    for line in open(path, encoding='utf-8', errors='replace'):
        if not line or line[0] == '#':
            continue
        parts = line.split()
        if len(parts) < 4:
            continue
        try:
            addr = int(parts[0], 16)
            size = int(parts[1], 16)
        except ValueError:
            continue
        rows.append((addr, size, parts[2], parts[3]))
    rows.sort()
    return rows


def dead_stack_ranges(capture_path):
    cap = json.load(open(capture_path, encoding='utf-8'))
    cur = cap.get('current_thread', 0)
    sp = int(cap.get('sp', '0'), 16) if isinstance(cap.get('sp'), str) else int(cap.get('sp', 0))
    out = []
    for t in cap.get('threads', []):
        stack = int(t['stack'], 16)
        size = int(t['stack_size'], 16)
        frame = int(t['frame'], 16)
        bound = sp if (cur and t['tid'] == cur and sp) else frame
        bound = min(bound, stack + size)
        if bound > stack:
            out.append((stack & KSEG_MASK, bound & KSEG_MASK))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('ref')
    ap.add_argument('ours')
    ap.add_argument('--sym', default='symbols/p3fes.sym')
    ap.add_argument('--lo', default='0x5A1400')
    ap.add_argument('--hi', default='0x9ACC80')
    ap.add_argument('--dead-stack', action='append', default=[])
    ap.add_argument('--top', type=int, default=60)
    a = ap.parse_args()
    lo, hi = int(a.lo, 16), int(a.hi, 16)
    ref = open(a.ref, 'rb').read()
    ours = open(a.ours, 'rb').read()
    if len(ref) != len(ours):
        sys.exit('images differ in size')
    masked = [(0, 0x100000)]
    for c in a.dead_stack:
        masked += dead_stack_ranges(c)
    masked.sort()

    def is_masked(off):
        i = bisect.bisect_right(masked, (off, 1 << 40)) - 1
        return i >= 0 and masked[i][0] <= off < masked[i][1]

    syms = load_syms(a.sym)
    addrs = [s[0] for s in syms]

    def name_of(off):
        i = bisect.bisect_right(addrs, off) - 1
        if i < 0:
            return '?', off
        addr, size, kind, name = syms[i]
        return (name if off < addr + max(size, 1) else name + '+'), off - addr

    runs = []
    i = lo
    while i < hi:
        if ref[i] != ours[i] and not is_masked(i):
            j = i
            while j < hi and ref[j] != ours[j] and not is_masked(j):
                j += 1
            runs.append((i, j - i))
            i = j
        else:
            i += 1
    by_sym = {}
    for off, n in runs:
        name, delta = name_of(off)
        e = by_sym.setdefault(name, [0, 0, off])
        e[0] += n
        e[1] += 1
    total = sum(n for _, n in runs)
    print(f'range 0x{lo:08X}-0x{hi:08X}: {total} differing bytes in {len(runs)} runs, {len(by_sym)} symbols')
    for name, (bytes_, nruns, first) in sorted(by_sym.items(), key=lambda kv: -kv[1][0])[:a.top]:
        print(f'  {bytes_:7d} B {nruns:5d} runs  0x{first:08X}  {name}')


if __name__ == '__main__':
    main()
