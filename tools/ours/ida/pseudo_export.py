"""Export Hex-Rays pseudocode for every function of symbols/functions.json into a gitignored reference folder.

Usage (idalib venv python; `import idapro` must be first; run ONE idalib process at a time):
  python -I tools/ours/ida/pseudo_export.py <ida/work_pseudocode.i64> [--root .] [--out <root>/ida/pseudocode]
         [--only @list.txt|0xA,0xB] [--limit N] [--force] [--no-prep] [--no-fold]

What it is: a READ-ONLY reading hint for the Phase 5 readability pass (docs/PHASE5_AGENT_BRIEF.md "The pseudocode
reference"). The pseudocode is derived from the game binary, so the output folder is never committed (`/ida/` is
gitignored). p3fes_handgen's body stays the faithful source of truth; the types and local names below are IDA's
guesses.

Refuses the master (`p3fes.i64`) by name: copy it first (`copy ida\\p3fes.i64 ida\\work_pseudocode.i64`).

Prep (on the copy only, idempotent, saved into the copy; `--no-prep` skips it):
  * `$gp` = 0x7D2CF0 (`.reginfo`, loaded by crt0) as the default of the `gp` segment register on every segment, so
    gp-relative globals resolve (`*(_DWORD *)(v0 - 18952)` becomes `unk_7CE2E8`);
  * every function gets exactly its symbols/functions.json name (the master carries 5,586 withheld community hint
    names, ADR-0009; the pseudocode must show only the names the repo uses), data/label names that the export rule
    withholds are removed (IDA's dummy name shows instead), and every `HINT[...]` comment line is deleted (Hex-Rays
    prints instruction comments inside `__asm` blocks);
  * the assert helpers `sub_19D3F0` / `sub_19D400` (K_Assert / K_Abort, `jr $ra` in retail) get
    `void (const char *file, int line)` / `void (const char *msg, const char *file, int line)` and lose any no-return
    flag: they are normal calls;
  * auto-analysis is disabled and its queue dropped: running it changes the master's layout.
Determinism: nothing the decompiler does is saved. After each function the prototypes Hex-Rays guessed (the
function's, its callees', its globals') are undone, and functions it created (call targets inside data: 12 on
2026-10-21) are deleted again; the callers that make it do that are listed in `<out>/mutators.txt` and decompiled
last, so every other function's text depends only on the prepped copy (an `--only` run equals a full run byte for
byte; two full runs differ in one mutator's file).
Output (`<out>`):
  fn/<addr8>_<name>.c   one file per function: a header (status, size, Hex-Rays warnings, the __asm census,
                        callers / callees / strings / globals from the database) and the pseudocode; for a failed
                        decompilation the header says why and the facts are the whole file
  index.tsv             one row per function (status, reason, counts, key, file) -- what pseudo.py reads
  summary.json          counts by status / failure reason / __asm class, timings
Incremental: a function is re-decompiled only when its key changes: SHA-1 of its chunk ranges and bytes, its name
and type, and the address / name / type of everything it references (callees, data, gp-relative globals), plus the
prep / format versions and the Hex-Rays version, all computed before anything is decompiled. After a master update, copy the master again and re-run: only functions whose
bytes or visible names changed are redone. Resumable: index.tsv is rewritten every 250 functions; an interrupted
run resumes where the keys match.
"""
import idapro  # noqa: F401 -- must be first
import argparse, hashlib, json, os, re, sys, time, collections

PREP_VERSION = "pseudo-prep-2"
FORMAT_VERSION = "pseudo-fmt-3"  # bump when the text written changes: part of every key
GP_VALUE = 0x7D2CF0
GP_SREG_NAME = "gp"
ASSERT_PROTOS = {0x19D3F0: "void __cdecl {n}(const char *file, int line);",
                 0x19D400: "void __cdecl {n}(const char *msg, const char *file, int line);"}

