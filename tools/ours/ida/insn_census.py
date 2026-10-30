"""Instruction census over every IDA function of SLUS_216.21 (Phase 3 recompiler sizing).

Usage (idalib venv python; `import idapro` must be first):
  python insn_census.py <ida/work_phase3prep.i64> <repo root> [--from-cache] [--log PATH]

Opens the database WITHOUT auto-analysis and closes it WITHOUT saving (read-only use of a work
copy; it refuses to open the master `ida/p3fes.i64`).

Two views are produced, because IDA's r5900l module (a) fuses `ldl/ldr`, `sdl/sdr`, `lwl/lwr`,
`swl/swr`, `lui+ori/addiu`, `lui+mtc1` into 8-byte macro items (`uld`, `usd`, `ulw`, `usw`, `li`,
`la`, `dli`, `li.s`), (b) renders every VU0 macro-mode instruction as an opaque `cop2`, and (c) uses
pseudo-names (`beqzl`, `bnezl`, `move`, `b`, `negu`...). The recompiler (ADR-0004) decodes raw words,
so the authoritative census is the word-level one; IDA's item view is kept for cross-checking.

Pass 1 (IDA): every function chunk (`idautils.Chunks`), every item: printed + canonical mnemonic,
item size, data items inside chunks, chunk bytes, `jr`/`jalr` operand text + switch-info presence,
orphan code outside all functions, disassembly samples for special-cased mnemonics. Cached in
`ida/logs/phase3prep_census_raw.json` (gitignored, contains code bytes) for `--from-cache`.
Pass 2 (pure python): our R5900 word decoder (encoding layout after the EE Core Instruction Set
manual; table shape mirrors ps2-web-recomp `recomp/r5900.cpp`, MIT) over every 4-byte word of
every code item; classification by execution unit; aggregation; outputs:
  symbols/insn_census.json
  docs/ANALYSIS/08_instruction_census.md   (text between GENERATED markers only)
  ida/logs/phase3prep_census.log
"""
import sys, os, re, json, time, argparse, collections, struct

ap = argparse.ArgumentParser()
ap.add_argument("i64"); ap.add_argument("root")
ap.add_argument("--from-cache", action="store_true", help="skip IDA; reclassify the cached raw pass")
ap.add_argument("--log", default=None)
ap.add_argument("--objdump", default=None, help="`objdump -d --no-show-raw-insn` listing of the ELF: per-word cross-check of our decoder")
A = ap.parse_args()
ROOT = os.path.abspath(A.root)
LG = os.path.join(ROOT, "ida", "logs"); os.makedirs(LG, exist_ok=True)
AN = os.path.join(ROOT, "docs", "ANALYSIS"); SY = os.path.join(ROOT, "symbols")
RAW = os.path.join(LG, "phase3prep_census_raw.json")
logf = open(A.log or os.path.join(LG, "phase3prep_census.log"), "a", encoding="utf-8"); T0 = time.time()
def log(m):
    s = f"[{time.strftime('%H:%M:%S')} +{time.time()-T0:6.1f}s] {m}"; print(s, flush=True); logf.write(s + "\n"); logf.flush()

# ----------------------------------------------------------------------------------------------
# Band map: docs/ANALYSIS/03 (leaked source-file names) as consolidated in 06 §2.1. Labels inferred.
BANDS = [
    (0x100000, 0x103da0, "crt0 + early SDK stubs"), (0x103da0, 0x1939d0, "h_* / _h_camp_*"),
    (0x1939d0, 0x199440, "kwln*"), (0x199440, 0x1e7f90, "k_*"), (0x1e7f90, 0x28dbf0, "br_*/bp_*/sfl_*/op_*"),
    (0x28dbf0, 0x30fc40, "btl*/dat*"), (0x30fc40, 0x35aef0, "unattributed"), (0x35aef0, 0x361350, "scr*"),
    (0x361350, 0x3a2150, "mt_evt*"), (0x3a2150, 0x3bdbd0, "itf*/fr*"), (0x3bdbd0, 0x4176f0, "comu*/fcl*"),
    (0x4176f0, 0x46c000, "unattributed (Y_StParts_UpdateStratumPartsTask)"), (0x46c000, 0x4e7000, "G3_2D* renderer"),
    (0x4e7000, 0x4f9000, "renderer tail"), (0x4f9000, 0x51d460, "SCE SDK libs"),
    (0x51d460, 0x5a2000, "MW runtime + CRI"), (0x5a2000, 0x7cde80, "data band"),
]
def band_of(ea):
    for s, e, n in BANDS:
        if s <= ea < e: return f"{s:#x}..{e:#x} {n}"
    return "outside band map"

SAMPLE_PREFIXES = ("pmfhl", "pmthl", "cop2", "bc2", "bc1", "bc0", "mtsa", "mfsa", "cache", "sync", "pref", "ei", "di",
                   "eret", "qmfc2", "qmtc2", "cfc2", "ctc2", "lqc2", "sqc2", "c.", "cvt.", "madd", "msub", "adda",
                   "suba", "mula", "rsqrt", "qfsrv", "mfc0", "mtc0", "tlb", "ldl", "ldr", "sdl", "sdr", "lwu", "movz",
                   "movn", "pext5", "ppac5", "plzcw", "pexcw", "pexow", "pexew", "mfthc1", "uld", "usd", "ulw", "usw",
                   "dli", "li.s", "dnegu", "beqzl", "bnezl", "lq", "sq", "mult1", "div1", "mfhi1", "mflo1", "madd1")
