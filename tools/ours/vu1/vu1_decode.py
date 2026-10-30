#!/usr/bin/env python3
"""VU1 micro-instruction decoder (stdlib only).

Decodes the 64-bit VU instruction pairs of the PS2 Vector Unit micro mode:
upper word (bits 63..32, FMAC/vector ops + the I/E/M/D/T flags) and lower
word (bits 31..0, load/store, integer, EFU, branch, flag-register ops; or a
32-bit float immediate when the I flag is set).

Encoding source: the VU User's Manual field layout as we know it, cross-checked
opcode by opcode against the MIT-licensed interpreter in
`tools/third_party/_community-eval/ps2-web-recomp/runtime/src/vu_micro.cpp`
(`decode_upper`, `lower`, `scan_flags`).  No text was copied from it.

Memory layout of a dump: each instruction is 8 bytes, little-endian 64-bit
value, i.e. bytes 0..3 = lower word, bytes 4..7 = upper word.

Unknown encodings decode to mnemonic ``UNKNOWN`` carrying the raw word; the
decoder never raises on input bytes.

Usage:
    python vu1_decode.py --selftest
    python vu1_decode.py <dump.bin>        # disassembly listing
"""
from __future__ import annotations

import struct
import sys
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Tuple

# ---------------------------------------------------------------------------
# field helpers
# ---------------------------------------------------------------------------

DEST_CHARS = "xyzw"
BC_CHARS = "xyzw"

# VU1 micro memory is 16 KiB (2048 instructions); the PC wraps inside it, so a
# branch whose raw target lies outside 0..0x3FFF lands at target & 0x3FFF.
# (VU0 has 4 KiB; pass micro_bytes=0x1000 for VU0 code.)
VU1_MICRO_BYTES = 0x4000


def dest_str(dest: int) -> str:
    return "".join(DEST_CHARS[i] for i in range(4) if dest & (8 >> i))


def sext(value: int, bits: int) -> int:
    value &= (1 << bits) - 1
    if value & (1 << (bits - 1)):
        value -= 1 << bits
    return value


@dataclass
class Op:
    """One decoded half-instruction."""

    mnemonic: str          # e.g. ADDbc, MULq, LQI, IBNE, LOI, NOP, UNKNOWN
    base: str              # e.g. ADD, MUL, LQI, IBNE
    cls: str               # upper: fmac, fmac_acc, conv, abs, clip, opm, nop, unknown
                           # lower: ldst, int, move, efu_q, efu_p, branch, flag, xg, rand, loi, nop, unknown
    text: str              # assembly-style rendering
    raw: int
    fields: Dict[str, int] = field(default_factory=dict)
    # branch info (lower only): byte target inside micro memory (wrapped), or None
    branch_target: Optional[int] = None
    branch_target_raw: Optional[int] = None   # pc + 8 + imm11*8 before wrapping
    branch_wraps: bool = False                # raw target was outside micro memory
    branch_indirect: bool = False
    branch_conditional: bool = False
    vi_read: Tuple[int, ...] = ()
    vi_write: Tuple[int, ...] = ()


@dataclass
class Insn:
    pc: int                # byte offset inside the program
    hi: int
    lo: int
    upper: Op
    lower: Op
    I: bool
    E: bool
    M: bool
    D: bool
    T: bool

    @property
    def flags(self) -> str:
        return "".join(ch for ch, on in zip("IEMDT", (self.I, self.E, self.M, self.D, self.T)) if on)


# ---------------------------------------------------------------------------
# upper word
# ---------------------------------------------------------------------------

# funct (bits 5..0) < 0x3C: (base, form)
_UPPER_FUNCT: Dict[int, Tuple[str, str]] = {}
for _f in range(0x00, 0x04):
    _UPPER_FUNCT[_f] = ("ADD", "bc")
for _f in range(0x04, 0x08):
    _UPPER_FUNCT[_f] = ("SUB", "bc")
for _f in range(0x08, 0x0C):
    _UPPER_FUNCT[_f] = ("MADD", "bc")
for _f in range(0x0C, 0x10):
    _UPPER_FUNCT[_f] = ("MSUB", "bc")
for _f in range(0x10, 0x14):
    _UPPER_FUNCT[_f] = ("MAX", "bc")
for _f in range(0x14, 0x18):
    _UPPER_FUNCT[_f] = ("MINI", "bc")
for _f in range(0x18, 0x1C):
    _UPPER_FUNCT[_f] = ("MUL", "bc")
_UPPER_FUNCT.update({
    0x1C: ("MUL", "q"), 0x1D: ("MAX", "i"), 0x1E: ("MUL", "i"), 0x1F: ("MINI", "i"),
    0x20: ("ADD", "q"), 0x21: ("MADD", "q"), 0x22: ("ADD", "i"), 0x23: ("MADD", "i"),
    0x24: ("SUB", "q"), 0x25: ("MSUB", "q"), 0x26: ("SUB", "i"), 0x27: ("MSUB", "i"),
    0x28: ("ADD", ""), 0x29: ("MADD", ""), 0x2A: ("MUL", ""), 0x2B: ("MAX", ""),
    0x2C: ("SUB", ""), 0x2D: ("MSUB", ""), 0x2E: ("OPMSUB", ""), 0x2F: ("MINI", ""),
})

# funct >= 0x3C: index = fd*4 + (funct & 3)
_UPPER_SPECIAL: Dict[int, Tuple[str, str]] = {}
for _f in range(0x00, 0x04):
    _UPPER_SPECIAL[_f] = ("ADDA", "bc")
for _f in range(0x04, 0x08):
    _UPPER_SPECIAL[_f] = ("SUBA", "bc")
for _f in range(0x08, 0x0C):
    _UPPER_SPECIAL[_f] = ("MADDA", "bc")