ap = argparse.ArgumentParser()
ap.add_argument("i64")
ap.add_argument("--root", default=".")
ap.add_argument("--out", default=None)
ap.add_argument("--only", default=None, help="@file of hex starts or comma list")
ap.add_argument("--limit", type=int, default=0)
ap.add_argument("--force", action="store_true", help="re-decompile even when the key is unchanged")
ap.add_argument("--no-prep", action="store_true")
ap.add_argument("--no-fold", action="store_true", help="keep the 128-bit register-save __asm blocks verbatim")
A = ap.parse_args()

ROOT = os.path.abspath(A.root)
DB = os.path.abspath(A.i64)
if os.path.basename(DB).lower() == "p3fes.i64":
    sys.exit("refusing the master database: copy ida/p3fes.i64 to ida/work_pseudocode.i64 and pass the copy")
OUT = os.path.abspath(A.out or os.path.join(ROOT, "ida", "pseudocode"))
FN_DIR = os.path.join(OUT, "fn")
os.makedirs(FN_DIR, exist_ok=True)
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
T0 = time.time()
logf = open(os.path.join(OUT, "export.log"), "a", encoding="utf-8")
def log(m):
    s = f"[{time.strftime('%H:%M:%S')} +{time.time()-T0:7.1f}s] {m}"
    print(s, flush=True); logf.write(s + "\n"); logf.flush()

funcs = json.load(open(os.path.join(ROOT, "symbols", "functions.json"), encoding="utf-8"))
FN = {int(f["a"], 16): (f["n"], f["s"]) for f in funcs}

def parse_only(spec):
    if not spec: return None
    if spec.startswith("@"):
        out = []
        for line in open(spec[1:], encoding="utf-8"):
            line = line.split("#", 1)[0].strip()
            if line: out.append(int(line.split()[0], 16))
        return out
    return [int(x, 16) for x in spec.split(",") if x.strip()]

rc = idapro.open_database(DB, False)
if rc != 0: sys.exit(f"open_database rc={rc}")
import ida_hexrays, ida_funcs, ida_name, ida_bytes, ida_segregs, ida_segment, ida_idp, ida_ua, ida_xref
import ida_nalt, ida_typeinf, ida_kernwin, idautils, idc
from import_symbols import withheld_name_map, load_manual_addresses, HINT_LINE_RE

import ida_auto
# Never let auto-analysis run on the copy: the prep (gp, names, prototypes) queues reanalysis, and running that queue
# changes the layout the master has (e.g. it turns the mis-typed code island 0x5D7E7C into a function). Hex-Rays is
# called with DECOMP_NO_WAIT for the same reason.
ida_auto.enable_auto(False)
if not ida_hexrays.init_hexrays_plugin(): sys.exit("Hex-Rays did not initialise")
HX_VER = ida_hexrays.get_hexrays_version()
log(f"db={DB} hexrays={HX_VER} funcs(db)={ida_funcs.get_func_qty()} funcs(json)={len(FN)} out={OUT}")
GP_SREG = next(i for i in range(ida_idp.ph_get_reg_first_sreg(), ida_idp.ph_get_reg_last_sreg() + 1)
               if ida_idp.get_reg_name(i, 4) == GP_SREG_NAME)

