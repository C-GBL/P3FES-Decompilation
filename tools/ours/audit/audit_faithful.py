"""Driver of p3fes_audit_faithful (tests/game/audit_faithful.cmake, tests/game/test_audit_faithful.cpp).

Runs the audit over every function of game/replaced.txt in worker processes (crash and hang safe: a process that dies
or stops making progress marks its current function 'crash' / 'hang' and the run resumes after it), then writes the
per-function TSV and a summary: counts per source file (the slice) and per difference class.

  python -I tools/ours/audit/audit_faithful.py --exe build/e-audit/bin/p3fes_audit_faithful.exe --out audit.tsv
      [--jobs 3] [--seeds 16] [--snapshots dorm_replay_4900,b_5800] [--only name,name] [--timeout 120]
      [--objdir build/e-audit/game]   (functions to files by the defining object; dumpbin from tools/env.ps1)
      [--summary-only]   (re-summarise an existing --out file)
"""
import argparse
import collections
import os
import re
import subprocess
import sys
import threading
import time

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))

# Difference classes -> report groups (test_audit_faithful.cpp's header explains each class). The stack classes count
# from every pair; the others from the pairs where both runs returned (a function that differs only on runs that stop
# -- a bad pointer of a random world the original faults on and the hand version reads through -- is 'faults only').
GROUPS = [
    ("frame/spills (own frame)", {"frame"}, False),
    ("callee frames ($sp off / deeper stack)", {"deep"}, False),
    ("logic (memory, saved registers)", {"ram", "spr", "bus", "bios", "vuctl", "cp_saved", "end_saved"}, True),
    ("check-point count", {"nchk", "stop"}, True),
    ("$ra at a call", {"cp_ra", "end_ra"}, True),
    ("$v0", {"cp_v0", "end_v0"}, True),
    ("scratch GPRs", {"cp_scratch", "end_scratch"}, True),
    ("upper 64 bits of GPRs", {"cp_u128", "end_u128"}, True),
    ("HI/LO", {"cp_hilo", "end_hilo"}, True),
    ("FPRs/FCR31/ACC", {"cp_fpu", "end_fpu"}, True),
    ("VU0 / SA", {"cp_vu0", "end_vu0", "cp_sa", "end_sa"}, True),
    ("cycles only", {"cp_cycles", "end_cycles"}, True),
]
FAULTS_ONLY = "faults only (differs only on runs that stop)"
GROUP_NAMES = [g[0] for g in GROUPS] + [FAULTS_ONLY]


def primary(classes, clean):
    """The most serious group of a function's classes (the table's one-group-per-function column)."""
    for name, members, on_clean in GROUPS:
        if (clean if on_clean else classes) & members:
            return name
    return FAULTS_ONLY if classes else "?"


def list_cases(exe):
    env = dict(os.environ, P3FES_AUDIT_LIST="1")
    out = subprocess.run([exe], env=env, capture_output=True, text=True, check=False).stdout
    cases = []
    for ln in out.splitlines():
        parts = ln.split("\t")
        if len(parts) == 3 and parts[0].isdigit():
            cases.append((int(parts[0]), parts[1], parts[2]))
    return cases


def source_map(objdir=None):
    """recomp_gen symbol address -> the game/src file that defines the shim (the slice).

    With objdir (the tree's game/ object directory; dumpbin on PATH through tools/env.ps1) the object defining each
    fn_<name>_<addr8> decides; otherwise a source scan (it misses shims written through macros)."""
    m = {}
    if objdir:
        sym = re.compile(r"SECT.*External.*\?fn_\w+_([0-9a-f]{8})@recomp_gen")
        for root, _, files in os.walk(objdir):
            for f in files:
                if not f.endswith(".obj"):
                    continue
                p = os.path.join(root, f)
                rel = p.replace(os.sep, "/")
                rel = "game/src/" + rel.split("/src/", 1)[1][:-4] if "/src/" in rel else rel
                out = subprocess.run(["dumpbin", "/symbols", p], capture_output=True, text=True, check=False).stdout
                for mm in sym.finditer(out):
                    m.setdefault(int(mm.group(1), 16), rel)
        return m
    pat =re.compile(r"\bfn_\w+?_([0-9a-f]{8})\s*\(\s*(?:p3fes::)?EEContext\s*&\s*\w*\s*\)\s*\{")
    for root, _, files in os.walk(os.path.join(REPO, "game", "src")):
        for f in files:
            if not f.endswith(".cpp"):
                continue
            p = os.path.join(root, f)
            with open(p, encoding="utf-8", errors="replace") as fh:
                for mm in pat.finditer(fh.read()):
                    m.setdefault(int(mm.group(1), 16), os.path.relpath(p, REPO).replace("\\", "/"))
    return m


