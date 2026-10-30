#!/usr/bin/env python3
"""PSNR / SSIM between two frame.png files (or two snapshot trees with the same sNNNN/frame.png layout), stdlib only.

  python -I tools/ours/perf/frame_psnr.py A.png B.png
  python -I tools/ours/perf/frame_psnr.py --trees DIR_A DIR_B      # every */frame.png present in both

Reports per pair: PSNR over RGB (dB, inf when identical), SSIM of the luma (8x8 windows, step 4), the share of pixels
whose largest channel difference exceeds 32 ("big": missing / extra geometry shows up here, rounding does not), and
the largest channel difference. Used for the native renderer's visual-equivalence check (docs/ANALYSIS/31 §6).
"""
import argparse
import math
import os
import struct
import sys
import zlib


def read_png(path):
    data = open(path, 'rb').read()
    if data[:8] != b'\x89PNG\r\n\x1a\n':
        raise ValueError(path + ': not a PNG')
    pos, idat, w = 8, [], 0
    while pos < len(data):
        n, typ = struct.unpack('>I4s', data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + n]
        pos += 12 + n
        if typ == b'IHDR':
            w, h, depth, ctype, _, _, inter = struct.unpack('>IIBBBBB', body)
            if depth != 8 or inter != 0 or ctype not in (2, 6):
                raise ValueError(path + ': only 8-bit RGB/RGBA non-interlaced')
            bpp = 3 if ctype == 2 else 4
        elif typ == b'IDAT':
            idat.append(body)
        elif typ == b'IEND':
            break
    raw = zlib.decompress(b''.join(idat))
    stride = w * bpp
    out = bytearray(w * h * 3)
    prev = bytearray(stride)
    p = 0
    for y in range(h):
        f = raw[p]
        line = bytearray(raw[p + 1:p + 1 + stride])
        p += 1 + stride
        if f == 1:
            for i in range(bpp, stride):
                line[i] = (line[i] + line[i - bpp]) & 255
        elif f == 2:
            for i in range(stride):
                line[i] = (line[i] + prev[i]) & 255
        elif f == 3:
            for i in range(stride):
                a = line[i - bpp] if i >= bpp else 0
                line[i] = (line[i] + ((a + prev[i]) >> 1)) & 255
        elif f == 4:
            for i in range(stride):
                a = line[i - bpp] if i >= bpp else 0
                b = prev[i]
                c = prev[i - bpp] if i >= bpp else 0
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                pr = a if (pa <= pb and pa <= pc) else (b if pb <= pc else c)
                line[i] = (line[i] + pr) & 255
        for x in range(w):
            out[(y * w + x) * 3:(y * w + x) * 3 + 3] = line[x * bpp:x * bpp + 3]
        prev = line
    return w, h, out


def compare(a_path, b_path):
    wa, ha, a = read_png(a_path)
    wb, hb, b = read_png(b_path)
    if (wa, ha) != (wb, hb):
        return None
    n = len(a)
    se = 0
    big = 0
    mx = 0
    for i in range(0, n, 3):
        d0, d1, d2 = a[i] - b[i], a[i + 1] - b[i + 1], a[i + 2] - b[i + 2]
        se += d0 * d0 + d1 * d1 + d2 * d2
        m = max(abs(d0), abs(d1), abs(d2))
        if m > mx:
            mx = m
        if m > 32:
            big += 1
    mse = se / n
    psnr = float('inf') if mse == 0 else 10 * math.log10(255 * 255 / mse)
    # SSIM on luma, 8x8 windows every 4 pixels
    ya = [0.299 * a[i] + 0.587 * a[i + 1] + 0.114 * a[i + 2] for i in range(0, n, 3)]
    yb = [0.299 * b[i] + 0.587 * b[i + 1] + 0.114 * b[i + 2] for i in range(0, n, 3)]
    c1, c2 = (0.01 * 255) ** 2, (0.03 * 255) ** 2
    tot, cnt = 0.0, 0
    for y0 in range(0, ha - 7, 4):
        for x0 in range(0, wa - 7, 4):
            sa = sb = saa = sbb = sab = 0.0
            for y in range(y0, y0 + 8):
                r = y * wa
                for x in range(x0, x0 + 8):
                    pa, pb = ya[r + x], yb[r + x]
                    sa += pa
                    sb += pb
                    saa += pa * pa
                    sbb += pb * pb
                    sab += pa * pb
            ma, mb = sa / 64, sb / 64
            va, vb, cv = saa / 64 - ma * ma, sbb / 64 - mb * mb, sab / 64 - ma * mb
            tot += ((2 * ma * mb + c1) * (2 * cv + c2)) / ((ma * ma + mb * mb + c1) * (va + vb + c2))
            cnt += 1
    return psnr, tot / max(cnt, 1), big / (wa * ha), mx


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('a')
    ap.add_argument('b')
    ap.add_argument('--trees', action='store_true')
    a = ap.parse_args()
    pairs = []
    if a.trees:
        for d in sorted(os.listdir(a.a)):
            fa, fb = os.path.join(a.a, d, 'frame.png'), os.path.join(a.b, d, 'frame.png')
            if os.path.isfile(fa) and os.path.isfile(fb):
                pairs.append((d, fa, fb))
    else:
        pairs.append((os.path.basename(a.a), a.a, a.b))
    print('| frame | PSNR dB | SSIM | pixels off > 32 | max diff |')
    print('|---|---|---|---|---|')
    for name, fa, fb in pairs:
        r = compare(fa, fb)
        if r is None:
            print(f'| {name} | size differs | | | |')
            continue
        psnr, ssim, big, mx = r
        print(f'| {name} | {psnr:.2f} | {ssim:.4f} | {100 * big:.3f} % | {mx} |')


if __name__ == '__main__':
    sys.exit(main())
