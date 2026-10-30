"""Post-process p3fes_types output: validation against the header-known records and the replay snapshots,
types.json for agents, the proposed headers under game/include/p3fes/game/types/ and the report numbers
(docs/ANALYSIS/28_types.md).

    python -I tools/ours/types/types_build.py --exe build\\<tree>\\bin\\p3fes_types.exe [--elf <SLUS_216.21>]
        [--snapshots F:\\P3FES-PORT\\p3fes-port\\extracted\\_ours] [--out-json tools/ours/types/types.json]
        [--headers game/include/p3fes/game/types] [--report <file.md>] [--raw <types.raw.json>]

Without --exe it reads an existing --raw file. Everything it writes is our own analysis (offsets, widths, accessor
addresses, project names from seeds.json); snapshot values are only checked, never written out.
"""
import argparse
import json
import math
import re
import os
import struct
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
sys.path.insert(0, HERE)
import make_anchors  # noqa: E402

DEFAULT_ELF = r"F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21"
DEFAULT_SNAPS = r"F:\P3FES-PORT\p3fes-port\extracted\_ours"
SNAPSHOTS = ["battle_ref_6150", "b_5800", "dorm_replay_4900", "climb_ref_17000", "fusion_ref_6300", "shop_ref_4100"]
RAM_LO, RAM_HI = 0x100000, 0x2000000
CLASS_NAMES = {}  # class id -> "Record (type N)" for anchored classes
CODE_LO, CODE_HI = 0x100000, 0x5A1400

SCALAR = {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4, "ptr": 4, "f32": 4, "u64": 8, "s64": 8}

# The multiplayer-readiness areas (STATE.md / the user's criterion) -> proposed header files and the seed records
# whose recovered classes they hold, in order.
HEADERS = {
    "unit.h": ("Battle units: the 60-byte DatUnit and the battle-side unit record", ["DatUnit", "btlUnit", "btlTarget",
                                                                                 "Persona", "PartyMemberRecord"]),
    "battle_state.h": ("Battle state: the context behind gBtl, actions, packets", ["gBtl", "btlAction", "BtlPacket",
                                                                                   "BtlSetupBlock", "DatScriptContext",
                                                                                   "BtlMainStateRecord"]),
    "task.h": ("kwln tasks (the frame scheduler's record)", ["KwlnTask"]),
    "field_object.h": ("Field objects, the player and actors, the field context", ["FldUnit", "sField", "MtScene",
                                                                                  "SceneRes", "TreasureBox"]),
    "tartarus_floor.h": ("Tartarus floors: grid cells, block descriptors, floor entries", ["FldGridCell", "FldBlockDesc",
                                                                                          "FldDngFloorEntry",
                                                                                          "EncountRecord"]),
    "effect_node.h": ("Effect nodes and EPL objects", ["EffectNode", "EplModelObj", "EplNodeModelObj",
                                                      "EplClumpParticleObj", "EplTexParticleObj", "EffectInstance"]),
    "script_event.h": ("Script VM task and event state", ["ScrTask", "EventWork", "BfHeader", "BfLabel"]),
    "model.h": ("Model / animation instances (RenderWare objects)", ["RpAtomic", "RwFrame", "RpGeometry", "RwMatrix",
                                                                    "MdlModel", "RwCamera"]),
    "calendar.h": ("Calendar / date / global progress (gGlobalWork)", ["gGlobalWork"]),
}


def load_names():
    names = {}
    with open(os.path.join(REPO, "symbols", "p3fes.sym"), encoding="utf-8") as f:
        for ln in f:
            if ln.startswith("#"):
                continue
            p = ln.split()
            if len(p) >= 4:
                names[int(p[0], 16)] = p[3]
    return names


def hx(v):
    return "0x%X" % v


# --- snapshots ---------------------------------------------------------------------------------------------------

class Snap:
    def __init__(self, path):
        with open(os.path.join(path, "eeMemory.bin"), "rb") as f:
            self.mem = f.read()

    def u32(self, a):
        a &= 0x1FFFFFFF
        if a + 4 > len(self.mem) or a < 0:
            return None
        return struct.unpack_from("<I", self.mem, a)[0]

    def f32(self, a):
        a &= 0x1FFFFFFF
        if a + 4 > len(self.mem):
            return None
        return struct.unpack_from("<f", self.mem, a)[0]


def is_ptr(v):
    return v is not None and (v == 0 or (RAM_LO <= v < RAM_HI) or (0x70000000 <= v < 0x70004000))


def plausible_float(x):
    if x is None or math.isnan(x) or math.isinf(x):
        return False
    return x == 0.0 or 1e-12 < abs(x) < 1e8


