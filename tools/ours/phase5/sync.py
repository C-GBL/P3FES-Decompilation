"""Merge main into a slice worktree that holds uncommitted work, keeping the work (slice.ps1 sync / final).

  python -I tools/ours/phase5/sync.py --repo <worktree> --slice <slice> [--log <file>]

The shared files a slice only appends to (game/replaced.txt, game/CMakeLists.txt, tests/game/CMakeLists.txt,
game/README.md, docs/INTEGRATION_LOG.md) are saved as their diff against HEAD and reset; `git merge --no-edit main`
runs (untracked slice files are untouched; a merge that would overwrite one, or a conflict, is aborted and everything
restored); then each added block is put back after its context lines in the merged file (lists are unions). Rows of
the slice that main now replaces are removed from replaced.txt and the slice's _replaced block; their definitions and
tests must then be deleted by hand: they are listed, exit code 3. Exit 0 = merged (or already up to date), 1 = failed.
Afterwards forwarders.py moves any recomp_gen forwarder the slice's sources still hold into the generated list.
"""
import argparse
import os
import re
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import p5common as P  # noqa: E402
import wire  # noqa: E402

SHARED = ["game/replaced.txt", "game/CMakeLists.txt", "tests/game/CMakeLists.txt", "game/README.md", "docs/INTEGRATION_LOG.md"]


def git(repo, *a):
    return subprocess.run(["git", "-C", repo] + list(a), capture_output=True, text=True)


def hunks(diff):
    """[(old_start, [(' '|'-'|'+', text)])] of a unified diff."""
    out, cur = [], None
    for ln in diff.splitlines():
        m = re.match(r"@@ -(\d+)(?:,\d+)? \+\d+(?:,\d+)? @@", ln)
        if m:
            cur = (int(m.group(1)), [])
            out.append(cur)
        elif cur is not None and ln[:1] in (" ", "-", "+") and not ln.startswith(("+++", "---")):
            cur[1].append((ln[0], ln[1:]))
        elif ln.startswith("\\"):
            continue
    return out


def reapply(lines, hs, nold):
    """Insert every added run of the hunks into `lines` (the merged file) after its context; [problems]."""
    problems = []
    plans = []
    for start, body in hs:
        old_idx = start - 1 if start else 0
        before = []
        i = 0
        while i < len(body):
            k, t = body[i]
            if k == "+":
                run = []
                while i < len(body) and body[i][0] == "+":
                    run.append(body[i][1])
                    i += 1
                after = [t2 for k2, t2 in body[i:] if k2 != "+"][:3]
                plans.append((before[-3:], run, after, old_idx))
                continue
            if k == "-":
                problems.append("a removed line (append-only file): %r" % t[:60])
            before.append(t)
            old_idx += 1
            i += 1
    for before, run, after, old_idx in reversed(plans):  # bottom up: earlier insert points stay valid
        pos = find(lines, before, after, old_idx, nold)
        if pos is None:
            problems.append("no anchor for %d added lines (appended at the end): %r" % (len(run), run[0][:60]))
            pos = len(lines)
            while pos and not lines[pos - 1].strip():
                pos -= 1
        lines[pos:pos] = run
    return problems


def find(lines, before, after, old_idx, nold):
    want = old_idx / max(1, nold) * len(lines)
    for ctx in (before, before[-1:]):
        if ctx:
            hits = [i + len(ctx) for i in range(len(lines) - len(ctx) + 1) if lines[i:i + len(ctx)] == ctx]
            if hits:
                return min(hits, key=lambda h: abs(h - want))
    for ctx in (after, after[:1]):
        if ctx:
            hits = [i for i in range(len(lines) - len(ctx) + 1) if lines[i:i + len(ctx)] == ctx]
            if hits:
                return min(hits, key=lambda h: abs(h - want))
    if not before and not after:
        return len(lines)
    return None