# ------------------------------------------------------------------ prep (copy only)
def prep():
    st = collections.Counter()
    for i in range(ida_segment.get_segm_qty()):
        s = ida_segment.getnseg(i)
        if ida_segregs.get_sreg(s.start_ea, GP_SREG) != GP_VALUE:
            ida_segregs.set_default_sreg_value(s, GP_SREG, GP_VALUE); st["gp_segments"] += 1
    manual = load_manual_addresses(os.path.join(ROOT, "tools", "ours", "ida", "names_manual.txt"))
    withheld = withheld_name_map(manual)
    st["withheld_names"] = len(withheld)
    fstarts = set(idautils.Functions())
    # functions: exactly the functions.json name
    for ea, (nm, _sz) in FN.items():
        if ea not in fstarts: st["json_func_missing_in_db"] += 1; continue
        if ida_name.get_name(ea) != nm:
            if ida_name.set_name(ea, nm, ida_name.SN_NOWARN | ida_name.SN_FORCE | ida_name.SN_NOCHECK): st["func_renamed"] += 1
            else: st["func_rename_failed"] += 1
    # withheld data / label names: drop them (IDA's dummy name shows instead)
    for ea, nm in list(idautils.Names()):
        if ea in fstarts: continue
        if nm in withheld:
            if ida_name.set_name(ea, "", ida_name.SN_NOWARN): st["data_name_removed"] += 1
            else: st["data_name_remove_failed"] += 1
    # HINT comment lines (both kinds of comment)
    for ea, _nm in list(idautils.Names()) + [(f, None) for f in fstarts]:
        for rpt in (True, False):
            c = ida_bytes.get_cmt(ea, rpt)
            if c and "HINT[" in c:
                keep = [l for l in c.splitlines() if not HINT_LINE_RE.match(l.strip())]
                ida_bytes.set_cmt(ea, "\n".join(keep), rpt); st["hint_comments_cut"] += 1
        f = ida_funcs.get_func(ea)
        if f is not None and f.start_ea == ea:
            for rpt in (True, False):
                c = ida_funcs.get_func_cmt(f, rpt)
                if c and "HINT[" in c:
                    keep = [l for l in c.splitlines() if not HINT_LINE_RE.match(l.strip())]
                    ida_funcs.set_func_cmt(f, "\n".join(keep), rpt); st["hint_func_comments_cut"] += 1
    # every address that still has a HINT line anywhere (comments at non-named heads)
    for seg_i in range(ida_segment.get_segm_qty()):
        s = ida_segment.getnseg(seg_i)
        ea = s.start_ea
        while ea != idc.BADADDR and ea < s.end_ea:
            for rpt in (True, False):
                c = ida_bytes.get_cmt(ea, rpt)
                if c and "HINT[" in c:
                    keep = [l for l in c.splitlines() if not HINT_LINE_RE.match(l.strip())]
                    ida_bytes.set_cmt(ea, "\n".join(keep), rpt); st["hint_comments_cut"] += 1
            ea = ida_bytes.next_that(ea, s.end_ea, lambda fl: ida_bytes.has_cmt(fl))
    # assert helpers: normal calls with (file, line)
    for ea, proto in ASSERT_PROTOS.items():
        f = ida_funcs.get_func(ea)
        if f is None: continue
        if f.flags & ida_funcs.FUNC_NORET:
            f.flags &= ~ida_funcs.FUNC_NORET; ida_funcs.update_func(f); st["noret_cleared"] += 1
        want = proto.format(n=ida_name.get_name(ea))
        norm = lambda t: re.sub(r"__cdecl|__fastcall|;|\s", "", t)
        if norm(idc.get_type(ea) or "") != norm(want.replace(ida_name.get_name(ea), "")):
            if idc.SetType(ea, want): st["protos_set"] += 1
            else: st["proto_failed"] += 1
    # drop what the edits queued for reanalysis (see enable_auto above): the copy keeps the master's layout
    import ida_ida
    lo, hi = ida_ida.inf_get_min_ea(), ida_ida.inf_get_max_ea()
    for q in [n for n in dir(ida_auto) if n.startswith("AU_") and isinstance(getattr(ida_auto, n), int)]:
        if q in ("AU_NONE",): continue
        ida_auto.auto_unmark(lo, hi, getattr(ida_auto, q))
    st["auto_queue_empty"] = int(ida_auto.auto_is_ok())
    return st, withheld

WITHHELD = {}
if not A.no_prep:
    t = time.time(); st, WITHHELD = prep()
    log(f"prep {PREP_VERSION}: {dict(st)} ({time.time()-t:.1f}s)")
    import ida_loader
    ida_loader.save_database(DB, 0)   # the copy keeps its prep; nothing the decompiler does below is saved
IDENT_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
def scrub(text):
    """Belt and braces: any withheld name that survived (e.g. in a type or a comment) becomes its exported form."""
    if WITHHELD: text = IDENT_RE.sub(lambda m: WITHHELD.get(m.group(0), m.group(0)), text)
    return "\n".join(l for l in text.split("\n") if "HINT[" not in l) if "HINT[" in text else text

