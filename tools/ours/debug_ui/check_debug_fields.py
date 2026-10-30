"""Check tools/ours/debug_ui/debug_fields.json: the schema, and every offset against the evidence it cites.

    python -I tools/ours/debug_ui/check_debug_fields.py [--json <file>] [--elf <SLUS_216.21>] [--no-elf] [-v]

Evidence forms (each field lists one or more; every one must hold):
  {"fn": "0x369A20", "src": "game/src/event/events2.cpp"}  the readable body of that function in that file (from its
        "// 0x00369A20 sub_..." header line to the closing brace) contains a load / store at the field's offset with
        the field's width (lb/lbu/sb 1, lh/lhu/sh 2, lw/sw/lwc1/swc1 4, ld/sd 8, lq/sq 16; for an aggregate field --
        char[n], u8[n], an f32 vector -- any access inside [off, off + size)). Symbolic offsets (ev::work::kEdUnit)
        are resolved from the constants of game/include/p3fes/game/*.h.
  {"src": "<header>", "match": "<text>"}                  the file has a line containing the text and the field's
        offset (decimal or 0x hex) on that line.
  {"elf_fn": "0x3407E0"}                                 for functions with no readable body: the function's
        instructions in the ELF (size from symbols/functions.json) contain a load / store with that immediate offset
        and width. Skipped (reported) when the ELF is not available.
With the ELF, label_addr / title_addr strings, enum strings and the list-box descriptor tables are compared too.
Cross-references (menu row targets "EvtKey[VARIANT]+N", list-box "writes") must name existing fields.
Exit status 0 when everything holds. Plain CPython, no dependencies.
"""
import argparse
import json
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
DEFAULT_JSON = os.path.join(HERE, "debug_fields.json")
ELF_CANDIDATES = [os.path.join(REPO, "extracted", "disc", "SLUS_216.21"),
                  r"F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21"]

SCALAR = {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4, "f32": 4, "ptr": 4}
AGG_RE = re.compile(r"^(char|u8|s8|u16|s16|u32|s32|f32)\[(\d+)\]$")
WIDTH = {"lb": 1, "lbu": 1, "sb": 1, "lh": 2, "lhu": 2, "sh": 2, "lw": 4, "lwu": 4, "sw": 4, "lwc1": 4, "swc1": 4,
         "ld": 8, "sd": 8, "lq": 16, "sq": 16}
ACCESS_RE = re.compile(r"\b(lbu|lb|sb|lhu|lh|sh|lwu|lwc1|swc1|lw|sw|ld|sd|lq|sq)\(\s*\w+\s*,\s*\w+\s*,\s*([^)]+?)\s*\)")
FIELD_KEYS = {"off", "size", "type", "name", "label", "evidence"}
OPTIONAL_KEYS = {"label_addr", "label_raw", "unit", "min", "max", "step", "default", "wrap", "format", "enum",
                 "subfields", "menu", "note"}
TOP_KEYS = {"schema", "about", "records", "event_editor", "list_boxes", "globals"}
# MIPS load / store major opcodes -> width
OPC_WIDTH = {0x20: 1, 0x24: 1, 0x28: 1, 0x21: 2, 0x25: 2, 0x29: 2, 0x23: 4, 0x2B: 4, 0x31: 4, 0x39: 4, 0x27: 4,
             0x37: 8, 0x3F: 8, 0x1E: 16, 0x1F: 16}


class Checker:
    def __init__(self, verbose):
        self.errors = []
        self.warnings = []
        self.verbose = verbose
        self.stats = {"fields": 0, "evidence_src_body": 0, "evidence_header": 0, "evidence_elf": 0,
                      "evidence_elf_skipped": 0, "labels_checked": 0, "enum_strings_checked": 0,
                      "lbox_rows_checked": 0, "xrefs": 0}

    def err(self, where, msg):
        self.errors.append("%s: %s" % (where, msg))

    def warn(self, where, msg):
        self.warnings.append("%s: %s" % (where, msg))


