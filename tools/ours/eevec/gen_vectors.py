#!/usr/bin/env python3
"""EE semantics test vectors: generate an R5900 test program for PCSX2 and the matching vector layout.

Single source of truth for the Phase 4 "compiled test vectors" (GOAL.md Phase 4, ADR-0006 item 5): the tables
in this file describe every vector (operation, operand bit patterns, pre-state); the generator turns them into

  <out>/eevec.s        GNU assembler source for the EE (mips64r5900el-ps2-elf-as -march=r5900): one straight-
                       line block per vector that loads the operands, runs the instruction and stores every
                       architectural result into a fixed results table in RAM, then writes a marker and loops
  <out>/layout.json    the same vectors with their result-slot addresses, consumed by run_pcsx2.py

and, with --build, assembles and links <out>/eevec.elf (freestanding, entry 0x100000, no libc).

Results table (RAM, kuseg VA, read back over PINE):
  RESULTS_BASE + 0   u32 magic   written LAST, after every vector of the safe section
  RESULTS_BASE + 4   u32 count   number of vectors
  RESULTS_BASE + 8   u32 progress  index of the last completed vector + 1 (survives a trap in a later vector)
  RESULTS_BASE + 12  u32 tail_magic  written after the "risky" vectors that may raise an exception on hardware
  RESULTS_BASE + 64 + i * SLOT_BYTES   slot of vector i (SLOT_BYTES = 96):
      +0  qw  rd        the destination register after the instruction (family-specific, see decode_slot)
      +16 qw  hi        HI (both pipes, PMFHI) / FPU: ACC probe / VU0: ACC probe
      +32 qw  lo        LO (PMFLO) / core memory ops: second memory quadword
      +48 4 x u32 x0..x3, +64 4 x u32 x4..x7   family-specific extras (SA, FCR31, VU0 flags ...)
      +80 qw  spare

Register conventions in the emitted code (numeric names: the n32 ABI the toolchain defaults to has no $t4..$t7):
  $1 = address temp, $8 rs, $9 rt, $10 rd, $11..$15 temps, $16 = slot address, $20 = scratch RAM base.

Usage:
  python -I tools/ours/eevec/gen_vectors.py --out build/eevec-msvc/eevec [--build] [--toolchain DIR]
"""
import argparse
import json
import os
import pathlib
import struct
import subprocess
import sys

GENERATOR_VERSION = "1.1"
RESULTS_BASE = 0x01000000   # 16 MiB: inside the 32 MiB EE RAM, far from the ELF at 0x100000
SCRATCH_BASE = 0x01100000   # memory-operand scratch area (core family)
SLOT_BYTES = 96
HEADER_BYTES = 64
MAGIC = 0x50334645          # "P3FE"
TAIL_MAGIC = 0x454E4421     # "END!"

# ------------------------------------------------------------------------------------------------------------
# Bit-pattern helpers (all values are raw bits; nothing is ever a host float)
# ------------------------------------------------------------------------------------------------------------
M32 = 0xFFFFFFFF
M64 = 0xFFFFFFFFFFFFFFFF


def u32(x):
    return x & M32


def u64(x):
    return x & M64


def q32(w0, w1, w2, w3):
    """Quadword from four 32-bit lanes, lane 0 least significant."""
    return (u32(w3) << 96) | (u32(w2) << 64) | (u32(w1) << 32) | u32(w0)


def q64(lo, hi=0):
    return (u64(hi) << 64) | u64(lo)


def q16(*h):
    assert len(h) == 8
    v = 0
    for i, x in enumerate(h):
        v |= (x & 0xFFFF) << (16 * i)
    return v


def q8(*b):
    assert len(b) == 16
    v = 0
    for i, x in enumerate(b):
        v |= (x & 0xFF) << (8 * i)
    return v


def hex32(x):
    return "0x%08X" % u32(x)


def hex64(x):
    return "0x%016X" % u64(x)


def hex128(x):
    return "0x%032X" % (x & ((1 << 128) - 1))


# Float bit patterns used across the FPU and VU0 families (names are documentation only).
F = {
    "1.0": 0x3F800000, "2.0": 0x40000000, "3.0": 0x40400000, "4.0": 0x40800000, "0.5": 0x3F000000,
    "0.25": 0x3E800000, "1.5": 0x3FC00000, "2.25": 0x40100000, "6.0": 0x40C00000, "7.0": 0x40E00000,
    "10.0": 0x41200000, "20.0": 0x41A00000, "1000.0": 0x447A0000, "0.1": 0x3DCCCCCD, "pi": 0x40490FDB,
    "1e6": 0x49742400, "100.5": 0x42C90000, "3.99": 0x407F5C29, "1/3": 0x3EAAAAAB, "2/3": 0x3F2AAAAB,
    "-1.0": 0xBF800000, "-2.0": 0xC0000000, "-3.0": 0xC0400000, "-1.5": 0xBFC00000, "-0.5": 0xBF000000,
    "-6.0": 0xC0C00000, "-100.5": 0xC2C90000, "-4.0": 0xC0800000,
    "+0": 0x00000000, "-0": 0x80000000,
    "den": 0x00000001, "-den": 0x80000001, "denmax": 0x007FFFFF, "-denmax": 0x807FFFFF,
    "minnorm": 0x00800000, "-minnorm": 0x80800000, "minnorm+": 0x00800001, "oddmin": 0x00FFFFFF,
    "fltmax": 0x7F7FFFFF, "-fltmax": 0xFF7FFFFF, "eemax": 0x7FFFFFFF, "-eemax": 0xFFFFFFFF,
    "inf": 0x7F800000, "-inf": 0xFF800000, "qnan": 0x7FC00000, "-qnan": 0xFFC00000, "snan": 0x7F800001,
    "1+ulp": 0x3F800001, "1-ulp": 0x3F7FFFFF, "2-ulp": 0x3FFFFFFF, "1+2ulp": 0x3F800002,
    "1.5ulp": 0x34400000,   # 1.5 * 2^-23
    "2^-24": 0x33800000, "2^-25": 0x33000000, "2^-26": 0x32800000, "2^-31": 0x30000000, "2^-100": 0x0D800000,
    "2^24": 0x4B800000, "2^24-1": 0x4B7FFFFF, "2^24+2": 0x4B800001, "2^27": 0x4D000000, "2^30": 0x4E800000,
    "2^31": 0x4F000000, "-2^31": 0xCF000000, "2^31-128": 0x4EFFFFFF, "-2^31-256": 0xCF000001, "2^32": 0x4F800000,
    "-2^32": 0xCF800000, "2^63": 0x5F000000, "-2^63": 0xDF000000, "2^126": 0x7E800000, "2^64": 0x5F800000,
    "2^-126*1.5": 0x00C00000, "0x3F000001": 0x3F000001, "0x4EFFFFFE": 0x4EFFFFFE,
    "-1-ulp": 0xBF7FFFFF, "-1+ulp": 0xBF800001, "-2^-24": 0xB3800000, "-2^-25": 0xB3000000, "-2^-26": 0xB2800000,
    "9.0": 0x41100000, "16.0": 0x41800000,
}


# ------------------------------------------------------------------------------------------------------------
# Vector description
# ------------------------------------------------------------------------------------------------------------
class Vec:
    __slots__ = ("family", "op", "form", "inputs", "data", "risky", "note")

    def __init__(self, family, op, inputs, data, form=None, risky=False, note=""):
        self.family = family      # hilo | mmi | fpu | vu0 | core
        self.op = op              # assembler mnemonic (e.g. "paddw", "add.s", "vaddx.xyzw", "lwr")
        self.form = form or {}    # operand-form details (imm, dest, bc, fmt, byte offset ...)
        self.inputs = inputs      # named inputs as ints (the JSON gets hex strings)
        self.data = data          # list of quadword ints emitted into .data (up to 6)
        self.risky = risky        # may raise an exception: runs after the magic marker
        self.note = note


VECTORS = []


def add(v):
    VECTORS.append(v)
    return v


# ------------------------------------------------------------------------------------------------------------
# hilo: MULT/MULTU/DIV/DIVU/MADD/MADDU on both pipes, 2- and 3-operand forms
# ------------------------------------------------------------------------------------------------------------
HI_SENTINEL = q32(0x11111111, 0x22222222, 0x33333333, 0x44444444)
LO_SENTINEL = q32(0x55555555, 0x66666666, 0x77777777, 0x88888888)
RD_SENTINEL = q32(0xDEADBEEF, 0xCAFEBABE, 0xFEEDFACE, 0x0BADF00D)

HILO_PAIRS = [
    (7, 2), (u32(-7), 2), (7, u32(-2)), (u32(-7), u32(-2)), (0x7FFFFFFF, 2), (0x80000000, 0x80000000),
    (0xFFFFFFFF, 0xFFFFFFFF), (0, 5), (5, 0), (0, 0), (u32(-5), 0), (0x80000000, 0xFFFFFFFF), (0x80000000, 1),
    (0x12345678, 0x9ABCDEF0), (0xFFFFFFFF, 2), (100, 7), (u32(-100), 7), (100, u32(-7)), (0x7FFFFFFF, 0x7FFFFFFF),
    (1, 0xFFFFFFFF), (0x80000000, 0), (0xFFFFFFFF, 0), (0x10000, 0x10000), (0x7FFFFFFF, 0x80000000),
]
# 64-bit register images: the instruction must read only the low word (manual); the high word is garbage here.
HILO_PAIRS64 = [
    (0xDEADBEEF00000007, 0x1234567800000002), (0x0000000100000000 | u32(-7), 0xFFFFFFFF00000002),
    (0xFFFFFFFF80000000, 0x00000000FFFFFFFF),
]
# {HI, LO} presets for MADD/MADDU: (hi64, lo64). Only HI[31:0]/LO[31:0] feed the accumulate (manual).
HILO_PRESETS = [
    (0, 0), (1, 0xFFFFFFFF), (M64, M64), (0x7FFFFFFF, 0xFFFFFFFF), (0xFFFFFFFF80000000, 0),
    (0xDEADBEEF00000001, 0x1234567800000005),
]


