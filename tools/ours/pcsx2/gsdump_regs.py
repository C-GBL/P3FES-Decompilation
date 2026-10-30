#!/usr/bin/env python3
"""Walk a PCSX2 GS dump (.gs / .gs.zst, "Save Single Frame GS Dump") and list the GIF register writes that
place textures and frame buffers: BITBLTBUF / TRXPOS / TRXREG / TRXDIR and the IMAGE qwords that follow, TEX0_1/2,
TEX2_1/2, FRAME_1/2, ZBUF_1/2 -- per transfer packet and path. The output is the reference the host's
`--trace-gs A-B` log (runtime/app/game_host.cpp) is compared against when a frame renders differently.

Dump format (PCSX2 2.x GSDumpFile, pcsx2/GS/GSDump.cpp): optional header (crc == 0xFFFFFFFF, u32 header_size,
GSDumpHeader with the state version, the serial and a screenshot), u32 state_size + state, 8192 bytes of GS
privileged registers, then packets: 0 = Transfer (u8 path, u32 size, data), 1 = VSync (u8 field),
2 = ReadFIFO (u32 size), 3 = Registers (8192 bytes). GIF tags per the GS User's Manual: NLOOP[14:0], EOP[15],
PRE[46], PRIM[57:47], FLG[59:58] (0 PACKED, 1 REGLIST, 2/3 IMAGE), NREG[63:60], REGS[127:64] (4 bits each).

Zstandard is decoded through PCSX2's zstd.dll (as extract_savestate.py does): the frame size is read from
the zstd frame header through ZSTD_getFrameContentSize, or decoded in growing buffers when unknown.

Usage: python -I tools/ours/pcsx2/gsdump_regs.py extracted/_pcsx2/title_runC/gsdump.gs.zst [--all] [--out FILE]
"""
import argparse
import ctypes
import pathlib
import struct
import sys

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
DEFAULT_ZSTD_DLL = REPO / "tools" / "third_party" / "pcsx2" / "zstd.dll"

REG_NAMES = {
    0x00: "PRIM", 0x01: "RGBAQ", 0x02: "ST", 0x03: "UV", 0x04: "XYZF2", 0x05: "XYZ2", 0x06: "TEX0_1", 0x07: "TEX0_2",
    0x08: "CLAMP_1", 0x09: "CLAMP_2", 0x0A: "FOG", 0x0C: "XYZF3", 0x0D: "XYZ3", 0x0E: "A+D", 0x0F: "NOP",
    0x14: "TEX1_1", 0x15: "TEX1_2", 0x16: "TEX2_1", 0x17: "TEX2_2", 0x18: "XYOFFSET_1", 0x19: "XYOFFSET_2",
    0x1A: "PRMODECONT", 0x1B: "PRMODE", 0x1C: "TEXCLUT", 0x22: "SCANMSK", 0x34: "MIPTBP1_1", 0x35: "MIPTBP1_2",
    0x36: "MIPTBP2_1", 0x37: "MIPTBP2_2", 0x3B: "TEXA", 0x3D: "FOGCOL", 0x3F: "TEXFLUSH", 0x40: "SCISSOR_1",
    0x41: "SCISSOR_2", 0x42: "ALPHA_1", 0x43: "ALPHA_2", 0x44: "DIMX", 0x45: "DTHE", 0x46: "COLCLAMP", 0x47: "TEST_1",
    0x48: "TEST_2", 0x49: "PABE", 0x4A: "FBA_1", 0x4B: "FBA_2", 0x4C: "FRAME_1", 0x4D: "FRAME_2", 0x4E: "ZBUF_1",
    0x4F: "ZBUF_2", 0x50: "BITBLTBUF", 0x51: "TRXPOS", 0x52: "TRXREG", 0x53: "TRXDIR", 0x54: "HWREG",
    0x60: "SIGNAL", 0x61: "FINISH", 0x62: "LABEL",
}
PLACEMENT = {0x06, 0x07, 0x16, 0x17, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53}
PSM = {0: "CT32", 1: "CT24", 2: "CT16", 10: "CT16S", 19: "T8", 20: "T4", 27: "T8H", 36: "T4HL", 44: "T4HH",
       48: "Z32", 49: "Z24", 50: "Z16", 58: "Z16S"}


class Zstd:
    def __init__(self, dll_path):
        self.lib = ctypes.CDLL(str(dll_path))
        self.lib.ZSTD_decompress.restype = ctypes.c_size_t
        self.lib.ZSTD_decompress.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p, ctypes.c_size_t]
        self.lib.ZSTD_isError.restype = ctypes.c_uint
        self.lib.ZSTD_isError.argtypes = [ctypes.c_size_t]
        self.lib.ZSTD_getErrorName.restype = ctypes.c_char_p
        self.lib.ZSTD_getErrorName.argtypes = [ctypes.c_size_t]
        self.lib.ZSTD_getFrameContentSize.restype = ctypes.c_ulonglong
        self.lib.ZSTD_getFrameContentSize.argtypes = [ctypes.c_void_p, ctypes.c_size_t]

    def decompress(self, src):
        size = self.lib.ZSTD_getFrameContentSize(src, len(src))
        sizes = [size] if size < (1 << 62) and size > 0 else [len(src) * 8, len(src) * 32, len(src) * 128]
        for cap in sizes:
            dst = ctypes.create_string_buffer(cap)
            n = self.lib.ZSTD_decompress(dst, cap, src, len(src))
            if not self.lib.ZSTD_isError(n):
                return dst.raw[:n]
            err = self.lib.ZSTD_getErrorName(n).decode()
            if "Destination buffer is too small" not in err:
                raise RuntimeError("zstd: " + err)
        raise RuntimeError("zstd: output too large")


