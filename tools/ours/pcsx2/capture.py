#!/usr/bin/env python3
"""Reference captures from PCSX2 via PINE (ADR-0012; docs/PCSX2.md "Reference captures").

Boots the ISO (run_pcsx2.ps1 -KeepRunning, fast or slow boot as the ini says), detects each sync point by
polling game globals over PINE (one batched message per poll), saves a state per point (MsgSaveState),
optionally fires one single-frame GS dump (Shift+F8) into the PCSX2 window, extracts the state into
extracted/_pcsx2/<name>/ (eeMemory.bin, Screenshot.png, the other entries) and writes
<name>/capture.json. Finally stops PCSX2 (WM_CLOSE) and keeps the emulog. Everything written holds game or
BIOS data and stays under gitignored paths.

Oracle ini (ADR-0012 §3; enforced, run configure_ini.py to apply): fast boot on, PINE on, software
renderer, MTVU off, host audio Null (with Cubeb every run crashed ~10 s into the opening FMV, see
docs/PCSX2.md). PCSX2 rewrites a few Qt view-state keys on every exit, so capture.json records both the raw SHA-256
of the ini at launch and a normalized one without those keys (`ini_sha256_normalized`, the oracle id).

Detection (VAs from docs/ANALYSIS/10_frame_loop_gs.md; disassembly notes in docs/PCSX2.md):
  elf_loaded  read32(0x5E5150) == 0x17 (#DirLst# header)
  first_flip  after g_skyFrameCount 0x7CEA78 >= 2 (first RwCameraShowRaster), the first EXECUTED flip:
              g_rwDMAFlipPending 0x7CE9AC 1->0, or g_rwDMAFlipBuf 0x7CE9A8 toggling while pending stays 1
              (_rwDMAVSYNCHandler 0x4D47F0 clears pending, flips, and may pop the next flip at once)
  atlus_logo  g_skyFrameCount >= first-flip value + --logo-frames (default 150 = 5.0 s at 30 fps; the logo is
              fully shown ~+3.8..+6.2 s after the first flip, before the Sofdec/ADX screen and the FMV);
              heuristic, confirmed afterwards by a pixel test on the embedded screenshot
  title       "FMV ended" in logs/emulog.txt, then g_skyFrameCount + --title-frames (default 240 = 8 s);
              the title stays up ~34 s before the attract FMV restarts
The state is written at PCSX2's next VM sync point, so each capture.json also reads the globals back from
the extracted eeMemory.bin (`state_globals`): that is the exact frame the image represents.

Usage:
  python capture.py run --tag A [--points first_flip,atlus_logo,title] [--title-name title_runA] [--no-gsdump]
  python capture.py run --tag B --points title --title-name title_runB
  python capture.py extract <slot> <name> [--tag X]   # extract an existing slot into extracted/_pcsx2/<name>
"""
import argparse
import ctypes
import ctypes.wintypes as wt
import datetime
import hashlib
import json
import pathlib
import re
import shutil
import struct
import subprocess
import sys
import time
import zlib

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
sys.path.insert(0, str(HERE.parent))
import pine  # noqa: E402
import extract_savestate  # noqa: E402

PCSX2_DIR = REPO / "tools" / "third_party" / "pcsx2"
INI = PCSX2_DIR / "inis" / "PCSX2.ini"
EMULOG = PCSX2_DIR / "logs" / "emulog.txt"
SSTATES = PCSX2_DIR / "sstates"
SNAPS = PCSX2_DIR / "snaps"          # [Folders] Snapshots: GS dumps (.gs.zst + .png) land here
OUT_ROOT = REPO / "extracted" / "_pcsx2"
RUN_PS1 = HERE.parent / "run_pcsx2.ps1"
ELF = REPO / "extracted" / "disc" / "SLUS_216.21"
ELF_CRC = "94a82aaa"

