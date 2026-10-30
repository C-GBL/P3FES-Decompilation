#!/usr/bin/env python3
"""The performance harness: runs the six replay routes with a fast build, cuts each route into segments by what is on
screen, and reports per segment the game thread's CPU time, the graphics CPU time by subsystem, the render thread,
the GPU, x real time and frame-time percentiles (docs/ANALYSIS/23 "Re-measure 2026-10-25").

  python -I tools/ours/perf/bench.py run     --exe build/<tree>/bin/p3fes.exe --out <dir> [options]
  python -I tools/ours/perf/bench.py report  <dir> [--timeline] [--json FILE] [--csv FILE]
  python -I tools/ours/perf/bench.py compare <dirA> <dirB> [--json FILE]

run: every route (or --routes dorm,battle,...) in every mode (--modes windowed,headless) --repeat times, one process at
a time (--jobs N for more), each in its own working directory under <dir> (private copy-on-write memory cards). Modes:
  windowed  the player's configuration: window, D3D11 GS (interpolated), --unpaced (as fast as it can: capacity),
            --frames <route end>; a kill timeout (--timeout-scale x the route's real-time length + 120 s)
  headless  --headless --gs-backend d3d11 --gs-exact (the gates' fast mode, no window)
  software  --headless with the software GS (the oracle; slow)
Every run gets --vu1 aot (the fastest build: configure with -DP3FES_VU1_AOT=ON, gate.ps1 does) and
--zones <run>/zones.tsv --zones-every N (default 10): host_zones.h writes per-segment zone times, host-thread / process
CPU time, the machine's busy share, renderer counters, GPU time and the running kwln task names, and
zones.tsv.frames.tsv with one row per game frame. The machine is shared: run.json records the load before and after
each run (busy CPU %, the processes of other builds and games), and every row carries the machine's busy share.

report: one table per route and mode -- segments by class (title/movie, menu, field, tartarus, battle, event, load),
the whole route, then the heaviest segments -- plus JSON/CSV with every number. A "frame" is one game frame (one
flip; the game runs at 30 fps = 2 vblanks per frame; the budget is 15 ms of host time per frame at p99, --budget); "graphics" = VU1 + VIF1 + GIF + GS front
end (gs_raster = op recording with D3D11, the rasteriser with software) + uploads + CRTC + D3D11 submission, on the
game thread; the render thread and the GPU run alongside.

compare: the same tables side by side for two run directories (or report JSON files), with the change.
"""
import argparse
import csv
import json
import os
import statistics
import subprocess
import sys
import time

VBLANK_HZ = 59.94
GAME_FRAME_MS = 2e3 / VBLANK_HZ  # one game frame = 2 vblanks = 33.37 ms of real time
# The target (the user, 2026-10-25): at most 15 ms of host time per game frame in every scene at the 99th percentile,
# so the host can show 60 fps and more (track H interpolates in-between frames). --budget changes it.
FRAME_BUDGET_MS = 15.0
MAIN = r'F:\P3FES-PORT\p3fes-port'

ZONES = ['host', 'ee', 'kernel', 'fiber', 'hw_dmac', 'vif1', 'vu1', 'gif', 'gs_raster', 'gs_upload', 'gs_crtc', 'ipu',
         'iop', 'iop_cpu', 'audio', 'cdvd', 'present', 'gs_submit', 'gs_wait']
GFX = ['vu1', 'vif1', 'gif', 'gs_raster', 'gs_upload', 'gs_crtc', 'gs_submit', 'gs_wait']  # gs_wait: the game thread waiting for --gs-threads workers
GAME = ['ee', 'kernel', 'fiber', 'hw_dmac', 'iop', 'iop_cpu', 'audio', 'cdvd', 'ipu', 'host']

# Routes as tools/ours/gate/gate.ps1 runs them; `end` = the gate's snapshot vblank (m1: sky:11 is vblank ~380).
ROUTES = {
    'dorm':   {'args': ['--memcard', 'new', '--replay-input', r'{main}\config\inputs\to_dorm.txt'], 'end': 4900},
    'm1':     {'args': ['--memcard', 'new'], 'end': 400},  # the gate's m1 uses the default card (written in place): not here
    'battle': {'args': ['--memcard', r'{main}\extracted\_ours\cards\tartarus.ps2', '--replay-input', r'{main}\config\inputs\to_battle.txt'], 'end': 6150},
    'fusion': {'args': ['--memcard', r'{main}\extracted\_ours\cards\fusion.ps2', '--replay-input', r'{main}\config\inputs\fusion.txt'], 'end': 6300},
    'shop':   {'args': ['--memcard', r'{main}\extracted\_ours\cards\shop_buy.ps2', '--replay-input', r'{main}\config\inputs\shop.txt'], 'end': 4100},
    'climb':  {'args': ['--memcard', r'{main}\extracted\_ours\cards\full_battle.ps2', '--replay-input', r'{main}\config\inputs\full_battle.txt'], 'end': 39820},
}
MODES = {
    'windowed': ['--gs-backend', 'd3d11', '--unpaced', '--quiet'],  # --quiet: a log write blocked by the shared disk stalls the game thread
    'headless': ['--headless', '--quiet', '--gs-backend', 'd3d11', '--gs-exact'],
    'software': ['--headless', '--quiet'],
}