for _f in range(0x0C, 0x10):
    _UPPER_SPECIAL[_f] = ("MSUBA", "bc")
_UPPER_SPECIAL.update({
    0x10: ("ITOF0", ""), 0x11: ("ITOF4", ""), 0x12: ("ITOF12", ""), 0x13: ("ITOF15", ""),
    0x14: ("FTOI0", ""), 0x15: ("FTOI4", ""), 0x16: ("FTOI12", ""), 0x17: ("FTOI15", ""),
})
for _f in range(0x18, 0x1C):
    _UPPER_SPECIAL[_f] = ("MULA", "bc")
_UPPER_SPECIAL.update({
    0x1C: ("MULA", "q"), 0x1D: ("ABS", ""), 0x1E: ("MULA", "i"), 0x1F: ("CLIP", ""),
    0x20: ("ADDA", "q"), 0x21: ("MADDA", "q"), 0x22: ("ADDA", "i"), 0x23: ("MADDA", "i"),
    0x24: ("SUBA", "q"), 0x25: ("MSUBA", "q"), 0x26: ("SUBA", "i"), 0x27: ("MSUBA", "i"),
    0x28: ("ADDA", ""), 0x29: ("MADDA", ""), 0x2A: ("MULA", ""),
    0x2C: ("SUBA", ""), 0x2D: ("MSUBA", ""), 0x2E: ("OPMULA", ""), 0x2F: ("NOP", ""),
})

_CONV_BASES = {"ITOF0", "ITOF4", "ITOF12", "ITOF15", "FTOI0", "FTOI4", "FTOI12", "FTOI15"}


def decode_upper(hi: int) -> Op:
    hi &= 0xFFFFFFFF
    dest = (hi >> 21) & 0xF
    ft = (hi >> 16) & 0x1F
    fs = (hi >> 11) & 0x1F
    fd = (hi >> 6) & 0x1F
    funct = hi & 0x3F
    bc = hi & 3
    fields = {"dest": dest, "ft": ft, "fs": fs, "fd": fd, "funct": funct, "bc": bc}
    d = "." + dest_str(dest) if dest else ""

    if funct < 0x3C:
        entry = _UPPER_FUNCT.get(funct)
        if entry is None:  # 0x30..0x3B are not assigned
            return Op("UNKNOWN", "UNKNOWN", "unknown",
                      f"UNKNOWN_UPPER 0x{hi:08x} (funct 0x{funct:02x})", hi, fields)
        base, form = entry
        mnem = base + form
        fields["form"] = form
        if base == "OPMSUB":
            text = f"opmsub.xyz vf{fd:02d}, vf{fs:02d}, vf{ft:02d}"
            return Op(mnem, base, "opm", text, hi, fields)
        if form == "bc":
            text = f"{base.lower()}{BC_CHARS[bc]}{d} vf{fd:02d}, vf{fs:02d}, vf{ft:02d}{BC_CHARS[bc]}"
        elif form == "q":
            text = f"{base.lower()}q{d} vf{fd:02d}, vf{fs:02d}, Q"
        elif form == "i":
            text = f"{base.lower()}i{d} vf{fd:02d}, vf{fs:02d}, I"
        else:
            text = f"{base.lower()}{d} vf{fd:02d}, vf{fs:02d}, vf{ft:02d}"
        return Op(mnem, base, "fmac", text, hi, fields)

    index = fd * 4 + (funct & 3)
    fields["index"] = index
    entry = _UPPER_SPECIAL.get(index)
    if entry is None:
        return Op("UNKNOWN", "UNKNOWN", "unknown",
                  f"UNKNOWN_UPPER 0x{hi:08x} (special index 0x{index:02x})", hi, fields)
    base, form = entry
    mnem = base + form
    fields["form"] = form
    if base == "NOP":
        return Op("NOP", "NOP", "nop", "nop", hi, fields)
    if base == "CLIP":
        return Op("CLIP", "CLIP", "clip", f"clipw.xyz vf{fs:02d}, vf{ft:02d}w", hi, fields)
    if base == "ABS":
        return Op("ABS", "ABS", "abs", f"abs{d} vf{ft:02d}, vf{fs:02d}", hi, fields)
    if base in _CONV_BASES:
        return Op(mnem, base, "conv", f"{base.lower()}{d} vf{ft:02d}, vf{fs:02d}", hi, fields)
    if base == "OPMULA":
        return Op(mnem, base, "opm", f"opmula.xyz ACC, vf{fs:02d}, vf{ft:02d}", hi, fields)
    # accumulator forms
    if form == "bc":
        text = f"{base.lower()}{BC_CHARS[bc]}{d} ACC, vf{fs:02d}, vf{ft:02d}{BC_CHARS[bc]}"
    elif form == "q":
        text = f"{base.lower()}q{d} ACC, vf{fs:02d}, Q"
    elif form == "i":
        text = f"{base.lower()}i{d} ACC, vf{fs:02d}, I"
    else:
        text = f"{base.lower()}{d} ACC, vf{fs:02d}, vf{ft:02d}"
    return Op(mnem, base, "fmac_acc", text, hi, fields)


# ---------------------------------------------------------------------------
# lower word
# ---------------------------------------------------------------------------

