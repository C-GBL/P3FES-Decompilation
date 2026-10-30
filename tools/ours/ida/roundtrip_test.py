"""Round-trip test for symbols/p3fes.sym: delete 3 user names from the DB, re-import, verify.

Usage: python roundtrip_test.py <ida/p3fes.i64> <symbols/p3fes.sym>
The database is saved only if the round trip succeeded (names restored); otherwise closed without save.
"""
import idapro  # noqa -- must be first
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_symbols import parse_sym, apply_rows

i64, sym = os.path.abspath(sys.argv[1]), os.path.abspath(sys.argv[2])
rows = parse_sym(sym)
victims = [r for r in rows if r[2] == "F" and r[3].startswith("_sce")][:2] + [r for r in rows if r[2] == "F" and r[3] == "main"]
assert len(victims) == 3, victims
idapro.enable_console_messages(False)
assert idapro.open_database(i64, False) == 0
import ida_name, ida_funcs
for ea, _, _, name in victims:
    assert ida_name.get_name(ea) == name, (hex(ea), name, ida_name.get_name(ea))
    ida_name.set_name(ea, "", ida_name.SN_NOWARN)
    print(f"deleted {name} -> now {ida_funcs.get_func_name(ea)}")
    assert ida_funcs.get_func_name(ea).startswith("sub_")
stats = apply_rows(rows, False, print)
print("import stats:", stats)
ok = all(ida_name.get_name(ea) == name for ea, _, _, name in victims)
for ea, _, _, name in victims: print(f"restored? {name} @ {ea:#x}: {ida_name.get_name(ea) == name}")
idapro.close_database(ok)
print("ROUNDTRIP", "OK" if ok else "FAILED")
sys.exit(0 if ok else 1)