# Segment classes from the running kwln task names (host_zones.h "tasks" column), first match wins. Rules come from
# the task sets the six routes run (`report --tasks` prints them; docs/ANALYSIS/23 "Re-measure 2026-10-25").
#   result    battle_result (the RESULT / level-up screens after a battle)
#   battle    "battle" / "battle_*" (btlTableReload at boot is data loading, not a battle)
#   movie     a Sofdec movie is playing (the "movie" column: the player pointer 0x7CDF10 is set; the H_SfdPlay task
#             and the flag 5127 stay set long after a movie -- the flag also during battles and menus)
#   load      NOW_LOADING
#   menu      facility / system menus: shop (fclShop*), Velvet Room fusion (fclCombine*, fclCmbEff*), the memory-card
#             load menu (mcProc), the Tartarus floor select (y_StratumParts_proc), the town map (y_lmap_proc), the
#             camp menu (Camp*, cmp*), name entry (M_NameEntry)
#   event     the event viewer ((ZikkiPlayMode)EventVie, event_Draw_3D) or an event script task eNNN_*
#   tartarus  automatic_dungeon_ (exploring a Tartarus floor or its lobby)
#   field     field_root (town, dorm, school)
#   title     op / op_draw (title screen and the logos before it)
#   boot      anything else (boot, the first loads)
def _is_event_script(n):
    return len(n) > 4 and n[0] == 'e' and n[1:4].isdigit() and n[4] == '_'


MENU_PREFIX = ('fclShop', 'fclCombine', 'fclCmbEff', 'mcProc', 'y_StratumParts', 'y_lmap', 'y_LMap', 'Camp', 'cmp',
               'M_Name', 'fclBankMenu', 'H_Camp', 'camp')


def classify(tasks, movie=0):
    s = set(tasks)
    if 'battle_result' in s:
        return 'result'
    if 'battle' in s or any(n.startswith('battle_') for n in tasks):
        return 'battle'
    if movie:
        return 'movie'
    if 'NOW_LOADING' in s:
        return 'load'
    if any(n.startswith(MENU_PREFIX) for n in tasks):
        return 'menu'
    if '(ZikkiPlayMode)EventVie' in s or 'event_Draw_3D' in s or any(_is_event_script(n) for n in tasks):
        return 'event'
    if 'automatic_dungeon_' in s:
        return 'tartarus'
    if 'field_root' in s:
        return 'field'
    if 'op' in s or 'op_draw' in s:
        return 'title'
    return 'boot'


# ---------------------------------------------------------------------------------------------------------- loading
def num(v):
    try:
        return int(v)
    except ValueError:
        try:
            return float(v)
        except ValueError:
            return v


def load_zones(path):
    rows, header, tasks = [], None, []
    with open(path, encoding='utf-8', errors='replace') as f:
        for line in f:
            line = line.rstrip('\n')
            if not line or line.startswith('#'):
                continue
            p = line.split('\t')
            if p[0] == 'seg':
                header = p
            elif p[0] == 'vu1' or header is None:
                continue
            else:
                r = {k: num(v) for k, v in zip(header, p)}
                # Per-thread zones (the profiler of a graphics worker thread, once there is one): a column
                # "<thread>.<zone>" or "<zone>@<thread>" is that thread's zone; bare zone names are the game thread.
                th = {}
                for k, v in r.items():
                    if isinstance(v, str):
                        continue
                    if '.' in k and k.split('.', 1)[1] in ZONES:
                        th.setdefault(k.split('.', 1)[0], {})[k.split('.', 1)[1]] = v
                    elif '@' in k and k.split('@', 1)[0] in ZONES:
                        th.setdefault(k.split('@', 1)[1], {})[k.split('@', 1)[0]] = v
                    elif k[:1] == 'w' and '_' in k and k.split('_', 1)[0][1:].isdigit() and k.split('_', 1)[1] in ZONES:
                        # the graphics pipeline workers of --gs-threads (host_zones.h: w0_vu1, w1_gs_raster, ...)
                        th.setdefault(k.split('_', 1)[0], {})[k.split('_', 1)[1]] = v
                r['threads'] = th
                t = r.get('tasks', '-')
                if t == '=':
                    t = tasks
                elif t == '-' or t == '':
                    t = []
                else:
                    t = str(t).split('|')
                tasks = t
                r['tasks'] = t
                r['class'] = classify(t, r.get('movie', 0))
                rows.append(r)
    return rows


_VU1_NAMES = None


def vu1_name(key):
    """vu1_prog_* name of a program key (guest address of its MPG DMAtag) from symbols/p3fes.sym next to this script."""
    global _VU1_NAMES
    if _VU1_NAMES is None:
        _VU1_NAMES = {}
        sym = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..', 'symbols', 'p3fes.sym')
        try:
            for line in open(sym, encoding='utf-8', errors='replace'):
                p = line.split()
                if len(p) >= 4 and p[3].startswith('vu1_prog_'):
                    _VU1_NAMES[int(p[0], 16)] = p[3]
        except OSError:
            pass
    try:
        return _VU1_NAMES.get(int(key, 16), key)
    except ValueError:
        return key


def load_vu1(path, rows):
    """The per-segment VU1 program lines of a zones file -> {class: {key: {name, runs, pairs, ms}}}."""
    cls_of = {i: r['class'] for i, r in enumerate(rows)}
    out = {}
    with open(path, encoding='utf-8', errors='replace') as f:
        for line in f:
            if not line.startswith('vu1\t'):
                continue
            p = line.rstrip('\n').split('\t')
            cls = cls_of.get(int(p[1]), '?')
            name = p[3].split()[-1].replace('+0x0', '') if p[3] else p[2]
            if name.startswith('0x'):
                name = vu1_name(p[2])
            e = out.setdefault(cls, {}).setdefault(p[2], {'name': name, 'runs': 0, 'pairs': 0, 'ms': 0.0})
            e['runs'] += int(p[4])
            e['pairs'] += int(p[5])
            e['ms'] += float(p[6])
    return out


def load_frames(path):
    out, header = [], None
    if not os.path.exists(path):
        return out
    with open(path, encoding='utf-8') as f:
        for line in f:
            line = line.rstrip('\n')
            if not line or line.startswith('#'):
                continue
            p = line.split('\t')
            if p[0] == 'flip':
                header = p
                continue
            out.append({k: num(v) for k, v in zip(header, p)})
    prev = 0
    for f in out:  # vblanks since the previous flip
        f['dv'] = f['vblank'] - prev
        prev = f['vblank']
    return out


