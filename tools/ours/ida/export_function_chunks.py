"""Read-only idalib export (run with the idalib venv python, see tools/ours/ida/README.md; e.g.
  <idalib python> tools/ours/ida/export_function_chunks.py ida/work_<copy>.i64 symbols/function_chunks.txt   (copy the master first: the script refuses ida/p3fes.i64 by name))
 of function chunk ranges + data items inside chunks (addresses only).
Output: compact text, one function per line:
  <start> <name> C <s>-<e> [<s>-<e> ...] [D <ea>:<size> ...]
Names are written in their exported form (ADR-0009: unverified community hints -> `sub_<EA>`, as in
symbols/functions.json; rule in import_symbols.withheld_name_map, names_manual.txt next to this script).
Opens a WORK copy without auto-analysis and closes without saving."""
import sys, os
import idapro  # noqa: must be first
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_symbols import load_manual_addresses, withheld_name_map
idapro.enable_console_messages(False)
i64, out = os.path.abspath(sys.argv[1]), sys.argv[2]
if os.path.basename(i64).lower() == "p3fes.i64":
    print("refusing master database"); sys.exit(2)
rc = idapro.open_database(i64, False)
print("open rc", rc)
if rc != 0: sys.exit(rc)
import idautils, ida_funcs, ida_bytes
withheld = withheld_name_map(load_manual_addresses(os.path.join(os.path.dirname(os.path.abspath(__file__)), "names_manual.txt")))
lines = []; nf = 0; nchunks = 0; ndata = 0
for f_ea in idautils.Functions():
    pfn = ida_funcs.get_func(f_ea)
    if pfn is None: continue
    nf += 1
    chunks = [(s, e) for s, e in idautils.Chunks(f_ea)]
    data = []
    for s, e in chunks:
        for ea in idautils.Heads(s, e):
            if not ida_bytes.is_code(ida_bytes.get_flags(ea)):
                data.append((ea, ida_bytes.get_item_size(ea)))
    nchunks += len(chunks); ndata += len(data)
    name = ida_funcs.get_func_name(f_ea)
    line = f"{f_ea:x} {withheld.get(name, name)} C " + " ".join(f"{s:x}-{e:x}" for s, e in chunks)
    if data: line += " D " + " ".join(f"{ea:x}:{sz}" for ea, sz in data)
    lines.append(line)
idapro.close_database(False)
with open(out, "w", encoding="utf-8", newline="\n") as fo:
    fo.write(f"# function chunks + data items inside chunks; exported read-only from {os.path.basename(i64)} by tools/ours/ida/export_function_chunks.py\n")
    fo.write(f"# functions={nf} chunks={nchunks} data_items={ndata}\n")
    fo.write("\n".join(lines) + "\n")
print(f"functions={nf} chunks={nchunks} data_items={ndata} withheld_names={len(withheld)} -> {out}")
