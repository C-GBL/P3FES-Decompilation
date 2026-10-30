"""Carry an IDA master rename map through source and doc files.

Usage (plain CPython, `-I`):
  python -I tools/ours/ida/apply_rename_map.py <map.tsv> <path>... [--dry-run] [--quiet]

<map.tsv>: one row per renamed function, `<addr8> <old_name> <new_name>` (tab or blank separated; `#` starts a
comment), e.g. tools/ours/ida/rename_map_update4.tsv, written from the master's export diff (functions.json before ->
after). Every <path> is a file or a directory (walked recursively; `.git`, `build`, `recomp/generated` and binary
files are skipped).

Rewrites whole identifiers only (an identifier is `[A-Za-z_][A-Za-z0-9_]*`, so `sub_1939D0` never matches inside
`sub_1939D0A` or `xsub_1939D0`):
  <old>                          -> <new>                          C++ functions, game/replaced.txt, docs, tests
  fn_<old>_<addr8>[__<suffix>]   -> fn_<new>_<addr8>[__<suffix>]   recomp_gen shims, P3FES_DECL_PAIR, `__recomp`
(<addr8> = the row's address, 8 hex digits, matched case-insensitively and written back as found.) Line endings and
encoding are preserved; files that do not change are not touched. Prints the replacements per file and a total; with
--dry-run nothing is written. Also warns when a file already used a new name as an identifier before the rewrite
(possible collision with an existing helper of that name: check the build).
"""
import argparse, os, re, sys

IDENT_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
SHIM_RE = re.compile(r"^fn_(.+)_([0-9A-Fa-f]{8})((?:__\w*)?)$")
SKIP_DIRS = {".git", "build", "generated", "__pycache__", "node_modules"}

def load_map(path):
    exact, shim = {}, {}
    for ln in open(path, encoding="utf-8"):
        ln = ln.split("#", 1)[0].strip()
        if not ln: continue
        parts = ln.split()
        if len(parts) != 3: sys.exit(f"bad map row: {ln!r}")
        a, old, new = parts
        ea = int(a, 16)
        if old in exact and exact[old] != new: sys.exit(f"map renames {old} twice ({exact[old]}, {new})")
        exact[old] = new
        shim[(old, ea)] = new
    return exact, shim

def rewrite(text, exact, shim, newnames):
    counts = {}
    pre_used = sorted({m.group(0) for m in IDENT_RE.finditer(text) if m.group(0) in newnames})
    def sub(m):
        t = m.group(0)
        if t in exact:
            counts[t] = counts.get(t, 0) + 1; return exact[t]
        if t.startswith("fn_"):
            s = SHIM_RE.match(t)
            if s:
                key = (s.group(1), int(s.group(2), 16))
                if key in shim:
                    counts[t] = counts.get(t, 0) + 1
                    return f"fn_{shim[key]}_{s.group(2)}{s.group(3)}"
        return t
    return IDENT_RE.sub(sub, text), counts, pre_used

def iter_files(paths):
    for p in paths:
        if os.path.isdir(p):
            for root, dirs, files in os.walk(p):
                dirs[:] = sorted(d for d in dirs if d not in SKIP_DIRS)
                for f in sorted(files): yield os.path.join(root, f)
        elif os.path.isfile(p): yield p
        else: print(f"warning: {p} does not exist", file=sys.stderr)

def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("map"); ap.add_argument("paths", nargs="+")
    ap.add_argument("--dry-run", action="store_true"); ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    exact, shim = load_map(a.map)
    newnames = set(exact.values())
    total = nfiles = 0
    for path in iter_files(a.paths):
        raw = open(path, "rb").read()
        if b"\0" in raw: continue
        try: text = raw.decode("utf-8")
        except UnicodeDecodeError: continue
        out, counts, pre_used = rewrite(text, exact, shim, newnames)
        if not counts: continue
        n = sum(counts.values()); total += n; nfiles += 1
        print(f"{path}: {n} replacement(s)" + ("" if a.quiet else ": " + ", ".join(f"{k} x{v}" for k, v in sorted(counts.items()))))
        if pre_used and not a.quiet:
            print(f"  note: {len(pre_used)} new name(s) already present before the rewrite (comments, or a clash to check): "
                  + ", ".join(pre_used[:8]) + (", ..." if len(pre_used) > 8 else ""))
        if not a.dry_run:
            with open(path, "wb") as fh: fh.write(out.encode("utf-8"))
    print(f"{'would rewrite' if a.dry_run else 'rewrote'} {total} identifier(s) in {nfiles} file(s) ({len(exact)} map rows)")

if __name__ == "__main__":
    main()
