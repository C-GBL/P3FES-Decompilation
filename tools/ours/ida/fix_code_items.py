"""fix_code_items.py -- turn reviewed data words inside function chunks into instructions.

Reads tools/ours/ida/code_manual.txt (`<hex addr> owner=<hex func start> words=<n> [extend=yes] <reason>`,
`#` comments). For every word of [addr, addr + 4*n): refuse unless the word lies inside the owner function
(any chunk); skip it if it is already a 4-byte instruction head (idempotent); otherwise delete the item covering
it (ida_bytes.del_items), decode one instruction (ida_ua.create_insn) and, if the word is not in one of the
owner's chunks, append it as a tail (ida_funcs.append_func_tail). Then the owner is reanalysed and
auto-analysis drained, and every word is checked again (IDA re-marking data is reported as `reverted`).
The offset xrefs that made IDA create the data items are reported, never changed.

`extend=yes` (reviewed chunk extensions: a chunk IDA ended before words the code runs through): a word may
also lie outside the owner when it starts exactly at the end of one of the owner's chunks (after the entry's
previous words joined it), so the range grows that chunk word by word (IDA merges an appended tail with the
adjacent chunk; words that are already instructions are joined too). A function that starts inside the range
is absorbed -- deleted (ida_funcs.del_func) and its IDA dummy name cleared -- only if it lies entirely inside
the range and nothing outside the range refers to its start; anything else is refused.

Usage (idalib venv python, from the repo root; exit 1 on any failure, nothing saved then):
  python tools/ours/ida/fix_code_items.py ida/p3fes.i64 tools/ours/ida/code_manual.txt [--dry-run]
Then re-export (tools/ours/ida/README.md): copy the master to ida/work_master_snapshot.i64 and run
export_function_chunks.py, insn_census.py, export_jumptables.py and export_symbols.py on that copy.
"""
import idapro  # must be first

import argparse
import re
import sys

ap = argparse.ArgumentParser()
ap.add_argument("db")
ap.add_argument("list_file")
ap.add_argument("--dry-run", action="store_true")
A = ap.parse_args()

LINE_RE = re.compile(r"^(0x[0-9A-Fa-f]+)\s+owner=(0x[0-9A-Fa-f]+)\s+words=(\d+)\s*(extend=yes\s*)?(.*)$")
wanted = []
for ln in open(A.list_file, encoding="utf-8"):
    s = ln.strip()
    if not s or s.startswith("#"):
        continue
    m = LINE_RE.match(s)
    if not m:
        sys.exit(f"bad line: {s}")
    wanted.append((int(m.group(1), 16), int(m.group(2), 16), int(m.group(3)), m.group(5), bool(m.group(4))))

idapro.enable_console_messages(False)
rc = idapro.open_database(A.db, False)
if rc != 0:
    sys.exit(f"open_database rc={rc}")
import ida_auto, ida_bytes, ida_funcs, ida_name, ida_ua, idautils, idc  # noqa: E402


def h(x): return f"0x{x:06X}"


def describe(ea):
    fl = ida_bytes.get_flags(ea)
    head = ida_bytes.get_item_head(ea)
    kind = ("code" if ida_bytes.is_code(fl) else "data" if ida_bytes.is_data(fl) else
            "unknown" if ida_bytes.is_unknown(fl) else "tail" if ida_bytes.is_tail(fl) else "?")
    return f"{kind} head {h(head)} size {ida_bytes.get_item_size(head)} '{idc.GetDisasm(head).split('#')[0].strip()}'"


def in_owner(ea, owner):
    f = ida_funcs.get_func(ea)
    return f is not None and f.start_ea == owner


def is_insn_word(ea):
    return ida_bytes.is_code(ida_bytes.get_flags(ea)) and ida_bytes.get_item_head(ea) == ea and ida_bytes.get_item_size(ea) == 4


def is_macro_word(ea):
    # A word of an 8-byte IDA macro instruction (`lui`+`lw` shown as `lw $v0, sym`, `li` of a 32-bit value):
    # code for the recompiler, which decodes raw words (tools/ours/ida/README.md, insn_census macro_words).
    head = ida_bytes.get_item_head(ea)
    return ida_bytes.is_code(ida_bytes.get_flags(head)) and ida_bytes.get_item_size(head) == 8 and head in (ea, ea - 4)


def data_items(owner):
    out = []
    for s, e in idautils.Chunks(owner):
        out += [ea for ea in idautils.Heads(s, e) if not ida_bytes.is_code(ida_bytes.get_flags(ea))]
    return out


def at_chunk_end(ea, owner):
    # extend=yes: ea continues one of the owner's chunks.
    return any(e == ea for _, e in idautils.Chunks(owner))


def functions_in(lo, hi):
    # extend=yes: functions starting in [lo, hi) as (start, name, None) when they may be absorbed (wholly inside
    # the range, no reference to the start from outside it) or (start, name, reason) when not.
    out = []
    g = ida_funcs.get_next_func(lo - 1)
    while g is not None and g.start_ea < hi:
        name = ida_funcs.get_func_name(g.start_ea)
        refs = [x.frm for x in idautils.XrefsTo(g.start_ea, 0) if not (lo <= x.frm < hi)]
        past = any(e > hi for _, e in idautils.Chunks(g.start_ea))
        why = (f"has a chunk past {h(hi)}" if past else f"referenced from {[h(r) for r in refs]}" if refs else None)
        out.append((g.start_ea, name, why))
        g = ida_funcs.get_next_func(g.start_ea)
    return out


