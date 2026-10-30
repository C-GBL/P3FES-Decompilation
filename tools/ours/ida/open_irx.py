"""Create/open an IDA database for one IOP module (IRX) and dump it for reading.

Usage (idalib venv python; `import idapro` must be first):
  python open_irx.py <module.irx> <out.i64> [--rebuild] [--dump DIR] [--names FILE] [--no-save]

Behaviour:
  * IRX = MIPS R3000 little-endian relocatable ELF (e_type 0xFF80) with an `.iopmod` section. IDA's
    ELF loader maps the sections at their link addresses (text from 0, i.e. relocation base 0), so
    every VA in this database is a **module offset**; processor `mipsl`.
  * Reads `.iopmod` (entry, gp, text/data/bss sizes, version, module name) with struct, not IDA.
  * Names the IOP import stubs: an import table is `0x41E00000, 0, version, name[8]` followed by
    `jr $ra; addiu $zero,$zero,<ord>` pairs and a zero pair. Ordinals are resolved to ps2sdk names
    from the `DECLARE_IMPORT_TABLE(lib, ...)` / `DECLARE_IMPORT(ord, name)` lines of
    tools/third_party/ps2sdk/iop/**/include/*.h (AFL-2.0; numbering only) -> `<lib>_<name>`, else
    `<lib>_<ord>`. Each stub becomes a function.
  * Names export tables (`0x41C00000, 0, version, name[8]`, then function pointers up to 0) as
    `<lib>_export_<n>` (an analyst names file can override).
  * `--names FILE`: `<hex ea> <name>` lines applied after analysis (auto names only).
  * `--dump DIR` writes DIR/<MODULE>.asm (every function, with callers and data references) and
    DIR/<MODULE>.data (rodata/data words with names). DIR should be gitignored (`ida/logs/irx/`).
The database and dumps contain the module's bytes; they stay under the gitignored `ida/`.
"""
import idapro  # noqa: F401  -- first import
import argparse, glob, os, re, struct, sys, time

ap = argparse.ArgumentParser()
ap.add_argument("irx"); ap.add_argument("out_i64")
ap.add_argument("--rebuild", action="store_true")
ap.add_argument("--dump", default=None)
ap.add_argument("--names", default=None)
ap.add_argument("--no-save", action="store_true")
a = ap.parse_args()
irx = os.path.abspath(a.irx); out = os.path.abspath(a.out_i64)
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
T0 = time.time()

def log(m):
    print(f"[+{time.time()-T0:6.1f}s] {m}", flush=True)

# ---- .iopmod --------------------------------------------------------------------------------------
data = open(irx, "rb").read()
e_type, e_machine = struct.unpack_from("<HH", data, 16)
shoff, = struct.unpack_from("<I", data, 32)
shnum, shstrndx = struct.unpack_from("<HH", data, 48)
secs = [struct.unpack_from("<IIIIIIIIII", data, shoff + 40 * i) for i in range(shnum)]
strtab = secs[shstrndx]
def secname(off):
    s = data[strtab[4] + off:]
    return s[:s.index(b"\0")].decode("ascii", "replace")
iopmod = next((s for s in secs if secname(s[0]) == ".iopmod"), None)
IOPMOD = {}
if iopmod:
    o = iopmod[4]
    mi, entry, gp, tsz, dsz, bsz, ver = struct.unpack_from("<IIIIIIH", data, o)
    nm = data[o + 26:o + iopmod[5]].split(b"\0")[0].decode("ascii", "replace")
    IOPMOD = dict(moduleinfo=mi, entry=entry, gp=gp, text=tsz, data=dsz, bss=bsz, version=ver, name=nm)
log(f"irx={irx} e_type={e_type:#x} machine={e_machine} iopmod={ {k: (hex(v) if isinstance(v, int) else v) for k, v in IOPMOD.items()} }")
MODNAME = os.path.splitext(os.path.basename(irx))[0].upper()

# ---- ps2sdk import ordinals ---------------------------------------------------------------------
IMPORTS = {}
for h in glob.glob(os.path.join(ROOT, "tools", "third_party", "ps2sdk", "iop", "**", "include", "*.h"), recursive=True):
    lib = None
    for line in open(h, encoding="utf-8", errors="replace"):
        m = re.search(r"DECLARE_IMPORT_TABLE\((\w+)\s*,", line)
        if m: lib = m.group(1); continue
        m = re.search(r"DECLARE_IMPORT\((\d+)\s*,\s*(\w+)\)", line)
        if m and lib: IMPORTS.setdefault(lib, {})[int(m.group(1))] = m.group(2)