def gen_hilo():
    for pipe in (0, 1):
        sfx = "1" if pipe else ""
        for op in ("mult", "multu", "div", "divu", "madd", "maddu"):
            pairs = HILO_PAIRS + HILO_PAIRS64
            for s, t in pairs:
                presets = HILO_PRESETS if op in ("madd", "maddu") else [(0x1111111122222222, 0x5555555566666666)]
                for hi, lo in presets:
                    if op in ("madd", "maddu") and (s, t) not in HILO_PAIRS[:14] and (hi, lo) != HILO_PRESETS[0]:
                        continue
                    hi128 = HI_SENTINEL & ~((1 << 64) - 1) | u64(hi)
                    lo128 = LO_SENTINEL & ~((1 << 64) - 1) | u64(lo)
                    if pipe:
                        hi128 = (u64(hi) << 64) | (HI_SENTINEL & M64)
                        lo128 = (u64(lo) << 64) | (LO_SENTINEL & M64)
                    add(Vec("hilo", op + sfx, {"rs": s, "rt": t, "hi": hi128, "lo": lo128, "rd": RD_SENTINEL},
                            [q64(s), q64(t), hi128, lo128, RD_SENTINEL], form={"pipe": pipe, "rd": False}))
    # three-operand forms: rd <- LO of the pipe
    for op in ("mult", "multu", "mult1", "multu1", "madd", "maddu", "madd1", "maddu1"):
        for s, t in ((7, 2), (0x7FFFFFFF, 2), (0xFFFFFFFF, 0xFFFFFFFF), (0x80000000, 0x80000000), (0x12345678, 0x9ABCDEF0)):
            hi128 = HI_SENTINEL & ~((1 << 64) - 1) | 1
            lo128 = LO_SENTINEL & ~((1 << 64) - 1) | 0xFFFFFFFF
            pipe = 1 if op.endswith("1") else 0
            if pipe:
                hi128 = (1 << 64) | (HI_SENTINEL & M64)
                lo128 = (0xFFFFFFFF << 64) | (LO_SENTINEL & M64)
            add(Vec("hilo", op, {"rs": s, "rt": t, "hi": hi128, "lo": lo128, "rd": RD_SENTINEL},
                    [q64(s), q64(t), hi128, lo128, RD_SENTINEL], form={"pipe": pipe, "rd": True}))
    # mthi/mtlo/mfhi/mflo 64-bit round trips (both pipes)
    for op in ("mthi", "mtlo", "mthi1", "mtlo1"):
        for s in (0xDEADBEEF12345678, 0x80000000, 0xFFFFFFFF80000000):
            add(Vec("hilo", op, {"rs": s, "rt": 0, "hi": HI_SENTINEL, "lo": LO_SENTINEL, "rd": RD_SENTINEL},
                    [q64(s), q64(0), HI_SENTINEL, LO_SENTINEL, RD_SENTINEL], form={"pipe": 1 if op.endswith("1") else 0, "rd": False}))


# ------------------------------------------------------------------------------------------------------------
# MMI
# ------------------------------------------------------------------------------------------------------------
LANE_PAIRS = [
    (q32(0xFFFFFFFF, 1, 0x7FFFFFFF, 0), q32(1, 1, 1, 0)),
    (q32(0, 5, 0x80000000, 1), q32(1, 3, 1, 1)),
    (q32(0x7FFFFFFF, 0x80000000, 5, 0x80000000), q32(1, 0xFFFFFFFF, u32(-3), 0x7FFFFFFF)),
    (q16(0xFFFF, 1, 0x7FFF, 0, 0x8000, 0x7FFF, 0x1234, 0x8000), q16(1, 1, 1, 0, 0x8000, 1, 0x4321, 0x7FFF)),
    (q8(0xFF, 1, 0x7F, 0x80, 0, 0x80, 0x7F, 1, 0x10, 0x20, 0x30, 0x40, 0xF0, 0xE0, 0xD0, 0xC0),
     q8(1, 1, 1, 0x80, 0, 0x7F, 0x7F, 0xFF, 0x11, 0x22, 0x33, 0x44, 0x0F, 0x1F, 0x2F, 0x3F)),
    (q32(0x01234567, 0x89ABCDEF, 0xFEDCBA98, 0x76543210), q32(0x00FF00FF, 0xFF00FF00, 0x0F0F0F0F, 0xF0F0F0F0)),
    (q32(0x80000000, 0x80000000, 0x7FFFFFFF, 0x7FFFFFFF), q32(0x80000000, 0x7FFFFFFF, 0x80000000, 0x7FFFFFFF)),
    (q32(0, 0, 0, 0), q32(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF)),
    (q16(0x8000, 0x8000, 0x7FFF, 0x7FFF, 0xFFFF, 0x0001, 0x0000, 0xFFFF), q16(0x8000, 0x7FFF, 0x8000, 0x7FFF, 0xFFFF, 0xFFFF, 0x0000, 0x0001)),
    (q8(0x80, 0x80, 0x7F, 0x7F, 0xFF, 0x01, 0x00, 0xFF, 0x80, 0x7F, 0x7F, 0x80, 0x01, 0xFF, 0xFF, 0x01),
     q8(0x80, 0x7F, 0x80, 0x7F, 0xFF, 0xFF, 0x00, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0x80, 0x80, 0x7F, 0x7F)),
]
MMI_BIN = ["paddw", "psubw", "paddh", "psubh", "paddb", "psubb", "paddsw", "psubsw", "paddsh", "psubsh", "paddsb",
           "psubsb", "padduw", "psubuw", "padduh", "psubuh", "paddub", "psubub", "pcgtw", "pcgth", "pcgtb", "pceqw",
           "pceqh", "pceqb", "pmaxw", "pminw", "pmaxh", "pminh", "padsbh", "pand", "por", "pxor", "pnor", "pextlw",
           "pextuw", "pextlh", "pextuh", "pextlb", "pextub", "ppacw", "ppach", "ppacb", "pinth", "pinteh", "pcpyld",
           "pcpyud"]
MMI_UN = ["pabsw", "pabsh", "pcpyh", "pexch", "pexcw", "pexeh", "pexew", "prevh", "prot3w", "pext5", "ppac5"]
MMI_SHIFT = ["psllh", "psrlh", "psrah", "psllw", "psrlw", "psraw"]
MMI_VSHIFT = ["psllvw", "psrlvw", "psravw"]


def mmi_vec(op, s, t, form=None, hi=HI_SENTINEL, lo=LO_SENTINEL, sa_form=None, sa_rs=0, sa_imm=0, risky=False, note=""):
    inputs = {"rs": s, "rt": t, "hi": hi, "lo": lo, "rd": RD_SENTINEL}
    f = dict(form or {})
    if sa_form:
        f["sa_form"] = sa_form
        f["sa_imm"] = sa_imm
        inputs["sa_rs"] = sa_rs
    return add(Vec("mmi", op, inputs, [s, t, hi, lo, RD_SENTINEL, q64(sa_rs)], form=f, risky=risky, note=note))