SAMPLE_MAX = 3

# ----------------------------------------------------------------------------------------------
def pass1_ida():
    import idapro  # noqa  -- idalib
    idapro.enable_console_messages(False)
    i64 = os.path.abspath(A.i64)
    if os.path.basename(i64).lower() == "p3fes.i64":
        log("REFUSING to open the master database; use a work copy"); sys.exit(2)
    log(f"opening {i64} (no auto-analysis, will not save)")
    rc = idapro.open_database(i64, False)
    log(f"open_database rc={rc}")
    if rc != 0: sys.exit(rc)
    import idautils, ida_funcs, ida_bytes, ida_ua, ida_segment, ida_nalt, ida_ida, idc
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from import_symbols import load_manual_addresses, withheld_name_map, export_disasm
    # ADR-0009: names and samples written to committed files use the exported forms (unverified hints -> sub_/loc_/data_<EA>)
    withheld = withheld_name_map(load_manual_addresses(os.path.join(os.path.dirname(os.path.abspath(__file__)), "names_manual.txt")))
    log(f"withheld hint names (exported as sub_/loc_/data_<EA>): {len(withheld)}")
    raw = {"database": os.path.relpath(i64, ROOT).replace("\\", "/"), "procname": ida_ida.inf_get_procname(),
           "functions": [], "orphan": {}, "samples": {}, "jr_sites": []}
    samples = raw["samples"]; insn = ida_ua.insn_t()
    nfunc = 0; nitems = 0
    for f_ea in idautils.Functions():
        pfn = ida_funcs.get_func(f_ea)
        if pfn is None: continue
        nfunc += 1
        chunks = [(s, e) for s, e in idautils.Chunks(f_ea)]
        mn = collections.Counter(); data = []; macro = []; hexes = []
        for s, e in chunks:
            hexes.append(ida_bytes.get_bytes(s, e - s).hex())
            for ea in idautils.Heads(s, e):
                fl = ida_bytes.get_flags(ea); sz = ida_bytes.get_item_size(ea)
                if not ida_bytes.is_code(fl):
                    data.append((ea, sz)); continue
                if ida_ua.decode_insn(insn, ea) <= 0:
                    mn["<undecodable>"] += 1; continue
                printed = ida_ua.print_insn_mnem(ea) or "<empty>"
                canon = insn.get_canon_mnem() or printed
                key = printed if printed == canon else f"{printed}|{canon}"
                mn[key] += 1; nitems += 1
                if sz != 4: macro.append((ea, sz, printed))
                base = canon.lower()
                if base in ("jr", "jalr"):
                    raw["jr_sites"].append({"ea": ea, "f": f_ea, "m": base, "op0": idc.print_operand(ea, 0),
                                            "op1": idc.print_operand(ea, 1), "switch": bool(ida_nalt.get_switch_info(ea))})
                if printed.lower().startswith(SAMPLE_PREFIXES):
                    lst = samples.setdefault(printed, [])
                    if len(lst) < SAMPLE_MAX:
                        lst.append({"ea": f"{ea:#x}", "text": export_disasm(ea, withheld)})
        fname = ida_funcs.get_func_name(f_ea)
        raw["functions"].append({"a": f_ea, "n": withheld.get(fname, fname), "chunks": chunks, "hex": hexes,
                                 "data": data, "macro": macro, "mn": dict(mn)})
        if nfunc % 4000 == 0: log(f"  {nfunc} functions, {nitems} IDA items")
    log(f"pass1: {nfunc} functions, {nitems} IDA code items")
    orphan = {}
    for i in range(ida_segment.get_segm_qty()):
        seg = ida_segment.getnseg(i); items = 0; nbytes = 0; mns = collections.Counter(); first = last = None
        for ea in idautils.Heads(seg.start_ea, seg.end_ea):
            if not ida_bytes.is_code(ida_bytes.get_flags(ea)) or ida_funcs.get_func(ea) is not None: continue
            sz = ida_bytes.get_item_size(ea); items += 1; nbytes += sz
            mns[ida_ua.print_insn_mnem(ea) or "?"] += 1
            if first is None: first = ea
            last = ea
        if items:
            orphan[ida_segment.get_segm_name(seg)] = {"items": items, "bytes": nbytes, "first": f"{first:#x}",
                                                      "last": f"{last:#x}", "top_mnemonics": mns.most_common(12)}
    raw["orphan"] = orphan
    log(f"orphan code: {sum(v['bytes'] for v in orphan.values())} bytes in {len(orphan)} segment(s)")
    idapro.close_database(False); log("database closed without saving")
    json.dump(raw, open(RAW, "w", encoding="utf-8")); log(f"raw cache -> {RAW}")
    return raw