def pct(xs, q):
    if not xs:
        return 0.0
    s = sorted(xs)
    i = min(len(s) - 1, max(0, int(round(q / 100.0 * (len(s) - 1)))))
    return s[i]


# -------------------------------------------------------------------------------------------------------- metrics
def summarize(rows, frames, v0, v1):
    """Numbers for the vblank range [v0, v1) from zone rows (whole rows whose start lies inside) and frame rows."""
    rs = [r for r in rows if v0 <= r['v0'] < v1]
    if not rs:
        return None
    vb = sum(r['v1'] - r['v0'] for r in rs)
    wall = sum(r['wall_s'] for r in rs)
    flips = sum(r.get('flips', 0) for r in rs)
    fl = vb / 2.0  # "per frame" = per 2 vblanks, the game's 30 fps frame budget (also where it does not flip)
    z = {k: sum(r.get(k, 0.0) for r in rs) for k in ZONES}
    m = {
        'v0': rs[0]['v0'], 'v1': rs[-1]['v1'], 'vblanks': vb, 'frames': flips, 'wall_s': wall,
        'x_real': vb / VBLANK_HZ / wall if wall else 0.0,
        'fps': flips / wall if wall else 0.0,
        'wall_ms_frame': 1e3 * wall / fl,
        # share of the wall time the game thread spent on a CPU (1 - preempted / blocked)
        'cpu_share': sum(r.get('cpu_host_ms', 0.0) for r in rs) / (1e3 * wall) if wall else 0.0,
        'cpu_game_ms_frame': sum(r.get('cpu_host_ms', 0.0) for r in rs) / fl,
        'cpu_other_ms_frame': sum(r.get('cpu_other_ms', 0.0) for r in rs) / fl,
        'render_cpu_ms_frame': sum(r.get('r_cpu_ms', 0.0) for r in rs) / fl,
        'render_busy_ms_frame': sum(r.get('r_busy_ms', 0.0) for r in rs) / fl,
        'machine_busy': statistics.fmean([r.get('machine_busy', 0.0) for r in rs]),
        'lists_merged': sum(r.get('r_merged', 0) for r in rs),
        # the render thread fell behind: op lists appended to a queued one (GPU / render-thread limited, not the game)
        'lists_merged_share': (sum(r.get('r_merged', 0) for r in rs) / sum(r.get('r_submitted', 0) for r in rs))
                              if sum(r.get('r_submitted', 0) for r in rs) else None,
        # the game thread waited for the render thread (readbacks, start / stop)
        'render_wait_ms_frame': sum(r.get('r_wait_ms', 0.0) for r in rs) / (vb / 2.0),
        'lists_submitted': sum(r.get('r_submitted', 0) for r in rs),
        'vu1_pairs_frame': sum(r.get('vu1_pairs', 0) for r in rs) / fl,
        'prims_frame': sum(r.get('prims', 0) for r in rs) / fl,
    }
    gms = sum(r.get('gpu_ms', 0.0) for r in rs)
    gfr = sum(r.get('gpu_frames', 0) for r in rs)
    ex = sum(r.get('r_executed', 0) for r in rs)
    m['gpu_ms_frame'] = (gms / gfr) * ex / fl if gfr else None
    # Zones measure wall time on the game thread, so on a loaded machine they include the time the thread was
    # preempted. z_* are those wall times; c_* scale them by the thread's CPU time over its wall time in the range
    # (cpu_game / zone total), i.e. assume preemption hits every subsystem alike: the CPU cost on a quiet machine.
    # The scale is taken per row (10 vblanks by default), so a row in which the thread was blocked or starved does
    # not distort the others.
    ztot = sum(z.values())
    scale = (sum(r.get('cpu_host_ms', 0.0) for r in rs) / ztot) if ztot else 1.0
    m['cpu_scale'] = scale
    zc = {k: 0.0 for k in ZONES}
    for r in rs:
        rt = sum(r.get(k, 0.0) for k in ZONES)
        rsc = r.get('cpu_host_ms', 0.0) / rt if rt else 0.0
        for k in ZONES:
            zc[k] += r.get(k, 0.0) * rsc
    for k in ZONES:
        m['z_' + k] = z[k] / fl
        m['c_' + k] = zc[k] / fl
    m['gfx_ms_frame'] = sum(z[k] for k in GFX) / fl
    m['game_code_ms_frame'] = sum(z[k] for k in GAME) / fl
    m['gfx_cpu_ms_frame'] = sum(zc[k] for k in GFX) / fl
    m['game_code_cpu_ms_frame'] = sum(zc[k] for k in GAME) / fl
    m['x_real_cpu'] = (vb / VBLANK_HZ) / (sum(r.get('cpu_host_ms', 0.0) for r in rs) / 1e3) if scale else 0.0
    # Other threads' zones (wall ms per frame) and their graphics total; "cpu_<thread>_ms" columns, when a thread
    # reports its CPU time, scale that thread's zones like the game thread's.
    names = sorted({t for r in rs for t in r.get('threads', {})})
    for t in names:
        tz = {k: sum(r.get('threads', {}).get(t, {}).get(k, 0.0) for r in rs) for k in ZONES}
        tcpu = sum(r.get(f'cpu_{t}_ms', r.get(f'cpu_{t}', 0.0)) for r in rs)
        tsc = tcpu / sum(tz.values()) if tcpu and sum(tz.values()) else 1.0
        m[f'thread_{t}'] = {'zones_ms_frame': {k: v / fl for k, v in tz.items() if v},
                            'gfx_ms_frame': sum(tz[k] for k in GFX) / fl,
                            'gfx_cpu_ms_frame': sum(tz[k] for k in GFX) * tsc / fl,
                            'cpu_ms_frame': tcpu / fl if tcpu else None}
    if names:
        m['gfx_other_threads_ms_frame'] = sum(m[f'thread_{t}']['gfx_cpu_ms_frame'] for t in names)
    # Frame times: one value per flip interval, scaled to 2 vblanks (an interval of 2k vblanks -- a load screen that
    # does not flip, a dropped frame -- counts as k frames of its average cost; a frame is over budget when that
    # average exceeds the budget, FRAME_BUDGET_MS). cpu_* = the game thread's CPU time per frame; gfx_* = graphics,
    # CPU-scaled per frame. fps_* = game frames per second the host could produce uncapped (1000 / ms per frame).
    fs = [f for f in frames if v0 <= f['vblank'] < v1 and f.get('dv', 0) > 0]
    if fs:
        w = [f['wall_ms'] * 2 / f['dv'] for f in fs]
        c = [f['cpu_ms'] * 2 / f['dv'] for f in fs]
        g = []
        for f in fs:
            tot = sum(f.get(k, 0.0) for k in ZONES)
            s = f['cpu_ms'] / tot if tot else 1.0
            g.append(sum(f.get(k, 0.0) for k in GFX) * s * 2 / f['dv'])
        m.update({'frame_n': len(fs), 'frame_p50': pct(w, 50), 'frame_p90': pct(w, 90), 'frame_p99': pct(w, 99),
                  'frame_max': max(w), 'frame_over_budget': sum(1 for x in w if x > FRAME_BUDGET_MS) / len(w),
                  'frame_p95': pct(w, 95),
                  'cpu_p50': pct(c, 50), 'cpu_p90': pct(c, 90), 'cpu_p95': pct(c, 95), 'cpu_p99': pct(c, 99), 'cpu_max': max(c),
                  'cpu_over_budget': sum(1 for x in c if x > FRAME_BUDGET_MS) / len(c),
                  'budget_ms': FRAME_BUDGET_MS, 'pass': 'PASS' if pct(c, 99) <= FRAME_BUDGET_MS else 'FAIL',
                  'fps_cpu_mean': 1e3 / statistics.fmean(c) if statistics.fmean(c) else None,
                  'fps_cpu_p99': 1e3 / pct(c, 99) if pct(c, 99) else None,
                  'gfx_p95': pct(g, 95),
                  'gfx_p50': pct(g, 50), 'gfx_p90': pct(g, 90), 'gfx_p99': pct(g, 99), 'gfx_max': max(g),
                  'gfx_over_43': sum(1 for x in g if x >= 43.0) / len(g)})
    return m