# opcode (bits 31..25) != 0x40
_LOWER_OPCODE: Dict[int, Tuple[str, str]] = {
    0x00: ("LQ", "ldst"), 0x01: ("SQ", "ldst"), 0x04: ("ILW", "ldst"), 0x05: ("ISW", "ldst"),
    0x08: ("IADDIU", "int"), 0x09: ("ISUBIU", "int"),
    0x10: ("FCEQ", "flag"), 0x11: ("FCSET", "flag"), 0x12: ("FCAND", "flag"), 0x13: ("FCOR", "flag"),
    0x14: ("FSEQ", "flag"), 0x15: ("FSSET", "flag"), 0x16: ("FSAND", "flag"), 0x17: ("FSOR", "flag"),
    0x18: ("FMEQ", "flag"), 0x1A: ("FMAND", "flag"), 0x1B: ("FMOR", "flag"), 0x1C: ("FCGET", "flag"),
    0x20: ("B", "branch"), 0x21: ("BAL", "branch"), 0x24: ("JR", "branch"), 0x25: ("JALR", "branch"),
    0x28: ("IBEQ", "branch"), 0x29: ("IBNE", "branch"),
    0x2C: ("IBLTZ", "branch"), 0x2D: ("IBGTZ", "branch"), 0x2E: ("IBLEZ", "branch"), 0x2F: ("IBGEZ", "branch"),
}

# opcode 0x40, funct < 0x3C
_LOWER_INT: Dict[int, str] = {0x30: "IADD", 0x31: "ISUB", 0x32: "IADDI", 0x34: "IAND", 0x35: "IOR"}

# opcode 0x40, funct >= 0x3C: index = fd*4 + (funct & 3)
_LOWER_SPECIAL: Dict[int, Tuple[str, str]] = {
    0x30: ("MOVE", "move"), 0x31: ("MR32", "move"),
    0x34: ("LQI", "ldst"), 0x35: ("SQI", "ldst"), 0x36: ("LQD", "ldst"), 0x37: ("SQD", "ldst"),
    0x38: ("DIV", "efu_q"), 0x39: ("SQRT", "efu_q"), 0x3A: ("RSQRT", "efu_q"), 0x3B: ("WAITQ", "efu_q"),
    0x3C: ("MTIR", "move"), 0x3D: ("MFIR", "move"), 0x3E: ("ILWR", "ldst"), 0x3F: ("ISWR", "ldst"),
    0x40: ("RNEXT", "rand"), 0x41: ("RGET", "rand"), 0x42: ("RINIT", "rand"), 0x43: ("RXOR", "rand"),
    0x64: ("MFP", "efu_p"),
    0x68: ("XTOP", "xg"), 0x69: ("XITOP", "xg"), 0x6C: ("XGKICK", "xg"),
    0x70: ("ESADD", "efu_p"), 0x71: ("ERSADD", "efu_p"), 0x72: ("ELENG", "efu_p"), 0x73: ("ERLENG", "efu_p"),
    0x74: ("EATANxy", "efu_p"), 0x75: ("EATANxz", "efu_p"), 0x76: ("ESUM", "efu_p"),
    0x78: ("ESQRT", "efu_p"), 0x79: ("ERSQRT", "efu_p"), 0x7A: ("ERCPR", "efu_p"), 0x7B: ("WAITP", "efu_p"),
    0x7C: ("ESIN", "efu_p"), 0x7D: ("EATAN", "efu_p"), 0x7E: ("EEXP", "efu_p"),
}

LOWER_NOP = 0x8000033C  # move vf00, vf00 with dest 0: the conventional lower nop


def _f(v: int) -> str:
    return repr(struct.unpack("<f", struct.pack("<I", v & 0xFFFFFFFF))[0])