def fmt_reg(reg, v):
    n = REG_NAMES.get(reg, f"reg{reg:02X}")
    if reg in (0x06, 0x07, 0x16, 0x17):  # TEX0 / TEX2
        tbp0, tbw, psm, tw, th = v & 0x3FFF, (v >> 14) & 0x3F, (v >> 20) & 0x3F, (v >> 26) & 0xF, (v >> 30) & 0xF
        tcc, tfx, cbp, cpsm, csm, csa, cld = (v >> 34) & 1, (v >> 35) & 3, (v >> 37) & 0x3FFF, (v >> 51) & 0xF, (v >> 55) & 1, (v >> 56) & 0x1F, (v >> 61) & 7
        return (f"{n} tbp0=0x{tbp0:04X} tbw={tbw} psm={PSM.get(psm, psm)} {1 << tw}x{1 << th} tcc={tcc} tfx={tfx} "
                f"cbp=0x{cbp:04X} cpsm={PSM.get(cpsm, cpsm)} csm={csm} csa={csa} cld={cld}")
    if reg in (0x4C, 0x4D):
        return f"{n} fbp=0x{v & 0x1FF:03X} fbw={(v >> 16) & 0x3F} psm={PSM.get((v >> 24) & 0x3F, (v >> 24) & 0x3F)} fbmsk=0x{(v >> 32) & 0xFFFFFFFF:08X}"
    if reg in (0x4E, 0x4F):
        return f"{n} zbp=0x{v & 0x1FF:03X} psm={PSM.get((v >> 24) & 0xF, (v >> 24) & 0xF)} zmsk={(v >> 32) & 1}"
    if reg == 0x50:
        return (f"BITBLTBUF sbp=0x{v & 0x3FFF:04X} sbw={(v >> 16) & 0x3F} spsm={PSM.get((v >> 24) & 0x3F, (v >> 24) & 0x3F)} "
                f"dbp=0x{(v >> 32) & 0x3FFF:04X} dbw={(v >> 48) & 0x3F} dpsm={PSM.get((v >> 56) & 0x3F, (v >> 56) & 0x3F)}")
    if reg == 0x51:
        return f"TRXPOS ssax={v & 0x7FF} ssay={(v >> 16) & 0x7FF} dsax={(v >> 32) & 0x7FF} dsay={(v >> 48) & 0x7FF} dir={(v >> 59) & 3}"
    if reg == 0x52:
        return f"TRXREG rrw={v & 0xFFF} rrh={(v >> 32) & 0xFFF}"
    if reg == 0x53:
        return f"TRXDIR xdir={v & 3}"
    return f"{n} 0x{v:016X}"


class Walker:
    def __init__(self, out, want_all):
        self.out = out
        self.want_all = want_all
        self.counts = {}
        self.image_qw = 0
        self.packets = 0
        self.vsyncs = 0
        self.cur_prim = None

    def emit(self, path, reg, v):
        self.counts[reg] = self.counts.get(reg, 0) + 1
        if self.want_all or reg in PLACEMENT:
            self.out.append(f"P{path} {fmt_reg(reg, v)}")

    def gif(self, path, data):
        i, n = 0, len(data)
        while i + 16 <= n:
            lo, hi = struct.unpack_from("<QQ", data, i)
            i += 16
            nloop, eop, flg, nreg = lo & 0x7FFF, (lo >> 15) & 1, (lo >> 58) & 3, (lo >> 60) & 0xF
            nreg = nreg or 16
            if (lo >> 46) & 1:  # PRE: PRIM from the tag
                self.emit(path, 0x00, (lo >> 47) & 0x7FF)
            if flg == 0:  # PACKED
                for _ in range(nloop):
                    for r in range(nreg):
                        if i + 16 > n:
                            return
                        reg = (hi >> (4 * r)) & 0xF
                        a, b = struct.unpack_from("<QQ", data, i)
                        i += 16
                        if reg == 0x0E:
                            self.emit(path, b & 0xFF, a)
                        elif reg in (0x06, 0x07):  # TEX0 in PACKED form is the raw 64 bits
                            self.emit(path, reg, a)
                        elif reg in (0x00, 0x0A, 0x0F) or reg >= 0x10:
                            self.emit(path, reg, a)
                        else:
                            self.counts[reg] = self.counts.get(reg, 0) + 1  # vertex regs: counted only
            elif flg == 1:  # REGLIST
                total = nloop * nreg
                for k in range(total):
                    if i + 8 > n:
                        return
                    reg = (hi >> (4 * (k % nreg))) & 0xF
                    (a,) = struct.unpack_from("<Q", data, i)
                    i += 8
                    if reg in (0x00, 0x06, 0x07, 0x0A, 0x0F) or reg >= 0x10:
                        self.emit(path, reg, a)
                    else:
                        self.counts[reg] = self.counts.get(reg, 0) + 1
                if total & 1:
                    i += 8  # REGLIST pads to a qword
            else:  # IMAGE
                self.image_qw += nloop
                self.out.append(f"P{path} IMAGE {nloop} qw")
                i += 16 * nloop
            if eop and flg != 2 and flg != 3:
                pass  # PATH3 may chain more tags after EOP in one transfer; keep walking
        return

    def packet(self, pid, path, data, field=None):
        self.packets += 1
        if pid == 0:
            self.gif(path + 1, data)
        elif pid == 1:
            self.vsyncs += 1
            self.out.append(f"-- VSYNC field={field}")