def segments(rows, min_vblanks=60):
    """Contiguous runs of one class; runs shorter than min_vblanks join the previous run."""
    segs = []
    for r in rows:
        if segs and (segs[-1]['class'] == r['class'] or r['v1'] - r['v0'] < 1):
            segs[-1]['v1'] = r['v1']
            continue
        segs.append({'class': r['class'], 'v0': r['v0'], 'v1': r['v1']})
    out = []
    for s in segs:
        if out and s['v1'] - s['v0'] < min_vblanks:
            out[-1]['v1'] = s['v1']
        elif out and out[-1]['class'] == s['class']:
            out[-1]['v1'] = s['v1']
        else:
            out.append(dict(s))
    return out


def present_metrics(frows, v0, v1):
    """Track F's --frame-log rows (runtime/app/frame_telemetry.h) folded with its own frame_report.fold: the
    present-to-present interval of new frames (p99) and the hitches over 34 ms, for vblanks [v0, v1)."""
    sub = [r for r in frows if v0 <= int(r['vblank']) < v1]
    if not sub:
        return {}
    try:
        import frame_report
        f = frame_report.fold(sub, '')
    except Exception:  # noqa: BLE001 -- an older or newer CSV layout: leave the columns empty
        return {}
    return {'present_p50': f['p50'], 'present_p99': f['p99'], 'present_max': f['max'], 'hitches': f['hitches']}


def analyse_run(d, busy=None):
    if not os.path.exists(os.path.join(d, 'zones.tsv')):  # killed or still running
        return None
    rows = load_zones(os.path.join(d, 'zones.tsv'))
    if busy is not None:  # the machine's load while the run ran (bench's monitor thread)
        for r in rows:
            r.setdefault('machine_busy', busy)
    frames = load_frames(os.path.join(d, 'zones.tsv.frames.tsv'))
    if not rows:
        return None
    frows = []
    if os.path.exists(os.path.join(d, 'frames.csv')):
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import frame_report
        frows = frame_report.load(os.path.join(d, 'frames.csv'))
    segs = segments(rows)
    res = {'whole': summarize(rows, frames, 0, 1 << 62), 'segments': [], 'classes': {},
           'vu1': load_vu1(os.path.join(d, 'zones.tsv'), rows)}
    res['whole'].update(present_metrics(frows, 0, 1 << 62))
    for s in segs:
        m = summarize(rows, frames, s['v0'], s['v1'])
        if m:
            m['class'] = s['class']
            m.update(present_metrics(frows, s['v0'], s['v1']))
            res['segments'].append(m)
    for cls in sorted({r['class'] for r in rows}):
        sub = [r for r in rows if r['class'] == cls]
        fsub = []
        spans = [(r['v0'], r['v1']) for r in sub]
        for f in frames:
            if any(a <= f['vblank'] < b for a, b in spans):
                fsub.append(f)
        m = summarize(sub, fsub, 0, 1 << 62)
        if m:
            m['class'] = cls
            if frows:
                fr = [r for r in frows if any(a <= int(r['vblank']) < b for a, b in spans)]
                m.update(present_metrics(fr, 0, 1 << 62))
            res['classes'][cls] = m
    return res


def median_merge(results):
    """Per metric, the median over the repeats (numbers only); keeps the structure of the first."""
    if len(results) == 1:
        return results[0]
    def med(ms):
        ms = [m for m in ms if m]
        if not ms:
            return None
        out = dict(ms[0])
        for k, v in ms[0].items():
            if isinstance(v, (int, float)) and not isinstance(v, bool):
                vals = [m.get(k) for m in ms if isinstance(m.get(k), (int, float))]
                if vals:
                    out[k] = statistics.median(vals)
        out['repeats'] = len(ms)
        return out
    merged = {'whole': med([r['whole'] for r in results]), 'segments': results[0]['segments'], 'classes': {},
              'vu1': results[0].get('vu1', {})}
    for cls in results[0]['classes']:
        merged['classes'][cls] = med([r['classes'].get(cls) for r in results])
    return merged


