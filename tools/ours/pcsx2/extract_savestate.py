#!/usr/bin/env python3
"""Extract a PCSX2 2.x save state (.p2s) and optionally verify EE RAM against the game ELF.

Container (observed on PCSX2 v2.8.2, [EmuCore] SavestateCompressionType=2):
  a plain ZIP ("PK\\x03\\x04") whose entries are stored (method 0) or Zstandard-compressed
  (method 93, one raw zstd frame per entry).  Entries: "PCSX2 Savestate Version.id",
  "PCSX2 Internal Structures.dat", eeMemory.bin (32 MiB), iopMemory.bin (2 MiB), eeHwRegs.bin,
  iopHwRegs.bin, Scratchpad.bin, vu0Memory.bin, vu1Memory.bin, vu0MicroMem.bin, vu1MicroMem.bin,
  SPU2.bin, USB.bin, PAD.bin, GS.bin, Screenshot.png.
  eeMemory.bin is the EE's 32 MiB physical RAM: guest kuseg VA 0x00xxxxxx and kseg0 0x80xxxxxx both
  map to file offset (VA & 0x1FFFFFFF).

Zstandard: the stdlib has no zstd codec, so method-93 entries are decompressed through the zstd.dll that
ships with PCSX2 (tools/third_party/pcsx2/zstd.dll) via ctypes; --zstd-dll overrides the path.  Methods
0 and 8 go through zipfile; anything else (9 = Deflate64, 95 = XZ/LZMA2) is reported, not extracted.

Usage:
  python extract_savestate.py <state.p2s> <outdir>              # extract every entry
  python extract_savestate.py <state.p2s> <outdir> --verify-elf extracted/disc/SLUS_216.21
      -> prints the ELF/RAM comparison used by docs/PCSX2.md (code band, #DirLst# tables,
         kernel-patch payloads) and writes <outdir>/verify.json
"""
import argparse
import ctypes
import hashlib
import json
import pathlib
import struct
import sys
import zipfile

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
DEFAULT_ZSTD_DLL = REPO / "tools" / "third_party" / "pcsx2" / "zstd.dll"

ZIP_METHOD_STORED, ZIP_METHOD_DEFLATE, ZIP_METHOD_ZSTD = 0, 8, 93


class Zstd:
    """Thin ctypes binding over zstd.dll: ZSTD_decompress(dst, dstCap, src, srcSize)."""

    def __init__(self, dll_path):
        self.lib = ctypes.CDLL(str(dll_path))
        self.lib.ZSTD_decompress.restype = ctypes.c_size_t
        self.lib.ZSTD_decompress.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p, ctypes.c_size_t]
        self.lib.ZSTD_isError.restype = ctypes.c_uint
        self.lib.ZSTD_isError.argtypes = [ctypes.c_size_t]
        self.lib.ZSTD_getErrorName.restype = ctypes.c_char_p
        self.lib.ZSTD_getErrorName.argtypes = [ctypes.c_size_t]
        self.lib.ZSTD_versionString.restype = ctypes.c_char_p

    def version(self):
        return self.lib.ZSTD_versionString().decode()

    def decompress(self, src, dst_size):
        dst = ctypes.create_string_buffer(dst_size)
        n = self.lib.ZSTD_decompress(dst, dst_size, src, len(src))
        if self.lib.ZSTD_isError(n):
            raise RuntimeError(f"zstd: {self.lib.ZSTD_getErrorName(n).decode()}")
        return dst.raw[:n]


def raw_entry_bytes(zf, info):
    """Read the compressed payload of a zip entry without going through zipfile's codec table."""
    fp = zf.fp
    fp.seek(info.header_offset)
    hdr = fp.read(30)
    sig, _, _, method, _, _, _, _, _, name_len, extra_len = struct.unpack("<IHHHHHIIIHH", hdr)
    if sig != 0x04034B50:
        raise ValueError(f"{info.filename}: bad local header signature {sig:#x}")
    fp.seek(info.header_offset + 30 + name_len + extra_len)
    return fp.read(info.compress_size)


