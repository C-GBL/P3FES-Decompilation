#!/usr/bin/env python3
"""Fold a `p3fes --zones FILE` report (runtime/app/host_zones.h) into named vblank ranges and print Markdown tables:
wall time and speed per range, the share of each zone, workload per vblank and per flip, and the VU1 programs a
range ran. Ranges snap to the report's segment boundaries (a segment belongs to the range that holds its start).

  python -I tools/ours/perf/zones_report.py ZONES.tsv [--seg NAME=A:B ...] [--vu1 NAME ...] [--top 12]

Without --seg every segment is its own range. Example (the battle route, docs/ANALYSIS/23 §1.3):
  --seg boot=0:1100 --seg title=1100:1600 --seg field2F=3950:4600 --seg battle=4600:6150 --seg results=6150:6300
  --seg field_after=6300:6800 --vu1 battle --vu1 field2F
"""
import argparse
import sys

VBLANK_HZ = 59.94
ZONES = ['host', 'ee', 'kernel', 'fiber', 'hw_dmac', 'vif1', 'vu1', 'gif', 'gs_raster', 'gs_upload', 'gs_crtc', 'ipu',
         'iop', 'iop_cpu', 'audio', 'cdvd', 'present', 'gs_submit', 'gs_wait']
WORK = ['flips', 'prims', 'point', 'line', 'linestrip', 'tri', 'tristrip', 'trifan', 'sprite', 'pixels', 'tex_pixels',
        'bilinear_pixels', 'image_qw_in', 'image_qw_out', 'local_copies', 'clut_loads', 'gs_reg_writes', 'gif_p1_qw',
        'gif_p2_qw', 'gif_p3_qw', 'vu1_runs', 'vu1_pairs', 'mpg_pairs', 'vu1_kicks', 'vu1_kick_qw', 'iop_insns',
        'signal_p1', 'signal_p2', 'signal_p3', 'finish_p1', 'finish_p2', 'finish_p3']
PRIMS = ['point', 'line', 'linestrip', 'tri', 'tristrip', 'trifan', 'sprite']
RASTER = ['px_' + p for p in PRIMS] + ['ms_' + p for p in PRIMS]


def load(path):
    segs, vu1, header = [], [], None
    for line in open(path, encoding='utf-8'):
        line = line.rstrip('\n')
        if not line or line.startswith('#'):
            continue
        f = line.split('\t')
        if f[0] == 'seg':
            header = f
        elif f[0] == 'vu1':
            name = f[3].split()[-1].replace('+0x0', '')  # "0x006F8B10 vu1_prog_064_g3_skin+0x0"
            vu1.append({'seg': int(f[1]), 'key': f[2], 'name': name, 'runs': int(f[4]), 'pairs': int(f[5]),
                        'ms': float(f[6]) if len(f) > 6 else 0.0})
        elif header:
            row = {}
            for k, v in zip(header, f):
                if k == 'tasks':  # running kwln task names (text; tools/ours/perf/bench.py classifies by them)
                    row[k] = v
                    continue
                row[k] = float(v) if ('.' in v or k in ZONES or k.startswith('ms_') or k in ('wall_s', 'speed')) else int(v)
            segs.append(row)
    return segs, vu1


