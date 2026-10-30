#!/usr/bin/env python3
"""Write the per-vector `status` computed by tests/ee/test_pcsx2_vectors.cpp back into pcsx2_vectors.json.

  P3FES_EEVEC_REPORT=<report.jsonl> build/<tree>/bin/p3fes_tests -tc="pcsx2 vectors*"
  python -I tools/ours/eevec/annotate.py --report <report.jsonl> [--json tests/ee/vectors/pcsx2_vectors.json]

The report is one JSON object per line: {"id", "status", "ours": {...}, "mismatched": [...]}. `status` is
"agree", "disagree:<class>" (a documented, deliberate difference; the classes are defined in the test) or
"mismatch" (a real difference: the test fails on it). This script stores `status` on every vector, stores our
values next to the observed ones for the disagreeing vectors ("ours": only the mismatched fields), and rewrites
meta.summary (per family: agree / disagree by class / mismatch / missing). The test checks that the stored
status equals the one it computes, so the committed file never drifts from the headers.
"""
import argparse
import collections
import json
import pathlib
import sys

HERE = pathlib.Path(__file__).resolve()
REPO = HERE.parents[3]
DEFAULT_JSON = REPO / "tests" / "ee" / "vectors" / "pcsx2_vectors.json"


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--report", required=True, type=pathlib.Path)
    ap.add_argument("--json", type=pathlib.Path, default=DEFAULT_JSON)
    a = ap.parse_args(argv)
    rep = {}
    for line in a.report.read_text(encoding="utf-8").splitlines():
        if line.strip():
            r = json.loads(line)
            rep[r["id"]] = r
    doc = json.loads(a.json.read_text(encoding="utf-8"))
    summary = collections.defaultdict(lambda: collections.Counter())
    families = collections.Counter()
    ops = collections.defaultdict(set)
    for v in doc["vectors"]:
        r = rep.get(v["id"])
        status = r["status"] if r else "missing"
        v["status"] = status
        v.pop("ours", None)
        if r and status != "agree" and r.get("mismatched"):
            v["ours"] = {k: r["ours"][k] for k in r["mismatched"] if k in r["ours"]}
        summary[v["family"]][status] += 1
        families[v["family"]] += 1
        ops[v["family"]].add(v["op"].split(".")[0] if v["family"] == "vu0" else v["op"])
    doc["meta"]["summary"] = {fam: {"vectors": families[fam], "ops": len(ops[fam]), **dict(sorted(summary[fam].items()))} for fam in sorted(families)}
    a.json.write_text(json.dumps(doc, indent=1) + "\n", encoding="utf-8")
    for fam, s in doc["meta"]["summary"].items():
        print(fam, s)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