def gen_mmi():
    for op in MMI_BIN:
        for s, t in LANE_PAIRS:
            mmi_vec(op, s, t)
    for op in MMI_UN:
        for s, t in LANE_PAIRS[:6]:
            mmi_vec(op, 0, t)
    for op in MMI_SHIFT:
        for sa in (0, 1, 7, 15, 16, 31):
            for s, t in LANE_PAIRS[2:5]:
                mmi_vec(op, 0, t, form={"sa": sa})
    for op in MMI_VSHIFT:
        for shifts in (q32(0, 0, 0, 0), q32(1, 0, 31, 0), q32(33, 0, 32, 0), q32(0xFFFFFFFF, 0, 7, 0), q32(16, 5, 15, 9)):
            for s, t in LANE_PAIRS[2:4] + [LANE_PAIRS[6]]:
                mmi_vec(op, shifts, t)
    # plzcw: rd[127:64] undefined on hardware; rd carries a sentinel so the choice is observable
    for s in (q32(0, 0xFFFFFFFF, 1, 0x80000000), q32(0x7FFFFFFF, 0x80000000, 0x0000FFFF, 0xFFFF0000),
              q32(0x40000000, 0xBFFFFFFF, 0x00000002, 0xFFFFFFFD)):
        mmi_vec("plzcw", s, 0)
    # qfsrv with SA from mtsab / mtsah / mtsa
    s = q8(*range(0x10, 0x20))
    t = q8(*range(0x00, 0x10))
    for imm in range(16):
        mmi_vec("qfsrv", s, t, sa_form="mtsab", sa_rs=0, sa_imm=imm)
    for rs, imm in ((5, 3), (0xFFFFFFF0, 0), (0x1F, 0x1F), (0x100, 0x7)):
        mmi_vec("qfsrv", s, t, sa_form="mtsab", sa_rs=rs, sa_imm=imm)
    for imm in range(8):
        mmi_vec("qfsrv", s, t, sa_form="mtsah", sa_rs=0, sa_imm=imm)
    for rs, imm in ((3, 1), (0xFFFFFFF8, 0), (0x0F, 0x0F)):
        mmi_vec("qfsrv", s, t, sa_form="mtsah", sa_rs=rs, sa_imm=imm)
    for rs in (0, 8, 16, 120, 128, 3, 12, 0x88, 0xFFFFFFFF, 0x80000000, 0x40):
        mmi_vec("qfsrv", s, t, sa_form="mtsa", sa_rs=rs)
    # pmfhl formats on several HI/LO images
    hilo_images = [
        (HI_SENTINEL, LO_SENTINEL),
        (q32(0x7FFFFFFF, 0x80000000, 0x00008000, 0xFFFF7FFF), q32(0x00007FFF, 0xFFFF8000, 0x12345678, 0x9ABCDEF0)),
        (q32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0), q32(0x80000000, 0x7FFFFFFF, 0xFFFFFFFF, 0x00000001)),
        (q32(0x00010000, 0xFFFF0000, 0x7FFF8000, 0x80007FFF), q32(0xFFFFFFFF, 0x00000000, 0x0000FFFF, 0xFFFF0000)),
    ]
    for fmt in ("lw", "uw", "slw", "lh", "sh"):
        for hi, lo in hilo_images:
            mmi_vec("pmfhl." + fmt, 0, 0, hi=hi, lo=lo, form={"fmt": {"lw": 0, "uw": 1, "slw": 2, "lh": 3, "sh": 4}[fmt]})
    for fmt in (5, 6, 31):   # reserved formats: raw encoding, may be a Reserved Instruction on hardware
        mmi_vec("pmfhl.raw", 0, 0, hi=hilo_images[1][0], lo=hilo_images[1][1], form={"fmt": fmt}, risky=True)
    for hi, lo in hilo_images[:2]:
        for s, _ in LANE_PAIRS[:3]:
            mmi_vec("pmthl.lw", s, 0, hi=hi, lo=lo)
    for op in ("pmfhi", "pmflo"):
        for hi, lo in hilo_images[:2]:
            mmi_vec(op, 0, 0, hi=hi, lo=lo)
    for op in ("pmthi", "pmtlo"):
        for s, _ in LANE_PAIRS[:2]:
            mmi_vec(op, s, 0)
    # word multiply family (lanes 0 and 2 into pipes 0 and 1)
    wpairs = [
        (q32(7, 0, u32(-7), 0), q32(2, 0, 2, 0)),
        (q32(0x7FFFFFFF, 1, 0x80000000, 1), q32(0x7FFFFFFF, 1, 0x80000000, 1)),
        (q32(0xFFFFFFFF, 0, 0xFFFFFFFF, 0), q32(0xFFFFFFFF, 0, 2, 0)),
        (q32(0x12345678, 0xAAAAAAAA, 0x9ABCDEF0, 0xBBBBBBBB), q32(0x9ABCDEF0, 0xCCCCCCCC, 0x12345678, 0xDDDDDDDD)),
        (q32(0x10000, 0, 0x10000, 0), q32(0x10000, 0, 0xFFFF0000, 0)),
        (q32(0, 0, 1, 0), q32(5, 0, 0, 0)),
    ]
    for op in ("pmultw", "pmultuw", "pmaddw", "pmsubw", "pmadduw"):
        for s, t in wpairs:
            for hi, lo in ((HI_SENTINEL, LO_SENTINEL), (q32(1, 0x11111111, 0xFFFFFFFF, 0x22222222), q32(0xFFFFFFFF, 0x33333333, 0xFFFFFFFF, 0x44444444))):
                if op.startswith("pmult") and (hi, lo) != (HI_SENTINEL, LO_SENTINEL):
                    continue
                mmi_vec(op, s, t, hi=hi, lo=lo)
    dpairs = [
        (q32(u32(-7), 0, 100, 0), q32(2, 0, 0, 0)), (q32(0xFFFFFFFF, 0, 7, 0), q32(16, 0, 0, 0)),
        (q32(0x80000000, 0, 0x80000000, 0), q32(0xFFFFFFFF, 0, 1, 0)), (q32(0, 0, 0, 0), q32(0, 0, 5, 0)),
        (q32(u32(-5), 0, 5, 0), q32(0, 0, 0, 0)), (q32(100, 0, u32(-100), 0), q32(u32(-7), 0, 7, 0)),
        (q32(0x7FFFFFFF, 0, 0x12345678, 0), q32(0x7FFFFFFF, 0, 0x9ABCDEF0, 0)),
        (q32(1, 0, 0xFFFFFFFF, 0), q32(0xFFFFFFFF, 0, 0xFFFFFFFF, 0)),
    ]
    for op in ("pdivw", "pdivuw"):
        for s, t in dpairs:
            mmi_vec(op, s, t)
    bpairs = [
        (q32(100, u32(-100), 7, 0x80000000), q16(3, 0, 0, 0, 0, 0, 0, 0)),
        (q32(5, u32(-5), 0, 0x7FFFFFFF), q16(0, 0, 0, 0, 0, 0, 0, 0)),
        (q32(0x80000000, 1, u32(-1), 0x7FFFFFFF), q16(0xFFFF, 0, 0, 0, 0, 0, 0, 0)),
        (q32(0x12345678, 0x9ABCDEF0, 0x7FFFFFFF, 0x80000000), q16(0x7FFF, 0, 0, 0, 0, 0, 0, 0)),
        (q32(0x12345678, 0x9ABCDEF0, 0x7FFFFFFF, 0x80000000), q16(0x8000, 0x1234, 0, 0, 0, 0, 0, 0)),
        (q32(65535, u32(-65535), 0x10000, 0xFFFF0000), q16(0x100, 0, 0, 0, 0, 0, 0, 0)),
    ]
    for s, t in bpairs:
        mmi_vec("pdivbw", s, t)
    hpairs = [
        (q16(1, 2, 3, 4, 5, 6, 7, 8), q16(8, 7, 6, 5, 4, 3, 2, 1)),
        (q16(0x7FFF, 0x8000, 0x7FFF, 0x8000, 0xFFFF, 0x0001, 0x8000, 0x7FFF), q16(0x7FFF, 0x8000, 0x8000, 0x7FFF, 0xFFFF, 0xFFFF, 0x8000, 0x8000)),
        (q16(0x1234, 0x5678, 0x9ABC, 0xDEF0, 0x0F0F, 0xF0F0, 0x00FF, 0xFF00), q16(0x4321, 0x8765, 0xCBA9, 0x0FED, 0xF0F0, 0x0F0F, 0xFF00, 0x00FF)),
        (q16(0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF), q16(0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF)),
        (q16(0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000), q16(0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000)),
    ]
    for op in ("pmulth", "pmaddh", "pmsubh", "phmadh", "phmsbh"):
        for s, t in hpairs:
            for hi, lo in ((HI_SENTINEL, LO_SENTINEL), (q32(0x7FFFFFFF, 0x11111111, 0x80000000, 0x22222222), q32(0x7FFFFFF0, 0x33333333, 0x80000010, 0x44444444))):
                if op == "pmulth" and (hi, lo) != (HI_SENTINEL, LO_SENTINEL):
                    continue
                mmi_vec(op, s, t, hi=hi, lo=lo)
    # lq/sq ignore the low four address bits
    for off in (0, 1, 5, 15, 16, 21, 31):
        mmi_vec("lq", q8(*range(0x00, 0x10)), q8(*range(0x10, 0x20)), form={"off": off})
        mmi_vec("sq", q8(*range(0xA0, 0xB0)), 0, form={"off": off})


# ------------------------------------------------------------------------------------------------------------
# FPU (COP1)
# ------------------------------------------------------------------------------------------------------------
def fv(name):
    return F[name] if isinstance(name, str) else u32(name)


FPU_ADD_PAIRS = [
    ("1.0", "1.0"), ("1.5", "2.25"), ("1.0", "-1.0"), ("3.0", "2.0"), ("2.0", "3.0"), ("-0", "-0"), ("+0", "-0"),
    ("-0", "+0"), ("1.0", "den"), ("den", "-den"), ("+0", "2.0"), ("2.0", "+0"), ("fltmax", "fltmax"),
    ("-fltmax", "-fltmax"), ("eemax", "eemax"), ("eemax", "-eemax"), ("1.0", "1.5ulp"), ("1.0", "2^-24"),
    ("1.0", "2^-25"), ("1.0", "2^-26"), ("1.0", "2^-31"), ("1.0", "2^-100"), ("1.0", "-2^-24"), ("1.0", "-1-ulp"),
    ("inf", "1.0"), ("qnan", "1.0"), ("1.0", "qnan"), ("pi", "0.1"), ("1000.0", "0.1"), ("1+ulp", "1+ulp"),
    ("2^24", "1.0"), ("2^24-1", "1.0"), ("2^24", "-1.0"), ("2^63", "-2^63"), ("minnorm", "-minnorm"),
    ("minnorm", "minnorm"), ("oddmin", "-minnorm"), ("denmax", "denmax"), ("2.0", "-1+ulp"), ("eemax", "-fltmax"),
    ("1/3", "2/3"), ("1.0", "-2^-25"), ("2^31", "-1.0"), ("-1.0", "2^-24"), ("1.0", "-2^-26"),
]
FPU_MUL_PAIRS = [
    ("2.0", "3.0"), ("1.5", "1.5"), ("-2.0", "+0"), ("2.0", "-0"), ("den", "2.0"), ("fltmax", "2.0"),
    ("fltmax", "fltmax"), ("eemax", "1.0"), ("eemax", "eemax"), ("2^-100", "2^-100"), ("1+ulp", "1+ulp"),
    ("1/3", "3.0"), ("pi", "0.1"), ("2^63", "2^63"), ("minnorm", "0.5"), ("minnorm", "1.5"), ("oddmin", "1.0"),
    ("qnan", "1.0"), ("inf", "0.5"), ("-1.0", "eemax"), ("2-ulp", "2-ulp"), ("2^126", "2.0"), ("2^126", "2-ulp"),
    ("2^-126*1.5", "0.5"), ("0.1", "10.0"), ("-fltmax", "-fltmax"), ("1-ulp", "1+ulp"), ("2^64", "2^64"),
    ("1.0", "-eemax"), ("-0", "-0"), ("den", "-den"),
]
FPU_DIV_PAIRS = [
    ("1.0", "2.0"), ("6.0", "3.0"), ("1.0", "3.0"), ("2.0", "3.0"), ("1.0", "20.0"), ("1.0", "+0"), ("-1.0", "+0"),
    ("1.0", "-0"), ("+0", "+0"), ("-0", "+0"), ("+0", "-0"), ("+0", "2.0"), ("+0", "-2.0"), ("-0", "2.0"), ("1.0", "den"), ("den", "1.0"),
    ("fltmax", "0.5"), ("eemax", "1.0"), ("eemax", "eemax"), ("1.0", "eemax"), ("1.0", "minnorm"), ("2-ulp", "1-ulp"),
    ("pi", "0.1"), ("1.0", "10.0"), ("10.0", "3.0"), ("fltmax", "minnorm"), ("1.0", "7.0"), ("qnan", "1.0"),
    ("1.0", "qnan"), ("inf", "2.0"), ("-2.0", "1.5"), ("2.0", "1.5"), ("7.0", "1.0"), ("1+ulp", "1+ulp"),
    ("minnorm", "2.0"), ("minnorm", "fltmax"), ("1.0", "-3.0"), ("-1.0", "-3.0"), ("1000.0", "0.1"), ("1.0", "pi"),
    ("2^24+2", "2^24"), ("3.0", "7.0"), ("1.0", "1000.0"),
]
FPU_SQRT = ["4.0", "2.0", "+0", "-0", "den", "-4.0", "1.0", "3.0", "0.5", "fltmax", "eemax", "-eemax", "minnorm",
            "2^-100", "1+ulp", "qnan", "inf", "10.0", "1e6", "-den", "-1.0", "2^126", "0.1", "pi", "2^-24"]
