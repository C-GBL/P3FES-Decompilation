"""Make a Phase 5 slice's work packet: the functions to take, their callees, what to reuse, the test set -- so a slice
agent does no discovery (docs/PHASE5_QUICK.md).

  python -I tools/ours/phase5/make_packet.py <slice> [--range 0x3D0000-0x3E0000 ...] [--candidates 0x..,0x.. | @file]
         [--target 150] [--continue <worktree>] [--planned @file] [--allow iop,sound,cd,adxf,rofs,hw,syscall,cop0]
         [--area battle] [--desc "..."] [--force] [--blocked-report]

Writes F:/P3FES-PORT/lead/packets/<slice>/: packet.md (<= ~4k tokens), <slice>.txt (the slice list), claims.txt (what
this slice owns; every other packet skips it), packet.json (for slice.ps1), functions.tsv and excluded.tsv (details).

Filters, all exact, in this order (the first that applies is the reason): main's game/replaced.txt; another packet's
claims.txt; a test comment that says it stays recompiled (standins.py "held"); in the own body a hardware-register
load / store, a syscall or a COP0 instruction (the ELF words over symbols/function_chunks.txt); a direct call of SIF /
IOP RPC, the sound driver (sceSd / sceSk / sceSpu2), sceCd, ADXF or ROFS (by callee name); a mid-body entry
(p3fes_handgen refuses it, exactly as the emitter does).
Not a filter since 2026-10-29: a function a test stands in (a recorder / custom stand-in in any tests/game file of
main), names as a literal (a stop_pc / callee check) or had served by a stand-in in a suite run (absent.txt). The test
build's forwarder of a replaced function asks the installed stand-ins first (recomp/README.md "Forwarders"), so the
stand-in keeps serving it after the slice replaces it. packet.md lists those tests per function ("Tests that stand
them in"): the slice runs them. Order: reached on a replay route first (the
first-call probes earlier slices saved in their scratch folders), by call count, then by caller count (IDA export
header: callers + data refs), then address; the chosen functions are listed in address order (the work order).
Callees: the p3fes_handgen bodies (the emitter's CFG: every jal / tail j), so they are what the body calls.
"""
import argparse
import collections
import datetime
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import p5common as P  # noqa: E402
import standins  # noqa: E402

AUDIT_SNAPSHOTS = ["dorm_replay_4900", "b_5800", "climb_ref_17000"]
ROUTE_SNAPSHOTS = {"fusion": "fusion_ref_6300", "shop": "shop_ref_4100"}
SKIP_CLASSES = ("hw", "syscall", "cop0", "iop", "sound", "cd", "adxf", "rofs")


def short(a, names):
    n = names.get(a, ("", 0))[0]
    return "%x" % a if not n or n == "sub_%X" % a else "%x:%s" % (a, n[:22])


def role_of(a, names, facts):
    n = names[a][0]
    if n and not n.startswith(("sub_", "nullsub_")):
        return n[:28]
    if facts:
        cs = [s for s in facts["strings"] if s.endswith(".c")] or facts["strings"]
        if cs:
            return '"%s"' % cs[0].replace("\\n", "").strip()[:26]
        named = [c for c in facts["caller_names"] if not c.startswith(("sub_", "nullsub_"))]
        if named:
            return "<-" + named[0][:26]
    return "-"


def source_map(sha):
    """{addr: game/src file} of every hand-written shim on main (cached per main commit)."""
    cp = os.path.join(P.CACHE, "srcmap_%s.json" % sha[:12])
    if os.path.exists(cp):
        return {int(k, 16): v for k, v in json.load(open(cp, encoding="utf-8")).items()}
    out = P.git(P.MAIN, "grep", "-o", "-E", r"fn_[A-Za-z0-9_]+_[0-9a-f]{8} ?\((p3fes::)?EEContext ?& ?[a-z]*\) ?\{",
                sha, "--", "game/src", check=False)
    m = {}
    for ln in out.splitlines():
        parts = ln.split(":", 2)
        if len(parts) < 3:
            continue
        x = re.search(r"_([0-9a-f]{8}) ?\(", parts[2])
        if x:
            m.setdefault(int(x.group(1), 16), parts[1])
    json.dump({"0x%X" % k: v for k, v in m.items()}, open(cp, "w", encoding="utf-8"))
    return m


