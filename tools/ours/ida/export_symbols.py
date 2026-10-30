"""Export layout / functions / syscalls / strings / symbols from an existing p3fes IDA database.

Usage (venv python; `import idapro` must be first):
  python export_symbols.py <ida/p3fes.i64> <repo root> [--elf PATH] [--no-save]
                           [--apply-names tools/ours/ida/names_manual.txt] [--no-decompile]

Opens the database WITHOUT re-running auto-analysis. Side effects on the database (saved unless
--no-save): thin syscall wrappers are named `_sce<KernelName>` and manual names are applied.
Writes (regenerating only the text between GENERATED markers so hand-written narrative survives):
  docs/ANALYSIS/00_elf_layout.md, 01_functions_summary.md, 02_syscalls.md,
  03_strings_of_interest.md, 04_decompiler_check.md
  symbols/p3fes.sym, symbols/functions.json
  ida/logs/export.log, ida/logs/strings_all.txt, ida/logs/syscall_sites.txt
"""
import idapro  # noqa  -- must be first
import argparse, os, sys, re, json, struct, time, hashlib, collections

ap = argparse.ArgumentParser()
ap.add_argument("i64"); ap.add_argument("root")
ap.add_argument("--elf", default=None)
ap.add_argument("--no-save", action="store_true")
ap.add_argument("--no-decompile", action="store_true")
ap.add_argument("--apply-names", default=None)
ap.add_argument("--apply-sigs", default=None, help="directory of FLIRT .sig files to apply before export (writes 05_flirt.md)")
A = ap.parse_args()
AUTO_PREFIX = re.compile(r"^(sub_|nullsub_|j_sub_|j_nullsub_|loc_|off_|unk_|byte_|word_|dword_|qword_|xmmword_|asc_|locret_|flt_|dbl_)")
ROOT = os.path.abspath(A.root)
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ps2_syscalls import name_for, pcsx2_name, SOURCE as SYSCALL_SOURCE, HEADER_PATH
from import_symbols import hint_status as shared_hint_status  # ADR-0009 export rule; idapro already imported

AN = os.path.join(ROOT, "docs", "ANALYSIS"); SY = os.path.join(ROOT, "symbols"); LG = os.path.join(ROOT, "ida", "logs")
for d in (AN, SY, LG): os.makedirs(d, exist_ok=True)
logf = open(os.path.join(LG, "export.log"), "a", encoding="utf-8"); T0 = time.time()
def log(m):
    s = f"[{time.strftime('%H:%M:%S')} +{time.time()-T0:6.1f}s] {m}"; print(s, flush=True); logf.write(s+"\n"); logf.flush()
STAMP = time.strftime("%Y-%m-%d %H:%M:%S")
ELF = os.path.abspath(A.elf) if A.elf else os.path.join(ROOT, "extracted", "disc", "SLUS_216.21")
def sha256(p):
    h = hashlib.sha256()
    with open(p, "rb") as f:
        for c in iter(lambda: f.read(1 << 20), b""): h.update(c)
    return h.hexdigest()
ELF_SHA = sha256(ELF) if os.path.exists(ELF) else "unavailable"

BEGIN, END = "<!-- GENERATED:BEGIN (export_symbols.py) -->", "<!-- GENERATED:END -->"
DOC_NAME_FILTER = {}  # withheld hint name -> `sub_<ADDR>`; filled in the names section, applied to every generated doc block
IDENT_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
def write_doc(name, generated, narrative_default):
    if DOC_NAME_FILTER:  # listings, xref columns and decompiler text embed callee names: filter at the output boundary
        generated = IDENT_RE.sub(lambda m: DOC_NAME_FILTER.get(m.group(0), m.group(0)), generated)
    p = os.path.join(AN, name)
    gen = (f"{BEGIN}\n_Generated {STAMP} by `tools/ours/ida/export_symbols.py` from `ida/p3fes.i64` "
           f"(ELF SHA-256 `{ELF_SHA}`). Do not edit inside the markers._\n\n{generated}\n{END}")
    if os.path.exists(p):
        old = open(p, encoding="utf-8").read()
        if BEGIN in old and END in old:
            pre, rest = old.split(BEGIN, 1); _, post = rest.split(END, 1)
            open(p, "w", encoding="utf-8").write(pre + gen + post); return
    open(p, "w", encoding="utf-8").write(narrative_default.rstrip() + "\n\n" + gen + "\n")

idapro.enable_console_messages(False)
rc = idapro.open_database(os.path.abspath(A.i64), False)
log(f"open {A.i64} rc={rc}")
if rc != 0: sys.exit(rc)
import ida_ida, ida_segment, ida_funcs, ida_bytes, ida_name, idc, idautils, ida_hexrays, ida_idaapi

# ---------------------------------------------------------------- manual names
MANUAL = set()  # addresses named by names_manual.txt: analyst authority, so a matching hint counts as verified
def apply_manual_names(path):
    n = 0
    for line in open(path, encoding="utf-8"):
        line = line.split("#", 1)[0].strip()
        if not line: continue
        a, nm = line.split()
        ea = int(a, 16); MANUAL.add(ea)
        if ida_name.get_name(ea) != nm:
            if ida_name.set_name(ea, nm, ida_name.SN_NOWARN | ida_name.SN_FORCE): n += 1
    log(f"manual names applied: {n}")
