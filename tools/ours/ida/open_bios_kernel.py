"""Create/open an IDA database for the EE kernel (`KERNEL` ROMDIR entry) of a PS2 BIOS image.

Usage (idalib venv python; `import idapro` must be first):
  python open_bios_kernel.py <bios.bin> <out.i64> [--expect-romver 0230A] [--log PATH] [--no-save] [--rebuild]

Behaviour:
  * Parses the ROMDIR with bios_romdir.py (same directory), checks ROMVER, finds `KERNEL`.
  * Loads the KERNEL entry **in place** from the BIOS file (ida_loader.load_binary_file with a
    file offset/size) at kseg0 0x80000000 with processor `r5900l`; nothing is extracted or
    copied outside the gitignored database. Adds an uninitialised `kbss` segment after the image
    (kernel globals referenced via `lui 0x8001/0x8002`).
  * Seeds analysis at the R5900 exception vectors (0x80000000 TLB refill, 0x80000080 counter,
    0x80000100 debug, 0x80000180 common, 0x80000200 interrupt) and at `addiu $sp,-N` prologues,
    runs auto-analysis, then derives the **syscall table** from the dispatcher itself: common
    vector -> ExcCode table (`lui/lw $k0`) -> ExcCode 8 handler -> `sll $v1,2; lw $k0,TBL($v1)`.
    Every slot is commented with ps2_syscalls.py's name; a slot is reached by both `+N` and `-N`
    (the dispatcher negates negative numbers), so a slot whose only ps2sdk define is negative is
    named after that define (`iSignalSema`, not `unknown_syscall_43`). Each target gets a function
    named `ksc_<NN>_<Name>` (one shared stub for the RFU/unimplemented numbers); kseg1 targets
    (`0xA000xxxx`, the uncached-mode cache syscalls) are resolved to their kseg0 code.
  * Also seeds `kernel_entry 0x80001000` (reached only from the ROM RESET code's `jr $t0`).
  * Names the vectors (`kvec_*`), the interrupt-pending dispatch targets (`kint_ip<N>_*`) and the
    default exception handler, then (new DB only) splits `jal` targets that fell inside another
    function, attaches switch_info for the `sltiu N` / `lw TBL` / `jr` idiom IDA's MIPS module does
    not resolve, adds the runtime-installed dispatch entries (stored into the INTC/DMAC tables by
    `kintr_init_all`), and adds leaf functions IDA did not reach (a non-zero, non-code run that
    starts right after a `jr $ra` + delay slot and decodes to code ending in `jr $ra`).
  * Applies the analyst names of docs/ANALYSIS/15_ee_kernel_semantics.md (FN/DN tables) onto auto
    names only, and logs code-word coverage.
  * `--rebuild` deletes an existing <out.i64> first and re-creates it from the BIOS.
  * Writes `ida/logs/bios_kernel_open.log` and `ida/logs/bios_kernel_syscalls.txt`
    (number -> handler VA). If <out.i64> exists it is just opened (no re-analysis).
Only kernel VAs and names are logged; no ROM bytes are written anywhere but the database.
"""
import idapro  # noqa: F401  -- first import
import argparse, os, sys, time, struct

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import bios_romdir, ps2_syscalls  # noqa: E402

ap = argparse.ArgumentParser()
ap.add_argument("bios"); ap.add_argument("out_i64")
ap.add_argument("--expect-romver", default="0230A")
ap.add_argument("--log", default=None)
ap.add_argument("--no-save", action="store_true")
ap.add_argument("--rebuild", action="store_true")
a = ap.parse_args()
bios = os.path.abspath(a.bios); out = os.path.abspath(a.out_i64)
logdir = os.path.join(os.path.dirname(out), "logs"); os.makedirs(logdir, exist_ok=True)
log_path = a.log or os.path.join(logdir, "bios_kernel_open.log")
logf = open(log_path, "a", encoding="utf-8"); T0 = time.time()