FPU_RSQRT_PAIRS = [
    ("1.0", "4.0"), ("1.0", "+0"), ("-1.0", "+0"), ("+0", "4.0"), ("-0", "4.0"), ("1.0", "-4.0"), ("1.0", "-0"),
    ("2.0", "2.0"), ("1.0", "0.25"), ("1.0", "den"), ("+0", "+0"), ("1.0", "eemax"), ("eemax", "1.0"),
    ("eemax", "minnorm"), ("1.0", "3.0"), ("10.0", "7.0"), ("1.0", "qnan"), ("qnan", "4.0"), ("3.0", "2.0"),
    ("1.0", "2^-100"), ("1.0", "fltmax"), ("-1.0", "-4.0"), ("1.0", "0.1"),
]
FPU_UNARY = ["1.0", "-1.0", "+0", "-0", "den", "-den", "eemax", "-eemax", "qnan", "inf", "fltmax", "minnorm"]
FPU_MADD = [   # (acc, fs, ft)
    ("1.0", "2.0", "3.0"), ("+0", "2.0", "3.0"), ("-6.0", "2.0", "3.0"), ("6.0", "-2.0", "3.0"), ("1.0", "2^-100", "2^-100"),
    ("fltmax", "2.0", "2.0"), ("eemax", "-eemax", "1.0"), ("1.0", "1+ulp", "1+ulp"), ("2^24", "1.0", "1.0"),
    ("1.0", "3.0", "1/3"), ("2.0", "1.5", "1.5"), ("-0", "-0", "1.0"), ("+0", "-0", "1.0"), ("+0", "+0", "-1.0"),
    ("1.0", "den", "2.0"), ("1.0", "1.5ulp", "1.0"), ("1.0", "2^-24", "1.0"), ("1.0", "1.0", "-1.0"),
    ("fltmax", "fltmax", "fltmax"), ("pi", "0.1", "10.0"), ("1.0", "2-ulp", "2-ulp"), ("2^126", "2^126", "-2.0"),
    ("1.0", "2^63", "2^63"), ("1000.0", "0.1", "0.1"), ("1+ulp", "1-ulp", "1+ulp"),
]
FPU_MAXMIN_PAIRS = [
    ("1.0", "2.0"), ("2.0", "1.0"), ("1.0", "-1.0"), ("-1.0", "1.0"), ("+0", "-0"), ("-0", "+0"), ("1.0", "1.0"),
    ("den", "+0"), ("den", "-den"), ("-den", "+0"), ("eemax", "fltmax"), ("qnan", "1.0"), ("1.0", "qnan"),
    ("-eemax", "-fltmax"), ("1+ulp", "1.0"), ("-2.0", "-3.0"), ("-3.0", "-2.0"), ("inf", "eemax"), ("-0", "-0"),
]
FPU_CVT_W = ["1.0", "1.5", "-1.5", "0.5", "-0.5", "1-ulp", "2^31", "-2^31", "2^31-128", "2^32", "-2^32", "eemax",
             "-eemax", "qnan", "inf", "den", "-den", "+0", "-0", "2^24", "2^24+2", "1e6", "0.1", "100.5", "-100.5",
             "2^30", "-2^31-256", "3.99", "2^63", "-fltmax", "0x4EFFFFFE", "-1.0", "2^-24", "-inf", "fltmax"]
FPU_CVT_S = [0, 1, u32(-1), 7, u32(-7), 0x7FFFFFFF, 0x80000000, 0x00FFFFFF, 0x01000000, 0x01000001, 0x01000003,
             0xFF000000, 0xFEFFFFFF, 0x12345678, 0x7FFFFFFE, 0x0FFFFFFF, 0xFFFFFF80, 0x00800001, 0x33333333,
             0x7FFFFF80, 0x7FFFFFC0, 0x7FFFFFBF, 0x80000001, 0x01000002, 0x02000003, 0xFEFFFFFD]
FPU_CMP_PAIRS = [
    ("1.0", "2.0"), ("2.0", "1.0"), ("1.0", "1.0"), ("+0", "-0"), ("-0", "+0"), ("den", "+0"), ("-den", "+0"),
    ("den", "-den"), ("qnan", "1.0"), ("1.0", "qnan"), ("qnan", "qnan"), ("inf", "fltmax"), ("eemax", "eemax"),
    ("-eemax", "eemax"), ("-1.0", "-2.0"), ("-2.0", "-1.0"), ("1+ulp", "1.0"), ("-0", "-0"), ("den", "den"),
    ("-den", "den"), ("minnorm", "den"), ("-qnan", "qnan"),
]
FCR31_C = 1 << 23
FCR31_STICKY = 0x78          # SI SD SO SU (bits 6..3)
FCR31_CAUSE = 0x3C000        # I D O U (bits 17..14)


def fpu_vec(op, fs=0, ft=0, acc=0, fcr31=0, fd=0xDEADBEEF, form=None, note=""):
    inputs = {"fs": u32(fs), "ft": u32(ft), "acc": u32(acc), "fcr31": u32(fcr31), "fd": u32(fd)}
    return add(Vec("fpu", op, inputs, [q64(u32(fs)), q64(u32(ft)), q64(u32(acc)), q64(u32(fcr31)), q64(u32(fd))],
                   form=form, note=note))


def gen_fpu():
    for a, b in FPU_ADD_PAIRS:
        fpu_vec("add.s", fv(a), fv(b))
        fpu_vec("sub.s", fv(a), fv(b))
    for a, b in FPU_MUL_PAIRS:
        fpu_vec("mul.s", fv(a), fv(b))
    for a, b in FPU_DIV_PAIRS:
        fpu_vec("div.s", fv(a), fv(b))
    for a in FPU_SQRT:
        fpu_vec("sqrt.s", 0, fv(a))
    for a, b in FPU_RSQRT_PAIRS:
        fpu_vec("rsqrt.s", fv(a), fv(b))
    for op in ("abs.s", "neg.s", "mov.s"):
        for a in FPU_UNARY:
            fpu_vec(op, fv(a))
    for acc, a, b in FPU_MADD:
        for op in ("madd.s", "msub.s", "madda.s", "msuba.s"):
            fpu_vec(op, fv(a), fv(b), acc=fv(acc))
    for a, b in FPU_ADD_PAIRS[:16] + FPU_MUL_PAIRS[:12]:
        fpu_vec("adda.s", fv(a), fv(b), acc=F["7.0"])
        fpu_vec("suba.s", fv(a), fv(b), acc=F["7.0"])
        fpu_vec("mula.s", fv(a), fv(b), acc=F["7.0"])
    for a, b in FPU_MAXMIN_PAIRS:
        fpu_vec("max.s", fv(a), fv(b))
        fpu_vec("min.s", fv(a), fv(b))
    for a in FPU_CVT_W:
        fpu_vec("cvt.w.s", fv(a))
    for a in FPU_CVT_S:
        fpu_vec("cvt.s.w", a)
    for a, b in FPU_CMP_PAIRS:
        for op in ("c.eq.s", "c.lt.s", "c.le.s"):
            fpu_vec(op, fv(a), fv(b))
            fpu_vec(op, fv(a), fv(b), fcr31=FCR31_C)      # condition set beforehand: must be cleared on false
    fpu_vec("c.f.s", F["1.0"], F["2.0"], fcr31=FCR31_C)
    fpu_vec("c.f.s", F["1.0"], F["2.0"])
    # FCR31 flag behaviour: cause bits, sticky bits, what a later operation clears, what CTC1 accepts
    for pre in (0, FCR31_STICKY, FCR31_CAUSE, FCR31_C | FCR31_STICKY | FCR31_CAUSE, 0x00830000):
        fpu_vec("div.s", F["1.0"], F["+0"], fcr31=pre)
        fpu_vec("div.s", F["+0"], F["+0"], fcr31=pre)
        fpu_vec("div.s", F["1.0"], F["2.0"], fcr31=pre)
        fpu_vec("rsqrt.s", F["1.0"], F["+0"], fcr31=pre)
        fpu_vec("rsqrt.s", F["1.0"], F["-4.0"], fcr31=pre)
        fpu_vec("sqrt.s", 0, F["-4.0"], fcr31=pre)
        fpu_vec("add.s", F["1.0"], F["1.0"], fcr31=pre)
        fpu_vec("add.s", F["fltmax"], F["fltmax"], fcr31=pre)      # overflow: O/SO?
        fpu_vec("mul.s", F["2^-100"], F["2^-100"], fcr31=pre)      # underflow: U/SU?
        fpu_vec("mul.s", F["fltmax"], F["fltmax"], fcr31=pre)
        fpu_vec("cvt.w.s", F["2^32"], fcr31=pre)                   # invalid conversion?
        fpu_vec("c.eq.s", F["1.0"], F["1.0"], fcr31=pre)
    for pattern in (0xFFFFFFFF, 0x00800000, 0x0083C078, 0x01000000, 0x00000007, 0xFF7FFFFF):
        fpu_vec("ctc1", 0, 0, fcr31=pattern, form={"probe": "ctc1"})   # fcr31_in is written, then read back
    fpu_vec("cfc1.fcr0", 0, 0)
    # mfc1 sign extension / mtc1 of a 64-bit GPR (low word)
    for a in ("eemax", "-eemax", "-0", "1.0"):
        fpu_vec("mov.s", fv(a))