# ------------------------------------------------------------------ facts + key
FLOW = {ida_xref.fl_F}
CALLS = {ida_xref.fl_CN, ida_xref.fl_CF}
def chunks_of(ea):
    return sorted((s, e) for s, e in idautils.Chunks(ea))

def strlit(ea):
    fl = ida_bytes.get_flags(ea)
    if not ida_bytes.is_strlit(fl): return None
    b = ida_bytes.get_strlit_contents(ea, -1, ida_nalt.get_str_type(ea))
    if b is None: return None
    try: s = b.decode("cp932", errors="replace")
    except Exception: s = b.decode("latin-1")
    return s if len(s) <= 80 else s[:77] + "..."

def item_name(ea):
    nm = ida_name.get_name(ea)
    if nm: return nm
    h = ida_bytes.get_item_head(ea)
    hn = ida_name.get_name(h)
    return f"{hn}+0x{ea-h:X}" if hn else f"0x{ea:X}"

def facts(fea):
    """Callees, data / gp refs, strings, callers; and the key material."""
    callees = collections.OrderedDict(); data = collections.OrderedDict(); strings = collections.OrderedDict()
    jalr = 0; insns = 0
    ch = chunks_of(fea)
    h = hashlib.sha1()
    h.update(f"{PREP_VERSION}|{FORMAT_VERSION}|{HX_VER}|{fea:x}|{ida_name.get_name(fea)}|{idc.get_type(fea)}|{ch}".encode())
    for s, e in ch:
        h.update(ida_bytes.get_bytes(s, e - s) or b"")
        for hd in idautils.Heads(s, e):
            if not ida_bytes.is_code(ida_bytes.get_flags(hd)): continue
            insns += 1
            for x in idautils.XrefsFrom(hd, 0):
                if x.type in FLOW: continue
                t = x.to
                if any(cs <= t < ce for cs, ce in ch) and x.type not in CALLS: continue  # intra-function jumps
                if x.type in CALLS:
                    callees[t] = item_name(t)
                elif x.iscode:
                    f2 = ida_funcs.get_func(t)
                    if f2 is not None and f2.start_ea == t: callees[t] = item_name(t)  # tail call / jump to a function
                else:
                    sl = strlit(t)
                    if sl is not None: strings[t] = sl
                    else: data[t] = item_name(t)
            insn = ida_ua.insn_t()
            if ida_ua.decode_insn(insn, hd) > 0:
                mn = insn.get_canon_mnem()
                if mn in ("jalr",): jalr += 1
                for op in insn.ops:
                    if op.type == ida_ua.o_void: break
                    if op.type == ida_ua.o_mem:  # $gp-relative, shown resolved (no xref is created without reanalysis)
                        t = op.addr & 0xFFFFFFFF
                        sl = strlit(t)
                        if sl is not None: strings[t] = sl
                        else: data.setdefault(t, item_name(t))
                    elif op.type == ida_ua.o_displ and op.reg == 28:  # $gp-relative, unresolved form
                        off = op.addr if op.addr < 0x80000000 else op.addr - (1 << 32)
                        if off >= 1 << 63: off -= 1 << 64
                        t = (GP_VALUE + off) & 0xFFFFFFFF
                        sl = strlit(t)
                        if sl is not None: strings[t] = sl
                        else: data.setdefault(t, item_name(t))
    mat = [f"|{t:x}:{item_name(t)}:{idc.get_type(t)}" for t in list(callees) + list(data) + list(strings)]
    for m in mat: h.update(m.encode())
    if os.environ.get("PSEUDO_KEYDUMP"):
        os.makedirs(os.path.join(OUT, "keydump"), exist_ok=True)
        open(os.path.join(OUT, "keydump", f"{fea:08x}.txt"), "w", encoding="utf-8").write(
            f"{ida_name.get_name(fea)}|{idc.get_type(fea)}|{ch}\n" + "\n".join(mat) + "\n")
    callers = collections.OrderedDict(); ptr_refs = 0
    for x in idautils.XrefsTo(fea, 0):
        if x.type in FLOW: continue
        f2 = ida_funcs.get_func(x.frm)
        if x.iscode and f2 is not None and f2.start_ea != fea:
            callers[f2.start_ea] = ida_funcs.get_func_name(f2.start_ea)
        elif not x.iscode:
            ptr_refs += 1
    return dict(key=h.hexdigest(), chunks=ch, callees=callees, data=data, strings=strings, callers=callers,
                ptr_refs=ptr_refs, jalr=jalr, insns=insns)