# ------------------------------------------------------------------------------------------------------------ load
def machine_load():
    """Busy CPU % over one second and the processes of other builds / games (the machine is shared)."""
    info = {'time': time.strftime('%Y-%m-%d %H:%M:%S')}
    try:
        out = subprocess.run(['tasklist', '/fo', 'csv', '/nh'], capture_output=True, text=True, timeout=30).stdout
        counts = {}
        for line in out.splitlines():
            name = line.split('","')[0].strip('"').lower()
            if name in ('cl.exe', 'clang-cl.exe', 'link.exe', 'lld-link.exe', 'ninja.exe', 'p3fes.exe', 'msbuild.exe',
                        'ctest.exe', 'p3fes_game_tests.exe', 'python.exe', 'p3fes_recomp.exe', 'idat64.exe', 'ida64.exe'):
                counts[name] = counts.get(name, 0) + 1
        info['procs'] = counts
    except Exception as e:  # noqa: BLE001 -- best effort
        info['procs_error'] = str(e)
    try:
        ps = ('$a=Get-CimInstance Win32_Processor | Measure-Object -Property LoadPercentage -Average;'
              '[math]::Round($a.Average,1)')
        out = subprocess.run(['powershell', '-NoProfile', '-Command', ps], capture_output=True, text=True, timeout=60).stdout
        info['cpu_busy_pct'] = float(out.strip().splitlines()[-1])
    except Exception as e:  # noqa: BLE001
        info['cpu_error'] = str(e)
    return info


# ------------------------------------------------------------------------------------------------------------- run
def read_text(path):
    try:
        return open(path, encoding='utf-8', errors='replace').read()
    except OSError:
        return ''


def gs_fell_back(text):
    """The run's D3D11 GS did not come up or gave up (software from some point on): a different workload. (A render
    thread that does not stop within 3 s at exit is not a fallback.)"""
    return 'gs-backend: software' in text or 'falling back to software' in text


class LoadMonitor:
    """Samples the machine's busy share (GetSystemTimes) from a thread of this process, so the game never pays for it
    (the call took from ~1 ms up to seconds on the loaded 16-thread host)."""

    def __init__(self, period=2.0):
        import threading
        self.samples = []  # (time, busy share since the previous sample)
        self.stop = threading.Event()
        self.period = period
        self.t = threading.Thread(target=self.run, daemon=True)
        self.t.start()

    @staticmethod
    def times():
        import ctypes
        from ctypes import wintypes
        i, k, u = wintypes.FILETIME(), wintypes.FILETIME(), wintypes.FILETIME()
        if not ctypes.windll.kernel32.GetSystemTimes(ctypes.byref(i), ctypes.byref(k), ctypes.byref(u)):
            return None
        f = lambda x: (x.dwHighDateTime << 32) | x.dwLowDateTime
        return f(i), f(k), f(u)

    def run(self):
        prev = self.times()
        while not self.stop.wait(self.period):
            cur = self.times()
            if prev and cur:
                tot = (cur[1] - prev[1]) + (cur[2] - prev[2])
                if tot > 0:
                    self.samples.append((time.time(), 1.0 - (cur[0] - prev[0]) / tot))
            prev = cur

    def mean(self, t0, t1):
        xs = [b for t, b in self.samples if t0 <= t <= t1]
        return statistics.fmean(xs) if xs else None