def decode_lower(lo: int, i_flag: bool, pc: int = 0, micro_bytes: int = VU1_MICRO_BYTES) -> Op:
    lo &= 0xFFFFFFFF
    if i_flag:
        return Op("LOI", "LOI", "loi", f"loi {_f(lo)}", lo, {"imm32": lo})
    if lo == LOWER_NOP:
        return Op("NOP", "NOP", "nop", "nop", lo, {})

    opcode = lo >> 25
    dest = (lo >> 21) & 0xF
    it = (lo >> 16) & 0x1F
    is_ = (lo >> 11) & 0x1F
    id_ = (lo >> 6) & 0x1F
    imm11 = sext(lo & 0x7FF, 11)
    imm15 = ((lo >> 10) & 0x7800) | (lo & 0x7FF)
    fsf = (lo >> 21) & 3
    ftf = (lo >> 23) & 3
    d = "." + dest_str(dest) if dest else ""
    fields = {"opcode": opcode, "dest": dest, "it": it, "is": is_, "id": id_}
    fsf_c = DEST_CHARS[fsf]
    ftf_c = DEST_CHARS[ftf]

    if opcode == 0x40:
        funct = lo & 0x3F
        fields["funct"] = funct
        if funct < 0x3C:
            base = _LOWER_INT.get(funct)
            if base is None:
                return Op("UNKNOWN", "UNKNOWN", "unknown",
                          f"UNKNOWN_LOWER 0x{lo:08x} (int funct 0x{funct:02x})", lo, fields)
            if base == "IADDI":
                imm5 = sext(id_, 5)
                fields["imm5"] = imm5
                return Op(base, base, "int", f"iaddi vi{it:02d}, vi{is_:02d}, {imm5}", lo, fields,
                          vi_read=(is_,), vi_write=(it,))
            return Op(base, base, "int", f"{base.lower()} vi{id_:02d}, vi{is_:02d}, vi{it:02d}", lo, fields,
                      vi_read=(is_, it), vi_write=(id_,))
        index = id_ * 4 + (funct & 3)
        fields["index"] = index
        entry = _LOWER_SPECIAL.get(index)
        if entry is None:
            return Op("UNKNOWN", "UNKNOWN", "unknown",
                      f"UNKNOWN_LOWER 0x{lo:08x} (special index 0x{index:02x})", lo, fields)
        base, cls = entry
        vi_r: Tuple[int, ...] = ()
        vi_w: Tuple[int, ...] = ()
        if base == "MOVE":
            text = f"move{d} vf{it:02d}, vf{is_:02d}"
        elif base == "MR32":
            text = f"mr32{d} vf{it:02d}, vf{is_:02d}"
        elif base == "LQI":
            text = f"lqi{d} vf{it:02d}, (vi{is_:02d}++)"; vi_r = (is_,); vi_w = (is_,)
        elif base == "SQI":
            text = f"sqi{d} vf{is_:02d}, (vi{it:02d}++)"; vi_r = (it,); vi_w = (it,)
        elif base == "LQD":
            text = f"lqd{d} vf{it:02d}, (--vi{is_:02d})"; vi_r = (is_,); vi_w = (is_,)
        elif base == "SQD":
            text = f"sqd{d} vf{is_:02d}, (--vi{it:02d})"; vi_r = (it,); vi_w = (it,)
        elif base == "DIV":
            text = f"div Q, vf{is_:02d}{fsf_c}, vf{it:02d}{ftf_c}"
        elif base == "SQRT":
            text = f"sqrt Q, vf{it:02d}{ftf_c}"
        elif base == "RSQRT":
            text = f"rsqrt Q, vf{is_:02d}{fsf_c}, vf{it:02d}{ftf_c}"
        elif base == "WAITQ":
            text = "waitq"
        elif base == "MTIR":
            text = f"mtir vi{it:02d}, vf{is_:02d}{fsf_c}"; vi_w = (it,)
        elif base == "MFIR":
            text = f"mfir{d} vf{it:02d}, vi{is_:02d}"; vi_r = (is_,)
        elif base == "ILWR":
            text = f"ilwr{d} vi{it:02d}, (vi{is_:02d})"; vi_r = (is_,); vi_w = (it,)
        elif base == "ISWR":
            text = f"iswr{d} vi{it:02d}, (vi{is_:02d})"; vi_r = (is_, it)
        elif base in ("RNEXT", "RGET"):
            text = f"{base.lower()}{d} vf{it:02d}, R"
        elif base in ("RINIT", "RXOR"):
            text = f"{base.lower()} R, vf{is_:02d}{fsf_c}"
        elif base == "MFP":
            text = f"mfp{d} vf{it:02d}, P"
        elif base in ("XTOP", "XITOP"):
            text = f"{base.lower()} vi{it:02d}"; vi_w = (it,)
        elif base == "XGKICK":
            text = f"xgkick vi{is_:02d}"; vi_r = (is_,)
        elif base in ("ESADD", "ERSADD", "ELENG", "ERLENG", "EATANxy", "EATANxz", "ESUM"):
            text = f"{base.lower()} P, vf{is_:02d}"
        elif base == "WAITP":
            text = "waitp"
        else:  # ESQRT ERSQRT ERCPR ESIN EATAN EEXP
            text = f"{base.lower()} P, vf{is_:02d}{fsf_c}"
        return Op(base, base, cls, text, lo, fields, vi_read=vi_r, vi_write=vi_w)

    entry = _LOWER_OPCODE.get(opcode)
    if entry is None:
        return Op("UNKNOWN", "UNKNOWN", "unknown",
                  f"UNKNOWN_LOWER 0x{lo:08x} (opcode 0x{opcode:02x})", lo, fields)
    base, cls = entry
    fields["imm11"] = imm11
    vi_r = ()
    vi_w = ()
    target: Optional[int] = None
    raw_target: Optional[int] = None
    wraps = False
    indirect = False
    conditional = False
    if cls == "branch" and base not in ("JR", "JALR"):
        raw_target = pc + 8 + imm11 * 8
        target = raw_target % micro_bytes
        wraps = target != raw_target
    if base == "LQ":
        text = f"lq{d} vf{it:02d}, {imm11}(vi{is_:02d})"; vi_r = (is_,)
    elif base == "SQ":
        text = f"sq{d} vf{is_:02d}, {imm11}(vi{it:02d})"; vi_r = (it,)
    elif base == "ILW":
        text = f"ilw{d} vi{it:02d}, {imm11}(vi{is_:02d})"; vi_r = (is_,); vi_w = (it,)
    elif base == "ISW":
        text = f"isw{d} vi{it:02d}, {imm11}(vi{is_:02d})"; vi_r = (is_, it)
    elif base in ("IADDIU", "ISUBIU"):
        fields["imm15"] = imm15
        text = f"{base.lower()} vi{it:02d}, vi{is_:02d}, 0x{imm15:x}"; vi_r = (is_,); vi_w = (it,)
    elif base in ("FCEQ", "FCSET", "FCAND", "FCOR"):
        imm24 = lo & 0xFFFFFF
        fields["imm24"] = imm24
        text = f"{base.lower()} {'' if base == 'FCSET' else 'vi01, '}0x{imm24:06x}"
        if base != "FCSET":
            vi_w = (1,)
    elif base in ("FSEQ", "FSSET", "FSAND", "FSOR"):
        imm12 = ((lo >> 10) & 0x800) | (lo & 0x7FF)
        fields["imm12"] = imm12
        text = f"{base.lower()} {'' if base == 'FSSET' else f'vi{it:02d}, '}0x{imm12:03x}"
        if base != "FSSET":
            vi_w = (it,)
    elif base in ("FMEQ", "FMAND", "FMOR"):
        text = f"{base.lower()} vi{it:02d}, vi{is_:02d}"; vi_r = (is_,); vi_w = (it,)
    elif base == "FCGET":
        text = f"fcget vi{it:02d}"; vi_w = (it,)
    elif base in ("B", "BAL"):
        text = f"b {target // 8:#x}" if base == "B" else f"bal vi{it:02d}, {target // 8:#x}"
        if base == "BAL":
            vi_w = (it,)
    elif base in ("JR", "JALR"):
        indirect = True
        text = f"jr vi{is_:02d}" if base == "JR" else f"jalr vi{it:02d}, vi{is_:02d}"
        vi_r = (is_,)
        if base == "JALR":
            vi_w = (it,)
    else:  # IBEQ IBNE IBLTZ IBGTZ IBLEZ IBGEZ
        conditional = True
        if base in ("IBEQ", "IBNE"):
            text = f"{base.lower()} vi{it:02d}, vi{is_:02d}, {target // 8:#x}"; vi_r = (is_, it)
        else:
            text = f"{base.lower()} vi{is_:02d}, {target // 8:#x}"; vi_r = (is_,)
    if wraps:
        text += f"  ; wraps from {raw_target // 8:#x}"
    return Op(base, base, cls, text, lo, fields, branch_target=target, branch_target_raw=raw_target,
              branch_wraps=wraps, branch_indirect=indirect, branch_conditional=conditional,
              vi_read=vi_r, vi_write=vi_w)


