"""Export IDA's recovered switch jump tables and the unresolved indirect jumps (Phase 3 recompiler input).

Usage (idalib venv python; `import idapro` must be first):
  python export_jumptables.py <ida/work_phase3prep.i64> <repo root> [--log PATH]

Opens the database WITHOUT auto-analysis and closes it WITHOUT saving; refuses the master `ida/p3fes.i64`.

For every `jr $rN` (N != ra) inside an IDA function:
  * with `switch_info_t` (ida_nalt.get_switch_info): table VA, element size, case count, lowcase,
    default, shift, flags, targets from `calc_switch_cases` AND a raw read of the table (both recorded;
    mismatches flagged), sanity: every target must lie inside the same function (any chunk) or be a
    function start -> `violations`.
  * without switch info: the defining instruction of the jump register found by walking backwards in
    the chunk, the idiom we infer from it, the preceding disassembly (VAs, <= 10 lines), whether the
    site is a tail position (nothing but the delay slot follows in the chunk).
Also every `jalr` site (register, function) so the dispatch table can be sized.
Writes symbols/jumptables.json and ida/logs/phase3prep_jumptables.log.
"""
import sys, os, json, time, argparse, collections, re

ap = argparse.ArgumentParser()
ap.add_argument("i64"); ap.add_argument("root"); ap.add_argument("--log", default=None)
A = ap.parse_args()
ROOT = os.path.abspath(A.root); LG = os.path.join(ROOT, "ida", "logs"); os.makedirs(LG, exist_ok=True)
logf = open(A.log or os.path.join(LG, "phase3prep_jumptables.log"), "a", encoding="utf-8"); T0 = time.time()
def log(m):
    s = f"[{time.strftime('%H:%M:%S')} +{time.time()-T0:6.1f}s] {m}"; print(s, flush=True); logf.write(s + "\n"); logf.flush()

import idapro  # noqa
idapro.enable_console_messages(False)
i64 = os.path.abspath(A.i64)
if os.path.basename(i64).lower() == "p3fes.i64": log("REFUSING to open the master database"); sys.exit(2)
log(f"opening {i64} (no auto-analysis, will not save)")
rc = idapro.open_database(i64, False); log(f"open_database rc={rc}")
if rc != 0: sys.exit(rc)
import idautils, ida_funcs, ida_bytes, ida_ua, ida_nalt, ida_xref, idc, ida_idaapi
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_symbols import load_manual_addresses, withheld_name_map, export_disasm
BADADDR = ida_idaapi.BADADDR
# ADR-0009: names and disassembly text in jumptables.json use the exported forms (unverified hints -> sub_/loc_/data_<EA>)
WITHHELD = withheld_name_map(load_manual_addresses(os.path.join(os.path.dirname(os.path.abspath(__file__)), "names_manual.txt")))

def disasm(ea): return export_disasm(ea, WITHHELD)
def reg_of(op): return op.strip().lstrip("$")
def func_name(ea):
    n = ida_funcs.get_func_name(ea) or ""
    return WITHHELD.get(n, n)
def flag_names(si):
    names = []
    for n in dir(ida_nalt):
        if n.startswith("SWI_") and not n.startswith("SWI_SHIFT") and isinstance(getattr(ida_nalt, n), int):
            v = getattr(ida_nalt, n)
            if v and (si.flags & v) == v and bin(v).count("1") == 1: names.append(n)
    return sorted(names)

def switch_targets(ea, si):
    """targets via IDA's own computation, plus a raw read of the table for cross-checking."""
    calc = getattr(ida_nalt, "calc_switch_cases", None) or getattr(ida_xref, "calc_switch_cases", None)
    ida_targets = []; cases = []
    if calc:
        ct = calc(ea, si)
        if ct:
            for i in range(len(ct.targets)):
                ida_targets.append(ct.targets[i])
                cases.append([int(v) for v in ct.cases[i]] if i < len(ct.cases) else [])
    n = si.get_jtable_size(); esz = si.get_jtable_element_size(); raw = []
    rd = {1: ida_bytes.get_byte, 2: ida_bytes.get_word, 4: ida_bytes.get_dword, 8: ida_bytes.get_qword}.get(esz)
    if rd and si.jumps != BADADDR:
        for i in range(n):
            v = rd(si.jumps + i * esz)
            if si.is_indirect(): raw.append(v)  # index into values table; resolved by IDA only
            else:
                t = v
                if esz < 4 and (si.flags & ida_nalt.SWI_SIGNED): t = v - (1 << (8 * esz)) if v >= 1 << (8 * esz - 1) else v
                if si.flags & ida_nalt.SWI_ELBASE or esz < 4: t = (si.elbase + ((t << si.get_shift()) if si.get_shift() else t)) & 0xFFFFFFFF
                raw.append(t)
    return ida_targets, cases, raw

