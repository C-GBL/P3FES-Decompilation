#!/usr/bin/env python3
"""Boundary diff: IDA function set (symbols/functions.json) vs Ghidra export (ExportFunctions.java).

    python tools/ours/ghidra/diff_functions.py symbols/functions.json ghidra/functions_ghidra.json \
        [--out ghidra/logs/diff_report.md] [--json ghidra/logs/diff.json] [--top 40]

stdlib only. Prints a short summary; the full Markdown report (tables ready to paste into
docs/ANALYSIS/06_ghidra_crosscheck.md) goes to --out. Neither input is modified.

Address bands come from docs/ANALYSIS/03_strings_of_interest.md (leaked source-file names and
their referencing functions). Band *edges* are inferred there, not observed; they only serve to
show WHERE the two tools disagree.
"""
import argparse
import bisect
import json
import os
import sys
from collections import Counter, defaultdict

# (start, end_exclusive, label) -- from 03_strings_of_interest.md "module map" + 00_elf_layout.md.
BANDS = [
    (0x100000, 0x103DA0, "crt0/start + early SDK stubs"),
    (0x103DA0, 0x1939D0, "h_* / _h_camp_* (camp menu, fade, Sofdec, sound, malloc)"),
    (0x1939D0, 0x199440, "kwln* (task kernel, main loop)"),
    (0x199440, 0x1E7F90, "k_* (field/dungeon engine)"),
    (0x1E7F90, 0x28DBF0, "eff_*/br_*/bp_*/sfl_*/gc_*/op_*/gm_* (battle UI, shuffle, title)"),
    (0x28DBF0, 0x30FC40, "btl*/dat* (battle core, data tables)"),
    (0x30FC40, 0x35AEF0, "unattributed (between btl* and scr*)"),
    (0x35AEF0, 0x361350, "scr* (BF script VM)"),
    (0x361350, 0x3A2150, "mt_evt*/mt_scene* (event system, PM1/PM2)"),
    (0x3A2150, 0x3BDBD0, "itf*/fr*/fm*/resrc* (UI panels, BMD font)"),
    (0x3BDBD0, 0x4176F0, "comu*/nm*/fcl* (social links, fusion, shops)"),
    (0x4176F0, 0x46C000, "unattributed game code (incl. Y_StParts_UpdateStratumPartsTask admini/ed_*)"),
    (0x46C000, 0x4E7000, "G3_2D*_Node renderer (MMI-heavy band)"),
    (0x4E7000, 0x4F9000, "unattributed (renderer tail / pre-SDK)"),
    (0x4F9000, 0x51D460, "SCE SDK libs (libgraph..libdbc)"),
    (0x51D460, 0x5A2000, "MW runtime/libc + CRI middleware (inferred)"),
    (0x5A2000, 0x7CDE80, "DATA band (rodata/data; IDA: 19,008 orphan code items)"),
    (0x7CDE80, 0x9ACC80, ".bss (zero-filled by crt0)"),
]
DATA_BAND_START = 0x5A2000
_BAND_STARTS = [b[0] for b in BANDS]


def band_of(addr):
    i = bisect.bisect_right(_BAND_STARTS, addr) - 1
    if i < 0 or addr >= BANDS[i][1]:
        return "outside image"
    return BANDS[i][2]


def load_ida(path):
    with open(path, encoding="utf-8") as f:
        arr = json.load(f)
    out = {}
    for e in arr:
        a = int(e["a"], 16)
        out[a] = {"a": a, "s": int(e["s"]), "n": e["n"]}
    return out


def load_ghidra(path):
    with open(path, encoding="utf-8") as f:
        doc = json.load(f)
    out = {}
    for e in doc["functions"]:
        a = int(e["a"], 16)
        out[a] = {"a": a, "s": int(e["s"]), "n": e["n"], "ranges": int(e.get("ranges", 1)),
                  "thunk": bool(e.get("thunk")), "end": int(e["end"], 16) if e.get("end") else a,
                  "cc": e.get("cc"), "sig": e.get("sig")}
    return doc, out


class Containment:
    """Which function (if any) of a set contains an address? Uses contiguous [a, a+s) spans.
    IDA multi-chunk functions are approximated by their primary span (functions.json only carries
    the chunk-sum size), so 'inside' for IDA is a lower bound for chunked functions."""

    def __init__(self, funcs, use_end=False):
        self.starts = sorted(funcs)
        self.funcs = funcs
        self.use_end = use_end

    def containing(self, addr):
        i = bisect.bisect_right(self.starts, addr) - 1
        if i < 0:
            return None
        f = self.funcs[self.starts[i]]
        end = f["end"] + 1 if self.use_end else f["a"] + f["s"]
        return f if f["a"] <= addr < end else None


