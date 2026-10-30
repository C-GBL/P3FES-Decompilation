#!/usr/bin/env python3
"""cvm_extract.py -- probe / list / extract CRI ROFS ".CVM" containers (Persona 3 FES, PS2).

Pure Python 3 stdlib. Re-runnable. Never loads a whole file into memory.

    python cvm_extract.py probe   <file.cvm> [--json out.json]
    python cvm_extract.py list    <file.cvm> [--tree]
    python cvm_extract.py extract <file.cvm> <outdir> [--manifest manifest.json]
                                  [--container-name NAME] [--prefix PREFIX] [--verify] [--log file]

========================================================================================
OBSERVED CVM HEADER LAYOUT  (DATA.CVM / BTL.CVM / BGM.CVM from the NTSC-U P3FES disc,
observed 2026-10-18; all three files have identical layout, only the size fields differ)
========================================================================================

The container is a 0x1800-byte (6 x 2048) CRI header followed by a plain, unencrypted
ISO9660 image whose logical sector 0 starts at file offset 0x1800.  (Verified: the
ISO9660 PVD magic "\\x01CD001" sits at 0x9800 = 0x1800 + 16*2048, and the PVD's
volume-space-size * 2048 == file size - 0x1800 for all three containers.)

The header appears to be two tagged chunks.  Every multi-byte header field below is
BIG-endian (observed by fitting the values; the ISO9660 part uses ISO's both-endian
fields as usual).

  off   size  value (DATA / BTL / BGM)                 interpretation
  ----  ----  ---------------------------------------  --------------------------------
  0x000   4   "CVMH"                                   chunk tag
  0x004   4   0                                        unknown (0 in all three)
  0x008   4   0x000007F4                               chunk payload size: 0x800-0xC = 0x7F4
                                                       -> CVMH chunk occupies [0x000,0x800)
  0x020   4   0xC8B6E000 / 0x37D31000 / 0x0F6E8000     == total .CVM file size in bytes
                                                       (3,367,428,096 / 936,579,072 / 258,899,968)
  0x024   7   6A 0B 01 0D 25 04 24                     ISO9660 7-byte date (yr-1900=106 ->2006,
                                                       month 11, day 1, 13:37:04, tz 0x24=36*15min
                                                       = UTC+9).  Matches the PVD creation-date
                                                       string "2006110113370400$" at 0x9800+813.
                                                       Identical in all three containers.
  0x02C   4   0x01010000                               unknown
  0x034   4   "ROFS"                                   format tag
  0x038  ..   "ROFSBLD Ver.1.52 2003-06-09"            builder tool name/version (ASCII, NUL-padded)
  0x078   8   01 1F 00 00 03 00 00 00                  unknown
  0x080  16   00 00 00 01  00 00 00 00  00 00 00 03 00 unknown (three small ints: 1, 0, 3)
  0x100   4   0x00000001                               unknown
  0x800   4   "ZONE"                                   chunk tag
  0x804   4   0                                        unknown
  0x808   4   0xC8B6D7F4 / 0x37D307F4 / 0x0F6E77F4     chunk payload size == file size - 0x80C
                                                       (DATA: 0xC8B6E000-0xC8B6D7F4 = 0x80C)
                                                       -> ZONE chunk runs to end of file, i.e. the
                                                       ISO image is the ZONE payload (after a
                                                       0x1000-byte zone header, see below).
  0x80C   4   3                                        unknown (3 in all three)
  0x810   4   0x00000410                               unknown (0x410 = 1040, same in all three)
  0x818   4   0x800                                    hypothesis: sector size (2048)
  0x81C   4   0x800                                    hypothesis: sector size (2048)
  0x820   4   2                                        unknown
  0x828   4   0x800                                    hypothesis: sector size (2048)
  0x82C   4   3                                        unknown
  0x834   4   0xC8B6C800 / 0x37D2F800 / 0x0F6E6800     == file size - 0x1800 == ISO image size
                                                       == PVD volume_space_size * 2048
  0x1000  32  41 00 00 02 00 00 00 00                  four 8-byte records starting with 0x41;
              41 01 00 02 00 00 00 00                  the 4th differs per container
              41 01 01 02 00 00 02 00                  (DATA: ...00 A9 25 24, BGM: ...00 28 07 38).
              41 AA 01 02 xx xx xx xx                  Meaning unknown (not the PVD sector count).
  0x1800      start of ISO9660 image (logical sector 0)

Everything not listed is zero.  Nothing in the header is needed to read the data: the
parser locates the PVD by scanning for "CD001" on 2048-byte boundaries, so the header
size is *detected*, not assumed.

ISO9660 specifics observed: system id "CRI ROFS", volume id "SAMPLE_GAME_TITLE",
publisher "PUBLISHER_NAME", logical block size 2048, one volume in the set, no Joliet
SVD (sector 17 is the 0xFF terminator), file names "NAME.EXT;1" (version suffix is
stripped on output).  Multi-extent records (flag bit 7) are supported but were not
observed; the ISO9660 limit of 4 GiB per extent is never approached here.
"""

