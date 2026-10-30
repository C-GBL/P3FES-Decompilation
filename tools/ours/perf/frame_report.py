#!/usr/bin/env python3
"""Folds p3fes --frame-log CSVs (runtime/app/frame_telemetry.h, docs/ANALYSIS/31_frame_pacing.md) into a table.

    python -I tools/ours/perf/frame_report.py RUN.csv [RUN2.csv ...] [--seg name=A:B ...] [--md]

Per file (and per --seg vblank range): guest frames, new-frame interval p50 / p95 / p99 / max, hitches (> 34 ms),
frames held 2 display refreshes (DXGI), host work p50 / p95 and how many frames fit the 33.37 ms budget, and the
pacing quality of the frames that fit ("fit: p99 / hitches"): what the pacing alone delivers, separated from frames
that were too expensive (the other tracks' work) or descheduled by machine load (work - cpu > 30 % and > 5 ms).
"""
import csv
import math
import sys

VBLANK_MS = 1001.0 / 60.0


def pct(v, p):
    if not v:
        return float('nan')
    v = sorted(v)
    i = max(1, math.ceil(p / 100.0 * len(v)))
    return v[min(len(v), i) - 1]


def load(path):
    with open(path, newline='', encoding='utf-8-sig') as f:
        return list(csv.DictReader(f))


def fold(rows, name):
    iv = [float(r['interval_ms']) for r in rows if float(r['interval_ms']) >= 0]
    work = [float(r['work_ms']) for r in rows]
    refs = [int(r['refreshes']) for r in rows if int(r['refreshes']) > 0]
    fit_iv, load_n, fit_n = [], 0, 0
    prev_fit = False
    for r in rows:
        gv = max(2, int(r['guest_vblanks']))
        w, c = float(r['work_ms']), float(r['cpu_ms'])
        fit = w <= gv * VBLANK_MS
        if fit:
            fit_n += 1
            # The frame and its predecessor both fit (no inherited lateness), the game itself at 30 fps.
            if prev_fit and float(r['interval_ms']) >= 0 and int(r['guest_vblanks']) == 2:
                fit_iv.append(float(r['interval_ms']))
        elif w - c > 5.0 and w - c > 0.3 * w:
            load_n += 1
        prev_fit = fit
    two = sum(1 for x in refs if x == 2)
    return {
        'name': name, 'frames': len(rows),
        'p50': pct(iv, 50), 'p95': pct(iv, 95), 'p99': pct(iv, 99), 'max': max(iv) if iv else float('nan'),
        'hitches': sum(1 for x in iv if x > 34.0),
        'refresh2': f"{two}/{len(refs)}" if refs else '-',
        'work50': pct(work, 50), 'work95': pct(work, 95),
        'fit': f"{fit_n}/{len(rows)}", 'load': load_n,
        'fit_p99': pct(fit_iv, 99), 'fit_hitch': sum(1 for x in fit_iv if x > 34.0), 'fit_n': len(fit_iv),
    }


def main(argv):
    files, segs, md = [], [], False
    i = 0
    while i < len(argv):
        a = argv[i]
        if a == '--seg':
            n, rng = argv[i + 1].split('=')
            lo, hi = rng.split(':')
            segs.append((n, int(lo), int(hi)))
            i += 2
            continue
        if a == '--md':
            md = True
        else:
            files.append(a)
        i += 1
    out = []
    for f in files:
        rows = load(f)
        out.append(fold(rows, f.replace('\\', '/').split('/')[-1]))
        for n, lo, hi in segs:
            sub = [r for r in rows if lo <= int(r['vblank']) < hi]
            if sub:
                out.append(fold(sub, '  ' + n))
    cols = ['name', 'frames', 'p50', 'p95', 'p99', 'max', 'hitches', 'refresh2', 'work50', 'work95', 'fit', 'load',
            'fit_p99', 'fit_hitch']
    fmt = lambda v: f"{v:.1f}" if isinstance(v, float) else str(v)
    if md:
        print('| ' + ' | '.join(cols) + ' |')
        print('|' + '---|' * len(cols))
        for r in out:
            print('| ' + ' | '.join(fmt(r[c]) for c in cols) + ' |')
    else:
        print(' '.join(f"{c:>10}" for c in cols))
        for r in out:
            print(' '.join(f"{fmt(r[c]):>10}" for c in cols))


if __name__ == '__main__':
    main(sys.argv[1:])