def log(m):
    line = f"[{time.strftime('%H:%M:%S')} +{time.time()-T0:6.1f}s] {m}"
    print(line, flush=True); logf.write(line + "\n"); logf.flush()

with open(bios, "rb") as f:
    data = f.read()
rd, entries = bios_romdir.parse(data)
romver = next(e for e in entries if e["name"] == "ROMVER")
rv = data[romver["offset"]:romver["offset"] + romver["size"]].rstrip(b"\0\n").decode("ascii", "replace")
log(f"bios={bios} size={len(data):#x} ROMVER={rv!r} romdir@{rd:#x} entries={len(entries)}")
if not rv.startswith(a.expect_romver):
    log(f"ERROR: ROMVER does not start with {a.expect_romver}"); sys.exit(3)
kern = next(e for e in entries if e["name"] == "KERNEL")
KOFF, KSIZE = kern["offset"], kern["size"]
BASE = 0x80000000
log(f"KERNEL entry: file offset {KOFF:#x} size {KSIZE:#x} -> load at {BASE:#x}..{BASE+KSIZE:#x}")
del data

idapro.enable_console_messages(False)
if a.rebuild and os.path.exists(out):
    os.remove(out); log(f"--rebuild: removed {out}")
existing = os.path.exists(out)
if existing:
    rc = idapro.open_database(out, False)
else:
    rc = idapro.open_database(bios, False, f"-pr5900l -b{BASE >> 4:x} -o{out}")
log(f"open_database rc={rc} existing={existing}")
if rc != 0: sys.exit(rc)

import ida_ida, ida_segment, ida_loader, ida_diskio, ida_bytes, ida_auto, ida_funcs, ida_name, ida_idaapi, ida_ua, idautils, idc  # noqa: E402

KEND = BASE + KSIZE
if not existing:
    ida_segment.del_segm(BASE, ida_segment.SEGMOD_KILL)           # the whole-ROM segment the loader made
    li = ida_diskio.open_linput(bios, False)
    ok = ida_loader.load_binary_file(bios, li, ida_loader.NEF_SEGS | ida_loader.NEF_CODE, KOFF, BASE >> 4, 0, KSIZE)
    ida_diskio.close_linput(li)
    log(f"load_binary_file in place: {ok}")
    s = ida_segment.getseg(BASE); ida_segment.set_segm_name(s, "kernel"); s.perm = 7; s.update()
    bss = ida_segment.segment_t(); bss.start_ea = (KEND + 0xF) & ~0xF; bss.end_ea = 0x80080000
    bss.bitness = 1; bss.type = ida_segment.SEG_BSS; bss.perm = 6
    ida_segment.add_segm_ex(bss, "kbss", "BSS", ida_segment.ADDSEG_NOSREG | ida_segment.ADDSEG_SPARSE)
    for s in [ida_segment.getnseg(i) for i in range(ida_segment.get_segm_qty())]:
        log(f"  seg {ida_segment.get_segm_name(s):8s} {s.start_ea:#x}-{s.end_ea:#x} type={s.type}")
    # seed: exception vectors first (their dispatch tables are followed below), then prologues
    # 0x80001000 = kernel entry: the ROM RESET code's EE path ends `lui $t0,0x8000; ori $t0,0x1000;
    # jr $t0` (ROM 0xBFC008E4..0xBFC008F4); nothing in the image calls it, so IDA would never find it.
    for ea in (0x80000000, 0x80000080, 0x80000100, 0x80000180, 0x80000200, 0x80001000):
        ida_funcs.add_func(ea); ida_auto.auto_make_code(ea)
    ida_auto.auto_wait()
    added = 0
    for ea in range(BASE, KEND, 4):
        if ida_bytes.is_code(ida_bytes.get_flags(ea)): continue
        w = ida_bytes.get_dword(ea)
        prev = ida_bytes.get_dword(ea - 4)
        if (w & 0xFFFF0000) == 0x27BD0000 and (w & 0x8000) and (w & 0xF) == 0                 and (prev & 0xFFFF0000) != 0x3C1D0000:   # addiu $sp,$sp,-N, not the tail of `li $sp`
            if ida_funcs.add_func(ea): added += 1
    ida_auto.auto_wait()
    log(f"auto-analysis done: functions={ida_funcs.get_func_qty()} prologue-seeded={added}")

