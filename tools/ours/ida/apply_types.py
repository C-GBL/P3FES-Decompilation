"""apply_types.py -- import a topic's C header into the database's type library and apply types at addresses.

Counterpart of docs/ANALYSIS/PHASE2_BRIEF.md item 3b: a topic agent exports `symbols/types/<topic>.h`
(plain C declarations, re-parseable by ida_typeinf.parse_decls) and `symbols/types/<topic>.apply.txt`
with one line per typed address:
    <addr8> <TypeName>              apply a struct/typedef at the address
    <addr8> <TypeName>[<count>]     apply an array of <count> elements
    # comments and blank lines are ignored
The lead runs this on the master (one process at a time). Idempotent: re-applying the same type is a no-op.

Usage (idalib venv python, from the repo root):
  python tools/ours/ida/apply_types.py ida/p3fes.i64 symbols/types/file_io.h symbols/types/file_io.apply.txt [--dry-run]
Then re-export:  python tools/ours/ida/export_symbols.py ida/p3fes.i64 . --apply-names tools/ours/ida/names_manual.txt
"""
import idapro  # must be first

import argparse
import re
import sys
import time

ap = argparse.ArgumentParser()
ap.add_argument("db")
ap.add_argument("header")
ap.add_argument("apply_list")
ap.add_argument("--dry-run", action="store_true")
A = ap.parse_args()

LINE_RE = re.compile(r"^([0-9A-Fa-f]{6,8})\s+([A-Za-z_]\w*)(?:\[(\d+)\])?\s*(?:#.*)?$")
rows = []
for ln in open(A.apply_list, encoding="utf-8"):
    s = ln.strip()
    if not s or s.startswith("#"):
        continue
    m = LINE_RE.match(s)
    if not m:
        print(f"[apply_types] unparsable line skipped: {s[:80]}")
        continue
    rows.append((int(m.group(1), 16), m.group(2), int(m.group(3)) if m.group(3) else 0))
header_text = open(A.header, encoding="utf-8").read()

t0 = time.time()
rc = idapro.open_database(A.db, False)
if rc != 0:
    sys.exit(f"open_database rc={rc}")
import ida_typeinf, ida_bytes  # noqa: E402

# 1. parse the header into the local type library (errors are counted, not fatal, so we can report them)
errors = ida_typeinf.parse_decls(None, header_text, None, ida_typeinf.PT_TYP | ida_typeinf.PT_SIL)
print(f"[apply_types] parse_decls({A.header}): {errors} error(s)")

def named_tinfo(name):
    tif = ida_typeinf.tinfo_t()
    return tif if tif.get_named_type(None, name) else None

applied, same, missing_type, failed = [], [], [], []
for ea, tname, count in rows:
    base = named_tinfo(tname)
    if base is None:
        missing_type.append((ea, tname))
        continue
    tif = base
    if count:
        tif = ida_typeinf.tinfo_t()
        if not tif.create_array(base, count):
            failed.append((ea, f"{tname}[{count}]", "create_array"))
            continue
    cur = ida_typeinf.tinfo_t()
    if ida_typeinf.guess_tinfo(cur, ea) and cur.dstr() == tif.dstr() and ida_bytes.is_head(ida_bytes.get_flags(ea)):
        same.append(ea)
        continue
    if A.dry_run:
        applied.append((ea, tif.dstr()))
        continue
    # make room: undefine whatever items currently occupy the range, then apply definitively
    size = tif.get_size()
    if size and size != ida_typeinf.BADSIZE:
        ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, size)
    if ida_typeinf.apply_tinfo(ea, tif, ida_typeinf.TINFO_DEFINITE):
        applied.append((ea, tif.dstr()))
    else:
        failed.append((ea, tif.dstr(), "apply_tinfo"))

print(f"[apply_types] rows {len(rows)}: applied {len(applied)}, already typed {len(same)}, "
      f"missing type {len(missing_type)} {sorted({t for _, t in missing_type})}, failed {len(failed)}")
for ea, t, why in failed[:10]:
    print(f"   FAILED 0x{ea:06X} {t} ({why})")
print(f"[apply_types] {'DRY RUN' if A.dry_run else 'saving'} ({time.time() - t0:.1f}s)")
idapro.close_database(save=not A.dry_run)
sys.exit(1 if (failed or missing_type) else 0)