def extract(state, outdir, zstd_dll):
    outdir.mkdir(parents=True, exist_ok=True)
    zstd = None
    report = []
    with zipfile.ZipFile(state) as zf:
        for info in zf.infolist():
            target = outdir / info.filename
            if info.compress_type in (ZIP_METHOD_STORED, ZIP_METHOD_DEFLATE):
                data = zf.read(info)
            elif info.compress_type == ZIP_METHOD_ZSTD:
                if zstd is None:
                    zstd = Zstd(zstd_dll)
                data = zstd.decompress(raw_entry_bytes(zf, info), info.file_size)
            else:
                report.append((info.filename, info.compress_type, info.file_size, "SKIPPED: unsupported method"))
                continue
            crc_ok = (zipfile.crc32(data) & 0xFFFFFFFF) == info.CRC
            target.write_bytes(data)
            report.append((info.filename, info.compress_type, len(data), "crc ok" if crc_ok else "CRC MISMATCH"))
    for name, method, size, status in report:
        print(f"  {name:36s} method {method:3d}  {size:10d} B  {status}")
    if zstd is not None:
        print(f"  (zstd.dll {zstd.version()} from {zstd_dll})")
    return report


# ---------------------------------------------------------------- verification against the ELF

def load_elf_image(elf_path):
    """Return (vaddr, bytes) of the single PT_LOAD with p_filesz>0 (SLUS_216.21: VA 0x100000, 0x8ACC80 B)."""
    d = elf_path.read_bytes()
    e_phoff = struct.unpack_from("<I", d, 0x1C)[0]
    e_phentsize, e_phnum = struct.unpack_from("<HH", d, 0x2A)
    segs = []
    for i in range(e_phnum):
        p_type, p_off, p_va, _p_pa, p_filesz, p_memsz, _f, _a = struct.unpack_from("<8I", d, e_phoff + i * e_phentsize)
        if p_type == 1 and p_filesz:
            segs.append((p_va, d[p_off:p_off + p_filesz], p_memsz))
    if len(segs) != 1:
        raise ValueError(f"expected one loadable segment with data, found {len(segs)}")
    return segs[0]


def count_diff(a, b):
    return sum(1 for x, y in zip(a, b) if x != y)


def diff_runs(a, b, base, limit=20):
    """First `limit` differing runs as (va, length)."""
    runs = []
    i, n = 0, min(len(a), len(b))
    while i < n and len(runs) < limit:
        if a[i] != b[i]:
            j = i
            while j < n and a[j] != b[j]:
                j += 1
            runs.append((base + i, j - i))
            i = j
        else:
            i += 1
    return runs


