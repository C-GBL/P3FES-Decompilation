#!/usr/bin/env python3
r"""A/B of a PCSX2 audio capture against the port's mix dump (ADR-0014 milestone 3; docs/PCSX2.md "Audio capture",
runtime/audio/README.md "A/B against PCSX2").

Both inputs are 48 kHz stereo 16-bit WAVs: PCSX2's `extracted/_pcsx2/audio/<name>.wav` (audio_capture.py) and the
port's `--dump-wav DIR/mix_48k.wav`. The sound effects are located by their onsets -- a jump of the short-time RMS
(10 ms windows) above the running floor (the ADX title BGM under them) -- and each SE window is compared on:
RMS and peak per channel (dBFS), the floor-corrected SE RMS (power subtraction of the preceding floor), the
spectral centroid of the first 250 ms (a 4096-point DFT of the mono sum, stdlib only), the -20 dB envelope
length (time until the floor-corrected RMS stays 20 dB below the SE's peak RMS), and the normalized
cross-correlation of the mono envelopes (not the waveforms: the BGM phase differs between the two runs).
`compare` first refines the alignment: the given onset of the port's side is moved by the lag (within +-40 ms)
that maximizes the NCC of the 1 ms floor-corrected envelopes over the first 250 ms, so a key-on frame and an
audible onset line up. The spectral score is per octave band (125 Hz .. 16 kHz) of the first 250 ms: the
floor-corrected band energy of each side in dB (the 250 ms before the onset subtracted in power), the
difference, and the log-spectral distance (RMS of the band differences after removing their mean).
`bgm` locates a stretch of the PCSX2 capture's ADX stream (no SE in it) inside the port's mix by envelope
cross-correlation and then by waveform NCC (+-2 ms), and prints the level of both and the least-squares gain
between them (what the port's stream path does to the same ADX samples).

Usage:
  python -I tools\ours\pcsx2\audio_ab.py profile <wav> [--window-ms 10]        # print the RMS profile
  python -I tools\ours\pcsx2\audio_ab.py onsets <wav> [--threshold-db 6]       # list SE onsets
  python -I tools\ours\pcsx2\audio_ab.py compare <pcsx2.wav> <ours.wav> [--ours-onsets f1,f2,..] [--pcsx2-onsets ..]
         [--window-ms 600] [--no-align] [--json out.json]
  python -I tools\ours\pcsx2\audio_ab.py bgm <pcsx2.wav> <ours.wav> --pcsx2-at SECONDS --ours-from FRAME --ours-to FRAME
         [--len-ms 1000] [--json out.json]
"""
import argparse
import cmath
import json
import math
import struct
import sys
import wave


