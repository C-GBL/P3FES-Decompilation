#!/usr/bin/env python3
"""Idempotently configure the portable PCSX2 2.8.2 install for the P3FES reference-oracle role.

Edits tools/third_party/pcsx2/inis/PCSX2.ini in place (a timestamped backup is written first,
and PCSX2.ini.default.bak is the pristine `-testconfig` output). Only the keys listed in
SETTINGS (plus the optional --fastboot / --tracelog / --statecomp switches) are touched;
everything else is preserved verbatim, including key order and comments.

Usage:
  python configure_ini.py                      # apply the deterministic baseline
  python configure_ini.py --fastboot on|off    # EmuCore.EnableFastBoot
  python configure_ini.py --tracelog on|off    # EmuCore/TraceLog.Enabled + EE.bios/EE.r5900/EE.cop0/EE.memory/EE.knownhw/MISC.sif
  python configure_ini.py --statecomp 0|1|2|3  # EmuCore.SavestateCompressionType (0 Uncompressed, 1 Deflate64, 2 Zstandard, 3 LZMA2)
  python configure_ini.py --show               # print the effective values of the managed keys and exit
"""
import argparse
import datetime
import pathlib
import re
import shutil
import sys

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
INI = REPO / "tools" / "third_party" / "pcsx2" / "inis" / "PCSX2.ini"

# (section, key, value) -- see docs/PCSX2.md "ini keys changed" for the rationale of each.
SETTINGS = [
    ("UI", "SetupWizardIncomplete", "false"),   # otherwise the first-run wizard blocks every launch
    ("UI", "ConfirmShutdown", "false"),         # WM_CLOSE must stop the VM without a modal prompt
    ("UI", "StartFullscreen", "false"),
    ("UI", "PauseOnFocusLoss", "false"),
    ("UI", "StartPaused", "false"),
    ("Folders", "Bios", "bios"),
    ("Filenames", "BIOS", "ps2-0230a-20080220.bin"),  # user's own dump; referenced by file name only
    ("EmuCore", "EnablePINE", "true"),
    ("EmuCore", "PINESlot", "28011"),
    ("EmuCore", "SaveStateOnShutdown", "false"),
    ("EmuCore", "BackupSavestate", "false"),    # no .backup copies; extraction wants exactly one file per slot
    ("EmuCore", "EnableFastBootFastForward", "false"),
    ("EmuCore/Speedhacks", "vuThread", "false"),  # MTVU off: PCSX2 warns save states may be unstable with it (ADR-0012 §3)
    ("EmuCore/GS", "Renderer", "13"),           # GSRendererType::SW (software renderer)
    ("SPU2/Output", "Backend", "Null"),          # host audio off: with Cubeb, 5/5 runs crashed (0xC0000005) ~10 s into
                                                 # the opening FMV on 2026-10-18; guest SPU2 emulation is unaffected
    ("EmuCore/GS", "upscale_multiplier", "1"),  # native resolution
    ("Logging", "EnableFileLogging", "true"),   # -> logs/emulog.txt
    ("Logging", "EnableTimestamps", "true"),
    ("Logging", "EnableEEConsole", "true"),     # EEout (game printf / sceSif messages)
    ("Logging", "EnableIOPConsole", "true"),    # IOP tty (loadmodule lines)
    ("Logging", "EnableVerbose", "true"),
    ("Logging", "EnableSystemConsole", "false"),
]

TRACELOG_KEYS = ["Enabled", "EE.bios", "EE.memory", "EE.r5900", "EE.cop0", "EE.knownhw", "MISC.sif"]

SECTION_RE = re.compile(r"^\[(.+)\]\s*$")
KEY_RE = re.compile(r"^([^=\s][^=]*?)\s*=\s*(.*?)\s*$")


def load(path):
    return path.read_text(encoding="utf-8").splitlines(keepends=True)


def set_key(lines, section, key, value):
    """Set key in section, appending the key (or the section) if absent. Returns (changed, old)."""
    in_sec = False
    sec_start = None
    last_key_line = None
    for i, line in enumerate(lines):
        m = SECTION_RE.match(line)
        if m:
            if in_sec:
                break
            in_sec = m.group(1) == section
            if in_sec:
                sec_start = i
                last_key_line = i
            continue
        if in_sec:
            km = KEY_RE.match(line)
            if km:
                last_key_line = i
                if km.group(1) == key:
                    old = km.group(2)
                    if old == value:
                        return False, old
                    lines[i] = f"{key} = {value}\n"
                    return True, old
    if sec_start is None:
        if lines and not lines[-1].endswith("\n"):
            lines[-1] += "\n"
        lines.extend(["\n\n", f"[{section}]\n", f"{key} = {value}\n"])
        return True, None
    lines.insert(last_key_line + 1, f"{key} = {value}\n")
    return True, None


def get_key(lines, section, key):
    in_sec = False
    for line in lines:
        m = SECTION_RE.match(line)
        if m:
            in_sec = m.group(1) == section
            continue
        if in_sec:
            km = KEY_RE.match(line)
            if km and km.group(1) == key:
                return km.group(2)
    return None


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ini", type=pathlib.Path, default=INI)
    ap.add_argument("--fastboot", choices=["on", "off"])
    ap.add_argument("--tracelog", choices=["on", "off"])
    ap.add_argument("--statecomp", choices=["0", "1", "2", "3"])
    ap.add_argument("--set", nargs=3, action="append", metavar=("SECTION", "KEY", "VALUE"), default=[],
                    help="additional key to set, e.g. --set EmuCore/CPU/Recompiler EnableEE false")
    ap.add_argument("--show", action="store_true")
    args = ap.parse_args(argv)

    if not args.ini.is_file():
        print(f"error: {args.ini} not found; run `pcsx2-qt.exe -portable -testconfig` first", file=sys.stderr)
        return 2
    lines = load(args.ini)

    wanted = list(SETTINGS)
    if args.fastboot:
        wanted.append(("EmuCore", "EnableFastBoot", "true" if args.fastboot == "on" else "false"))
    if args.tracelog:
        v = "true" if args.tracelog == "on" else "false"
        wanted.extend(("EmuCore/TraceLog", k, v) for k in TRACELOG_KEYS)
    if args.statecomp:
        wanted.append(("EmuCore", "SavestateCompressionType", args.statecomp))
    wanted.extend((sec, key, value) for sec, key, value in args.set)

    if args.show:
        for sec, key, _ in wanted + [("EmuCore", "EnableFastBoot", None), ("EmuCore", "SavestateCompressionType", None),
                                     ("EmuCore/TraceLog", "Enabled", None)]:
            print(f"[{sec}] {key} = {get_key(lines, sec, key)}")
        return 0

    changes = []
    for sec, key, value in wanted:
        changed, old = set_key(lines, sec, key, value)
        if changed:
            changes.append((sec, key, old, value))
    if not changes:
        print("PCSX2.ini already configured; nothing written")
        return 0

    stamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    backup = args.ini.with_suffix(f".ini.{stamp}.bak")
    shutil.copy2(args.ini, backup)
    args.ini.write_text("".join(lines), encoding="utf-8")
    print(f"backup: {backup}")
    for sec, key, old, value in changes:
        print(f"[{sec}] {key}: {old!r} -> {value!r}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
