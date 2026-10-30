"""Query tools/ours/types/types.json (p3fes_types; docs/ANALYSIS/28_types.md).

    python -I tools/ours/types/types_query.py --addr 0x2FFD70          # what its arguments / result point to
    python -I tools/ours/types/types_query.py --addr datCalcGetHp      # same, by name (symbols/p3fes.sym)
    python -I tools/ours/types/types_query.py --type KwlnTask          # one layout (record name or class id)
    python -I tools/ours/types/types_query.py --type 89 --off 0x3C     # one field: accessors, pointee
    python -I tools/ours/types/types_query.py --global 0x7CE3EC        # an absolute address: accesses, pointee class
    python -I tools/ours/types/types_query.py --find-field 0x1C:4      # classes with a 4-byte field at +0x1C
  options: --json (machine-readable), --all (every field, not the first 64), --types <types.json>

Field lines: +offset widths type conf n_fns accessors [-> pointee class] [fnptr] [poly] [snap pass/total] [name].
`name` appears only where seeds.json (the project's headers) documents the field; `type_<id>` classes are unnamed.
"""
import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
ARGS = ["$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3"]


def load_names():
    names, by_name = {}, {}
    p = os.path.join(REPO, "symbols", "p3fes.sym")
    if os.path.isfile(p):
        with open(p, encoding="utf-8") as f:
            for ln in f:
                if ln.startswith("#"):
                    continue
                q = ln.split()
                if len(q) >= 4:
                    a = int(q[0], 16)
                    names[a] = q[3]
                    by_name.setdefault(q[3], a)
    return names, by_name


def label(names, a):
    a = int(a, 16) if isinstance(a, str) else a
    return "%s 0x%X" % (names.get(a, "sub_%X" % a), a)


def field_line(names, f):
    s = "  +0x%-5X %-8s %-6s %-6s %3d fn  %s" % (
        f["off"], "/".join(str(w) for w in f["w"]), f["type"], f["conf"], f["n_fns"],
        ", ".join(label(names, a) for a in f["fns"][:3]))
    if "ptr" in f:
        s += "  -> type %d" % f["ptr"]
    if f.get("fnptr"):
        s += "  fnptr"
    if f.get("poly"):
        s += "  poly"
    if "snap" in f:
        s += "  snap %d/%d" % tuple(f["snap"])
    if "name" in f:
        s += "  [%s]" % f["name"]
    return s


def show_class(doc, names, cid, all_fields=False, off=None, out=sys.stdout):
    c = doc["_by_id"].get(cid)
    if not c:
        print("  (class %s not in types.json)" % cid, file=out)
        return
    hdr = "type %d %s  size >= 0x%X" % (c["id"], c["name"], c["size_min"])
    if "size_header" in c:
        hdr += "  (documented 0x%X, %s)" % (c["size_header"], c.get("header", ""))
    hdr += "  %d params" % c["n_params"]
    if c.get("instances"):
        hdr += "  instances " + ", ".join("%s %d" % kv for kv in c["instances"].items())
    print(hdr, file=out)
    if c["params"]:
        print("  received by: " + ", ".join("%s %s" % (label(names, p[0]), ARGS[p[1]]) for p in c["params"][:6]) +
              (" ..." if c["n_params"] > 6 else ""), file=out)
    if c["gslots"]:
        print("  pointed to by globals: " + ", ".join(c["gslots"][:8]), file=out)
    if c["gobjs"]:
        print("  lives at: " + ", ".join(c["gobjs"][:8]), file=out)
    fields = c["fields"]
    if off is not None:
        fields = [f for f in fields if f["off"] == off]
    for i, f in enumerate(fields):
        if i >= 64 and not all_fields:
            print("  ... %d more fields (--all)" % (len(fields) - 64), file=out)
            break
        print(field_line(names, f), file=out)
    if off is None and c.get("arrays"):
        print("  indexed: " + ", ".join("+0x%X stride %d w%s" % (a["off"], a["stride"], a["w"]) for a in c["arrays"][:8]),
              file=out)
    if off is None and c.get("code"):
        print("  code objects (callbacks stored here): " + ", ".join(label(names, a) for a in c["code"][:8]), file=out)


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--types", default=os.path.join(HERE, "types.json"))
    ap.add_argument("--addr")
    ap.add_argument("--type")
    ap.add_argument("--off")
    ap.add_argument("--global", dest="glob")
    ap.add_argument("--find-field")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--all", action="store_true")
    a = ap.parse_args(argv)
    with open(a.types, encoding="utf-8") as f:
        doc = json.load(f)
    doc["_by_id"] = {c["id"]: c for c in doc["classes"]}
    by_name = {c["name"]: c["id"] for c in doc["classes"]}
    names, sym = load_names()
    off = int(a.off, 16) if a.off else None

    if a.addr:
        addr = sym.get(a.addr)
        if addr is None:
            addr = int(a.addr, 16)
        fe = doc["functions"].get("0x%X" % addr)
        if a.json:
            print(json.dumps({"function": "0x%X" % addr, "params": fe and fe.get("p"), "ret": fe and fe.get("r"),
                              "classes": {str(x): doc["_by_id"][x] for x in ((fe or {}).get("p", []) + [(fe or {}).get("r")])
                                          if x}}, indent=1))
            return
        print(label(names, addr))
        if not fe:
            print("  no argument or result points to a recovered type")
            return
        for i, cid in enumerate(fe.get("p", [])):
            if cid:
                print("%s ->" % ARGS[i], end=" ")
                show_class(doc, names, cid, a.all)
        if fe.get("r"):
            print("$v0 (result) ->", end=" ")
            show_class(doc, names, fe["r"], a.all)
    if a.type:
        cid = by_name.get(a.type)
        if cid is None:
            cid = int(a.type, 0)
        if a.json:
            print(json.dumps(doc["_by_id"].get(cid), indent=1))
        else:
            show_class(doc, names, cid, a.all, off)
    if a.glob:
        g = int(a.glob, 16)
        rows = [r for r in doc["globals"] if int(r[0], 16) == g]
        for r in rows:
            print("0x%X: widths %s kinds '%s' %d fn%s" % (g, r[1], r[2], r[3], "" if r[3] == 1 else "s") +
                  ("  -> type %d" % r[4] if len(r) > 4 else ""))
            if len(r) > 4:
                show_class(doc, names, r[4], a.all)
        holders = [c for c in doc["classes"] if "0x%X" % g in c["gobjs"]]
        for c in holders:
            print("an object of type %d %s lives here" % (c["id"], c["name"]))
        if not rows and not holders:
            print("0x%X: no absolute-address access recorded" % g)
    if a.find_field:
        o, _, w = a.find_field.partition(":")
        o = int(o, 16)
        w = int(w) if w else None
        for c in doc["classes"]:
            for f in c["fields"]:
                if f["off"] == o and (w is None or w in f["w"]):
                    print("type %d %s: %s" % (c["id"], c["name"], field_line(names, f).strip()))


if __name__ == "__main__":
    main(sys.argv[1:])