def cmd_run(a):
    exe = os.path.abspath(a.exe)
    if not os.path.exists(exe):
        sys.exit('no ' + exe)
    os.makedirs(a.out, exist_ok=True)
    routes = list(ROUTES) if a.routes == 'all' else a.routes.split(',')
    modes = a.modes.split(',')
    elf = os.path.join(a.main, 'extracted', 'disc', 'SLUS_216.21')
    iso = os.path.join(a.main, 'input', 'persona3fes.iso')
    jobs = []
    for rep in range(a.rep_from, a.rep_from + a.repeat):
        for mode in modes:
            for route in routes:
                jobs.append((route, mode, rep))
    meta_path = os.path.join(a.out, 'run.json')
    meta = json.load(open(meta_path)) if os.path.exists(meta_path) else {'runs': []}
    meta.update({'exe': exe, 'vu1': a.vu1, 'every': a.every})
    running = []
    monitor = LoadMonitor()

    def start(route, mode, rep):
        r = ROUTES[route]
        d = os.path.abspath(os.path.join(a.out, f'{route}.{mode}.{rep}'))
        os.makedirs(d, exist_ok=True)
        for f in ('zones.tsv', 'zones.tsv.frames.tsv'):
            if os.path.exists(os.path.join(d, f)):
                os.remove(os.path.join(d, f))
        args = [exe, '--elf', elf, '--iso', iso] + MODES[mode] + ['--vu1', a.vu1]
        args += [x.format(main=a.main) for x in r['args']]
        end = a.frames or r['end']
        args += ['--frames', str(end), '--zones', os.path.join(d, 'zones.tsv'), '--zones-every', str(a.every)]
        if mode == 'windowed':  # track F's per-frame telemetry (present intervals, hitches): tools/ours/perf/frame_report.py
            args += ['--frame-log', os.path.join(d, 'frames.csv')]
        args += a.extra
        timeout = a.timeout_scale * end / VBLANK_HZ + 120
        if mode == 'software':
            timeout *= 10
        log = open(os.path.join(d, 'log.txt'), 'w')
        rec = {'route': route, 'mode': mode, 'rep': rep, 'dir': d, 'cmd': args, 'load_before': machine_load(),
               'start': time.time()}
        print(f'[bench] start {route} {mode} #{rep} (end vblank {end}, timeout {timeout:.0f} s); load {rec["load_before"].get("cpu_busy_pct")}% '
              f'{rec["load_before"].get("procs")}', flush=True)
        p = subprocess.Popen(args, cwd=d, stdout=log, stderr=subprocess.STDOUT)
        running.append((p, rec, timeout, log))

    def reap(p, rec, timeout, log):
        try:
            p.wait(timeout=max(1, timeout - (time.time() - rec['start'])))
        except subprocess.TimeoutExpired:
            p.kill()
            p.wait()
            rec['killed'] = True
        log.close()
        rec['exit'] = p.returncode
        rec['wall_s'] = time.time() - rec['start']
        rec['load_after'] = machine_load()
        rec['busy_avg'] = monitor.mean(rec['start'], time.time())
        rec['ok'] = os.path.exists(os.path.join(rec['dir'], 'zones.tsv'))
        # A run whose D3D11 device did not come up (a GPU swamped by other processes: start timeout) continues on the
        # software GS -- a different workload: flag it (the report skips it).
        try:
            text = open(os.path.join(rec['dir'], 'log.txt'), encoding='utf-8', errors='replace').read()
        except OSError:
            text = ''
        if gs_fell_back(text):
            rec['gs_fallback'] = True
            rec['ok'] = False
            print(f'[bench] WARNING {rec["route"]} {rec["mode"]} #{rec["rep"]}: the D3D11 GS fell back to software; not reported', flush=True)
        print(f'[bench] done  {rec["route"]} {rec["mode"]} #{rec["rep"]}: exit {rec["exit"]}, {rec["wall_s"]:.1f} s'
              f'{" KILLED" if rec.get("killed") else ""}{"" if rec["ok"] else " (no zones.tsv)"}', flush=True)
        meta['runs'] = [x for x in meta['runs'] if x['dir'] != rec['dir']] + [rec]
        json.dump(meta, open(meta_path, 'w'), indent=1)

    def reap_one():
        # the first run that has finished or timed out (not simply the oldest: a long route must not hold a slot)
        while True:
            for i, (p, rec, timeout, log) in enumerate(running):
                if p.poll() is not None or time.time() - rec['start'] > timeout:
                    running.pop(i)
                    reap(p, rec, timeout, log)
                    return
            time.sleep(2)

    for job in jobs:
        while len(running) >= a.jobs:
            reap_one()
        start(*job)
    while running:
        reap(*running.pop(0))
    cmd_report(argparse.Namespace(dir=a.out, timeline=False, json=os.path.join(a.out, 'report.json'),
                                  csv=os.path.join(a.out, 'report.csv'), tasks=False, top=5, vu1=False))


# ---------------------------------------------------------------------------------------------------------- report
def build_report(d):
    meta_path = os.path.join(d, 'run.json')
    runs = json.load(open(meta_path))['runs'] if os.path.exists(meta_path) else []
    if not runs:  # a directory of run folders without run.json
        for name in sorted(os.listdir(d)):
            p = name.split('.')
            if len(p) == 3 and os.path.exists(os.path.join(d, name, 'zones.tsv')):
                runs.append({'route': p[0], 'mode': p[1], 'rep': int(p[2]), 'dir': os.path.join(d, name)})
    groups = {}
    for r in runs:
        if gs_fell_back(read_text(os.path.join(r['dir'], 'log.txt'))):
            continue
        res = analyse_run(r['dir'], r.get('busy_avg'))
        if res is None:
            continue
        res['load_before'] = r.get('load_before')
        res['load_after'] = r.get('load_after')
        groups.setdefault((r['route'], r['mode']), []).append(res)
    rep = {'dir': os.path.abspath(d), 'routes': {}}
    for (route, mode), results in sorted(groups.items()):
        m = median_merge(results)
        m['repeats'] = len(results)
        m['loads'] = [{'before': x['load_before'], 'after': x['load_after']} for x in results]
        m['per_repeat_whole'] = [x['whole'] for x in results]
        rep['routes'].setdefault(route, {})[mode] = m
    return rep


def f1(x, d=1):
    return '-' if x is None else f'{x:,.{d}f}'


ORDER = ['boot', 'title', 'movie', 'load', 'menu', 'field', 'tartarus', 'event', 'battle', 'result']
COLS = [('x real', 'x_real', 2), ('x real (CPU)', 'x_real_cpu', 2), ('on CPU', 'cpu_share', 2), ('game CPU', 'cpu_game_ms_frame', 1),
        ('gfx', 'gfx_cpu_ms_frame', 1), ('VU1', 'c_vu1', 1), ('VIF1', 'c_vif1', 1), ('GIF', 'c_gif', 1),
        ('GS fe', 'c_gs_raster', 1), ('upload', 'c_gs_upload', 2), ('submit', 'c_gs_submit', 2), ('gs wait', 'c_gs_wait', 1),
        ('game code', 'game_code_cpu_ms_frame', 1), ('gfx thr', 'gfx_other_threads_ms_frame', 1),
        ('render CPU', 'render_cpu_ms_frame', 1), ('GPU', 'gpu_ms_frame', 1), ('lists late', 'lists_merged_share', 2),
        ('render wait', 'render_wait_ms_frame', 1), ('other thr', 'cpu_other_ms_frame', 1), ('CPU p50', 'cpu_p50', 1), ('CPU p95', 'cpu_p95', 1),
        ('CPU p99', 'cpu_p99', 1), ('CPU max', 'cpu_max', 0), ('>budget', 'cpu_over_budget', 2), ('p99 vs budget', 'pass', 0),
        ('fps (CPU)', 'fps_cpu_mean', 0), ('fps p99', 'fps_cpu_p99', 0), ('gfx p99', 'gfx_p99', 1), ('wall p99', 'frame_p99', 1),
        ('present p99', 'present_p99', 1), ('hitches', 'hitches', 0),
        ('busy', 'machine_busy', 2)]