log(f"ps2sdk import tables: {len(IMPORTS)}")

idapro.enable_console_messages(False)
if a.rebuild:
    stem = os.path.splitext(out)[0]
    for ext in (".i64", ".id0", ".id1", ".id2", ".nam", ".til"):   # incl. a crashed run's unpacked files
        if os.path.exists(stem + ext):
            os.remove(stem + ext); log(f"--rebuild: removed {stem + ext}")
existing = os.path.exists(out)
rc = idapro.open_database(out if existing else irx, not existing, "" if existing else f"-pmipsl -o{out}")
log(f"open_database rc={rc} existing={existing}")
if rc != 0: sys.exit(rc)

import ida_auto, ida_bytes, ida_funcs, ida_name, ida_segment, ida_idaapi, ida_lines, ida_ua, ida_xref, idautils, idc  # noqa: E402

segs = [ida_segment.getnseg(i) for i in range(ida_segment.get_segm_qty())]
for s in segs:
    log(f"  seg {ida_segment.get_segm_name(s):10s} {s.start_ea:#x}-{s.end_ea:#x}")
text = ida_segment.get_segm_by_name(".text") or segs[0]
TS, TE = text.start_ea, text.end_ea

def cstr(ea, n=8):
    b = ida_bytes.get_bytes(ea, n) or b""
    return b.split(b"\0")[0].decode("ascii", "replace")

def set_auto(ea, nm):
    cur = ida_name.get_name(ea) or ""
    if cur and not cur.startswith(("sub_", "loc_", "nullsub_", "j_", "unk_", "dword_", "off_")) and cur != nm:
        return False
    return ida_name.set_name(ea, nm, ida_name.SN_FORCE | ida_name.SN_NOWARN)

n_imp = n_exp = 0
imports_seen = []
exports_seen = []
for ea in range(TS, TE - 20, 4):
    w = ida_bytes.get_dword(ea)
    if w == 0x41E00000 and ida_bytes.get_dword(ea + 4) == 0:
        lib = cstr(ea + 12); ver = ida_bytes.get_dword(ea + 8)
        ida_name.set_name(ea, f"imptab_{lib}", ida_name.SN_FORCE | ida_name.SN_NOWARN)
        p = ea + 20; cnt = 0
        while p < TE and ida_bytes.get_dword(p) == 0x03E00008:
            w2 = ida_bytes.get_dword(p + 4)
            if (w2 & 0xFFFF0000) != 0x24000000: break
            o = w2 & 0xFFFF
            nm = IMPORTS.get(lib, {}).get(o, f"{o}")
            ida_bytes.del_items(p, 0, 8); ida_ua.create_insn(p); ida_ua.create_insn(p + 4)
            f = ida_funcs.get_func(p)
            if f and f.start_ea != p: ida_funcs.del_func(f.start_ea)
            ida_funcs.add_func(p, p + 8)
            ida_name.set_name(p, f"{lib}_{nm}", ida_name.SN_FORCE | ida_name.SN_NOWARN)
            imports_seen.append((p, lib, o, nm)); cnt += 1; n_imp += 1
            p += 8
        log(f"  import table {lib} v{ver:#x} @ {ea:#x}: {cnt} stubs")
    elif w == 0x41C00000 and ida_bytes.get_dword(ea + 4) == 0:
        lib = cstr(ea + 12); ver = ida_bytes.get_dword(ea + 8)
        ida_name.set_name(ea, f"exptab_{lib}", ida_name.SN_FORCE | ida_name.SN_NOWARN)
        p = ea + 20; i = 0
        while p < TE:
            v = ida_bytes.get_dword(p)
            if v == 0 or not (TS <= v < TE): break
            ida_bytes.create_dword(p, 4)
            if not ida_funcs.get_func(v): ida_auto.auto_make_code(v); ida_funcs.add_func(v)
            set_auto(v, f"{lib}_export_{i}")
            exports_seen.append((v, lib, i)); i += 1; n_exp += 1
            p += 4
        log(f"  export table {lib} v{ver:#x} @ {ea:#x}: {i} entries")
if IOPMOD.get("entry") is not None and TS <= IOPMOD["entry"] < TE:
    ida_funcs.add_func(IOPMOD["entry"]); set_auto(IOPMOD["entry"], f"{MODNAME.lower()}_start")
