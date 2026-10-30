#!/usr/bin/env python3
"""Flip-rate measurement at the title screen over PINE (ADR-0012 "Q-01 empirically"; docs/PCSX2.md
"Reference captures").

Samples, in ONE batched PINE message per tick (pine.Pine.read_many), the RenderWare/kwln globals of
docs/ANALYSIS/10_frame_loop_gs.md that move with the display:

  g_skyFrameCount      0x7CEA78 u32  ++ per RwCameraShowRaster = per flip REQUEST (SkyRasterShowRaster)
  g_rwDMAFlipPending   0x7CE9AC u8   1 while a flip is queued; _rwDMAVSYNCHandler 0x4D47F0 clears it as the
                                     first action of the flip path (sb zero @0x4D486C) and, if the next flip
                                     request is already queued, _rwDMAHandler(-1) at the end of the same
                                     handler sets it again
  g_rwDMAFlipBuf       0x7CE9A8 u8   0/1 buffer of the pending flip; so an EXECUTED flip is a pending 1->0
                                     edge, or a buffer toggle while pending stays 1 (back-to-back flips)
  adxt_vsync_cnt       0x787568 u32  ++ on entry of ADXPS2_ExecVint 0x540D80 (unconditional, @0x540DA8),
                                     whose only caller is kwlnGsSyncVCallback 0x197FE0 = the INTC-2
                                     (VBLANK_START) handler installed with next=-1 -> counts the vblanks on
                                     which the kernel's cause-2 chain REACHES that handler
  kwln frame counter   0x7CE10C u32  ++ per kwlnUpdate (game frame)
  g_kwlnFrameEndHsync  0x7CE148 f32  T0 (H-BLANK clock) at ShowRaster; T0 is zeroed right after, so this is
                                     the H-lines between two ShowRaster calls (one game frame; 262.5/field)
  g_kwlnFrameDeltaHsync 0x7CE14C f32 H-lines of CPU work in the frame (kwlnUpdate start -> ShowRaster)
  g_kwlnCpuLoadPct     0x7CE150 f32  delta / 520 * 100

PINE cannot read GS privileged registers (0x12000070 DISPFB1, 0x12001000 CSR read back as 0 on PCSX2
2.8.2) or EE hardware registers, so there is no direct VBlank/FIELD counter; the vblank time base is the
H-line count (g_kwlnFrameEndHsync / 262.5) and PCSX2's frame limiter (59.94 Hz NTSC).

Derived (all printed and written to JSON):
  * flip requests/s, executed flips/s (pending 1->0 edges), callback invocations/s, game frames/s,
    each also as a ratio to 59.94 Hz
  * fields per game frame from g_kwlnFrameEndHsync, CPU load per frame
  * coincidence: for every executed flip, whether adxt_vsync_cnt stepped within the same sampling
    interval (+-1 interval) -- vblanks are 16.7 ms apart and samples ~2 ms, so "same interval" means
    "same vblank". This tests whether the RW flip handler and the tail handler run on the SAME vblanks.
This corroborates, it does not prove, the INTC chain rule (Q-01): it observes the outcome of the
kernel's dispatch, not the dispatch itself.

Usage:
  python measure_flips.py [--samples 2000] [--interval-ms 2] [--out DIR]          # PCSX2 already at title
  python measure_flips.py --boot [--samples 2000] ...                               # boot to the title first
"""
import argparse
import datetime
import json
import pathlib
import statistics
import struct
import sys
import time

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
sys.path.insert(0, str(HERE.parent))
import pine  # noqa: E402

NTSC_FIELD_HZ = 59.94
HLINES_PER_FIELD = 262.5
OUT_DEFAULT = REPO / "extracted" / "_pcsx2" / "flips"

FIELDS = [  # (name, width, va)
    ("sky", 32, 0x7CEA78),
    ("pend", 8, 0x7CE9AC),
    ("buf", 8, 0x7CE9A8),
    ("adx", 32, 0x787568),
    ("kwln", 32, 0x7CE10C),
    ("end_hsync", 32, 0x7CE148),
    ("delta_hsync", 32, 0x7CE14C),
    ("cpu_pct", 32, 0x7CE150),
]
FLOATS = {"end_hsync", "delta_hsync", "cpu_pct"}