def strip_forwarders(repo):
    """Since 2026-10-29 the recomp_gen forwarders are generated (game/forwarders.cmake): move any a slice's sources
    still hold (written by an older p3fes_handgen) out, so the tree links (tools/ours/phase5/forwarders.py)."""
    tool = os.path.join(repo, "tools", "ours", "phase5", "forwarders.py")
    if not os.path.exists(os.path.join(repo, "game", "forwarders.cmake")) or not os.path.exists(tool):
        return
    r = subprocess.run([sys.executable, "-I", tool, "--repo", repo], capture_output=True, text=True)
    for ln in (r.stdout + r.stderr).strip().splitlines()[:3]:
        print("  " + ln)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", required=True)
    ap.add_argument("--slice", required=True)
    a = ap.parse_args()
    repo, s = a.repo, a.slice
    if git(repo, "merge-base", "--is-ancestor", "main", "HEAD").returncode == 0:
        print("sync: main is already merged (HEAD %s)" % git(repo, "rev-parse", "--short", "HEAD").stdout.strip())
        strip_forwarders(repo)
        return drop_main_rows(repo, s)
    backup = os.path.join(repo, "build", "slice-logs", "sync_backup")
    os.makedirs(backup, exist_ok=True)
    saved = {}
    for f in SHARED:
        d = git(repo, "diff", "HEAD", "-U3", "--", f).stdout
        if d.strip():
            saved[f] = (d, len(wire.load(os.path.join(repo, f))[0]))
            shutil.copy2(os.path.join(repo, f), os.path.join(backup, f.replace("/", "_")))
    for f in saved:
        git(repo, "checkout", "HEAD", "--", f)
    r = git(repo, "merge", "--no-edit", "main")
    if r.returncode != 0:
        git(repo, "merge", "--abort")
        for f in saved:
            shutil.copy2(os.path.join(backup, f.replace("/", "_")), os.path.join(repo, f))
        msg = (r.stdout + r.stderr).strip().splitlines()
        print("sync: FAILED, git merge main refused or conflicted (work restored): " + " | ".join(msg[-3:]))
        return 1
    problems = []
    for f, (d, nold) in saved.items():
        lines, nl = wire.load(os.path.join(repo, f))
        problems += ["%s: %s" % (f, p) for p in reapply(lines, hunks(d), nold)]
        wire.save(os.path.join(repo, f), lines, nl)
    print("sync: merged main %s into %s; re-applied %d shared files (backup %s)" %
          (git(repo, "rev-parse", "--short", "main").stdout.strip(), git(repo, "rev-parse", "--abbrev-ref", "HEAD").stdout.strip(),
           len(saved), backup))
    for p in problems[:5]:
        print("  CHECK " + p)
    strip_forwarders(repo)
    rc = drop_main_rows(repo, s)
    return 1 if problems else rc


def drop_main_rows(repo, s):
    """Remove the slice's rows that main's replaced.txt lists too (and their _replaced entries); list their definitions."""
    main_rows = {r[0] for r in P.replaced_rows(P.git(P.MAIN, "show", "main:game/replaced.txt"))}
    rp = os.path.join(repo, "game", "replaced.txt")
    lines, nl = wire.load(rp)
    blk = wire.slice_block(lines, s)
    if blk is None:
        return 0
    drop = []
    for i in range(blk[1], blk[0], -1):
        t = lines[i].strip()
        if t.lower().startswith("0x") and int(t.split()[0], 16) in main_rows:
            drop.append(t)
            del lines[i]
    if not drop:
        print("sync: no row of the slice is on main")
        return 0
    wire.save(rp, lines, nl)
    tp = os.path.join(repo, "tests", "game", "CMakeLists.txt")
    tl, tnl = wire.load(tp)
    gone = {d.split()[0].lower() for d in drop}
    b = next((i for i, ln in enumerate(tl) if re.match(r"\s*# %s slice\b" % re.escape(s), ln)), None)
    e = next((i for i in range(b or 0, len(tl)) if re.match(r"\s*# end %s\b" % re.escape(s), tl[i])), None) if b is not None else None
    for i, ln in enumerate(tl):
        if b is None or e is None or not (b < i < e):
            continue  # only the slice's own block
        if "APPEND _replaced" in ln and ln.strip().startswith("string("):
            m = re.search(r'"(,[^"]*)"', ln)
            if m and any(x in gone for x in m.group(1).split(",")):
                keep = [x for x in m.group(1).split(",") if x and x not in gone]
                tl[i] = ln.replace(m.group(1), "," + ",".join(keep)) if keep else None
    wire.save(tp, [ln for ln in tl if ln is not None], tnl)
    print("sync: dropped %d rows main now replaces: %s" % (len(drop), " ".join(d.split()[1] for d in drop[:12])))
    print("  delete their definitions (game::<name>, the fn_<name>_<addr8> shim) and their test rows, then rebuild")
    return 3


if __name__ == "__main__":
    sys.exit(main())