# ----------------------------------------------------------------------------------------------
# Our R5900 word decoder. '-' = no instruction on the EE. Returns (unit, base, variant).
# Encoding layout: Sony "EE Core Instruction Set Manual"; table shape mirrors ps2-web-recomp
# recomp/r5900.cpp (MIT, snuri00) so the two can be diffed line by line.
PRIMARY = ("- - j jal beq bne blez bgtz addi addiu slti sltiu andi ori xori lui - - - - beql bnel blezl bgtzl "
           "daddi daddiu ldl ldr - - lq sq lb lh lwl lw lbu lhu lwr lwu sb sh swl sw sdl sdr swr cache "
           "- lwc1 - pref - - lqc2 ld - swc1 - - - - sqc2 sd").split()
SPECIAL = ("sll - srl sra sllv - srlv srav jr jalr movz movn syscall break - sync mfhi mthi mflo mtlo dsllv - dsrlv dsrav "
           "mult multu div divu - - - - add addu sub subu and or xor nor mfsa mtsa slt sltu dadd daddu dsub dsubu "
           "tge tgeu tlt tltu teq - tne - dsll - dsrl dsra dsll32 - dsrl32 dsra32").split()
REGIMM = ("bltz bgez bltzl bgezl - - - - tgei tgeiu tlti tltiu teqi - tnei - bltzal bgezal bltzall bgezall - - - - "
          "mtsab mtsah - - - - - -").split()
MMI = ("madd maddu - - plzcw - - - - - - - - - - - mfhi1 mthi1 mflo1 mtlo1 - - - - mult1 multu1 div1 divu1 - - - - "
       "madd1 maddu1 - - - - - - - - - - - - - - pmfhl pmthl - - psllh - psrlh psrah - - - - psllw - psrlw psraw").split()
MMI0 = ("paddw psubw pcgtw pmaxw paddh psubh pcgth pmaxh paddb psubb pcgtb - - - - - paddsw psubsw pextlw ppacw "
        "paddsh psubsh pextlh ppach paddsb psubsb pextlb ppacb - - pext5 ppac5").split()
MMI1 = ("- pabsw pceqw pminw padsbh pabsh pceqh pminh - - pceqb - - - - - padduw psubuw pextuw - padduh psubuh pextuh - "
        "paddub psubub pextub qfsrv - - - -").split()
MMI2 = ("pmaddw - psllvw psrlvw pmsubw - - - pmfhi pmflo pinth - pmultw pdivw pcpyld - pmaddh phmadh pand pxor pmsubh phmsbh - - "
        "- - pexeh prevh pmulth pdivbw pexew prot3w").split()
MMI3 = ("pmadduw - - psravw - - - - pmthi pmtlo pinteh - pmultuw pdivuw pcpyud - - - por pnor - - - - - - pexch pcpyh - - pexcw -").split()
PMFHL = ["pmfhl.lw", "pmfhl.uw", "pmfhl.slw", "pmfhl.lh", "pmfhl.sh"]
COP1S = ("add.s sub.s mul.s div.s sqrt.s abs.s mov.s neg.s - - - - - - - - - - - - - - rsqrt.s - adda.s suba.s mula.s - "
         "madd.s msub.s madda.s msuba.s - - - - cvt.w.s - - - max.s min.s - - - - - - c.f.s - c.eq.s - c.lt.s - c.le.s - "
         "- - - - - - - -").split()
VEC = (["vaddbc"] * 4 + ["vsubbc"] * 4 + ["vmaddbc"] * 4 + ["vmsubbc"] * 4 + ["vmaxbc"] * 4 + ["vminibc"] * 4 + ["vmulbc"] * 4 +
       "vmulq vmaxi vmuli vminii vaddq vmaddq vaddi vmaddi vsubq vmsubq vsubi vmsubi vadd vmadd vmul vmax vsub vmsub vopmsub vmini "
       "viadd visub viaddi - viand vior - - vcallms vcallmsr - - - - - -".split())
VECX = [("vaddabc vsubabc vmaddabc vmsubabc vitof0 vftoi0 vmulabc vmulaq vaddaq vsubaq vadda vsuba vmove vlqi vdiv vmtir vrnext " + "- " * 15).split(),
        ("vaddabc vsubabc vmaddabc vmsubabc vitof4 vftoi4 vmulabc vabs vmaddaq vmsubaq vmadda vmsuba vmr32 vsqi vsqrt vmfir vrget " + "- " * 15).split(),
        ("vaddabc vsubabc vmaddabc vmsubabc vitof12 vftoi12 vmulabc vmulai vaddai vsubai vmula vopmula - vlqd vrsqrt vilwr vrinit " + "- " * 15).split(),
        ("vaddabc vsubabc vmaddabc vmsubabc vitof15 vftoi15 vmulabc vclip vmaddai vmsubai - vnop - vsqd vwaitq viswr vrxor " + "- " * 15).split()]
for t, n in ((PRIMARY, 64), (SPECIAL, 64), (REGIMM, 32), (MMI, 64), (MMI0, 32), (MMI1, 32), (MMI2, 32), (MMI3, 32), (COP1S, 64), (VEC, 64)):
    assert len(t) == n, (len(t), n)
for t in VECX: assert len(t) == 32, len(t)
BC = "xyzw"; DEST_BITS = "xyzw"  # dest field bits 24..21 = x y z w
U_INT, U_BR, U_BRL, U_JMP, U_TRAP, U_MMI, U_COP0, U_COP1, U_COP2X, U_VU, U_INV = (
    "integer core", "branch", "branch (likely)", "jump", "trap", "MMI", "COP0", "COP1 FPU", "COP2 transfer", "COP2 VU0 macro", "invalid")
