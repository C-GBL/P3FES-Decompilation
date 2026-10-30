#!/usr/bin/env python3
"""VU1 micro-instruction census over the 114 dumped microprograms.

Inputs (read-only):
  symbols/p3fes.sym            rows `vu1_prog_NNN_<family>` at the DMA ret-tag VA
  ida/logs/vu1/<code_va>.bin   gitignored microcode dumps, code_va = tag VA + 0xC

Outputs (owned by this script):
  symbols/vu1_micro_census.json
  docs/ANALYSIS/09_vu1_micro_census.md   -- only the GENERATED block is rewritten;
                                           the narrative above it is hand-written.

Everything here is derived from the dump bytes with tools/ours/vu1/vu1_decode.py.
Branch targets, loop shapes and E-segments are static readings of the code, not
observed execution.

Usage: python tools/ours/vu1/vu1_census.py [--repo DIR] [--no-doc]
"""
from __future__ import annotations

import argparse
import datetime as _dt
import hashlib
import json
import os
import re
import sys
from collections import Counter, defaultdict
from typing import Dict, List, Optional, Tuple

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import vu1_decode as vd  # noqa: E402

SYM_RE = re.compile(r"^([0-9a-fA-F]{8})\s+\S+\s+\S+\s+(vu1_prog_(\d{3})_(\w+))\s*$")

EFU_Q = {"DIV", "SQRT", "RSQRT", "WAITQ"}
EFU_P = {"ESADD", "ERSADD", "ELENG", "ERLENG", "EATANxy", "EATANxz", "ESUM", "ESQRT", "ERSQRT", "ERCPR",
         "WAITP", "ESIN", "EATAN", "EEXP", "MFP"}
FLAG_OPS_CLIP = {"FCEQ", "FCSET", "FCAND", "FCOR", "FCGET"}
FLAG_OPS_STATUS = {"FSEQ", "FSSET", "FSAND", "FSOR"}
FLAG_OPS_MAC = {"FMEQ", "FMAND", "FMOR"}
RAND_OPS = {"RNEXT", "RGET", "RINIT", "RXOR"}
BRANCH_OPS = {"B", "BAL", "JR", "JALR", "IBEQ", "IBNE", "IBLTZ", "IBGTZ", "IBLEZ", "IBGEZ"}

# Families and the boot-path reading used in the doc (inferred, see narrative).
BOOT_PATH_FAMILIES = ("rt2d_stroke", "rt2d_font", "rt2d_fill", "g3_generic", "null_transform",
                      "ptank_spr2d", "ptank_spr3d", "ptank_xform")


# ---------------------------------------------------------------------------
# inventory
# ---------------------------------------------------------------------------

def load_inventory(repo: str) -> List[dict]:
    rows = []
    with open(os.path.join(repo, "symbols", "p3fes.sym"), encoding="utf-8") as fh:
        for line in fh:
            m = SYM_RE.match(line.rstrip("\n"))
            if not m:
                continue
            tag_va = int(m.group(1), 16)
            rows.append({
                "index": int(m.group(3)),
                "name": m.group(2),
                "family": m.group(4),
                "tag_va": tag_va,
                "code_va": tag_va + 0xC,
                "dump": os.path.join(repo, "ida", "logs", "vu1", f"{tag_va + 0xC:08x}.bin"),
            })
    rows.sort(key=lambda r: r["index"])
    return rows


# ---------------------------------------------------------------------------
# per-program analysis
# ---------------------------------------------------------------------------

def jr_target_sets(insns: List[vd.Insn]) -> Dict[int, set]:
    """Possible instruction-index targets of `jr viN`, per register N, read
    statically: every `iaddiu viN, vi00, imm` constant that lies inside the
    program (the RW code stores such continuations in VU memory and reloads them
    with `ilw` before the `jr`), plus the return site of every `bal viN`."""
    n = len(insns)
    out: Dict[int, set] = defaultdict(set)
    for k, ins in enumerate(insns):
        low = ins.lower
        if low.base == "IADDIU" and low.fields["is"] == 0 and low.fields["imm15"] < n:
            out[low.fields["it"]].add(low.fields["imm15"])
        elif low.base == "BAL" and k + 2 < n:
            out[low.fields["it"]].add(k + 2)
    return out