def fmt(x, d=1):
    return f'{x:,.{d}f}'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('report')
    ap.add_argument('--seg', action='append', default=[], help='NAME=A:B (vblanks)')
    ap.add_argument('--vu1', action='append', default=[], help='range NAME whose VU1 programs to list')
    ap.add_argument('--top', type=int, default=12)
    a = ap.parse_args()
    segs, vu1 = load(a.report)
    if not segs:
        sys.exit('no segments in ' + a.report)
    ranges = []
    for s in a.seg:
        name, span = s.split('=')
        lo, hi = (int(x) for x in span.split(':'))
        ranges.append((name, lo, hi))
    if not ranges:
        ranges = [(f"{s['v0']}-{s['v1']}", s['v0'], s['v1']) for s in segs]

    agg = []
    for name, lo, hi in ranges:
        rows = [s for s in segs if lo <= s['v0'] < hi]
        if not rows:
            continue
        t = {'name': name, 'v0': rows[0]['v0'], 'v1': rows[-1]['v1'], 'ids': {s['seg'] for s in rows}}
        for k in ['wall_s'] + ZONES + WORK + RASTER:
            t[k] = sum(s.get(k, 0) for s in rows)
        t['vblanks'] = t['v1'] - t['v0']
        t['speed'] = t['vblanks'] / VBLANK_HZ / t['wall_s'] if t['wall_s'] else 0
        agg.append(t)

    print('| Range | vblanks | wall s | x real time | ms / vblank |')
    print('|---|---|---|---|---|')
    for t in agg:
        print(f"| {t['name']} ({t['v0']}-{t['v1']}) | {t['vblanks']} | {fmt(t['wall_s'], 2)} | {fmt(t['speed'], 3)} | "
              f"{fmt(1e3 * t['wall_s'] / t['vblanks'], 2)} |")
    print()
    print('Zone share (% of the zone total; ms per vblank in brackets):')
    print()
    print('| Zone | ' + ' | '.join(t['name'] for t in agg) + ' |')
    print('|---|' + '---|' * len(agg))
    for z in ZONES:
        if not any(t[z] for t in agg):
            continue
        cells = []
        for t in agg:
            tot = sum(t[k] for k in ZONES)
            cells.append(f"{100 * t[z] / tot:.1f} ({t[z] / t['vblanks']:.2f})" if tot else '-')
        print(f'| {z} | ' + ' | '.join(cells) + ' |')
    print()
    print('Workload per vblank (per flip in brackets where the game flips):')
    print()
    print('| Counter | ' + ' | '.join(t['name'] for t in agg) + ' |')
    print('|---|' + '---|' * len(agg))
    for k in WORK:
        if not any(t[k] for t in agg):
            continue
        cells = []
        for t in agg:
            pv = t[k] / t['vblanks']
            pf = t[k] / t['flips'] if t['flips'] else 0
            cells.append(f'{fmt(pv, 1)} ({fmt(pf, 1)})' if k != 'flips' else f'{fmt(pv, 3)}')
        print(f'| {k} | ' + ' | '.join(cells) + ' |')
    if any(t['ms_tristrip'] for t in agg):
        print()
        print('GS raster by primitive type (per flip: primitives / pixels written / raster ms; ns per pixel):')
        print()
        print('| Type | ' + ' | '.join(t['name'] for t in agg) + ' |')
        print('|---|' + '---|' * len(agg))
        for p in PRIMS:
            if not any(t[p] for t in agg):
                continue
            cells = []
            for t in agg:
                fl = t['flips'] or 1
                px, ms = t['px_' + p], t['ms_' + p]
                ns = 1e6 * ms / px if px else 0
                cells.append(f"{fmt(t[p] / fl, 0)} / {fmt(px / fl, 0)} / {ms / fl:.2f} ms; {ns:.0f} ns/px")
            print(f'| {p} | ' + ' | '.join(cells) + ' |')
    for name in a.vu1:
        t = next((x for x in agg if x['name'] == name), None)
        if not t:
            continue
        progs = {}
        for v in vu1:
            if v['seg'] in t['ids']:
                p = progs.setdefault(v['key'], {'name': v['name'], 'runs': 0, 'pairs': 0, 'ms': 0.0})
                p['runs'] += v['runs']
                p['pairs'] += v['pairs']
                p['ms'] += v['ms']
        tot = sum(p['pairs'] for p in progs.values()) or 1
        print()
        print(f"VU1 programs in {name} ({len(progs)} distinct; per flip = / {t['flips']} flips):")
        print()
        print('| Program | key | runs / flip | pairs / flip | pairs / run | share of pairs | vu1 ms / flip | ns / pair |')
        print('|---|---|---|---|---|---|---|---|')
        for key, p in sorted(progs.items(), key=lambda kv: -kv[1]['pairs'])[:a.top]:
            fl = t['flips'] or 1
            ns = 1e6 * p['ms'] / p['pairs'] if p['pairs'] else 0
            print(f"| {p['name']} | {key} | {fmt(p['runs'] / fl, 1)} | {fmt(p['pairs'] / fl, 0)} | "
                  f"{fmt(p['pairs'] / max(1, p['runs']), 0)} | {100 * p['pairs'] / tot:.1f} % | {p['ms'] / fl:.2f} | {ns:.1f} |")


if __name__ == '__main__':
    main()