# ---------------------------------------------------------------------------------------------------------------------
def load_constants():
    """name suffix 'ns::kName' and bare 'kName' -> set of values, from the game headers."""
    consts = {}
    inc = os.path.join(REPO, "game", "include", "p3fes", "game")
    ns_re = re.compile(r"namespace\s+([\w:]+)\s*\{")
    kv_re = re.compile(r"constexpr\s+\w+\s+(k\w+)\s*=\s*(-?(?:0x[0-9A-Fa-f]+|\d+))u?\s*[;,]")
    multi_re = re.compile(r"(k\w+)\s*=\s*(-?(?:0x[0-9A-Fa-f]+|\d+))")
    for root, _, files in os.walk(inc):
        for fn in files:
            if not fn.endswith(".h"):
                continue
            stack = []
            with open(os.path.join(root, fn), encoding="utf-8", errors="replace") as f:
                for line in f:
                    code = line.split("//", 1)[0]
                    m = ns_re.search(code)
                    if m:
                        stack.append(m.group(1).split("::")[-1])
                    if "constexpr" in code:
                        for name, val in multi_re.findall(code):
                            v = int(val, 0)
                            consts.setdefault(name, set()).add(v)
                            if stack:
                                consts.setdefault(stack[-1] + "::" + name, set()).add(v)
                    if "}" in code and "namespace" in line and stack:
                        stack.pop()
    return consts


def resolve(expr, consts):
    expr = expr.strip()
    try:
        return {int(expr, 0)}
    except ValueError:
        pass
    parts = expr.split("::")
    if len(parts) >= 2 and "::".join(parts[-2:]) in consts:
        return consts["::".join(parts[-2:])]
    return consts.get(parts[-1], set())


_body_cache = {}


def function_body(src, fn):
    key = (src, fn)
    if key in _body_cache:
        return _body_cache[key]
    path = os.path.join(REPO, src)
    body = None
    if os.path.isfile(path):
        tag = "// 0x%08X " % int(fn, 16)
        with open(path, encoding="utf-8", errors="replace") as f:
            lines = f.readlines()
        for i, line in enumerate(lines):
            if line.startswith(tag):
                out = []
                for line2 in lines[i:]:
                    out.append(line2)
                    if line2.startswith("}"):
                        break
                body = out
                break
    _body_cache[key] = body
    return body


class Elf:
    def __init__(self, path):
        self.data = open(path, "rb").read()
        phoff, = struct.unpack_from("<I", self.data, 0x1C)
        phentsize, phnum = struct.unpack_from("<HH", self.data, 0x2A)
        self.segs = []
        for i in range(phnum):
            t, off, va, pa, fs, ms, fl, al = struct.unpack_from("<8I", self.data, phoff + i * phentsize)
            if t == 1:
                self.segs.append((va, off, fs))

    def fo(self, va):
        for v, o, fs in self.segs:
            if v <= va < v + fs:
                return o + va - v
        return None

    def u32(self, va):
        return struct.unpack_from("<I", self.data, self.fo(va))[0]

    def s32(self, va):
        return struct.unpack_from("<i", self.data, self.fo(va))[0]

    def cstr(self, va):
        o = self.fo(va)
        if o is None:
            return None
        e = self.data.index(b"\0", o)
        return self.data[o:e].decode("cp932", "replace")


def load_function_sizes():
    path = os.path.join(REPO, "symbols", "functions.json")
    with open(path, encoding="utf-8") as f:
        return {int(r["a"], 16): int(r["s"]) for r in json.load(f)}


# ---------------------------------------------------------------------------------------------------------------------
def field_width_ok(width, f):
    if f["type"] in SCALAR:
        return width == f["size"]
    return True  # aggregate: any access inside counts


def offsets_wanted(f):
    if f["type"] in SCALAR:
        return {f["off"]}
    return set(range(f["off"], f["off"] + f["size"]))