# ---- syscall table: derived from the dispatcher, never from a pointer-run heuristic -----------
def k0(v): return (v - 0x20000000) if 0xA0000000 <= v < 0xC0000000 else v   # kseg1 -> kseg0 alias
def in_code(v): return BASE <= k0(v) < KEND and (v & 3) == 0

def decode_lui_lw(ea_lui, ea_lw):
    """`lui $k0, HI` ... `lw $k0, LO($k0)` -> HI<<16 + sext(LO)."""
    w1, w2 = ida_bytes.get_dword(ea_lui), ida_bytes.get_dword(ea_lw)
    assert (w1 >> 26) == 0x0F and (w2 >> 26) == 0x23, (hex(w1), hex(w2))
    lo = w2 & 0xFFFF; lo -= 0x10000 if lo & 0x8000 else 0
    return ((w1 & 0xFFFF) << 16) + lo

# common-exception vector 0x80000180: lui $k0 @+0xC, lw $k0,LO($k0) @+0x18 -> ExcCode table
exc_tbl = decode_lui_lw(0x8000018C, 0x80000198)
sys_hdl = ida_bytes.get_dword(exc_tbl + 8 * 4)          # ExcCode 8 = SYSCALL
log(f"ExcCode table {exc_tbl:#x}; SYSCALL handler {sys_hdl:#x}")
# interrupt vector 0x80000200: `lui $k0,HI; addu $k0,$at; lw $k0,LO($k0)` -> IP dispatch table
int_tbl = None
for ea in range(0x80000200, 0x80000280, 4):
    w = ida_bytes.get_dword(ea)
    if (w >> 26) == 0x0F and ((w >> 16) & 31) == 26: hi = (w & 0xFFFF) << 16
    if (w >> 26) == 0x23 and ((w >> 16) & 31) == 26 and ((w >> 21) & 31) in (1, 26):   # lw $k0, LO($k0|$at)
        lo = w & 0xFFFF; lo -= 0x10000 if lo & 0x8000 else 0; int_tbl = hi + lo
log(f"interrupt (IP) dispatch table {int_tbl:#x}")
if not existing:
    # the li $sp pseudo-op inside the syscall handler was mis-seeded as a prologue: redo the handler
    for ea in (exc_tbl, int_tbl):
        for k in range(16):
            v = ida_bytes.get_dword(ea + 4 * k)
            if in_code(v):
                f = ida_funcs.get_func(v)
                if f and f.start_ea != v: ida_funcs.del_func(f.start_ea)
                ida_funcs.add_func(v)
    ida_auto.auto_wait()
    f = ida_funcs.get_func(sys_hdl)
    for ea in range(sys_hdl, sys_hdl + 0x100, 4):
        g = ida_funcs.get_func(ea)
        if g and g.start_ea != sys_hdl: ida_funcs.del_func(g.start_ea)
    ida_funcs.del_func(sys_hdl); ida_funcs.add_func(sys_hdl); ida_auto.auto_wait()
    ida_name.set_name(exc_tbl, "kexc_code_table", ida_name.SN_FORCE)
    ida_name.set_name(int_tbl, "kint_ip_table", ida_name.SN_FORCE)
    ida_name.set_name(sys_hdl, "ksyscall_entry", ida_name.SN_FORCE)