def run_worker(exe, indices, env_base, timeout, results, lock, log):
    """Run the exe over `indices` (sorted, contiguous chunks), resuming after crashes / hangs."""
    pending = list(indices)
    while pending:
        lo, hi = pending[0], pending[-1] + 1
        env = dict(env_base, P3FES_AUDIT_FROM=str(lo), P3FES_AUDIT_TO=str(hi))
        p = subprocess.Popen([exe], env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, bufsize=1)
        state = {"current": None, "last": time.time()}

        def read_err():
            for ln in p.stderr:
                if ln.startswith("AUDIT BEGIN "):
                    state["current"] = int(ln.split()[2])
                    state["last"] = time.time()

        t = threading.Thread(target=read_err, daemon=True)
        t.start()
        done = set()

        def read_out():
            for ln in p.stdout:
                parts = ln.rstrip("\n").split("\t")
                if len(parts) >= 11 and parts[0].isdigit():
                    with lock:
                        results[int(parts[0])] = parts
                    done.add(int(parts[0]))
                    state["last"] = time.time()

        t2 = threading.Thread(target=read_out, daemon=True)
        t2.start()
        hung = False
        while p.poll() is None:
            time.sleep(0.5)
            if time.time() - state["last"] > timeout:
                hung = True
                p.kill()
                break
        p.wait()
        t2.join(5)
        t.join(5)
        cur = state["current"]
        pending = [i for i in pending if i not in done]
        if not pending:
            break
        if cur is not None and cur in pending:
            kind = "hang" if hung else "crash"
            with lock:
                results[cur] = [str(cur), "?", "?", "?", "0", "0", "0", kind, kind, kind, f"process {kind} (exit {p.returncode})"]
            log(f"  {kind} at case {cur}")
            pending = [i for i in pending if i > cur]
        elif p.returncode != 0 and cur is None:
            log(f"  worker failed before any case (exit {p.returncode}); giving up on {len(pending)} cases")
            for i in pending:
                with lock:
                    results[i] = [str(i), "?", "?", "?", "0", "0", "0", "crash", "crash", "crash", "worker failed"]
            break
        else:
            pending = [i for i in pending if i > (cur if cur is not None else -1)]


