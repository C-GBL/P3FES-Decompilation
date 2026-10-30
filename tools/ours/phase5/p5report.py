"""Short summaries of slice.ps1's logs (each prints a few lines; the full logs stay on disk).

  p5report.py names <list file> <functions.json>        -> name,name,... (for audit --only)
  p5report.py build <log>                               -> the first distinct compiler / linker errors
  p5report.py doctest <log>                             -> case / assertion counts, failing cases + first error
  p5report.py audit <tsv>                               -> the verdict line, the non-faithful functions
  p5report.py gate <log>                                -> the gate's verdict lines
  p5report.py report <repo> <slice> <packet.json>       -> the counts block of the slice report
"""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import wire  # noqa: E402


def read(p):
    return open(p, encoding="utf-8", errors="replace").read() if os.path.exists(p) else ""


def names(lst, fj):
    fn = {int(f["a"], 16): f["n"] for f in json.load(open(fj, encoding="utf-8"))}
    out = []
    for ln in open(lst, encoding="utf-8"):
        ln = ln.split("#", 1)[0].strip()
        if ln:
            out.append(fn.get(int(ln.split()[0], 16), ln))
    print(",".join(out))


ERR = re.compile(r"(error C\d+|error LNK\d+|fatal error|: error:|error: |FAILED: |CMake Error)", re.I)


def build(log, n=5):
    seen, out = set(), []
    for ln in read(log).splitlines():
        if ERR.search(ln) and "warning" not in ln.lower()[:40]:
            key = re.sub(r"\(\d+\)|:\d+:\d+", "", ln.strip())[:160]
            if key not in seen:
                seen.add(key)
                out.append(ln.strip()[:200])
    for ln in out[:n]:
        print("  " + ln)
    if len(out) > n:
        print("  (+%d more distinct error lines)" % (len(out) - n))


def doctest(log, n=6):
    text = read(log)
    cases = re.findall(r"\[doctest\] test cases:\s*(\d+)\s*\|\s*(\d+) passed\s*\|\s*(\d+) failed(?:\s*\|\s*(\d+) skipped)?", text)
    asserts = re.findall(r"\[doctest\] assertions:\s*(\d+)\s*\|\s*(\d+) passed\s*\|\s*(\d+) failed", text)
    if cases:
        c, a = cases[-1], asserts[-1] if asserts else ("?", "?", "?")
        print("cases %s | %s passed | %s failed; assertions %s | %s passed | %s failed" % (c[0], c[1], c[2], a[0], a[1], a[2]))
    else:
        tail = [ln for ln in text.splitlines() if ln.strip()][-2:]
        print("no doctest summary (crashed or did not start): " + " | ".join(t[:120] for t in tail))
    fails = []
    for blk in re.split(r"^={20,}\s*$", text, flags=re.M):
        m = re.search(r"TEST CASE:\s*(.+)", blk)
        e = re.search(r"^.*(ERROR|FATAL ERROR|exception|CRASHED).*$", blk, re.M)
        if m and e:
            fails.append("%s: %s" % (m.group(1).strip()[:70], e.group(0).strip()[-130:]))
    for f in fails[:n]:
        print("  FAIL " + f)
    if len(fails) > n:
        print("  (+%d more failing cases)" % (len(fails) - n))


def audit(tsv, n=8):
    rows = [ln.rstrip("\n").split("\t") for ln in open(tsv, encoding="utf-8") if ln[:1].isdigit()] if os.path.exists(tsv) else []
    if not rows:
        print("audit: no rows (%s)" % tsv)
        return
    bad = [r for r in rows if r[7] != "faithful"]
    print("audit: %d functions, %d faithful, %d not" % (len(rows), len(rows) - len(bad), len(bad)))
    for r in bad[:n]:
        print("  %s %s %s: %s" % (r[1], r[2], r[7], (r[8] + " " + r[10])[:120]))
    if len(bad) > n:
        print("  (+%d more, %s)" % (len(bad) - n, tsv))


