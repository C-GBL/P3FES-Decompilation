"""Collect the Hex-Rays pseudocode reference for a slice's functions, next to their p3fes_handgen bodies.

Plain CPython (`python -I`), no IDA: it reads the gitignored folder `pseudo_export.py` writes (default: the MAIN
tree's `ida/pseudocode`, found through git from any worktree).

  python -I tools/ours/ida/pseudo.py --only @<slice>.txt [--handgen game/src/<area>/<slice>.cpp]...
         [--out <scratch>/<slice>.pseudo.c] [--facts-only] [--ref <dir>] [--functions symbols/functions.json]

  --only      @file (one hex start per line, `#` comments; the p3fes_handgen list) or a comma list of hex starts
              and/or names
  --handgen   a p3fes_handgen output (or a slice .cpp that keeps its `// 0x<ADDR> <name> -- N bytes` lines): each
              function's generated body is printed right after its pseudocode (repeatable)
  --out       write there instead of stdout (keep it in your scratch area: it is derived from the game binary
              and is never committed)
  --facts-only  the header only (callers, callees, globals, strings, warnings): e.g. for a function whose
              decompilation failed, or to scan a big slice

The pseudocode is a READ-ONLY hint for the readability pass: names of locals, argument counts and types are IDA's
guesses; p3fes_handgen's body is the faithful source of truth (docs/PHASE5_AGENT_BRIEF.md "The pseudocode
reference"). A name in the pseudocode file that differs from symbols/functions.json means the master was updated
after the export: re-run pseudo_export.py (incremental) on a fresh copy.
"""
import argparse, json, os, re, subprocess, sys

ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
ap.add_argument("--only", required=True)
ap.add_argument("--handgen", action="append", default=[])
ap.add_argument("--out", default=None)
ap.add_argument("--facts-only", action="store_true")
ap.add_argument("--ref", default=None, help="the pseudocode folder (default: <main tree>/ida/pseudocode)")
ap.add_argument("--functions", default=None, help="symbols/functions.json (default: this tree's)")
A = ap.parse_args()

HERE = os.path.dirname(os.path.abspath(__file__))
TREE = os.path.abspath(os.path.join(HERE, "..", "..", ".."))

def main_tree():
    try:
        common = subprocess.run(["git", "-C", TREE, "rev-parse", "--path-format=absolute", "--git-common-dir"],
                                capture_output=True, text=True, check=True).stdout.strip()
        return os.path.dirname(os.path.abspath(common))
    except Exception:  # noqa: BLE001
        return TREE

REF = os.path.abspath(A.ref) if A.ref else next((p for p in (os.path.join(TREE, "ida", "pseudocode"),
                                                             os.path.join(main_tree(), "ida", "pseudocode"))
                                                 if os.path.exists(os.path.join(p, "index.tsv"))), None)
if REF is None:
    sys.exit("no pseudocode reference found (ida/pseudocode/index.tsv in this tree or the main tree): "
             "run tools/ours/ida/pseudo_export.py first (tools/ours/ida/README.md)")
index = {}
cols = None
for ln in open(os.path.join(REF, "index.tsv"), encoding="utf-8"):
    f = ln.rstrip("\n").split("\t")
    if cols is None: cols = f; continue
    r = dict(zip(cols, f)); index[int(r["addr"], 16)] = r
funcs = json.load(open(A.functions or os.path.join(TREE, "symbols", "functions.json"), encoding="utf-8"))
CUR = {int(x["a"], 16): x["n"] for x in funcs}
BY_NAME = {n: a for a, n in CUR.items()}

def parse_only(spec):
    items = []
    if spec.startswith("@"):
        for line in open(spec[1:], encoding="utf-8"):
            line = line.split("#", 1)[0].strip()
            if line: items.append(line.split()[0])
    else:
        items = [x.strip() for x in spec.split(",") if x.strip()]
    out = []
    for it in items:
        if re.fullmatch(r"(0x)?[0-9A-Fa-f]{5,8}", it): out.append(int(it, 16))
        elif it in BY_NAME: out.append(BY_NAME[it])
        else: sys.exit(f"unknown function {it!r} (not a hex start, not a name in functions.json)")
    return out

HG_HEAD = re.compile(r"^// 0x([0-9A-Fa-f]{8}) (\S+) -- \d+ bytes")
def handgen_bodies(path):
    """{addr: (line number, text)}: from the `// 0x<ADDR> <name> -- N bytes` line to the `}` that closes the body."""
    out = {}; lines = open(path, encoding="utf-8").read().split("\n"); i = 0
    while i < len(lines):
        m = HG_HEAD.match(lines[i])
        if not m: i += 1; continue
        start = i; j = i + 1
        while j < len(lines) and not (lines[j].startswith("void ") and lines[j].rstrip().endswith("{")): j += 1
        while j < len(lines) and lines[j] != "}": j += 1
        out[int(m.group(1), 16)] = (start + 1, "\n".join(lines[start:j + 1]))
        i = j + 1
    return out

hg = {}
for p in A.handgen:
    try: shown = os.path.relpath(p)
    except ValueError: shown = os.path.abspath(p)  # another drive
    for a, (ln, txt) in handgen_bodies(p).items(): hg[a] = (f"{shown}:{ln}", txt)

addrs = parse_only(A.only)
out = []
rows = []
for a in addrs:
    r = index.get(a)
    if r is None:
        rows.append(f"//   0x{a:08X} {CUR.get(a, '?'):40s} NOT IN THE REFERENCE (not a function start in the export)")
        continue
    stale = "" if r["name"] == CUR.get(a) else f"  [STALE: exported as {r['name']}, now {CUR.get(a)}]"
    extra = []
    if int(r.get("asm_lines") or 0): extra.append(f"asm {r['asm_lines']}")
    if int(r.get("jumpout") or 0): extra.append(f"JUMPOUT {r['jumpout']}")
    if int(r.get("warnings") or 0): extra.append(f"warn {r['warnings']}")
    rows.append(f"//   0x{a:08X} {CUR.get(a, r['name']):40s} {r['status']:10s} {r['lines']:>5s} lines"
                + (f"  ({', '.join(extra)})" if extra else "") + (f"  {r['reason']}" if r["reason"] else "") + stale)
out.append(f"// Pseudocode reference for {len(addrs)} functions -- IDA Hex-Rays, a READ-ONLY hint (derived from the game "
           "binary: never commit this file).")
out.append(f"// Source: {REF}. p3fes_handgen's body is the faithful source of truth; IDA's types and names are guesses.")
out.extend(rows)
out.append("")
for a in addrs:
    r = index.get(a)
    if r is None: continue
    text = open(os.path.join(REF, r["file"]), encoding="utf-8").read()
    if A.facts_only:
        text = text.split("\n\n", 1)[0] + "\n"
    out.append("// " + "=" * 110)
    out.append(text.rstrip("\n"))
    if a in hg:
        where, body = hg[a]
        out.append(f"// ----- p3fes_handgen body ({where}) " + "-" * 60)
        out.append(body)
    out.append("")
res = "\n".join(out) + "\n"
if A.out:
    os.makedirs(os.path.dirname(os.path.abspath(A.out)) or ".", exist_ok=True)
    open(A.out, "w", encoding="utf-8", newline="\n").write(res)
    print(f"wrote {A.out}: {len(addrs)} functions ({sum(1 for a in addrs if a in index)} in the reference, "
          f"{sum(1 for a in addrs if a in hg)} with a handgen body)")
else:
    sys.stdout.reconfigure(encoding="utf-8"); sys.stdout.write(res)
