"""Apply community symbol HINTS (symbols/hints/*.sym, ADR-0009) to an IDA database and report coverage.

Usage (idalib venv python; `import idapro` must be first):
  python hints_import.py <ida/work_hints.i64> [--root .] [--hints-dir symbols/hints]
                         [--sources fes-pc-recomp,tge-pr4,snaku] [--dry-run] [--out symbols/p3fes.hints.sym]

Semantics (owned by import_symbols.apply_hint, shared with import_symbols.py):
  * The IDA name is set only where the address still carries an auto/dummy name (`sub_*`, `nullsub_*`, no name).
    A user or FLIRT name is never overwritten: that is a `conflict`, written to ida/logs/hints_conflicts.tsv.
  * Every hint (named, same, conflict, no_func) gets a repeatable comment line `HINT[<source>] <name>` at its
    address, so all sources stay visible in IDA and export_symbols.py can tell hint-placed names apart.
  * `--sources` is also the priority order when several sources name the same address differently: the
    first source wins the IDA name, the others are recorded as comments (counted as `alternate`).
  * F hints at an address where no IDA function starts are comment-only (`no_func`); functions are not created
    (boundary disagreements are reported by hints_convert.py --compare).
  * Writes symbols/p3fes.hints.sym (gitignored): every hint row with `source=` and `applied=<status>` tags,
    importable by import_symbols.py (hint semantics preserved; add `verified=yes` to promote a row).
  * Coverage before/after by band and source -> ida/logs/hints_coverage.json; log -> ida/logs/hints_import.log.
  * --dry-run computes everything without modifying the database (closed without save).
"""
import idapro  # noqa -- must be first
import argparse, collections, json, os, re, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_symbols import AUTO_RE, PERMISSIVE_SOURCES, parse_sym, apply_hint, has_user_name_at, set_hint_comment
from hints_convert import BANDS, band_of

