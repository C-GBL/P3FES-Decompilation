#!/usr/bin/env python3
r"""PCSX2 2.8.2 audio reference capture of the title screen and the memory-card prompt (ADR-0014 milestone 3;
docs/PCSX2.md "Audio capture").

PCSX2 has no PINE opcode for its media capture; the only non-interactive path is the `ToggleVideoCapture`
hotkey (unbound by default) and the ini keys `[EmuCore/GS] EnableVideoCapture / EnableAudioCapture /
CaptureContainer`. This tool:

  1. checks the ini is the oracle configuration (capture.check_ini) and keeps a byte copy of it;
  2. binds the hotkey (`[Hotkeys] ToggleVideoCapture = Keyboard/F7`), turns video capture off and selects the
     `wav` container (audio only, PCM), through configure_ini.py's key editor;
  3. boots the ISO (fast boot, run_pcsx2.ps1 -KeepRunning), waits for "FMV ended" in the emulog (the title
     screen, ~145 s) plus --settle seconds, foregrounds the PCSX2 window exactly as capture.py does for GS dumps;
  4. sends F7 (capture on), then the pad keys of the recorded route's first inputs with --gap seconds between
     them -- Cross (Keyboard/K: the title's decide SE, which opens the memory-card prompt), Cross, Down
     (Keyboard/Down: the prompt's cursor SE), Cross -- then F7 (capture off); every keystroke is timed against
     the capture start;
  5. stops PCSX2, copies the new file from PCSX2's videos/ folder to extracted/_pcsx2/audio/<name>.wav with a
     <name>.json record (key times, ini hashes, PCSX2 version), and restores the ini byte for byte, checking its
     normalized hash is the one it had before (the oracle id).

Everything written holds game data and stays under gitignored paths. No other key than F7 / K / Down is sent,
and only while PCSX2 has the foreground.

Usage:
  python -I tools\ours\pcsx2\audio_capture.py run --name title_prompt [--settle 8] [--gap 3] [--no-restore]
  python -I tools\ours\pcsx2\audio_capture.py restore           # put the saved ini back by hand
"""
import argparse
import hashlib
import json
import pathlib
import shutil
import sys
import time

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
sys.path.insert(0, str(HERE.parent))
import capture  # noqa: E402
import configure_ini  # noqa: E402

VIDEOS = capture.PCSX2_DIR / "videos"
OUT_DIR = capture.OUT_ROOT / "audio"
INI_SAVE = OUT_DIR / "PCSX2.ini.before_audio_capture"

VK_F7, VK_K, VK_DOWN = 0x76, 0x4B, 0x28
KEYEVENTF_EXTENDEDKEY = 0x0001

CAPTURE_KEYS = [
    ("Hotkeys", "ToggleVideoCapture", "Keyboard/F7"),
    ("EmuCore/GS", "EnableVideoCapture", "false"),
    ("EmuCore/GS", "EnableAudioCapture", "true"),
    ("EmuCore/GS", "CaptureContainer", "wav"),
]


def log(msg):
    capture.log(msg)


def press(vk, extended=False, hold=0.06):
    """One key press through SendInput (capture.send_key's INPUT record), with the extended flag for arrows."""
    flags = KEYEVENTF_EXTENDEDKEY if extended else 0
    inp = capture.INPUT(type=1)
    inp.ki = capture.KEYBDINPUT(wVk=vk, wScan=0, dwFlags=flags, time=0, dwExtraInfo=None)
    if capture.user32.SendInput(1, capture.ctypes.byref(inp), capture.ctypes.sizeof(capture.INPUT)) != 1:
        raise OSError(capture.ctypes.get_last_error())
    time.sleep(hold)
    inp.ki.dwFlags = flags | capture.KEYEVENTF_KEYUP
    if capture.user32.SendInput(1, capture.ctypes.byref(inp), capture.ctypes.sizeof(capture.INPUT)) != 1:
        raise OSError(capture.ctypes.get_last_error())


def set_capture_keys():
    lines = configure_ini.load(capture.INI)
    changed = []
    for sec, key, value in CAPTURE_KEYS:
        c, old = configure_ini.set_key(lines, sec, key, value)
        if c:
            changed.append((sec, key, old, value))
    capture.INI.write_text("".join(lines), encoding="utf-8")
    return changed