def format_host_log(path):
    """The host's `--trace-gs A-B` lines (`[gs] vblank N P<path> reg 0xRR = 0xVVVV`) in this tool's notation."""
    import re
    rx = re.compile(r"\[gs\] vblank (\d+) P(\d) reg 0x([0-9A-Fa-f]+) = 0x([0-9A-Fa-f]+)")
    out, last_vb = [], None
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = rx.search(line)
        if not m:
            continue
        vb, p, reg, v = int(m.group(1)), int(m.group(2)), int(m.group(3), 16), int(m.group(4), 16)
        if vb != last_vb:
            out.append(f"-- VBLANK {vb}")
            last_vb = vb
        out.append(f"P{p} {fmt_reg(reg, v)}")
    return out


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("dump", type=pathlib.Path, help="PCSX2 .gs/.gs.zst dump, or with --host-log the host's log file")
    ap.add_argument("--all", action="store_true", help="every state-register write, not only the placement registers")
    ap.add_argument("--out", type=pathlib.Path)
    ap.add_argument("--zstd-dll", type=pathlib.Path, default=DEFAULT_ZSTD_DLL)
    ap.add_argument("--host-log", action="store_true", help="format a p3fes --trace-gs log instead of a PCSX2 dump")
    a = ap.parse_args(argv)
    if a.host_log:
        text = "\n".join(format_host_log(a.dump)) + "\n"
        if a.out:
            a.out.write_text(text, encoding="utf-8")
            print(f"-> {a.out}")
        else:
            sys.stdout.write(text)
        return 0
    raw = a.dump.read_bytes()
    if raw[:4] == b"\x28\xb5\x2f\xfd":
        raw = Zstd(a.zstd_dll).decompress(raw)
    pos = 0
    (crc,) = struct.unpack_from("<I", raw, pos)
    pos += 4
    header_note = ""
    if crc == 0xFFFFFFFF:
        # GSDumpHeader (pcsx2/GS/GSDump.h): state_version, state_size, serial_offset, serial_size,
        # screenshot_width, screenshot_height, screenshot_offset, screenshot_size; the serial and the
        # screenshot live inside the header block, the state follows it with no size prefix.
        (hsize,) = struct.unpack_from("<I", raw, pos)
        pos += 4
        header = raw[pos:pos + hsize]
        pos += hsize
        sv, state_size, so, ss = struct.unpack_from("<IIII", header, 0)
        serial = header[so:so + ss].rstrip(b"\0").decode("latin1") if ss else ""
        header_note = f"header {hsize} B state_version=0x{sv:X} serial={serial}"
    else:
        (state_size,) = struct.unpack_from("<I", raw, pos)
        pos += 4
    pos += state_size
    regs = raw[pos:pos + 8192]
    pos += 8192
    out = [f"# {a.dump} : {len(raw)} B decoded, crc=0x{crc:08X} {header_note} state {state_size} B"]
    w = Walker(out, a.all)
    while pos < len(raw):
        pid = raw[pos]
        pos += 1
        if pid == 0:
            path = raw[pos]
            (size,) = struct.unpack_from("<I", raw, pos + 1)
            pos += 5
            w.packet(0, path, raw[pos:pos + size])
            pos += size
        elif pid == 1:
            w.packet(1, 0, b"", raw[pos])
            pos += 1
        elif pid == 2:
            (size,) = struct.unpack_from("<I", raw, pos)
            pos += 4
            out.append(f"-- READFIFO {size} qw")
        elif pid == 3:
            pos += 8192
            out.append("-- REGISTERS")
        else:
            out.append(f"-- unknown packet id {pid} at {pos - 1}; stopping")
            break
    out.append(f"# packets {w.packets}, vsyncs {w.vsyncs}, image qwords {w.image_qw}")
    out.append("# register write counts: " + ", ".join(f"{REG_NAMES.get(r, hex(r))}={c}" for r, c in sorted(w.counts.items())))
    text = "\n".join(out) + "\n"
    if a.out:
        a.out.write_text(text, encoding="utf-8")
        print(f"{len(out)} lines -> {a.out}")
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