WRITES_FIRST = set("lw lwu ld lq lb lbu lh lhu lui li la addu addiu daddu daddiu add addi dadd daddi or ori and andi xor xori nor "
                   "sll srl sra sllv srlv srav dsll dsrl dsra dsll32 dsrl32 dsra32 dsllv dsrlv dsrav move dli mfhi mflo mfhi1 mflo1 "
                   "subu sub dsubu dsub slt sltu slti sltiu movz movn uld ulw negu not mfc0 mfc1 cfc1 cfc2 qmfc2 pcpyld pextlw plzcw".split())
def defining_insn(jr_ea, reg, chunk_start, maxback=24):
    """Walk back within the chunk for the last instruction that writes `reg`. Returns (ea, text, mnem) or None."""
    ea = jr_ea; ctx = []
    for _ in range(maxback):
        ea = idc.prev_head(ea, chunk_start)
        if ea == BADADDR or ea < chunk_start: break
        text = disasm(ea); ctx.append((ea, text))
        mn = (idc.print_insn_mnem(ea) or "").lower()
        if mn in WRITES_FIRST and reg_of(idc.print_operand(ea, 0)) == reg: return ea, text, mn, ctx
        if mn in ("jalr", "jal", "bal", "bgezal", "bltzal") and reg in ("v0", "v1"): return ea, text, mn, ctx  # call result
    return None, None, None, ctx

def idiom_for(defn_mn, ctx_mnems, defn_text):
    if defn_mn is None: return "unknown: no write to the jump register within 24 instructions of this chunk"
    if defn_mn in ("lw", "ld") and "sll" in ctx_mnems and ("addu" in ctx_mnems or "daddu" in ctx_mnems): return "table load: sll/addu/lw/jr (MW switch idiom; IDA attached no switch_info)"
    if defn_mn in ("lw", "ld", "lq") and ("gp" in defn_text or "sp" in defn_text): return f"pointer load from $gp/$sp frame ({defn_mn})"
    if defn_mn in ("lw", "ld", "uld"): return f"pointer load from memory ({defn_mn}; function pointer / vtable-like)"
    if defn_mn in ("addu", "daddu", "add", "dadd"): return "computed address (addu of base + scaled index; relative jump into code stride)"
    if defn_mn in ("jalr", "jal", "bal", "bgezal", "bltzal"): return "call result used as jump target (jr $v0 after a call: tail-call through returned pointer)"
    if defn_mn in ("move",): return "register copy (move); provenance outside window"
    if defn_mn in ("lui", "li", "la", "addiu", "ori", "dli"): return "immediate/absolute address (constant target; resolvable statically)"
    return f"defined by {defn_mn}"

resolved = []; unresolved = []; jalr_sites = []; violations_total = 0; raw_mismatch = 0
nfunc = 0
for f_ea in idautils.Functions():
    nfunc += 1
    fn = func_name(f_ea); chunks = [(s, e) for s, e in idautils.Chunks(f_ea)]
    def in_func(t): return any(s <= t < e for s, e in chunks)
    for s, e in chunks:
        for ea in idautils.Heads(s, e):
            if not ida_bytes.is_code(ida_bytes.get_flags(ea)): continue
            mn = (idc.print_insn_mnem(ea) or "").lower()
            if mn == "jalr":
                op0, op1 = idc.print_operand(ea, 0), idc.print_operand(ea, 1)
                jalr_sites.append({"ea": f"{ea:#x}", "func": fn, "reg": "$" + reg_of(op1 or op0)}); continue
            if mn != "jr": continue
            reg = reg_of(idc.print_operand(ea, 0))
            if reg == "ra": continue
            si = ida_nalt.get_switch_info(ea)
            if si:
                ida_t, cases, raw_t = switch_targets(ea, si)
                targets = ida_t or raw_t
                bad = [f"{t:#x}" for t in targets if not (in_func(t) or (ida_funcs.get_func(t) and ida_funcs.get_func(t).start_ea == t))]
                outside_any_func = [f"{t:#x}" for t in targets if ida_funcs.get_func(t) is None]
                # calc_switch_cases groups cases per distinct target, so compare target SETS (raw table has one entry per case)
                mism = bool(ida_t and raw_t and not si.is_indirect() and set(ida_t) != set(raw_t))
                if mism: raw_mismatch += 1
                violations_total += len(bad)
                resolved.append({
                    "jr_ea": f"{ea:#x}", "func": fn, "func_ea": f"{f_ea:#x}", "reg": "$" + reg,
                    "table_ea": f"{si.jumps:#x}", "elem_size": si.get_jtable_element_size(), "ncases": si.get_jtable_size(),
                    "lowcase": int(si.lowcase) if not si.is_indirect() else None, "default_ea": f"{si.defjump:#x}" if si.defjump != BADADDR else None,
                    "shift": si.get_shift(), "elbase": f"{si.elbase:#x}" if si.elbase not in (0, BADADDR) else None,
                    "startea": f"{si.startea:#x}" if si.startea != BADADDR else None,
                    "kind": {"indirect": bool(si.is_indirect()), "subtract": bool(si.is_subtract()), "flags": flag_names(si),
                             "values_table": f"{si.values:#x}" if si.is_indirect() and si.values != BADADDR else None,
                             "values_elem_size": si.get_vtable_element_size() if si.is_indirect() else None},
                    "targets": [f"{t:#x}" for t in targets], "cases": cases if cases else None,
                    "distinct_targets": len(set(targets)),
                    "raw_table_targets_match_ida": (not mism) if (ida_t and raw_t and not si.is_indirect()) else None,
                    "violations": bad, "targets_outside_any_function": outside_any_func,
                    "default_in_func": (si.defjump == BADADDR) or in_func(si.defjump),
                })
            else:
                d_ea, d_text, d_mn, ctx = defining_insn(ea, reg, s)
                ctx_mn = [(idc.print_insn_mnem(c_ea) or "").lower() for c_ea, _ in ctx]
                nxt = idc.next_head(ea, e); tail = (nxt == BADADDR) or (idc.next_head(nxt, e) == BADADDR) or (idc.next_head(nxt, e) >= e)
                unresolved.append({
                    "jr_ea": f"{ea:#x}", "func": fn, "func_ea": f"{f_ea:#x}", "reg": "$" + reg, "chunk": f"{s:#x}..{e:#x}",
                    "tail_position": bool(tail), "delay_slot": disasm(ea + 4) if ea + 4 < e else None,
                    "defining_insn": {"ea": f"{d_ea:#x}", "text": d_text} if d_ea else None,
                    "idiom": idiom_for(d_mn, ctx_mn, d_text or ""),
                    "context_before": [{"ea": f"{c_ea:#x}", "text": t} for c_ea, t in reversed(ctx[:10])],
                    "code_xrefs_from_jr": [f"{x:#x}" for x in idautils.CodeRefsFrom(ea, 0)],
                })
    if nfunc % 4000 == 0: log(f"  {nfunc} functions; resolved={len(resolved)} unresolved={len(unresolved)} jalr={len(jalr_sites)}")