if A.apply_names: apply_manual_names(A.apply_names)

# ---------------------------------------------------------------- FLIRT signatures (optional, --apply-sigs DIR)
# Order: SDK 3.0.x first, then 2.x, 1.x, then libsn / CodeWarrior, then anything else (alphabetical within a tier).
def sig_tier(name):
    n = name.lower()
    m = re.search(r"(\d)[._]?(\d)[._]?(\d)", n)
    if "libsn" in n or "sn_" in n: return (3, n)
    if "codewarrior" in n or "mw" in n or "metrowerks" in n: return (4, n)
    if m:
        major = int(m.group(1))
        return ({3: 0, 2: 1, 1: 2}.get(major, 5), -int(m.group(1) + m.group(2) + m.group(3)), n)
    return (5, n)
flirt = dict(applied=[], dir=A.apply_sigs, before_named=set(), new_lib=[])
if A.apply_sigs:
    import ida_auto
    sigdir = os.path.abspath(A.apply_sigs)
    sigs = sorted([f for f in os.listdir(sigdir) if f.lower().endswith(".sig")], key=sig_tier) if os.path.isdir(sigdir) else []
    log(f"FLIRT: {len(sigs)} .sig files in {sigdir}")
    flirt["files"] = sigs
    flirt["before_named"] = {fea for fea in idautils.Functions() if not AUTO_PREFIX.match(ida_funcs.get_func_name(fea))}
    for sname in sigs:
        full = os.path.join(sigdir, sname)
        rc_ = ida_funcs.plan_to_apply_idasgn(full)
        ida_auto.auto_wait()
        log(f"FLIRT: applied {sname} rc={rc_}")
    for i in range(ida_funcs.get_idasgn_qty()):
        d = ida_funcs.get_idasgn_desc(i)  # (signame, optlibs) -- or with counts depending on API version
        flirt["applied"].append((i,) + tuple(d) if isinstance(d, (tuple, list)) else (i, d))
    try:
        ida_funcs.get_idasgn_desc_with_matches  # newer API: returns (name, optlibs, nmatches)
        flirt["applied"] = [(i,) + tuple(ida_funcs.get_idasgn_desc_with_matches(i)) for i in range(ida_funcs.get_idasgn_qty())]
    except AttributeError:
        pass
    flirt["new_lib"] = [fea for fea in idautils.Functions()
                        if fea not in flirt["before_named"] and not AUTO_PREFIX.match(ida_funcs.get_func_name(fea))]
    log(f"FLIRT: newly named functions = {len(flirt['new_lib'])}")

# ---------------------------------------------------------------- layout
procname = ida_ida.inf_get_procname(); is_be = ida_ida.inf_is_be()
entry = ida_ida.inf_get_start_ea(); min_ea = ida_ida.inf_get_min_ea(); max_ea = ida_ida.inf_get_max_ea()
segs = []
for i in range(ida_segment.get_segm_qty()):
    s = ida_segment.getnseg(i)
    segs.append(dict(name=ida_segment.get_segm_name(s), start=s.start_ea, end=s.end_ea, size=s.size(), perm=s.perm,
                     cls=ida_segment.get_segm_class(s), bitness=s.bitness))
ph = []; sh = []; elf_hdr = {}
if os.path.exists(ELF):
    d = open(ELF, "rb").read()
    (e_type, e_machine, e_version, e_entry, e_phoff, e_shoff, e_flags, e_ehsize, e_phentsize, e_phnum,
     e_shentsize, e_shnum, e_shstrndx) = struct.unpack_from('<HHIIIIIHHHHHH', d, 16)
    PT = {0: 'NULL', 1: 'LOAD', 2: 'DYNAMIC', 3: 'INTERP', 4: 'NOTE', 6: 'PHDR', 0x70000000: 'MIPS_REGINFO'}
    for i in range(e_phnum):
        t, off, va, pa, fsz, msz, fl, al = struct.unpack_from('<IIIIIIII', d, e_phoff + i * e_phentsize)
        ph.append((i, PT.get(t, hex(t)), off, va, fsz, msz, fl, al))
    if e_shnum:
        hdrs = [struct.unpack_from('<IIIIIIIIII', d, e_shoff + i * e_shentsize) for i in range(e_shnum)]
        st = hdrs[e_shstrndx]
        def nm(o):
            s = d[st[4] + o:]; return s[:s.index(b'\0')].decode('latin1')
        SHT = {0: 'NULL', 1: 'PROGBITS', 2: 'SYMTAB', 3: 'STRTAB', 8: 'NOBITS', 9: 'REL', 0x70000006: 'MIPS_REGINFO'}
        for i, s in enumerate(hdrs): sh.append((i, nm(s[0]), SHT.get(s[1], hex(s[1])), s[2], s[3], s[4], s[5], s[8]))
    comment = None; reginfo = None
    for row in sh:
        if row[1] == ".comment": comment = d[row[5]:row[5] + row[6]].replace(b"\0", b" | ").decode('latin1', 'replace')
        if row[1] == ".reginfo": reginfo = struct.unpack_from('<IIIIII', d, row[5])
    img = d[ph[0][2]:ph[0][2] + ph[0][4]]
    k = len(img)
    while k > 0 and img[k - 1] == 0: k -= 1
    elf_hdr = dict(e_type=e_type, e_machine=e_machine, e_entry=e_entry, e_flags=e_flags, phnum=e_phnum, shnum=e_shnum,
                   symtab=any(r[2] == 'SYMTAB' for r in sh), comment=comment, reginfo=reginfo,
                   zero_tail_start=ph[0][3] + k, size=len(d))

