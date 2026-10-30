"""Open/create the IDA database for SLUS_216.21 with the R5900 (EE) processor.

Usage (venv python, `import idapro` must be first):
  python open_p3fes.py <elf> <out.i64> [--probe] [--log PATH]

  --probe   open without auto-analysis, print processor/segments, close WITHOUT saving
            (used to confirm the -p switch before the long analysis)
Behaviour:
  * If <out.i64> exists it is opened as-is (no re-analysis), else the ELF is loaded with
    `-pr5900l -o<out.i64>` and auto-analysis runs to completion (ida_auto.auto_wait).
  * If idalib ignores -o the database is moved next to <out.i64> afterwards.
  * Re-runnable; progress + timings go to the log file (default ida/logs/open.log).
"""
import idapro  # noqa: F401  -- must be the first import
import argparse, os, shutil, sys, time, hashlib

ap = argparse.ArgumentParser()
ap.add_argument("elf")
ap.add_argument("out_i64")
ap.add_argument("--probe", action="store_true")
ap.add_argument("--log", default=None)
a = ap.parse_args()

elf = os.path.abspath(a.elf)
out = os.path.abspath(a.out_i64)
log_path = a.log or os.path.join(os.path.dirname(out), "logs", "open.log")
os.makedirs(os.path.dirname(log_path), exist_ok=True)
logf = open(log_path, "a", encoding="utf-8")
T0 = time.time()

def log(msg):
    line = f"[{time.strftime('%H:%M:%S')} +{time.time()-T0:7.1f}s] {msg}"
    print(line, flush=True)
    logf.write(line + "\n"); logf.flush()

def sha256(p):
    h = hashlib.sha256()
    with open(p, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()

log(f"elf={elf} sha256={sha256(elf)}")
idapro.enable_console_messages(False)

existing = os.path.exists(out) and not a.probe
if existing:
    log(f"opening existing database {out}")
    rc = idapro.open_database(out, False)
else:
    args = f"-pr5900l -o{out}"
    log(f"loading ELF with args: {args} (auto-analysis={'no' if a.probe else 'yes'})")
    rc = idapro.open_database(elf, False, args)
log(f"open_database rc={rc}")
if rc != 0:
    sys.exit(rc)

import ida_ida, ida_segment, ida_nalt, ida_auto, ida_funcs, ida_loader, idc

log(f"procname={ida_ida.inf_get_procname()} be={ida_ida.inf_is_be()} "
    f"min_ea={ida_ida.inf_get_min_ea():#x} max_ea={ida_ida.inf_get_max_ea():#x} "
    f"start_ea={ida_ida.inf_get_start_ea():#x} idb={idc.get_idb_path()}")
for i in range(ida_segment.get_segm_qty()):
    s = ida_segment.getnseg(i)
    log(f"  seg {ida_segment.get_segm_name(s):10s} {s.start_ea:#010x}-{s.end_ea:#010x} "
        f"size={s.size():#x} perm={s.perm} type={s.type} bitness={s.bitness}")

if a.probe:
    log("probe: closing without save")
    idapro.close_database(False)
    sys.exit(0)

if not existing:
    log("auto-analysis: waiting ...")
    ida_auto.auto_wait()
    log(f"auto-analysis done; functions={ida_funcs.get_func_qty()}")

idb_before = idc.get_idb_path()
log(f"saving database (idb path reported by IDA: {idb_before})")
idapro.close_database(True)
if os.path.exists(out):
    log(f"OK database at {out} size={os.path.getsize(out)}")
else:
    # -o ignored: look for the i64 next to the ELF or at IDA's reported path
    cands = [idb_before, os.path.splitext(elf)[0] + ".i64", elf + ".i64"]
    for c in cands:
        if c and os.path.exists(c):
            shutil.move(c, out)
            log(f"MOVED {c} -> {out} (idalib ignored -o) size={os.path.getsize(out)}")
            break
    else:
        log("ERROR: no database produced"); sys.exit(2)