DEFAULT_ORDER = ["fes-pc-recomp", "tge-pr4", "snaku"]
# Module-family prefixes for the headline (case-sensitive alternatives listed explicitly; documented in 07_hints_coverage.md)
FAMILY = collections.OrderedDict([
    ("sce", re.compile(r"^_?i?(sce|Sce|SCE)")),
    ("rw", re.compile(r"^_?(Rw|Rp|Rt|rw|rp|rt|RW|RP|RT)[A-Za-z0-9_]")),
    ("cri", re.compile(r"^_?(cri|CRI|ADX|adx|AIX|aix|AHX|ahx|cv[A-Z]|CV[A-Z_]|ROFS|rofs|mw[A-Z]|MW|sj[A-Z]|SJ|srd|SRD|DVCI|dvci|HTCI|htci|svm|SVM|SFD|sfd|mpeg|MPEG)")),
])
def family_of(name):
    for k, rx in FAMILY.items():
        if rx.match(name): return k
    return None

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("i64"); ap.add_argument("--root", default=".")
    ap.add_argument("--hints-dir", default=None); ap.add_argument("--sources", default=",".join(DEFAULT_ORDER))
    ap.add_argument("--dry-run", action="store_true"); ap.add_argument("--out", default=None)
    a = ap.parse_args()
    root = os.path.abspath(a.root); i64 = os.path.abspath(a.i64)
    hints_dir = os.path.abspath(a.hints_dir) if a.hints_dir else os.path.join(root, "symbols", "hints")
    out_sym = os.path.abspath(a.out) if a.out else os.path.join(root, "symbols", "p3fes.hints.sym")
    logdir = os.path.join(root, "ida", "logs"); os.makedirs(logdir, exist_ok=True)
    lf = open(os.path.join(logdir, "hints_import.log"), "a", encoding="utf-8")
    def log(m): lf.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] {m}\n"); lf.flush()
    sources = [s.strip() for s in a.sources.split(",") if s.strip()]
    log(f"hints_import {i64} sources={sources} dry_run={a.dry_run}")

    # ---- load hints, grouped per address in priority order
    by_ea = collections.defaultdict(list); loaded = collections.Counter(); headers = {}
    for src in sources:
        p = os.path.join(hints_dir, f"{src}.sym")
        if not os.path.exists(p): log(f"missing hint file {p}"); print(f"missing {p}"); continue
        headers[src] = [l.rstrip("\n") for l in open(p, encoding="utf-8") if l.startswith("#")][:4]
        for ea, sz, kind, name, tags in parse_sym(p, with_tags=True):
            tags.setdefault("source", src)
            by_ea[ea].append((src, kind, name, sz, tags)); loaded[src] += 1
    log(f"loaded {dict(loaded)} over {len(by_ea)} addresses")

    idapro.enable_console_messages(False)
    rc = idapro.open_database(i64, False)
    if rc != 0: log(f"open failed rc={rc}"); print(f"open failed rc={rc}"); sys.exit(rc)
    import ida_funcs, ida_name, idautils, ida_bytes

    def snapshot():
        """Per-function (ea -> name) and derived coverage counters."""
        names = {fea: ida_funcs.get_func_name(fea) for fea in idautils.Functions()}
        cov = dict(functions=len(names), descriptive=0, by_band=collections.Counter(), by_band_total=collections.Counter(),
                   family=collections.Counter())
        for fea, nm in names.items():
            b = band_of(fea); cov["by_band_total"][b] += 1
            if not AUTO_RE.match(nm):
                cov["descriptive"] += 1; cov["by_band"][b] += 1
                fam = family_of(nm)
                if fam: cov["family"][fam] += 1
        return names, cov
    before_names, before = snapshot()
    log(f"before: functions={before['functions']} descriptive={before['descriptive']} family={dict(before['family'])}")

    # ---- apply
    status_by_src = collections.defaultdict(collections.Counter); kind_by_src = collections.defaultdict(collections.Counter)
    rows_out = []; conflicts = []; alternates = 0; named_by_src_ea = {}
    for ea in sorted(by_ea):
        hints = by_ea[ea]; primary_name = None
        existing = ida_name.get_name(ea) or ""      # state before this run touches the address
        existing_user = has_user_name_at(ea)
        for src, kind, name, sz, tags in hints:
            verified = tags.get("verified") == "yes"
            if primary_name is not None and name != primary_name and not existing_user:
                # a lower-priority source disagreeing with the name just applied: comment only
                st = "alternate"; alternates += 1
                if not a.dry_run: set_hint_comment(ea, src, name, "verified" if verified else "")
            else:
                st = apply_hint(ea, kind, name, src, verified, log, dry_run=a.dry_run)
                if st in ("named", "same") and primary_name is None:
                    primary_name = name; named_by_src_ea[ea] = (src, name, st)
            status_by_src[src][st] += 1
            if st in ("named", "same"): kind_by_src[src][kind] += 1
            if st == "conflict": conflicts.append((ea, kind, existing, src, name))
            extra = " ".join(f"{k}={v}" for k, v in tags.items() if k not in ("source",))
            rows_out.append(f"{ea:08x} {sz:08x} {kind} {name} source={src} applied={st}" + (f" {extra}" if extra else ""))
    after_names, after = snapshot()
    log(f"after: descriptive={after['descriptive']} family={dict(after['family'])} alternates={alternates}")

    # ---- per-source gains on functions (which source's name is now the IDA name)
    gained_by_src = collections.Counter(); gained_band_src = collections.defaultdict(collections.Counter)
    gained_family_src = collections.defaultdict(collections.Counter)
    for fea, nm in after_names.items():
        if AUTO_RE.match(before_names.get(fea, "sub_")) and not AUTO_RE.match(nm):
            src = named_by_src_ea.get(fea, ("?", None, None))[0]
            gained_by_src[src] += 1; gained_band_src[band_of(fea)][src] += 1
            fam = family_of(nm)
            if fam: gained_family_src[fam][src] += 1
    data_named = {src: kind_by_src[src]["D"] + kind_by_src[src]["L"] for src in sources}

    # ---- outputs
    if not a.dry_run or True:  # the .sym and reports are written even on dry-run (they describe the plan)
        with open(out_sym, "w", encoding="utf-8", newline="\n") as fh:
            fh.write("# p3fes.hints.sym  PRIVATE community hints applied to the IDA database (ADR-0009) -- gitignored, never commit\n")
            fh.write(f"# generated {time.strftime('%Y-%m-%d %H:%M:%S')} by tools/ours/ida/hints_import.py onto {os.path.basename(i64)}"
                     f"{' (DRY RUN: nothing written to the DB)' if a.dry_run else ''}; sources in priority order: {','.join(sources)}\n")
            fh.write("# <addr8> <size8> <F|D|L> <name> source=<src> applied=<named|same|alternate|conflict|no_func|mid_item|failed> [module=..] [cite=..]\n")
            fh.write("#   promotion: append ` verified=yes` to a row and re-run import_symbols.py (see its docstring)\n")
            for src in sources:
                for h in headers.get(src, []): fh.write("#   " + h.lstrip("# ") + "\n")
            for r in rows_out: fh.write(r + "\n")
        with open(os.path.join(logdir, "hints_conflicts.tsv"), "w", encoding="utf-8", newline="\n") as fh:
            fh.write("address\tkind\texisting_name\thint_source\thint_name\n")
            for ea, kind, ex, src, name in conflicts: fh.write(f"0x{ea:06X}\t{kind}\t{ex}\t{src}\t{name}\n")
        report = dict(database=i64, dry_run=a.dry_run, sources=sources, loaded=dict(loaded),
                      status_by_source={s: dict(c) for s, c in status_by_src.items()},
                      kind_named_by_source={s: dict(c) for s, c in kind_by_src.items()},
                      before=dict(functions=before["functions"], descriptive=before["descriptive"], family=dict(before["family"]),
                                  by_band={b: [before["by_band"][b], before["by_band_total"][b]] for b in before["by_band_total"]}),
                      after=dict(functions=after["functions"], descriptive=after["descriptive"], family=dict(after["family"]),
                                 by_band={b: [after["by_band"][b], after["by_band_total"][b]] for b in after["by_band_total"]}),
                      gained_by_source=dict(gained_by_src),
                      gained_by_band_source={b: dict(c) for b, c in gained_band_src.items()},
                      gained_family_by_source={f: dict(c) for f, c in gained_family_src.items()},
                      data_items_named_by_source=data_named, alternates=alternates,
                      conflicts=[dict(ea=f"0x{ea:06X}", kind=k, existing=ex, source=src, hint=name) for ea, k, ex, src, name in conflicts],
                      band_order=[b[2] for b in BANDS] + ["other game code (between bands)"])
        json.dump(report, open(os.path.join(logdir, "hints_coverage.json"), "w", encoding="utf-8"), indent=1)
    idapro.close_database(not a.dry_run)
    print(f"{'DRY RUN ' if a.dry_run else ''}functions {before['functions']}: descriptive {before['descriptive']} -> {after['descriptive']}; "
          f"family before {dict(before['family'])} after {dict(after['family'])}")
    for src in sources:
        print(f"  {src}: {dict(status_by_src[src])} data/labels named={data_named[src]} functions gained={gained_by_src[src]}")
    print(f"  conflicts={len(conflicts)} alternates={alternates}; wrote {out_sym}, ida/logs/hints_coverage.json, ida/logs/hints_conflicts.tsv")

if __name__ == "__main__":
    main()