def summarise(rows, srcmap, out):
    per_file = collections.OrderedDict()
    per_group = collections.Counter()
    per_class = collections.Counter()
    for r in rows:
        name, addr, status = r[1], r[2], r[7]
        try:
            a = int(addr, 16)
        except ValueError:
            a = -1
        f = srcmap.get(a, "?")
        d = per_file.setdefault(f, collections.Counter())
        d["functions"] += 1
        if status == "faithful":
            d["faithful"] += 1
            continue
        classes = set(r[8].split(",")) if r[8] not in ("-", "") else set()
        clean = set(r[9].split(",")) if r[9] not in ("-", "") else set()
        if status in ("crash", "hang"):
            d[status] += 1
            per_group[status] += 1
            continue
        g = primary(classes, clean)
        d["differs"] += 1
        d[g] += 1
        per_group[g] += 1
        for c in classes:
            per_class[c] += 1
    lines = []
    total = collections.Counter()
    for d in per_file.values():
        total.update(d)
    lines.append(f"functions {total['functions']}: faithful {total['faithful']}, differ {total['differs']}, crash {total['crash']}, hang {total['hang']}")
    lines.append("")
    lines.append("per difference group (each differing function counted once, under its most serious group):")
    for name in GROUP_NAMES + ["crash", "hang"]:
        if per_group[name]:
            lines.append(f"  {name:46s} {per_group[name]}")
    lines.append("")
    lines.append("per class (a function counts in every class it shows):")
    for c, n in sorted(per_class.items(), key=lambda kv: -kv[1]):
        lines.append(f"  {c:14s} {n}")
    lines.append("")
    lines.append("per source file: functions / faithful / differ  (groups)")
    for f, d in sorted(per_file.items()):
        gs = ", ".join(f"{name.split(' (')[0]} {d[name]}" for name in GROUP_NAMES if d[name])
        extra = "".join(f", {k} {d[k]}" for k in ("crash", "hang") if d[k])
        lines.append(f"  {f:44s} {d['functions']:4d} {d['faithful']:4d} {d['differs']:4d}  {gs}{extra}")
    text = "\n".join(lines) + "\n"
    with open(out, "w", encoding="utf-8") as fh:
        fh.write(text)
    return text


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--exe", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--jobs", type=int, default=3)
    ap.add_argument("--seeds", type=int, default=16)
    ap.add_argument("--snapshots", default="")
    ap.add_argument("--snapshot-seeds", type=int, default=4)
    ap.add_argument("--only", default="")
    ap.add_argument("--timeout", type=int, default=120)
    ap.add_argument("--summary-only", action="store_true")
    ap.add_argument("--objdir", default="", help="the tree's game/ object directory: files by the defining object")
    args = ap.parse_args()

    srcmap = source_map(args.objdir or None)
    if args.summary_only:
        rows = [ln.rstrip("\n").split("\t") for ln in open(args.out, encoding="utf-8") if ln[:1].isdigit()]
        print(summarise(rows, srcmap, args.out + ".summary.txt"))
        return 0
    cases = list_cases(args.exe)
    if not cases:
        print("no cases (is the exe built with the ELF?)", file=sys.stderr)
        return 1
    if args.only:
        names = set(args.only.split(","))
        cases = [c for c in cases if c[1] in names]
    env = dict(os.environ, P3FES_AUDIT_SEEDS=str(args.seeds), P3FES_AUDIT_SNAPSHOTS=args.snapshots,
               P3FES_AUDIT_SNAPSHOT_SEEDS=str(args.snapshot_seeds))
    env.pop("P3FES_AUDIT_OUT", None)
    env.pop("P3FES_AUDIT_ONLY", None)
    results = {}
    lock = threading.Lock()
    t0 = time.time()

    def log(s):
        print(s, flush=True)

    idx = [c[0] for c in cases]
    # interleaved stripes would break the contiguous FROM/TO ranges: give each worker contiguous blocks of 64
    blocks = [idx[i:i + 64] for i in range(0, len(idx), 64)]
    queue = collections.deque(blocks)

    def worker():
        while True:
            with lock:
                if not queue:
                    return
                b = queue.popleft()
            if args.only:  # non-contiguous: one process per case
                for i in b:
                    run_worker(args.exe, [i], env, args.timeout, results, lock, log)
            else:
                run_worker(args.exe, b, env, args.timeout, results, lock, log)
            with lock:
                n = len(results)
            log(f"  {n}/{len(idx)} cases, {time.time() - t0:.0f} s")

    ths = [threading.Thread(target=worker) for _ in range(max(1, args.jobs))]
    for t in ths:
        t.start()
    for t in ths:
        t.join()
    byidx = {c[0]: c for c in cases}
    rows = []
    for i in idx:
        r = results.get(i)
        if r is None:
            r = [str(i), byidx[i][1], byidx[i][2], "?", "0", "0", "0", "crash", "crash", "crash", "no result"]
        if r[1] == "?":
            r[1], r[2] = byidx[i][1], byidx[i][2]
        rows.append(r)
    with open(args.out, "w", encoding="utf-8") as fh:
        fh.write("idx\tname\taddr\tframe\tpairs\tdiffering_pairs\tstops\tstatus\tclasses\tclasses_returning\tdetails\n")
        for r in rows:
            fh.write("\t".join(r) + "\n")
    print(f"audit: {len(rows)} functions in {time.time() - t0:.0f} s")
    print(summarise(rows, srcmap, args.out + ".summary.txt"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