def f32(u):
    return struct.unpack("<f", struct.pack("<I", u))[0]


def sample_loop(p, n, interval_s):
    reqs = [(w, va) for _, w, va in FIELDS]
    rows = []
    next_t = time.perf_counter()
    for _ in range(n):
        t_a = time.perf_counter()
        v = p.read_many(reqs)
        t_b = time.perf_counter()
        rows.append((t_a, t_b, v))
        next_t += interval_s
        # busy-wait the last ~1.5 ms for an even cadence (Windows sleep granularity is ~1 ms at best)
        while True:
            rem = next_t - time.perf_counter()
            if rem <= 0:
                break
            if rem > 0.0015:
                time.sleep(rem - 0.0012)
    return rows


def analyse(rows, interval_s):
    idx = {name: i for i, (name, _, _) in enumerate(FIELDS)}
    t = [(a + b) / 2 for a, b, _ in rows]
    col = lambda name: [r[2][idx[name]] for r in rows]  # noqa: E731
    sky, pend, adx, kwln, buf = col("sky"), col("pend"), col("adx"), col("kwln"), col("buf")
    dur = t[-1] - t[0]
    gaps = [t[i + 1] - t[i] for i in range(len(t) - 1)]

    edge_idx = [i for i in range(1, len(rows)) if pend[i - 1] == 1 and pend[i] == 0]
    b2b_idx = [i for i in range(1, len(rows)) if pend[i - 1] == 1 and pend[i] == 1 and buf[i] != buf[i - 1]]
    flip_idx = sorted(edge_idx + b2b_idx)
    adx_step_idx = {i for i in range(1, len(rows)) if adx[i] != adx[i - 1]}
    adx_multi = [i for i in adx_step_idx if adx[i] - adx[i - 1] > 1]
    coincident = [i for i in flip_idx if {i - 1, i, i + 1} & adx_step_idx]
    # flip edges that fall in an interval long enough to straddle two vblanks are ambiguous
    long_gap = [i for i in flip_idx if (t[i] - t[i - 1]) > 0.008]
    buf_changes = sum(1 for i in range(1, len(rows)) if buf[i] != buf[i - 1])
    # how long pend stays high (in samples) -> whether a short pulse could be missed
    highs, run = [], 0
    for v in pend:
        if v == 1:
            run += 1
        elif run:
            highs.append(run)
            run = 0

    end_h = [f32(u) for u in col("end_hsync")]
    delta_h = [f32(u) for u in col("delta_hsync")]
    cpu = [f32(u) for u in col("cpu_pct")]
    # one value per game frame: take the value at each kwln step
    per_frame = [(end_h[i], delta_h[i], cpu[i]) for i in range(1, len(rows)) if kwln[i] != kwln[i - 1]]

    def rate(series):
        return (series[-1] - series[0]) / dur

    res = {
        "samples": len(rows),
        "duration_s": round(dur, 4),
        "mean_interval_ms": round(1000 * dur / (len(rows) - 1), 3),
        "max_interval_ms": round(1000 * max(gaps), 3),
        "intervals_over_8ms": sum(1 for g in gaps if g > 0.008),
        "requested_interval_ms": interval_s * 1000,
        "flip_requests": sky[-1] - sky[0],
        "flip_requests_per_s": round(rate(sky), 4),
        "executed_flips": len(flip_idx),
        "executed_flips_pending_edges": len(edge_idx),
        "executed_flips_back_to_back": len(b2b_idx),
        "executed_flips_per_s": round(len(flip_idx) / dur, 4),
        "flip_buffer_changes": buf_changes,
        "pending_high_samples_min_median_max": [min(highs), statistics.median(highs), max(highs)] if highs else None,
        "tail_handler_invocations_adx": adx[-1] - adx[0],
        "tail_handler_invocations_per_s": round(rate(adx), 4),
        "adx_steps_gt1_in_one_interval": len(adx_multi),
        "game_frames_kwln": kwln[-1] - kwln[0],
        "game_frames_per_s": round(rate(kwln), 4),
        "ratio_to_59_94": {
            "flip_requests": round(rate(sky) / NTSC_FIELD_HZ, 4),
            "executed_flips": round(len(flip_idx) / dur / NTSC_FIELD_HZ, 4),
            "tail_handler": round(rate(adx) / NTSC_FIELD_HZ, 4),
            "game_frames": round(rate(kwln) / NTSC_FIELD_HZ, 4),
        },
        "flips_coincident_with_tail_handler_vblank": len(coincident),
        "flips_not_coincident": len(flip_idx) - len(coincident),
        "flips_in_intervals_over_8ms": len(long_gap),
        "per_frame_hlines": {
            "frames": len(per_frame),
            "end_hsync_median": statistics.median(x[0] for x in per_frame) if per_frame else None,
            "end_hsync_min": min(x[0] for x in per_frame) if per_frame else None,
            "end_hsync_max": max(x[0] for x in per_frame) if per_frame else None,
            "fields_per_frame_median": (statistics.median(x[0] for x in per_frame) / HLINES_PER_FIELD) if per_frame else None,
            "cpu_delta_hsync_median": statistics.median(x[1] for x in per_frame) if per_frame else None,
            "cpu_load_pct_median": statistics.median(x[2] for x in per_frame) if per_frame else None,
            "cpu_load_pct_max": max(x[2] for x in per_frame) if per_frame else None,
        },
    }
    return res