def row_cells(m):
    out = []
    for _, k, dg in COLS:
        v = m.get(k)
        if isinstance(v, str):
            out.append(v)
        elif k in ('frame_over_budget', 'cpu_over_budget', 'machine_busy', 'cpu_share', 'lists_merged_share') and v is not None:
            out.append(f'{100 * v:.0f}%')
        else:
            out.append(f1(v, dg))
    return out


def print_vu1(rep, top=8):
    """VU1 programs per route and segment class: ms per frame, ns per pair (compiled programs run at ~15 ns per pair,
    interpreted ones at ~45-55), share of the class's VU1 time."""
    for route, modes in rep['routes'].items():
        for mode, m in modes.items():
            for cls, progs in sorted(m.get('vu1', {}).items()):
                c = m['classes'].get(cls)
                if not c or not progs:
                    continue
                fl = c['frames'] or c['vblanks'] / 2
                tot = sum(p['ms'] for p in progs.values()) or 1
                print()
                print(f'VU1 programs, {route} / {mode} / {cls} ({fl:.0f} frames):')
                print()
                print('| program | key | ms / frame | share | ns / pair | runs / frame |')
                print('|---|---|---|---|---|---|')
                for key, p in sorted(progs.items(), key=lambda kv: -kv[1]['ms'])[:top]:
                    ns = 1e6 * p['ms'] / p['pairs'] if p['pairs'] else 0
                    print(f"| {p['name']} | {key} | {p['ms'] / fl:.2f} | {100 * p['ms'] / tot:.0f}% | {ns:.1f} | {p['runs'] / fl:.0f} |")


def print_report(rep, timeline=False, top=5):
    print(f'Per game frame (1 frame = 2 vblanks; budget {FRAME_BUDGET_MS:g} ms of game-thread CPU at p99). Columns: x real time (wall clock); x real time if the game'
          ' thread had a core to itself (its CPU time); the share of wall time the game thread was on a CPU (low = preempted or blocked: the zone split below is then approximate); game-thread CPU ms per frame; graphics on the game thread (VU1 + VIF1'
          ' + GIF + GS front end + uploads + CRTC + submit) and its parts, CPU ms (zone wall times scaled by the thread\'s'
          ' CPU / wall ratio); game code (EE + kernel + IOP + audio + ...), CPU ms; render-thread CPU ms; GPU ms (timestamp'
          ' queries); share of op lists the render thread received late (appended to a queued one: GPU / render-thread'
          ' bound); ms per frame the game thread waited for the render thread; other threads\' CPU ms (process - game thread); game-thread CPU ms per frame p50 / p95 / p99 / max;'
          ' share of frames over the budget; PASS/FAIL of the p99 against the budget; game frames per second the host could'
          ' produce uncapped (1000 / mean, 1000 / p99 CPU ms); graphics CPU ms p99; wall-clock frame time p99; windowed: present-to-present interval p99 and hitches > 34 ms (--frame-log, track F); machine busy'
          ' (all cores).')
    for route, modes in rep['routes'].items():
        for mode, m in modes.items():
            loads = '; '.join(f"{(l['before'] or {}).get('cpu_busy_pct', '?')}%->{(l['after'] or {}).get('cpu_busy_pct', '?')}%"
                              for l in m.get('loads', []))
            print()
            print(f'### {route} / {mode} ({m["repeats"]} run(s), median; machine load before->after: {loads})')
            print()
            print('| segment | vblanks | ' + ' | '.join(c[0] for c in COLS) + ' |')
            print('|---|---|' + '---|' * len(COLS))
            for cls in sorted(m['classes'], key=lambda c: ORDER.index(c) if c in ORDER else 99):
                c = m['classes'][cls]
                print(f'| {cls} | {c["vblanks"]} | ' + ' | '.join(row_cells(c)) + ' |')
            w = m['whole']
            print(f'| **whole route** | {w["vblanks"]} | ' + ' | '.join(row_cells(w)) + ' |')
            segs = m['segments']
            if timeline:
                print()
                print('| # | class | vblanks | ' + ' | '.join(c[0] for c in COLS) + ' |')
                print('|---|---|---|' + '---|' * len(COLS))
                for i, s in enumerate(segs):
                    print(f'| {i} | {s["class"]} | {s["v0"]}-{s["v1"]} | ' + ' | '.join(row_cells(s)) + ' |')
            elif segs and top:
                heavy = sorted(segs, key=lambda s: -s['cpu_game_ms_frame'])[:top]
                print()
                print('Heaviest segments (game-thread CPU per frame): ' + '; '.join(
                    f'{s["class"]} {s["v0"]}-{s["v1"]} {s["cpu_game_ms_frame"]:.1f} ms (gfx {s["gfx_cpu_ms_frame"]:.1f}, '
                    f'VU1 {s["c_vu1"]:.1f}; {s["x_real_cpu"]:.2f}x)' for s in heavy))