def h(a):
    return f"0x{a:06x}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ida_json")
    ap.add_argument("ghidra_json")
    ap.add_argument("--out", default=None)
    ap.add_argument("--json", default=None)
    ap.add_argument("--top", type=int, default=40)
    A = ap.parse_args()

    ida = load_ida(A.ida_json)
    gdoc, gh = load_ghidra(A.ghidra_json)
    ida_set, gh_set = set(ida), set(gh)
    common = ida_set & gh_set
    ida_only = sorted(ida_set - gh_set)
    gh_only = sorted(gh_set - ida_set)

    same_size = [a for a in common if ida[a]["s"] == gh[a]["s"]]
    diff_size = [a for a in common if ida[a]["s"] != gh[a]["s"]]
    deltas = sorted(diff_size, key=lambda a: -abs(ida[a]["s"] - gh[a]["s"]))
    gh_bigger = sum(1 for a in diff_size if gh[a]["s"] > ida[a]["s"])
    ida_bigger = len(diff_size) - gh_bigger
    small_delta = sum(1 for a in diff_size if abs(ida[a]["s"] - gh[a]["s"]) <= 16)

    cont_ida = Containment(ida)
    cont_gh = Containment(gh, use_end=True)

    # IDA-only: does Ghidra have the address inside some function body (merge/tail) or not at all?
    ida_only_inside = [a for a in ida_only if cont_gh.containing(a) is not None]
    ida_only_gap = [a for a in ida_only if cont_gh.containing(a) is None]
    gh_only_inside = [a for a in gh_only if cont_ida.containing(a) is not None]
    gh_only_gap = [a for a in gh_only if cont_ida.containing(a) is None]

    def bucket(addrs):
        c = Counter(band_of(a) for a in addrs)
        return c

    b_ida_only, b_gh_only = bucket(ida_only), bucket(gh_only)
    b_ida_only_gap, b_gh_only_gap = bucket(ida_only_gap), bucket(gh_only_gap)

    gh_data = sorted(a for a in gh if a >= DATA_BAND_START)
    ida_data = sorted(a for a in ida if a >= DATA_BAND_START)
    gh_data_bytes = sum(gh[a]["s"] for a in gh_data)
    gh_multi = [a for a in gh if gh[a]["ranges"] > 1]
    gh_thunks = [a for a in gh if gh[a]["thunk"]]
    ida_total = sum(f["s"] for f in ida.values())
    gh_total = sum(f["s"] for f in gh.values())

    # Nullsub-sized disagreements: IDA 8-byte stubs.
    ida_only_nullsub = sum(1 for a in ida_only if ida[a]["n"].startswith("nullsub_"))
    ida_only_tiny = sum(1 for a in ida_only if ida[a]["s"] <= 16)

    summary = {
        "ida_functions": len(ida), "ghidra_functions": len(gh),
        "common_entries": len(common), "agree_entry_and_size": len(same_size),
        "same_entry_diff_size": len(diff_size), "diff_size_ghidra_bigger": gh_bigger,
        "diff_size_ida_bigger": ida_bigger, "diff_size_within_16_bytes": small_delta,
        "ida_only": len(ida_only), "ida_only_inside_ghidra_function": len(ida_only_inside),
        "ida_only_in_ghidra_gap": len(ida_only_gap), "ida_only_nullsub": ida_only_nullsub,
        "ida_only_size_le_16": ida_only_tiny,
        "ghidra_only": len(gh_only), "ghidra_only_inside_ida_function": len(gh_only_inside),
        "ghidra_only_in_ida_gap": len(gh_only_gap),
        "ghidra_in_data_band": len(gh_data), "ghidra_in_data_band_bytes": gh_data_bytes,
        "ida_in_data_band": len(ida_data),
        "ghidra_multi_range": len(gh_multi), "ghidra_thunks": len(gh_thunks),
        "ida_total_function_bytes": ida_total, "ghidra_total_function_bytes": gh_total,
        "ghidra_stats": gdoc.get("stats"),
    }

    L = []
    w = L.append
    w("### Boundary agreement (IDA `symbols/functions.json` vs Ghidra `ghidra/functions_ghidra.json`)\n")
    w("| Metric | Count |")
    w("|---|---|")
    w(f"| IDA functions | {len(ida)} |")
    w(f"| Ghidra functions | {len(gh)} |")
    w(f"| Entries in both | {len(common)} ({100*len(common)/len(ida):.1f} % of IDA, {100*len(common)/len(gh):.1f} % of Ghidra) |")
    w(f"| ... agree on entry **and** size | {len(same_size)} ({100*len(same_size)/len(common):.1f} % of common) |")
    w(f"| ... same entry, different size | {len(diff_size)} (Ghidra larger: {gh_bigger}; IDA larger: {ida_bigger}; delta <= 16 B: {small_delta}) |")
    w(f"| IDA-only entries | {len(ida_only)} (inside a Ghidra function body: {len(ida_only_inside)}; in Ghidra-undefined space: {len(ida_only_gap)}; `nullsub_*`: {ida_only_nullsub}; size <= 16 B: {ida_only_tiny}) |")
    w(f"| Ghidra-only entries | {len(gh_only)} (inside an IDA function body: {len(gh_only_inside)}; in IDA-undefined space: {len(gh_only_gap)}) |")
    w(f"| Ghidra functions at/after `0x{DATA_BAND_START:x}` (data band) | {len(gh_data)} ({gh_data_bytes} bytes); IDA: {len(ida_data)} |")
    w(f"| Ghidra multi-range functions / thunks | {len(gh_multi)} / {len(gh_thunks)} (IDA multi-chunk: 172, from 01) |")
    w(f"| Total function bytes IDA / Ghidra | {ida_total} / {gh_total} |")
    st = gdoc.get("stats") or {}
    w(f"| Ghidra listing: instructions / defined data / undefined bytes in `{st.get('main_block')}` | {st.get('instructions')} / {st.get('defined_data')} / {st.get('undefined_bytes_in_main')} |")
    w("")
    w("### One-sided entries by address band (bands inferred from `03`)\n")
    w("| Band | IDA-only | ... of which Ghidra has no code there | Ghidra-only | ... of which IDA has no function there |")
    w("|---|---|---|---|---|")
    for s, e, label in BANDS:
        io, ig, go, gg = b_ida_only[label], b_ida_only_gap[label], b_gh_only[label], b_gh_only_gap[label]
        if io or go:
            w(f"| `{h(s)}..{h(e)}` {label} | {io} | {ig} | {go} | {gg} |")
    if b_ida_only["outside image"] or b_gh_only["outside image"]:
        w(f"| outside image | {b_ida_only['outside image']} | {b_ida_only_gap['outside image']} | {b_gh_only['outside image']} | {b_gh_only_gap['outside image']} |")
    w("")
    w(f"### {A.top} largest size deltas (same entry)\n")
    w("| Entry | IDA name | IDA size | Ghidra size | Delta (Ghidra-IDA) | Ghidra ranges | Band |")
    w("|---|---|---|---|---|---|---|")
    top = []
    for a in deltas[:A.top]:
        d = gh[a]["s"] - ida[a]["s"]
        w(f"| `{h(a)}` | `{ida[a]['n']}` | {ida[a]['s']} | {gh[a]['s']} | {d:+d} | {gh[a]['ranges']} | {band_of(a)} |")
        top.append({"a": h(a), "n": ida[a]["n"], "ida": ida[a]["s"], "ghidra": gh[a]["s"], "delta": d,
                    "ghidra_ranges": gh[a]["ranges"], "band": band_of(a)})
    w("")
    w("### Ghidra functions in the data band (first 25)\n")
    w("| Entry | Ghidra name | Size | IDA has function here? |")
    w("|---|---|---|---|")
    for a in gh_data[:25]:
        c = cont_ida.containing(a)
        w(f"| `{h(a)}` | `{gh[a]['n']}` | {gh[a]['s']} | {('yes: ' + c['n']) if c else 'no'} |")
    w("")
    # Largest IDA-only and Ghidra-only functions (what is actually missing).
    w("### Largest IDA-only functions (Ghidra has no entry)\n")
    w("| Entry | IDA name | IDA size | Ghidra containing function |")
    w("|---|---|---|---|")
    for a in sorted(ida_only, key=lambda x: -ida[x]["s"])[:15]:
        c = cont_gh.containing(a)
        w(f"| `{h(a)}` | `{ida[a]['n']}` | {ida[a]['s']} | {(c['n'] + ' @ ' + h(c['a'])) if c else '(undefined)'} |")
    w("")
    w("### Largest Ghidra-only functions (IDA has no entry)\n")
    w("| Entry | Ghidra name | Ghidra size | IDA containing function |")
    w("|---|---|---|---|")
    for a in sorted(gh_only, key=lambda x: -gh[x]["s"])[:15]:
        c = cont_ida.containing(a)
        w(f"| `{h(a)}` | `{gh[a]['n']}` | {gh[a]['s']} | {(c['n'] + ' @ ' + h(c['a'])) if c else '(undefined)'} |")
    w("")
    report = "\n".join(L)

    if A.out:
        os.makedirs(os.path.dirname(os.path.abspath(A.out)), exist_ok=True)
        with open(A.out, "w", encoding="utf-8") as f:
            f.write(report)
    if A.json:
        with open(A.json, "w", encoding="utf-8") as f:
            json.dump({"summary": summary, "top_deltas": top,
                       "ida_only": [h(a) for a in ida_only], "ghidra_only": [h(a) for a in gh_only],
                       "ghidra_in_data_band": [h(a) for a in gh_data]}, f, indent=1)
    for k, v in summary.items():
        if k != "ghidra_stats":
            print(f"{k}: {v}")
    if A.out:
        print(f"report: {A.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