# syscall table: `sll $v1,$v1,2; lui $k0,HI; addu $k0,$v1; lw $k0,LO($k0)` in the handler
tbl = None; hi = None; seen_sll = False
for ea in range(sys_hdl, sys_hdl + 0x200, 4):
    w = ida_bytes.get_dword(ea)
    if w == 0x00031880: seen_sll = True                                   # sll $v1, $v1, 2
    if (w >> 26) == 0x0F and ((w >> 16) & 31) == 26: hi = (w & 0xFFFF) << 16   # lui $k0, HI
    if seen_sll and hi is not None and (w >> 26) == 0x23 and ((w >> 16) & 31) == 26 \
            and ((w >> 21) & 31) in (3, 26):                               # lw $k0, LO($k0|$v1)
        lo = w & 0xFFFF; lo -= 0x10000 if lo & 0x8000 else 0; tbl = hi + lo; break
assert tbl, "syscall table load not found in the dispatcher"
NUM_ENTRIES = (exc_tbl - tbl) // 4 if exc_tbl > tbl else 0x100
log(f"ksyscall_table at {tbl:#x}; {NUM_ENTRIES:#x} positive entries up to the ExcCode table")
ida_name.set_name(tbl, "ksyscall_table", ida_name.SN_FORCE)
sc_lines = []; stub = {}
for i in range(NUM_ENTRIES):
    ea = tbl + 4 * i
    ida_bytes.create_dword(ea, 4)
    raw = ida_bytes.get_dword(ea); tgt = k0(raw)
    if i not in ps2_syscalls.POS and i in ps2_syscalls.NEG:      # slot reached by +N and -N alike
        nm, src = ps2_syscalls.name_for(-i)
        src += f" (negative define; slot {i:#x} serves +{i:#x} and -{i:#x})"
    else:
        nm, src = ps2_syscalls.name_for(i)
    if not in_code(raw): sc_lines.append(f"{i:#04x} {raw:#010x} {nm} {src} (not in image)"); continue
    if raw != tgt: src += f" (kseg1 alias {raw:#x})"
    if not ida_funcs.get_func(tgt): ida_funcs.add_func(tgt)
    stub.setdefault(tgt, []).append((i, nm))
    idc.set_cmt(ea, f"{i:#04x} {nm} ({src})", 0)
    sc_lines.append(f"{i:#04x} {tgt:#010x} {nm} {src}")
for tgt, lst in stub.items():
    f = ida_funcs.get_func(tgt)
    if not (f and f.start_ea == tgt): continue
    cur = ida_name.get_name(tgt)
    if cur and not (cur.startswith("sub_") or cur.startswith("ksc_") or cur.startswith("loc_")): continue
    if len(lst) > 4:
        ida_name.set_name(tgt, "ksc_unimplemented_stub", ida_name.SN_FORCE)
    else:
        i, nm = lst[0]
        ida_name.set_name(tgt, f"ksc_{i:02X}_{nm}", ida_name.SN_FORCE)
    if len(lst) > 1:
        ida_bytes.set_cmt(tgt, "syscall numbers: " + ", ".join(f"{i:#04x} {nm}" for i, nm in lst), 1)
# ---- vectors, interrupt-pending dispatch, default exception handler --------------------------
VEC = {0x80000000: "kvec_tlb_refill", 0x80000080: "kvec_perf_counter", 0x80000100: "kvec_debug",
       0x80000180: "kvec_common", 0x80000200: "kvec_interrupt"}
IPN = {2: "kint_ip2_intc", 3: "kint_ip3_dmac", 7: "kint_ip7_cop0_timer"}
for ea, nm in VEC.items():
    cur = ida_name.get_name(ea)
    if not cur or cur.startswith("sub_"): ida_name.set_name(ea, nm, ida_name.SN_FORCE)
for n in range(8):
    v = ida_bytes.get_dword(int_tbl + 4 * n); ida_bytes.create_dword(int_tbl + 4 * n, 4)
    if in_code(v):
        if not ida_funcs.get_func(v): ida_funcs.add_func(v)
        nm = IPN.get(n, f"kint_ip{n}")
        cur = ida_name.get_name(v)
        if not cur or cur.startswith("sub_"): ida_name.set_name(v, nm, ida_name.SN_FORCE)
        idc.set_cmt(int_tbl + 4 * n, f"Cause.IP{n} pending -> {nm}", 0)
