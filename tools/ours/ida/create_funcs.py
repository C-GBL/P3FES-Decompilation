"""create_funcs.py -- define functions IDA auto-analysis missed, from a reviewed list.

Reads tools/ours/ida/funcs_manual.txt (`<hex addr> <reason>` lines, `#` comments; optional tokens
`size=0x..` (bounded fallback / extension of an existing function that ends short of it) and `code=yes`
(the bounded range is reviewed code: IDA's data items inside it are undefined and decoded first)), and for each
address that is not already a function start calls ida_funcs.add_func(ea) so IDA finds the end
itself (falling through tail calls / jump tables as it normally would).  Addresses that fall inside
an existing function body are reported as `inside:<func>` and NOT split automatically -- a mid-body
call target (see 06_ghidra_crosscheck.md, "54 mid-body jal targets") is a recompiler concern, not a
boundary error, and splitting would corrupt the enclosing function.

Usage (idalib venv python, from the repo root):
  python tools/ours/ida/create_funcs.py ida/p3fes.i64 tools/ours/ida/funcs_manual.txt [--dry-run]
Then re-export:  python tools/ours/ida/export_symbols.py ida/p3fes.i64 . --apply-names tools/ours/ida/names_manual.txt
"""
import idapro  # must be first

import argparse
import sys
import time

ap = argparse.ArgumentParser()
ap.add_argument("db")
ap.add_argument("list_file")
ap.add_argument("--dry-run", action="store_true")
A = ap.parse_args()

wanted = []
for ln in open(A.list_file, encoding="utf-8"):
    s = ln.strip()
    if not s or s.startswith("#"):
        continue
    tok = s.split(None, 1)
    why = tok[1] if len(tok) > 1 else ""
    size = 0
    for t in why.split():
        if t.startswith("size="):          # optional: size=0x980 (hex) from the Ghidra cross-check
            size = int(t[5:], 16)
    wanted.append((int(tok[0], 16), why, size))

t0 = time.time()
rc = idapro.open_database(A.db, False)
if rc != 0:
    sys.exit(f"open_database rc={rc}")
import ida_auto, ida_bytes, ida_funcs, ida_name, ida_ua  # noqa: E402


def describe(ea):
    fl = ida_bytes.get_flags(ea)
    kind = "code" if ida_bytes.is_code(fl) else "data" if ida_bytes.is_data(fl) else "unknown" if ida_bytes.is_unknown(fl) else "tail" if ida_bytes.is_tail(fl) else "?"
    sz = ida_bytes.get_item_size(ea)
    head = ida_bytes.get_item_head(ea)
    return f"{kind} item 0x{sz:X}B head 0x{head:06X}"


def make_code(ea, end):
    # Reviewed `code=yes` ranges: IDA typed some words as data (or left them unexplored) inside a
    # function body; undefine and decode every word, as fix_code_items.py does for single words.
    ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, end - ea)
    for a in range(ea, end, 4):
        ida_ua.create_insn(a)


created, existing, inside, failed, extended = [], [], [], [], []
for ea, why, size in wanted:
    f = ida_funcs.get_func(ea)
    if f and f.start_ea == ea:
        # `size=` on an existing function that ends short of it (IDA stopped at a function it then
        # dropped): extend it when nothing else starts inside the requested range.
        if size and f.end_ea < ea + size and not A.dry_run:
            nxt = ida_funcs.get_next_func(ea)
            if (not nxt or nxt.start_ea >= ea + size) and ida_funcs.set_func_end(ea, ea + size):
                extended.append(ea)
                continue
        existing.append(ea)
        continue
    if f:
        if "split=yes" in why and not A.dry_run:
            # Reviewed case: two functions IDA merged (the first one falls through / has no return
            # IDA recognised). Truncate the enclosing function at ea, then define the new one.
            if ida_funcs.set_func_end(f.start_ea, ea) and ida_funcs.add_func(ea):
                created.append(ea)
                continue
            failed.append((ea, f"split of {ida_funcs.get_func_name(f.start_ea)} failed", describe(ea)))
            continue
        inside.append((ea, ida_funcs.get_func_name(f.start_ea)))
        continue
    if A.dry_run:
        created.append(ea)
        continue
    before = describe(ea)
    if not ida_bytes.is_code(ida_bytes.get_flags(ea)):
        # IDA typed the bytes as data (a table it guessed) or left them unexplored:
        # undefine the item covering ea, decode one instruction, let autoanalysis follow.
        ida_bytes.del_items(ea, ida_bytes.DELIT_EXPAND, 4)
        ida_ua.create_insn(ea)
        ida_auto.auto_wait()
    if ida_funcs.add_func(ea):
        created.append(ea)
        continue
    ida_auto.auto_make_code(ea)
    ida_auto.auto_wait()
    if ida_funcs.add_func(ea):
        created.append(ea)
        continue
    # Bounded fallback: IDA's function finder refuses when the flow from ea runs into an existing
    # function. If the list gives a size (from the Ghidra cross-check), create [ea, end) with end
    # clamped to the next function start so nothing overlaps.
    if size:
        nxt = ida_funcs.get_next_func(ea)
        end = min(ea + size, nxt.start_ea) if nxt else ea + size
        if ida_funcs.add_func(ea, end):
            created.append(ea)
            continue
        if "code=yes" in why:
            make_code(ea, end)
            if ida_funcs.add_func(ea, end):
                created.append(ea)
                continue
    failed.append((ea, before, describe(ea)))

if not A.dry_run:
    ida_auto.auto_wait()

def h(x): return f"0x{x:06X}"
print(f"[create_funcs] requested {len(wanted)}: created {len(created)} {[h(e) for e in created]}; "
      f"already functions {len(existing)}; inside existing body {len(inside)} {[(h(e), n) for e, n in inside]}; "
      f"failed {len(failed)} {[(h(e), b, a) for e, b, a in failed]}; extended {len(extended)} {[h(e) for e in extended]}")
if not A.dry_run and (created or extended):
    for ea in created + extended:
        f = ida_funcs.get_func(ea)
        print(f"   {h(ea)} -> {ida_funcs.get_func_name(ea)} size 0x{(f.end_ea - f.start_ea) if f else 0:X}")
print(f"[create_funcs] {'DRY RUN' if A.dry_run else 'saving'} ({time.time() - t0:.1f}s)")
idapro.close_database(save=not A.dry_run)
