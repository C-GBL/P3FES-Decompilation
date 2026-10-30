"""Checks the in-between pictures that `p3fes --fps N --hfr-dump DIR` wrote (docs/ANALYSIS/32 §9).

For every game frame dumped: <tag>_a.png (frame A replayed), <tag>_mNN.png (the in-between picture at alpha NN %),
<tag>_b.png (frame B replayed), <tag>_b_latched.png (B as the renderer latched it on the exact path). Prints per frame:
  replay   B replayed == B latched (byte-identical pictures: the record / bank / replay mechanism is exact)
  moved    pixels where A and B differ (> 24 in a channel): how much changed between the two game frames
  between  of the in-between picture's pixels that differ from B, the share that lies between A and B per channel
           (min(A,B) - 24 <= m <= max(A,B) + 24) -- blended motion stays between the two frames
  stray    pixels where A and B agree (< 8) but the in-between picture differs from both by > 48: something drawn
           where neither frame has it (a misplaced triangle, a hole, a wrong instance match)
Plain CPython (-I); PNG decoding with zlib (8-bit RGB / RGBA, non-interlaced, as gs::write_png writes them).
Usage: python -I tools/ours/hfr/hfr_dump_check.py DIR [--max-stray 0.002]
"""
import os
import re
import struct
import sys
import zlib


def read_png(path):
    data = open(path, 'rb').read()
    if data[:8] != b'\x89PNG\r\n\x1a\n':
        raise ValueError(path + ': not a PNG')
    pos, idat, w, h, ctype = 8, [], 0, 0, 0
    while pos < len(data):
        n, kind = struct.unpack('>I4s', data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + n]
        if kind == b'IHDR':
            w, h, depth, ctype, _, _, interlace = struct.unpack('>IIBBBBB', body)
            if depth != 8 or ctype not in (2, 6) or interlace:
                raise ValueError(path + ': unsupported PNG layout')
        elif kind == b'IDAT':
            idat.append(body)
        pos += 12 + n
    bpp = 4 if ctype == 6 else 3
    raw = zlib.decompress(b''.join(idat))
    stride = w * bpp
    out = bytearray(h * stride)
    prev = bytearray(stride)
    for y in range(h):
        f = raw[y * (stride + 1)]
        line = bytearray(raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)])
        if f == 1:
            for i in range(bpp, stride):
                line[i] = (line[i] + line[i - bpp]) & 0xFF
        elif f == 2:
            for i in range(stride):
                line[i] = (line[i] + prev[i]) & 0xFF
        elif f == 3:
            for i in range(stride):
                left = line[i - bpp] if i >= bpp else 0
                line[i] = (line[i] + ((left + prev[i]) >> 1)) & 0xFF
        elif f == 4:
            for i in range(stride):
                a = line[i - bpp] if i >= bpp else 0
                b = prev[i]
                c = prev[i - bpp] if i >= bpp else 0
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                pr = a if pa <= pb and pa <= pc else (b if pb <= pc else c)
                line[i] = (line[i] + pr) & 0xFF
        out[y * stride:(y + 1) * stride] = line
        prev = line
    return w, h, bpp, bytes(out)


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    d = sys.argv[1]
    max_stray = 0.002
    if '--max-stray' in sys.argv:
        max_stray = float(sys.argv[sys.argv.index('--max-stray') + 1])
    tags = sorted({m.group(1) for f in os.listdir(d) if (m := re.match(r'hfr_(\d+)_a\.png$', f))})
    bad = 0
    print(f'{"frame":>10} {"alpha":>5} {"replay":>7} {"moved":>7} {"between":>8} {"stray":>8}')
    for t in tags:
        mids = [f for f in os.listdir(d) if re.match(rf'hfr_{t}_m(\d+)\.png$', f)]
        if not mids:
            continue
        alpha = int(re.match(rf'hfr_{t}_m(\d+)\.png$', mids[0]).group(1))
        w, h, bpp, a = read_png(os.path.join(d, f'hfr_{t}_a.png'))
        _, _, _, b = read_png(os.path.join(d, f'hfr_{t}_b.png'))
        _, _, _, m = read_png(os.path.join(d, mids[0]))
        lat = os.path.join(d, f'hfr_{t}_b_latched.png')
        replay = 'n/a'
        if os.path.exists(lat):
            _, _, _, bl = read_png(lat)
            replay = 'equal' if bl == b else 'DIFF'
        n = w * h
        moved = diff_b = between = stray = 0
        for i in range(0, n * bpp, bpp):
            ab = max(abs(a[i + c] - b[i + c]) for c in range(3))
            if ab > 24:
                moved += 1
            mb = max(abs(m[i + c] - b[i + c]) for c in range(3))
            if mb > 24:
                diff_b += 1
                if all(min(a[i + c], b[i + c]) - 24 <= m[i + c] <= max(a[i + c], b[i + c]) + 24 for c in range(3)):
                    between += 1
            if ab < 8:
                ma = max(abs(m[i + c] - a[i + c]) for c in range(3))
                if ma > 48 and mb > 48:
                    stray += 1
        share = stray / n
        flag = ''
        if replay == 'DIFF' or share > max_stray:
            bad += 1
            flag = '  <-- check'
        print(f'{t:>10} {alpha:>4}% {replay:>7} {moved / n:>6.1%} {between / diff_b if diff_b else 1.0:>8.1%} {share:>8.3%}{flag}')
    print(f'{len(tags)} frames, {bad} to check')
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