def header_of(src, sha, cache={}):
    """The slice header a game/src file includes (the include whose name prefixes the file's), or ''."""
    if src in cache:
        return cache[src]
    text = P.git(P.MAIN, "show", "%s:%s" % (sha, src), check=False)
    incs = re.findall(r'#include "p3fes/game/([^"]+\.h)"', text)
    base = os.path.basename(src).rsplit(".", 1)[0]
    pick = [i for i in incs if base.startswith(i[:-2].split("/")[-1])] or [i for i in incs if i not in ("hg_cpu.h", "guest.h")]
    cache[src] = ("p3fes/game/" + pick[-1]) if pick else ""
    return cache[src]


def wip_state(wt):
    """What a paused worktree's uncommitted diff holds."""
    st = {"wt": wt}
    st["branch"] = P.git(wt, "rev-parse", "--abbrev-ref", "HEAD").strip()
    st["head"] = P.git(wt, "rev-parse", "--short", "HEAD").strip()
    st["behind"] = P.git(wt, "rev-list", "--count", "HEAD..main").strip()
    st["status"] = [ln for ln in P.git(wt, "status", "--porcelain").splitlines() if ln.strip()]
    diff = P.git(wt, "diff", "HEAD", "--unified=0", "--", "game/replaced.txt")
    rows, hdr = [], []
    for ln in diff.splitlines():
        if ln.startswith("+") and not ln.startswith("+++"):
            s = ln[1:].strip()
            if s.startswith("#"):
                hdr.append(s)
            elif s.lower().startswith("0x"):
                p = s.split()
                rows.append((int(p[0], 16), p[1] if len(p) > 1 else ""))
    st["rows"], st["row_header"] = rows, " ".join(hdr)[:300]
    files = []
    for ln in st["status"]:
        code, path = ln[:2], ln[3:].strip().strip('"')
        full = os.path.join(wt, path)
        if os.path.isdir(full):
            for root, _, fs in os.walk(full):
                files += [(code, os.path.relpath(os.path.join(root, f), wt).replace("\\", "/")) for f in fs]
        else:
            files.append((code, path))
    st["files"] = files
    defs, tests = {}, {}
    for code, path in files:
        full = os.path.join(wt, path)
        if not os.path.exists(full):
            continue
        if path.startswith("game/src/") and path.endswith(".cpp"):
            txt = P.read_text(full)
            for m in re.finditer(r"fn_\w+_([0-9a-f]{8})\s*\(\s*(?:p3fes::)?EEContext\s*&\s*\w*\s*\)\s*\{", txt):
                defs.setdefault(int(m.group(1), 16), path)
        if path.startswith("tests/game/test_") and path.endswith(".cpp"):
            txt = P.read_text(full)
            tests[path] = (len(re.findall(r"\bTEST_CASE\s*\(", txt)), txt)
    st["defs"], st["tests"] = defs, tests
    return st


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("slice")
    ap.add_argument("--range", action="append", default=[])
    ap.add_argument("--candidates", default="")
    ap.add_argument("--target", type=int, default=0, help="functions to take (default 150; --continue: all remaining)")
    ap.add_argument("--continue", dest="cont", default="")
    ap.add_argument("--planned", default="", help="--continue: the slice's planned list (default <scratch>/<slice>/<slice>.txt)")
    ap.add_argument("--allow", default="", help="skip classes this slice may take: " + ",".join(SKIP_CLASSES))
    ap.add_argument("--area", default="")
    ap.add_argument("--desc", default="")
    ap.add_argument("--handgen", default="")
    ap.add_argument("--force", action="store_true", help="overwrite this slice's existing packet")
    ap.add_argument("--blocked-report", action="store_true", help="also count game code blocked only by stand-ins")
    a = ap.parse_args()
    s = a.slice
    out_dir = os.path.join(P.PACKETS, s)
    if os.path.exists(os.path.join(out_dir, "claims.txt")) and not a.force:
        print("packet %s exists (claims.txt); --force to remake it" % out_dir)
        return 2
    allow = {x.strip() for x in a.allow.split(",") if x.strip()}
    sha = P.main_sha()
    sym = P.tmpdir("sym_" + sha[:12])
    for f in ("functions.json", "function_chunks.txt", "jumptables.json", "p3fes.sym"):
        dst = os.path.join(sym, f)
        if not os.path.exists(dst):
            open(dst, "wb").write(open(P.main_file("symbols/" + f), "rb").read())
    names = P.load_functions(os.path.join(sym, "functions.json"))
    chunks = P.load_chunks(os.path.join(sym, "function_chunks.txt"))
    rep_rows = P.replaced_rows(P.read_text(P.main_file("game/replaced.txt")))
    replaced = {r[0] for r in rep_rows}
    tcm = P.read_text(P.main_file("tests/game/CMakeLists.txt"))
    emitted = P.cmake_hex_list(tcm, "_callees") | P.cmake_hex_list(tcm, "_replaced")
    si = standins.build()
    stood = standins.addresses(si)
    held = {int(k, 16): v for k, v in si.get("held", {}).items()}  # "stays recompiled" comments: still a filter
    tested = standins.tested(si)  # stood in / named / served: reported, not a filter (the hooked forwarders)
    claims = P.other_claims(s)
    reach, reach_files = P.load_reach(names)
    elf = P.Elf()
    handgen = a.handgen or P.find_handgen()
    if not handgen:
        print("no p3fes_handgen.exe newer than recomp/src/handgen*.cpp under %s\\build\\*\\bin: build one (slice.ps1 build)" % P.MAIN)
        return 1

    # ---- the universe ----
    wip = wip_state(a.cont) if a.cont else None
    uni = []
    for r in a.range:
        lo, hi = (int(x, 16) for x in r.split("-"))
        uni += [x for x in names if lo <= x < hi]
    if a.candidates:
        uni += P.parse_addr_list(a.candidates)
    planned_src = ""
    if wip:
        pl = a.planned[1:] if a.planned.startswith("@") else a.planned
        pl = pl or os.path.join(P.SCRATCH, s, s + ".txt")
        if os.path.exists(pl):
            uni += P.parse_addr_list("@" + pl)
            planned_src = pl
        done = {x for x, _ in wip["rows"]}
        uni = [x for x in uni if x not in done]
    uni = [x for x in dict.fromkeys(uni) if x in names]

    reason, cat = {}, {}
    def drop(x, c, why):
        if x not in reason:
            reason[x], cat[x] = why, c

    body = {}
    for x in uni:
        if x in replaced:
            drop(x, "replaced", "replaced on main")
        elif x in claims:
            drop(x, "claimed", "claimed by packet " + claims[x])
        elif x in held:
            drop(x, "held by a test comment", held[x][0])
        else:
            rngs, data = chunks.get(x, ([(x, x + names[x][1])], set()))
            flags, targets, jalr = P.scan_body(elf, rngs, data)
            body[x] = (flags, jalr)
            for k in ("hw", "syscall", "cop0"):
                if k in flags and k not in allow:
                    drop(x, k, "%s" % flags[k])
                    break
            else:
                for t in sorted(targets):
                    cls = P.callee_class(names.get(t, ("", 0))[0])
                    if cls and cls not in allow:
                        drop(x, "calls " + cls, names[t][0])
                        break
    alive = [x for x in uni if x not in reason]
    work = P.tmpdir(s)
    callees, refused, _ = P.run_handgen(handgen, sym, alive, work) if alive else ({}, {}, 0)
    for x in alive:
        if x in refused:
            drop(x, "mid-body", "p3fes_handgen: " + refused[x][:60])
        elif x not in callees:
            drop(x, "not generated", "p3fes_handgen gave no body")
    alive = [x for x in alive if x not in reason]

    facts = {x: P.pseudo_facts(x, names[x][0]) for x in alive}
    def prio(x):
        r = reach.get(x, (0, set()))
        f = facts.get(x) or {"callers": 0, "data_refs": 0}
        return (0 if r[0] else 1, -r[0], -(f["callers"] + f["data_refs"]), x)
    ranked = sorted(alive, key=prio)
    target = a.target or (len(ranked) if wip else 150)
    chosen = sorted(ranked[:target])
    for x in ranked[target:]:
        drop(x, "over target", "over the target (%d)" % target)
    chosen_set = set(chosen)

    # ---- reuse: headers of the replaced callees, named records, type deltas ----
    srcmap = source_map(sha)
    hdr_count, area_count = collections.Counter(), collections.Counter()
    all_callees = set()
    for x in chosen:
        for c in callees.get(x, []):
            all_callees.add(c)
            if c in replaced and c in srcmap:
                h = header_of(srcmap[c], sha)
                if h:
                    hdr_count[h] += 1
    for x in chosen:  # the area: where the replaced neighbours live
        near = [y for y in srcmap if abs(y - x) < 0x8000]
        for y in near[:40]:
            parts = srcmap[y].split("/")
            if len(parts) > 3:
                area_count[parts[2]] += 1
    area = a.area or (area_count.most_common(1)[0][0] if area_count else "sweep")
    types = json.load(open(P.main_file("tools/ours/types/types.json"), encoding="utf-8"))
    cls_name = {c["id"]: c.get("name", "") for c in types["classes"]}
    rec_count = collections.Counter()
    for x in chosen:
        tf = types["functions"].get("0x%X" % x)
        if not tf:
            continue
        for i, cid in enumerate(tf.get("p", [])):
            n = cls_name.get(cid, "") if cid is not None else ""
            if n and not n.startswith("type_"):
                rec_count["%s ($%s)" % (n, ["a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3"][i] if i < 8 else i)] += 1
        n = cls_name.get(tf.get("r"), "") if tf.get("r") is not None else ""
        if n and not n.startswith("type_"):
            rec_count["%s ($v0)" % n] += 1
    rec_names = {k.split(" ")[0] for k in rec_count}
    deltas = []
    for ln in P.git(P.MAIN, "ls-tree", "--name-only", sha, "tools/ours/types/deltas/").splitlines():
        try:
            d = json.loads(P.git(P.MAIN, "show", "%s:%s" % (sha, ln)))
        except ValueError:
            continue
        hit = 0
        for r in d.get("records", []):
            anchors = {int(an["fn"], 16) for an in r.get("anchors", []) if "fn" in an}
            if r.get("name") in rec_names or anchors & (chosen_set | all_callees):
                hit += 1
        if hit:
            deltas.append((hit, ln))
    deltas.sort(reverse=True)
    rec_hdr = {}
    if rec_names:
        g = P.git(P.MAIN, "grep", "-n", "-E", r"^struct (%s)\b" % "|".join(sorted(rec_names)), sha, "--",
                  "game/include/p3fes/game/types", check=False)
        for ln in g.splitlines():
            parts = ln.split(":", 3)
            m = re.match(r"struct (\w+)", parts[3]) if len(parts) > 3 else None
            if m:
                rec_hdr.setdefault(m.group(1), parts[1].replace("game/include/", ""))

    # ---- write ----
    os.makedirs(out_dir, exist_ok=True)
    routes = set()
    for x in chosen:
        routes |= reach.get(x, (0, set()))[1]
    snaps = AUDIT_SNAPSHOTS + [ROUTE_SNAPSHOTS[r] for r in sorted(routes) if r in ROUTE_SNAPSHOTS]
    done_rows = [x for x, _ in wip["rows"]] if wip else []
    dropped_done = {}
    if wip:
        for x in done_rows:
            if x in replaced:
                dropped_done[x] = "main replaces it now (slice.ps1 sync drops the row; delete its definition and test)"
            elif x in claims:
                dropped_done[x] = "claimed by packet " + claims[x]
    keep_done = [x for x in done_rows if x not in dropped_done]
    slice_list = sorted(set(keep_done) | chosen_set)
    with open(os.path.join(out_dir, s + ".txt"), "w", newline="\n") as f:
        f.write("# slice %s: %d functions (main %s)\n" % (s, len(slice_list), sha[:8]))
        f.writelines("0x%X\n" % x for x in slice_list)
    with open(os.path.join(out_dir, s + ".gen.txt"), "w", newline="\n") as f:
        f.write("# slice %s: the %d functions slice.ps1 gen generates\n" % (s, len(chosen)))
        f.writelines("0x%X\n" % x for x in chosen)
    with open(os.path.join(out_dir, "claims.txt"), "w", newline="\n") as f:
        f.write("# claims of slice %s (main %s, %s): no other packet takes these\n" % (s, sha[:8], datetime.date.today()))
        f.writelines("0x%X\n" % x for x in slice_list)
    with open(os.path.join(out_dir, "functions.tsv"), "w", newline="\n") as f:
        f.write("addr\tname\tsize\tcallers\tdata_refs\treach\troutes\tjalr\tcallees\ttests\n")
        for x in chosen:
            fc = facts.get(x) or {"callers": 0, "data_refs": 0}
            r = reach.get(x, (0, set()))
            f.write("0x%X\t%s\t%d\t%d\t%d\t%d\t%s\t%d\t%s\t%s\n" % (x, names[x][0], names[x][1], fc["callers"], fc["data_refs"],
                    r[0], ",".join(sorted(r[1])), body.get(x, ({}, 0))[1], ",".join("0x%X" % c for c in callees.get(x, [])),
                    "; ".join(tested.get(x, []))))
    with open(os.path.join(out_dir, "excluded.tsv"), "w", newline="\n") as f:
        f.write("addr\tname\tclass\tdetail\n")
        for x, why in sorted(reason.items()):
            f.write("0x%X\t%s\t%s\t%s\n" % (x, names[x][0], cat[x], why))

    exists = lambda rel: os.path.exists(os.path.join(a.cont or P.MAIN, rel))  # noqa: E731
    suffix = "_rest" if wip and (exists("game/src/%s/%s.cpp" % (area, s)) or exists("game/include/p3fes/game/%s.h" % s)) else ""
    pj = {"slice": s, "main": sha, "made": datetime.datetime.now().isoformat(timespec="seconds"), "area": area,
          "list": os.path.join(out_dir, s + ".txt"), "gen_list": os.path.join(out_dir, s + ".gen.txt"),
          "out_cpp": "game/src/%s/%s%s.cpp" % (area, s, suffix), "out_h": "game/include/p3fes/game/%s%s.h" % (s, suffix),
          "header_include": "p3fes/game/%s%s.h" % (s, suffix), "test": "tests/game/test_%s%s.cpp" % (s, suffix),
          "test_glob": "*test_%s*" % s, "snapshots": snaps, "seeds": 96, "snapshot_seeds": 16,
          "desc": a.desc or (wip["row_header"] if wip else ""), "continue": a.cont,
          "count": len(slice_list), "gen_count": len(chosen)}
    json.dump(pj, open(os.path.join(out_dir, "packet.json"), "w", encoding="utf-8"), indent=1)

    L = []
    L.append("# Packet `%s`: %d functions (%d bytes) -- main %s, %s" %
             (s, len(slice_list), sum(names[x][1] for x in slice_list), sha[:8], datetime.date.today()))
    if wip:
        L.append("Mode: **continue** a paused slice: worktree `%s` (branch `%s`, HEAD %s, %s commits behind main)." %
                 (wip["wt"], wip["branch"], wip["head"], wip["behind"]))
    L.append("Lists: `%s` (the slice; --only @file), `%s` (what `slice.ps1 gen` generates), `claims.txt`; details "
             "`functions.tsv`, `excluded.tsv` (same folder)." % (pj["list"], pj["gen_list"]))
    L.append("Write: `%s`, `%s`, `%s` (`slice.ps1 gen` creates and wires them)." % (pj["out_cpp"], pj["out_h"], pj["test"]))
    L.append("Audit (`slice.ps1 audit`): --seeds 96 --snapshots %s --snapshot-seeds 16. Pair tests: the skeleton's random "
             "worlds + real data (`read_snapshot(\"b_5800\")` etc.); `P3FES_HG_SEEDS=<n>` for more pairs." % ",".join(snaps))
    L.append("Chosen by: reach (saved first-call probes, %d files) then caller count; callees from p3fes_handgen bodies." % reach_files)
    if wip:
        L.append("")
        L.append("## The paused work (uncommitted in the worktree)")
        defs = wip["defs"]
        undefined = [x for x in done_rows if x not in defs]
        extra = [x for x in defs if x not in set(done_rows)]
        byfile = collections.Counter(defs[x] for x in done_rows if x in defs)
        def state(path):
            txt = P.read_text(os.path.join(wip["wt"], path))
            return "%d lines, %d raw handgen banners, %d gotos" % (txt.count("\n"), txt.count(
                "Generated by p3fes_handgen: register for register"), len(re.findall(r"\bgoto L_", txt)))
        L.append("- Done: %d rows in game/replaced.txt; defined in %s." %
                 (len(done_rows), ", ".join("`%s` (%d fns; %s)" % (k, v, state(k)) for k, v in sorted(byfile.items())) or "-"))
        changed = {p for _, p in wip["files"]}
        todo = [f for f in ("docs/INTEGRATION_LOG.md", "game/README.md") if f not in changed]
        if todo:
            L.append("- Not written yet: %s." % ", ".join("`%s` (%s)" % (f, "one section at the end" if f.endswith(".md") and "LOG" in f else "one table row") for f in todo))
        if undefined:
            L.append("- Rows without a definition yet (%d): %s" % (len(undefined), " ".join(short(x, names) for x in undefined[:20])))
        if extra:
            L.append("- Defined but not in replaced.txt (%d): %s" % (len(extra), " ".join(short(x, names) for x in extra[:20])))
        for path, (n, txt) in sorted(wip["tests"].items()):
            cov = sum(1 for x in done_rows if names.get(x, ("?",))[0] in txt or ("%08x" % x) in txt)
            L.append("- Test `%s`: %d TEST_CASEs; names %d of the %d done functions." % (path, n, cov, len(done_rows)))
        other = [p for c, p in wip["files"] if not p.startswith(("game/src/", "tests/game/test_"))]
        L.append("- Other changed files: %s" % (", ".join("`%s`" % p for p in other) or "-"))
        if dropped_done:
            L.append("- **Must drop (%d)**: %s" % (len(dropped_done), "; ".join(
                "%s %s" % (short(x, names), why) for x, why in sorted(dropped_done.items())[:12])))
        L.append("- Remaining to do: %d (below)%s." % (len(chosen), (", planned list `%s`" % planned_src) if planned_src else
                 " (no planned list found: only the done rows are claimed)"))
        L.append("- Start with `slice.ps1 sync` (merges main, keeps the WIP), then `slice.ps1 build` and `slice.ps1 test` "
                 "to see where it stands; `gen` writes the remaining ones to new files (%s)." % pj["out_cpp"])
    L.append("")
    L.append("## Exclusions applied (%d candidates)" % (len(uni)))
    rc = collections.Counter(cat.values())
    L.append(" | ".join("%s %d" % kv for kv in rc.most_common()) or "none")
    for key in [k for k, _ in rc.most_common() if k not in ("replaced", "over target")]:
        xs = [x for x in sorted(reason) if cat[x] == key]
        L.append("- %s: %s%s" % (key, "; ".join("%s %s" % (short(x, names), reason[x]) for x in xs[:6]),
                                  " (+%d, excluded.tsv)" % (len(xs) - 6) if len(xs) > 6 else ""))
    st = [x for x in chosen if x in tested]
    if st:
        L.append("")
        L.append("## Tests that stand them in (%d functions; not a blocker: the test build's forwarder asks the stand-ins first)" % len(st))
        L.append("After the replacement these tests meet the stand-in, as before, instead of the body: run them "
                 "(`p3fes_game_tests -sf=*<file>*`) besides your own. A `stop_pc` / not-emitted check on the function "
                 "(\"named\") or an absent-run recorder (\"served\": installed on a missing-function stop, which a replaced "
                 "function no longer gives) can still change: fix such a test by standing the function in explicitly.")
        for x in st[:40]:
            L.append("- %s: %s" % (short(x, names), "; ".join(tested[x][:4])))
        if len(st) > 40:
            L.append("- (+%d more: functions.tsv, column tests)" % (len(st) - 40))
    L.append("")
    L.append("## Reuse")
    L.append("- Headers of the replaced callees: %s" % (", ".join("`%s` (%d)" % kv for kv in hdr_count.most_common(8)) or "-"))
    L.append("- Named records (types.json): %s" % (", ".join("%s %d fns%s" % (k, v, (" `%s`" % rec_hdr[k.split(" ")[0]])
                                                            if k.split(" ")[0] in rec_hdr else "") for k, v in rec_count.most_common(8)) or "-"))
    L.append("- Type deltas touching these functions / records: %s" % (", ".join("`%s` (%d)" % (os.path.basename(p), n)
                                                                              for n, p in deltas[:8]) or "-"))
    L.append("")
    L.append("## Functions (work order)")
    L.append("Callees: I this slice, R replaced (count), E recompiled + emitted in the test build (runs in pairs), "
             "G recompiled and not emitted (a pair stops there: stand it in), S stood in by another test (a stand-in "
             "serves it there, recompiled or replaced). "
             "cr = callers+data refs, reach = probe call count.")
    L.append("```")
    L.append("addr    bytes  cr reach role | callees")
    for x in chosen:
        fc = facts.get(x) or {"callers": 0, "data_refs": 0}
        r = reach.get(x, (0, set()))[0]
        cs = callees.get(x, [])
        groups = collections.OrderedDict((k, []) for k in "IGSE")
        nrep = 0
        for c in cs:
            if c in chosen_set or c in set(keep_done):
                groups["I"].append(c)
            elif c in replaced:
                nrep += 1
            elif c in stood:
                groups["S"].append(c)
            elif c in emitted:
                groups["E"].append(c)
            else:
                groups["G"].append(c)
        parts = []
        for k, v in groups.items():
            if v:
                parts.append("%s:%s%s" % (k, ",".join(short(c, names) for c in v[:5]), "+%d" % (len(v) - 5) if len(v) > 5 else ""))
        if nrep:
            parts.append("R%d" % nrep)
        jal = body.get(x, ({}, 0))[1]
        if jal:
            parts.append("jalr%d" % jal)
        nm = names[x][0]
        lab = "%x" % x if nm == "sub_%X" % x else "%x %s" % (x, nm[:24])
        L.append("%-7s %5d %3d %5s %s | %s" % (lab if len(lab) <= 7 else lab, names[x][1], fc["callers"] + fc["data_refs"],
                                              r or "-", role_of(x, names, facts.get(x)), " ".join(parts) or "-"))
    L.append("```")
    text = "\n".join(L) + "\n"
    open(os.path.join(out_dir, "packet.md"), "w", encoding="utf-8", newline="\n").write(text)

    print("packet %s: %d functions (%d to generate), %d excluded, ~%d tokens -> %s" %
          (s, len(slice_list), len(chosen), len(reason), P.tokens(text), out_dir))
    if a.blocked_report:
        blocked_report(names, chunks, replaced, tested, held, claims, elf, handgen, sym)
    return 0