VA_DIRLST = 0x5E5150
GLOBALS = [  # name, width, VA (kuseg == physical offset in eeMemory.bin)
    ("g_skyFrameCount", 32, 0x7CEA78),
    ("g_rwDMAFlipPending", 8, 0x7CE9AC),
    ("g_rwDMAFlipBuf", 8, 0x7CE9A8),
    ("adxt_vsync_cnt", 32, 0x787568),
    ("kwln_frame", 32, 0x7CE10C),
    ("g_kwlnFirstFrame", 32, 0x7CC134),
]
G = {name: i for i, (name, _, _) in enumerate(GLOBALS)}

REQUIRED_INI = {
    ("EmuCore", "EnableFastBoot"): "true",
    ("EmuCore", "EnablePINE"): "true",
    ("EmuCore/GS", "Renderer"): "13",
    ("EmuCore/Speedhacks", "vuThread"): "false",
    ("SPU2/Output", "Backend"): "Null",
}
# Qt view state PCSX2 rewrites on every exit, in whichever section holds it ([UI], [GameListTableView], ...)
VOLATILE_INI_KEYS = {"HeaderState", "MainWindowGeometry", "MainWindowState"}

SECTION_RE = re.compile(r"^\[(.+)\]\s*$")
KEY_RE = re.compile(r"^([^=\s][^=]*?)\s*=\s*(.*?)\s*$")


def log(msg):
    print(f"[{time.strftime('%H:%M:%S')}] {msg}", flush=True)


def now_iso():
    return datetime.datetime.now().astimezone().isoformat(timespec="seconds")


# ---------------------------------------------------------------- ini
def ini_values(path):
    vals, sec = {}, None
    for line in path.read_text(encoding="utf-8").splitlines():
        m = SECTION_RE.match(line)
        if m:
            sec = m.group(1)
            continue
        k = KEY_RE.match(line)
        if k and sec is not None:
            vals[(sec, k.group(1))] = k.group(2)
    return vals


def ini_hashes(path):
    raw = path.read_bytes()
    kept, sec = [], None
    for line in raw.decode("utf-8").splitlines():
        m = SECTION_RE.match(line)
        if m:
            sec = m.group(1)
        else:
            k = KEY_RE.match(line)
            if k and k.group(1) in VOLATILE_INI_KEYS:
                continue
        kept.append(line.rstrip())
    norm = "\n".join(kept).encode("utf-8")
    return hashlib.sha256(raw).hexdigest(), hashlib.sha256(norm).hexdigest()


def check_ini():
    vals = ini_values(INI)
    bad = {k: vals.get(k) for k, v in REQUIRED_INI.items() if vals.get(k) != v}
    if bad:
        lines = [f"  [{s}] {k} = {got!r}, want {REQUIRED_INI[(s, k)]!r}" for (s, k), got in bad.items()]
        raise SystemExit("PCSX2.ini is not in the oracle configuration:\n" + "\n".join(lines) +
                         "\n  fix: python tools/ours/pcsx2/configure_ini.py --fastboot on")
    raw, norm = ini_hashes(INI)
    return {"ini_path": str(INI.relative_to(REPO)), "ini_sha256_at_launch": raw, "ini_sha256_normalized": norm,
            "ini_normalization": "drops the keys " + ", ".join(sorted(VOLATILE_INI_KEYS)) + " in any section",
            "ini_oracle_keys": {f"[{s}] {k}": vals.get((s, k)) for (s, k) in REQUIRED_INI},
            "boot": "fast" if vals.get(("EmuCore", "EnableFastBoot")) == "true" else "slow"}