def check_evidence(ck, where, f, consts, elf, fsizes):
    evs = f.get("evidence") or []
    if not evs:
        ck.err(where, "no evidence")
    for ev in evs:
        if "fn" in ev and "src" in ev:
            body = function_body(ev["src"], ev["fn"])
            if body is None:
                ck.err(where, "no readable body for %s in %s" % (ev["fn"], ev["src"]))
                continue
            want = offsets_wanted(f)
            hit = False
            for line in body:
                for op, arg in ACCESS_RE.findall(line):
                    vals = resolve(arg, consts)
                    if vals & want and field_width_ok(WIDTH[op], f):
                        hit = True
                        break
                if hit:
                    break
            if hit:
                ck.stats["evidence_src_body"] += 1
            else:
                ck.err(where, "%s (%s) has no %d-byte access at +%d" % (ev["fn"], ev["src"], f["size"], f["off"]))
        elif "src" in ev and "match" in ev:
            path = os.path.join(REPO, ev["src"])
            if not os.path.isfile(path):
                ck.err(where, "missing file %s" % ev["src"])
                continue
            nums = {str(f["off"]), "0x%X" % f["off"], "0x%x" % f["off"]}
            ok = False
            with open(path, encoding="utf-8", errors="replace") as fh:
                for line in fh:
                    if ev["match"] in line and any(re.search(r"(?<![0-9A-Za-z_])%s(?![0-9A-Za-z_])" % re.escape(n),
                                                             line) for n in nums):
                        ok = True
                        break
            if ok:
                ck.stats["evidence_header"] += 1
            else:
                ck.err(where, "no line in %s with '%s' and %d" % (ev["src"], ev["match"], f["off"]))
        elif "elf_fn" in ev:
            if elf is None:
                ck.stats["evidence_elf_skipped"] += 1
                continue
            a = int(ev["elf_fn"], 16)
            size = fsizes.get(a)
            if not size:
                ck.err(where, "%s not in symbols/functions.json" % ev["elf_fn"])
                continue
            want = offsets_wanted(f)
            hit = False
            for pc in range(a, a + size, 4):
                w = elf.u32(pc)
                opc = w >> 26
                if opc in OPC_WIDTH:
                    imm = w & 0xFFFF
                    imm = imm - 0x10000 if imm & 0x8000 else imm
                    if imm in want and field_width_ok(OPC_WIDTH[opc], f):
                        hit = True
                        break
            if hit:
                ck.stats["evidence_elf"] += 1
            else:
                ck.err(where, "ELF %s has no %d-byte access at +%d" % (ev["elf_fn"], f["size"], f["off"]))
        else:
            ck.err(where, "unknown evidence form %r" % (ev,))


def check_label(ck, where, label, addr, raw, elf):
    if addr is None:
        return
    if not re.fullmatch(r"0x[0-9A-F]+", addr):
        ck.err(where, "bad address %r" % addr)
        return
    if elf is None:
        return
    s = elf.cstr(int(addr, 16))
    if s is None:
        ck.err(where, "label address %s outside the ELF" % addr)
        return
    if raw is not None and s != raw:
        ck.err(where, "label_raw %r != ELF %r" % (raw, s))
    if label is not None and not s.strip().startswith(label):
        ck.err(where, "label %r is not the ELF string %r at %s" % (label, s, addr))
    ck.stats["labels_checked"] += 1