def blocked_report(names, chunks, replaced, tested, held, claims, elf, handgen, sym):
    """Game code (< 0x460000) still recompiled: how many are free, and how many of those tests stand in."""
    rest = [x for x in names if x < P.GAME_END and x not in replaced]
    clean, only_si = [], []
    for x in rest:
        rngs, data = chunks.get(x, ([(x, x + names[x][1])], set()))
        flags, targets, _ = P.scan_body(elf, rngs, data)
        if flags or any(P.callee_class(names.get(t, ("", 0))[0]) for t in targets):
            continue
        clean.append(x)
    _, refused, _ = P.run_handgen(handgen, sym, clean, P.tmpdir("blocked"))
    clean = [x for x in clean if x not in refused]
    free = [x for x in clean if x not in held and x not in claims]
    print("game code < 0x%X still recompiled: %d; skip-rule clean + generated: %d; held by a test comment: %d; "
          "claimed by packets: %d; free: %d (of which stood in / named / served by tests: %d, not a blocker)" % (
              P.GAME_END, len(rest), len(clean), sum(1 for x in clean if x in held),
              sum(1 for x in clean if x in claims and x not in held), len(free), sum(1 for x in free if x in tested)))
    by = collections.Counter("0x%02X0000" % (x >> 16) for x in free)
    print("free by 64 KB band: " + ", ".join("%s %d" % kv for kv in sorted(by.items())))


if __name__ == "__main__":
    sys.exit(main())