# --- main analysis -----------------------------------------------------------------------------------------------

def run_tool(args, anchors_path):
    cmd = [os.path.abspath(args.exe), "--elf", args.elf, "--functions", os.path.join(REPO, "symbols", "functions.json"),
           "--chunks", os.path.join(REPO, "symbols", "function_chunks.txt"),
           "--jumptables", os.path.join(REPO, "symbols", "jumptables.json"),
           "--anchors", anchors_path, "--out", args.raw]
    t0 = time.time()
    r = subprocess.run(cmd, capture_output=True, text=True)
    dt = time.time() - t0
    sys.stderr.write(r.stderr)
    if r.returncode != 0:
        raise SystemExit("p3fes_types failed")
    return dt


def field_flags(f):
    k = f["k"]
    return {
        "float": "f" in k and not ("s" in k or "u" in k),
        "ptr": f["ptr"] is not None or f["called"] or f["code"],
        "code": f["code"] or f["called"],
    }


def class_kind_str(f):
    w = max(f["w"])
    k = f["k"]
    if f["code"] or f["called"]:
        return "fnptr"
    if f["ptr"] is not None and w == 4:
        return "ptr"
    if w == 16:
        return "vec4" if "v" in k else "u128"
    if w == 8:
        return "u64"
    if "f" in k and not ("s" in k or "u" in k):
        return "f32"
    signed = "s" in k and "u" not in k
    return {1: "s8" if signed else "u8", 2: "s16" if signed else "u16", 4: "s32" if signed else "u32"}.get(w, "u32")


def compare_record(rec, cls):
    """Header-known fields vs the recovered class: agree / conflict / missing, plus recovered-only offsets."""
    size = rec.get("size")
    rf = {f["off"]: f for f in cls["fields"]} if cls else {}
    known = [f for f in rec["fields"] if not f["name"].startswith(("unk", "pad"))]
    res = {"known": len(known), "found": 0, "conflicts": [], "missing": 0, "new": 0}
    covered = set()
    for f in known:
        lo, hi = f["off"], f["off"] + f["width"]
        scalar = f["type"] in SCALAR
        for o in rf:
            if lo <= o < hi:
                covered.add(o)
        if not cls:
            res["missing"] += 1
            continue
        if scalar:
            g = rf.get(lo)
            inside = [o for o in rf if lo < o < hi and max(rf[o]["w"]) <= 4]
            if g is not None:
                ws = [w for w in g["w"] if w <= 4 or w == f["width"]]
                if f["width"] in g["w"] or not ws:
                    res["found"] += 1
                else:
                    res["conflicts"].append({"off": lo, "header": f["type"], "recovered": g["w"]})
            elif inside:
                res["conflicts"].append({"off": lo, "header": f["type"], "recovered_inside": inside})
            else:
                res["missing"] += 1
        else:
            if any(lo <= o < hi for o in rf):
                res["found"] += 1
            else:
                res["missing"] += 1
    if cls:
        for o in rf:
            if o in covered or o < 0:
                continue
            if size and o >= size:
                continue
            res["new"] += 1
    return res


def global_views(raw, seeds, classes, by_anchor):
    """Records that live at a fixed address (gobj anchors) are mostly accessed through absolute addresses (lui/addiu,
    gp-relative), which p3fes_types records per address rather than per object. Fold those accesses into the
    record's class: plain accesses inside [base, base + size) at their offset, indexed accesses whose stride is a
    multiple of the size at their offset modulo the size (arrays of the record)."""
    by_addr = {}
    for g in raw["globals"]:
        by_addr.setdefault(int(g[0], 16), []).append(g)
    addrs = sorted(by_addr)
    import bisect
    next_id = max(classes) + 1 if classes else 1
    for rec in seeds["records"]:
        bases = [int(a["addr"], 16) for a in rec.get("anchors", []) if a["how"] == "gobj"]
        if not bases:
            continue
        size = rec.get("size") or max(f["off"] + f["width"] for f in rec["fields"])
        fields = {}
        for base in bases[:64]:
            span = size  # indexed accesses address their array through its base (la + index)
            i = bisect.bisect_left(addrs, base)
            while i < len(addrs) and addrs[i] < base + span:
                a = addrs[i]
                i += 1
                for g in by_addr[a]:
                    stride = g[1]
                    rel = a - base
                    if stride == 0 and rel < size:
                        off = rel
                    elif stride and size and stride % size == 0:
                        off = rel % size
                    else:
                        continue
                    f = fields.setdefault(off, {"off": off, "w": [], "k": "", "ld": 0, "st": 0, "n_fns": 0, "fns": [],
                                                "ptr": None, "poly": False, "called": False, "code": False,
                                                "gview": True})
                    for w in g[2]:
                        if w not in f["w"]:
                            f["w"].append(w)
                    f["k"] = "".join(sorted(set(f["k"]) | set(g[3])))
                    f["ld"] += g[4]
                    f["st"] += g[5]
                    for fn in g[7]:
                        if fn not in f["fns"]:
                            f["fns"].append(fn)
                    f["n_fns"] = max(f["n_fns"], g[6], len(f["fns"]))
                    if stride == 0 and g[8] is not None and f["ptr"] is None:
                        f["ptr"] = g[8]
        if not fields:
            continue
        cls = by_anchor.get(rec["name"])
        if cls is None:
            cls = {"id": next_id, "anchor": rec["name"], "size_min": 0, "called": False, "n_members": 0, "params": [],
                   "n_params": 0, "rets": [], "gslots": [], "gobjs": [hx(b) for b in bases[:16]], "n_stack": 0,
                   "n_deref": 0, "n_callres": 0, "code": [], "fields": [], "arrays": [], "embeds": []}
            next_id += 1
            raw["classes"].append(cls)
            classes[cls["id"]] = cls
            by_anchor[rec["name"]] = cls
        have = {f["off"] for f in cls["fields"]}
        for off, f in fields.items():
            if off not in have:
                f["w"].sort()
                cls["fields"].append(f)
        cls["fields"].sort(key=lambda f: f["off"])
        cls["size_min"] = max([cls["size_min"]] + [f["off"] + max(f["w"]) for f in cls["fields"]])