# ---------------------------------------------------------------- PCSX2 session
class Session:
    def __init__(self, ini_info):
        self.ini = ini_info
        flag = "-FastBoot" if ini_info["boot"] == "fast" else "-SlowBoot"
        cmd = ["powershell", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", str(RUN_PS1), "-KeepRunning", flag]
        self.t0 = time.perf_counter()
        out = subprocess.run(cmd, capture_output=True, text=True, cwd=str(REPO))
        m = re.search(r"pid=(\d+)", out.stdout)
        if out.returncode != 0 or not m:
            raise RuntimeError(f"run_pcsx2.ps1 failed (rc={out.returncode}):\n{out.stdout}\n{out.stderr}")
        self.pid = int(m.group(1))
        self.started_at = now_iso()
        self.p = None
        self.meta = {}
        self.events = {}
        self.exited_by_itself = None

    def since_boot(self):
        return time.perf_counter() - self.t0

    def connect(self):
        self.p = pine.connect_retry(total=60.0)
        while True:  # the PINE server answers before the VM exists; reads fail until then
            try:
                self.p.read32(VA_DIRLST)
                break
            except pine.PineError:
                if self.since_boot() > 60:
                    raise
                time.sleep(0.02)
        self.meta = {"pcsx2_version": self.p.version(), "elf_crc": self.p.uuid(), "game_id": self.p.game_id()}
        if self.meta["elf_crc"].lower() != ELF_CRC:
            raise RuntimeError(f"unexpected game CRC {self.meta['elf_crc']}")
        return self.p

    def globals(self):
        v = self.p.read_many([(w, va) for _, w, va in GLOBALS])
        return dict(zip((n for n, _, _ in GLOBALS), v))

    def alive(self):
        out = subprocess.run(["powershell", "-NoProfile", "-Command",
                              f"if (Get-Process -Id {self.pid} -ErrorAction SilentlyContinue) {{ 'yes' }}"],
                             capture_output=True, text=True)
        return "yes" in out.stdout

    def stop(self):
        if self.p is not None:
            try:
                self.p.close()
            except OSError:
                pass
        self.exited_by_itself = not self.alive()
        cmd = ["powershell", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", str(RUN_PS1), "-StopPid", str(self.pid)]
        out = subprocess.run(cmd, capture_output=True, text=True, cwd=str(REPO))
        log(out.stdout.strip())
        logs = OUT_ROOT / "logs"
        logs.mkdir(parents=True, exist_ok=True)
        if EMULOG.exists():
            self.emulog_copy = logs / f"emulog_capture_{datetime.datetime.now():%Y%m%d-%H%M%S}.txt"
            shutil.copy2(EMULOG, self.emulog_copy)
            log(f"emulog -> {self.emulog_copy}")

    def describe(self):
        d = dict(self.ini)
        d.update(self.meta)
        d.update({"pid": self.pid, "started_at": self.started_at, "events_s_since_launch": self.events})
        return d

    def wait_elf(self, limit=120):
        while self.p.read32(VA_DIRLST) != 0x17:
            if self.since_boot() > limit:
                raise RuntimeError("game ELF not detected in RAM")
            time.sleep(0.01)
        self.events["elf_in_ram"] = round(self.since_boot(), 3)

    def wait_first_flip(self, limit=180):
        """Returns (sample_before, sample_at, polls, method)."""
        polls, prev = 0, None
        while True:
            g = self.globals()
            polls += 1
            if prev is not None and prev["g_skyFrameCount"] >= 2:
                edge = prev["g_rwDMAFlipPending"] == 1 and g["g_rwDMAFlipPending"] == 0
                swap = (prev["g_rwDMAFlipPending"] == 1 and g["g_rwDMAFlipPending"] == 1
                        and prev["g_rwDMAFlipBuf"] != g["g_rwDMAFlipBuf"])
                if edge or swap:
                    self.events["first_flip_executed"] = round(self.since_boot(), 3)
                    return prev, g, polls, "pending 1->0" if edge else "buffer toggled while pending"
                if g["g_skyFrameCount"] >= prev["g_skyFrameCount"] + 3 and g["g_rwDMAFlipPending"] == 0:
                    # three more requests without seeing an edge: the edge fell between polls
                    self.events["first_flip_executed"] = round(self.since_boot(), 3)
                    return prev, g, polls, "inferred (no edge seen; sky advanced by 3 with pending 0)"
            if self.since_boot() > limit:
                raise RuntimeError("no flip executed")
            prev = g
            time.sleep(0.001)

    def wait_title(self, limit=420):
        while not emulog_contains("FMV ended"):
            if self.since_boot() > limit:
                raise RuntimeError("'FMV ended' not seen in emulog")
            if not self.alive():
                raise RuntimeError("PCSX2 exited (crash?) before the title")
            time.sleep(0.25)
        self.events["fmv_ended_seen"] = round(self.since_boot(), 3)


def emulog_contains(needle):
    try:
        return needle in EMULOG.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return False


def boot_and_wait_title(settle_s=8.0):
    """Used by measure_flips.py --boot: oracle ini, boot, wait for the title, settle."""
    s = Session(check_ini())
    try:
        s.connect()
        s.wait_elf()
        s.wait_title()
        time.sleep(settle_s)
    except BaseException:
        s.stop()
        raise
    if s.p is not None:
        s.p.close()
        s.p = None
    return s


# ---------------------------------------------------------------- GS dump hotkey
# PCSX2 has no PINE opcode for GS dumps; its hotkey ([Hotkeys] GSDumpSingleFrame = Shift+F8) is the only
# non-interactive path. We foreground the PCSX2 main window (it hosts the display widget) and send exactly
# Shift+F8 with SendInput, only after GetForegroundWindow() confirms PCSX2 has focus. No other key is sent.
user32 = ctypes.WinDLL("user32", use_last_error=True)
EnumWindowsProc = ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
VK_SHIFT, VK_F8, VK_MENU = 0x10, 0x77, 0x12
KEYEVENTF_KEYUP = 0x0002


class KEYBDINPUT(ctypes.Structure):
    _fields_ = [("wVk", wt.WORD), ("wScan", wt.WORD), ("dwFlags", wt.DWORD), ("time", wt.DWORD),
                ("dwExtraInfo", ctypes.POINTER(ctypes.c_ulong))]


class INPUT(ctypes.Structure):
    class _U(ctypes.Union):
        _fields_ = [("ki", KEYBDINPUT), ("pad", ctypes.c_byte * 32)]
    _anonymous_ = ("u",)
    _fields_ = [("type", wt.DWORD), ("u", _U)]


def send_key(vk, up=False):
    inp = INPUT(type=1)
    inp.ki = KEYBDINPUT(wVk=vk, wScan=0, dwFlags=KEYEVENTF_KEYUP if up else 0, time=0, dwExtraInfo=None)
    if user32.SendInput(1, ctypes.byref(inp), ctypes.sizeof(INPUT)) != 1:
        raise OSError(ctypes.get_last_error())


def find_main_window(pid):
    found = []

    def cb(hwnd, _):
        owner = wt.DWORD()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(owner))
        if owner.value == pid and user32.IsWindowVisible(hwnd) and user32.GetWindow(hwnd, 4) == 0:  # GW_OWNER
            n = user32.GetWindowTextLengthW(hwnd)
            buf = ctypes.create_unicode_buffer(n + 1)
            user32.GetWindowTextW(hwnd, buf, n + 1)
            found.append((hwnd, buf.value))
        return True

    user32.EnumWindows(EnumWindowsProc(cb), 0)
    for hwnd, title in found:
        if "PCSX2" in title or "Persona" in title:
            return hwnd, title
    return found[0] if found else (None, None)


def gs_focus(session):
    """Foreground the PCSX2 window (done once ahead of the points so that firing costs only the keystroke)."""
    hwnd, title = find_main_window(session.pid)
    if hwnd is None:
        return None, title, False
    if user32.GetForegroundWindow() != hwnd:
        send_key(VK_MENU)  # a synthetic Alt tap lets SetForegroundWindow succeed from a background process
        send_key(VK_MENU, up=True)
        user32.SetForegroundWindow(hwnd)
        time.sleep(0.2)
    return hwnd, title, user32.GetForegroundWindow() == hwnd


def gs_fire(session):
    """Sends exactly Shift+F8 if (and only if) PCSX2 has the foreground. Returns the attempt record."""
    SNAPS.mkdir(exist_ok=True)
    hwnd, title, fg = gs_focus(session)
    rec = {"method": "SendInput Shift+F8 to the foregrounded PCSX2 main window ([Hotkeys] GSDumpSingleFrame), "
                     "fired immediately before MsgSaveState",
           "window_title": title, "foreground": fg, "files": [], "globals_at_keystroke": None,
           "_before": {p.name for p in SNAPS.iterdir()}}
    if not fg:
        rec["result"] = "PCSX2 window could not be foregrounded; no key sent"
        return rec
    rec["globals_at_keystroke"] = session.globals()
    send_key(VK_SHIFT)
    send_key(VK_F8)
    time.sleep(0.03)
    send_key(VK_F8, up=True)
    send_key(VK_SHIFT, up=True)
    rec["result"] = "sent"
    return rec


def gs_collect(rec, outdir):
    before = rec.pop("_before", set())
    if rec.get("result") != "sent":
        return rec
    deadline = time.time() + 10.0
    new = []
    while time.time() < deadline:
        new = sorted({p.name for p in SNAPS.iterdir()} - before)
        if any(n.endswith(".gs.zst") for n in new):
            break
        time.sleep(0.2)
    if not any(n.endswith(".gs.zst") for n in new):
        rec["result"] = "no .gs.zst appeared within 10 s"
        return rec
    for n in sorted({p.name for p in SNAPS.iterdir()} - before):
        src = SNAPS / n
        dst = outdir / ("gsdump.gs.zst" if n.endswith(".gs.zst") else "gsdump" + src.suffix)
        # PCSX2 keeps the file open while compressing; copy once it is readable and its size is stable
        last, t_end = -1, time.time() + 30.0
        while True:
            try:
                sz = src.stat().st_size
                if sz == last and sz > 0:
                    shutil.copy2(src, dst)
                    break
                last = sz
            except PermissionError:
                pass
            if time.time() > t_end:
                raise RuntimeError(f"GS dump {n} stayed locked/growing for 30 s")
            time.sleep(0.5)
        rec["files"].append({"source": f"snaps/{n}", "copy": dst.name, "bytes": src.stat().st_size,
                             "sha256": hashlib.sha256(src.read_bytes()).hexdigest()})
    rec["result"] = "ok"
    return rec


# ---------------------------------------------------------------- screenshot check (stdlib PNG decode)
def png_rgb(path):
    data = path.read_bytes()
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError("not a PNG")
    pos, idat, w = 8, [], None
    while pos < len(data):
        (n,) = struct.unpack(">I", data[pos:pos + 4])
        typ, body = data[pos + 4:pos + 8], data[pos + 8:pos + 8 + n]
        if typ == b"IHDR":
            w, h, depth, ctype, _, _, interlace = struct.unpack(">IIBBBBB", body)
            if depth != 8 or ctype not in (2, 6) or interlace:
                raise ValueError(f"unsupported PNG (depth {depth}, color {ctype}, interlace {interlace})")
            bpp = 3 if ctype == 2 else 4
        elif typ == b"IDAT":
            idat.append(body)
        pos += 12 + n
    raw = zlib.decompress(b"".join(idat))
    stride = w * bpp
    rows, prev = [], bytearray(stride)
    for y in range(h):
        f = raw[y * (stride + 1)]
        line = bytearray(raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)])
        for i in range(stride):
            a = line[i - bpp] if i >= bpp else 0
            b = prev[i]
            c = prev[i - bpp] if i >= bpp else 0
            if f == 1:
                line[i] = (line[i] + a) & 255
            elif f == 2:
                line[i] = (line[i] + b) & 255
            elif f == 3:
                line[i] = (line[i] + ((a + b) >> 1)) & 255
            elif f == 4:
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                line[i] = (line[i] + (a if pa <= pb and pa <= pc else b if pb <= pc else c)) & 255
        rows.append(line)
        prev = line
    return w, h, bpp, rows