def reachable_from(insns: List[vd.Insn], entries: List[int]) -> Tuple[set, int]:
    """Static reachability (instruction indices) from `entries`, honouring the one
    delay slot after a branch and the one instruction after an E bit. `jr viN`
    follows every statically visible constant/`bal` link for viN (over-
    approximation); `jr` with no visible source is counted as unresolved."""
    n = len(insns)
    jr_sets = jr_target_sets(insns)
    seen: set = set()
    unresolved = 0
    work = list(entries)
    while work:
        i = work.pop()
        if i < 0 or i >= n or i in seen:
            continue
        seen.add(i)
        ins = insns[i]
        succ: List[int] = []
        low = ins.lower
        if low.cls == "branch":
            if i + 1 < n:
                seen.add(i + 1)  # delay slot always executes
                if insns[i + 1].E:
                    continue  # E in the delay slot: stop after it
            if low.branch_indirect:
                reg = low.fields["is"]
                targets = jr_sets.get(reg, set())
                if not targets:
                    unresolved += 1
                succ.extend(targets)
                if low.base == "JALR" and i + 2 < n:
                    succ.append(i + 2)
            else:
                t = low.branch_target
                if t is not None:
                    succ.append(t // 8)
                if low.branch_conditional or low.base == "BAL":
                    succ.append(i + 2)
        elif ins.E:
            if i + 1 < n:
                seen.add(i + 1)  # the pair after E executes, then the unit stops
            continue
        else:
            succ.append(i + 1)
        work.extend(succ)
    return seen, unresolved


def analyse_program(row: dict) -> dict:
    with open(row["dump"], "rb") as fh:
        data = fh.read()
    insns = vd.decode_program(data)
    n = len(insns)
    size = len(data)

    upper = Counter(i.upper.mnemonic for i in insns)
    lower = Counter(i.lower.mnemonic for i in insns)
    upper_base = Counter(i.upper.base for i in insns)
    lower_base = Counter(i.lower.base for i in insns)
    upper_form = Counter(i.upper.fields.get("form", "") for i in insns if i.upper.cls in ("fmac", "fmac_acc"))
    dest_masks = Counter(vd.dest_str(i.upper.fields["dest"]) or "-" for i in insns if i.upper.cls != "nop")

    flags = {k: sum(1 for i in insns if getattr(i, k)) for k in "IEMDT"}
    e_pcs = [i.pc // 8 for i in insns if i.E]
    xgkick_pcs = [i.pc // 8 for i in insns if i.lower.base == "XGKICK"]

    branches = [i for i in insns if i.lower.cls == "branch"]
    br_kinds = Counter(i.lower.base for i in branches)
    br_out = []
    br_wrap = []
    br_back = 0
    br_fwd = 0
    loops: List[Tuple[int, int]] = []  # (target_insn, branch_insn) for backward branches
    for i in branches:
        t = i.lower.branch_target
        if t is None:
            continue
        if i.lower.branch_wraps:
            br_wrap.append({"pc": i.pc // 8, "raw_target": i.lower.branch_target_raw // 8, "target": t // 8})
        if t >= size:
            br_out.append({"pc": i.pc // 8, "target": t // 8, "text": i.lower.text})
        elif t < i.pc:
            br_back += 1
            loops.append((t // 8, i.pc // 8))
        else:
            br_fwd += 1
    jr = sum(1 for i in branches if i.lower.branch_indirect)
    # topic 14 counted lower words with opcode 0x20..0x2F without honouring the I bit
    legacy_br = sum(1 for i in insns if 0x20 <= (i.lo >> 25) <= 0x2F)

    xg_in_loop = sum(1 for x in xgkick_pcs if any(t <= x <= b for t, b in loops))
    # E-segments in linear layout: [start, e_pc+1] regions; xgkicks per region
    seg_bounds = []
    start = 0
    for e in e_pcs:
        seg_bounds.append((start, e + 1))
        start = e + 2
    if start < n:
        seg_bounds.append((start, n - 1))
    xg_per_seg = [sum(1 for x in xgkick_pcs if a <= x <= b) for a, b in seg_bounds]

    # entries: MSCAL 0 and the MSCNT resume point after every E pair
    entries = [0] + [e + 2 for e in e_pcs if e + 2 < n]
    reach, unresolved = reachable_from(insns, entries)
    reach_xg = sum(1 for x in xgkick_pcs if x in reach)
    reach_e = sum(1 for e in e_pcs if e in reach)
    # what the post-E resume code jumps to (batch entry), when it is a plain b/jr-constant
    resume_targets = []
    for e in e_pcs:
        for k in range(e + 2, min(e + 6, n)):
            low = insns[k].lower
            if low.base == "B":
                resume_targets.append(low.branch_target // 8)
                break
            if low.base == "JR":
                ts = jr_target_sets(insns).get(low.fields["is"], set())
                resume_targets.extend(sorted(ts))
                break
    first_xitop = next((i.pc // 8 for i in insns if i.lower.base == "XITOP"), None)

    vi_used = set()
    vi_written = set()
    for i in insns:
        vi_used.update(r for r in i.lower.vi_read if r)
        vi_used.update(w for w in i.lower.vi_write if w)
        vi_written.update(w for w in i.lower.vi_write if w)
    vf_used = set()
    for i in insns:
        u = i.upper
        if u.cls in ("fmac", "fmac_acc", "conv", "abs", "clip", "opm"):
            vf_used.update(v for v in (u.fields["ft"], u.fields["fs"]) if v)
            if u.cls in ("fmac", "opm") and u.base != "OPMULA":
                if u.fields["fd"]:
                    vf_used.add(u.fields["fd"])
            if u.cls in ("conv", "abs"):
                vf_used.add(u.fields["ft"])
    unknown = [{"pc": i.pc // 8, "hi": f"0x{i.hi:08x}", "lo": f"0x{i.lo:08x}",
                "half": "upper" if i.upper.mnemonic == "UNKNOWN" else "lower"}
               for i in insns if i.upper.mnemonic == "UNKNOWN" or i.lower.mnemonic == "UNKNOWN"]

    efu_q = {k: v for k, v in lower_base.items() if k in EFU_Q}
    efu_p = {k: v for k, v in lower_base.items() if k in EFU_P}
    flag_ops = {k: v for k, v in lower_base.items() if k in FLAG_OPS_CLIP | FLAG_OPS_STATUS | FLAG_OPS_MAC}
    rand_ops = {k: v for k, v in lower_base.items() if k in RAND_OPS}
    loi_values = Counter(i.lower.text[4:] for i in insns if i.lower.base == "LOI")

    return {
        "index": row["index"], "name": row["name"], "family": row["family"],
        "tag_va": f"0x{row['tag_va']:06x}", "code_va": f"0x{row['code_va']:06x}",
        "bytes": size, "units": n, "trailing_bytes": size % 8,
        "sha256_16": hashlib.sha256(data).hexdigest()[:16],
        "unknown_count": len(unknown), "unknown": unknown,
        "flags": flags, "e_pcs": e_pcs,
        "upper": dict(sorted(upper.items(), key=lambda kv: (-kv[1], kv[0]))),
        "lower": dict(sorted(lower.items(), key=lambda kv: (-kv[1], kv[0]))),
        "upper_forms": dict(upper_form), "dest_masks": dict(dest_masks.most_common()),
        "upper_nop": upper["NOP"], "lower_nop": lower["NOP"], "loi": lower["LOI"],
        "loi_values": dict(loi_values.most_common(8)),
        "xgkick": len(xgkick_pcs), "xgkick_pcs": xgkick_pcs, "xgkick_in_loop": xg_in_loop,
        "xgkick_per_e_segment": xg_per_seg, "e_segments": len(seg_bounds),
        "branches": len(branches), "branch_kinds": dict(br_kinds), "branch_back": br_back,
        "branch_fwd": br_fwd, "branch_out_of_program": br_out, "branch_wraps": br_wrap, "jr_jalr": jr,
        "legacy_branch_count_topic14": legacy_br,
        "loops": len(loops),
        "entries": entries, "resume_targets": resume_targets, "first_xitop": first_xitop,
        "reach": {"insns": len(reach), "coverage": round(len(reach) / n, 4) if n else 0.0,
                  "xgkick": reach_xg, "e_bits": reach_e, "unresolved_jr": unresolved},
        "clip": upper_base["CLIP"], "efu_q": efu_q, "efu_p": efu_p, "flag_ops": flag_ops, "rand_ops": rand_ops,
        "xtop": lower_base["XTOP"], "xitop": lower_base["XITOP"],
        "int_ops": sum(v for k, v in lower_base.items()
                       if k in ("IADD", "ISUB", "IADDI", "IADDIU", "ISUBIU", "IAND", "IOR")),
        "vi_used": sorted(vi_used), "vi_written": sorted(vi_written), "vf_used": sorted(vf_used),
        "ilw_isw": sum(v for k, v in lower_base.items() if k in ("ILW", "ISW", "ILWR", "ISWR")),
        "mfir_mtir": sum(v for k, v in lower_base.items() if k in ("MFIR", "MTIR")),
    }


# ---------------------------------------------------------------------------
# aggregation
# ---------------------------------------------------------------------------

def hist_distance(a: Dict[str, int], b: Dict[str, int]) -> float:
    """L1 distance of the two mnemonic histograms normalised by the larger total."""
    keys = set(a) | set(b)
    tot = max(sum(a.values()), sum(b.values()), 1)
    return sum(abs(a.get(k, 0) - b.get(k, 0)) for k in keys) / tot


def combined_hist(p: dict) -> Dict[str, int]:
    h = {f"U:{k}": v for k, v in p["upper"].items()}
    h.update({f"L:{k}": v for k, v in p["lower"].items()})
    return h


def aggregate(progs: List[dict]) -> dict:
    total_units = sum(p["units"] for p in progs)
    upper = Counter()
    lower = Counter()
    for p in progs:
        upper.update(p["upper"])
        lower.update(p["lower"])
    fam: Dict[str, dict] = {}
    for f in sorted({p["family"] for p in progs}):
        ps = [p for p in progs if p["family"] == f]
        fu = Counter()
        fl = Counter()
        for p in ps:
            fu.update(p["upper"])
            fl.update(p["lower"])
        fam[f] = {
            "programs": len(ps), "units": sum(p["units"] for p in ps),
            "units_min": min(p["units"] for p in ps), "units_max": max(p["units"] for p in ps),
            "distinct_upper": len(fu), "distinct_lower": len(fl),
            "upper": dict(fu.most_common()), "lower": dict(fl.most_common()),
            "xgkick": [min(p["xgkick"] for p in ps), max(p["xgkick"] for p in ps)],
            "e_bits": [min(p["flags"]["E"] for p in ps), max(p["flags"]["E"] for p in ps)],
            "branches": [min(p["branches"] for p in ps), max(p["branches"] for p in ps)],
            "clip": [min(p["clip"] for p in ps), max(p["clip"] for p in ps)],
            "jr_jalr": sum(p["jr_jalr"] for p in ps),
            "unknown": sum(p["unknown_count"] for p in ps),
            "xitop": sum(p["xitop"] for p in ps), "xtop": sum(p["xtop"] for p in ps),
            "efu_q": dict(sum((Counter(p["efu_q"]) for p in ps), Counter())),
            "efu_p": dict(sum((Counter(p["efu_p"]) for p in ps), Counter())),
            "flag_ops": dict(sum((Counter(p["flag_ops"]) for p in ps), Counter())),
            "rand_ops": dict(sum((Counter(p["rand_ops"]) for p in ps), Counter())),
            "vi_used": sorted(set().union(*(set(p["vi_used"]) for p in ps))),
            "branch_out_of_program": sum(len(p["branch_out_of_program"]) for p in ps),
            "branch_wraps": sum(len(p["branch_wraps"]) for p in ps),
            "xgkick_in_loop": sum(p["xgkick_in_loop"] for p in ps),
            "reach_coverage_min": min(p["reach"]["coverage"] for p in ps),
            "unresolved_jr": sum(p["reach"]["unresolved_jr"] for p in ps),
            "max_xgkick_per_e_segment": max(max(p["xgkick_per_e_segment"] or [0]) for p in ps),
        }

    # unreferenced vs referenced similarity
    unref = [p for p in progs if p["family"] == "unreferenced"]
    ref = [p for p in progs if p["family"] != "unreferenced"]
    nearest = []
    for u in unref:
        hu = combined_hist(u)
        best = min(ref, key=lambda r: hist_distance(hu, combined_hist(r)))
        d = hist_distance(hu, combined_hist(best))
        nearest.append({"name": u["name"], "units": u["units"], "nearest": best["name"],
                        "nearest_units": best["units"], "l1_norm": round(d, 3),
                        "distinct_upper": len(u["upper"]), "distinct_lower": len(u["lower"]),
                        "only_in_unreferenced": sorted(set(u["upper"]) - set(best["upper"]))
                        + sorted(f"L:{k}" for k in set(u["lower"]) - set(best["lower"]))})

    # mnemonic -> families and number of programs using it
    mn_fams: Dict[str, set] = defaultdict(set)
    mn_progs: Counter = Counter()
    for p in progs:
        for k in p["upper"]:
            mn_fams[f"U:{k}"].add(p["family"])
            mn_progs[f"U:{k}"] += 1
        for k in p["lower"]:
            mn_fams[f"L:{k}"].add(p["family"])
            mn_progs[f"L:{k}"] += 1
    boot_set = set(BOOT_PATH_FAMILIES)
    boot_upper = Counter()
    boot_lower = Counter()
    for p in progs:
        if p["family"] in boot_set:
            boot_upper.update(p["upper"])
            boot_lower.update(p["lower"])
    full_only = {"upper": sorted(set(upper) - set(boot_upper)), "lower": sorted(set(lower) - set(boot_lower))}

    return {
        "programs": len(progs), "units": total_units, "bytes": sum(p["bytes"] for p in progs),
        "unknown": sum(p["unknown_count"] for p in progs),
        "distinct_upper": len(upper), "distinct_lower": len(lower),
        "upper": dict(upper.most_common()), "lower": dict(lower.most_common()),
        "upper_base": dict(sum((Counter({re.sub(r"(bc|i|q)$", "", k): v}) for k, v in upper.items()),
                               Counter()).most_common()),
        "flags": {k: sum(p["flags"][k] for p in progs) for k in "IEMDT"},
        "xgkick": sum(p["xgkick"] for p in progs), "branches": sum(p["branches"] for p in progs),
        "branch_kinds": dict(sum((Counter(p["branch_kinds"]) for p in progs), Counter()).most_common()),
        "branch_out_of_program": sum(len(p["branch_out_of_program"]) for p in progs),
        "branch_wraps": sum(len(p["branch_wraps"]) for p in progs),
        "programs_with_wrapping_branch": sum(1 for p in progs if p["branch_wraps"]),
        "legacy_branch_count_topic14": sum(p["legacy_branch_count_topic14"] for p in progs),
        "reach_coverage_min": min(p["reach"]["coverage"] for p in progs),
        "programs_full_reach": sum(1 for p in progs if p["reach"]["coverage"] >= 0.999),
        "unresolved_jr": sum(p["reach"]["unresolved_jr"] for p in progs),
        "jr_jalr": sum(p["jr_jalr"] for p in progs), "clip": sum(p["clip"] for p in progs),
        "efu_q": dict(sum((Counter(p["efu_q"]) for p in progs), Counter()).most_common()),
        "efu_p": dict(sum((Counter(p["efu_p"]) for p in progs), Counter()).most_common()),
        "flag_ops": dict(sum((Counter(p["flag_ops"]) for p in progs), Counter()).most_common()),
        "rand_ops": dict(sum((Counter(p["rand_ops"]) for p in progs), Counter()).most_common()),
        "xitop": sum(p["xitop"] for p in progs), "xtop": sum(p["xtop"] for p in progs),
        "programs_with_xitop": sum(1 for p in progs if p["xitop"]),
        "programs_with_loops": sum(1 for p in progs if p["loops"]),
        "programs_with_xgkick_in_loop": sum(1 for p in progs if p["xgkick_in_loop"]),
        "programs_multi_xgkick_per_e_segment": sum(1 for p in progs if max(p["xgkick_per_e_segment"] or [0]) > 1),
        "vi_used": sorted(set().union(*(set(p["vi_used"]) for p in progs))),
        "dest_masks": dict(sum((Counter(p["dest_masks"]) for p in progs), Counter()).most_common()),
        "upper_forms": dict(sum((Counter(p["upper_forms"]) for p in progs), Counter()).most_common()),
        "families": fam,
        "mnemonic_families": {k: sorted(v) for k, v in sorted(mn_fams.items())},
        "mnemonic_program_counts": dict(sorted(mn_progs.items(), key=lambda kv: (kv[1], kv[0]))),
        "boot_path_families": list(BOOT_PATH_FAMILIES),
        "boot_path_subset": {"upper": dict(boot_upper.most_common()), "lower": dict(boot_lower.most_common()),
                             "distinct_upper": len(boot_upper), "distinct_lower": len(boot_lower)},
        "full_game_only": full_only,
        "unreferenced_nearest": nearest,
    }


# ---------------------------------------------------------------------------
# markdown
# ---------------------------------------------------------------------------

def fmt_hist(h: Dict[str, int], limit: Optional[int] = None) -> str:
    items = list(h.items())[:limit] if limit else list(h.items())
    return ", ".join(f"`{k}` {v:,}" for k, v in items) or "-"


def md_block(progs: List[dict], agg: dict, repo_rel_dump: str) -> str:
    now = _dt.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    L: List[str] = []
    L.append("<!-- GENERATED:BEGIN (vu1_census.py) -->")
    L.append(f"_Generated {now} by `tools/ours/vu1/vu1_census.py` with `tools/ours/vu1/vu1_decode.py` over "
             f"`{repo_rel_dump}` (114 gitignored dumps named by code VA = tag VA + 0xC, inventory from "
             "`symbols/p3fes.sym` rows `vu1_prog_*`). Do not edit inside the markers. Counts are observed "
             "(decoder over the dump bytes); E-segments, loops and reachability are static readings._")
    L.append("")
    L.append("### Headline")
    L.append("")
    L.append("| Metric | Value |")
    L.append("|---|---|")
    L.append(f"| Programs decoded | {agg['programs']} |")
    L.append(f"| 64-bit instructions | {agg['units']:,} ({agg['bytes']:,} bytes) |")
    L.append(f"| `UNKNOWN` halves | **{agg['unknown']}** |")
    L.append(f"| Distinct upper mnemonics (form-qualified) | {agg['distinct_upper']} |")
    L.append(f"| Distinct lower mnemonics | {agg['distinct_lower']} |")
    f = agg["flags"]
    L.append(f"| Flag bits I / E / M / D / T | {f['I']:,} / {f['E']:,} / {f['M']:,} / {f['D']:,} / {f['T']:,} |")
    L.append(f"| `xgkick` | {agg['xgkick']:,} (in a backward-branch loop body: "
             f"{sum(p['xgkick_in_loop'] for p in progs):,}; programs with >1 per linear E-segment: "
             f"{agg['programs_multi_xgkick_per_e_segment']}) |")
    L.append(f"| Branches | {agg['branches']:,} ({fmt_hist(agg['branch_kinds'])}); `jr`/`jalr` {agg['jr_jalr']}; "
             f"targets outside the owning program after 16 KiB wrap: **{agg['branch_out_of_program']}**; "
             f"branches whose raw target wraps around micro memory: {agg['branch_wraps']} in "
             f"{agg['programs_with_wrapping_branch']} programs |")
    L.append(f"| Static reachability from entry 0 + post-`E` resume points | min coverage "
             f"{agg['reach_coverage_min']:.0%}; programs fully covered: {agg['programs_full_reach']}; "
             f"`jr` with no visible constant/`bal` source: {agg['unresolved_jr']} |")
    L.append(f"| Topic-14-style branch count (opcode 0x20-0x2F, I bit ignored) | "
             f"{agg['legacy_branch_count_topic14']:,} (over-counts `loi` floats) |")
    L.append(f"| `clipw` | {agg['clip']:,} |")
    L.append(f"| EFU Q-pipe | {fmt_hist(agg['efu_q'])} |")
    L.append(f"| EFU P-pipe | {fmt_hist(agg['efu_p'])} |")
    L.append(f"| Flag-register ops | {fmt_hist(agg['flag_ops'])} |")
    L.append(f"| R ops | {fmt_hist(agg['rand_ops'])} |")
    L.append(f"| `xtop` / `xitop` | {agg['xtop']:,} / {agg['xitop']:,} (programs with `xitop`: "
             f"{agg['programs_with_xitop']}) |")
    L.append(f"| Programs with backward branches | {agg['programs_with_loops']} |")
    L.append(f"| Integer registers touched (any program) | {', '.join(f'vi{v:02d}' for v in agg['vi_used'])} |")
    L.append("")
    L.append("### Upper mnemonics (all programs)")
    L.append("")
    L.append(fmt_hist(agg["upper"]))
    L.append("")
    L.append(f"Forms: {fmt_hist(agg['upper_forms'])} (`bc` broadcast, `i`/`q` register, empty = vector). "
             f"Dest masks: {fmt_hist(agg['dest_masks'], 12)}.")
    L.append("")
    L.append("### Lower mnemonics (all programs)")
    L.append("")
    L.append(fmt_hist(agg["lower"]))
    L.append("")
    L.append("### Per family")
    L.append("")
    L.append("| Family | Progs | Units (min-max) | Upper distinct | Lower distinct | E | XGK | br | clipw | EFU Q | EFU P | flag ops | `xitop` | vi regs | UNK |")
    L.append("|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|")
    for name, fa in agg["families"].items():
        L.append(f"| `{name}` | {fa['programs']} | {fa['units']:,} ({fa['units_min']}-{fa['units_max']}) | "
                 f"{fa['distinct_upper']} | {fa['distinct_lower']} | {fa['e_bits'][0]}-{fa['e_bits'][1]} | "
                 f"{fa['xgkick'][0]}-{fa['xgkick'][1]} | {fa['branches'][0]}-{fa['branches'][1]} | "
                 f"{fa['clip'][0]}-{fa['clip'][1]} | {fmt_hist(fa['efu_q'])} | {fmt_hist(fa['efu_p'])} | "
                 f"{fmt_hist(fa['flag_ops'])} | {fa['xitop']} | {len(fa['vi_used'])} | {fa['unknown']} |")
    L.append("")
    L.append("### Rare mnemonics (used by at most 40 of the 114 programs)")
    L.append("")
    L.append("| Mnemonic | Programs | Total | Families |")
    L.append("|---|---|---|---|")
    for k, cnt in agg["mnemonic_program_counts"].items():
        if cnt > 40:
            continue
        side, name = k.split(":", 1)
        total = (agg["upper"] if side == "U" else agg["lower"]).get(name, 0)
        L.append(f"| `{k}` | {cnt} | {total:,} | {', '.join(f'`{x}`' for x in agg['mnemonic_families'][k])} |")
    L.append("")
    L.append("### Boot-path subset vs full game")
    L.append("")
    bp = agg["boot_path_subset"]
    L.append(f"Families taken as the boot path (inferred, see narrative): {', '.join(f'`{x}`' for x in agg['boot_path_families'])}. "
             f"They use {bp['distinct_upper']} upper and {bp['distinct_lower']} lower mnemonics. "
             f"Mnemonics that appear only outside that subset: upper {', '.join(f'`{x}`' for x in agg['full_game_only']['upper']) or 'none'}; "
             f"lower {', '.join(f'`{x}`' for x in agg['full_game_only']['lower']) or 'none'}.")
    L.append("")
    L.append("### Largest / most complex programs")
    L.append("")
    L.append("| Program | Family | Units | Upper distinct | Lower distinct | br | back-br | `bal`/`jr` | XGK | E | clipw | EFU | static reach |")
    L.append("|---|---|---|---|---|---|---|---|---|---|---|---|---|")
    top = sorted(progs, key=lambda p: (-p["units"], p["index"]))[:12]
    top += [p for p in sorted(progs, key=lambda p: (-p["branches"], p["index"]))[:5] if p not in top]
    for p in top:
        efu = sum(p["efu_q"].values()) + sum(p["efu_p"].values())
        r = p["reach"]
        L.append(f"| `{p['name']}` `{p['tag_va']}` | `{p['family']}` | {p['units']:,} | {len(p['upper'])} | "
                 f"{len(p['lower'])} | {p['branches']} | {p['branch_back']} | "
                 f"{p['branch_kinds'].get('BAL', 0)}/{p['jr_jalr']} | {p['xgkick']} | {p['flags']['E']} | "
                 f"{p['clip']} | {efu} | {r['coverage']:.0%} |")
    L.append("")
    L.append("### Unreferenced programs: nearest referenced program by mnemonic histogram")
    L.append("")
    L.append("Distance = L1 of the combined upper+lower histograms / larger instruction count (0 = identical multiset).")
    L.append("")
    L.append("| Unreferenced | Units | Nearest referenced | Units | Distance | Mnemonics only in the unreferenced one |")
    L.append("|---|---|---|---|---|---|")
    for e in agg["unreferenced_nearest"]:
        L.append(f"| `{e['name']}` | {e['units']} | `{e['nearest']}` | {e['nearest_units']} | {e['l1_norm']:.3f} | "
                 f"{', '.join(f'`{x}`' for x in e['only_in_unreferenced']) or '-'} |")
    L.append("")
    L.append("### Per program")
    L.append("")
    L.append("E pcs / resume: instruction index of each E bit and where the post-E resume code jumps (the batch entry). "
             "XGK/E-seg: `xgkick` count per linear E-segment.")
    L.append("")
    L.append("| # | tag VA | family | units | E pcs -> resume | I(loi) | XGK | XGK/E-seg | br (back) | bal | jr | wrap | out | clipw | EFU Q | EFU P | flag ops | xtop/xitop | vi | reach | UNK |")
    L.append("|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|")
    for p in progs:
        f = p["flags"]
        epcs = ",".join(f"{e:#x}" for e in p["e_pcs"])
        res = ",".join(f"{t:#x}" for t in sorted(set(p["resume_targets"]))) or "-"
        L.append(f"| {p['index']} | `{p['tag_va']}` | `{p['family']}` | {p['units']} | {epcs} -> {res} | {f['I']} | "
                 f"{p['xgkick']} | {'/'.join(str(x) for x in p['xgkick_per_e_segment'])} | "
                 f"{p['branches']} ({p['branch_back']}) | {p['branch_kinds'].get('BAL', 0)} | {p['jr_jalr']} | "
                 f"{len(p['branch_wraps'])} | {len(p['branch_out_of_program'])} | {p['clip']} | "
                 f"{sum(p['efu_q'].values())} | {sum(p['efu_p'].values())} | {sum(p['flag_ops'].values())} | "
                 f"{p['xtop']}/{p['xitop']} | {len(p['vi_used'])} | {p['reach']['coverage']:.0%} | {p['unknown_count']} |")
    L.append("")
    unk = [(p, u) for p in progs for u in p["unknown"]]
    if unk:
        L.append("### UNKNOWN encodings")
        L.append("")
        L.append("| Program | pc | upper | lower | half |")
        L.append("|---|---|---|---|---|")
        for p, u in unk[:200]:
            L.append(f"| `{p['name']}` | {u['pc']:#x} | `{u['hi']}` | `{u['lo']}` | {u['half']} |")
        L.append("")
    L.append("<!-- GENERATED:END -->")
    return "\n".join(L) + "\n"


def write_doc(path: str, block: str) -> None:
    begin = "<!-- GENERATED:BEGIN (vu1_census.py) -->"
    end = "<!-- GENERATED:END -->"
    if os.path.exists(path):
        with open(path, encoding="utf-8") as fh:
            text = fh.read()
        b = text.find(begin)
        e = text.find(end)
        if b >= 0 and e >= 0:
            text = text[:b] + block + text[e + len(end):].lstrip("\n")
        else:
            text = text.rstrip("\n") + "\n\n" + block
    else:
        text = "# 09 - VU1 micro-instruction census\n\n_Narrative to be written._\n\n" + block
    with open(path, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(text)


# ---------------------------------------------------------------------------

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", default=os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "..")))
    ap.add_argument("--no-doc", action="store_true")
    args = ap.parse_args()
    repo = args.repo

    rows = load_inventory(repo)
    if len(rows) != 114:
        print(f"warning: expected 114 vu1_prog_* rows, found {len(rows)}", file=sys.stderr)
    missing = [r["dump"] for r in rows if not os.path.exists(r["dump"])]
    if missing:
        print(f"error: {len(missing)} dumps missing, e.g. {missing[0]}", file=sys.stderr)
        return 1

    progs = [analyse_program(r) for r in rows]
    agg = aggregate(progs)

    out = {
        "generated": _dt.datetime.now().isoformat(timespec="seconds"),
        "tool": "tools/ours/vu1/vu1_census.py + vu1_decode.py",
        "source": "ida/logs/vu1/<code_va>.bin (gitignored) ; inventory symbols/p3fes.sym vu1_prog_*",
        "notes": [
            "counts are observed from the dump bytes; branch targets, loops, E-segments and reachability are static",
            "branch targets are wrapped into the 16 KiB VU1 micro memory (vu1_decode.VU1_MICRO_BYTES); branch_wraps lists raw targets",
            "entries = instruction 0 (MSCAL 0) plus the pair after every E (MSCNT resume); reach follows jr via visible iaddiu constants and bal links",
            "upper mnemonics are form-qualified: ADD (vector), ADDbc (broadcast), ADDi, ADDq",
            "boot_path_families is an inference (see docs/ANALYSIS/09_vu1_micro_census.md)",
        ],
        "aggregate": agg,
        "programs": progs,
    }
    json_path = os.path.join(repo, "symbols", "vu1_micro_census.json")
    with open(json_path, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(out, fh, indent=1)
        fh.write("\n")

    if not args.no_doc:
        write_doc(os.path.join(repo, "docs", "ANALYSIS", "09_vu1_micro_census.md"),
                  md_block(progs, agg, "ida/logs/vu1/<code_va>.bin"))

    print(f"programs {agg['programs']} units {agg['units']:,} unknown {agg['unknown']} "
          f"upper {agg['distinct_upper']} lower {agg['distinct_lower']} xgkick {agg['xgkick']} "
          f"branches {agg['branches']} out-of-program {agg['branch_out_of_program']} jr {agg['jr_jalr']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