def verify(outdir, elf_path):
    ee = (outdir / "eeMemory.bin").read_bytes()
    if len(ee) != 32 * 1024 * 1024:
        print(f"eeMemory.bin is {len(ee)} bytes, expected 33554432", file=sys.stderr)
    va, img, memsz = load_elf_image(elf_path)
    phys = va & 0x1FFFFFFF
    ram = ee[phys:phys + len(img)]
    res = {"elf": str(elf_path), "elf_sha256": hashlib.sha256(elf_path.read_bytes()).hexdigest(),
           "segment_va": va, "segment_filesz": len(img), "segment_memsz": memsz}

    # (a) code band 0x100000-0x5A1400 and the rest of the single PROGBITS `main` section
    #     (docs/ANALYSIS/00_elf_layout.md: no .text/.data split; .bss = [0x7CDE80, 0x9ACC80) zero in file)
    bands = {"code_0x100000_0x5A1400": (0x100000, 0x5A1400),
             "initdata_0x5A1400_0x7CDE80": (0x5A1400, 0x7CDE80),
             "bss_0x7CDE80_0x9ACC80": (0x7CDE80, va + len(img))}
    res["bands"] = {}
    for name, (lo, hi) in bands.items():
        hi = min(hi, va + len(img))
        a, b = img[lo - va:hi - va], ram[lo - va:hi - va]
        n = count_diff(a, b)
        res["bands"][name] = {"start": lo, "end": hi, "bytes": hi - lo, "differing_bytes": n,
                              "first_runs": [{"va": r[0], "len": r[1]} for r in diff_runs(a, b, lo, 8)]}
    res["whole_image_differing_bytes"] = sum(v["differing_bytes"] for v in res["bands"].values())

    # (b) the 149 #DirLst# tables, VA 0x5E5150-0x6784B8 (docs/DISC_LAYOUT.md §6)
    lo, hi = 0x5E5150, 0x6784B8
    a, b = img[lo - va:hi - va], ram[lo - va:hi - va]
    marker = b"#DirLst#"
    elf_tables = [lo + i for i in range(0, len(a) - 8) if a[i:i + 8] == marker]
    ram_tables = [lo + i for i in range(0, len(b) - 8) if b[i:i + 8] == marker]
    res["dirlst"] = {"start": lo, "end": hi, "bytes": hi - lo, "differing_bytes": count_diff(a, b),
                     "tables_in_elf": len(elf_tables), "tables_in_ram": len(ram_tables),
                     "marker_positions_equal": elf_tables == ram_tables,
                     "first_header_ram": b[0:24].hex(), "first_header_elf": a[0:24].hex()}
    # per-table byte-equality
    bad = []
    for k, t in enumerate(elf_tables):
        end = elf_tables[k + 1] if k + 1 < len(elf_tables) else hi
        s = t - 12  # header starts 12 bytes before the marker
        if img[s - va:end - va] != ram[s - va:end - va]:
            bad.append(t)
    res["dirlst"]["tables_differing"] = len(bad)

    # (c) kernel-patch payloads (docs/ANALYSIS/12_irx_rpc_threads.md §5): source bytes in the ELF image,
    #     destination in kseg0 -> physical offsets in eeMemory.bin
    payloads = {
        "execps2_0x80074000": (0x77FBD8, 0x74000, 1960, "InitExecPS2: only if PatchIsNeeded (old ROM)"),
        "tlb_0x80075000": (0x77F568, 0x75000, 816, "InitTLBFunctions: always"),
        "alarm_0x80076000": (0x7803A0, 0x76000, 1856, "InitAlarm: only if (T3_MODE & 0x100)==0"),
        "alarm_stub_0x00082000": (0x780AE0, 0x82000, 40, "InitAlarm T3 interrupt stub"),
    }
    res["kernel_patches"] = {}
    for name, (src_va, dst_phys, n, cond) in payloads.items():
        src = img[src_va - va:src_va - va + n]
        dst = ee[dst_phys:dst_phys + n]
        res["kernel_patches"][name] = {
            "source_va": src_va, "dest_phys": dst_phys, "bytes": n, "condition": cond,
            "present": src == dst, "dest_all_zero": not any(dst),
            "matching_bytes": sum(1 for x, y in zip(src, dst) if x == y),
            "dest_first16": dst[:16].hex(), "src_first16": src[:16].hex()}
    return res


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("state", type=pathlib.Path)
    ap.add_argument("outdir", type=pathlib.Path)
    ap.add_argument("--zstd-dll", type=pathlib.Path, default=DEFAULT_ZSTD_DLL)
    ap.add_argument("--verify-elf", type=pathlib.Path)
    ap.add_argument("--no-extract", action="store_true", help="only verify an already extracted outdir")
    args = ap.parse_args(argv)

    if not args.no_extract:
        print(f"extracting {args.state} -> {args.outdir}")
        extract(args.state, args.outdir, args.zstd_dll)
    if args.verify_elf:
        res = verify(args.outdir, args.verify_elf)
        (args.outdir / "verify.json").write_text(json.dumps(res, indent=2))
        print(json.dumps(res, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