def screenshot_stats(path):
    """Coarse pixel classes, sampled every 2nd pixel. Atlus logo = dark frame with blue letters and a red 'T'."""
    w, h, bpp, rows = png_rgb(path)
    n = dark = red = blue = bright_blue_bg = 0
    for y in range(0, h, 2):
        line = rows[y]
        for x in range(0, w, 2):
            r, g, b = line[x * bpp], line[x * bpp + 1], line[x * bpp + 2]
            n += 1
            if r < 40 and g < 40 and b < 40:
                dark += 1
            if r > 150 and g < 90 and b < 110:
                red += 1
            if b > 140 and r < 120 and g < 140:
                blue += 1
            if b > 180 and g > 100 and r < 80:
                bright_blue_bg += 1
    s = {"width": w, "height": h, "dark_frac": round(dark / n, 4), "red_frac": round(red / n, 5),
         "blue_frac": round(blue / n, 5), "light_blue_bg_frac": round(bright_blue_bg / n, 4)}
    s["atlus_logo_likely"] = s["dark_frac"] > 0.8 and s["red_frac"] > 0.002 and s["blue_frac"] > 0.01 \
        and s["light_blue_bg_frac"] < 0.05
    return s


# ---------------------------------------------------------------- save state + extraction
def slot_path(slot):
    return SSTATES / f"SLUS-21621 (94A82AAA).{slot:02d}.p2s"