# ------------------------------------------------------------------ __asm census and folding
MMI_RE = re.compile(r"^(p[a-z0-9.]+|qfsrv|mfhi1|mflo1|mthi1|mtlo1|mult1|multu1|div1|divu1|madd1|maddu1|madd|maddu|mtsab|mtsah|mfsa|mtsa)$")
COP2_RE = re.compile(r"^(cop2|lqc2|sqc2|qmfc2|qmtc2|cfc2|ctc2|bc2[ft]l?|v[a-z0-9.]+)$")
FPUACC_RE = re.compile(r"^(adda|suba|mula|madda|msuba|madd|msub)\.s$")
SPILL_RE = re.compile(r"^\s*(sq|lq)\s+\$(s[0-7]|fp|ra|gp|s8),\s*[^,]*\(\$sp\)\s*$")
def asm_class(mn):
    if mn in ("sq", "lq"): return "lq_sq"
    if mn == "syscall": return "syscall"
    if FPUACC_RE.match(mn): return "fpu_acc"
    if COP2_RE.match(mn): return "cop2_vu0"
    if mn in ("mfc0", "mtc0", "sync", "sync.l", "sync.p", "cache", "ei", "di", "eret", "bc0f", "bc0t", "bc0fl", "bc0tl"): return "cop0_sync"
    if MMI_RE.match(mn): return "mmi"
    return "other"

def fold_and_census(text):
    """Census of the mnemonics inside __asm blocks; blocks that only save/restore callee-saved registers with
    128-bit sq/lq to $sp (Metrowerks' prologue/epilogue) are folded into one comment line."""
    lines = text.split("\n"); out = []; census = collections.Counter(); folded = 0; i = 0; others = collections.Counter()
    while i < len(lines):
        ln = lines[i]; st = ln.strip()
        if st.startswith("__asm"):
            indent = ln[:len(ln) - len(ln.lstrip())]
            body = []; j = i
            if "{" in st and "}" in st:  # one-line block: __asm { mnem ops }
                body = [st[st.index("{") + 1:st.rindex("}")].strip()]
            else:
                j = i + 1
                if j < len(lines) and lines[j].strip() == "{": j += 1
                while j < len(lines) and lines[j].strip() != "}":
                    body.append(lines[j].strip()); j += 1
            mns = [b.split()[0] for b in body if b]
            for mn in mns:
                c = asm_class(mn); census[c] += 1
                if c == "other": others[mn] += 1  # e.g. `mfthc1`: an R5900 word IDA decodes as another ISA's op
            if body and all(SPILL_RE.match(b) for b in body):
                census["_saves"] += len(mns)
            if not A.no_fold and body and all(SPILL_RE.match(b) for b in body):
                regs = ",".join(b.split()[1].rstrip(",") for b in body)
                out.append(f"{indent}// __asm: 128-bit {body[0].split()[0]} of {regs} ($sp) -- callee-saved registers")
                folded += 1; i = j + 1; continue
            out.append(ln)
            if j != i:
                out.extend(lines[i + 1:j + 1]); i = j + 1; continue
            i += 1; continue
        out.append(ln); i += 1
    return "\n".join(out), census, folded, others

GUESSED_RE = re.compile(r": using guessed type |^using guessed type ")
MERR = {getattr(ida_hexrays, n): n for n in dir(ida_hexrays) if n.startswith("MERR_") and isinstance(getattr(ida_hexrays, n), int)}

# ------------------------------------------------------------------ index
INDEX = os.path.join(OUT, "index.tsv")
COLS = ["addr", "name", "size", "status", "reason", "lines", "asm_lines", "folded", "jumpout", "warnings",
        "mmi", "cop2_vu0", "syscall", "fpu_acc", "cop0_sync", "lq_sq", "other", "ms", "key", "file"]