LIKELY = set("beql bnel blezl bgtzl bltzl bgezl bltzall bgezall bc0fl bc0tl bc1fl bc1tl bc2fl bc2tl".split())
BRANCHES = set("beq bne blez bgtz bltz bgez bltzal bgezal bc0f bc0t bc1f bc1t bc2f bc2t".split())
TRAPS = set("syscall break teq tne tge tgeu tlt tltu tgei tgeiu tlti tltiu teqi tnei".split())
MMI_SET = set(MMI + MMI0 + MMI1 + MMI2 + MMI3 + ["lq", "sq", "mfsa", "mtsa", "mtsab", "mtsah"]) - {"-"}
COP0_SET = set("mfc0 mtc0 cache sync sync.p bc0f bc0t bc0fl bc0tl tlbr tlbwi tlbwr tlbp eret ei di".split())

def dest_str(w): return "".join(DEST_BITS[i] for i in range(4) if (w >> (24 - i)) & 1)

def decode(w):
    """-> (unit, base_mnemonic, variant_mnemonic). variant carries VU dest/bc, pmfhl fmt, interlock bit."""
    op = w >> 26; rs = (w >> 21) & 31; rt = (w >> 16) & 31; funct = w & 63; sa = (w >> 6) & 31
    if op == 0:
        m = SPECIAL[funct]
        if m == "sync" and sa & 0x10: return U_COP0, "sync", "sync.p"
        if m == "sync": return U_COP0, "sync", "sync.l"
    elif op == 1: m = REGIMM[rt]
    elif op == 0x10:
        if rs == 0: m = "mfc0"
        elif rs == 4: m = "mtc0"
        elif rs == 8: m = ["bc0f", "bc0t", "bc0fl", "bc0tl"][rt] if rt < 4 else "-"
        elif rs == 16: m = {1: "tlbr", 2: "tlbwi", 6: "tlbwr", 8: "tlbp", 24: "eret", 56: "ei", 57: "di"}.get(funct, "-")
        else: m = "-"
    elif op == 0x11:
        if rs == 0: m = "mfc1"
        elif rs == 2: m = "cfc1"
        elif rs == 4: m = "mtc1"
        elif rs == 6: m = "ctc1"
        elif rs == 8: m = ["bc1f", "bc1t", "bc1fl", "bc1tl"][rt] if rt < 4 else "-"
        elif rs == 16: m = COP1S[funct]
        elif rs == 20: m = "cvt.s.w" if funct == 32 else "-"
        else: m = "-"
        if m != "-": return U_COP1, m, m
    elif op == 0x12:
        if rs >= 16:
            m = VECX[funct & 3][sa] if funct >= 60 else VEC[funct]
            if m == "-": return U_INV, "-", "-"
            if m.endswith("bc"): base = m[:-2]; var = f"{base}{BC[w & 3]}.{dest_str(w)}"
            elif m in ("vcallms", "vcallmsr", "vnop", "vwaitq", "vdiv", "vsqrt", "vrsqrt", "vmtir", "vmfir", "vilwr", "viswr",
                       "viadd", "visub", "viaddi", "viand", "vior", "vrnext", "vrget", "vrinit", "vrxor", "vclip"):
                base = m; var = m if m not in ("vilwr", "viswr", "vrnext", "vrget", "vrinit", "vrxor") else f"{m}.{dest_str(w)}"
            else: base = m; var = f"{m}.{dest_str(w)}"
            return U_VU, base, var
        m = {1: "qmfc2", 2: "cfc2", 5: "qmtc2", 6: "ctc2"}.get(rs, "-")
        if rs == 8: m = ["bc2f", "bc2t", "bc2fl", "bc2tl"][rt] if rt < 4 else "-"
        if m == "-": return U_INV, "-", "-"
        var = m + (".i" if (m in ("qmfc2", "cfc2", "qmtc2", "ctc2") and (w & 1)) else "")
        return (U_BRL if m in LIKELY else U_BR if m in BRANCHES else U_COP2X), m, var
    elif op == 0x1C:
        if funct == 8: m = MMI0[sa]
        elif funct == 40: m = MMI1[sa]
        elif funct == 9: m = MMI2[sa]
        elif funct == 41: m = MMI3[sa]
        elif funct == 48: m = PMFHL[sa] if sa <= 4 else "-"
        elif funct == 49: m = "pmthl.lw" if sa == 0 else "-"
        else: m = MMI[funct]
        if m == "-": return U_INV, "-", "-"
        return U_MMI, m.split(".")[0], m
    else: m = PRIMARY[op]
    if m == "-": return U_INV, "-", "-"
    if m in LIKELY: return U_BRL, m, m
    if m in BRANCHES: return U_BR, m, m
    if m in ("j", "jal", "jr", "jalr"): return U_JMP, m, m
    if m in TRAPS: return U_TRAP, m, m
    if m in MMI_SET: return U_MMI, m, m
    if m in COP0_SET: return U_COP0, m, m
    if m in ("lwc1", "swc1"): return U_COP1, m, m
    if m in ("lqc2", "sqc2"): return U_COP2X, m, m
    return U_INT, m, m