def save_state(session, slot, timeout=30.0):
    path = slot_path(slot)
    if path.exists():
        path.unlink()
    at_request = session.globals()
    t_req = session.since_boot()
    session.p.save_state(slot)
    deadline = time.time() + timeout
    last = -1
    while time.time() < deadline:
        if path.exists():
            sz = path.stat().st_size
            if sz == last and sz > 0:
                return path, at_request, t_req, session.since_boot() - t_req
            last = sz
        time.sleep(0.1)
    raise RuntimeError(f"save state slot {slot} did not appear at {path}")


def read_state_globals(ee_path):
    data = ee_path.read_bytes()
    out = {}
    for name, w, va in GLOBALS:
        off = va & 0x1FFFFFFF
        out[name] = int.from_bytes(data[off:off + w // 8], "little")
    return out


def extract_to(state_path, outdir):
    if outdir.exists():
        shutil.rmtree(outdir)
    outdir.mkdir(parents=True)
    report = extract_savestate.extract(state_path, outdir, extract_savestate.DEFAULT_ZSTD_DLL)
    ee = outdir / "eeMemory.bin"
    if not ee.exists() or ee.stat().st_size != 32 * 1024 * 1024:
        raise RuntimeError(f"{outdir.name}: eeMemory.bin missing or not 32 MiB")
    bad = [r for r in report if r[3] != "crc ok"]
    if bad:
        raise RuntimeError(f"{outdir.name}: entries failed CRC/extraction: {bad}")
    return [{"entry": n, "method": m, "bytes": s, "status": st} for n, m, s, st in report]


def capture_point(session, name, slot, args, detection, extra=None):
    outdir = OUT_ROOT / name
    gs = gs_fire(session) if not args.no_gsdump else {"result": "skipped (--no-gsdump)"}
    path, at_req, t_req, latency = save_state(session, slot)
    entries = extract_to(path, outdir)
    gs = gs_collect(gs, outdir)
    state_g = read_state_globals(outdir / "eeMemory.bin")
    rec = session.describe()
    rec.update({
        "point": name, "run_tag": args.tag, "captured_at": now_iso(), "slot": slot, "state_file": path.name,
        "seconds_since_launch_at_save_request": round(t_req, 3), "savestate_file_latency_s": round(latency, 3),
        "detection": detection, "globals_at_save_request": at_req, "state_globals": state_g,
        "state_frames_after_request": {
            "g_skyFrameCount": state_g["g_skyFrameCount"] - at_req["g_skyFrameCount"],
            "kwln_frame": state_g["kwln_frame"] - at_req["kwln_frame"]},
        "screenshot": screenshot_stats(outdir / "Screenshot.png") if (outdir / "Screenshot.png").exists() else None,
        "gs_dump": gs, "extracted": entries,
        "elf_sha256": hashlib.sha256(ELF.read_bytes()).hexdigest() if ELF.exists() else None,
    })
    if extra:
        rec.update(extra)
    (outdir / "capture.json").write_text(json.dumps(rec, indent=2))
    log(f"{name}: slot {slot}, state sky={state_g['g_skyFrameCount']} kwln={state_g['kwln_frame']}, "
        f"gs dump {gs.get('result')}, screenshot {rec['screenshot']}")
    return rec


# ---------------------------------------------------------------- commands
def run(args):
    ini_info = check_ini()
    points = args.points.split(",")
    for pt in points:
        if pt not in ("first_flip", "atlus_logo", "title"):
            raise SystemExit(f"unknown point {pt}")
    OUT_ROOT.mkdir(parents=True, exist_ok=True)
    session = Session(ini_info)
    log(f"PCSX2 pid {session.pid} ({ini_info['boot']} boot, ini {ini_info['ini_sha256_normalized'][:12]})")
    names = {}
    try:
        session.connect()
        log(f"PINE: {session.meta}")
        session.wait_elf()
        log(f"ELF in RAM at {session.events['elf_in_ram']} s")
        if not args.no_gsdump:
            log(f"PCSX2 window foregrounded for the GS-dump hotkey: {gs_focus(session)[2]}")
        prev, trig, polls, how = session.wait_first_flip()
        log(f"first flip executed at {session.events['first_flip_executed']} s ({how}; {trig})")
        slot = args.slot_base
        if "first_flip" in points:
            name = "first_flip"
            names["first_flip"] = name
            capture_point(session, name, slot, args, {
                "method": "poll (batched PINE, ~1 ms) until the first executed RW flip after g_skyFrameCount >= 2, "
                          "then MsgSaveState", "edge": how, "polls": polls,
                "globals_before_edge": prev, "globals_at_edge": trig,
                "note": "the state is written at PCSX2's next VM sync point; state_globals gives its exact frame"})
            slot += 1
        if "atlus_logo" in points:
            name = "atlus_logo"
            names["atlus_logo"] = name
            target = trig["g_skyFrameCount"] + args.logo_frames
            while session.globals()["g_skyFrameCount"] < target:
                time.sleep(0.002)
            rec = capture_point(session, name, slot, args, {
                "method": f"g_skyFrameCount >= first-flip value + {args.logo_frames}", "target_frame": target,
                "uncertainty": "time-window heuristic: in four probe runs the logo was fully shown ~+3.5..+6 s after "
                               "the first flip (fade-in at +3 s, Sofdec/ADX screen by +7 s); the memory-card check "
                               "before it can vary. Confirmed only by the screenshot pixel test below."})
            if not rec["screenshot"] or not rec["screenshot"]["atlus_logo_likely"]:
                log("WARNING: atlus_logo screenshot does not look like the Atlus logo")
            slot += 1
        if "title" in points:
            name = args.title_name
            names["title"] = name
            session.wait_title()
            base = session.globals()["g_skyFrameCount"]
            target = base + args.title_frames
            while session.globals()["g_skyFrameCount"] < target:
                time.sleep(0.005)
            capture_point(session, name, slot, args, {
                "method": f"emulog 'FMV ended' seen, then g_skyFrameCount >= value then + {args.title_frames}",
                "sky_at_fmv_ended_seen": base, "target_frame": target,
                "uncertainty": "the emulog is polled every 0.25 s and flushed by PCSX2 with some delay (~1 s seen), "
                               "so the anchor jitters by tens of frames between runs; state_globals records the "
                               "exact frame. The title stays up ~34 s before the attract FMV restarts."})
            slot += 1
            if args.measure_flips:
                import measure_flips  # same directory
                time.sleep(2.0)
                rows = measure_flips.sample_loop(session.p, args.measure_flips, 0.002)
                res = measure_flips.analyse(rows, 0.002)
                res.update(session.meta)
                res["measured_at"] = now_iso()
                res["session"] = session.describe()
                res["context"] = f"same PCSX2 session as capture point {name}, right after it"
                out = OUT_ROOT / "flips"
                out.mkdir(parents=True, exist_ok=True)
                jpath = out / f"flip_rate_{args.tag}_{datetime.datetime.now():%Y%m%d-%H%M%S}.json"
                jpath.write_text(json.dumps(res, indent=2))
                log(f"flip rate -> {jpath}: {res['executed_flips_per_s']} flips/s, ratio "
                    f"{res['ratio_to_59_94']['executed_flips']}, coincident {res['flips_coincident_with_tail_handler_vblank']}"
                    f"/{res['executed_flips']}")
    finally:
        session.stop()
        crashed = session.exited_by_itself
        log(f"PCSX2 {'had already EXITED (crash?)' if crashed else 'stopped'}")
    summary = OUT_ROOT / f"capture_run_{args.tag}.json"
    summary.write_text(json.dumps({"tag": args.tag, "points": names, "session": session.describe(),
                                   "pcsx2_exited_by_itself": session.exited_by_itself,
                                   "emulog_copy": str(getattr(session, "emulog_copy", ""))}, indent=2))
    return 0


def extract_cmd(args):
    path = slot_path(args.slot)
    outdir = OUT_ROOT / args.name
    entries = extract_to(path, outdir)
    raw, norm = ini_hashes(INI)
    rec = {"point": args.name, "slot": args.slot, "state_file": path.name, "run_tag": args.tag,
           "ini_sha256_now": raw, "ini_sha256_normalized_now": norm, "captured_at": now_iso(),
           "detection": {"method": "manual: extracted from an existing slot"},
           "state_globals": read_state_globals(outdir / "eeMemory.bin"),
           "screenshot": screenshot_stats(outdir / "Screenshot.png") if (outdir / "Screenshot.png").exists() else None,
           "extracted": entries}
    (outdir / "capture.json").write_text(json.dumps(rec, indent=2))
    print(f"extracted slot {args.slot} -> {outdir}")
    return 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("run")
    r.add_argument("--tag", required=True, help="run tag recorded in capture.json")
    r.add_argument("--points", default="first_flip,atlus_logo,title")
    r.add_argument("--title-name", default="title", help="directory name of the title point, e.g. title_runA")
    r.add_argument("--slot-base", type=int, default=1)
    r.add_argument("--logo-frames", type=int, default=150)
    r.add_argument("--title-frames", type=int, default=240)
    r.add_argument("--no-gsdump", action="store_true")
    r.add_argument("--measure-flips", type=int, default=0, metavar="N",
                   help="after the title point, PINE-sample N times at 2 ms (measure_flips.py analysis)")
    r.set_defaults(fn=run)
    e = sub.add_parser("extract")
    e.add_argument("slot", type=int)
    e.add_argument("name")
    e.add_argument("--tag", default="manual")
    e.set_defaults(fn=extract_cmd)
    args = ap.parse_args(argv)
    return args.fn(args)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