ida_auto.auto_wait()

# prologue seeding for code IDA did not reach (callbacks stored in tables)
added = 0
for ea in range(TS, TE, 4):
    if ida_bytes.is_code(ida_bytes.get_flags(ea)) or ida_funcs.get_func(ea): continue
    w = ida_bytes.get_dword(ea)
    if (w & 0xFFFF8000) == 0x27BD8000 and (w & 7) == 0:   # addiu $sp,$sp,-N
        if ida_funcs.add_func(ea): added += 1
ida_auto.auto_wait()
log(f"imports {n_imp}, exports {n_exp}, prologue-seeded {added}, functions {ida_funcs.get_func_qty()}")

if a.names:
    applied = 0
    for line in open(a.names, encoding="utf-8"):
        line = line.split("#", 1)[0].strip()
        if not line: continue
        ea_s, nm = line.split()[:2]
        ea = int(ea_s, 16)
        if not ida_funcs.get_func(ea) and ida_bytes.is_code(ida_bytes.get_flags(ea)): ida_funcs.add_func(ea)
        if ida_name.set_name(ea, nm, ida_name.SN_FORCE | ida_name.SN_NOWARN): applied += 1
    log(f"names applied: {applied}")

code = infn = 0
for ea in range(TS, TE, 4):
    if ida_bytes.is_code(ida_bytes.get_flags(ea)):
        code += 1; infn += 1 if ida_funcs.get_func(ea) else 0
log(f"code words {code} (in functions {infn}) of {(TE-TS)//4}")

if a.dump:
    os.makedirs(a.dump, exist_ok=True)
    with open(os.path.join(a.dump, f"{MODNAME}.asm"), "w", encoding="utf-8") as fh:
        fh.write(f"# {MODNAME} iopmod {IOPMOD}\n# imports: " + ", ".join(f"{p:#x}={lib}.{nm}" for p, lib, o, nm in imports_seen) + "\n")
        fh.write("# exports: " + ", ".join(f"{lib}[{i}]={v:#x}" for v, lib, i in exports_seen) + "\n")
        for fea in idautils.Functions(TS, TE):
            f = ida_funcs.get_func(fea)
            callers = sorted({x.frm for x in idautils.XrefsTo(fea) if x.iscode})
            drefs = sorted({x.frm for x in idautils.XrefsTo(fea) if not x.iscode})
            fh.write(f"\n== {ida_name.get_name(fea)} {fea:#x}-{f.end_ea:#x} callers[{len(callers)}]: "
                     + " ".join(f"{c:#x}" for c in callers[:24]) + (f" drefs: " + " ".join(f"{d:#x}" for d in drefs[:12]) if drefs else "") + "\n")
            for ea in idautils.FuncItems(fea):
                lbl = ida_name.get_name(ea) if ea != fea and ida_name.get_name(ea) else ""
                dis = ida_lines.tag_remove(idc.generate_disasm_line(ea, 0) or "")
                refs = [x.to for x in idautils.XrefsFrom(ea) if not x.iscode]
                extra = ""
                if refs:
                    extra = "  ; -> " + " ".join(f"{r:#x}" + (f"({ida_name.get_name(r)})" if ida_name.get_name(r) else "") for r in refs[:3])
                if lbl: fh.write(f"  {lbl}:\n")
                fh.write(f"    {ea:6x}: {ida_bytes.get_dword(ea):08x}  {dis}{extra}\n")
    with open(os.path.join(a.dump, f"{MODNAME}.data"), "w", encoding="utf-8") as fh:
        for s in segs:
            nm = ida_segment.get_segm_name(s)
            if nm in (".text",): continue
            fh.write(f"\n== {nm} {s.start_ea:#x}-{s.end_ea:#x}\n")
            ea = s.start_ea
            while ea < s.end_ea:
                n = ida_name.get_name(ea)
                b = ida_bytes.get_bytes(ea, 4) if ida_bytes.is_loaded(ea) else None
                w = struct.unpack("<I", b)[0] if b and len(b) == 4 else None
                asc = "".join(chr(c) if 32 <= c < 127 else "." for c in (b or b""))
                fh.write(f"  {ea:6x}: {'--------' if w is None else f'{w:08x}'} {asc:4s} {n or ''}\n")
                ea += 4
    log(f"dumped to {a.dump}")

if a.no_save:
    idapro.close_database(False); log("closed without save")
else:
    idapro.close_database(True); log(f"saved {out}")