def gate(log):
    """One line per route (exit, frame vs expected, eeMemory bytes, gsMemory), the suites, the verdict."""
    text = read(log)
    exp = dict(re.findall(r"(\w+) ([0-9A-F]{16})\.\.\.", text.split("expected frames:", 1)[1].splitlines()[0])) if "expected frames:" in text else {}
    routes, cur = {}, None
    for ln in text.splitlines():
        m = re.match(r"^(dorm|m1|battle|fusion|shop|climb)\s+exit (-?\d+)\s+([\d.]+) s", ln)
        if m:
            cur = m.group(1)
            routes[cur] = {"exit": m.group(2), "s": m.group(3)}
            continue
        m = re.match(r"^(dorm|m1|battle|fusion|shop|climb)\s+frame ([0-9A-F]+)", ln)
        if m:
            routes.setdefault(m.group(1), {})["frame"] = m.group(2)
            cur = m.group(1)
            continue
        if cur and "differing bytes" in ln:
            routes[cur]["ee"] = re.search(r"differing bytes: (\d+)", ln).group(1) if re.search(r"differing bytes: (\d+)", ln) else "?"
        if cur and "gsMemory" in ln:
            routes[cur]["gs"] = ln.split("gsMemory", 1)[1].strip()
        if re.match(r"^\S+: no frame\.png", ln):
            routes.setdefault(ln.split(":")[0], {})["frame"] = "none"
    for ln in text.splitlines():
        if re.match(r"^(build msvc|emit|ctest \w+|pair tests|BUILD:|ABORT)", ln):
            print("  " + ln.strip()[:150])
    for r, v in routes.items():
        fr = v.get("frame", "?")
        ok = "ok" if exp.get(r) and fr.startswith(exp[r]) else ("DIFFERS" if exp.get(r) else "?")
        print("  %-6s exit %s %ss frame %s %s, eeMemory %s bytes, gsMemory %s" % (
            r, v.get("exit", "?"), v.get("s", "?"), fr[:8], ok, v.get("ee", "?"), v.get("gs", "?")))
    v = re.findall(r"^GATE: \w+", text, re.M)
    print("  " + (v[-1] if v else "GATE: no verdict (see the log)"))


def report(repo, s, pjp):
    import subprocess
    pj = json.load(open(pjp, encoding="utf-8"))
    g = lambda *a: subprocess.run(["git", "-C", repo] + list(a), capture_output=True, text=True).stdout.strip()  # noqa: E731
    print("branch %s, commit %s" % (g("rev-parse", "--abbrev-ref", "HEAD"), g("log", "-1", "--format=%h %s")[:90]))
    lines, _ = wire.load(os.path.join(repo, "game", "replaced.txt"))
    blk = wire.slice_block(lines, s)
    mine = [int(ln.split()[0], 16) for ln in lines[blk[0]:blk[1] + 1] if ln.strip().lower().startswith("0x")] if blk else []
    fn = {int(f["a"], 16): (f["n"], f["s"]) for f in json.load(open(os.path.join(repo, "symbols", "functions.json"), encoding="utf-8"))}
    lst = [int(ln.split()[0], 16) for ln in open(pj["list"], encoding="utf-8") if ln.strip() and not ln.startswith("#")]
    missing = [fn.get(x, ("0x%X" % x,))[0] for x in lst if x not in set(mine)]
    print("functions: %d replaced (%d bytes); packet list %d; not taken %d%s" % (
        len(mine), sum(fn.get(x, ("", 0))[1] for x in mine), len(lst), len(missing),
        (": " + " ".join(missing[:10]) + (" ..." if len(missing) > 10 else "")) if missing else ""))
    logs = os.path.join(repo, "build", "slice-logs")
    for tag, f in (("pair tests MSVC", "test.log"), ("pair tests clang-cl", "clang-test.log")):
        m = re.findall(r"\[doctest\] test cases:.*|\[doctest\] assertions:.*", read(os.path.join(logs, f)))
        print("%s: %s" % (tag, " / ".join(x.replace("[doctest] ", "") for x in m[-2:]) or "not run"))
    t = os.path.join(logs, "audit.tsv")
    if os.path.exists(t):
        audit(t, n=4)
    else:
        print("audit: not run")
    gl = os.path.join(logs, "gate.log")
    if os.path.exists(gl):
        print("gate (%s):" % gl)
        gate(gl)
    else:
        print("gate: not run (slice.ps1 final)")


if __name__ == "__main__":
    cmd = sys.argv[1]
    if cmd == "names":
        names(sys.argv[2], sys.argv[3])
    elif cmd == "build":
        build(sys.argv[2])
    elif cmd == "doctest":
        doctest(sys.argv[2])
    elif cmd == "audit":
        audit(sys.argv[2])
    elif cmd == "gate":
        gate(sys.argv[2])
    elif cmd == "report":
        report(sys.argv[2], sys.argv[3], sys.argv[4])