log(f"scan done: {nfunc} functions; resolved switches={len(resolved)} (target violations={violations_total}, raw/IDA target mismatches={raw_mismatch}); "
    f"unresolved jr={len(unresolved)}; jalr sites={len(jalr_sites)}")
idapro.close_database(False); log("database closed without saving")

esz = collections.Counter(r["elem_size"] for r in resolved)
summary = {
    "functions_scanned": nfunc, "resolved_switch_sites": len(resolved), "resolved_in_functions": len({r["func_ea"] for r in resolved}),
    "total_cases": sum(r["ncases"] for r in resolved), "total_targets": sum(len(r["targets"]) for r in resolved),
    "elem_size_histogram": dict(esz), "indirect_switches": sum(1 for r in resolved if r["kind"]["indirect"]),
    "with_default": sum(1 for r in resolved if r["default_ea"]), "shift_histogram": dict(collections.Counter(r["shift"] for r in resolved)),
    "largest_tables": [{"jr_ea": r["jr_ea"], "func": r["func"], "ncases": r["ncases"]} for r in sorted(resolved, key=lambda r: -r["ncases"])[:10]],
    "sites_with_violations": sum(1 for r in resolved if r["violations"]), "target_violations": violations_total,
    "raw_table_vs_ida_mismatches": raw_mismatch, "sites_with_targets_outside_any_function": sum(1 for r in resolved if r["targets_outside_any_function"]),
    "unresolved_jr_sites": len(unresolved), "unresolved_idioms": dict(collections.Counter(u["idiom"] for u in unresolved)),
    "unresolved_tail_position": sum(1 for u in unresolved if u["tail_position"]),
    "jalr_sites": len(jalr_sites), "jalr_functions": len({j["func"] for j in jalr_sites}),
    "jalr_by_register": dict(collections.Counter(j["reg"] for j in jalr_sites).most_common()),
}
out = {"generated": time.strftime("%Y-%m-%d %H:%M:%S"), "tool": "tools/ours/ida/export_jumptables.py",
       "database": os.path.relpath(i64, ROOT).replace("\\", "/") + " (copy of ida/p3fes.i64)",
       "semantics": {"resolved": "IDA switch_info_t at the jr site (observed); targets from calc_switch_cases, cross-read from the table bytes",
                     "unresolved": "jr $rN without switch_info; defining instruction and idiom are our inference from the preceding disassembly",
                     "sanity": "a target violates when it is neither inside the jr's function (any chunk) nor a function start"},
       "summary": summary, "resolved": resolved, "unresolved": unresolved, "jalr_sites": jalr_sites}
p = os.path.join(ROOT, "symbols", "jumptables.json")
json.dump(out, open(p, "w", encoding="utf-8"), indent=1)
log(f"-> {p}: {json.dumps({k: v for k, v in summary.items() if k not in ('largest_tables', 'unresolved_idioms', 'jalr_by_register')})}")
log(f"unresolved idioms: {summary['unresolved_idioms']}")
