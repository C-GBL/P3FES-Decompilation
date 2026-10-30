"""Read-only dump of the call graph + hardware-touch census used by docs/ANALYSIS/22_rendering.md.

Usage (idalib venv python, `import idapro` first; never on the master):
  python -I rendering_dump.py <work.i64> <out_dir> [--decompile LIST] [--disasm LIST]

Writes into <out_dir>:
  funcs.jsonl   one object per function: start, size (sum of chunks), ida name, function comment,
                callers (call sites), callees (direct calls), frefs (function addresses referenced as data,
                i.e. callbacks / function pointers), jalr count, blocks, back-edges (flow-chart edges to a
                block at or before the source), and a census decoded from the raw words:
                hw (lui of 0x1000/0x1001 = EE hardware registers), gspriv (lui 0x1200), vumem (lui 0x1100),
                spr (lui 0x7000), syscall, cop0 (mfc0/mtc0/di/ei/eret), cfc2/ctc2, qmfc2/qmtc2, vu0 (COP2 macro
                ops), lqc2/sqc2, mmi, sync, the distinct lui immediates in the hardware windows, and `hwregs`: the
                hardware registers really accessed (lui whose register is then a load/store base; VU control cfc2/ctc2).
  hx/<ea>.c     Hex-Rays text for every address in --decompile (one hex address per line)
  asm/<ea>.s    disassembly with xref comments for every address in --disasm
The database is opened without auto-analysis and closed without saving.
"""
import idapro  # noqa: F401  -- must be the first import
import argparse, json, os, sys

ap = argparse.ArgumentParser()
ap.add_argument("db")
ap.add_argument("out")
ap.add_argument("--decompile", default=None)
ap.add_argument("--disasm", default=None)
ap.add_argument("--skip-funcs", action="store_true", help="only the --decompile/--disasm dumps")
a = ap.parse_args()
if os.path.basename(a.db).lower() == "p3fes.i64":
    sys.exit("refusing the master database; copy it to ida/work_<x>.i64 first")

idapro.enable_console_messages(False)
rc = idapro.open_database(os.path.abspath(a.db), False)
if rc != 0:
    sys.exit(f"open_database rc={rc}")

import ida_funcs, ida_bytes, ida_xref, ida_gdl, ida_name, ida_lines, idautils, idc, ida_ua

os.makedirs(a.out, exist_ok=True)


def chunks(f):
    return [(s, e) for s, e in idautils.Chunks(f.start_ea)]


def census(f):
    c = dict(hw=0, gspriv=0, vumem=0, spr=0, syscall=0, cop0=0, ctc2=0, cfc2=0, qmfc2=0, qmtc2=0,
             vu0=0, lqc2=0, sqc2=0, mmi=0, sync=0)
    luis = set()
    for s, e in chunks(f):
        ea = s
        while ea < e:
            if not ida_bytes.is_code(ida_bytes.get_flags(ea)):
                ea += 4
                continue
            w = ida_bytes.get_dword(ea)
            op = w >> 26
            rs = (w >> 21) & 31
            if op == 0x0F:  # lui
                imm = w & 0xFFFF
                if imm in (0x1000, 0x1001):
                    c["hw"] += 1; luis.add(imm)
                elif imm == 0x1200:
                    c["gspriv"] += 1; luis.add(imm)
                elif imm == 0x1100:
                    c["vumem"] += 1; luis.add(imm)
                elif imm == 0x7000:
                    c["spr"] += 1; luis.add(imm)
            elif op == 0 and (w & 0x3F) == 0x0C:
                c["syscall"] += 1
            elif op == 0 and (w & 0x3F) == 0x0F:
                c["sync"] += 1
            elif op == 0x10:
                c["cop0"] += 1
            elif op == 0x12:
                if rs == 2: c["cfc2"] += 1
                elif rs == 6: c["ctc2"] += 1
                elif rs == 1: c["qmfc2"] += 1
                elif rs == 5: c["qmtc2"] += 1
                elif rs >= 0x10: c["vu0"] += 1
            elif op == 0x36:
                c["lqc2"] += 1
            elif op == 0x3E:
                c["sqc2"] += 1
            elif op == 0x1C:
                c["mmi"] += 1
            ea += 4
    c["luis"] = sorted(luis)
    c["hwregs"] = hw_registers(f)
    return c


LOADSTORE = set(range(0x20, 0x40)) | {0x1A, 0x1B, 0x1E, 0x1F}          # incl. ldl/ldr/lq/sq, lwc1/swc1, lqc2/sqc2
GPR_LOADS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x37, 0x1A, 0x1B, 0x1E}
BRANCHES = {0x04, 0x05, 0x14, 0x15}