def read_wav(path):
    with wave.open(path, "rb") as w:
        rate, ch, width, n = w.getframerate(), w.getnchannels(), w.getsampwidth(), w.getnframes()
        raw = w.readframes(n)
    if width != 2:
        raise SystemExit(f"{path}: {width * 8}-bit samples, want 16")
    data = struct.unpack("<%dh" % (len(raw) // 2), raw)
    if ch == 1:
        l = r = data
    elif ch == 2:
        l, r = data[0::2], data[1::2]
    else:
        raise SystemExit(f"{path}: {ch} channels")
    return rate, l, r


def rms_profile(l, r, rate, window_ms):
    w = max(1, rate * window_ms // 1000)
    out = []
    for i in range(0, min(len(l), len(r)) - w + 1, w):
        sl = sum(x * x for x in l[i:i + w])
        sr = sum(x * x for x in r[i:i + w])
        out.append((i, math.sqrt(sl / w), math.sqrt(sr / w)))
    return w, out


def db(x):
    return 20 * math.log10(x / 32768.0) if x > 0 else -999.0


def find_onsets(profile, threshold_db, hold_windows=30, floor_windows=20):
    """Windows whose mono RMS exceeds the median of the preceding `floor_windows` by threshold_db, with a hold-off."""
    onsets = []
    last = -10 ** 9
    for k in range(floor_windows, len(profile)):
        mono = [(p[1] + p[2]) / 2 for p in profile[k - floor_windows:k]]
        floor = sorted(mono)[len(mono) // 2]
        cur = (profile[k][1] + profile[k][2]) / 2
        if cur > 0 and floor >= 0 and 20 * math.log10((cur + 1) / (floor + 1)) >= threshold_db and k - last >= hold_windows:
            onsets.append((k, profile[k][0], floor, cur))
            last = k
    return onsets


def refine_onset(l, r, frame, w, rate):
    """Move the onset inside its window to the first 1 ms block whose RMS exceeds the window's floor by 6 dB."""
    blk = rate // 1000
    pre = [((l[i] + r[i]) / 2) ** 2 for i in range(max(0, frame - w), frame)]
    floor = math.sqrt(sum(pre) / max(1, len(pre)))
    for i in range(frame, min(frame + 2 * w, len(l) - blk), blk):
        s = math.sqrt(sum(((l[j] + r[j]) / 2) ** 2 for j in range(i, i + blk)) / blk)
        if s > 2 * floor + 8:
            return i
    return frame


def centroid(mono, rate, n=4096):
    seg = list(mono[:n]) + [0] * max(0, n - len(mono))
    # Hann window, radix-2 FFT (stdlib).
    x = [seg[i] * (0.5 - 0.5 * math.cos(2 * math.pi * i / n)) for i in range(n)]
    def fft(a):
        m = len(a)
        if m == 1:
            return a
        e, o = fft(a[0::2]), fft(a[1::2])
        return [e[k] + cmath.exp(-2j * math.pi * k / m) * o[k] for k in range(m // 2)] + \
               [e[k] - cmath.exp(-2j * math.pi * k / m) * o[k] for k in range(m // 2)]
    X = fft([complex(v) for v in x])
    num = den = 0.0
    for k in range(1, n // 2):
        p = abs(X[k]) ** 2
        num += p * k * rate / n
        den += p
    return num / den if den > 0 else 0.0


def analyse_window(l, r, rate, onset, window_frames, floor_rms):
    seg_l, seg_r = l[onset:onset + window_frames], r[onset:onset + window_frames]
    n = len(seg_l)
    rms_l = math.sqrt(sum(x * x for x in seg_l) / n)
    rms_r = math.sqrt(sum(x * x for x in seg_r) / n)
    peak_l, peak_r = max(abs(x) for x in seg_l), max(abs(x) for x in seg_r)
    mono = [(a + b) / 2 for a, b in zip(seg_l, seg_r)]
    # 5 ms envelope, floor-corrected (power subtraction).
    blk = rate * 5 // 1000
    env = []
    for i in range(0, n - blk + 1, blk):
        s = sum(v * v for v in mono[i:i + blk]) / blk
        env.append(math.sqrt(max(0.0, s - floor_rms * floor_rms)))
    peak_env = max(env) if env else 0.0
    # length: last 5 ms block whose corrected RMS is within 20 dB of the envelope peak
    length_blocks = 0
    for i, e in enumerate(env):
        if e > peak_env / 10.0:
            length_blocks = i + 1
    se_rms = math.sqrt(max(0.0, (rms_l ** 2 + rms_r ** 2) / 2 - floor_rms ** 2))
    return {"onset_frame": onset, "rms_l_dbfs": round(db(rms_l), 2), "rms_r_dbfs": round(db(rms_r), 2),
            "peak_l": peak_l, "peak_r": peak_r, "peak_l_dbfs": round(db(peak_l), 2), "peak_r_dbfs": round(db(peak_r), 2),
            "floor_rms_dbfs": round(db(floor_rms), 2), "se_rms_corrected_dbfs": round(db(se_rms), 2),
            "se_to_floor_db": round(db(se_rms) - db(floor_rms), 2) if floor_rms > 0 else None,
            "centroid_hz_first_250ms": round(centroid(mono[:rate // 4], rate), 1),
            "length_ms_minus20db": length_blocks * 5, "env_peak_dbfs": round(db(peak_env), 2), "_env": env}


def ncc(a, b):
    n = min(len(a), len(b))
    a, b = a[:n], b[:n]
    ma, mb = sum(a) / n, sum(b) / n
    num = sum((x - ma) * (y - mb) for x, y in zip(a, b))
    da = math.sqrt(sum((x - ma) ** 2 for x in a))
    dbb = math.sqrt(sum((y - mb) ** 2 for y in b))
    return num / (da * dbb) if da > 0 and dbb > 0 else 0.0


def floor_before(l, r, rate, onset, ms=500):
    a = max(0, onset - rate * ms // 1000)
    seg = [((l[i] + r[i]) / 2) for i in range(a, onset)]
    return math.sqrt(sum(v * v for v in seg) / max(1, len(seg)))


def fft_iter(a):
    """Iterative radix-2 FFT of a list of complex (length a power of two), in place."""
    n = len(a)
    j = 0
    for i in range(1, n):
        bit = n >> 1
        while j & bit:
            j ^= bit
            bit >>= 1
        j |= bit
        if i < j:
            a[i], a[j] = a[j], a[i]
    m = 2
    while m <= n:
        w = cmath.exp(-2j * math.pi / m)
        half = m // 2
        tw = [w ** q for q in range(half)]
        for k in range(0, n, m):
            for q in range(half):
                u, v = a[k + q], a[k + q + half] * tw[q]
                a[k + q], a[k + q + half] = u + v, u - v
        m <<= 1
    return a


BANDS = [125, 250, 500, 1000, 2000, 4000, 8000, 16000]  # octave centres (Hz); edges c / sqrt 2 .. c * sqrt 2


def band_power(mono, rate, n=16384):
    m = min(len(mono), n)
    x = [complex(mono[i] * (0.5 - 0.5 * math.cos(2 * math.pi * i / max(1, m - 1)))) for i in range(m)] + [0j] * (n - m)
    X = fft_iter(x)
    out = []
    for c in BANDS:
        lo, hi = c / math.sqrt(2), min(c * math.sqrt(2), rate / 2)
        k0, k1 = max(1, int(lo * n / rate)), int(hi * n / rate)
        out.append(sum(abs(X[k]) ** 2 for k in range(k0, max(k0 + 1, k1))))
    return out


def env_1ms(l, r, rate, start, n_ms, floor_rms=0.0):
    blk = rate // 1000
    out = []
    for b in range(n_ms):
        i = start + b * blk
        if i < 0 or i + blk > len(l):
            out.append(0.0)
            continue
        s = sum(((l[j] + r[j]) / 2) ** 2 for j in range(i, i + blk)) / blk
        out.append(math.sqrt(max(0.0, s - floor_rms * floor_rms)))
    return out


def best_lag(ea, lb, rb, rate, fb, n_ms, max_lag_ms, floor_b):
    """The shift (ms) of side B's onset that maximizes the NCC of the 1 ms envelopes; (lag_ms, ncc)."""
    best = (0, -2.0)
    for lag in range(-max_lag_ms, max_lag_ms + 1):
        c = ncc(ea, env_1ms(lb, rb, rate, fb + lag * (rate // 1000), n_ms, floor_b))
        if c > best[1]:
            best = (lag, c)
    return best


def cmd_profile(args):
    rate, l, r = read_wav(args.wav)
    w, prof = rms_profile(l, r, rate, args.window_ms)
    print(f"{args.wav}: {rate} Hz, {len(l)} frames ({len(l) / rate:.3f} s), {len(prof)} windows of {w} frames")
    for i, (f, a, b) in enumerate(prof):
        print(f"{f:9d} {f / rate:8.3f}s  L {db(a):7.1f} dBFS  R {db(b):7.1f} dBFS")
    return 0


def cmd_onsets(args):
    rate, l, r = read_wav(args.wav)
    w, prof = rms_profile(l, r, rate, args.window_ms)
    for k, f, floor, cur in find_onsets(prof, args.threshold_db):
        rf = refine_onset(l, r, f, w, rate)
        print(f"onset window {k} frame {f} refined {rf} ({rf / rate:.3f} s): floor {db(floor):.1f} -> {db(cur):.1f} dBFS")
    return 0


def cmd_compare(args):
    rate_a, la, ra = read_wav(args.pcsx2)
    rate_b, lb, rb = read_wav(args.ours)
    if rate_a != rate_b:
        raise SystemExit(f"rates differ: {rate_a} vs {rate_b}")
    rate = rate_a
    window = rate * args.window_ms // 1000

    def onsets_of(l, r, given):
        if given:
            return [int(x, 0) for x in given.split(",")]
        w, prof = rms_profile(l, r, rate, 10)
        return [refine_onset(l, r, f, w, rate) for _, f, _, _ in find_onsets(prof, args.threshold_db)]

    oa = onsets_of(la, ra, args.pcsx2_onsets)
    ob = onsets_of(lb, rb, args.ours_onsets)
    print(f"PCSX2 onsets: {oa}")
    print(f"ours  onsets: {ob}")
    result = {"pcsx2": args.pcsx2, "ours": args.ours, "rate": rate, "window_ms": args.window_ms, "pairs": []}
    for i, (fa, fb) in enumerate(zip(oa, ob)):
        lag_ms, lag_ncc = 0, None
        n_al = min(args.window_ms, 250)
        if not args.no_align:
            ea = env_1ms(la, ra, rate, fa, n_al, floor_before(la, ra, rate, fa, 250))
            lag_ms, lag_ncc = best_lag(ea, lb, rb, rate, fb, n_al, 40, floor_before(lb, rb, rate, fb, 250))
            fb += lag_ms * (rate // 1000)
        A = analyse_window(la, ra, rate, fa, window, floor_before(la, ra, rate, fa))
        B = analyse_window(lb, rb, rate, fb, window, floor_before(lb, rb, rate, fb))
        corr = ncc(A.pop("_env"), B.pop("_env"))
        n250 = rate // 4

        def bands_of(l, r, f):
            # (floor-corrected dB, SE-dominated: the window's band energy at least twice the floor's)
            se = band_power([(l[k] + r[k]) / 2 for k in range(f, min(len(l), f + n250))], rate)
            fl = band_power([(l[k] + r[k]) / 2 for k in range(max(0, f - n250), f)], rate)
            return [(10 * math.log10(max(1e-9, a - b)), a >= 2 * b and a > 0) for a, b in zip(se, fl)]
        bA, bB = bands_of(la, ra, fa), bands_of(lb, rb, fb)
        used = [k for k in range(len(BANDS)) if bA[k][1] and bB[k][1]]
        d = [bA[k][0] - bB[k][0] for k in used]
        mean_d = sum(d) / len(d) if d else 0.0
        lsd = math.sqrt(sum((x - mean_d) ** 2 for x in d) / len(d)) if d else 0.0
        pair_bands = {str(c): {"pcsx2_db": round(x[0], 1), "ours_db": round(y[0], 1), "delta_db": round(x[0] - y[0], 1),
                               "se_dominated": bool(x[1] and y[1])} for c, x, y in zip(BANDS, bA, bB)}
        pair = {"index": i, "pcsx2": A, "ours": B, "envelope_ncc": round(corr, 4), "align_lag_ms": lag_ms,
                "align_ncc_250ms": round(lag_ncc, 4) if lag_ncc is not None else None,
                "bands_250ms": pair_bands, "bands_used": len(used), "band_mean_delta_db": round(mean_d, 2), "log_spectral_distance_db": round(lsd, 2),
                "delta_se_rms_db": round(A["se_rms_corrected_dbfs"] - B["se_rms_corrected_dbfs"], 2),
                "delta_floor_db": round(A["floor_rms_dbfs"] - B["floor_rms_dbfs"], 2),
                "delta_peak_l_db": round(A["peak_l_dbfs"] - B["peak_l_dbfs"], 2),
                "delta_centroid_hz": round(A["centroid_hz_first_250ms"] - B["centroid_hz_first_250ms"], 1),
                "delta_length_ms": A["length_ms_minus20db"] - B["length_ms_minus20db"]}
        result["pairs"].append(pair)
        print(f"\nSE {i}: PCSX2 @ {fa} ({fa / rate:.3f} s)  ours @ {fb} ({fb / rate:.3f} s)")
        for k in ("rms_l_dbfs", "rms_r_dbfs", "peak_l", "peak_r", "peak_l_dbfs", "floor_rms_dbfs", "se_rms_corrected_dbfs",
                  "se_to_floor_db", "centroid_hz_first_250ms", "length_ms_minus20db", "env_peak_dbfs"):
            print(f"  {k:26s} PCSX2 {A[k]!s:>10}   ours {B[k]!s:>10}")
        print(f"  envelope NCC {corr:.4f} (ours moved {lag_ms:+d} ms; NCC over the first 250 ms {pair['align_ncc_250ms']})")
        print("  octave bands of the first 250 ms, floor-corrected, dB (PCSX2 / ours / delta; * = SE-dominated on both sides):")
        print("   " + "  ".join(f"{c}{'*' if x[1] and y[1] else ''}:{x[0]:.1f}/{y[0]:.1f}/{x[0] - y[0]:+.1f}" for c, x, y in zip(BANDS, bA, bB)))
        print(f"  over the {len(used)} SE-dominated bands: mean delta {mean_d:+.2f} dB, log-spectral distance {lsd:.2f} dB")
    if args.json:
        with open(args.json, "w", encoding="utf-8") as f:
            json.dump(result, f, indent=2)
        print(f"-> {args.json}")
    return 0


def cmd_bgm(args):
    """Finds PCSX2's [at, at + len) inside ours [from, to); prints both levels and the gain between them."""
    rate, la, ra = read_wav(args.pcsx2)
    rate_b, lb, rb = read_wav(args.ours)
    if rate != rate_b:
        raise SystemExit("rates differ")
    a0 = int(args.pcsx2_at * rate)
    n_ms = args.len_ms
    blk = rate // 1000
    ea = env_1ms(la, ra, rate, a0, n_ms)
    eb_all = env_1ms(lb, rb, rate, args.ours_from, (args.ours_to - args.ours_from) // blk)
    best = (-2.0, 0)
    for k in range(0, len(eb_all) - n_ms):
        c = ncc(ea, eb_all[k:k + n_ms])
        if c > best[0]:
            best = (c, k)
    coarse = args.ours_from + best[1] * blk
    m = rate // 5
    ma = [(la[a0 + i] + ra[a0 + i]) / 2 for i in range(m)]
    fine = (-2.0, coarse)
    for off in range(coarse - 2 * blk, coarse + 2 * blk + 1):
        c = ncc(ma, [(lb[off + i] + rb[off + i]) / 2 for i in range(m)])
        if c > fine[0]:
            fine = (c, off)
    b0 = fine[1]
    n = n_ms * blk

    def rms(x):
        return math.sqrt(sum(v * v for v in x) / len(x))
    xa = [(la[a0 + i] + ra[a0 + i]) / 2 for i in range(n)]
    xb = [(lb[b0 + i] + rb[b0 + i]) / 2 for i in range(n)]
    g = sum(p * q for p, q in zip(xa, xb)) / max(1e-9, sum(q * q for q in xb))
    res = {"pcsx2_at_frame": a0, "ours_at_frame": b0, "envelope_ncc": round(best[0], 4), "waveform_ncc_200ms": round(fine[0], 4),
           "waveform_ncc_full": round(ncc(xa, xb), 4),
           "pcsx2_rms_l_dbfs": round(db(rms(la[a0:a0 + n])), 2), "pcsx2_rms_r_dbfs": round(db(rms(ra[a0:a0 + n])), 2),
           "ours_rms_l_dbfs": round(db(rms(lb[b0:b0 + n])), 2), "ours_rms_r_dbfs": round(db(rms(rb[b0:b0 + n])), 2),
           "ls_gain_pcsx2_from_ours": round(g, 4), "ls_gain_db": round(20 * math.log10(abs(g)), 2) if g else None,
           "ls_residual_rel_db": round(db(rms([p - g * q for p, q in zip(xa, xb)])) - db(rms(xa)), 2),
           "pcsx2_peak": max(max(abs(v) for v in la[a0:a0 + n]), max(abs(v) for v in ra[a0:a0 + n])),
           "ours_peak": max(max(abs(v) for v in lb[b0:b0 + n]), max(abs(v) for v in rb[b0:b0 + n]))}
    for k, v in res.items():
        print(f"  {k:30s} {v}")
    if args.json:
        with open(args.json, "w", encoding="utf-8") as f:
            json.dump(res, f, indent=2)
    return 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("profile")
    p.add_argument("wav")
    p.add_argument("--window-ms", type=int, default=10)
    o = sub.add_parser("onsets")
    o.add_argument("wav")
    o.add_argument("--window-ms", type=int, default=10)
    o.add_argument("--threshold-db", type=float, default=6.0)
    c = sub.add_parser("compare")
    c.add_argument("pcsx2")
    c.add_argument("ours")
    c.add_argument("--pcsx2-onsets")
    c.add_argument("--ours-onsets")
    c.add_argument("--threshold-db", type=float, default=6.0)
    c.add_argument("--window-ms", type=int, default=600)
    c.add_argument("--no-align", action="store_true")
    c.add_argument("--json")
    b = sub.add_parser("bgm")
    b.add_argument("pcsx2")
    b.add_argument("ours")
    b.add_argument("--pcsx2-at", type=float, required=True)
    b.add_argument("--ours-from", type=int, required=True)
    b.add_argument("--ours-to", type=int, required=True)
    b.add_argument("--len-ms", type=int, default=1000)
    b.add_argument("--json")
    args = ap.parse_args(argv)
    return {"profile": cmd_profile, "onsets": cmd_onsets, "compare": cmd_compare, "bgm": cmd_bgm}[args.cmd](args)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