exc_cnt = {}
for n in range(14):
    v = ida_bytes.get_dword(exc_tbl + 4 * n); ida_bytes.create_dword(exc_tbl + 4 * n, 4)
    exc_cnt[v] = exc_cnt.get(v, 0) + 1
dflt = max(exc_cnt, key=exc_cnt.get)
if in_code(dflt) and (ida_name.get_name(dflt) or "sub_").startswith("sub_"):
    ida_name.set_name(dflt, "kexc_default_handler", ida_name.SN_FORCE)
ida_name.set_name(exc_tbl + 14 * 4, "kexc_t9_save", ida_name.SN_FORCE)   # sd/ld $t9 slot in both vectors
# ---- leaf functions not reached by jal (computed jumps / pointer tables) -----------------------
leaf = 0
if not existing:
    lim = min(tbl, exc_tbl)
    for ea in range(BASE + 8, lim, 4):
        if ida_bytes.get_dword(ea - 8) != 0x03E00008: continue                  # jr $ra two words back
        if ida_bytes.is_code(ida_bytes.get_flags(ea)) or ida_bytes.get_dword(ea) == 0: continue
        if ida_funcs.get_func(ea): continue
        end = None
        for k in range(ea, min(ea + 0x400, lim), 4):                          # must decode up to a jr $ra
            if ida_ua.decode_insn(ida_ua.insn_t(), k) == 0: break
            if ida_bytes.get_dword(k) == 0x03E00008: end = k + 8; break
        if end and ida_funcs.add_func(ea): leaf += 1
    ida_auto.auto_wait()