def boot_to_title(args):
    import capture  # same directory; shares the oracle ini checks and title detection
    return capture.boot_and_wait_title(settle_s=args.settle)


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--samples", type=int, default=2000)
    ap.add_argument("--interval-ms", type=float, default=2.0)
    ap.add_argument("--out", type=pathlib.Path, default=OUT_DEFAULT)
    ap.add_argument("--boot", action="store_true", help="boot PCSX2 (oracle ini and its boot mode) and wait for the title")
    ap.add_argument("--settle", type=float, default=8.0, help="with --boot: seconds after title detection")
    ap.add_argument("--keep-running", action="store_true", help="with --boot: leave PCSX2 running")
    args = ap.parse_args(argv)
    if args.samples < 200:
        ap.error("--samples must be >= 200")

    session = None
    if args.boot:
        session = boot_to_title(args)
    try:
        p = pine.connect_retry(total=10.0)
        meta = {"pcsx2_version": p.version(), "game_id": p.game_id(), "elf_crc": p.uuid(),
                "status": pine.STATUS.get(p.status(), "?")}
        rows = sample_loop(p, args.samples, args.interval_ms / 1000.0)
        p.close()
    finally:
        if session is not None and not args.keep_running:
            session.stop()
    res = analyse(rows, args.interval_ms / 1000.0)
    res.update(meta)
    res["measured_at"] = datetime.datetime.now().astimezone().isoformat(timespec="seconds")
    if session is not None:
        res["session"] = session.describe()
    res["globals"] = {name: f"0x{va:08X} ({w}-bit)" for name, w, va in FIELDS}
    res["caveat"] = ("Corroborates, does not prove, the INTC chain rule (Q-01): only the outcome of the kernel's "
                     "cause-2 dispatch is observed. Wall-clock rates assume PCSX2 runs at full speed (frame limiter "
                     "59.94 Hz); ratios between counters do not depend on that.")
    args.out.mkdir(parents=True, exist_ok=True)
    stamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    jpath = args.out / f"flip_rate_{stamp}.json"
    jpath.write_text(json.dumps(res, indent=2))
    cpath = args.out / f"flip_rate_{stamp}.csv"
    with cpath.open("w") as f:
        f.write("t_send,t_recv," + ",".join(n for n, _, _ in FIELDS) + "\n")
        for a, b, v in rows:
            f.write(f"{a:.6f},{b:.6f}," + ",".join(
                f"{f32(x):.3f}" if FIELDS[i][0] in FLOATS else str(x) for i, x in enumerate(v)) + "\n")
    print(json.dumps({k: res[k] for k in res if k not in ("globals", "caveat", "session")}, indent=2))
    print(f"-> {jpath}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