# ------------------------------------------------------------------------------------------------------------
# VU0 macro mode (COP2)
# ------------------------------------------------------------------------------------------------------------
def v4(*names):
    assert len(names) == 4
    return q32(*(fv(n) for n in names))


VU_SETS = [   # (fs, ft)
    (v4("1.0", "2.0", "3.0", "4.0"), v4("4.0", "3.0", "2.0", "1.0")),
    (v4("+0", "-0", "den", "-den"), v4("-0", "-0", "-den", "den")),
    (v4("fltmax", "eemax", "-fltmax", "-eemax"), v4("fltmax", "eemax", "fltmax", "eemax")),
    (v4("1.0", "1.0", "1.0", "1.0"), v4("1.5ulp", "2^-24", "2^-26", "2^-100")),
    (v4("qnan", "inf", "1+ulp", "2^24"), v4("1.0", "1.0", "1+ulp", "1.0")),
    (v4("-1.0", "-2.0", "2.0", "-0"), v4("1.0", "2.0", "-2.0", "+0")),
    (v4("2^-100", "minnorm", "2^126", "pi"), v4("2^-100", "0.5", "2.0", "0.1")),
    (v4("1/3", "2/3", "0.1", "1000.0"), v4("3.0", "1.5", "10.0", "0.1")),
    (v4("+0", "+0", "-0", "-0"), v4("+0", "-0", "+0", "-0")),
    (v4("2^31", "-2^31", "2^31-128", "2^32"), v4("1.0", "1.0", "1.0", "1.0")),
    (v4("1.5", "-1.5", "100.5", "-100.5"), v4("0.5", "-0.5", "3.99", "0.1")),
    (v4("2^63", "-2^63", "2^64", "-fltmax"), v4("2^63", "2^63", "2^64", "fltmax")),
]
FD_SENTINEL = v4("0x3F000001", "0x3F000001", "0x3F000001", "0x3F000001")
ACC_SETS = [v4("+0", "+0", "+0", "+0"), v4("1.0", "2.0", "3.0", "4.0"), v4("-6.0", "6.0", "fltmax", "-fltmax"),
            v4("1.0", "1.0", "1.0", "1.0"), v4("eemax", "-eemax", "2^24", "2^-100")]
DESTS = ["xyzw", "xyz", "w", "x", "zw", "xy", "y", "z"]


def dest_mask(d):
    return (8 if "x" in d else 0) | (4 if "y" in d else 0) | (2 if "z" in d else 0) | (1 if "w" in d else 0)


def vu_vec(op, fs=0, ft=0, fd=FD_SENTINEL, acc=0, i=0, q=0, status=0, mac=0, clip=0, form=None, note="", vi=None):
    inputs = {"fs": fs, "ft": ft, "fd": fd, "acc": acc, "i": u32(i), "q": u32(q), "status": u32(status),
              "mac": u32(mac), "clip": u32(clip)}
    if vi:
        inputs["vi1"], inputs["vi2"] = vi
    data = [fs, ft, fd, acc, q32(i, q, status, mac), q32(clip, vi[0] if vi else 0, vi[1] if vi else 0, 0)]
    return add(Vec("vu0", op, inputs, data, form=form, note=note))


def gen_vu0():
    for base in ("vadd", "vsub", "vmul", "vmadd", "vmsub", "vmax", "vmini"):
        for k, (fs, ft) in enumerate(VU_SETS):
            d = DESTS[k % len(DESTS)]
            vu_vec("%s.%s" % (base, d), fs, ft, acc=ACC_SETS[k % len(ACC_SETS)], form={"dest": dest_mask(d)})
            if k < 4:
                vu_vec("%s.xyzw" % base, fs, ft, acc=ACC_SETS[1], form={"dest": 15})
        for bc in "xyzw":
            for k in (0, 2, 3, 5):
                fs, ft = VU_SETS[k]
                vu_vec("%s%s.xyzw" % (base, bc), fs, ft, acc=ACC_SETS[1], form={"dest": 15, "bc": "xyzw".index(bc)})
        for k in (0, 3, 5, 9):
            fs, ft = VU_SETS[k]
            if base not in ("vmax", "vmini"):   # VMAX/VMINI have no Q form on the EE
                vu_vec("%sq.xyzw" % base, fs, ft, acc=ACC_SETS[1], q=F["0.5"] if k != 9 else F["2^-24"], form={"dest": 15})
            vu_vec("%si.xyz" % base, fs, ft, acc=ACC_SETS[1], i=F["3.0"] if k != 9 else F["-0"], form={"dest": 14})
    for base in ("vadda", "vsuba", "vmula", "vmadda", "vmsuba"):
        for k in (0, 1, 2, 3, 4, 5, 6, 9):
            fs, ft = VU_SETS[k]
            d = DESTS[k % len(DESTS)]
            vu_vec("%s.%s" % (base, d), fs, ft, acc=ACC_SETS[k % len(ACC_SETS)], form={"dest": dest_mask(d)})
        for bc in "xyzw":
            fs, ft = VU_SETS["xyzw".index(bc)]
            vu_vec("%s%s.xyzw" % (base, bc), fs, ft, acc=ACC_SETS[1], form={"dest": 15, "bc": "xyzw".index(bc)})
        vu_vec("%sq.xyzw" % base, VU_SETS[0][0], VU_SETS[0][1], acc=ACC_SETS[1], q=F["0.5"], form={"dest": 15})
        vu_vec("%si.w" % base, VU_SETS[0][0], VU_SETS[0][1], acc=ACC_SETS[1], i=F["-2.0"], form={"dest": 1})
    for k in (0, 2, 4, 5, 7, 11):
        fs, ft = VU_SETS[k]
        vu_vec("vopmula.xyz", fs, ft, acc=ACC_SETS[1], form={"dest": 14})
        vu_vec("vopmsub.xyz", fs, ft, acc=ACC_SETS[k % len(ACC_SETS)], form={"dest": 14})
    for op in ("vabs", "vmove", "vmr32"):
        for k in (1, 2, 4, 5):
            fs, ft = VU_SETS[k]
            d = DESTS[k % len(DESTS)]
            vu_vec("%s.%s" % (op, d), fs, ft, form={"dest": dest_mask(d)})
            vu_vec("%s.xyzw" % op, fs, ft, form={"dest": 15})
    for frac in (0, 4, 12, 15):
        for k in (0, 1, 2, 4, 9, 10, 11, 7, 3):
            fs, ft = VU_SETS[k]
            vu_vec("vftoi%d.xyzw" % frac, fs, ft, form={"dest": 15, "frac": frac})
        for ints in (q32(2, 16, 4096, u32(-32768)), q32(0x7FFFFFFF, 0x80000000, 0x00FFFFFF, 0x01000001),
                     q32(0, u32(-1), 1, 0x12345678), q32(0x01000003, 0xFEFFFFFD, 0x7FFFFFC0, 0x7FFFFF80),
                     q32(0x8000, 0xFFFF8000, 0x1000, 0xFFFFF000)):
            vu_vec("vitof%d.xyzw" % frac, ints, 0, form={"dest": 15, "frac": frac})
    for fs, ft in ((v4("2.0", "-2.0", "0.5", "+0"), v4("+0", "+0", "+0", "1.0")),
                   (v4("2.0", "-2.0", "0.5", "+0"), v4("+0", "+0", "+0", "-1.0")),
                   (v4("1.0", "1.0", "1.0", "+0"), v4("+0", "+0", "+0", "1.0")),
                   (v4("1+ulp", "-1+ulp", "1-ulp", "+0"), v4("+0", "+0", "+0", "1.0")),
                   (v4("den", "-den", "+0", "+0"), v4("+0", "+0", "+0", "+0")),
                   (v4("eemax", "-eemax", "fltmax", "+0"), v4("+0", "+0", "+0", "fltmax"))):
        for clip_pre in (0, 0xFFFFFF, 0x249249):
            vu_vec("vclipw.xyz", fs, ft, clip=clip_pre)
    # Q pipe: vdiv/vsqrt/vrsqrt with component selectors; Q read after vwaitq (the game's pattern)
    QS = [
        (v4("1.0", "4.0", "9.0", "16.0"), v4("-4.0", "+0", "2.0", "-0")),
        (v4("1.0", "2.0", "3.0", "20.0"), v4("3.0", "-3.0", "7.0", "0.1")),
        (v4("+0", "-0", "den", "-den"), v4("+0", "-0", "den", "2.0")),
        (v4("fltmax", "eemax", "minnorm", "2^-100"), v4("minnorm", "fltmax", "eemax", "2^-100")),
        (v4("qnan", "inf", "1+ulp", "2-ulp"), v4("1.0", "-1.0", "1+ulp", "1-ulp")),
    ]
    for fs, ft in QS:
        for fsf, ftf in ((0, 0), (0, 1), (1, 2), (2, 3), (3, 0), (3, 3), (1, 1), (2, 0)):
            vu_vec("vdiv", fs, ft, q=F["7.0"], form={"fsf": fsf, "ftf": ftf, "wait": True})
            vu_vec("vrsqrt", fs, ft, q=F["7.0"], form={"fsf": fsf, "ftf": ftf, "wait": True})
        for ftf in range(4):
            vu_vec("vsqrt", fs, ft, q=F["7.0"], form={"ftf": ftf, "wait": True})
    # the same without vwaitq, and with the sticky status bits set beforehand
    for fs, ft in QS[:2]:
        vu_vec("vdiv", fs, ft, q=F["7.0"], form={"fsf": 0, "ftf": 1, "wait": False})
        vu_vec("vdiv", fs, ft, q=F["7.0"], status=0xFC0, form={"fsf": 0, "ftf": 1, "wait": True})
        vu_vec("vdiv", fs, ft, q=F["7.0"], status=0x030, form={"fsf": 0, "ftf": 2, "wait": True})
        vu_vec("vrsqrt", fs, ft, q=F["7.0"], status=0xFC0, form={"fsf": 0, "ftf": 1, "wait": True})
        vu_vec("vsqrt", fs, ft, q=F["7.0"], status=0xFC0, form={"ftf": 0, "wait": True})
    # vwaitq / vnop
    vu_vec("vwaitq", VU_SETS[0][0], VU_SETS[0][1], q=F["0.5"], status=0x20)
    vu_vec("vnop", VU_SETS[0][0], VU_SETS[0][1], q=F["0.5"], status=0x20)
    # integer unit
    for op, (a, b, imm) in (("viadd", (0xFFFF, 1, 0)), ("viadd", (0x1234, 0x4321, 0)), ("visub", (1, 0xFFFF, 0)),
                            ("viand", (0xFFFF, 0x0F0F, 0)), ("vior", (1, 0x0F0F, 0)), ("viaddi", (0xFFFF, 0, -1)),
                            ("viaddi", (0x0F0F, 0, 15)), ("viaddi", (0, 0, -16)), ("visub", (0x8000, 0x8001, 0))):
        vu_vec(op, 0, 0, vi=(a, b), form={"imm": imm})
    vu_vec("vmfir.xyzw", 0, 0, vi=(0x8000, 0x1234), form={"dest": 15})
    # control-register write masks: ctc2 value then cfc2
    for reg, val in ((16, 0xFFFFFFFF), (16, 0x00000FFF), (16, 0x0000003F), (17, 0xFFFFFFFF), (17, 0x0000FFFF),
                     (18, 0xFFFFFFFF), (20, 0xFFFFFFFF), (20, 0x007FFFFF), (21, 0xFFFFFFFF), (22, 0xFFFFFFFF),
                     (26, 0xFFFFFFFF), (27, 0xFFFFFFFF), (27, 0x0000FFFF), (28, 0), (29, 0), (31, 0), (1, 0x12345678)):
        vu_vec("ctc2", 0, 0, form={"reg": reg, "val": val})
    # macro-mode flags after arithmetic: every arithmetic vector records STATUS/MAC pre and post already;
    # add sticky-bit carriers: STATUS preset with sticky bits, then an op producing zero/sign/overflow results
    for st in (0x000, 0xFC0, 0x03F):
        vu_vec("vadd.xyzw", v4("1.0", "-1.0", "fltmax", "+0"), v4("-1.0", "+0", "fltmax", "+0"), status=st, mac=0xFFFF, form={"dest": 15})
        vu_vec("vmul.xyzw", v4("2^-100", "-1.0", "fltmax", "2.0"), v4("2^-100", "1.0", "fltmax", "3.0"), status=st, mac=0xFFFF, form={"dest": 15})
        vu_vec("vmove.xyzw", v4("+0", "-1.0", "eemax", "2.0"), 0, status=st, mac=0xFFFF, form={"dest": 15})
        vu_vec("vabs.xyzw", v4("+0", "-1.0", "-eemax", "2.0"), 0, status=st, mac=0xFFFF, form={"dest": 15})
        vu_vec("vftoi0.xyzw", v4("+0", "-1.0", "eemax", "2.0"), 0, status=st, mac=0xFFFF, form={"dest": 15, "frac": 0})
        vu_vec("vadd.x", v4("1.0", "-1.0", "fltmax", "+0"), v4("-1.0", "+0", "fltmax", "+0"), status=st, mac=0xFFFF, form={"dest": 8})