# jal targets that landed inside another function (fall-through entries, e.g. 0x80001578 after the
# undefined-syscall stub): truncate the container at the target and make the target a function.
split = 0
if not existing:
    for _ in range(3):
        todo = set()
        for ea in range(BASE, KEND, 4):
            w = ida_bytes.get_dword(ea)
            if (w >> 26) == 3 and ida_bytes.is_code(ida_bytes.get_flags(ea)):
                t = (ea & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                g = ida_funcs.get_func(t)
                if BASE <= t < KEND and not (g and g.start_ea == t): todo.add(t)
        if not todo: break
        for t in sorted(todo):
            g = ida_funcs.get_func(t)
            if g and g.start_ea != t: ida_funcs.set_func_end(g.start_ea, t)
            if not ida_bytes.is_code(ida_bytes.get_flags(t)): ida_auto.auto_make_code(t)
            if ida_funcs.add_func(t): split += 1
        ida_auto.auto_wait()
log(f"jal-target entries split/added: {split}")
# switch idiom IDA's MIPS module does not resolve here: `sltiu $rB, $rI, N` ... `lw $rT, TBL($rS)`
# ... `jr $rT` (TBL folded by IDA from lui/addu). Define the table, mark the case targets as code and
# attach switch_info so the cases join the function body.
import ida_nalt, ida_xref  # noqa: E402
nsw = 0
if not existing:
    for fea in list(idautils.Functions(BASE, KEND)):
        for ea in idautils.FuncItems(fea):
            w = ida_bytes.get_dword(ea)
            if (w & 0xFC1FFFFF) != 0x00000008 or ((w >> 21) & 31) in (31, 26): continue   # jr $rT, not $ra/$k0
            rT = (w >> 21) & 31; tbl_ea = ncase = start = None
            for k in range(1, 7):
                pe = ea - 4 * k; pw = ida_bytes.get_dword(pe)
                if tbl_ea is None:                      # IDA folds lui/addu/lw into one 12-byte `lw` macro
                    insn = ida_ua.insn_t(); ida_ua.decode_insn(insn, pe)
                    t_ = insn.Op2.addr & 0xFFFFFFFF
                    if insn.get_canon_mnem() == "lw" and insn.Op1.reg == rT and insn.Op2.type == ida_ua.o_displ                             and BASE <= t_ < KEND: tbl_ea = t_
                if tbl_ea is not None and (pw >> 26) == 0x0B:                       # sltiu bound
                    ncase = pw & 0xFFFF; start = pe; break
            if not (tbl_ea and ncase): continue
            tg = [ida_bytes.get_dword(tbl_ea + 4 * i) for i in range(ncase)]
            if not all(in_code(t) for t in tg): continue
            for i in range(ncase): ida_bytes.create_dword(tbl_ea + 4 * i, 4)
            for t in set(tg): ida_auto.auto_make_code(t)
            si = ida_nalt.switch_info_t()
            si.set_jtable_element_size(4); si.jumps = tbl_ea; si.ncases = ncase
            si.startea = start; si.lowcase = 0; si.defjump = ida_idaapi.BADADDR
            si.set_expr(rT, ida_ua.dt_dword)
            ida_nalt.set_switch_info(ea, si); ida_xref.create_switch_table(ea, si)
            ida_name.set_name(tbl_ea, f"jtbl_{fea:08X}", ida_name.SN_FORCE | ida_name.SN_NOWARN)
            nsw += 1
    ida_auto.auto_wait()
    for fea in list(idautils.Functions(BASE, KEND)):
        f = ida_funcs.get_func(fea)
        if f: ida_funcs.reanalyze_function(f)
    ida_auto.auto_wait()
log(f"switch tables attached: {nsw}")
for ea, nm in ((0x80001000, "kernel_entry"), (0x80001578, "kSetIntrTrampoline")):
    if (ida_name.get_name(ea) or "sub_").startswith("sub_"): ida_name.set_name(ea, nm, ida_name.SN_FORCE)
# ---- analyst names (docs/ANALYSIS/15_ee_kernel_semantics.md) -------------------------------
# Runtime-installed entry points (stored into the per-cause / per-channel dispatch tables by
# kintr_init_all, never reached by jal): make them function starts first.
RUNTIME_ENTRIES = (0x80001630, 0x80001798, 0x80001D58, 0x80002650)
if not existing:
    for ea in RUNTIME_ENTRIES:
        g = ida_funcs.get_func(ea)
        if g and g.start_ea != ea: ida_funcs.set_func_end(g.start_ea, ea)
        nxt = ida_funcs.get_func(ea + 8)
        if ea == 0x80002650 and nxt and nxt.start_ea == ea + 8: ida_funcs.del_func(ea + 8)
        ida_auto.auto_make_code(ea); ida_funcs.add_func(ea)
    ida_auto.auto_wait()
FN = {
    0x80001300: "kintr_save_gprs", 0x800013C0: "kintr_restore_gprs", 0x80001460: "kclear_gprs",
    0x800014D8: "kintc_cause_unexpected", 0x800015A0: "khandler_node_alloc", 0x800015E8: "khandler_node_free",
    0x80001630: "kintc_dispatch_chain", 0x80001798: "kdmac_dispatch_chain", 0x800018B0: "kintc_add_handler_core",
    0x80001A50: "kAddIntcHandler_kmode", 0x80001B10: "kdmac_add_handler_core", 0x80001C98: "kAddDmacHandler_kmode",
    0x80001D58: "ksbus_dispatch", 0x80002050: "kintr_init_all", 0x800021B0: "kintr_reinit_keep_sbus",
    0x80002650: "kalarm_t3_dispatch", 0x80002840: "kcall_user_handler",
    0x80002A80: "kicache_invalidate_all", 0x80002AC0: "kdcache_wb_invalidate_all", 0x80002B00: "kdcache_invalidate_all",
    0x80003680: "kctx_save_on_thread_stack", 0x80003800: "kctx_restore", 0x80003940: "ksched_preempt_current",
    0x8000394C: "ksched_preempt", 0x80003A78: "ksched_block_current", 0x80003A84: "ksched_block",
    0x80003BB8: "kthread_reset_dormant", 0x80003EF8: "kDeleteThread_core", 0x80003F68: "kStartThread_core",
    0x80003FF0: "kExitThread_core", 0x80004108: "kExitDeleteThread_core", 0x80004650: "kSleepThread_core_cur",
    0x8000465C: "kSleepThread_core", 0x80004CF0: "kWaitSema_core", 0x80004E60: "ksema_init",
    0x80004EC0: "kthread_init", 0x80004FA8: "kthread_copy_args", 0x80005140: "kthread_launch_first",
    0x80005388: "kthread_create_from_rom", 0x800057E0: "kExecPS2_core", 0x800059D8: "ktcb_free",
    0x80005A18: "kready_remove", 0x80005A58: "kready_insert_tail", 0x80005AF8: "klist_pop_head",
    0x80005B38: "klist_rotate_head_to_tail", 0x80005B88: "klist_unlink", 0x80005BA8: "klist_insert_before",
    0x800073E0: "kprintf",
}
DN = {
    0x800010C0: "kexc_save_sp_ra_at", 0x80001100: "kintr_gpr_save_area", 0x80015980: "kintc_cause_dispatch_tbl",
    0x800159C0: "kdmac_chan_dispatch_tbl", 0x80015A64: "g_kIntrTrampoline", 0x80015B6C: "g_kCurrentTid",
    0x80015B70: "g_kTopReadyPrio", 0x80015B74: "g_kNeedResched", 0x80017400: "g_kMachineType",
    0x80017408: "g_kGsIMR", 0x80017410: "g_kMemorySize", 0x80019440: "kstack_top",
    0x80019444: "g_kVSyncFlagPtr", 0x80019448: "g_kVSyncCsrPtr", 0x80019450: "khandler_free_list",
    0x80019458: "kintc_lists", 0x80019510: "kdmac_lists", 0x800195D0: "khandler_nodes",
    0x8001A268: "kalarm_bitmap", 0x8001A270: "kalarm_active", 0x8001A278: "kalarm_slots",
    0x8001A778: "kalarm_order", 0x8001A7C0: "g_kIntrSavedRa", 0x8001A7D0: "g_kIntrSavedSp",
    0x8001A7E0: "kthread_count", 0x8001A7E8: "ktcb_free_list", 0x8001A7F0: "kready_queues",
    0x8001ABF8: "ksema_count", 0x8001ABFC: "ksema_free_head", 0x8001AC00: "ktcb", 0x8001F800: "ksema",
    0x80022B50: "g_kOsdConfigParam",
}
named = 0
for ea, nm in list(FN.items()) + list(DN.items()):
    cur = ida_name.get_name(ea) or ""
    if not cur or cur.startswith(("sub_", "loc_", "dword_", "unk_", "byte_", "off_", "nullsub_")) or cur == nm:
        if ida_name.set_name(ea, nm, ida_name.SN_FORCE | ida_name.SN_NOWARN): named += 1
log(f"analyst names applied: {named}/{len(FN) + len(DN)}")
code = infn = 0
for ea in range(BASE, KEND, 4):
    if ida_bytes.is_code(ida_bytes.get_flags(ea)):
        code += 1; infn += 1 if ida_funcs.get_func(ea) else 0
log(f"leaf functions added: {leaf}; code words {code} (in functions {infn}) of {(KEND-BASE)//4}; "
    f"functions={ida_funcs.get_func_qty()}")
ida_auto.auto_wait()
with open(os.path.join(logdir, "bios_kernel_syscalls.txt"), "w", encoding="utf-8") as fh:
    fh.write(f"# ksyscall_table @ {tbl:#x}, {NUM_ENTRIES} positive entries; ExcCode table {exc_tbl:#x}; IP table {int_tbl:#x}\n")
    fh.write("\n".join(sc_lines) + "\n")
log(f"syscall table named: {NUM_ENTRIES} entries; functions={ida_funcs.get_func_qty()}")

if a.no_save:
    idapro.close_database(False); log("closed without save")
else:
    idapro.close_database(True); log(f"saved {out} size={os.path.getsize(out) if os.path.exists(out) else 'missing'}")