# byte accounting over the whole image
code_b = data_b = unk_b = align_b = 0; orphan_code_b = 0; orphan_items = 0
ea = min_ea
while ea < max_ea:
    fl = ida_bytes.get_flags(ea); sz = ida_bytes.get_item_size(ea)
    if ida_bytes.is_code(fl):
        code_b += sz
        if not ida_funcs.get_func(ea): orphan_code_b += sz; orphan_items += 1
    elif ida_bytes.is_data(fl): data_b += sz
    elif ida_bytes.is_align(fl): align_b += sz
    else: unk_b += sz
    nx = ida_bytes.next_head(ea, max_ea)
    ea = nx if nx != ida_idaapi.BADADDR else max_ea
log(f"bytes code={code_b:#x} data={data_b:#x} unk={unk_b:#x} align={align_b:#x} orphan_code={orphan_code_b:#x}/{orphan_items}")

# ---------------------------------------------------------------- functions
funcs = []
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    chunk_list = list(idautils.Chunks(fea))  # main chunk + tails
    total = sum(e - s for s, e in chunk_list); chunks = len(chunk_list)
    funcs.append(dict(ea=fea, size=f.end_ea - f.start_ea, total=total, chunks=chunks, name=ida_funcs.get_func_name(fea)))
nfunc = len(funcs)
AUTO_RE = AUTO_PREFIX
def is_auto_name(n): return bool(AUTO_RE.match(n))
n_auto = sum(1 for f in funcs if is_auto_name(f["name"])); n_nullsub = sum(1 for f in funcs if f["name"].startswith("nullsub_"))
n_chunked = sum(1 for f in funcs if f["chunks"] > 1)
buckets = [(0, 16), (16, 64), (64, 256), (256, 1024), (1024, 4096), (4096, 16384), (16384, 1 << 30)]
hist = collections.Counter()
for f in funcs:
    for lo, hi in buckets:
        if lo <= f["total"] < hi: hist[(lo, hi)] += 1; break
largest = sorted(funcs, key=lambda f: -f["total"])[:30]
func_code_bytes = sum(f["total"] for f in funcs)
funcs_outside_main = [f for f in funcs if not (segs[0]["start"] <= f["ea"] < segs[0]["end"])]