old = {}
if os.path.exists(INDEX):
    for ln in open(INDEX, encoding="utf-8"):
        if ln.startswith("addr\t") or not ln.strip(): continue
        r = dict(zip(COLS, ln.rstrip("\n").split("\t")))
        old[int(r["addr"], 16)] = r
def write_index(rows):
    tmp = INDEX + ".tmp"
    with open(tmp, "w", encoding="utf-8", newline="\n") as f:
        f.write("\t".join(COLS) + "\n")
        for ea in sorted(rows):
            r = rows[ea]; f.write("\t".join(str(r.get(c, "")) for c in COLS) + "\n")
    os.replace(tmp, INDEX)

def fmt_list(d, limit=40):
    items = [v if v == f"0x{k:X}" else f"{v} 0x{k:X}" for k, v in d.items()]
    more = len(items) - limit
    return ", ".join(items[:limit]) + (f", ... (+{more})" if more > 0 else "") if items else "-"

def header(ea, nm, sz, fx, status, reason, warnings, census, folded, jumpout, others):
    ch = fx["chunks"]
    L = [f"// {nm} 0x{ea:08X} -- {sz} bytes, {fx['insns']} instructions" + (f", {len(ch)} chunks: " +
         " ".join(f"{s:X}-{e:X}" for s, e in ch) if len(ch) > 1 else ""),
         f"// IDA {HX_VER} Hex-Rays pseudocode: a READ-ONLY hint (gitignored, never committed). Types, locals and",
         "// argument counts are IDA's guesses; p3fes_handgen's body is the faithful source. Check against the binary.",
         f"// status: {status}" + (f" ({reason})" if reason else "")]
    if warnings: L += [f"// hexrays warning: {w}" for w in warnings]
    if census: L.append("// __asm (not lifted): " + ", ".join(f"{k} {v}" for k, v in sorted(census.items())) +
                        (f"; {folded} save/restore blocks folded" if folded else "") +
                        (f"; other = {', '.join(f'{k} x{v}' for k, v in others.most_common())} (IDA's decoding:"
                         " read the handgen body)" if others else ""))
    if jumpout: L.append(f"// JUMPOUT: {jumpout} (control flow the decompiler could not follow: unresolved jr / chunk)")
    L.append(f"// callers ({len(fx['callers'])}" + (f", +{fx['ptr_refs']} data refs" if fx['ptr_refs'] else "") +
             f"): {fmt_list(fx['callers'])}")
    L.append(f"// callees ({len(fx['callees'])}" + (f", {fx['jalr']} jalr" if fx['jalr'] else "") + f"): {fmt_list(fx['callees'])}")
    L.append(f"// globals ({len(fx['data'])}): {fmt_list(fx['data'])}")
    if fx["strings"]:
        L.append(f"// strings ({len(fx['strings'])}): " + "; ".join(f"0x{k:X} {json.dumps(v, ensure_ascii=False)}"
                                                         for k, v in list(fx['strings'].items())[:24]))
    return "\n".join(L) + "\n"

SAFE_RE = re.compile(r"[^A-Za-z0-9_.$@-]")
only = parse_only(A.only)
targets = sorted(only) if only else sorted(FN)
if A.limit: targets = targets[:A.limit]
rows = {ea: r for ea, r in old.items() if ea in FN}
stale = [ea for ea in old if ea not in FN]
for ea in stale:  # functions gone from functions.json
    p = os.path.join(OUT, old[ea].get("file", ""))
    if old[ea].get("file") and os.path.exists(p): os.remove(p)