def build(args):
    names = load_names()
    seeds = make_anchors.load_seeds(args.seeds)
    timing = {}
    if args.exe:
        anchors_path = args.raw + ".anchors.txt"
        lines = make_anchors.anchor_lines(seeds)
        with open(anchors_path, "w", encoding="utf-8", newline="\n") as f:
            f.write("\n".join(lines) + "\n")
        timing["p3fes_types_s"] = round(run_tool(args, anchors_path), 2)
    t0 = time.time()
    with open(args.raw, encoding="utf-8") as f:
        raw = json.load(f)
    classes = {c["id"]: c for c in raw["classes"]}
    by_anchor = {}
    for c in raw["classes"]:
        if c["anchor"]:
            by_anchor.setdefault(c["anchor"], c)
    recs = {r["name"]: r for r in seeds["records"]}
    global_views(raw, seeds, classes, by_anchor)
    CLASS_NAMES.update({c["id"]: "%s (type %d)" % (c["anchor"], c["id"]) for c in raw["classes"] if c["anchor"]})
    # A field is a function pointer only when its pointee is pure code (callbacks stored, called through); a pointee
    # class with data fields that is also "called" got there through a merge, so the field stays a data pointer.
    for c in raw["classes"]:
        for f in c["fields"]:
            if (f["code"] or f["called"]) and f["ptr"] is not None and classes.get(f["ptr"], {}).get("fields"):
                f["code"] = f["called"] = False

    # 1. header agreement
    seed_cmp = {}
    tot = {"records": 0, "anchored": 0, "known": 0, "found": 0, "conflicts": 0, "missing": 0, "new": 0}
    for r in seeds["records"]:
        c = by_anchor.get(r["name"])
        res = compare_record(r, c)
        seed_cmp[r["name"]] = res
        tot["records"] += 1
        if c:
            tot["anchored"] += 1
            tot["known"] += res["known"]
            tot["found"] += res["found"]
            tot["conflicts"] += len(res["conflicts"])
            tot["missing"] += res["missing"]
            tot["new"] += res["new"]

    # 2. snapshots: instances by BFS from global slots / objects, field plausibility
    snap_stats = {}
    inst_counts = {}  # class id -> {snap: n}
    field_checks = {}  # (cid, off) -> [pass, total]
    raw_checks = [0, 0]  # every check, accepted or rejected instance
    hdr_at = {}  # record -> byte offset -> documented type (every byte of a documented field)
    for r in seeds["records"]:
        m = hdr_at.setdefault(r["name"], {})
        for f in r["fields"]:
            for b in range(f["off"], f["off"] + max(1, f["width"])):
                m[b] = f["type"] if b == f["off"] else "inside"
    snap_rejected = {}
    if args.snapshots and os.path.isdir(args.snapshots):
        gslot_cls = {}
        for g in raw["globals"]:
            if g[1] == 0 and g[8] is not None:
                gslot_cls[int(g[0], 16)] = g[8]
        gobj_cls = {}
        for c in raw["classes"]:
            for a in c["gobjs"]:
                gobj_cls.setdefault(int(a, 16), c["id"])
        for sn in SNAPSHOTS:
            path = os.path.join(args.snapshots, sn)
            if not os.path.isfile(os.path.join(path, "eeMemory.bin")):
                continue
            s = Snap(path)
            seen = {}  # (cid, addr)
            frontier = []
            for a, cid in gslot_cls.items():
                p = s.u32(a)
                if p and RAM_LO <= p < RAM_HI:
                    frontier.append((cid, p, 0))
            for a, cid in gobj_cls.items():
                frontier.append((cid, a, 0))
            per_cls = {}
            rejected = 0
            while frontier:
                cid, addr, depth = frontier.pop()
                if (cid, addr) in seen or per_cls.get(cid, 0) >= 256:
                    continue
                c = classes.get(cid)
                if not c:
                    continue
                seen[(cid, addr)] = True
                results = []  # (off, ok, follow)
                for f in c["fields"]:
                    if f["off"] < 0 or f["off"] > 0x100000 or max(f["w"]) != 4:
                        continue
                    a = addr + f["off"]
                    fl = field_flags(f)
                    hf = hdr_at.get(c["anchor"], {}).get(f["off"]) if c["anchor"] else None
                    if hf is not None:  # a documented field: its documented type decides the check
                        fl = {"code": False, "ptr": hf == "ptr", "float": hf == "f32"}
                        if not (fl["ptr"] or fl["float"]):
                            continue
                    v = s.u32(a)
                    if v is None:
                        continue
                    if fl["code"]:
                        results.append((f["off"], v == 0 or CODE_LO <= v < CODE_HI, None))
                    elif fl["ptr"]:
                        ok = is_ptr(v)
                        follow = None
                        if ok and v and f["ptr"] is not None and not f["poly"] and depth < 6 and (v & 3) == 0:
                            follow = (f["ptr"], v, depth + 1)
                        results.append((f["off"], ok, follow))
                    elif fl["float"]:
                        results.append((f["off"], plausible_float(s.f32(a)), None))
                raw_checks[0] += sum(1 for r in results if r[1])
                raw_checks[1] += len(results)
                # An instance is accepted when most of its checkable fields hold plausible values: a pointer that
                # reaches freed or reused memory (a stale global, a polymorphic field) would otherwise count its
                # garbage against every field of the class.
                npass = sum(1 for r in results if r[1])
                if results and npass < 0.8 * len(results):
                    rejected += 1
                    continue
                per_cls[cid] = per_cls.get(cid, 0) + 1
                for off, ok, follow in results:
                    fc = field_checks.setdefault((cid, off), [0, 0])
                    fc[1] += 1
                    if ok:
                        fc[0] += 1
                    if follow:
                        frontier.append(follow)
            for cid, n in per_cls.items():
                inst_counts.setdefault(cid, {})[sn] = n
            snap_rejected[sn] = rejected
            snap_stats[sn] = {"instances": sum(per_cls.values()), "classes_with_instances": len(per_cls),
                              "rejected": rejected}
    fc_tot = [0, 0]
    fc_ptr = [0, 0]
    fc_flt = [0, 0]
    fc_anch = [0, 0]
    fc_many = [0, 0]
    for (cid, off), (p, t) in field_checks.items():
        fc_tot[0] += p
        fc_tot[1] += t
        f = next((x for x in classes[cid]["fields"] if x["off"] == off), None)
        if f is not None:
            fl = field_flags(f)
            tgt = fc_ptr if (fl["ptr"] or fl["code"]) else fc_flt
            tgt[0] += p
            tgt[1] += t
            if classes[cid]["anchor"]:
                fc_anch[0] += p
                fc_anch[1] += t
            if f["n_fns"] >= 3:
                fc_many[0] += p
                fc_many[1] += t
    fc_tot += fc_anch + fc_many + raw_checks

    # 3. confidence per field
    def confidence(cid, f):
        n = f["n_fns"]
        chk = field_checks.get((cid, f["off"]))
        bad = chk is not None and chk[1] >= 4 and chk[0] < 0.9 * chk[1]
        good = chk is not None and chk[1] >= 1 and chk[0] == chk[1]
        if bad:
            return "low"
        if n >= 3 or (n >= 2 and good):
            return "high"
        if n >= 2 or good:
            return "medium"
        return "low"

    # 4. types.json (compact)
    keep = set()
    for c in raw["classes"]:
        if c["anchor"] or len(c["fields"]) >= 2 or c["n_params"] >= 1 and len(c["fields"]) >= 1:
            keep.add(c["id"])
    out_classes = []
    for c in raw["classes"]:
        if c["id"] not in keep:
            continue
        rec = recs.get(c["anchor"]) if c["anchor"] else None
        hdr_fields = {f["off"]: f for f in rec["fields"]} if rec else {}
        fields = []
        for f in c["fields"]:
            e = {"off": f["off"], "w": f["w"], "type": class_kind_str(f), "n_fns": f["n_fns"],
                 "fns": f["fns"][:4], "conf": confidence(c["id"], f)}
            if f["ptr"] is not None and f["ptr"] in keep:
                e["ptr"] = f["ptr"]
            if f["poly"]:
                e["poly"] = True
            if f["code"] or f["called"]:
                e["fnptr"] = True
            if f["st"] and not f["ld"]:
                e["write_only"] = True
            h = hdr_fields.get(f["off"])
            if h:
                e["name"] = h["name"]
            chk = field_checks.get((c["id"], f["off"]))
            if chk:
                e["snap"] = chk
            fields.append(e)
        oc = {"id": c["id"], "name": c["anchor"] or ("type_%d" % c["id"]), "size_min": c["size_min"],
              "n_params": c["n_params"], "params": c["params"][:24], "gslots": c["gslots"][:16],
              "gobjs": c["gobjs"][:16], "fields": fields}
        if c["anchor"]:
            oc["header"] = rec["header"] + ":" + str(rec["line"])
            if rec.get("size"):
                oc["size_header"] = rec["size"]
        if c["arrays"]:
            oc["arrays"] = [{"stride": a["stride"], "off": a["off"], "w": a["w"], "n_fns": a["n_fns"]}
                            for a in c["arrays"][:64]]
        if c["code"]:
            oc["code"] = c["code"][:64]
        if c["called"]:
            oc["called"] = True
        if c["id"] in inst_counts:
            oc["instances"] = inst_counts[c["id"]]
        out_classes.append(oc)
    funcs = {}
    for fa, fe in raw["functions"].items():
        p = [x if x in keep else None for x in fe["p"]]
        while p and p[-1] is None:
            p.pop()
        r = fe["r"] if fe["r"] in keep else None
        if p or r:
            funcs[fa] = {"p": p} if r is None else {"p": p, "r": r}
    gl = []
    for g in raw["globals"]:
        if g[1] != 0:
            continue
        e = [g[0], g[2], g[3], g[6]]
        if g[8] is not None and g[8] in keep:
            e.append(g[8])
        gl.append(e)
    doc = {
        "about": "p3fes_types output (docs/ANALYSIS/28_types.md): proposed struct layouts recovered from the whole "
                 "program; names only where seeds.json (the project's headers) establish them.",
        "stats": raw["stats"],
        "validation": {"headers": tot, "snapshots": snap_stats,
                       "snapshot_field_checks": {"all": fc_tot[:2], "pointers": fc_ptr, "floats": fc_flt,
                                                 "anchored": fc_tot[2:4], "three_plus_accessors": fc_tot[4:6],
                                                 "before_acceptance": fc_tot[6:8]}},
        "classes": out_classes,
        "functions": funcs,
        "globals_format": ["addr", "widths", "kinds", "n_fns", "pointee class"],
        "globals": gl,
    }
    with open(args.out_json, "w", encoding="utf-8", newline="\n") as f:
        json.dump(doc, f, separators=(",", ":"))
    timing["post_s"] = round(time.time() - t0, 2)

    # 5. headers
    if args.headers:
        write_headers(args.headers, by_anchor, recs, seed_cmp, field_checks, confidence, names, inst_counts, keep)

    # 6. report
    rep = report(raw, tot, seed_cmp, snap_stats, fc_tot, fc_ptr, fc_flt, by_anchor, recs, inst_counts, timing,
                 len(out_classes), os.path.getsize(args.out_json), names, confidence, field_checks)
    if args.report:
        with open(args.report, "w", encoding="utf-8", newline="\n") as f:
            f.write(rep)
    print(rep)