def hw_registers(f):
    """Hardware registers really accessed: a `lui rt, 0x1000|0x1001|0x1100|0x1200` whose rt is the base of a load/store
    within 12 instructions before rt is redefined (first access per lui; constants that only build DMA tags or GIF tags are
    not counted), plus cfc2/ctc2 of the VU control registers vi26-29/31 (reported as 0xC2000000 | rs << 8 | vi)."""
    regs = set()
    for s, e in chunks(f):
        words = [ida_bytes.get_dword(ea) for ea in range(s, e, 4)]
        for i, w in enumerate(words):
            op = w >> 26
            if op == 0x12 and ((w >> 21) & 31) in (2, 6) and ((w >> 11) & 31) in (26, 27, 28, 29, 31):
                regs.add(0xC2000000 | (((w >> 21) & 31) << 8) | ((w >> 11) & 31))
            if op != 0x0F or (w & 0xFFFF) not in (0x1000, 0x1001, 0x1100, 0x1200):
                continue
            rt = (w >> 16) & 31
            for x in words[i + 1:i + 13]:
                xo = x >> 26
                base, xrt = (x >> 21) & 31, (x >> 16) & 31
                if xo in GPR_LOADS and xrt == rt and base != rt:
                    break
                if xo in LOADSTORE and base == rt:
                    off = x & 0xFFFF
                    regs.add((((w & 0xFFFF) << 16) + (off - 0x10000 if off & 0x8000 else off)) & 0xFFFFFFFF)
                    break
                if xo != 0 and xo not in LOADSTORE and xo not in BRANCHES and xrt == rt:
                    break
                if xo == 0 and ((x >> 11) & 31) == rt:
                    break
    return sorted(regs)


def walk(f):
    callees, frefs, jalr = set(), set(), 0
    for s, e in chunks(f):
        for h in idautils.Heads(s, e):
            if not ida_bytes.is_code(ida_bytes.get_flags(h)):
                continue
            w = ida_bytes.get_dword(h)
            if (w >> 26) == 0 and (w & 0x3F) == 0x09:
                jalr += 1
            for x in idautils.XrefsFrom(h, 0):
                t = x.to
                g = ida_funcs.get_func(t)
                if x.iscode:
                    if x.type in (ida_xref.fl_CN, ida_xref.fl_CF) and g and g.start_ea == t:
                        callees.add(t)
                    elif x.type in (ida_xref.fl_JN, ida_xref.fl_JF) and g and g.start_ea == t and g.start_ea != f.start_ea:
                        callees.add(t)  # tail jump
                else:
                    if g and g.start_ea == t:
                        frefs.add(t)
    return sorted(callees), sorted(frefs), jalr


def flow(f):
    blocks = back = 0
    try:
        fc = ida_gdl.FlowChart(f)
        for b in fc:
            blocks += 1
            for s in b.succs():
                if s.start_ea <= b.start_ea and ida_funcs.get_func(s.start_ea) and ida_funcs.get_func(s.start_ea).start_ea == f.start_ea:
                    back += 1
    except Exception:
        pass
    return blocks, back


if not a.skip_funcs:
    with open(os.path.join(a.out, "funcs.jsonl"), "w", encoding="utf-8") as out:
        for fea in idautils.Functions():
            f = ida_funcs.get_func(fea)
            size = sum(e - s for s, e in chunks(f))
            callers = sorted({x.frm for x in idautils.XrefsTo(fea, 0) if x.iscode and x.type in (ida_xref.fl_CN, ida_xref.fl_CF)})
            drefs_to = sorted({x.frm for x in idautils.XrefsTo(fea, 0) if not x.iscode})
            callees, frefs, jalr = walk(f)
            blocks, back = flow(f)
            rec = dict(a=fea, s=size, n=ida_funcs.get_func_name(fea),
                       cmt=(ida_funcs.get_func_cmt(f, True) or "") + "|" + (ida_funcs.get_func_cmt(f, False) or ""),
                       callers=callers, drefs_to=drefs_to, callees=callees, frefs=frefs, jalr=jalr,
                       blocks=blocks, back=back, **census(f))
            out.write(json.dumps(rec) + "\n")


def addrs(path):
    if not path:
        return []
    r = []
    for line in open(path, encoding="utf-8"):
        line = line.split("#")[0].strip()
        if line:
            r.append(int(line.split()[0], 16))
    return r


dl = addrs(a.decompile)
if dl:
    import ida_hexrays
    ida_hexrays.init_hexrays_plugin()
    os.makedirs(os.path.join(a.out, "hx"), exist_ok=True)
    for ea in dl:
        p = os.path.join(a.out, "hx", f"{ea:08x}.c")
        try:
            cf = ida_hexrays.decompile(ea)
            txt = str(cf)
        except Exception as ex:  # noqa: BLE001
            txt = f"// decompile failed: {ex}"
        open(p, "w", encoding="utf-8").write(txt)

sl = addrs(a.disasm)
if sl:
    os.makedirs(os.path.join(a.out, "asm"), exist_ok=True)
    for ea in sl:
        f = ida_funcs.get_func(ea)
        if not f:
            continue
        lines = [f"; {ida_funcs.get_func_name(f.start_ea)} {f.start_ea:08x}"]
        for s, e in chunks(f):
            lines.append(f"; chunk {s:08x}-{e:08x}")
            for h in idautils.Heads(s, e):
                dis = ida_lines.tag_remove(ida_lines.generate_disasm_line(h, 0) or "")
                lines.append(f"{h:08x}  {ida_bytes.get_dword(h):08x}  {dis}")
        open(os.path.join(a.out, "asm", f"{f.start_ea:08x}.s"), "w", encoding="utf-8").write("\n".join(lines) + "\n")

idapro.close_database(False)
print("done")