counts = collections.Counter(); t_dec = 0.0; t_facts = 0.0; done = 0
BASE_FUNCS = set(idautils.Functions()); BASE_QTY = len(BASE_FUNCS); created = []
flags = ida_hexrays.DECOMP_NO_WAIT | ida_hexrays.DECOMP_NO_CACHE
log(f"targets={len(targets)} previously indexed={len(old)} removed={len(stale)}")
# Keys and facts first, all on the prepped state: decompiling can change the database in memory (below), and a key
# computed after such a change would never match the next run's.
t = time.time(); FACTS = {ea: facts(ea) for ea in targets}; t_facts = time.time() - t
# Functions whose decompilation makes Hex-Rays create functions (call targets in data: code copied to the
# scratchpad / kernel patches) go last; del_func undoes the function but not the code items it made, so everything
# decompiled before them sees exactly the prepped copy. The list grows by itself (mutators.txt in the output).
MUT_PATH = os.path.join(OUT, "mutators.txt")
MUTATORS = set()
if os.path.exists(MUT_PATH):
    MUTATORS = {int(l.split()[0], 16) for l in open(MUT_PATH, encoding="utf-8") if l.strip() and not l.startswith("#")}
targets = [ea for ea in targets if ea not in MUTATORS] + [ea for ea in targets if ea in MUTATORS]
for n_i, ea in enumerate(targets):
    nm, sz = FN[ea]
    fx = FACTS[ea]
    prev = rows.get(ea)
    fname = f"fn/{ea:08x}_{SAFE_RE.sub('_', nm)}.c"
    if prev and not A.force and prev.get("key") == fx["key"] and prev.get("file") == fname and os.path.exists(os.path.join(OUT, fname)):
        counts["unchanged"] += 1; continue
    if prev and prev.get("file") and prev["file"] != fname and os.path.exists(os.path.join(OUT, prev["file"])):
        os.remove(os.path.join(OUT, prev["file"]))
    pf = ida_funcs.get_func(ea)
    status, reason, text, warnings, guessed = "ok", "", "", [], 0
    census, folded, jumpout, others = collections.Counter(), 0, 0, collections.Counter()
    t = time.time()
    if pf is None or pf.start_ea != ea:
        status, reason = "fail", "no IDA function at this address"
    else:
        hf = ida_hexrays.hexrays_failure_t()
        # Hex-Rays stores the prototypes it guesses (the function's, its callees', globals' types) in the database;
        # undo that after each function so every function's text depends only on the prepped copy, not on which
        # functions were decompiled before it in this run (incremental runs equal full runs).
        saved_ti = []
        for t_ea in [ea] + list(fx["callees"]) + list(fx["data"]):
            ti = ida_typeinf.tinfo_t()
            saved_ti.append((t_ea, ti if ida_nalt.get_tinfo(ti, t_ea) else None))
        try:
            cf = ida_hexrays.decompile_func(pf, hf, flags)
        except Exception as ex:  # noqa: BLE001
            cf = None; hf.str = f"exception {ex}"
        if cf is None:
            status = "fail"
            code = MERR.get(hf.code, str(hf.code))
            reason = f"{code}: {hf.desc()}" + (f" at 0x{hf.errea:X}" if hf.errea not in (idc.BADADDR, 0) else "")
        else:
            text = str(cf)
            try:
                warnings = [f"0x{w.ea:X}: {w.text}" if w.ea != idc.BADADDR else w.text for w in cf.get_warnings()]
            except Exception:  # noqa: BLE001
                warnings = []
            del cf
        if ida_funcs.get_func_qty() != BASE_QTY:
            # Hex-Rays made functions of call targets that are not functions on the master: remove them again
            for f_ea in set(idautils.Functions()) - BASE_FUNCS:
                created.append((ea, f_ea)); ida_funcs.del_func(f_ea)
        for t_ea, ti in saved_ti:
            now = ida_typeinf.tinfo_t()
            has = ida_nalt.get_tinfo(now, t_ea)
            if ti is None and has: ida_nalt.del_tinfo(t_ea)
            elif ti is not None and (not has or now != ti): ida_nalt.set_tinfo(t_ea, ti)
    dt = time.time() - t; t_dec += dt
    if text:
        text, census, folded, others = fold_and_census(scrub(text))
        jumpout = text.count("JUMPOUT(")
        saves = census.pop("_saves", 0)
        if sum(census.values()) > saves or jumpout: status = "ok_partial"
    guessed = sum(1 for w in warnings if GUESSED_RE.search(w))
    warnings = [scrub(w) for w in warnings if not GUESSED_RE.search(w)]
    if guessed: warnings.append(f"{guessed} 'using guessed type' warnings (callee / global types IDA assumed)")
    reason = scrub(reason.replace("\t", " ").replace("\n", " "))
    body = header(ea, nm, sz, fx, status, reason, warnings, census, folded, jumpout, others)
    body = scrub(body) + "\n" + (text + "\n" if text else "// (no pseudocode: decompilation failed; the facts above are what the database knows)\n")
    with open(os.path.join(OUT, fname), "w", encoding="utf-8", newline="\n") as f: f.write(body)
    asm_lines = sum(census.values())
    rows[ea] = dict(addr=f"{ea:08x}", name=nm, size=sz, status=status, reason=reason, lines=text.count("\n") + 1 if text else 0,
                    asm_lines=asm_lines, folded=folded, jumpout=jumpout, warnings=len(warnings) - (1 if guessed else 0),
                    mmi=census["mmi"], cop2_vu0=census["cop2_vu0"], syscall=census["syscall"], fpu_acc=census["fpu_acc"],
                    cop0_sync=census["cop0_sync"], lq_sq=census["lq_sq"], other=census["other"], ms=int(dt * 1000),
                    key=fx["key"], file=fname)
    counts[status] += 1; done += 1
    if done % 250 == 0:
        write_index(rows); ida_hexrays.clear_cached_cfuncs()
        log(f"  {n_i+1}/{len(targets)} decompiled={done} ({dict(counts)}) dec={t_dec:.0f}s facts={t_facts:.0f}s")