# objdump mnemonic -> our base/variant it is allowed to stand for (binutils pseudo-ops)
OBJDUMP_ALIAS = {"nop": {"sll"}, "move": {"addu", "daddu", "or"}, "b": {"beq"}, "beqz": {"beq"}, "bnez": {"bne"}, "beqzl": {"beql"},
                 "bnezl": {"bnel"}, "li": {"addiu", "ori", "lui"}, "negu": {"subu"}, "neg": {"sub"}, "dnegu": {"dsubu"}, "dneg": {"dsub"},
                 "not": {"nor"}, "bal": {"bgezal"}, "sync": {"sync.l"}, "ehb": {"sll"}, "ssnop": {"sll"}, "pause": {"sll"}}
def objdump_crosscheck(raw, listing):
    """Compare our decode of every function word against an `objdump -d` listing (third decoder; observed)."""
    rx = re.compile(r"^\s*([0-9a-f]+):\s+(\S+)")
    od = {}
    for line in open(listing, encoding="utf-8", errors="replace"):
        m = rx.match(line)
        if m: od[int(m.group(1), 16)] = m.group(2)
    agree = 0; missing = 0; pairs = collections.Counter(); samples = collections.defaultdict(list); compared = 0
    for f in raw["functions"]:
        datas = sorted(f["data"])
        for (s, e), hx in zip(f["chunks"], f["hex"]):
            b = bytes.fromhex(hx); di = 0
            for off in range(0, len(b) - 3, 4):
                ea = s + off
                while di < len(datas) and datas[di][0] + datas[di][1] <= ea: di += 1
                if di < len(datas) and datas[di][0] <= ea < datas[di][0] + datas[di][1]: continue
                unit, base, var = decode(struct.unpack_from("<I", b, off)[0])
                o = od.get(ea)
                if o is None: missing += 1; continue
                compared += 1
                ol = o.lower()
                if ol in (base, var) or base in OBJDUMP_ALIAS.get(ol, ()) or var in OBJDUMP_ALIAS.get(ol, ()): agree += 1; continue
                key = f"ours={var} objdump={o}"; pairs[key] += 1
                if len(samples[key]) < 3: samples[key].append(f"{ea:#x}")
    return {"listing": os.path.basename(listing), "words_compared": compared, "agree": agree, "disagree": compared - agree,
            "missing_in_objdump": missing, "disagreement_pairs": [{"pair": k, "count": n, "samples": samples[k]} for k, n in pairs.most_common()]}

# IDA printed/canonical mnemonic -> unit (IDA view; pseudo-names and macros classified by what they stand for)
IDA_MACROS = {"uld": "ldl+ldr", "usd": "sdl+sdr", "ulw": "lwl+lwr", "usw": "swl+swr", "li": "lui+ori/addiu (32-bit immediate)",
              "la": "lui+addiu", "dli": "lui/ori/dsll32/or 64-bit immediate sequence", "li.s": "lui+mtc1 (float immediate)"}
IDA_MACRO_DEFAULT = "lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word"