# ---------------------------------------------------------------- syscalls
seg0 = ida_segment.getnseg(0)
blob = ida_bytes.get_bytes(seg0.start_ea, seg0.size())
words = struct.unpack_from(f"<{len(blob)//4}I", blob)
def w_at(ea): return words[(ea - seg0.start_ea) // 4]
def li_v1(w):
    """Return the immediate if w is addiu/daddiu/ori $v1,$zero,imm else None."""
    op = w & 0xFFFF0000
    if op in (0x24030000, 0x64030000):
        imm = w & 0xFFFF; return imm - 0x10000 if imm & 0x8000 else imm
    if op == 0x34030000: return w & 0xFFFF
    return None
sites = []; junk_sites = []
for i, w in enumerate(words):
    if (w & 0xFC00003F) != 0x0000000C: continue
    ea = seg0.start_ea + 4 * i
    if not ida_bytes.is_code(ida_bytes.get_flags(ea)): continue
    f = ida_funcs.get_func(ea)
    num = None
    for back in range(1, 7):  # nearest preceding li $v1 within 6 instructions
        n = li_v1(words[i - back])
        if n is not None: num = n; break
    if f is None and num is None: junk_sites.append(ea); continue
    sites.append(dict(ea=ea, num=num, func=f))
wrapper_count = 0; renamed = 0; table = []
WRAP_SHAPES = {("li", "sc", "jr", "nop"), ("li", "sc", "nop", "nop"), ("li", "jr", "sc", "nop")}
def shape(ws):
    out = []
    for x in ws:
        out.append("li" if li_v1(x) is not None else "sc" if (x & 0xFC00003F) == 0xC else
                   "jr" if x == 0x03E00008 else "nop" if x == 0 else "?")
    return tuple(out)
def eff_name(num):
    return name_for(num)  # (name, source) -- sign handling lives in ps2_syscalls
for s in sites:
    f = s["func"]; num = s["num"]
    kname, conf = eff_name(num) if num is not None else ("unknown_syscall_??", "-")
    neg = num is not None and num < 0
    wrap = False
    if f is not None and (f.end_ea - f.start_ea) == 16 and f.start_ea in (s["ea"] - 4, s["ea"] - 8):
        wrap = shape([w_at(f.start_ea + 4 * k) for k in range(4)]) in WRAP_SHAPES
    if wrap and num is not None:
        wrapper_count += 1
        # `_sce<Name>`; header names that already carry the sce prefix (sceSifSetDma / isceSifSetDma) get only `_`
        want = ("_" + kname) if kname.lstrip("i").startswith("sce") else f"_sce{kname}"
        cur = ida_funcs.get_func_name(f.start_ea)
        # rename IDA auto names and names this tool assigned earlier (idempotent, self-correcting); never touch other user names
        if is_auto_name(cur) or (cur.startswith(("_sce", "_isce")) and re.sub(r"_\d+$", "", cur) != want):
            if ida_name.force_name(f.start_ea, want, ida_name.SN_NOWARN): renamed += 1
    table.append(dict(ea=s["ea"], num=num, abs=abs(num) if num is not None else None, neg=neg, kname=kname, conf=conf,
                      func=ida_funcs.get_func_name(f.start_ea) if f else "-", fstart=f.start_ea if f else None, wrap=wrap))
log(f"syscall sites={len(sites)} wrappers={wrapper_count} renamed={renamed} junk_code_outside_funcs={len(junk_sites)}")
with open(os.path.join(LG, "syscall_sites.txt"), "w") as fh:
    for t in table: fh.write(f"{t['ea']:#010x} num={t['num']} {t['kname']} func={t['func']} wrap={t['wrap']}\n")
    fh.write("\njunk (code-flagged syscall opcodes outside functions, no li $v1 nearby):\n" + "\n".join(f"{e:#010x}" for e in junk_sites))

# ---------------------------------------------------------------- MMI / COP2 census (raw opcode scan over function bodies)
mmi_per_func = collections.Counter(); lqsq = 0; cop2 = 0; mmi = 0
for f in funcs:
    s_, e_ = f["ea"], f["ea"] + f["size"]
    if s_ < seg0.start_ea or e_ > seg0.end_ea: continue
    c = 0
    for k in range((s_ - seg0.start_ea) // 4, (e_ - seg0.start_ea) // 4):
        op = words[k] >> 26
        if op == 0x1C: c += 1; mmi += 1
        elif op in (0x1E, 0x1F): lqsq += 1
        elif op == 0x12: cop2 += 1
    if c: mmi_per_func[f["ea"]] = c
log(f"MMI insns={mmi} in {len(mmi_per_func)} funcs; lq/sq={lqsq}; COP2={cop2}")

# ---------------------------------------------------------------- names -> symbols
# re-read names after renaming
for f in funcs: f["name"] = ida_funcs.get_func_name(f["ea"])
# Community hints (ADR-0009): a name placed by hints_import.py / import_symbols.py is recognised by its repeatable
# comment line `HINT[<source>] <name>[ verified]`. Unless the source is permissively licensed (PERMISSIVE_SOURCES),
# the line says `verified`, or names_manual.txt owns the address, the name is WITHHELD from every committed
# output (sym, functions.json, docs): the function is exported under its IDA auto form `sub_<ADDR>`, D/L rows are
# dropped, and the real rows go to ida/logs/export_hints_withheld.txt (gitignored). Done once here so every consumer
# below sees the sanitised name.
def hint_status(ea, name): return shared_hint_status(ea, name, MANUAL)
hint_tag = {}; withheld = []
for f in funcs:
    hs = hint_status(f["ea"], f["name"])
    if hs is None: continue
    src, ok = hs
    if ok: hint_tag[f["ea"]] = f"source={src}"
    else:
        withheld.append((f["ea"], f["total"], "F", f["name"], src))
        DOC_NAME_FILTER[f["name"]] = f["name"] = f"sub_{f['ea']:X}"
for t in table: t["func"] = DOC_NAME_FILTER.get(t["func"], t["func"])  # syscall-site table was built before sanitising
flirt_set = set(flirt["new_lib"])
def is_flirt(ea):
    # `flirt` <=> IDA's FUNC_LIB (set by a signature match; also anything newly named by this run's --apply-sigs).
    # The tag does not depend on the name: a FUNC_LIB function whose name flirt_audit.py stripped (auto name) or
    # whose name is a withheld hint (exported as sub_<EA>) carries it too, so import_symbols.py can restore the
    # flag from the text and a re-export reproduces the row (tools/ours/ida/README.md "Round trip").
    fn = ida_funcs.get_func(ea)
    return ea in flirt_set or bool(fn and (fn.flags & ida_funcs.FUNC_LIB))
def tags_for(ea):
    t = []
    if is_flirt(ea): t.append("flirt")
    if ea in hint_tag: t.append(hint_tag[ea])
    return (" " + " ".join(t)) if t else ""
sym = [(f["ea"], f["total"], "F", f["name"] + tags_for(f["ea"])) for f in funcs]
n_flirt_funcs = sum(1 for f in funcs if is_flirt(f["ea"]))
fstarts = {f["ea"] for f in funcs}
n_data_names = n_labels = 0
for ea, nm in idautils.Names():
    if ea in fstarts: continue
    fl = ida_bytes.get_flags(ea)
    # keep only user-assigned names: IDA's auto names (strings aXxx, jpt_, def_, off_, ...) are excluded by flag and by pattern
    if is_auto_name(nm) or ida_bytes.has_dummy_name(fl) or ida_bytes.has_auto_name(fl) or re.match(r"^(jpt_|def_)", nm): continue
    kind, size = ("L", 0) if ida_bytes.is_code(fl) else ("D", ida_bytes.get_item_size(ea))
    hs = hint_status(ea, nm)
    if hs is not None and not hs[1]:
        withheld.append((ea, size, kind, nm, hs[0])); DOC_NAME_FILTER[nm] = f"{'loc' if kind == 'L' else 'data'}_{ea:X}"; continue
    tag = f" source={hs[0]}" if hs is not None else ""
    sym.append((ea, size, kind, nm + tag))
    if kind == "L": n_labels += 1
    else: n_data_names += 1
sym.sort()
with open(os.path.join(LG, "export_hints_withheld.txt"), "w", encoding="utf-8", newline="\n") as fh:
    fh.write("# names present in the DB but withheld from symbols/ and docs/ (unverified, non-permissive hints; ADR-0009)\n")
    for ea, sz, k, nm, src in sorted(withheld): fh.write(f"{ea:08x} {sz:08x} {k} {nm} source={src}\n")
log(f"hint names: exported with source tag={len(hint_tag)} withheld (unverified community hints)={len(withheld)}")
with open(os.path.join(SY, "p3fes.sym"), "w", encoding="utf-8", newline="\n") as fh:
    fh.write(f"# p3fes.sym  SLUS_216.21 (Persona 3 FES NTSC-U)  ELF SHA-256 {ELF_SHA}\n")
    fh.write(f"# generated {STAMP} by tools/ours/ida/export_symbols.py from ida/p3fes.i64 (processor {procname})\n")
    fh.write("# <addr8> <size8> <F|D|L> <name> [flirt] [source=<src>]   F=function (all, incl. auto sub_), D=named data item, L=named code label;\n"
             "#   optional tags: `flirt` = name derived from a FLIRT signature match (IDA FUNC_LIB), not from analysis evidence;\n"
             "#   `source=<src>` = name adopted from a community source (ADR-0009: permissive license, or verified and promoted)\n")
    for ea, sz, k, nm in sym: fh.write(f"{ea:08x} {sz:08x} {k} {nm}\n")
with open(os.path.join(SY, "functions.json"), "w", encoding="utf-8", newline="\n") as fh:
    fh.write(json.dumps([{"a": f"0x{f['ea']:x}", "s": f["total"], "n": f["name"]}
                         for f in sorted(funcs, key=lambda f: f["ea"])], separators=(",", ":")))
log(f"symbols: F={nfunc} D={n_data_names} L={n_labels}")

# ---------------------------------------------------------------- strings
strs = list(idautils.Strings())
log(f"strings={len(strs)}")
def refs_of(ea, limit=2):
    out = []
    for x in idautils.XrefsTo(ea):
        f = ida_funcs.get_func(x.frm)
        out.append(f"{x.frm:#x}" + (f" ({ida_funcs.get_func_name(f.start_ea)})" if f else ""))
        if len(out) >= limit: break
    return out
CATS = [
    ("Source paths (`*.c/*.cpp/*.h/*.s`)", re.compile(r"\.(c|cpp|cc|cxx|h|hpp|s|asm)(\b|$)", re.I), None),
    ("Assertion / debug format strings mentioning file or line", re.compile(r"(line|File|%s.*%d|%d.*%s|assert|Assert|ASSERT)"), re.compile(r"%")),
    ("SCE SDK / Sony library identifiers (`sce`, `SCE`)", re.compile(r"(sce[A-Z_]|^sce|SCE|Sce)"), None),
    ("Library / module names (`lib`, `.IRX`)", re.compile(r"(\blib|lib[a-z]|\.irx)", re.I), None),
    ("Device / path prefixes (`cdrom0:`, `host0:`, `mc0:`, `rom0:`)", re.compile(r"(cdrom0?:|host0?:|mc[01]:|rom0:|hdd0:|pfs0:|mass:)"), None),
    ("Atlus asset extensions (.CVM .PAC .BF .BMD .TMX .PM1 .AMD .ADX ...)",
     re.compile(r"\.(cvm|pac|bf|bmd|tmx|pm1|pm2|amd|adx|ahx|afs|spd|tb|pak|bin|arc|epl|gmd|pb|rmd|tbl|fbn|fnt|sfd|gfs|acx|csv|dat|img|txt)(\b|$)", re.I), None),
    ("Version / SDK / compiler banners", re.compile(r"(Version|Ver\.|SDK|GCC|Copyright|Compiler|CodeWarrior|Metrowerks|ProDG|SN Systems|CRI|Build:|lib[a-z]+ +[0-9]{4}|[0-9]+\.[0-9]+\.[0-9]+)"), None),
]
cat_hits = collections.OrderedDict((c[0], []) for c in CATS)
fmt_count = 0
with open(os.path.join(LG, "strings_all.txt"), "w", encoding="utf-8") as fh:
    for s in strs:
        txt = str(s)
        fh.write(f"{s.ea:#010x} {s.length} {txt!r}\n")
        if "%" in txt: fmt_count += 1
        for title, rx, rx2 in CATS:
            if rx.search(txt) and (rx2 is None or rx2.search(txt)):
                cat_hits[title].append((s.ea, txt))
log("strings categorised: " + ", ".join(f"{k.split(' ')[0]}={len(v)}" for k, v in cat_hits.items()))

# ---------------------------------------------------------------- decompiler check
dec_results = []; hx_ok = None
if not A.no_decompile:
    hx_ok = ida_hexrays.init_hexrays_plugin()
    log(f"hexrays init={hx_ok}")
    targets = [("crt0 / `start`", ida_funcs.get_func(entry).start_ea)]
    leaf = None
    for f in sorted(funcs, key=lambda f: f["total"]):
        if 48 <= f["total"] <= 96 and f["chunks"] == 1 and not f["name"].startswith("nullsub") and mmi_per_func.get(f["ea"], 0) == 0:
            ws = [w_at(f["ea"] + 4 * k) for k in range(f["total"] // 4)]
            if not any(((w >> 26) == 3) or ((w & 0xFC00003F) == 0x09) for w in ws):  # no jal / jalr
                leaf = f; break
    if leaf: targets.append(("small leaf function", leaf["ea"]))
    mmi_choice = None
    for fea, c in mmi_per_func.most_common():
        f = next(x for x in funcs if x["ea"] == fea)
        if 64 <= f["total"] <= 1200: mmi_choice = (fea, c, f); break
    if mmi_choice: targets.append((f"MMI-heavy function ({mmi_choice[1]} MMI opcodes, {mmi_choice[2]['total']} bytes)", mmi_choice[0]))
    for title, fea in targets:
        if not hx_ok: dec_results.append((title, fea, "hexrays plugin failed to initialise", "")); continue
        try:
            cf = ida_hexrays.decompile(fea)
            txt = str(cf); lines = txt.splitlines()
            n_asm = sum(1 for l in lines if "__asm" in l)
            dec_results.append((title, fea, f"OK: {len(lines)} lines, {n_asm} lines containing `__asm`",
                                "\n".join(lines[:110]) + ("\n... [truncated]" if len(lines) > 110 else "")))
        except Exception as e:
            dec_results.append((title, fea, f"FAILED: {e!r}", ""))
        log(f"decompile {title} {fea:#x}: {dec_results[-1][2]}")

# ---------------------------------------------------------------- listings
def listing(ea, n):
    out = []
    for _ in range(n):
        out.append(f"{ea:08x}  {idc.GetDisasm(ea)}"); ea = idc.next_head(ea)
    return "\n".join(out)
entry_f = ida_funcs.get_func(entry)

# ================================================================ docs
def hx(v): return f"`0x{v:08x}`"
g = ["| Item | Value (observed in IDA) |", "|---|---|"]
g.append(f"| Processor module | `{procname}` (IDA `inf_get_procname`) |")
g.append(f"| Endianness | {'big' if is_be else 'little'} (`inf_is_be`={is_be}) |")
g.append(f"| Entry point | {hx(entry)} (`inf_get_start_ea`; ELF `e_entry`={elf_hdr.get('e_entry', 0):#x}) |")
g.append(f"| Image range | {hx(min_ea)} .. {hx(max_ea)} (`inf_get_min_ea`/`max_ea`) |")
g.append(f"| Image base / first PT_LOAD vaddr | {hx(segs[0]['start'])} |")
g.append(f"| ELF type / machine / flags | {elf_hdr.get('e_type')} (ET_EXEC) / {elf_hdr.get('e_machine')} (EM_MIPS) / {elf_hdr.get('e_flags', 0):#x} |")
g.append(f"| ELF file size | {elf_hdr.get('size')} bytes |")
g.append(f"| `.comment` | `{elf_hdr.get('comment')}` |")
ri = elf_hdr.get('reginfo')
if ri: g.append(f"| `.reginfo` | gprmask={ri[0]:#x} cprmask=[{', '.join(hex(x) for x in ri[1:5])}] **gp={ri[5]:#x}** |")
g.append(f"| `.symtab` present | {elf_hdr.get('symtab')} ({'symbols present' if elf_hdr.get('symtab') else 'fully stripped, no ELF symbols'}) |")
g.append("\n### IDA segments (`ida_segment`)\n\n| Name | Start | End | Size | Perm | Class | Bitness |\n|---|---|---|---|---|---|---|")
for s in segs:
    perm = "".join(c if s['perm'] & b else "-" for c, b in (("r", 4), ("w", 2), ("x", 1)))
    g.append(f"| `{s['name']}` | {hx(s['start'])} | {hx(s['end'])} | {s['size']:#x} ({s['size']/1048576:.2f} MiB) | {perm} | {s['cls']} | {16 << s['bitness']} |")
g.append("\n### ELF program headers (raw file parse)\n\n| # | Type | Offset | Vaddr | Filesz | Memsz | Flags | Align |\n|---|---|---|---|---|---|---|---|")
for r in ph: g.append(f"| {r[0]} | {r[1]} | {r[2]:#x} | {r[3]:#010x} | {r[4]:#x} | {r[5]:#x} | {r[6]:#x} | {r[7]:#x} |")
g.append("\n### ELF section headers (raw file parse)\n\n| # | Name | Type | Flags | Addr | Offset | Size | Align |\n|---|---|---|---|---|---|---|---|")
for r in sh: g.append(f"| {r[0]} | `{r[1]}` | {r[2]} | {r[3]:#x} | {r[4]:#010x} | {r[5]:#x} | {r[6]:#x} | {r[7]} |")
g.append(f"\n### Byte accounting over {hx(min_ea)}..{hx(max_ea)} (IDA item flags)\n\n| Kind | Bytes | MiB |\n|---|---|---|")
for k, v in (("code (is_code)", code_b), ("  of which code outside any function", orphan_code_b), ("data (is_data)", data_b),
             ("align", align_b), ("unknown/unexplored", unk_b)):
    g.append(f"| {k} | {v:#x} | {v/1048576:.2f} |")
g.append(f"| sum of function sizes (all chunks) | {func_code_bytes:#x} | {func_code_bytes/1048576:.2f} |")
if elf_hdr:
    zt = elf_hdr['zero_tail_start']; ze = ph[0][3] + ph[0][5]
    g.append(f"\nZero-initialised tail: every byte from {hx(zt)} to {hx(ze)} is zero in the file ({ze-zt:#x} bytes = {(ze-zt)/1048576:.2f} MiB); "
             f"PT_LOAD[0] has filesz == memsz, so `.bss` was emitted as file bytes rather than NOBITS.")
g.append(f"\nFunctions outside the first segment (`{segs[0]['name']}`): {len(funcs_outside_main)}. Code items outside any function: {orphan_items} items / {orphan_code_b:#x} bytes.")
write_doc("00_elf_layout.md", "\n".join(g), "# 00 — ELF layout as IDA sees it\n\n_Narrative (hand-written, outside the generated block) follows the tables._")

g = ["| Metric | Value |", "|---|---|"]
g.append(f"| Functions (IDA `Functions()`) | {nfunc} |")
g.append(f"| ... with auto names (`sub_`/`nullsub_`/`j_`) | {n_auto} |")
g.append(f"| ... with non-auto names | {nfunc - n_auto} |")
g.append(f"| ... `nullsub_*` (empty `jr $ra`) | {n_nullsub} |")
g.append(f"| ... multi-chunk functions | {n_chunked} |")
g.append(f"| Total function bytes | {func_code_bytes:#x} ({func_code_bytes/1048576:.2f} MiB) |")
g.append(f"| ELF symbols (`.symtab`) | {'present' if elf_hdr.get('symtab') else 'none — stripped'} |")
g.append(f"| MMI (opcode 0x1C) instructions / functions containing them | {mmi} / {len(mmi_per_func)} |")
g.append(f"| `lq`/`sq` instructions | {lqsq} |")
g.append(f"| COP2 (VU0 macro) instructions | {cop2} |")
g.append("\n### Size histogram (bytes, all chunks)\n\n| Range | Count |\n|---|---|")
for lo, hi in buckets: g.append(f"| {lo} – {hi if hi < (1<<30) else 'inf'} | {hist[(lo, hi)]} |")
g.append("\n### 30 largest functions\n\n| Address | Size | Chunks | Name |\n|---|---|---|---|")
for f in largest: g.append(f"| {hx(f['ea'])} | {f['total']:#x} ({f['total']}) | {f['chunks']} | `{f['name']}` |")
g.append("\n### Top MMI-using functions (raw opcode census)\n\n| Address | Name | Size | MMI ops |\n|---|---|---|---|")
for fea, c in mmi_per_func.most_common(15):
    f = next(x for x in funcs if x["ea"] == fea); g.append(f"| {hx(fea)} | `{f['name']}` | {f['total']:#x} | {c} |")
g.append(f"\n### Entry function listing (`{ida_funcs.get_func_name(entry)}` {hx(entry_f.start_ea)}..{hx(entry_f.end_ea)}), tail from `0x100198`\n\n```")
g.append(listing(0x100198, 34)); g.append("```")
g.append(f"\n### `{ida_funcs.get_func_name(0x193980)}` at `0x00193980`\n\n```"); g.append(listing(0x193980, 12)); g.append("```")
g.append(f"\n### `{ida_funcs.get_func_name(0x1984C0)}` at `0x001984C0` (called from `sub_1939B0`)\n\n```"); g.append(listing(0x1984C0, 32)); g.append("```")
write_doc("01_functions_summary.md", "\n".join(g), "# 01 — Functions summary\n\n_Narrative (entry chain, `main` evidence) is hand-written below the generated block._")

g = []
cnt = collections.Counter((t["abs"], t["neg"]) for t in table)
g.append(f"Syscall sites (code `syscall` opcode with a `li $v1,N` within 6 preceding instructions, or inside a function): **{len(table)}**. "
         f"Thin wrappers (`li $v1,N ; syscall ; jr $ra ; nop` or `li ; syscall ; nop ; nop`, exactly 16 bytes): **{wrapper_count}**, renamed this run: {renamed}. "
         f"Code-flagged `syscall` opcodes outside any function with no `li $v1` (mis-disassembled data): {len(junk_sites)} (listed in `ida/logs/syscall_sites.txt`).")
g.append(f"\nName authority: {SYSCALL_SOURCE}. Source column: `ps2sdk` = exact `__NR_` define incl. sign; `ps2sdk+i` = positive define exists, "
         f"negative form inferred as its interrupt-context variant; `pcsx2` = fallback table only. Sites using the negative form: {sum(1 for t in table if t['neg'])}.")
g.append("\n### Distinct syscall numbers used\n\n| N (hex) | neg form | Kernel name | Source | PCSX2/ps2tek name if different | Sites |\n|---|---|---|---|---|---|")
for (n, neg), c in sorted(cnt.items(), key=lambda kv: (kv[0][0] if kv[0][0] is not None else 999, kv[0][1])):
    nm, conf = eff_name(-n if neg else n) if n is not None else ("?", "-")
    alt = pcsx2_name(n) if n is not None else None
    diff = "" if alt is None or alt == nm or alt.endswith("_" + nm.lstrip("i")) or alt.lstrip("_") == nm.lstrip("_i") else f"`{alt}`"
    g.append(f"| {n:#04x} | {'yes' if neg else ''} | `{nm}` | {conf} | {diff} | {c} |")
g.append("\n### All sites\n\n| Site | Function | N | Kernel name | Source | Thin wrapper |\n|---|---|---|---|---|---|")
for t in sorted(table, key=lambda t: t["ea"]):
    nstr = "?" if t['num'] is None else (f"{t['num']:#x}" if t['num'] >= 0 else f"-{-t['num']:#x}")
    g.append(f"| {hx(t['ea'])} | `{t['func']}`{(' @ ' + hx(t['fstart'])) if t['fstart'] is not None else ''} | {nstr} | `{t['kname']}` | {t['conf']} | {'yes' if t['wrap'] else ''} |")
write_doc("02_syscalls.md", "\n".join(g), "# 02 — EE kernel syscall sites\n\n_Narrative (table provenance, naming pattern, empirical checks) is hand-written below the generated block._")

g = [f"Total strings in IDA string list: {len(strs)}; strings containing `%`: {fmt_count}. Full list: `ida/logs/strings_all.txt` (gitignored)."]
CAP = 400
for title, hits in cat_hits.items():
    g.append(f"\n### {title} — {len(hits)} hits{' (first %d shown)' % CAP if len(hits) > CAP else ''}\n\n| Address | String | Referenced from |\n|---|---|---|")
    for ea, txt in hits[:CAP]:
        t = txt.replace("|", "\\|").replace("`", "'").replace("\n", "\\n").replace("\r", "\\r")
        if len(t) > 100: t = t[:100] + "..."
        g.append(f"| {hx(ea)} | `{t}` | {', '.join(refs_of(ea)) or '-'} |")
write_doc("03_strings_of_interest.md", "\n".join(g), "# 03 — Strings of interest\n\n_Narrative is hand-written below the generated block._")

g = [f"`ida_hexrays.init_hexrays_plugin()` -> **{hx_ok if not A.no_decompile else 'skipped'}** with processor `{procname}`."]
for title, fea, status, txt in dec_results:
    g.append(f"\n### {title} — `{ida_funcs.get_func_name(fea)}` {hx(fea)}\n\nResult: {status}\n")
    if txt: g.append("```c\n" + txt + "\n```")
write_doc("04_decompiler_check.md", "\n".join(g), "# 04 — Hex-Rays MIPS decompiler on R5900 code\n\n_Verdict (hand-written) below the generated block._")

if A.apply_sigs:
    g = [f"Signature directory: `{flirt['dir']}`; files applied this run (in order): " + ", ".join(f"`{s}`" for s in flirt.get("files", [])) + "."]
    g.append("\n### Signatures known to the database (`ida_funcs.get_idasgn_qty/get_idasgn_desc`)\n\n| # | Signature | Declared library | Matches |\n|---|---|---|---|")
    for row in flirt["applied"]:
        i = row[0]; name = row[1] if len(row) > 1 else "?"; lib = row[2] if len(row) > 2 else ""; nm = row[3] if len(row) > 3 else "n/a (API without counts)"
        g.append(f"| {i} | `{name}` | {lib} | {nm} |")
    g.append(f"\nFunctions newly named by this run's signature pass: **{len(flirt['new_lib'])}**; functions carrying FUNC_LIB (any run): **{n_flirt_funcs}**. "
             "These names are *derived* and tagged `flirt` in `symbols/p3fes.sym`; manual names (`names_manual.txt`) were applied before the signatures and win on conflict.")
    # spot check: FLIRT-named functions that contain a syscall or reference a string
    g.append("\n### Spot check (first 12 FLIRT-named functions with independent evidence)\n\n| Address | FLIRT name | Evidence |\n|---|---|---|")
    shown = 0
    sysc_by_func = collections.defaultdict(list)
    for t in table:
        if t["fstart"] is not None: sysc_by_func[t["fstart"]].append(t["kname"])
    for fea in sorted(flirt_set):
        ev = []
        if fea in sysc_by_func: ev.append("syscall(s): " + ", ".join(f"`{k}`" for k in sysc_by_func[fea][:3]))
        for ea_ in idautils.FuncItems(fea):
            for x in idautils.DataRefsFrom(ea_):
                s_ = idc.get_strlit_contents(x)
                if s_: ev.append(f"string {x:#x} `{s_[:60].decode('latin1', 'replace').replace(chr(10), ' ').replace(chr(13), ' ').replace('|', '/')}`"); break
            if len(ev) >= 2: break
        if ev:
            g.append(f"| {hx(fea)} | `{ida_funcs.get_func_name(fea)}` | {'; '.join(ev)} |"); shown += 1
        if shown >= 12: break
    if shown == 0: g.append("| — | — | no FLIRT-named function with a syscall or string reference found |")
    write_doc("05_flirt.md", "\n".join(g), "# 05 — FLIRT signature pass\n\n_Narrative (which packs, verdict on match quality) is hand-written below the generated block._")

log("docs written")
if A.no_save: idapro.close_database(False); log("closed without save")
else: idapro.close_database(True); log("closed with save")