# ------------------------------------------------------------------------------------------------------------
# Integer core: unaligned loads/stores, lq/sq, 32-bit ALU on 64-bit register images
# ------------------------------------------------------------------------------------------------------------
MEM_IMAGE = (q8(*range(0x00, 0x10)), q8(*range(0x10, 0x20)))
RT_PRESETS = [0xAAAAAAAA55555555, 0x0000000080000000, 0xFFFFFFFF7FFFFFFF, 0x1234567800000000]


def core_mem(op, off, rt, note=""):
    return add(Vec("core", op, {"mem0": MEM_IMAGE[0], "mem1": MEM_IMAGE[1], "rt": rt}, [MEM_IMAGE[0], MEM_IMAGE[1], q64(rt)],
                   form={"off": off}, note=note))


def core_alu(op, rs, rt, imm=None, risky=False):
    inputs = {"rs": rs, "rt": rt}
    f = {}
    if imm is not None:
        f["imm"] = imm
    return add(Vec("core", op, inputs, [q64(rs), q64(rt)], form=f, risky=risky))


def gen_core():
    for op, n in (("lwl", 4), ("lwr", 4), ("ldl", 8), ("ldr", 8)):
        for off in range(n):
            for rt in RT_PRESETS[:3]:
                core_mem(op, off, rt)
    for op, n in (("swl", 4), ("swr", 4), ("sdl", 8), ("sdr", 8)):
        for off in range(n):
            core_mem(op, off, 0xA1B2C3D4E5F60718)
    for op in ("lb", "lbu", "lh", "lhu", "lw", "lwu", "ld"):
        core_mem(op, 8, 0xAAAAAAAA55555555)
    PAIRS = [(0x0000000000000007, 0x0000000000000002), (0x000000017FFFFFFF, 0x0000000000000001),
             (0xFFFFFFFF80000000, 0xFFFFFFFFFFFFFFFF), (0x00000000FFFFFFFF, 0x0000000000000001),
             (0x8000000000000000, 0x0000000000000001), (0x123456789ABCDEF0, 0x0FEDCBA987654321),
             (0x0000000080000000, 0x0000000080000000), (0xFFFFFFFFFFFFFFFF, 0x00000000FFFFFFFF),
             (0x00000000FFFFFFFF, 0x00000000FFFFFFFF), (0x7FFFFFFFFFFFFFFF, 0x0000000000000001)]
    for op in ("addu", "subu", "and", "or", "xor", "nor", "slt", "sltu", "daddu", "dsubu", "sllv", "srlv", "srav",
               "dsllv", "dsrlv", "dsrav", "movn", "movz", "mult", "multu", "div", "divu"):
        for rs, rt in PAIRS:
            core_alu(op, rs, rt)
    for op in ("sll", "srl", "sra", "dsll", "dsrl", "dsra", "dsll32", "dsrl32", "dsra32"):
        for sa in (0, 1, 31):
            for rs, rt in PAIRS[1:4] + [PAIRS[5]]:
                core_alu(op, rs, rt, imm=sa)
    for op in ("addiu", "daddiu", "slti", "sltiu", "andi", "ori", "xori"):
        for imm in (-1, 1, -32768, 32767):
            for rs, rt in PAIRS[1:4] + [PAIRS[5]]:
                core_alu(op, rs, rt, imm=imm)
    for imm in (-1, 1, 0x7FFF, -32768):
        core_alu("lui", 0, 0, imm=imm)
    # ADD/SUB/ADDI integer overflow: traps on hardware (Integer Overflow exception); risky tail
    core_alu("add", 0x000000007FFFFFFF, 0x0000000000000001, risky=True)
    core_alu("sub", 0xFFFFFFFF80000000, 0x0000000000000001, risky=True)
    core_alu("addi", 0x000000007FFFFFFF, 0, imm=1, risky=True)
    core_alu("add", 0x0000000000000003, 0x0000000000000004, risky=True)
    core_alu("dadd", 0x7FFFFFFFFFFFFFFF, 0x0000000000000001, risky=True)


# ------------------------------------------------------------------------------------------------------------
# Assembly emission
# ------------------------------------------------------------------------------------------------------------
def emit_qw_data(lines, label, qws):
    lines.append("%s:" % label)
    for qw in qws:
        words = [(qw >> (32 * i)) & M32 for i in range(4)]
        lines.append("        .word 0x%08X, 0x%08X, 0x%08X, 0x%08X" % tuple(words))
    while len(qws) < 6:
        lines.append("        .word 0, 0, 0, 0")
        qws = qws + [0]


def slot_addr(i):
    return RESULTS_BASE + HEADER_BYTES + i * SLOT_BYTES


