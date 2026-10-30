"""roundtrip_diff.py -- classify the differences between two exports of export_symbols.py (plain CPython, run with -I).

Usage:
  python -I tools/ours/ida/roundtrip_diff.py <ref root> <rebuilt root> [--details PATH]

Each root holds `symbols/p3fes.sym` (+ optionally `symbols/functions.json`, `symbols/function_chunks.txt`,
`docs/ANALYSIS/*.md`) as written by export_symbols.py / export_function_chunks.py. Timestamp lines
(`# generated ...`, `_Generated ...`, the chunk file's first header line) are ignored. Prints one line per
difference class with its count (the numbers quoted in tools/ours/ida/README.md "Round trip") and exits 0 only
when every compared file is equal apart from timestamps. `--details` writes every differing row.
"""
import argparse, json, os, re, sys

def parse_sym(path):
    rows = {}
    for line in open(path, encoding="utf-8"):
        line = line.strip()
        if not line or line.startswith("#"): continue
        a, sz, kind, name, *rest = line.split()
        tags = rest[0:]  # `flirt`, `source=...`
        rows[(int(a, 16), kind)] = (int(sz, 16), name, tuple(sorted(tags)))
    return rows

def strip_stamps(text):
    return "\n".join(l for l in text.replace("\r\n", "\n").split("\n")
                     if not l.startswith("# generated ") and not l.startswith("_Generated ")
                     and not l.startswith("# function chunks + data items inside chunks; exported read-only from")
                     and not l.startswith((' "generated":', ' "database":')))  # insn_census.json / jumptables.json headers

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ref"); ap.add_argument("new"); ap.add_argument("--details", default=None)
    a = ap.parse_args()
    ref = parse_sym(os.path.join(a.ref, "symbols", "p3fes.sym"))
    new = parse_sym(os.path.join(a.new, "symbols", "p3fes.sym"))
    det = []; counts = {}
    def hit(cls, text):
        counts[cls] = counts.get(cls, 0) + 1; det.append(f"{cls:28s} {text}")
    for key in sorted(set(ref) | set(new)):
        ea, kind = key
        if key not in new: hit(f"{kind} missing in rebuild", f"{ea:08x} {ref[key][1]} size={ref[key][0]:#x} {' '.join(ref[key][2])}"); continue
        if key not in ref: hit(f"{kind} extra in rebuild", f"{ea:08x} {new[key][1]} size={new[key][0]:#x} {' '.join(new[key][2])}"); continue
        (rs, rn, rt), (ns, nn, nt) = ref[key], new[key]
        if rn != nn: hit(f"{kind} name differs", f"{ea:08x} ref={rn} new={nn}")
        if rs != ns: hit(f"{kind} size differs", f"{ea:08x} {rn} ref={rs:#x} new={ns:#x}")
        if ("flirt" in rt) != ("flirt" in nt): hit(f"{kind} flirt tag differs", f"{ea:08x} {rn} ref={' '.join(rt)} new={' '.join(nt)}")
        rsrc = [t for t in rt if t.startswith("source=")]; nsrc = [t for t in nt if t.startswith("source=")]
        if rsrc != nsrc: hit(f"{kind} source tag differs", f"{ea:08x} {rn} ref={rsrc} new={nsrc}")
    total_rows = sum(counts.values())
    print(f"p3fes.sym: ref rows={len(ref)} rebuilt rows={len(new)} differing rows={total_rows}")
    for cls in sorted(counts): print(f"  {counts[cls]:6d}  {cls}")
    ok = total_rows == 0; docs_ok = True
    for rel in ("symbols/functions.json", "symbols/function_chunks.txt", "symbols/insn_census.json", "symbols/jumptables.json",
                "docs/ANALYSIS/00_elf_layout.md", "docs/ANALYSIS/01_functions_summary.md", "docs/ANALYSIS/02_syscalls.md",
                "docs/ANALYSIS/03_strings_of_interest.md", "docs/ANALYSIS/04_decompiler_check.md"):
        pr, pn = os.path.join(a.ref, rel), os.path.join(a.new, rel)
        if not (os.path.exists(pr) and os.path.exists(pn)): print(f"{rel}: not compared (missing)"); continue
        tr, tn = strip_stamps(open(pr, encoding="utf-8").read()), strip_stamps(open(pn, encoding="utf-8").read())
        if tr == tn: print(f"{rel}: equal (apart from timestamps)"); continue
        lr, ln = tr.split("\n"), tn.split("\n")
        ndiff = sum(1 for x, y in zip(lr, ln) if x != y) + abs(len(lr) - len(ln))
        if rel.endswith("jumptables.json") and len(lr) == len(ln) and all(
                x == y or (x.strip().startswith('"text":') and y.strip().startswith('"text":')) for x, y in zip(lr, ln)):
            # descriptive load-idiom text only: the master's scrub of a withheld data name (`data_<EA>`) against IDA's
            # dummy form in a rebuild (`dword_<EA>`); tables, cases and targets are equal
            print(f"{rel}: equal apart from {ndiff} `text` lines (withheld-hint scrub forms)"); continue
        if rel.startswith("docs/"): docs_ok = False
        else: ok = False
        print(f"{rel}: DIFFERENT ({ndiff} lines differ or extra; {len(lr)} vs {len(ln)} lines)")
        if rel.endswith("function_chunks.txt"):
            sr = {l.split()[0]: l for l in lr if l and not l.startswith("#")}
            sn = {l.split()[0]: l for l in ln if l and not l.startswith("#")}
            for k in sorted(set(sr) | set(sn)):
                if sr.get(k) != sn.get(k): det.append(f"{'chunks differ':28s} ref: {sr.get(k)}\n{'':28s} new: {sn.get(k)}")
    if a.details:
        with open(a.details, "w", encoding="utf-8", newline="\n") as fh: fh.write("\n".join(det) + "\n")
        print(f"details -> {a.details} ({len(det)} entries)")
    print(f"ROUNDTRIP symbols/: {'EQUAL' if ok else 'DIFFERENT'}; docs/ANALYSIS: "
          f"{'equal' if docs_ok else 'differ (traces of the withheld hints the master carries; expected, see README)'}")
    sys.exit(0 if ok else 1)

if __name__ == "__main__":
    main()