# ---------------------------------------------------------------------------
# whole instructions / programs
# ---------------------------------------------------------------------------

def decode_pair(hi: int, lo: int, pc: int = 0) -> Insn:
    hi &= 0xFFFFFFFF
    lo &= 0xFFFFFFFF
    I = bool(hi & 0x80000000)
    E = bool(hi & 0x40000000)
    M = bool(hi & 0x20000000)
    D = bool(hi & 0x10000000)
    T = bool(hi & 0x08000000)
    return Insn(pc, hi, lo, decode_upper(hi), decode_lower(lo, I, pc), I, E, M, D, T)


def decode_program(data: bytes) -> List[Insn]:
    """Decode a raw microcode image (little-endian 64-bit words). A trailing
    partial word is ignored (callers can report len(data) % 8)."""
    out: List[Insn] = []
    n = len(data) // 8
    for k in range(n):
        lo, hi = struct.unpack_from("<II", data, k * 8)
        out.append(decode_pair(hi, lo, k * 8))
    return out


def format_insn(insn: Insn) -> str:
    fl = insn.flags or "-"
    return f"{insn.pc // 8:04x}  {insn.hi:08x} {insn.lo:08x}  [{fl:5}] {insn.upper.text:<40} | {insn.lower.text}"


# ---------------------------------------------------------------------------
# self test
# ---------------------------------------------------------------------------

def _mk_upper(funct: int, fd: int = 0, fs: int = 0, ft: int = 0, dest: int = 0xF, flags: int = 0) -> int:
    return (flags << 27) | (dest << 21) | (ft << 16) | (fs << 11) | (fd << 6) | funct


def _mk_upper_special(index: int, fs: int = 0, ft: int = 0, dest: int = 0xF, flags: int = 0) -> int:
    return _mk_upper(0x3C | (index & 3), index >> 2, fs, ft, dest, flags)


def _mk_lower_special(index: int, it: int = 0, is_: int = 0, dest: int = 0xF, fsf: int = 0, ftf: int = 0) -> int:
    hi_bits = (ftf << 23) | (fsf << 21) if (fsf or ftf) else (dest << 21)
    return (0x40 << 25) | hi_bits | (it << 16) | (is_ << 11) | ((index >> 2) << 6) | (0x3C | (index & 3))


def _mk_lower(opcode: int, it: int = 0, is_: int = 0, dest: int = 0, imm11: int = 0) -> int:
    return (opcode << 25) | (dest << 21) | (it << 16) | (is_ << 11) | (imm11 & 0x7FF)