def asm_load_addr(reg, addr):
    hi = (addr >> 16) & 0xFFFF
    lo = addr & 0xFFFF
    return ["        lui   $%d, 0x%04X" % (reg, hi), "        ori   $%d, $%d, 0x%04X" % (reg, reg, lo)]


def std_epilogue(i, rd_reg=10, store_hilo=True):
    """Store rd / HI / LO / x0..x3 ($12..$15) / x4..x7 ($17,$18,$19,$21) and bump the progress word."""
    out = ["        sq    $%d, 0($16)" % rd_reg]
    if store_hilo:
        out += ["        pmfhi $11", "        sq    $11, 16($16)", "        pmflo $11", "        sq    $11, 32($16)"]
    out += ["        sw    $12, 48($16)", "        sw    $13, 52($16)", "        sw    $14, 56($16)", "        sw    $15, 60($16)",
            "        sw    $17, 64($16)", "        sw    $18, 68($16)", "        sw    $19, 72($16)", "        sw    $21, 76($16)"]
    out += asm_load_addr(1, RESULTS_BASE)
    out += ["        ori   $11, $0, 0x%04X" % ((i + 1) & 0xFFFF)]
    if (i + 1) > 0xFFFF:
        raise SystemExit("too many vectors for the progress word")
    out += ["        sw    $11, 8($1)"]
    return out


def clear_temps():
    return ["        or    $%d, $0, $0" % r for r in (12, 13, 14, 15, 17, 18, 19, 21)]


def emit_hilo(i, v):
    out = clear_temps()
    out += ["        ld    $8, 0($1)", "        ld    $9, 16($1)", "        lq    $11, 32($1)", "        pmthi $11",
            "        lq    $11, 48($1)", "        pmtlo $11", "        lq    $10, 64($1)"]
    op = v.op
    if op.startswith("mthi") or op.startswith("mtlo"):
        out.append("        %s $8" % op)
    elif op.startswith("div"):
        out.append("        %s $zero, $8, $9" % op)
    elif v.form.get("rd"):
        out.append("        %s $10, $8, $9" % op)
    else:
        out.append("        %s $8, $9" % op)
    out.append("        mfsa  $12")
    return out + std_epilogue(i)


def emit_mmi(i, v):
    out = clear_temps()
    out += ["        lq    $8, 0($1)", "        lq    $9, 16($1)", "        lq    $11, 32($1)", "        pmthi $11",
            "        lq    $11, 48($1)", "        pmtlo $11", "        lq    $10, 64($1)", "        ld    $13, 80($1)",
            "        mtsa  $0"]
    op = v.op
    f = v.form
    if op == "qfsrv":
        if f["sa_form"] == "mtsab":
            out.append("        mtsab $13, %d" % f["sa_imm"])
        elif f["sa_form"] == "mtsah":
            out.append("        mtsah $13, %d" % f["sa_imm"])
        else:
            out.append("        mtsa  $13")
        out.append("        qfsrv $10, $8, $9")
    elif op in MMI_BIN or op in MMI_VSHIFT or op in ("pmultw", "pmultuw", "pmaddw", "pmsubw", "pmadduw", "pmulth",
                                                      "pmaddh", "pmsubh", "phmadh", "phmsbh"):
        out.append("        %s $10, $8, $9" % op)
    elif op in MMI_UN:
        out.append("        %s $10, $9" % op)
    elif op in MMI_SHIFT:
        out.append("        %s $10, $9, %d" % (op, f["sa"]))
    elif op == "plzcw":
        out.append("        plzcw $10, $8")
    elif op.startswith("pmfhl."):
        if op == "pmfhl.raw":
            out.append("        .word 0x%08X" % (0x70000030 | (10 << 11) | (f["fmt"] << 6)))
        else:
            out.append("        %s $10" % op)
    elif op == "pmthl.lw":
        out.append("        pmthl.lw $8")
    elif op in ("pmfhi", "pmflo"):
        out.append("        %s $10" % op)
    elif op in ("pmthi", "pmtlo"):
        out.append("        %s $8" % op)
    elif op in ("pdivw", "pdivuw", "pdivbw"):
        out.append("        %s $8, $9" % op)
    elif op == "lq":
        out += asm_load_addr(20, SCRATCH_BASE)
        out += ["        sq    $8, 0($20)", "        sq    $9, 16($20)", "        lq    $10, %d($20)" % f["off"]]
    elif op == "sq":
        out += asm_load_addr(20, SCRATCH_BASE)
        out += ["        sq    $0, 0($20)", "        sq    $0, 16($20)", "        sq    $8, %d($20)" % f["off"],
                "        lq    $10, 0($20)", "        lq    $11, 16($20)", "        sq    $11, 80($16)"]
    else:
        raise SystemExit("unhandled mmi op " + op)
    out.append("        mfsa  $12")
    return out + std_epilogue(i)


def emit_fpu(i, v):
    out = clear_temps()
    out += ["        lw    $8, 0($1)", "        mtc1  $8, $f1", "        lw    $9, 16($1)", "        mtc1  $9, $f2",
            "        lw    $11, 32($1)", "        mtc1  $11, $f3", "        mtc1  $0, $f4", "        adda.s $f3, $f4",
            "        lw    $11, 48($1)", "        ctc1  $11, $31", "        lw    $11, 64($1)", "        mtc1  $11, $f5",
            "        cfc1  $13, $31"]
    op = v.op
    if op in ("add.s", "sub.s", "mul.s", "div.s", "madd.s", "msub.s", "max.s", "min.s"):
        out.append("        %s $f5, $f1, $f2" % op)
    elif op == "sqrt.s":
        out.append("        sqrt.s $f5, $f2")
    elif op == "rsqrt.s":
        out.append("        rsqrt.s $f5, $f1, $f2")
    elif op in ("abs.s", "neg.s", "mov.s", "cvt.w.s", "cvt.s.w"):
        out.append("        %s $f5, $f1" % op)
    elif op in ("adda.s", "suba.s", "mula.s", "madda.s", "msuba.s"):
        out.append("        %s $f1, $f2" % op)
    elif op in ("c.eq.s", "c.lt.s", "c.le.s", "c.f.s"):
        out.append("        %s $f1, $f2" % op)
    elif op == "ctc1":
        pass   # the preset ctc1 above is the operation
    elif op == "cfc1.fcr0":
        pass
    else:
        raise SystemExit("unhandled fpu op " + op)
    out += ["        cfc1  $12, $31", "        cfc1  $14, $0", "        mfc1  $10, $f5", "        pcpyld $10, $0, $10",
            "        mtc1  $0, $f6", "        madd.s $f7, $f6, $f6", "        mfc1  $11, $f7", "        pcpyld $11, $0, $11",
            "        sq    $11, 16($16)"]
    return out + std_epilogue(i, store_hilo=False) + ["        swc1  $f5, 60($16)"]


def emit_vu0(i, v):
    out = clear_temps()
    out += ["        lq    $8, 0($1)", "        qmtc2 $8, $vf1", "        lq    $9, 16($1)", "        qmtc2 $9, $vf2",
            "        lq    $10, 32($1)", "        qmtc2 $10, $vf3", "        lq    $11, 48($1)", "        qmtc2 $11, $vf4",
            "        vaddax.xyzw $ACC, $vf4, $vf0",
            "        lw    $11, 64($1)", "        ctc2  $11, $vi21", "        lw    $11, 68($1)", "        ctc2  $11, $vi22",
            "        lw    $11, 72($1)", "        ctc2  $11, $vi16", "        lw    $11, 76($1)", "        ctc2  $11, $vi17",
            "        lw    $11, 80($1)", "        ctc2  $11, $vi18", "        lw    $11, 84($1)", "        ctc2  $11, $vi1",
            "        lw    $11, 88($1)", "        ctc2  $11, $vi2",
            "        cfc2  $12, $vi16", "        cfc2  $13, $vi17", "        cfc2  $14, $vi18", "        cfc2  $15, $vi22"]
    op = v.op
    f = v.form
    base, _, dest = op.partition(".")
    if base in ("vdiv", "vrsqrt"):
        out.append("        %s $Q, $vf1%s, $vf2%s" % (base, "xyzw"[f["fsf"]], "xyzw"[f["ftf"]]))
        if f["wait"]:
            out.append("        vwaitq")
    elif base == "vsqrt":
        out.append("        vsqrt $Q, $vf2%s" % "xyzw"[f["ftf"]])
        if f["wait"]:
            out.append("        vwaitq")
    elif base in ("vwaitq", "vnop"):
        out.append("        %s" % base)
    elif base in ("viadd", "visub", "viand", "vior"):
        out.append("        %s $vi3, $vi1, $vi2" % base)
    elif base == "viaddi":
        out.append("        viaddi $vi3, $vi1, %d" % f["imm"])
    elif base == "vmfir":
        out.append("        vmfir.xyzw $vf3, $vi1")
    elif base == "ctc2":
        out += asm_load_addr(11, f["val"])
        out.append("        ctc2  $11, $vi%d" % f["reg"])
        out.append("        cfc2  $17, $vi%d" % f["reg"])
    elif base == "vclipw":
        out.append("        vclipw.xyz $vf1, $vf2")
    elif base in ("vopmula",):
        out.append("        vopmula.xyz $ACC, $vf1, $vf2")
    elif base == "vopmsub":
        out.append("        vopmsub.xyz $vf3, $vf1, $vf2")
    elif base in ("vabs", "vmove", "vmr32") or base.startswith("vftoi") or base.startswith("vitof"):
        out.append("        %s.%s $vf3, $vf1" % (base, dest))
    else:
        # vector ALU: v<op>[bc|q|i].<dest>; ACC roots first since "vadda" starts with "vadd"
        for root in ("vmadda", "vmsuba", "vadda", "vsuba", "vmula", "vmadd", "vmsub", "vmini", "vadd", "vsub", "vmul", "vmax"):
            if base.startswith(root) and base[len(root):] in ("", "x", "y", "z", "w", "q", "i"):
                sfx = base[len(root):]
                dst = "$ACC" if root in ("vmadda", "vmsuba", "vadda", "vsuba", "vmula") else "$vf3"
                if sfx == "":
                    out.append("        %s.%s %s, $vf1, $vf2" % (base, dest, dst))
                elif sfx == "q":
                    out.append("        %s.%s %s, $vf1, $Q" % (base, dest, dst))
                elif sfx == "i":
                    out.append("        %s.%s %s, $vf1, $I" % (base, dest, dst))
                else:
                    out.append("        %s.%s %s, $vf1, $vf2%s" % (base, dest, dst, sfx))
                break
        else:
            raise SystemExit("unhandled vu0 op " + op)
    if base in ("ctc2",):
        out += ["        cfc2  $18, $vi16", "        cfc2  $19, $vi17", "        cfc2  $21, $vi18"]
    else:
        out += ["        cfc2  $17, $vi16", "        cfc2  $18, $vi17", "        cfc2  $19, $vi18", "        cfc2  $21, $vi22"]
    if base in ("viadd", "visub", "viand", "vior", "viaddi"):
        out += ["        cfc2  $10, $vi3", "        pcpyld $10, $0, $10"]
    else:
        out += ["        qmfc2 $10, $vf3"]
    out += ["        vmaddx.xyzw $vf5, $vf0, $vf0", "        qmfc2 $11, $vf5"]
    out += ["        sq    $11, 16($16)", "        qmfc2 $11, $vf1", "        sq    $11, 32($16)",
            "        qmfc2 $11, $vf2", "        sq    $11, 80($16)"]
    return out + std_epilogue(i, store_hilo=False)