failed, changed, already, absorbed = [], [], [], []
owners = sorted({o for _, o, _, _, _ in wanted})
before = {o: data_items(o) for o in owners if ida_funcs.get_func(o)}
for ea0, owner, n, why, extend in wanted:
    f = ida_funcs.get_func(owner)
    if f is None or f.start_ea != owner:
        failed.append((ea0, f"owner {h(owner)} is not a function start")); continue
    print(f"[fix_code_items] {h(ea0)} x{n}{' extend' if extend else ''} in {ida_funcs.get_func_name(owner)}: {why}")
    for x in idautils.XrefsTo(ea0, 0):
        if not x.iscode:
            print(f"   data xref to {h(ea0)} from {h(x.frm)} type {x.type}: {describe(x.frm)}")
    if extend:
        blocked = False
        for g_ea, g_name, g_why in functions_in(ea0, ea0 + 4 * n):
            if g_ea == owner:
                continue
            if g_why:
                failed.append((g_ea, f"cannot absorb {g_name}: {g_why}")); blocked = True; continue
            print(f"   absorb {g_name} {[(h(s), h(e)) for s, e in idautils.Chunks(g_ea)]} (no references)")
            if A.dry_run:
                absorbed.append((g_ea, g_name)); continue
            if not ida_funcs.del_func(g_ea):
                failed.append((g_ea, f"del_func {g_name} refused")); blocked = True; continue
            if not ida_bytes.has_user_name(ida_bytes.get_flags(g_ea)):
                ida_name.set_name(g_ea, "", ida_name.SN_NOWARN)  # IDA's dummy name (nullsub_N / sub_X) of the deleted function
            absorbed.append((g_ea, g_name))
        if blocked:
            continue
        f = ida_funcs.get_func(owner)
    for i in range(n):
        ea = ea0 + 4 * i
        print(f"   {h(ea)} before: {describe(ea)}")
        inside = in_owner(ea, owner)
        # A dry run does not grow the chunk, so later words of an extension are contiguous with the entry's start.
        joins = extend and (at_chunk_end(ea, owner) or (A.dry_run and at_chunk_end(ea0, owner)))
        if not inside and not joins:
            failed.append((ea, f"outside {ida_funcs.get_func_name(owner)}"
                               f"{' and not at the end of one of its chunks' if extend else ''}: {describe(ea)}")); continue
        code = is_insn_word(ea) or is_macro_word(ea)
        if code and inside:
            already.append(ea); continue
        if A.dry_run:
            changed.append(ea); continue
        if not code:
            ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, 4)
            if ida_ua.create_insn(ea) != 4:
                failed.append((ea, f"create_insn refused: {describe(ea)}")); continue
        if ida_funcs.get_fchunk(ea) is None or not in_owner(ea, owner):
            if not ida_funcs.append_func_tail(f, ea, ea + 4):
                failed.append((ea, "append_func_tail refused")); continue
        changed.append(ea)

if not A.dry_run and changed:
    for o in owners:
        f = ida_funcs.get_func(o)
        if f: ida_funcs.reanalyze_function(f)
    ida_auto.auto_wait()

reverted = []
for ea0, owner, n, _, _ in wanted:
    for i in range(n):
        ea = ea0 + 4 * i
        ok = (is_insn_word(ea) or is_macro_word(ea)) and in_owner(ea, owner)
        print(f"   {h(ea)} after:  {describe(ea)} in_owner={in_owner(ea, owner)} "
              f"flow_from={[h(x.frm) for x in idautils.XrefsTo(ea, 0) if x.iscode]} "
              f"flow_to_next={h(ea + 4) in [h(x.to) for x in idautils.XrefsFrom(ea, 0) if x.iscode]}")
        if not ok and not A.dry_run and ea not in [e for e, _ in failed]:
            reverted.append(ea)
for o in owners:
    f = ida_funcs.get_func(o)
    if f is None: continue
    after = data_items(o)
    print(f"   {ida_funcs.get_func_name(o)} chunks {[(h(s), h(e)) for s, e in idautils.Chunks(o)]} "
          f"data items {len(before.get(o, []))} -> {len(after)} {[h(e) for e in after]}")

print(f"[fix_code_items] {len(wanted)} entries: converted/joined {len(changed)} {[h(e) for e in changed]}; "
      f"already code {len(already)}; absorbed functions {len(absorbed)} {[(h(e), nm) for e, nm in absorbed]}; "
      f"reverted by auto-analysis {len(reverted)} {[h(e) for e in reverted]}; "
      f"failed {len(failed)} {[(h(e), m) for e, m in failed]}")
ok = not failed and not reverted
save = ok and not A.dry_run
print(f"[fix_code_items] {'DRY RUN, not saved' if A.dry_run else 'saving' if save else 'NOT saved (failures)'}")
idapro.close_database(save=save)
sys.exit(0 if ok else 1)