import argparse
import datetime
import json
import os
import struct
import sys
import time

SECTOR = 2048
CHUNK = 4 * 1024 * 1024  # streaming copy chunk
PVD_SCAN_LIMIT = 64 * 1024

# ------------------------------------------------------------------------------------
# low-level helpers
# ------------------------------------------------------------------------------------


def _both_u32(b, off):
    """ISO9660 both-byte-order 32-bit field: LE copy at off, BE copy at off+4."""
    le = struct.unpack_from("<I", b, off)[0]
    be = struct.unpack_from(">I", b, off + 4)[0]
    if le != be:
        raise ValueError("both-endian u32 mismatch at %d: LE=%d BE=%d" % (off, le, be))
    return le


def _both_u16(b, off):
    le = struct.unpack_from("<H", b, off)[0]
    be = struct.unpack_from(">H", b, off + 2)[0]
    if le != be:
        raise ValueError("both-endian u16 mismatch at %d: LE=%d BE=%d" % (off, le, be))
    return le


def _iso_date7(b):
    """7-byte directory-record date -> ISO string (or None when all-zero)."""
    if len(b) < 7 or not any(b[:7]):
        return None
    y, mo, d, h, mi, s, tz = b[:7]
    tz = tz - 256 if tz > 127 else tz
    sign = "+" if tz >= 0 else "-"
    tzmin = abs(tz) * 15
    return "%04d-%02d-%02dT%02d:%02d:%02d%s%02d:%02d" % (
        1900 + y, mo, d, h, mi, s, sign, tzmin // 60, tzmin % 60)


# ------------------------------------------------------------------------------------
# container model
# ------------------------------------------------------------------------------------


class Entry(object):
    __slots__ = ("path", "name", "is_dir", "extents", "size", "flags", "date", "record_offsets")

    def __init__(self, path, name, is_dir, flags, date):
        self.path = path
        self.name = name
        self.is_dir = is_dir
        self.extents = []  # list of (lba, length)
        self.size = 0
        self.flags = flags
        self.date = date
        self.record_offsets = []  # absolute file offsets of the directory record(s)

    @property
    def lba(self):
        return self.extents[0][0] if self.extents else None


class CvmImage(object):
    """A CVM file = detected header + ISO9660 image. All offsets are absolute file offsets."""

    def __init__(self, path):
        self.path = path
        self.f = open(path, "rb")
        self.file_size = os.path.getsize(path)
        self.header = self._read_cvm_header()
        self.header_size = self._detect_header_size()
        self.pvd = self._read_pvd()
        self.block = self.pvd["logical_block_size"]
        if self.block != SECTOR:
            raise ValueError("unexpected logical block size %d" % self.block)

    # -- header -----------------------------------------------------------------------

    def _read_cvm_header(self):
        self.f.seek(0)
        b = self.f.read(0x1800)
        if len(b) < 0x1800:
            raise ValueError("file shorter than 0x1800 bytes")
        h = {
            "magic": b[0:4].decode("latin-1"),
            "cvmh_unknown_04": struct.unpack_from(">I", b, 4)[0],
            "cvmh_chunk_size_08": struct.unpack_from(">I", b, 8)[0],
            "file_size_20": struct.unpack_from(">I", b, 0x20)[0],
            "date_24": _iso_date7(b[0x24:0x2B]),
            "unknown_2c": struct.unpack_from(">I", b, 0x2C)[0],
            "tag_34": b[0x34:0x38].decode("latin-1"),
            "builder_38": b[0x38:0x78].split(b"\0", 1)[0].decode("latin-1", "replace"),
            "unknown_78": b[0x78:0x80].hex(),
            "unknown_80": b[0x80:0x90].hex(),
            "unknown_100": struct.unpack_from(">I", b, 0x100)[0],
            "zone_magic_800": b[0x800:0x804].decode("latin-1"),
            "zone_unknown_804": struct.unpack_from(">I", b, 0x804)[0],
            "zone_chunk_size_808": struct.unpack_from(">I", b, 0x808)[0],
            "zone_80c": struct.unpack_from(">I", b, 0x80C)[0],
            "zone_810": struct.unpack_from(">I", b, 0x810)[0],
            "zone_818": struct.unpack_from(">I", b, 0x818)[0],
            "zone_81c": struct.unpack_from(">I", b, 0x81C)[0],
            "zone_820": struct.unpack_from(">I", b, 0x820)[0],
            "zone_828": struct.unpack_from(">I", b, 0x828)[0],
            "zone_82c": struct.unpack_from(">I", b, 0x82C)[0],
            "zone_image_size_834": struct.unpack_from(">I", b, 0x834)[0],
            "zone_1000_records": [b[0x1000 + i * 8: 0x1008 + i * 8].hex() for i in range(4)],
        }
        return h

    def _detect_header_size(self):
        """Find the PVD ("\\x01CD001") on a 2048-byte boundary; header = that offset - 16*2048."""
        self.f.seek(0)
        blob = self.f.read(PVD_SCAN_LIMIT)
        for off in range(0, len(blob) - 6, SECTOR):
            if blob[off:off + 6] == b"\x01CD001":
                if off < 16 * SECTOR:
                    raise ValueError("PVD at 0x%X is before sector 16; not a CVM/ISO" % off)
                return off - 16 * SECTOR
        raise ValueError("no ISO9660 PVD found in the first %d bytes of %s" % (PVD_SCAN_LIMIT, self.path))

    # -- ISO9660 ----------------------------------------------------------------------

    def _abs(self, lba, within=0):
        return self.header_size + lba * SECTOR + within

    def read_sectors(self, lba, nbytes):
        self.f.seek(self._abs(lba))
        return self.f.read(nbytes)

    def _read_pvd(self):
        b = self.read_sectors(16, SECTOR)
        if b[0:6] != b"\x01CD001":
            raise ValueError("PVD magic mismatch")
        root = self._parse_record(b, 156)
        pvd = {
            "type": b[0],
            "standard_id": b[1:6].decode("latin-1"),
            "version": b[6],
            "system_id": b[8:40].decode("latin-1").rstrip(),
            "volume_id": b[40:72].decode("latin-1").rstrip(),
            "volume_space_size": _both_u32(b, 80),
            "volume_set_size": _both_u16(b, 120),
            "volume_sequence_number": _both_u16(b, 124),
            "logical_block_size": _both_u16(b, 128),
            "path_table_size": _both_u32(b, 132),
            "l_path_table_lba": struct.unpack_from("<I", b, 140)[0],
            "opt_l_path_table_lba": struct.unpack_from("<I", b, 144)[0],
            "m_path_table_lba": struct.unpack_from(">I", b, 148)[0],
            "opt_m_path_table_lba": struct.unpack_from(">I", b, 152)[0],
            "root_dir_lba": root["lba"],
            "root_dir_size": root["size"],
            "volume_set_id": b[190:318].decode("latin-1").rstrip(),
            "publisher_id": b[318:446].decode("latin-1").rstrip(),
            "data_preparer_id": b[446:574].decode("latin-1").rstrip(),
            "application_id": b[574:702].decode("latin-1").rstrip(),
            "creation_date": b[813:830].decode("latin-1"),
            "modification_date": b[830:847].decode("latin-1"),
            "file_structure_version": b[881],
        }
        # secondary descriptors / terminator
        descs = []
        lba = 17
        while True:
            d = self.read_sectors(lba, SECTOR)
            descs.append({"lba": lba, "type": d[0], "id": d[1:6].decode("latin-1")})
            if d[0] == 0xFF or lba > 32:
                break
            lba += 1
        pvd["other_descriptors"] = descs
        return pvd

    @staticmethod
    def _parse_record(b, off):
        """Parse one directory record at b[off:]. Returns dict or None for a 0-length pad."""
        rlen = b[off]
        if rlen == 0:
            return None
        if off + rlen > len(b):
            raise ValueError("directory record at %d overruns buffer (len %d)" % (off, rlen))
        ext_attr_len = b[off + 1]
        lba = _both_u32(b, off + 2)
        size = _both_u32(b, off + 10)
        date = _iso_date7(b[off + 18:off + 25])
        flags = b[off + 25]
        unit_size = b[off + 26]
        gap_size = b[off + 27]
        vol_seq = _both_u16(b, off + 28)
        nlen = b[off + 32]
        raw_name = b[off + 33:off + 33 + nlen]
        return {
            "len": rlen, "ext_attr_len": ext_attr_len, "lba": lba, "size": size,
            "date": date, "flags": flags, "unit_size": unit_size, "gap_size": gap_size,
            "vol_seq": vol_seq, "raw_name": raw_name,
        }

    @staticmethod
    def _clean_name(raw):
        name = raw.decode("latin-1")
        if ";" in name:
            name = name.rsplit(";", 1)[0]
        if name.endswith("."):
            name = name[:-1]
        return name

    def iter_directory(self, lba, size, dirpath):
        """Yield Entry objects for one directory extent (self/parent excluded, multi-extent merged)."""
        data = self.read_sectors(lba, size)
        off = 0
        pending = None  # Entry being assembled from multi-extent records
        while off < len(data):
            rec = self._parse_record(data, off)
            if rec is None:
                # zero padding: records never cross a sector boundary; skip to the next sector
                off = (off // SECTOR + 1) * SECTOR
                continue
            off += rec["len"]
            raw = rec["raw_name"]
            if raw in (b"\x00", b"\x01"):
                continue  # self / parent
            if rec["unit_size"] or rec["gap_size"]:
                raise ValueError("interleaved record not supported: %r in %s" % (raw, dirpath))
            if rec["vol_seq"] != 1:
                raise ValueError("record on volume %d: %r" % (rec["vol_seq"], raw))
            is_dir = bool(rec["flags"] & 0x02)
            name = self._clean_name(raw)
            if pending is not None and pending.name == name:
                e = pending
            else:
                if pending is not None:
                    raise ValueError("multi-extent chain for %s broken by %s" % (pending.name, name))
                e = Entry(dirpath + name, name, is_dir, rec["flags"], rec["date"])
            e.extents.append((rec["lba"], rec["size"]))
            e.size += rec["size"]
            e.record_offsets.append(self._abs(lba, off - rec["len"]))
            if rec["flags"] & 0x80:
                pending = e  # more extents follow
                continue
            pending = None
            yield e
        if pending is not None:
            raise ValueError("multi-extent chain for %s not terminated" % pending.name)

    def walk(self):
        """Depth-first walk of the whole tree. Yields Entry (a directory's entries, then recursion)."""
        root_lba, root_size = self.pvd["root_dir_lba"], self.pvd["root_dir_size"]
        stack = [(root_lba, root_size, "")]
        seen = set()
        while stack:
            lba, size, dirpath = stack.pop()
            if lba in seen:
                raise ValueError("directory loop at LBA %d" % lba)
            seen.add(lba)
            subdirs = []
            for e in self.iter_directory(lba, size, dirpath):
                yield e
                if e.is_dir:
                    subdirs.append(e)
            # push in reverse so siblings are visited in directory order
            for e in reversed(subdirs):
                if len(e.extents) != 1:
                    raise ValueError("multi-extent directory %s" % e.path)
                stack.append((e.extents[0][0], e.extents[0][1], e.path + "/"))

    # -- streaming --------------------------------------------------------------------

    def iter_file_chunks(self, entry):
        """Yield bytes chunks for a file entry, in order, never more than CHUNK at a time."""
        for lba, length in entry.extents:
            self.f.seek(self._abs(lba))
            remaining = length
            while remaining:
                n = min(CHUNK, remaining)
                buf = self.f.read(n)
                if len(buf) != n:
                    raise IOError("short read at LBA %d: wanted %d got %d (%s)" % (lba, n, len(buf), entry.path))
                remaining -= n
                yield buf

    def close(self):
        self.f.close()


# ------------------------------------------------------------------------------------
# format guessing (magic / extension only; conservative)
# ------------------------------------------------------------------------------------

# Tags observed at offset 0 in the P3FES containers (2026-10-18) plus a few well-known ones.
MAGIC_AT_0 = [
    (b"FLW0", "BF (Atlus flow script, FLW0)"),
    (b"MSG1", "BMD (Atlus message, MSG1)"),
    (b"AFS\x00", "AFS (CRI archive)"),
    (b"\x7fELF", "ELF"),
    (b"\x00\x00\x01\xba", "MPEG program stream (CRI Sofdec SFD / PSS video)"),
    (b"RIFF", "RIFF"),
    (b"CVMH", "CVM (CRI ROFS container)"),
    (b"TIM2", "TIM2 texture"),
    (b"BED4", "BED4-tagged (unknown semantics; battle effect data by location)"),
    (b"CIN\x00", "CIN-tagged (unknown semantics)"),
    (b"IECS", "Sony sound bank (IECS = 'SCEI' reversed; .HD header / .SQ sequence)"),
    (b"RESET", "IOP ROM image (romdir starts with RESET)"),
]
# Formats that carry their tag at offset 8 (u32 flags/id, u32 size, tag) -- observed values.
MAGIC_AT_8 = {
    b"TMX0": "TMX (Atlus texture, TMX0 @8)",
    b"PMD1": "PM1 (Atlus model container, PMD1 @8)",
    b"PMD2": "PM2 (Atlus model container, PMD2 @8)",
    b"PMD3": "PM3 (Atlus model container, PMD3 @8)",
    b"MSG1": "BMD (Atlus message, MSG1 @8)",
    b"FLW0": "BF (Atlus flow script, FLW0 @8)",
    b"SPR0": "SPR (Atlus sprite, SPR0 @8)",
    b"EPL0": "EPL (Atlus effect, EPL0 @8)",
    b"AMD\x00": "AMD (Atlus model data @8)",
}
# RenderWare binary-stream chunk ids seen at offset 0 (u32 LE type, u32 size, u32 libraryID).
RW_CHUNK_IDS = {
    0x00000016: "RenderWare TexDictionary stream (chunk 0x16)",
    0x0000001B: "RenderWare Animation stream (chunk 0x1B)",
    0xF0F000F0: "RenderWare stream, Atlus RMD scene chunk 0xF0F000F0",
}
EXT_HINT = {
    ".ADX": "ADX (CRI audio, by ext)",
    ".AHX": "AHX (CRI speech, by ext)",
    ".AFS": "AFS (CRI archive, by ext)",
    ".PAC": "PAC (Atlus container, by ext)",
    ".PAK": "PAK (Atlus container, by ext)",
    ".BIN": "BIN (container/blob, by ext)",
    ".CPK": "CPK (Atlus container, by ext; NOT CRI CPK here)",
    ".FPC": "FPC (Atlus container, by ext)",
    ".BF": "BF (Atlus flow script, by ext)",
    ".BMD": "BMD (Atlus message, by ext)",
    ".TMX": "TMX (Atlus texture, by ext)",
    ".PM1": "PM1 (Atlus model, by ext)",
    ".PM2": "PM2 (Atlus model, by ext)",
    ".PM3": "PM3 (Atlus model, by ext)",
    ".AMD": "AMD (Atlus model data, by ext)",
    ".SPD": "SPD (Atlus sprite, by ext)",
    ".SPR": "SPR (Atlus sprite, by ext)",
    ".TB": "TB (Atlus table, by ext)",
    ".TBL": "TBL (Atlus table, by ext)",
    ".EPL": "EPL (Atlus effect, by ext)",
    ".RMD": "RMD (RenderWare stream, by ext)",
    ".RWS": "RWS (RenderWare stream, by ext)",
    ".ANM": "ANM (animation, by ext)",
    ".BED": "BED (by ext)",
    ".CIN": "CIN (by ext)",
    ".SFD": "SFD (CRI Sofdec video, by ext)",
    ".PSS": "PSS (MPEG program stream, by ext)",
    ".ELF": "ELF (by ext)",
    ".IRX": "IRX (IOP module, by ext)",
    ".IMG": "IMG (IOP image, by ext)",
    ".HD": "Sony sound header (.HD, by ext)",
    ".BD": "Sony sound body / sample data (.BD, by ext)",
    ".SQ": "Sony sound sequence (.SQ, by ext)",
    ".SE": "SE (by ext)",
    ".SEQ": "SEQ (by ext)",
    ".MAP": "MAP (by ext)",
    ".FNT": "FNT font (by ext)",
    ".FLD": "FLD (by ext)",
    ".BVP": "BVP (by ext)",
    ".TXT": "text (by ext)",
    ".INI": "text (by ext)",
    ".BAT": "text batch file (by ext)",
    ".LST": "text list (by ext)",
    ".CSV": "CSV (by ext)",
    ".WAV": "WAV (by ext)",
    ".DAT": "DAT (by ext)",
}
_NAME_FIRST_EXTS = (".PAC", ".PAK", ".BIN", ".CPK", ".FPC", ".SE", "")


def _looks_like_name_first(magic16):
    """True when the first bytes look like an ASCII file name (Atlus PAK-style '252-byte name + u32 size' header)."""
    if len(magic16) < 8:
        return False
    head = magic16.split(b"\0", 1)[0]
    if len(head) < 3 or not all(0x20 <= c < 0x7F for c in head):
        return False
    return b"." in head or b"/" in head or b"\\" in head


def guess_format(magic16, ext):
    ext = ext.upper()
    for m, label in MAGIC_AT_0:
        if magic16.startswith(m):
            return label
    if len(magic16) >= 12:
        tag = magic16[8:12]
        if tag in MAGIC_AT_8:
            return MAGIC_AT_8[tag]
        rw_type = struct.unpack_from("<I", magic16, 0)[0]
        rw_lib = struct.unpack_from("<I", magic16, 8)[0]
        if rw_type in RW_CHUNK_IDS and (rw_lib >> 16) == 0x1C02:
            return RW_CHUNK_IDS[rw_type] + " (libraryID 0x%08X)" % rw_lib
    if magic16[:2] == b"\x80\x00" and ext in (".ADX", ".AHX", ""):
        # CRI ADX and AHX both start with 0x8000 (copyright-string offset follows)
        return EXT_HINT.get(ext, "ADX/AHX (CRI, 0x8000 header)")
    if ext in _NAME_FIRST_EXTS and _looks_like_name_first(magic16):
        return "PAK-style container (ASCII name-first header%s)" % (", ext " + ext if ext else "")
    if ext in EXT_HINT:
        return EXT_HINT[ext]
    return "unknown"


# ------------------------------------------------------------------------------------
# commands
# ------------------------------------------------------------------------------------


def cmd_probe(args):
    img = CvmImage(args.cvm)
    try:
        h = img.header
        print("file:              %s  (%d bytes)" % (img.path, img.file_size))
        print("header magic:      %r   tag@0x34: %r   builder: %r" % (h["magic"], h["tag_34"], h["builder_38"]))
        print("detected header:   0x%X bytes (PVD found at 0x%X)" % (img.header_size, img.header_size + 16 * SECTOR))
        print("hdr file_size@20:  0x%08X  (== file size: %s)" % (h["file_size_20"], h["file_size_20"] == img.file_size))
        print("hdr date@24:       %s" % h["date_24"])
        print("CVMH chunk size:   0x%X (0x800-0xC == %s)" % (h["cvmh_chunk_size_08"], h["cvmh_chunk_size_08"] == 0x800 - 0xC))
        print("ZONE chunk size:   0x%X (file-0x80C == %s)" % (h["zone_chunk_size_808"], h["zone_chunk_size_808"] == img.file_size - 0x80C))
        print("ZONE img size@834: 0x%X (file-0x1800 == %s)" % (h["zone_image_size_834"], h["zone_image_size_834"] == img.file_size - img.header_size))
        print("ZONE 80c/810/818/81c/820/828/82c: 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X" % (
            h["zone_80c"], h["zone_810"], h["zone_818"], h["zone_81c"], h["zone_820"], h["zone_828"], h["zone_82c"]))
        print("ZONE @0x1000 records: %s" % " ".join(h["zone_1000_records"]))
        p = img.pvd
        print("-- PVD --")
        for k in ("standard_id", "version", "system_id", "volume_id", "volume_space_size", "volume_set_size",
                  "volume_sequence_number", "logical_block_size", "path_table_size", "l_path_table_lba",
                  "opt_l_path_table_lba", "m_path_table_lba", "opt_m_path_table_lba", "root_dir_lba",
                  "root_dir_size", "volume_set_id", "publisher_id", "data_preparer_id", "application_id",
                  "creation_date", "modification_date", "file_structure_version"):
            print("  %-24s %r" % (k, p[k]))
        img_bytes = p["volume_space_size"] * p["logical_block_size"]
        print("  volume bytes             %d (== file - header: %s)" % (img_bytes, img_bytes == img.file_size - img.header_size))
        print("  other descriptors        %s" % p["other_descriptors"])
        if args.json:
            with open(args.json, "w") as fp:
                json.dump({"file": img.path, "file_size": img.file_size, "header_size": img.header_size,
                           "header": h, "pvd": p}, fp, indent=1)
    finally:
        img.close()


def cmd_list(args):
    img = CvmImage(args.cvm)
    try:
        nfiles = ndirs = total = 0
        for e in img.walk():
            if e.is_dir:
                ndirs += 1
                if args.tree:
                    print("%s/  <dir>  %d" % (e.path, e.lba))
                continue
            nfiles += 1
            total += e.size
            extra = ""
            if len(e.extents) > 1:
                extra = "  extents=%s" % e.extents
            print("%s  %d  %d%s" % (e.path, e.size, e.lba, extra))
        print("# %d files, %d dirs, %d bytes" % (nfiles, ndirs, total), file=sys.stderr)
    finally:
        img.close()


def _log(fp, msg):
    line = "%s %s" % (time.strftime("%H:%M:%S"), msg)
    if fp:
        fp.write(line + "\n")
        fp.flush()


def cmd_extract(args):
    img = CvmImage(args.cvm)
    container = args.container_name or os.path.basename(args.cvm)
    prefix = args.prefix if args.prefix is not None else os.path.splitext(os.path.basename(args.cvm))[0]
    outdir = os.path.abspath(args.outdir)
    os.makedirs(outdir, exist_ok=True)
    log = open(args.log, "a") if args.log else None
    _log(log, "extract %s -> %s (header 0x%X)" % (args.cvm, outdir, img.header_size))

    # load existing manifest (merge semantics: entries for this container are replaced)
    manifest = {"entries": []}
    if args.manifest and os.path.exists(args.manifest):
        with open(args.manifest, "r") as fp:
            manifest = json.load(fp)
        manifest["entries"] = [m for m in manifest.get("entries", []) if m.get("container") != container]
    manifest.setdefault("schema", "p3fes-port/extracted/manifest v1")
    manifest.setdefault("containers", {})

    entries = []
    files = []
    nfiles = ndirs = total = 0
    t0 = time.time()
    try:
        for e in img.walk():
            dest = os.path.join(outdir, *e.path.split("/"))
            if e.is_dir:
                os.makedirs(dest, exist_ok=True)
                ndirs += 1
                continue
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            magic = b""
            written = 0
            with open(dest, "wb") as out:
                for buf in img.iter_file_chunks(e):
                    if not magic:
                        magic = buf[:16]
                    out.write(buf)
                    written += len(buf)
            if written != e.size:
                raise IOError("size mismatch writing %s: %d != %d" % (e.path, written, e.size))
            if e.date and not args.no_timestamps:
                try:
                    ts = datetime.datetime.fromisoformat(e.date).timestamp()
                    os.utime(dest, (ts, ts))
                except (ValueError, OSError, OverflowError):
                    pass
            ext = os.path.splitext(e.name)[1]
            rec = {
                "path": (prefix + "/" if prefix else "") + e.path,
                "container": container,
                "size": e.size,
                "lba": e.lba,
                "magic16": magic.hex(),
                "ext": ext,
                "format_guess": guess_format(magic, ext),
                "parser_status": "unknown",
            }
            if len(e.extents) > 1:
                rec["extents"] = [list(x) for x in e.extents]
            if e.date:
                rec["iso_date"] = e.date
            rec["dir_record_offset"] = e.record_offsets[0]
            entries.append(rec)
            files.append(e)
            nfiles += 1
            total += e.size
            if nfiles % 500 == 0:
                _log(log, "  %d files, %d bytes" % (nfiles, total))
        _log(log, "wrote %d files, %d dirs, %d bytes in %.1fs" % (nfiles, ndirs, total, time.time() - t0))

        verify_fail = 0
        if args.verify:
            t1 = time.time()
            for rec, e in zip(entries, files):
                dest = os.path.join(outdir, *e.path.split("/"))
                st = os.stat(dest)
                with open(dest, "rb") as fp:
                    head = fp.read(16)
                src_head = img.read_sectors(e.lba, min(16, e.size)) if e.size else b""
                ok = st.st_size == e.size and head == src_head and head.hex() == rec["magic16"]
                rec["verified"] = ok
                if not ok:
                    verify_fail += 1
                    _log(log, "VERIFY FAIL %s size %d/%d head %s/%s" % (e.path, st.st_size, e.size, head.hex(), src_head.hex()))
            _log(log, "verify: %d files, %d failures, %.1fs" % (len(entries), verify_fail, time.time() - t1))

        manifest["entries"].extend(entries)
        manifest["containers"][container] = {
            "source": os.path.abspath(args.cvm), "source_size": img.file_size,
            "header_size": img.header_size, "pvd_volume_id": img.pvd["volume_id"],
            "volume_space_size": img.pvd["volume_space_size"], "files": nfiles, "dirs": ndirs,
            "bytes": total, "outdir": outdir, "prefix": prefix,
            "extracted_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
            "verified": (verify_fail == 0) if args.verify else None,
        }
        if args.manifest:
            tmp = args.manifest + ".tmp"
            with open(tmp, "w") as fp:
                json.dump(manifest, fp, indent=0, sort_keys=False)
            os.replace(tmp, args.manifest)
        print("%s: %d files, %d dirs, %d bytes -> %s%s" % (
            container, nfiles, ndirs, total, outdir,
            ("; verify failures: %d" % verify_fail) if args.verify else ""))
        return 1 if verify_fail else 0
    finally:
        img.close()
        if log:
            log.close()


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n", 1)[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("probe", help="print CVM header and ISO9660 PVD fields")
    p.add_argument("cvm")
    p.add_argument("--json", help="also write the parsed header/PVD as JSON")
    p.set_defaults(fn=cmd_probe)
    p = sub.add_parser("list", help="list files: path size lba")
    p.add_argument("cvm")
    p.add_argument("--tree", action="store_true", help="also print directories")
    p.set_defaults(fn=cmd_list)
    p = sub.add_parser("extract", help="extract every file")
    p.add_argument("cvm")
    p.add_argument("outdir")
    p.add_argument("--manifest", help="JSON manifest to write/merge")
    p.add_argument("--container-name", help="container label in the manifest (default: basename)")
    p.add_argument("--prefix", help="manifest path prefix (default: cvm basename without extension)")
    p.add_argument("--verify", action="store_true", help="re-read size + first 16 bytes of each written file")
    p.add_argument("--no-timestamps", action="store_true")
    p.add_argument("--log", help="append progress log here")
    p.set_defaults(fn=cmd_extract)
    args = ap.parse_args(argv)
    return args.fn(args) or 0


if __name__ == "__main__":
    sys.exit(main())
