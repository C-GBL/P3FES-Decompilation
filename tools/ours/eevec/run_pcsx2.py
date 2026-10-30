#!/usr/bin/env python3
"""Run the EE semantics test ELF (gen_vectors.py --build) under PCSX2 2.8.2 and collect the observed results.

  python -I tools/ours/eevec/run_pcsx2.py --elf build/eevec-msvc/eevec/eevec.elf --layout build/eevec-msvc/eevec/layout.json
                                          --out tests/ee/vectors/pcsx2_vectors.json [--ee-mode rec|int] [--merge FILE]

Steps: (1) check the oracle ini (tools/ours/pcsx2/capture.py check_ini; --ee-mode int temporarily sets
[EmuCore/CPU/Recompiler] EnableEE = false through configure_ini.py and restores it afterwards), (2) boot PCSX2 on the
ELF through run_pcsx2.ps1 -KeepRunning -FastBoot (PCSX2 boots a bare ELF given as the file argument: observed
"ELF Loading: host:<name>.elf"), (3) poll the results-table header over PINE until the magic word appears, then
wait for the tail magic (the "risky" vectors may trap: a missing tail magic is recorded, not fatal), (4) read the
table in batched 64-bit PINE reads, decode every slot per family, (5) stop PCSX2 (WM_CLOSE) and verify the ini is
back in the oracle configuration (normalized hash). --merge adds this run's observations to an existing JSON as
"obs_<mode>" instead of rewriting it (used to record the interpreter pass next to the recompiler pass).

The output JSON (committed as tests/ee/vectors/pcsx2_vectors.json) is self-contained: every vector carries its
inputs and the observed outputs as hex strings; tests/ee/test_pcsx2_vectors.cpp replays it through the headers.
"""
import argparse
import datetime
import hashlib
import json
import pathlib
import re
import subprocess
import sys
import time

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
sys.path.insert(0, str(REPO / "tools" / "ours" / "pcsx2"))
import pine  # noqa: E402
import capture  # noqa: E402

RUN_PS1 = REPO / "tools" / "ours" / "pcsx2" / "run_pcsx2.ps1"
CONFIGURE = REPO / "tools" / "ours" / "pcsx2" / "configure_ini.py"
EMULOG = REPO / "tools" / "third_party" / "pcsx2" / "logs" / "emulog.txt"
ORACLE_INI_NORMALIZED = "2630dac33716a408f24adc3d20250cc240bef9b5c77451305787c08019782a59"  # docs/PCSX2.md section 9


def log(msg):
    print("[%s] %s" % (time.strftime("%H:%M:%S"), msg), flush=True)