def write_csv(rep, path):
    keys = ['route', 'mode', 'segment', 'v0', 'v1', 'vblanks', 'frames'] + [c[1] for c in COLS] + \
           ['z_' + z for z in ZONES] + ['render_busy_ms_frame', 'lists_merged', 'lists_submitted', 'vu1_pairs_frame',
                                       'prims_frame', 'frame_p90', 'frame_p95', 'cpu_p90', 'gfx_p50', 'gfx_p90', 'gfx_p95',
                                       'gfx_max', 'gfx_over_43', 'budget_ms']
    with open(path, 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(keys)
        for route, modes in rep['routes'].items():
            for mode, m in modes.items():
                items = [(c, m['classes'][c]) for c in m['classes']] + [('whole', m['whole'])] + \
                        [(f'seg:{s["class"]}', s) for s in m['segments']]
                for name, s in items:
                    w.writerow([route, mode, name] + [s.get(k) for k in keys[3:]])


def cmd_report(a):
    rep = build_report(a.dir)
    if a.tasks:
        for name in sorted(os.listdir(a.dir)):
            z = os.path.join(a.dir, name, 'zones.tsv')
            if not os.path.exists(z):
                continue
            print(f'## {name}')
            last = None
            for r in load_zones(z):
                key = (tuple(r['tasks']), r.get('movie', 0))
                if key != last:
                    print(f"{r['v0']:>6} {r['class']:<9} movie={r.get('movie', 0)} {'|'.join(r['tasks'])}")
                    last = key
        return
    print_report(rep, a.timeline, a.top)
    if a.vu1:
        print_vu1(rep)
    if a.json:
        json.dump(rep, open(a.json, 'w'), indent=1)
    if a.csv:
        write_csv(rep, a.csv)


def load_any(x):
    if os.path.isdir(x):
        return build_report(x)
    return json.load(open(x))


def cmd_compare(a):
    A, B = load_any(a.a), load_any(a.b)
    keys = [('x real', 'x_real', 2), ('x real (CPU)', 'x_real_cpu', 2), ('game CPU', 'cpu_game_ms_frame', 1),
            ('gfx', 'gfx_cpu_ms_frame', 1), ('VU1', 'c_vu1', 1), ('VIF1', 'c_vif1', 2), ('GIF', 'c_gif', 2),
            ('GS fe', 'c_gs_raster', 2), ('submit', 'c_gs_submit', 2), ('game code', 'game_code_cpu_ms_frame', 1),
            ('render CPU', 'render_cpu_ms_frame', 1), ('GPU', 'gpu_ms_frame', 1), ('CPU p95', 'cpu_p95', 1),
            ('CPU p99', 'cpu_p99', 1), ('fps (CPU)', 'fps_cpu_mean', 0), ('busy', 'machine_busy', 2)]
    out = {'a': A['dir'], 'b': B['dir'], 'routes': {}}
    print(f'A = {A["dir"]}\nB = {B["dir"]}\nCells: A -> B (B/A for x real time, B-A ms otherwise). The machine is shared: compare'
          ' the busy column before trusting a difference under ~10 %.')
    for route in sorted(set(A['routes']) & set(B['routes'])):
        for mode in sorted(set(A['routes'][route]) & set(B['routes'][route])):
            ma, mb = A['routes'][route][mode], B['routes'][route][mode]
            print()
            print(f'### {route} / {mode}')
            print()
            print('| segment | ' + ' | '.join(k[0] for k in keys) + ' |')
            print('|---|' + '---|' * len(keys))
            names = [c for c in ORDER if c in ma['classes'] and c in mb['classes']] + ['whole']
            for n in names:
                sa = ma['whole'] if n == 'whole' else ma['classes'][n]
                sb = mb['whole'] if n == 'whole' else mb['classes'][n]
                cells = []
                for _, k, dg in keys:
                    va, vb = sa.get(k), sb.get(k)
                    if va is None or vb is None:
                        cells.append('-')
                    elif k == 'machine_busy':
                        cells.append(f'{100 * va:.0f}% -> {100 * vb:.0f}%')
                    elif k in ('x_real', 'x_real_cpu'):
                        cells.append(f'{va:.2f} -> {vb:.2f} ({vb / va if va else 0:.2f}x)')
                    else:
                        cells.append(f'{va:.{dg}f} -> {vb:.{dg}f} ({vb - va:+.{dg}f})')
                    out['routes'].setdefault(route, {}).setdefault(mode, {}).setdefault(n, {})[k] = [va, vb]
                print(f'| {n} | ' + ' | '.join(cells) + ' |')
    if a.json:
        json.dump(out, open(a.json, 'w'), indent=1)


def main():
    global FRAME_BUDGET_MS
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--budget', type=float, default=FRAME_BUDGET_MS,
                    help='host ms per game frame that passes, at p99 of the game-thread CPU time (default %(default)s)')
    sub = ap.add_subparsers(dest='cmd', required=True)
    r = sub.add_parser('run')
    r.add_argument('--exe', required=True)
    r.add_argument('--out', required=True)
    r.add_argument('--main', default=MAIN, help='tree with the game data, cards and inputs (default %(default)s)')
    r.add_argument('--routes', default='all', help='comma-separated: ' + ','.join(ROUTES))
    r.add_argument('--modes', default='windowed,headless', help='comma-separated: ' + ','.join(MODES))
    r.add_argument('--repeat', type=int, default=2)
    r.add_argument('--rep-from', type=int, default=1, help='number of the first repeat (add runs to an existing directory)')
    r.add_argument('--jobs', type=int, default=1, help='processes at once (more = more contention)')
    r.add_argument('--every', type=int, default=10, help='vblanks per zone row')
    r.add_argument('--vu1', default='aot', help='interp|aot (default aot)')
    r.add_argument('--frames', type=int, default=0, help='override the route end (vblanks)')
    r.add_argument('--timeout-scale', type=float, default=6.0, help='kill timeout = scale x route real time + 120 s')
    r.add_argument('extra', nargs='*', help='more p3fes arguments (after --)')
    r.set_defaults(fn=cmd_run)
    p = sub.add_parser('report')
    p.add_argument('dir')
    p.add_argument('--timeline', action='store_true', help='every segment, in order')
    p.add_argument('--tasks', action='store_true', help='print the running task sets and their class per run')
    p.add_argument('--top', type=int, default=5)
    p.add_argument('--vu1', action='store_true', help='VU1 programs per segment class (which run compiled, which interpreted)')
    p.add_argument('--json')
    p.add_argument('--csv')
    p.set_defaults(fn=cmd_report)
    c = sub.add_parser('compare')
    c.add_argument('a')
    c.add_argument('b')
    c.add_argument('--json')
    c.set_defaults(fn=cmd_compare)
    a = ap.parse_args()
    FRAME_BUDGET_MS = a.budget
    a.fn(a)


if __name__ == '__main__':
    main()