def emit_core(i, v):
    out = clear_temps()
    op = v.op
    f = v.form
    if "mem0" in v.inputs:
        out += asm_load_addr(20, SCRATCH_BASE)
        out += ["        lq    $11, 0($1)", "        sq    $11, 0($20)", "        lq    $11, 16($1)", "        sq    $11, 16($20)",
                "        ld    $10, 32($1)", "        pcpyld $10, $0, $10",
                "        %s $10, %d($20)" % (op, f["off"])]
        if op in ("lwl", "lwr", "ldl", "ldr", "lb", "lbu", "lh", "lhu", "lw", "lwu", "ld"):
            out.append("        pcpyld $10, $0, $10")
        out += ["        lq    $11, 0($20)", "        sq    $11, 16($16)", "        lq    $11, 16($20)", "        sq    $11, 32($16)"]
        return out + std_epilogue(i, store_hilo=False)
    out += ["        ld    $8, 0($1)", "        ld    $9, 16($1)", "        lq    $11, 32($1)", "        pmthi $11", "        pmtlo $11",
            "        or    $10, $0, $0"]   # rd preset 0 so a not-taken MOVN/MOVZ is observable
    if op in ("mult", "multu"):
        out.append("        %s $10, $8, $9" % op)
    elif op in ("div", "divu"):
        out += ["        %s $zero, $8, $9" % op, "        or    $10, $0, $0"]
    elif op in ("sll", "srl", "sra", "dsll", "dsrl", "dsra", "dsll32", "dsrl32", "dsra32"):
        out.append("        %s $10, $9, %d" % (op, f["imm"]))
    elif op in ("addiu", "daddiu", "slti", "sltiu", "andi", "ori", "xori", "addi"):
        out.append("        %s $10, $8, %d" % (op, f["imm"] & 0xFFFF if op in ("andi", "ori", "xori") else f["imm"]))
    elif op == "lui":
        out.append("        lui   $10, %d" % (f["imm"] & 0xFFFF))
    else:
        out.append("        %s $10, $8, $9" % op)
    out.append("        pcpyld $10, $0, $10")
    return out + std_epilogue(i, store_hilo=True)


EMITTERS = {"hilo": emit_hilo, "mmi": emit_mmi, "fpu": emit_fpu, "vu0": emit_vu0, "core": emit_core}


def generate(out_dir):
    gen_core()
    gen_hilo()
    gen_mmi()
    gen_fpu()
    gen_vu0()
    # risky vectors go last so a trap cannot hide earlier results
    safe = [v for v in VECTORS if not v.risky]
    risky = [v for v in VECTORS if v.risky]
    ordered = safe + risky
    lines = ["# generated by tools/ours/eevec/gen_vectors.py v%s -- do not edit" % GENERATOR_VERSION,
             "        .set noreorder", "        .set noat", "        .set nomacro", "        .text", "        .globl _start",
             "_start:", "        lui   $29, 0x01FF", "        ori   $29, $29, 0xFF00", "        or    $28, $0, $0"]
    lines += asm_load_addr(1, RESULTS_BASE)
    lines += ["        sw    $0, 0($1)", "        sw    $0, 4($1)", "        sw    $0, 8($1)", "        sw    $0, 12($1)"]
    # vf0 sanity: nothing to do (hardware constant)
    data = []
    layout = []
    for i, v in enumerate(ordered):
        label = "v%d_in" % i
        lines.append("# vector %d: %s %s %s" % (i, v.family, v.op, json.dumps(v.form) if v.form else ""))
        lines += ["        lui   $1, %%hi(%s)" % label, "        addiu $1, $1, %%lo(%s)" % label]
        lines += asm_load_addr(16, slot_addr(i))
        lines += EMITTERS[v.family](i, v)
        if i == len(safe) - 1:
            lines += asm_load_addr(1, RESULTS_BASE)
            lines += ["        ori   $11, $0, 0x%04X" % len(ordered), "        sw    $11, 4($1)", "        sync.l"]
            lines += asm_load_addr(11, MAGIC)
            lines += ["        sw    $11, 0($1)", "        sync.l"]
        data.append((label, list(v.data)))
        layout.append({"index": i, "family": v.family, "op": v.op, "form": v.form, "risky": v.risky, "note": v.note,
                       "slot": slot_addr(i), "in": {k: fmt_in(v.family, k, x) for k, x in v.inputs.items()}})
    lines += asm_load_addr(1, RESULTS_BASE)
    lines += asm_load_addr(11, TAIL_MAGIC)
    lines += ["        sw    $11, 12($1)", "        sync.l", "end_loop:", "        j     end_loop", "        nop"]
    lines += ["        .data", "        .align 4"]
    for label, qws in data:
        emit_qw_data(lines, label, qws)
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "eevec.s").write_text("\n".join(lines) + "\n", encoding="utf-8")
    fam = {}
    for v in ordered:
        fam[v.family] = fam.get(v.family, 0) + 1
    meta = {"generator": "tools/ours/eevec/gen_vectors.py", "generator_version": GENERATOR_VERSION,
            "results_base": hex32(RESULTS_BASE), "scratch_base": hex32(SCRATCH_BASE), "slot_bytes": SLOT_BYTES,
            "header_bytes": HEADER_BYTES, "magic": hex32(MAGIC), "tail_magic": hex32(TAIL_MAGIC),
            "count": len(ordered), "safe_count": len(safe), "families": fam}
    (out_dir / "layout.json").write_text(json.dumps({"meta": meta, "vectors": layout}, indent=1), encoding="utf-8")
    return meta


WIDTHS = {
    "hilo": {"rs": 64, "rt": 64, "hi": 128, "lo": 128, "rd": 128},
    "mmi": {"rs": 128, "rt": 128, "hi": 128, "lo": 128, "rd": 128, "sa_rs": 64},
    "fpu": {},
    "vu0": {"fs": 128, "ft": 128, "fd": 128, "acc": 128},
    "core": {"mem0": 128, "mem1": 128, "rs": 64, "rt": 64},
}


def fmt_in(family, key, x):
    w = WIDTHS[family].get(key, 32)
    return {32: hex32, 64: hex64, 128: hex128}[w](x)


def build(out_dir, toolchain):
    tc = pathlib.Path(toolchain)
    asm = tc / "mips64r5900el-ps2-elf-as.exe"
    ld = tc / "mips64r5900el-ps2-elf-ld.exe"
    (out_dir / "link.ld").write_text("ENTRY(_start)\nSECTIONS {\n  . = 0x100000;\n  .text : { *(.text) }\n"
                                     "  . = ALIGN(16);\n  .data : { *(.data) }\n  . = ALIGN(16);\n  .bss : { *(.bss) }\n}\n",
                                     encoding="utf-8")
    for cmd in ([str(asm), "-march=r5900", "-o", str(out_dir / "eevec.o"), str(out_dir / "eevec.s")],
                [str(ld), "-T", str(out_dir / "link.ld"), "-o", str(out_dir / "eevec.elf"), str(out_dir / "eevec.o")]):
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode != 0:
            print(r.stdout, r.stderr, file=sys.stderr)
            raise SystemExit("failed: " + " ".join(cmd))
    return out_dir / "eevec.elf"


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", required=True, type=pathlib.Path)
    ap.add_argument("--build", action="store_true")
    ap.add_argument("--toolchain", default=os.environ.get("PS2DEV", "") and os.path.join(os.environ["PS2DEV"], "ee", "bin"))
    a = ap.parse_args(argv)
    meta = generate(a.out)
    print("vectors: %d (%s), safe %d, results %s..%s" % (meta["count"], meta["families"], meta["safe_count"],
                                                          meta["results_base"], hex32(slot_addr(meta["count"]))))
    if a.build:
        if not a.toolchain:
            raise SystemExit("--toolchain DIR (or $PS2DEV) required for --build")
        elf = build(a.out, a.toolchain)
        print("built", elf, elf.stat().st_size, "bytes")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