def ps(args):
    cmd = ["powershell", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", str(RUN_PS1)] + args
    return subprocess.run(cmd, capture_output=True, text=True, cwd=str(REPO))


def configure(extra):
    r = subprocess.run([sys.executable, "-I", str(CONFIGURE), "--fastboot", "on"] + extra, capture_output=True, text=True, cwd=str(REPO))
    log("configure_ini: " + r.stdout.strip().replace("\n", " | "))
    if r.returncode != 0:
        raise SystemExit(r.stderr)


def h32(x):
    return "0x%08X" % (x & 0xFFFFFFFF)


def h64(x):
    return "0x%016X" % (x & 0xFFFFFFFFFFFFFFFF)


def h128(x):
    return "0x%032X" % x


def slot_fields(buf):
    """Split a 96-byte slot into quadwords and the eight extra words."""
    qw = [int.from_bytes(buf[o:o + 16], "little") for o in (0, 16, 32, 80)]
    x = [int.from_bytes(buf[48 + 4 * i:52 + 4 * i], "little") for i in range(8)]
    return qw, x


def decode_slot(vec, buf):
    (rd, hi, lo, spare), x = slot_fields(buf)
    fam = vec["family"]
    op = vec["op"]
    if fam == "hilo":
        return {"rd": h128(rd), "hi": h128(hi), "lo": h128(lo), "sa": h32(x[0])}
    if fam == "mmi":
        d = {"rd": h128(rd), "hi": h128(hi), "lo": h128(lo), "sa": h32(x[0])}
        if op == "sq":
            d["mem0"] = h128(rd)
            d["mem1"] = h128(spare)
        return d
    if fam == "fpu":
        return {"fd64": h64(rd & 0xFFFFFFFFFFFFFFFF), "fd": h32(x[3]), "acc": h32(hi & 0xFFFFFFFF), "fcr31": h32(x[0]),
                "fcr31_pre": h32(x[1]), "fcr0": h32(x[2])}
    if fam == "vu0":
        base = op.split(".")[0]
        d = {"status_pre": h32(x[0]), "mac_pre": h32(x[1]), "clip_pre": h32(x[2]), "q_pre": h32(x[3]),
             "acc": h128(hi), "fs_after": h128(lo), "ft_after": h128(spare)}
        if base == "ctc2":
            d.update({"readback": h32(x[4]), "status": h32(x[5]), "mac": h32(x[6]), "clip": h32(x[7]), "fd": h128(rd)})
        elif base in ("viadd", "visub", "viand", "vior", "viaddi"):
            d.update({"vi3": h32(rd & 0xFFFFFFFF), "status": h32(x[4]), "mac": h32(x[5]), "clip": h32(x[6]), "q": h32(x[7])})
        else:
            d.update({"fd": h128(rd), "status": h32(x[4]), "mac": h32(x[5]), "clip": h32(x[6]), "q": h32(x[7])})
        return d
    if fam == "core":
        if "mem0" in vec["in"]:
            return {"rt": h64(rd & 0xFFFFFFFFFFFFFFFF), "mem0": h128(hi), "mem1": h128(lo)}
        return {"rd": h64(rd & 0xFFFFFFFFFFFFFFFF), "hi": h128(hi), "lo": h128(lo)}
    raise SystemExit("unknown family " + fam)


def read_table(p, base, length):
    out = bytearray()
    addr = base
    while len(out) < length:
        n = min(512, (length - len(out)) // 8)
        vals = p.read_many([(64, addr + 8 * k) for k in range(n)])
        for v in vals:
            out += v.to_bytes(8, "little")
        addr += 8 * n
    return bytes(out)


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", required=True, type=pathlib.Path)
    ap.add_argument("--layout", required=True, type=pathlib.Path)
    ap.add_argument("--out", required=True, type=pathlib.Path)
    ap.add_argument("--ee-mode", choices=["rec", "int"], default="rec",
                    help="rec = EE recompiler (oracle ini), int = EE interpreter (EnableEE=false for this run)")
    ap.add_argument("--merge", type=pathlib.Path, help="existing JSON to add obs_<mode> to (instead of writing a new file)")
    ap.add_argument("--timeout", type=float, default=120.0)
    a = ap.parse_args(argv)

    layout = json.loads(a.layout.read_text(encoding="utf-8"))
    meta = layout["meta"]
    base = int(meta["results_base"], 16)
    count = meta["count"]
    slot_bytes = meta["slot_bytes"]
    header = meta["header_bytes"]
    magic = int(meta["magic"], 16)
    tail_magic = int(meta["tail_magic"], 16)
    table_len = header + count * slot_bytes

    if a.ee_mode == "int":
        configure(["--set", "EmuCore/CPU/Recompiler", "EnableEE", "false"])
    else:
        configure([])
    ini_info = capture.check_ini()
    ini_at_launch = capture.ini_hashes(capture.INI)[1]

    r = ps(["-Iso", str(a.elf.resolve()), "-KeepRunning", "-FastBoot"])
    m = re.search(r"pid=(\d+)", r.stdout)
    if r.returncode != 0 or not m:
        raise SystemExit("run_pcsx2.ps1 failed:\n%s\n%s" % (r.stdout, r.stderr))
    pid = int(m.group(1))
    launch_cmd = [ln for ln in r.stdout.splitlines() if "start:" in ln]
    log("PCSX2 pid %d, ee-mode %s" % (pid, a.ee_mode))
    t0 = time.time()
    result = {"ok": False}
    try:
        p = pine.connect_retry(total=60.0)
        version = p.version()
        seen_magic = None
        while time.time() - t0 < a.timeout:
            try:
                v = p.read32(base)
            except pine.PineError:
                v = 0
            if v == magic:
                seen_magic = time.time() - t0
                break
            time.sleep(0.05)
        if seen_magic is None:
            prog = p.read32(base + 8)
            raise SystemExit("magic not seen within %.0fs (progress word %d of %d)" % (a.timeout, prog, count))
        log("magic seen %.2fs after launch; waiting for the tail marker" % seen_magic)
        tail = None
        t1 = time.time()
        while time.time() - t1 < 10.0:
            if p.read32(base + 12) == tail_magic:
                tail = time.time() - t0
                break
            time.sleep(0.05)
        progress = p.read32(base + 8)
        reported_count = p.read32(base + 4)
        log("tail marker: %s; progress %d / count %d (table says %d)" % ("seen" if tail else "MISSING", progress, count, reported_count))
        raw = read_table(p, base, table_len)
        raw2 = read_table(p, base, table_len)
        if raw != raw2:
            raise SystemExit("results table changed between two reads")
        log("read %d bytes (twice, identical)" % len(raw))
        title = p.title()
        p.close()
        result = {"ok": True, "pcsx2_version": version, "title": title, "magic_s": round(seen_magic, 3),
                  "tail_marker_seen": tail is not None, "progress": progress}
    finally:
        out = ps(["-StopPid", str(pid)])
        log(out.stdout.strip())
        if a.ee_mode == "int":
            configure(["--set", "EmuCore/CPU/Recompiler", "EnableEE", "true"])
        else:
            configure([])
        norm_after = capture.ini_hashes(capture.INI)[1]
        log("ini normalized hash after the run: %s (%s)" % (norm_after, "oracle" if norm_after == ORACLE_INI_NORMALIZED else "NOT the oracle hash"))
    if not result["ok"]:
        return 1

    vectors = []
    for vec in layout["vectors"]:
        i = vec["index"]
        buf = raw[header + i * slot_bytes: header + (i + 1) * slot_bytes]
        completed = i < result["progress"]
        obs = decode_slot(vec, buf) if completed else None
        vectors.append({"id": "%s_%04d" % (vec["family"], i), "family": vec["family"], "op": vec["op"], "form": vec["form"],
                        "risky": vec["risky"], "in": vec["in"], "obs": obs})
    run_meta = {"pcsx2_version": result["pcsx2_version"], "ee_mode": a.ee_mode,
                "ee_mode_note": "rec = EE recompiler + microVU0 macro mode (the oracle ini used for all captures); int = EE interpreter + VU0 interpreter",
                "elf": str(a.elf), "elf_sha256": hashlib.sha256(a.elf.read_bytes()).hexdigest(), "elf_title": result["title"],
                "launch": launch_cmd[0] if launch_cmd else "", "captured_at": datetime.datetime.now().astimezone().isoformat(timespec="seconds"),
                "ini_sha256_normalized_at_launch": ini_at_launch, "ini_oracle_keys": ini_info["ini_oracle_keys"],
                "magic_seen_s": result["magic_s"], "tail_marker_seen": result["tail_marker_seen"], "progress": result["progress"],
                "count": count}
    if a.merge:
        doc = json.loads(a.merge.read_text(encoding="utf-8"))
        if len(doc["vectors"]) != len(vectors):
            raise SystemExit("merge: vector count differs")
        key = "obs_" + a.ee_mode
        differ = 0
        for d, v in zip(doc["vectors"], vectors):
            if d["id"] != v["id"]:
                raise SystemExit("merge: id mismatch at " + d["id"])
            if v["obs"] != d["obs"]:
                d[key] = v["obs"]
                differ += 1
            elif key in d:
                del d[key]
        doc["runs"][a.ee_mode] = run_meta
        doc["meta"]["%s_differs_from_obs" % key] = differ
        a.out.write_text(json.dumps(doc, indent=1) + "\n", encoding="utf-8")
        log("merged %s into %s: %d vectors differ from obs" % (key, a.out, differ))
        return 0
    doc = {"meta": {"generator": meta["generator"], "generator_version": meta["generator_version"], "count": count,
                    "families": meta["families"], "safe_count": meta["safe_count"], "obs_source": "PCSX2 2.8.2, ee_mode " + a.ee_mode,
                    "value_format": "hex strings; u128 as 32 hex digits w3w2w1w0 (lane 0 = least significant)",
                    "slot_layout": "see tools/ours/eevec/gen_vectors.py and decode_slot in run_pcsx2.py"},
           "runs": {a.ee_mode: run_meta}, "vectors": vectors}
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_text(json.dumps(doc, indent=1) + "\n", encoding="utf-8")
    log("wrote %s (%d vectors, %d completed)" % (a.out, count, result["progress"]))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