def check_enum(ck, where, enum, elf):
    if not isinstance(enum, dict):
        ck.err(where, "enum must be an object")
        return
    if "per_type" in enum:
        for k, sub in enum["per_type"].items():
            check_enum(ck, where + " per_type " + k, sub, elf)
        return
    vals = enum.get("values")
    if not isinstance(vals, dict) or not vals:
        ck.err(where, "enum without values")
        return
    for k in vals:
        if not re.fullmatch(r"-?\d+", k):
            ck.err(where, "enum key %r is not an integer" % k)
    if elf is None:
        return
    if "addr" in enum and "stride" in enum:
        base, stride = int(enum["addr"], 16), int(enum["stride"])
        for k, v in vals.items():
            if (elf.cstr(base + stride * int(k)) or "").strip() != v:
                ck.err(where, "enum %s=%r differs from the ELF string table" % (k, v))
            ck.stats["enum_strings_checked"] += 1
    elif "addr" in enum:
        base = int(enum["addr"], 16)
        first = min(int(k) for k in vals)
        for k, v in vals.items():
            p = elf.u32(base + 4 * (int(k) - first))
            if (elf.cstr(p) or "").strip() != v:
                ck.err(where, "enum %s=%r differs from the pointer table %s" % (k, v, enum["addr"]))
            ck.stats["enum_strings_checked"] += 1
    if "addrs" in enum:
        for k, a in enum["addrs"].items():
            if (elf.cstr(int(a, 16)) or "").strip() != vals.get(k):
                ck.err(where, "enum %s=%r differs from the ELF string at %s" % (k, vals.get(k), a))
            ck.stats["enum_strings_checked"] += 1


def check_field(ck, where, f, rsize, consts, elf, fsizes):
    ck.stats["fields"] += 1
    missing = FIELD_KEYS - set(f)
    if missing:
        ck.err(where, "missing keys %s" % sorted(missing))
        return
    extra = set(f) - FIELD_KEYS - OPTIONAL_KEYS
    if extra:
        ck.err(where, "unknown keys %s" % sorted(extra))
    if not isinstance(f["off"], int) or f["off"] < 0 or not isinstance(f["size"], int) or f["size"] <= 0:
        ck.err(where, "bad off / size")
        return
    t = f["type"]
    if t in SCALAR:
        if SCALAR[t] != f["size"]:
            ck.err(where, "type %s has size %d, not %d" % (t, SCALAR[t], f["size"]))
    elif AGG_RE.match(t):
        m = AGG_RE.match(t)
        unit = {"char": 1, "u8": 1, "s8": 1, "u16": 2, "s16": 2}.get(m.group(1), 4)
        if unit * int(m.group(2)) != f["size"]:
            ck.err(where, "type %s does not have size %d" % (t, f["size"]))
    else:
        ck.err(where, "unknown type %r" % t)
    if rsize is not None and f["off"] + f["size"] > rsize:
        ck.err(where, "past the record size %d" % rsize)
    if not re.fullmatch(r"[a-z][a-z0-9_]*", f["name"]):
        ck.err(where, "name %r is not snake_case" % f["name"])
    if "min" in f and "max" in f and isinstance(f["min"], (int, float)) and isinstance(f["max"], (int, float)):
        if f["min"] > f["max"]:
            ck.err(where, "min > max")
    if "step" in f:
        st = f["step"] if isinstance(f["step"], list) else [f["step"]]
        if not all(isinstance(x, (int, float)) and x > 0 for x in st):
            ck.err(where, "bad step")
    check_label(ck, where, f["label"], f.get("label_addr"), f.get("label_raw"), elf)
    if f["label"] is not None and "label_addr" not in f:
        ck.err(where, "label without label_addr")
    if "enum" in f:
        check_enum(ck, where, f["enum"], elf)
    for sf in f.get("subfields", []):
        if not re.fullmatch(r"\d+(-\d+)?", sf.get("bits", "")):
            ck.err(where, "bad subfield bits %r" % sf.get("bits"))
        else:
            hi = int(sf["bits"].split("-")[-1])
            if hi >= 8 * f["size"]:
                ck.err(where, "subfield %s past the field" % sf["bits"])
        check_label(ck, where + "." + sf.get("name", "?"), sf.get("label"), sf.get("label_addr"), sf.get("label_raw"),
                    elf)
        if "enum" in sf:
            check_enum(ck, where + "." + sf.get("name", "?"), sf["enum"], elf)
    check_evidence(ck, where, f, consts, elf, fsizes)


def check_overlaps(ck, where, fields):
    spans = sorted((f["off"], f["off"] + f["size"], f["name"]) for f in fields if "off" in f and "size" in f)
    for (a0, a1, an), (b0, b1, bn) in zip(spans, spans[1:]):
        if b0 < a1:
            ck.err(where, "fields %s and %s overlap" % (an, bn))