def selftest() -> None:
    checks = 0

    def eq(a, b, what):
        nonlocal checks
        checks += 1
        assert a == b, f"{what}: got {a!r}, expected {b!r}"

    # --- upper, funct table ---
    eq(decode_upper(_mk_upper(0x00, 1, 2, 3)).mnemonic, "ADDbc", "ADDx")
    eq(decode_upper(_mk_upper(0x03, 1, 2, 3)).text, "addw.xyzw vf01, vf02, vf03w", "ADDw text")
    eq(decode_upper(_mk_upper(0x05, 1, 2, 3)).mnemonic, "SUBbc", "SUBy")
    eq(decode_upper(_mk_upper(0x0A, 1, 2, 3)).mnemonic, "MADDbc", "MADDz")
    eq(decode_upper(_mk_upper(0x0F, 1, 2, 3)).mnemonic, "MSUBbc", "MSUBw")
    eq(decode_upper(_mk_upper(0x10, 1, 2, 3)).mnemonic, "MAXbc", "MAXx")
    eq(decode_upper(_mk_upper(0x15, 1, 2, 3)).mnemonic, "MINIbc", "MINIy")
    eq(decode_upper(_mk_upper(0x18, 1, 2, 3)).mnemonic, "MULbc", "MULx")
    eq(decode_upper(_mk_upper(0x1C, 1, 2)).mnemonic, "MULq", "MULq")
    eq(decode_upper(_mk_upper(0x1D, 1, 2)).mnemonic, "MAXi", "MAXi")
    eq(decode_upper(_mk_upper(0x1E, 1, 2)).mnemonic, "MULi", "MULi")
    eq(decode_upper(_mk_upper(0x1F, 1, 2)).mnemonic, "MINIi", "MINIi")
    eq(decode_upper(_mk_upper(0x20, 1, 2)).mnemonic, "ADDq", "ADDq")
    eq(decode_upper(_mk_upper(0x21, 1, 2)).mnemonic, "MADDq", "MADDq")
    eq(decode_upper(_mk_upper(0x22, 1, 2)).mnemonic, "ADDi", "ADDi")
    eq(decode_upper(_mk_upper(0x23, 1, 2)).mnemonic, "MADDi", "MADDi")
    eq(decode_upper(_mk_upper(0x24, 1, 2)).mnemonic, "SUBq", "SUBq")
    eq(decode_upper(_mk_upper(0x25, 1, 2)).mnemonic, "MSUBq", "MSUBq")
    eq(decode_upper(_mk_upper(0x26, 1, 2)).mnemonic, "SUBi", "SUBi")
    eq(decode_upper(_mk_upper(0x27, 1, 2)).mnemonic, "MSUBi", "MSUBi")
    eq(decode_upper(_mk_upper(0x28, 1, 2, 3)).text, "add.xyzw vf01, vf02, vf03", "ADD")
    eq(decode_upper(_mk_upper(0x29, 1, 2, 3)).mnemonic, "MADD", "MADD")
    eq(decode_upper(_mk_upper(0x2A, 1, 2, 3, dest=0x8)).text, "mul.x vf01, vf02, vf03", "MUL dest x")
    eq(decode_upper(_mk_upper(0x2B, 1, 2, 3)).mnemonic, "MAX", "MAX")
    eq(decode_upper(_mk_upper(0x2C, 1, 2, 3)).mnemonic, "SUB", "SUB")
    eq(decode_upper(_mk_upper(0x2D, 1, 2, 3)).mnemonic, "MSUB", "MSUB")
    eq(decode_upper(_mk_upper(0x2E, 1, 2, 3)).mnemonic, "OPMSUB", "OPMSUB")
    eq(decode_upper(_mk_upper(0x2F, 1, 2, 3)).mnemonic, "MINI", "MINI")
    # --- upper, special table ---
    eq(decode_upper(_mk_upper_special(0x00, 2, 3)).mnemonic, "ADDAbc", "ADDAx")
    eq(decode_upper(_mk_upper_special(0x06, 2, 3)).mnemonic, "SUBAbc", "SUBAz")
    eq(decode_upper(_mk_upper_special(0x09, 2, 3)).mnemonic, "MADDAbc", "MADDAy")
    eq(decode_upper(_mk_upper_special(0x0C, 2, 3)).mnemonic, "MSUBAbc", "MSUBAx")
    eq(decode_upper(_mk_upper_special(0x10, 2, 3)).mnemonic, "ITOF0", "ITOF0")
    eq(decode_upper(_mk_upper_special(0x11, 2, 3)).mnemonic, "ITOF4", "ITOF4")
    eq(decode_upper(_mk_upper_special(0x12, 2, 3)).mnemonic, "ITOF12", "ITOF12")
    eq(decode_upper(_mk_upper_special(0x13, 2, 3)).mnemonic, "ITOF15", "ITOF15")
    eq(decode_upper(_mk_upper_special(0x14, 2, 3)).mnemonic, "FTOI0", "FTOI0")
    eq(decode_upper(_mk_upper_special(0x15, 2, 3)).mnemonic, "FTOI4", "FTOI4")
    eq(decode_upper(_mk_upper_special(0x16, 2, 3)).mnemonic, "FTOI12", "FTOI12")
    eq(decode_upper(_mk_upper_special(0x17, 2, 3)).mnemonic, "FTOI15", "FTOI15")
    eq(decode_upper(_mk_upper_special(0x1B, 2, 3)).mnemonic, "MULAbc", "MULAw")
    eq(decode_upper(_mk_upper_special(0x1C, 2)).mnemonic, "MULAq", "MULAq")
    eq(decode_upper(_mk_upper_special(0x1D, 2, 3)).mnemonic, "ABS", "ABS")
    eq(decode_upper(_mk_upper_special(0x1E, 2)).mnemonic, "MULAi", "MULAi")
    eq(decode_upper(_mk_upper_special(0x1F, 2, 3)).mnemonic, "CLIP", "CLIP")
    eq(decode_upper(_mk_upper_special(0x1F, 2, 3)).text, "clipw.xyz vf02, vf03w", "CLIP text")
    eq(decode_upper(_mk_upper_special(0x20, 2)).mnemonic, "ADDAq", "ADDAq")
    eq(decode_upper(_mk_upper_special(0x23, 2)).mnemonic, "MADDAi", "MADDAi")
    eq(decode_upper(_mk_upper_special(0x25, 2)).mnemonic, "MSUBAq", "MSUBAq")
    eq(decode_upper(_mk_upper_special(0x26, 2)).mnemonic, "SUBAi", "SUBAi")
    eq(decode_upper(_mk_upper_special(0x28, 2, 3)).mnemonic, "ADDA", "ADDA")
    eq(decode_upper(_mk_upper_special(0x29, 2, 3)).mnemonic, "MADDA", "MADDA")
    eq(decode_upper(_mk_upper_special(0x2A, 2, 3)).mnemonic, "MULA", "MULA")
    eq(decode_upper(_mk_upper_special(0x2C, 2, 3)).mnemonic, "SUBA", "SUBA")
    eq(decode_upper(_mk_upper_special(0x2D, 2, 3)).mnemonic, "MSUBA", "MSUBA")
    eq(decode_upper(_mk_upper_special(0x2E, 2, 3)).mnemonic, "OPMULA", "OPMULA")
    eq(decode_upper(0x000002FF).mnemonic, "NOP", "upper NOP 0x2FF")
    eq(decode_upper(_mk_upper_special(0x2B, 2, 3)).mnemonic, "UNKNOWN", "upper special 0x2B undefined")
    eq(decode_upper(_mk_upper_special(0x3F, 2, 3)).mnemonic, "UNKNOWN", "upper special 0x3F undefined")
    eq(decode_upper(_mk_upper(0x30, 1, 2, 3)).mnemonic, "UNKNOWN", "upper funct 0x30 undefined")
    # --- flags ---
    ins = decode_pair(0x400002FF, LOWER_NOP)
    eq((ins.E, ins.I, ins.M, ins.D, ins.T), (True, False, False, False, False), "E flag")
    eq(ins.lower.mnemonic, "NOP", "lower NOP")
    ins = decode_pair(0x800002FF, 0x3F800000)
    eq(ins.lower.mnemonic, "LOI", "LOI when I set")
    eq(ins.lower.text, "loi 1.0", "LOI value")
    ins = decode_pair(0x380002FF, LOWER_NOP)
    eq(ins.flags, "MDT", "M/D/T flags")
    # --- lower, opcode table ---
    eq(decode_lower(_mk_lower(0x00, it=1, is_=2, dest=0xF, imm11=-1), False).text, "lq.xyzw vf01, -1(vi02)", "LQ")
    eq(decode_lower(_mk_lower(0x01, it=1, is_=2, dest=0xF, imm11=3), False).text, "sq.xyzw vf02, 3(vi01)", "SQ")
    eq(decode_lower(_mk_lower(0x04, it=1, is_=2, dest=0x8), False).mnemonic, "ILW", "ILW")
    eq(decode_lower(_mk_lower(0x05, it=1, is_=2, dest=0x8), False).mnemonic, "ISW", "ISW")
    op = decode_lower((0x08 << 25) | (1 << 16) | (2 << 11) | (0xF << 21) | 0x7FF, False)
    eq((op.mnemonic, op.fields["imm15"]), ("IADDIU", 0x7FFF), "IADDIU imm15")
    eq(decode_lower(_mk_lower(0x09, it=1, is_=2), False).mnemonic, "ISUBIU", "ISUBIU")
    eq(decode_lower(_mk_lower(0x10) | 0xABCDEF, False).text, "fceq vi01, 0xabcdef", "FCEQ")
    eq(decode_lower(_mk_lower(0x11) | 0x123456, False).text, "fcset 0x123456", "FCSET")
    eq(decode_lower(_mk_lower(0x12), False).mnemonic, "FCAND", "FCAND")
    eq(decode_lower(_mk_lower(0x13), False).mnemonic, "FCOR", "FCOR")
    eq(decode_lower(_mk_lower(0x14, it=3), False).mnemonic, "FSEQ", "FSEQ")
    eq(decode_lower(_mk_lower(0x15) | (1 << 21) | 0x7FF, False).fields["imm12"], 0xFFF, "FSSET imm12")
    eq(decode_lower(_mk_lower(0x16, it=3), False).mnemonic, "FSAND", "FSAND")
    eq(decode_lower(_mk_lower(0x17, it=3), False).mnemonic, "FSOR", "FSOR")
    eq(decode_lower(_mk_lower(0x18, it=3, is_=4), False).mnemonic, "FMEQ", "FMEQ")
    eq(decode_lower(_mk_lower(0x1A, it=3, is_=4), False).mnemonic, "FMAND", "FMAND")
    eq(decode_lower(_mk_lower(0x1B, it=3, is_=4), False).mnemonic, "FMOR", "FMOR")
    eq(decode_lower(_mk_lower(0x1C, it=3), False).mnemonic, "FCGET", "FCGET")
    op = decode_lower(_mk_lower(0x20, imm11=-3), False, pc=16)
    eq((op.mnemonic, op.branch_target, op.branch_wraps), ("B", 0, False), "B backwards to 0")
    op = decode_lower(_mk_lower(0x20, imm11=-2), False, pc=0)
    eq((op.branch_target, op.branch_target_raw, op.branch_wraps), (0x3FF8, -8, True), "B wraps below 0")
    op = decode_lower(_mk_lower(0x20, imm11=0x2A5), False, pc=0x56C * 8)
    eq((op.branch_target // 8, op.branch_target_raw // 8, op.branch_wraps), (0x12, 0x812, True), "B wraps above 16K")
    op = decode_lower(_mk_lower(0x20, imm11=-2), False, pc=0, micro_bytes=0x1000)
    eq(op.branch_target, 0xFF8, "VU0 4 KiB wrap")
    op = decode_lower(_mk_lower(0x21, it=5, imm11=2), False, pc=0)
    eq((op.mnemonic, op.branch_target, op.vi_write), ("BAL", 24, (5,)), "BAL")
    op = decode_lower(_mk_lower(0x24, is_=7), False)
    eq((op.mnemonic, op.branch_indirect), ("JR", True), "JR")
    eq(decode_lower(_mk_lower(0x25, it=5, is_=7), False).mnemonic, "JALR", "JALR")
    op = decode_lower(_mk_lower(0x28, it=1, is_=2, imm11=4), False, pc=0)
    eq((op.mnemonic, op.branch_conditional, op.branch_target), ("IBEQ", True, 40), "IBEQ")
    eq(decode_lower(_mk_lower(0x29, it=1, is_=2), False).mnemonic, "IBNE", "IBNE")
    eq(decode_lower(_mk_lower(0x2C, is_=2), False).mnemonic, "IBLTZ", "IBLTZ")
    eq(decode_lower(_mk_lower(0x2D, is_=2), False).mnemonic, "IBGTZ", "IBGTZ")
    eq(decode_lower(_mk_lower(0x2E, is_=2), False).mnemonic, "IBLEZ", "IBLEZ")
    eq(decode_lower(_mk_lower(0x2F, is_=2), False).mnemonic, "IBGEZ", "IBGEZ")
    eq(decode_lower(_mk_lower(0x02), False).mnemonic, "UNKNOWN", "opcode 0x02 undefined")
    eq(decode_lower(_mk_lower(0x19), False).mnemonic, "UNKNOWN", "opcode 0x19 undefined")
    # --- lower, opcode 0x40 integer ---
    eq(decode_lower((0x40 << 25) | (1 << 16) | (2 << 11) | (3 << 6) | 0x30, False).text,
       "iadd vi03, vi02, vi01", "IADD")
    eq(decode_lower((0x40 << 25) | (1 << 16) | (2 << 11) | (3 << 6) | 0x31, False).mnemonic, "ISUB", "ISUB")
    op = decode_lower((0x40 << 25) | (1 << 16) | (2 << 11) | (0x1F << 6) | 0x32, False)
    eq((op.mnemonic, op.fields["imm5"]), ("IADDI", -1), "IADDI -1")
    eq(decode_lower((0x40 << 25) | 0x34, False).mnemonic, "IAND", "IAND")
    eq(decode_lower((0x40 << 25) | 0x35, False).mnemonic, "IOR", "IOR")
    eq(decode_lower((0x40 << 25) | 0x33, False).mnemonic, "UNKNOWN", "int funct 0x33 undefined")
    # --- lower, opcode 0x40 special ---
    eq(decode_lower(_mk_lower_special(0x30, it=1, is_=2), False).text, "move.xyzw vf01, vf02", "MOVE")
    eq(decode_lower(_mk_lower_special(0x31, it=1, is_=2), False).mnemonic, "MR32", "MR32")
    eq(decode_lower(_mk_lower_special(0x34, it=1, is_=2), False).text, "lqi.xyzw vf01, (vi02++)", "LQI")
    eq(decode_lower(_mk_lower_special(0x35, it=1, is_=2), False).text, "sqi.xyzw vf02, (vi01++)", "SQI")
    eq(decode_lower(_mk_lower_special(0x36, it=1, is_=2), False).mnemonic, "LQD", "LQD")
    eq(decode_lower(_mk_lower_special(0x37, it=1, is_=2), False).mnemonic, "SQD", "SQD")
    eq(decode_lower(_mk_lower_special(0x38, it=1, is_=2, dest=0, fsf=3, ftf=0), False).text,
       "div Q, vf02w, vf01x", "DIV")
    eq(decode_lower(_mk_lower_special(0x39, it=1, dest=0), False).mnemonic, "SQRT", "SQRT")
    eq(decode_lower(_mk_lower_special(0x3A, it=1, is_=2, dest=0), False).mnemonic, "RSQRT", "RSQRT")
    eq(decode_lower(_mk_lower_special(0x3B, dest=0), False).mnemonic, "WAITQ", "WAITQ")
    eq(decode_lower(_mk_lower_special(0x3C, it=1, is_=2, dest=0), False).mnemonic, "MTIR", "MTIR")
    eq(decode_lower(_mk_lower_special(0x3D, it=1, is_=2), False).mnemonic, "MFIR", "MFIR")
    eq(decode_lower(_mk_lower_special(0x3E, it=1, is_=2), False).mnemonic, "ILWR", "ILWR")
    eq(decode_lower(_mk_lower_special(0x3F, it=1, is_=2), False).mnemonic, "ISWR", "ISWR")
    eq(decode_lower(_mk_lower_special(0x40, it=1), False).mnemonic, "RNEXT", "RNEXT")
    eq(decode_lower(_mk_lower_special(0x41, it=1), False).mnemonic, "RGET", "RGET")
    eq(decode_lower(_mk_lower_special(0x42, is_=2, dest=0), False).mnemonic, "RINIT", "RINIT")
    eq(decode_lower(_mk_lower_special(0x43, is_=2, dest=0), False).mnemonic, "RXOR", "RXOR")
    eq(decode_lower(_mk_lower_special(0x64, it=1), False).mnemonic, "MFP", "MFP")
    eq(decode_lower(_mk_lower_special(0x68, it=1, dest=0), False).text, "xtop vi01", "XTOP")
    eq(decode_lower(_mk_lower_special(0x69, it=1, dest=0), False).text, "xitop vi01", "XITOP")
    eq(decode_lower(_mk_lower_special(0x6C, is_=2, dest=0), False).text, "xgkick vi02", "XGKICK")
    for idx, name in ((0x70, "ESADD"), (0x71, "ERSADD"), (0x72, "ELENG"), (0x73, "ERLENG"), (0x74, "EATANxy"),
                      (0x75, "EATANxz"), (0x76, "ESUM"), (0x78, "ESQRT"), (0x79, "ERSQRT"), (0x7A, "ERCPR"),
                      (0x7B, "WAITP"), (0x7C, "ESIN"), (0x7D, "EATAN"), (0x7E, "EEXP")):
        eq(decode_lower(_mk_lower_special(idx, is_=2, dest=0), False).mnemonic, name, name)
    eq(decode_lower(_mk_lower_special(0x32, is_=2), False).mnemonic, "UNKNOWN", "special 0x32 undefined")
    eq(decode_lower(_mk_lower_special(0x7F, is_=2), False).mnemonic, "UNKNOWN", "special 0x7F undefined")
    # --- robustness: every opcode/funct/fd combination decodes without raising ---
    for opc in range(128):
        for funct in range(64):
            for idf in (0, 0x0C, 0x1F):
                decode_pair(0xFFFFFFFF, (opc << 25) | (idf << 6) | funct)
                decode_pair(0x00000000, (opc << 25) | (idf << 6) | funct)
    for funct in range(64):
        for fd in range(32):
            decode_upper((fd << 6) | funct)
    checks += 1
    # --- program decode of the 4-unit null-transform image (nop/nop E, nop/nop, b 0, nop/nop) ---
    img = bytes.fromhex("3c030080ff020040" "3c030080ff020000" "fd070040ff020000" "3c030080ff020000")
    prog = decode_program(img)
    eq([i.upper.mnemonic for i in prog], ["NOP"] * 4, "null program uppers")
    eq([i.lower.mnemonic for i in prog], ["NOP", "NOP", "B", "NOP"], "null program lowers")
    eq(prog[0].E, True, "null program E at 0")
    eq(prog[2].lower.branch_target, 0, "null program b -> 0")
    print(f"vu1_decode selftest: {checks} checks passed")


def main(argv: List[str]) -> int:
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0
    if argv[0] == "--selftest":
        selftest()
        return 0
    with open(argv[0], "rb") as fh:
        data = fh.read()
    for insn in decode_program(data):
        print(format_insn(insn))
    if len(data) % 8:
        print(f"; trailing {len(data) % 8} byte(s) not decoded")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