def restore_ini():
    if not INI_SAVE.exists():
        raise SystemExit(f"no saved ini at {INI_SAVE}")
    capture.INI.write_bytes(INI_SAVE.read_bytes())
    raw, norm = capture.ini_hashes(capture.INI)
    log(f"ini restored: normalized {norm}")
    return norm


def run(args):
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    VIDEOS.mkdir(exist_ok=True)
    ini_info = capture.check_ini()
    before_norm = ini_info["ini_sha256_normalized"]
    INI_SAVE.write_bytes(capture.INI.read_bytes())
    changed = set_capture_keys()
    log(f"ini: capture keys set ({len(changed)} changed); oracle normalized hash before: {before_norm}")
    rec = {"name": args.name, "ini_before": ini_info, "ini_capture_keys": [f"[{s}] {k} = {v}" for s, k, v in CAPTURE_KEYS],
           "keys": [], "settle_s": args.settle, "gap_s": args.gap}
    videos_before = {p.name for p in VIDEOS.iterdir()}
    try:
        s = capture.Session(ini_info)
        try:
            s.connect()
            s.wait_elf()
            s.wait_title()
            log(f"title reached at {s.since_boot():.1f} s; settling {args.settle} s")
            time.sleep(args.settle)
            hwnd, title, fg = capture.gs_focus(s)
            rec["window_title"] = title
            if not fg:
                raise RuntimeError("PCSX2 window could not be foregrounded; no key sent")
            # Capture on.
            t0 = time.perf_counter()
            press(VK_F7)
            rec["capture_start_s_since_launch"] = round(s.since_boot(), 3)
            rec["globals_at_capture_start"] = s.globals()
            sequence = [("Cross", VK_K, False), ("Cross", VK_K, False), ("Down", VK_DOWN, True), ("Cross", VK_K, False)]
            for name, vk, ext in sequence:
                time.sleep(args.gap)
                if capture.user32.GetForegroundWindow() != hwnd:
                    raise RuntimeError(f"PCSX2 lost the foreground before {name}; stopping the key sequence")
                t = time.perf_counter() - t0
                press(vk, extended=ext)
                rec["keys"].append({"key": name, "t_s_since_capture_start": round(t, 3), "globals": s.globals()})
                log(f"sent {name} at +{t:.3f} s")
            time.sleep(args.gap)
            rec["capture_stop_s_since_capture_start"] = round(time.perf_counter() - t0, 3)
            press(VK_F7)
            time.sleep(1.5)
        finally:
            s.stop()
            rec["pcsx2_exited_by_itself"] = s.exited_by_itself
            rec["session"] = s.describe()
        new = sorted({p.name for p in VIDEOS.iterdir()} - videos_before)
        rec["files"] = []
        for n in new:
            src = VIDEOS / n
            dst = OUT_DIR / (args.name + src.suffix)
            shutil.copy2(src, dst)
            rec["files"].append({"source": f"videos/{n}", "copy": str(dst.relative_to(REPO)), "bytes": src.stat().st_size,
                                 "sha256": hashlib.sha256(src.read_bytes()).hexdigest()})
            log(f"capture -> {dst} ({src.stat().st_size} bytes)")
        if not new:
            log("WARNING: no capture file appeared in videos/")
    finally:
        if not args.no_restore:
            after_norm = restore_ini()
            rec["ini_restored_normalized"] = after_norm
            rec["ini_restored_equals_before"] = after_norm == before_norm
    (OUT_DIR / (args.name + ".json")).write_text(json.dumps(rec, indent=2), encoding="utf-8")
    log(f"record -> {OUT_DIR / (args.name + '.json')}")
    return 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("run")
    r.add_argument("--name", default="title_prompt")
    r.add_argument("--settle", type=float, default=8.0)
    r.add_argument("--gap", type=float, default=3.0)
    r.add_argument("--no-restore", action="store_true")
    sub.add_parser("restore")
    args = ap.parse_args(argv)
    if args.cmd == "restore":
        restore_ini()
        return 0
    return run(args)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