def field_index(records):
    """(record, variant or None) -> {off: field}"""
    idx = {}
    for rn, r in records.items():
        idx[(rn, None)] = {f["off"]: f for f in r.get("fields", [])}
        variants = r.get("variants", {})
        for vn, v in variants.items():
            d = dict(idx[(rn, None)])
            if "/" in vn and vn.split("/")[0] in variants:  # "X/Y" extends "X"
                d.update({f["off"]: f for f in variants[vn.split("/")[0]]["fields"]})
            d.update({f["off"]: f for f in v["fields"]})
            idx[(rn, vn)] = d
    return idx


XREF_RE = re.compile(r"^(\w+)(?:\[([^\]]+)\])?\+(\d+)(?:\.\.\+(\d+))?")


def check_xref(ck, where, text, idx):
    m = XREF_RE.match(text or "")
    if not m or m.group(1) not in {k[0] for k in idx}:
        return  # free text (a global, a menu, a tool)
    rec, var, off = m.group(1), m.group(2), int(m.group(3))
    if (rec, var) not in idx:
        ck.err(where, "unknown record / variant %s[%s]" % (rec, var))
        return
    fields = idx[(rec, var)]
    if off not in fields and not any(f["off"] <= off < f["off"] + f["size"] for f in fields.values()):
        ck.err(where, "%s has no field at +%d" % (text, off))
    ck.stats["xrefs"] += 1


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--json", default=DEFAULT_JSON)
    ap.add_argument("--elf", default=None)
    ap.add_argument("--no-elf", action="store_true")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args(argv)
    ck = Checker(args.verbose)
    with open(args.json, encoding="utf-8") as f:
        doc = json.load(f)
    elf = None
    if not args.no_elf:
        for p in ([args.elf] if args.elf else ELF_CANDIDATES):
            if p and os.path.isfile(p):
                elf = Elf(p)
                break
        if elf is None:
            ck.warn("elf", "ELF not found: label / table / elf_fn checks skipped")
    consts = load_constants()
    fsizes = load_function_sizes()

    if doc.get("schema") != "p3fes-debug-fields/1":
        ck.err("schema", "unexpected schema %r" % doc.get("schema"))
    miss = TOP_KEYS - set(doc)
    if miss:
        ck.err("top", "missing %s" % sorted(miss))
    records = doc.get("records", {})
    for rn, r in records.items():
        if not re.fullmatch(r"[A-Z][A-Za-z0-9]*", rn):
            ck.err(rn, "record name not CamelCase")
        rsize = r.get("size")
        if rsize is not None and (not isinstance(rsize, int) or rsize <= 0):
            ck.err(rn, "bad size")
        for f in r.get("fields", []):
            check_field(ck, "%s+%s" % (rn, f.get("off")), f, rsize, consts, elf, fsizes)
        check_overlaps(ck, rn, r.get("fields", []))
        for vn, v in r.get("variants", {}).items():
            if not v.get("unit_types"):
                ck.err("%s[%s]" % (rn, vn), "variant without unit_types")
            if elf is not None:
                for t, nm in zip(v.get("unit_types", []), v.get("unit_type_names", [])):
                    if (elf.cstr(0x69F1B0 + 30 * t) or "") != nm:
                        ck.err("%s[%s]" % (rn, vn), "unit type %d is not %r in the ELF" % (t, nm))
            for f in v["fields"]:
                check_field(ck, "%s[%s]+%s" % (rn, vn, f.get("off")), f, rsize, consts, elf, fsizes)
            check_overlaps(ck, "%s[%s]" % (rn, vn), v["fields"])

    idx = field_index(records)
    ee = doc.get("event_editor", {})
    seen = set()
    for m in ee.get("menus", []):
        where = "menu %s" % m.get("id")
        if m.get("id") in seen:
            ck.err(where, "duplicate id")
        seen.add(m.get("id"))
        if not isinstance(m.get("id"), int) or not 0 <= m["id"] < 48:
            ck.err(where, "id outside 0..47")
        if elf is not None:
            upd = elf.u32(0x6A0270 + 4 * m["id"])
            if (m.get("update") and int(m["update"], 16) != upd) or (not m.get("update") and upd):
                ck.err(where, "update %s differs from the menu table (0x%X)" % (m.get("update"), upd))
        check_label(ck, where + " title", m.get("title"), m.get("title_addr"), None, elf)
        for i, r in enumerate(m.get("rows", [])):
            check_label(ck, "%s row %d" % (where, i), r.get("label"), r.get("label_addr"), None, elf)
            check_xref(ck, "%s row %d" % (where, i), r.get("target"), idx)
    cols = ee.get("key_columns", {}).get("columns", [])
    for c in cols:
        check_label(ck, "column %d" % c["kind"], c["label"], c["label_addr"], c["label"], elf)
    for cl in ee.get("choice_lists", []):
        check_label(ck, "choice " + cl["title"], cl["title"], cl["title_addr"], None, elf)
        if elf is not None:
            base = int(cl["items_addr"], 16)
            for i, it in enumerate(cl["items"]):
                if (elf.cstr(elf.u32(base + 4 * i)) or "").strip() != it:
                    ck.err("choice " + cl["title"], "item %d %r differs from the ELF" % (i, it))
                ck.stats["enum_strings_checked"] += 1

    kinds = {"label": 0, "string": 1, "flag": 2, "int": 3, "float": 4}
    for b in doc.get("list_boxes", []):
        where = "lbox " + b["table"]
        if len(b["items"]) != b["count"]:
            ck.err(where, "count differs from items")
        base = int(b["table"], 16)
        for it in b["items"]:
            w = "%s item %d" % (where, it["index"])
            check_label(ck, w, it["label"], it["label_addr"], it.get("label_raw"), elf)
            if "writes" in it:
                check_xref(ck, w, it["writes"], idx)
            if elf is not None:
                e = base + 32 * it["index"]
                if "0x%X" % elf.u32(e) != it["label_addr"]:
                    ck.err(w, "descriptor label pointer differs")
                if elf.s32(e + 4) != kinds[it["kind"]]:
                    ck.err(w, "descriptor kind differs")
                if "min" in it and (elf.s32(e + 16) != it["min"] or elf.s32(e + 20) != it["max"] or
                                    elf.s32(e + 12) != it["value"]):
                    ck.err(w, "descriptor value / min / max differ")
                ck.stats["lbox_rows_checked"] += 1

    for w in ck.warnings:
        print("warning:", w)
    for e in ck.errors:
        print("ERROR:", e)
    nrec = len(records)
    nvar = sum(len(r.get("variants", {})) for r in records.values())
    nrows = sum(len(m.get("rows", [])) for m in ee.get("menus", []))
    print("check_debug_fields: %d records, %d variants, %d fields; %d menus / %d rows, %d list boxes / %d items, "
          "%d choice lists" % (nrec, nvar, ck.stats["fields"], len(ee.get("menus", [])), nrows,
                               len(doc.get("list_boxes", [])), sum(len(b["items"]) for b in doc.get("list_boxes", [])),
                               len(ee.get("choice_lists", []))))
    print("  evidence: %d readable-body accesses, %d header lines, %d ELF accesses (%d skipped); %d labels, %d enum / "
          "item strings, %d descriptor rows, %d cross-references checked" % (
              ck.stats["evidence_src_body"], ck.stats["evidence_header"], ck.stats["evidence_elf"],
              ck.stats["evidence_elf_skipped"], ck.stats["labels_checked"], ck.stats["enum_strings_checked"],
              ck.stats["lbox_rows_checked"], ck.stats["xrefs"]))
    print("  %s" % ("OK" if not ck.errors else "%d error(s)" % len(ck.errors)))
    return 1 if ck.errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