def pass2(raw):
    funcs = raw["functions"]
    word_units = collections.defaultdict(collections.Counter)   # unit -> base -> count   (word level, ours)
    variants = collections.defaultdict(collections.Counter)     # base -> variant -> count
    unit_tot = collections.Counter(); printed_hist = collections.Counter(); ida_item_sizes = collections.defaultdict(collections.Counter)
    invalid_words = []; per_func = []; flags = collections.Counter()
    band = collections.defaultdict(lambda: {"insns": 0, "mmi": 0, "cop2": 0, "fpu": 0, "likely": 0, "funcs": 0, "funcs_mmi": 0, "funcs_cop2": 0, "funcs_likely": 0})
    total_words = 0; total_code_bytes = 0; total_data_items = 0; total_data_bytes = 0; data_words_decodable = 0
    accounting_mismatch = []
    for f in funcs:
        fu = collections.Counter(); fb = collections.Counter()
        words_before = total_words
        for key, c in f["mn"].items():
            printed = key.split("|")[0]; printed_hist[printed] += c
        for ea, sz, printed in f["macro"]: ida_item_sizes[printed][sz] += 1
        datas = sorted(f["data"]); total_data_items += len(datas); total_data_bytes += sum(s for _, s in datas)
        for (s, e), hx in zip(f["chunks"], f["hex"]):
            b = bytes.fromhex(hx); di = 0
            for off in range(0, len(b) - 3, 4):
                ea = s + off
                while di < len(datas) and datas[di][0] + datas[di][1] <= ea: di += 1
                if di < len(datas) and datas[di][0] <= ea < datas[di][0] + datas[di][1]:
                    if decode(struct.unpack_from("<I", b, off)[0])[0] != U_INV: data_words_decodable += 1
                    continue
                w = struct.unpack_from("<I", b, off)[0]
                unit, base, var = decode(w); total_words += 1; total_code_bytes += 4
                word_units[unit][base] += 1; unit_tot[unit] += 1; fu[unit] += 1; fb[base] += 1
                if var != base: variants[base][var] += 1
                if unit == U_INV and len(invalid_words) < 200: invalid_words.append({"ea": f"{ea:#x}", "func": f["n"]})
        mmi = fu[U_MMI]; cop2 = fu[U_VU] + fu[U_COP2X]; likely = fu[U_BRL]; fpu = fu[U_COP1]
        ldsd = fb["ld"] + fb["sd"]; ldsd_all = ldsd + fb["ldl"] + fb["ldr"] + fb["sdl"] + fb["sdr"]
        d64 = sum(c for m, c in fb.items() if m in ("dadd", "daddu", "daddi", "daddiu", "dsub", "dsubu", "dsll", "dsrl", "dsra", "dsll32", "dsrl32", "dsra32", "dsllv", "dsrlv", "dsrav"))
        for k, v in (("any_likely_branch", likely), ("any_cop2", cop2), ("any_vu0_macro", fu[U_VU]), ("any_ld_sd", ldsd),
                     ("any_ld_sd_or_unaligned_64", ldsd_all), ("any_mmi", mmi), ("any_mmi_or_cop2", mmi + cop2), ("any_fpu", fpu),
                     ("any_64bit_int_alu_shift", d64), ("any_trap_or_syscall", fu[U_TRAP]), ("any_cop0", fu[U_COP0]),
                     ("any_invalid_word", fu[U_INV]), ("multi_chunk", len(f["chunks"]) > 1), ("contains_data_items", len(datas)),
                     ("any_jalr", fb["jalr"]), ("any_jr_non_ra", 0)):
            if v: flags[k] += 1
        bd = band[band_of(f["a"])]; bd["insns"] += sum(fu.values()); bd["mmi"] += mmi; bd["cop2"] += cop2; bd["fpu"] += fpu; bd["likely"] += likely; bd["funcs"] += 1
        if mmi: bd["funcs_mmi"] += 1
        if cop2: bd["funcs_cop2"] += 1
        if likely: bd["funcs_likely"] += 1
        expected = sum(f["mn"].values()) + sum(sz // 4 - 1 for _, sz, _ in f["macro"])
        if expected != total_words - words_before:
            accounting_mismatch.append({"func": f["n"], "a": f"{f['a']:#x}", "ida_items_plus_macro_words": expected, "words": total_words - words_before,
                                        "chunks": [f"{s:#x}..{e:#x}" for s, e in f["chunks"]]})
        per_func.append({"a": f"{f['a']:#x}", "n": f["n"], "size": sum(e - s for s, e in f["chunks"]), "chunks": len(f["chunks"]),
                         "insns": sum(fu.values()), "mmi": mmi, "cop2": cop2, "fpu": fpu, "likely": likely, "ld_sd": ldsd, "band": band_of(f["a"])})
    jr = raw["jr_sites"]
    def is_ra(op): return op.strip("$").lower() == "ra"
    jr_non_ra = [s for s in jr if s["m"] == "jr" and not is_ra(s["op0"])]
    flags["any_jr_non_ra"] = len({s["f"] for s in jr_non_ra})
    indirect = {"jr_total": sum(1 for s in jr if s["m"] == "jr"), "jr_ra": sum(1 for s in jr if s["m"] == "jr" and is_ra(s["op0"])),
                "jr_non_ra": len(jr_non_ra), "jr_non_ra_functions": len({s["f"] for s in jr_non_ra}),
                "jr_non_ra_with_switch_info": sum(1 for s in jr_non_ra if s["switch"]),
                "jr_non_ra_without_switch_info": sum(1 for s in jr_non_ra if not s["switch"]),
                "jr_non_ra_by_register": collections.Counter(s["op0"] for s in jr_non_ra).most_common(),
                "jalr": sum(1 for s in jr if s["m"] == "jalr"), "jalr_functions": len({s["f"] for s in jr if s["m"] == "jalr"}),
                "jalr_by_register": collections.Counter((s["op1"] or s["op0"]) for s in jr if s["m"] == "jalr").most_common(),
                "note": "sites inside IDA functions only; per-site detail in symbols/jumptables.json (export_jumptables.py)"}
    ida_items_total = sum(printed_hist.values())
    ida_opaque = {m: n for m, n in printed_hist.items() if m.lower() in ("cop2", "cop0", "cop1", "cop3") or m.startswith("<")}
    macro_items = {m: {"items": sum(c.values()), "sizes": dict(c), "expands_to": IDA_MACROS.get(m, IDA_MACRO_DEFAULT)} for m, c in ida_item_sizes.items()}
    objdump = objdump_crosscheck(raw, A.objdump) if A.objdump else {"listing": None, "note": "not run (--objdump not given)"}
    if A.objdump: log(f"objdump cross-check: {objdump['agree']}/{objdump['words_compared']} agree, {objdump['disagree']} disagree, {objdump['missing_in_objdump']} missing; top pairs: {[(p['pair'], p['count']) for p in objdump['disagreement_pairs'][:8]]}")
    extra_words = sum(sum((sz // 4 - 1) * n for sz, n in c.items()) for c in ida_item_sizes.values())
    census = {
        "generated": time.strftime("%Y-%m-%d %H:%M:%S"), "tool": "tools/ours/ida/insn_census.py",
        "database": raw["database"] + " (copy of ida/p3fes.i64)", "procname": raw["procname"],
        "scope": "every 4-byte word of every code item inside every IDA function chunk (idautils.Chunks); data items inside chunks and orphan code outside functions are counted separately",
        "functions": len(funcs), "words_decoded": total_words, "code_bytes_in_functions": total_code_bytes,
        "ida_code_items": ida_items_total, "ida_macro_items_extra_words": extra_words,
        "ida_items_plus_macro_words_equals_words": ida_items_total + extra_words == total_words,
        "data_items_in_functions": {"items": total_data_items, "bytes": total_data_bytes, "words_that_also_decode_as_valid_instructions": data_words_decodable},
        "orphan_code_outside_functions": {"bytes": sum(v["bytes"] for v in raw["orphan"].values()), "by_segment": raw["orphan"]},
        "unit_totals": dict(unit_tot.most_common()),
        "units": {u: dict(c.most_common()) for u, c in word_units.items()},
        "variants": {b: dict(c.most_common()) for b, c in variants.items()},
        "invalid_words": invalid_words,
        "word_accounting_mismatches": accounting_mismatch,
        "objdump_crosscheck": objdump,
        "ida_view": {"printed_mnemonics": dict(printed_hist.most_common()), "opaque_renderings": ida_opaque, "macro_items": macro_items},
        "indirect_jumps": indirect, "function_flags": dict(flags.most_common()),
        "by_band": {k: v for k, v in sorted(band.items())},
        "top20_mmi_cop2_functions": sorted(per_func, key=lambda x: -(x["mmi"] + x["cop2"]))[:20],
        "operand_samples_ida": raw["samples"],
        "classification_note": "counts are observed (bytes from IDA's function chunks, decoded by our table); unit assignment, VU0 dest/broadcast collapse and the IDA-macro expansion mapping are ours (inferred)",
    }
    json.dump(census, open(os.path.join(SY, "insn_census.json"), "w", encoding="utf-8"), indent=1)
    log(f"census -> symbols/insn_census.json: {total_words} words in {len(funcs)} functions; units={dict(unit_tot)}; "
        f"ida_items={ida_items_total} +macro_words={extra_words} match={census['ida_items_plus_macro_words_equals_words']}; invalid={unit_tot[U_INV]}")
    write_doc(census)
    return census

BEGIN, END = "<!-- GENERATED:BEGIN (insn_census.py) -->", "<!-- GENERATED:END -->"
def write_doc(c):
    L = [f"_Generated {c['generated']} by `tools/ours/ida/insn_census.py` from `{c['database']}`. Do not edit inside the markers. "
         f"Word counts are observed (our decoder over IDA's function-chunk bytes); unit grouping and macro expansion are ours._\n", "### Headline\n", "| Metric | Value |\n|---|---|"]
    L.append(f"| IDA functions walked (all chunks) | {c['functions']:,} |")
    L.append(f"| Instruction words inside functions (word-level, ours) | {c['words_decoded']:,} |")
    L.append(f"| IDA code items (macro-fused view) | {c['ida_code_items']:,} (+{c['ida_macro_items_extra_words']:,} words hidden in macro items; sum matches words: {c['ida_items_plus_macro_words_equals_words']}) |")
    L.append(f"| Code bytes inside functions | {c['code_bytes_in_functions']:,} |")
    di = c["data_items_in_functions"]
    L.append(f"| Data items inside function chunks (not decoded) | {di['items']:,} items, {di['bytes']:,} bytes ({di['words_that_also_decode_as_valid_instructions']:,} words would decode as valid instructions) |")
    oc = c["orphan_code_outside_functions"]
    L.append(f"| Orphan code outside every function (excluded) | {oc['bytes']:,} bytes in {len(oc['by_segment'])} segment(s) |")
    for seg, v in oc["by_segment"].items():
        L.append(f"| &nbsp;&nbsp;orphan in `{seg}` | {v['items']:,} items, {v['bytes']:,} bytes, `{v['first']}`..`{v['last']}`; top: " + ", ".join(f"`{m}` {n}" for m, n in v["top_mnemonics"][:6]) + " |")
    L.append(f"| Words our decoder rejects (`invalid`) | {c['unit_totals'].get('invalid', 0):,} (first 200 listed in JSON) |")
    L += ["\n### Per-unit totals (word level)\n", "| Unit | Words | Share | Distinct base mnemonics |\n|---|---|---|---|"]
    tot = c["words_decoded"]
    for u, n in c["unit_totals"].items(): L.append(f"| {u} | {n:,} | {100*n/tot:.2f}% | {len(c['units'][u])} |")
    L.append("\n### Mnemonic table by unit (VU0 dest `.xyzw` / broadcast `x|y|z|w` and `pmfhl.*` fold into the base; variants in `symbols/insn_census.json#variants`)\n")
    for u, mns in c["units"].items():
        L.append(f"**{u}** ({c['unit_totals'][u]:,}): " + ", ".join(f"`{m}` {n:,}" for m, n in mns.items()) + "\n")
    L.append("### Third decoder: ps2dev binutils `objdump -d` over the same words (observed)\n")
    od = c["objdump_crosscheck"]
    if od.get("listing"):
        L.append(f"Listing `{od['listing']}`: {od['words_compared']:,} words compared, **{od['agree']:,} agree**, {od['disagree']:,} disagree, {od['missing_in_objdump']:,} not in listing. "
                 "Agreement allows binutils pseudo-ops (`move`, `li`, `nop`, `b`, `beqz`...). Disagreement pairs:\n")
        L.append("| ours | objdump | Words | Sample VAs |\n|---|---|---|---|")
        for p in od["disagreement_pairs"][:40]:
            ours, theirs = p["pair"].split(" objdump=")
            L.append(f"| `{ours[5:]}` | `{theirs}` | {p['count']:,} | " + ", ".join(f"`{s}`" for s in p["samples"]) + " |")
    else:
        L.append("_not run_")
    am = c["word_accounting_mismatches"]
    L.append(f"\nWord accounting (IDA items + macro words vs chunk words): {len(am)} function(s) differ" + (": " + "; ".join(f"`{x['func']}` `{x['a']}` items+macro={x['ida_items_plus_macro_words']} words={x['words']}" for x in am[:10]) if am else "") + ".\n")
    L.append("### How IDA renders the same stream (cross-check)\n")
    L.append("| IDA rendering | Items | Meaning |\n|---|---|---|")
    for m, n in c["ida_view"]["opaque_renderings"].items(): L.append(f"| `{m}` | {n:,} | opaque: IDA does not name the VU0 macro op (the word-level table above does) |")
    for m, v in c["ida_view"]["macro_items"].items(): L.append(f"| `{m}` | {v['items']:,} | macro item, sizes {v['sizes']}; expands to {v['expands_to']} |")
    ind = c["indirect_jumps"]
    L += ["\n### Indirect jumps and calls\n", "| Site kind | Count |\n|---|---|",
          f"| `jr $ra` (returns) | {ind['jr_ra']:,} |", f"| `jr $rN`, N != ra (indirect jumps) | {ind['jr_non_ra']:,} in {ind['jr_non_ra_functions']:,} functions |",
          f"| &nbsp;&nbsp;with IDA switch info | {ind['jr_non_ra_with_switch_info']:,} |", f"| &nbsp;&nbsp;without switch info (unresolved) | {ind['jr_non_ra_without_switch_info']:,} |",
          f"| `jalr` (indirect calls) | {ind['jalr']:,} in {ind['jalr_functions']:,} functions |",
          "\n`jr $rN` by register: " + ", ".join(f"`{r}` {n}" for r, n in ind["jr_non_ra_by_register"]) + ".  ",
          "`jalr` by target register: " + ", ".join(f"`{r}` {n}" for r, n in ind["jalr_by_register"]) + ".\n",
          "### Functions by feature (recompiler test-matrix sizing)\n", "| Feature present in function | Functions |\n|---|---|"]
    for k, v in c["function_flags"].items(): L.append(f"| {k} | {v:,} |")
    L += ["\n### Distribution across the band map (`03`, bands as in `06` §2.1)\n", "| Band | Functions | Words | MMI | fn w/ MMI | COP2 | fn w/ COP2 | FPU | likely | fn w/ likely |\n|---|---|---|---|---|---|---|---|---|---|"]
    for b, v in c["by_band"].items():
        L.append(f"| `{b}` | {v['funcs']:,} | {v['insns']:,} | {v['mmi']:,} | {v['funcs_mmi']:,} | {v['cop2']:,} | {v['funcs_cop2']:,} | {v['fpu']:,} | {v['likely']:,} | {v['funcs_likely']:,} |")
    L += ["\n### Top 20 functions by MMI + COP2 word count\n", "| Function | VA | Size (B) | Chunks | Words | MMI | COP2 | FPU | Likely | Band |\n|---|---|---|---|---|---|---|---|---|---|"]
    for f in c["top20_mmi_cop2_functions"]:
        L.append(f"| `{f['n']}` | `{f['a']}` | {f['size']:,} | {f['chunks']} | {f['insns']:,} | {f['mmi']:,} | {f['cop2']:,} | {f['fpu']:,} | {f['likely']} | {f['band'].split(' ',1)[1]} |")
    L += ["\n### Operand-format samples as IDA prints them (first 3 sites each; VAs)\n", "| IDA mnemonic | IDA items | Sample sites |\n|---|---|---|"]
    for m, lst in sorted(c["operand_samples_ida"].items()):
        L.append(f"| `{m}` | {c['ida_view']['printed_mnemonics'].get(m, 0):,} | " + "; ".join(f"`{s['ea']}` `{s['text']}`" for s in lst) + " |")
    gen = f"{BEGIN}\n" + "\n".join(L) + f"\n{END}"
    p = os.path.join(AN, "08_instruction_census.md")
    if os.path.exists(p):
        old = open(p, encoding="utf-8").read()
        if BEGIN in old and END in old:
            pre, rest = old.split(BEGIN, 1); _, post = rest.split(END, 1)
            open(p, "w", encoding="utf-8").write(pre + gen + post); log(f"doc updated -> {p}"); return
    open(p, "w", encoding="utf-8").write("# 08 - Instruction census (Phase 3 recompiler input)\n\n" + gen + "\n"); log(f"doc created -> {p}")

if __name__ == "__main__":
    if A.from_cache: raw = json.load(open(RAW, encoding="utf-8")); log(f"raw cache loaded from {RAW}")
    else: raw = pass1_ida()
    pass2(raw)
    log("done")