write_index(rows)
if created:
    new_mut = MUTATORS | {e for e, _f in created}
    with open(MUT_PATH, "w", encoding="utf-8", newline="\n") as f:
        f.write("# functions whose decompilation creates functions (decompiled last; pseudo_export.py)\n")
        for e in sorted(new_mut): f.write(f"{e:08x} {FN[e][0]}\n")
    log(f"functions Hex-Rays created (removed again): " + ", ".join(f"0x{f:X} (decompiling 0x{e:X})" for e, f in created))
if ida_funcs.get_func_qty() != len(FN):
    log(f"WARNING: the database has {ida_funcs.get_func_qty()} functions, functions.json {len(FN)}: refresh the copy from the master")
log(f"done: {dict(counts)} decompile {t_dec:.1f}s facts {t_facts:.1f}s total {time.time()-T0:.1f}s")

# ------------------------------------------------------------------ summary over the whole index
allr = list(rows.values())
by_status = collections.Counter(r["status"] for r in allr)
by_reason = collections.Counter(re.sub(r" at 0x[0-9A-F]+$", "", r["reason"]) for r in allr if r["status"] == "fail")
asm_fn = collections.Counter()
for r in allr:
    for c in ("mmi", "cop2_vu0", "syscall", "fpu_acc", "cop0_sync", "lq_sq", "other"):
        if int(r.get(c) or 0): asm_fn[c] += 1
size = sum(os.path.getsize(os.path.join(OUT, r["file"])) for r in allr if r.get("file") and os.path.exists(os.path.join(OUT, r["file"])))
summ = dict(generated=time.strftime("%Y-%m-%d %H:%M:%S"), database=DB, hexrays=HX_VER, prep=PREP_VERSION,
            functions=len(allr), by_status=dict(by_status), fail_reasons=dict(by_reason),
            functions_with_asm_class=dict(asm_fn),
            functions_with_jumpout=sum(1 for r in allr if int(r.get("jumpout") or 0)),
            functions_with_warnings=sum(1 for r in allr if int(r.get("warnings") or 0)),
            folded_blocks=sum(int(r.get("folded") or 0) for r in allr),
            bytes_on_disk=size, this_run=dict(counts=dict(counts), decompile_s=round(t_dec, 1), facts_s=round(t_facts, 1),
                                               total_s=round(time.time() - T0, 1)))
json.dump(summ, open(os.path.join(OUT, "summary.json"), "w", encoding="utf-8"), indent=1)
log(json.dumps(summ))
idapro.close_database(False)   # the prep was saved above; the decompiler's guesses are not