def fn_label(names, a):
    a = int(a, 16) if isinstance(a, str) else a
    return "%s 0x%X" % (names.get(a, "sub_%X" % a), a)


def ctype(t):
    return {"u8": "u8", "s8": "s8", "u16": "u16", "s16": "s16", "u32": "u32", "s32": "s32", "f32": "f32",
            "ptr": "u32", "fnptr": "u32", "u64": "u64", "u128": "u128", "vec4": "f32x4"}.get(t, "u32")


def write_headers(outdir, by_anchor, recs, seed_cmp, field_checks, confidence, names, inst_counts, keep):
    os.makedirs(outdir, exist_ok=True)
    common = [
        "// Shared scalar names of the proposed type headers (GENERATED by tools/ours/types/types_build.py).",
        "// The structs are byte-packed: offsets are the guest's, never the host compiler's padding.",
        "#pragma once",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "",
        "namespace p3fes::game::types {",
        "",
        "using u8 = std::uint8_t; using s8 = std::int8_t; using u16 = std::uint16_t; using s16 = std::int16_t;",
        "using u32 = std::uint32_t; using s32 = std::int32_t; using u64 = std::uint64_t; using f32 = float;",
        "struct u128 { u32 w[4]; };        // a 128-bit lq/sq quadword",
        "struct f32x4 { f32 x, y, z, w; };  // a VU0 vector (lqc2/sqc2)",
        "",
        "}  // namespace p3fes::game::types",
    ]
    with open(os.path.join(outdir, "common.h"), "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(common) + "\n")
    for fname, (title, members) in HEADERS.items():
        lines = []
        guard_ns = "p3fes::game::types"
        lines.append("// %s -- PROPOSED layouts (p3fes_types, docs/ANALYSIS/28_types.md). GENERATED by" % title)
        lines.append("// tools/ours/types/types_build.py: do not edit by hand; confirm fields in your slice and feed names back")
        lines.append("// through tools/ours/types/seeds.json (brief: \"Type recovery\"). Not included by game code yet.")
        lines.append("//")
        lines.append("// Per field: /* +offset width */, a confidence (known = the project header documents it; high = 3+")
        lines.append("// accessor functions, or 2 and every snapshot instance plausible; medium = 2 or snapshot-plausible;")
        lines.append("// low = one accessor or failed snapshot checks) and accessor functions as evidence. unk_XX = recovered,")
        lines.append("// unnamed; names come only from the project's headers (ADR-0009). Guest pointers are u32.")
        lines.append("#pragma once")
        lines.append("")
        lines.append("#include \"p3fes/game/types/common.h\"")
        lines.append("")
        lines.append("namespace %s {" % guard_ns)
        lines.append("")
        lines.append("#pragma pack(push, 1)")
        lines.append("")
        for name in members:
            rec = recs.get(name)
            if not rec:
                continue
            cls = by_anchor.get(name)
            lines += struct_text(name, rec, cls, seed_cmp.get(name), field_checks, confidence, names, inst_counts)
            lines.append("")
        lines.append("#pragma pack(pop)")
        lines.append("")
        lines.append("}  // namespace %s" % guard_ns)
        with open(os.path.join(outdir, fname), "w", encoding="utf-8", newline="\n") as f:
            f.write("\n".join(lines) + "\n")


def ident(s):
    out = "".join(ch if ch.isalnum() or ch == "_" else "_" for ch in s)
    if out and out[0].isdigit():
        out = "f_" + out
    return out or "unk"


def struct_text(name, rec, cls, cmpres, field_checks, confidence, names, inst_counts):
    size = rec.get("size")
    rf = {f["off"]: f for f in cls["fields"]} if cls else {}
    hdr = {f["off"]: f for f in rec["fields"]}
    # Entries: header fields first (authoritative), then recovered offsets not inside a header field.
    entries = []  # (off, width, ctype, name, comment)
    occupied = []
    for off in sorted(hdr):
        h = hdr[off]
        w = h["width"]
        t = h["type"]
        g = rf.get(off)
        ev = ""
        if g:
            ev = "; recovered %s by %d fn%s: %s" % ("/".join(str(x) for x in g["w"]), g["n_fns"],
                                                    "" if g["n_fns"] == 1 else "s",
                                                    ", ".join(fn_label(names, a) for a in g["fns"][:3]))
        # The header's identifier when it is one; a descriptor ("u16 +4", "block depth") stays in the comment.
        nm = h["name"]
        if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", nm):
            fname, desc = nm, ""
        else:
            fname, desc = "f_%X" % off, " \"%s\"" % nm.replace("*/", "")
        if t in SCALAR:
            ct = {"ptr": "u32"}.get(t, t)
            entries.append((off, w, ct, fname, "known%s%s" % (desc, ev)))
        else:
            entries.append((off, w, "u8[%d]" % w, fname, "known: %s%s%s" % (t, desc, ev)))
        occupied.append((off, off + w))

    def inside(o, w):
        return any(a <= o < b or a < o + w <= b or (o <= a and o + w >= b) for a, b in occupied)

    beyond = []
    if cls:
        for off in sorted(rf):
            f = rf[off]
            if off < 0:
                continue
            w = max(x for x in f["w"])
            t = class_kind_str(f)
            if t in ("u128", "vec4") and off % 16:
                w = 4
                t = "u32"
            if size and off + w > size:
                beyond.append(off)
                continue
            if inside(off, w):
                # an access inside a documented pad / unknown field: worth a line for the slice that confirms it
                h = next((x for x in rec["fields"] if x["off"] <= off < x["off"] + x["width"]), None)
                if h is not None and h["name"].startswith(("pad", "unk")) and off != h["off"]:
                    entries.append((off, 0, class_kind_str(f), "", "%s accessed inside %s (%s; %d fn%s: %s)" % (
                        class_kind_str(f), h["name"], confidence(cls["id"], f), f["n_fns"],
                        "" if f["n_fns"] == 1 else "s", ", ".join(fn_label(names, a) for a in f["fns"][:3]))))
                continue
            conf = confidence(cls["id"], f)
            chk = field_checks.get((cls["id"], off))
            extra = ""
            if t == "fnptr":
                extra = " fnptr"
            elif t == "ptr" and f["ptr"] is not None:
                extra = " ptr -> %s" % CLASS_NAMES.get(f["ptr"], "type_%d" % f["ptr"])
            if f.get("poly"):
                extra += " (polymorphic pointee)"
            snap = " snap %d/%d" % tuple(chk) if chk else ""
            entries.append((off, w, ctype(t), "unk_%X" % off, "%s%s%s; %d fn%s: %s" % (
                conf, extra, snap, f["n_fns"], "" if f["n_fns"] == 1 else "s",
                ", ".join(fn_label(names, a) for a in f["fns"][:3]))))
            occupied.append((off, off + w))
    entries.sort(key=lambda e: e[0])
    out = []
    loc = rec["header"] + ":" + str(rec["line"])
    out.append("// %s -- %s. Documented in %s." % (name, rec.get("note", "").split(".")[0][:120], loc))
    if cls:
        out.append("// Recovered class %d: %d fixed-offset fields, %d parameter slots (e.g. %s), size >= 0x%X%s." % (
            cls["id"], len(cls["fields"]), cls["n_params"],
            ", ".join(fn_label(names, p[0]) + " a%d" % p[1] for p in cls["params"][:3]) or "none",
            cls["size_min"], "" if not inst_counts.get(cls["id"]) else
            "; snapshot instances " + ", ".join("%s %d" % kv for kv in inst_counts[cls["id"]].items())))
        if cmpres:
            out.append("// Against the header: %d known fields, %d found, %d conflicting, %d recovered-only offsets." % (
                cmpres["known"], cmpres["found"], len(cmpres["conflicts"]), cmpres["new"]))
        if beyond:
            out.append("// %d accessed offsets lie beyond the documented size (views merged from other records): %s" % (
                len(beyond), ", ".join("+0x%X" % o for o in beyond[:12]) + (" ..." if len(beyond) > 12 else "")))
    else:
        out.append("// No recovered class (the record's anchors reached no accesses).")
    out.append("struct %s {" % ident(name))
    pos = 0
    names_used = set()
    for off, w, ct, nm, cm in entries:
        if w == 0:
            out.append("    // +0x%X %s" % (off, cm))
            continue
        if off < pos:
            out.append("    // +0x%X %s %s overlaps the previous field (%s)" % (off, ct, nm, cm))
            continue
        if off > pos:
            out.append("    u8 gap_%X[0x%X];" % (pos, off - pos))
        base = nm
        k = 2
        while nm in names_used:
            nm = "%s_%d" % (base, k)
            k += 1
        names_used.add(nm)
        if ct.startswith("u8["):
            out.append("    /* +0x%X %d */ u8 %s[%d];  // %s" % (off, w, nm, w, cm))
        else:
            out.append("    /* +0x%X %d */ %s %s;  // %s" % (off, w, ct, nm, cm))
        pos = off + w
    if size and pos < size:
        out.append("    u8 gap_%X[0x%X];" % (pos, size - pos))
        pos = size
    out.append("};")
    if size:
        out.append("static_assert(sizeof(%s) == 0x%X);" % (ident(name), size))
    return out


def report(raw, tot, seed_cmp, snap_stats, fc_tot, fc_ptr, fc_flt, by_anchor, recs, inst_counts, timing, n_out,
           json_size, names, confidence, field_checks):
    st = raw["stats"]
    L = []
    L.append("## Numbers (generated by tools/ours/types/types_build.py)")
    L.append("")
    L.append("| | |")
    L.append("|---|---|")
    L.append("| functions analysed | %d of %d |" % (st["analysed"], st["functions"]))
    L.append("| instruction visits (dataflow) | %d |" % st["instructions"])
    L.append("| type variables / accesses / absolute-address accesses | %d / %d / %d |" % (
        st["type_vars"], st["accesses"], st["global_accesses"]))
    L.append("| constraints / unions / vetoes (anchor clashes) | %d / %d / %d (%d) |" % (
        st["constraints"], st["unions"], st["vetoes"], st["vetoes_anchor"]))
    L.append("| polymorphic callee sides (not linked) | %d |" % st["polymorphic_links"])
    L.append("| classes with fields (raw) / in types.json | %d / %d |" % (st["classes"], n_out))
    multi = sum(1 for c in raw["classes"] if len(c["fields"]) >= 4)
    L.append("| classes with >= 4 fields | %d |" % multi)
    L.append("| types.json | %.1f MB |" % (json_size / 1e6))
    L.append("| runtime | p3fes_types %s s (phase 1 %.2f s); post-processing %s s |" % (
        timing.get("p3fes_types_s", "?"), st["phase1_s"], timing.get("post_s", "?")))
    L.append("")
    L.append("Header agreement (seeds.json: %d records from the project's headers and topic docs, %d with a recovered "
             "class): %d known fields, **%d found**, **%d conflicting**, %d not accessed through the anchors, "
             "%d recovered-only offsets inside the documented sizes." % (
                 tot["records"], tot["anchored"], tot["known"], tot["found"], tot["conflicts"], tot["missing"],
                 tot["new"]))
    L.append("")
    L.append("Snapshots: field checks (pointer fields hold 0 or a RAM / code address, float fields plausible floats) "
             "on accepted instances reached from global pointers: %d of %d pass (pointers %d/%d, floats %d/%d); fields of "
             "anchored records %d/%d; fields with >= 3 accessor functions %d/%d." % (
                 fc_tot[0], fc_tot[1], fc_ptr[0], fc_ptr[1], fc_flt[0], fc_flt[1], fc_tot[2], fc_tot[3], fc_tot[4],
                 fc_tot[5]))
    L.append("")
    L.append("Before the acceptance filter (every instance reached): %d of %d checks pass." % (fc_tot[6], fc_tot[7]))
    L.append("")
    L.append("| snapshot | instances accepted | rejected (< 80 % of fields plausible) | classes with instances |")
    L.append("|---|---|---|---|")
    for sn, v in snap_stats.items():
        L.append("| %s | %d | %d | %d |" % (sn, v["instances"], v["rejected"], v["classes_with_instances"]))
    L.append("")
    L.append("Per record (multiplayer areas first):")
    L.append("")
    L.append("| record | class | fields recovered | params | known | found | conflicts | new | snapshot instances |")
    L.append("|---|---|---|---|---|---|---|---|---|")
    order = []
    for _, (_, members) in HEADERS.items():
        order += members
    order += sorted(r for r in recs if r not in order)
    for nm in order:
        c = by_anchor.get(nm)
        r = seed_cmp.get(nm)
        if not c or not r:
            continue
        ins = inst_counts.get(c["id"], {})
        L.append("| %s | %d | %d | %d | %d | %d | %d | %d | %s |" % (
            nm, c["id"], len(c["fields"]), c["n_params"], r["known"], r["found"], len(r["conflicts"]), r["new"],
            ", ".join("%s %d" % kv for kv in ins.items()) or "-"))
    L.append("")
    L.append("Conflicts (a documented scalar field accessed with another width, or an access starting inside it):")
    L.append("")
    L.append("| record | offset | header | recovered | accessors |")
    L.append("|---|---|---|---|---|")
    for nm in order:
        c = by_anchor.get(nm)
        r = seed_cmp.get(nm)
        if not c or not r:
            continue
        for cf in r["conflicts"]:
            h = next(x for x in recs[nm]["fields"] if x["off"] == cf["off"])
            if "recovered" in cf:
                f = next((x for x in c["fields"] if x["off"] == cf["off"]), None)
                what = "width %s" % "/".join(str(w) for w in cf["recovered"])
            else:
                f = next((x for x in c["fields"] if x["off"] == cf["recovered_inside"][0]), None)
                what = "access at " + ", ".join("+0x%X" % o for o in cf["recovered_inside"])
            acc = ", ".join(fn_label(names, a) for a in (f["fns"][:2] if f else []))
            L.append("| %s | +0x%X | %s %s | %s | %s |" % (nm, cf["off"], h["type"], h["name"], what, acc))
    L.append("")
    return "\n".join(L) + "\n"


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("--exe", help="p3fes_types.exe (runs it); without it --raw must exist")
    ap.add_argument("--elf", default=DEFAULT_ELF)
    ap.add_argument("--raw", default=os.path.join(REPO, "build", "types.raw.json"))
    ap.add_argument("--seeds", default=os.path.join(HERE, "seeds.json"))
    ap.add_argument("--snapshots", default=DEFAULT_SNAPS)
    ap.add_argument("--out-json", default=os.path.join(HERE, "types.json"))
    ap.add_argument("--headers", default=None)
    ap.add_argument("--report", default=None)
    args = ap.parse_args(argv)
    build(args)


if __name__ == "__main__":
    main(sys.argv[1:])
