"""Apply symbols/p3fes.sym back onto an IDA database (fresh or existing).

Usage (venv python; `import idapro` must be first):
  python import_symbols.py <ida/p3fes.i64> <symbols/p3fes.sym> [--no-save] [--create-funcs]
                           [--chunks symbols/function_chunks.txt] [--as-hints]

Semantics:
  * F lines: if --create-funcs and no function exists at the address, a function is created there (exact bounds
    from --chunks when given, else [addr, addr+size); IDA's refusals are retried after decoding the bytes, see
    create_function). The name is applied only when it is not an IDA auto name (sub_/nullsub_/j_...), so auto
    names never become user names.
  * D / L lines: ida_name.set_name(addr, name) (SN_FORCE: a clash gets a numeric suffix and is reported).
  * Optional tags after the name (`key=value` tokens; the bare `flirt` token = FLIRT-derived name):
      source=<src>   the row is a HINT (ADR-0009): applied only where IDA still has an auto/dummy name, never
                     over a user or FLIRT name; always records a repeatable comment `HINT[<src>] <name>`.
      verified=yes   PROMOTION: the row is applied like an ordinary user name and the comment line becomes
                     `HINT[<src>] <name> verified`; export_symbols.py then exports it with `source=<src>`.
                     Promotion is therefore the one-line edit `... source=snaku` -> `... source=snaku verified=yes`
                     in the hint file (or symbols/p3fes.hints.sym) plus the evidence note in docs/ANALYSIS/.
    Rows without `source=` are authoritative (our names), as before.
    Rows with `source=phase2-<topic>`, `source=phase5-<slice>` (or `source=manual`) are OUR analysis (Phase 2
    topic deltas, see docs/ANALYSIS/PHASE2_BRIEF.md; Phase 5 slice deltas, docs/PHASE5_AGENT_BRIEF.md): they take the authoritative path -- names set (auto names skipped),
    functions created with --create-funcs -- and an `ev=<anchor>` tag is recorded as a repeatable comment
    `EV[<source>] <anchor>` so the evidence trail survives in the database.
  * `# comment <addr8> <text>` lines (anywhere in the file) set a function comment when <addr8> is a function
    start, otherwise a repeatable comment at that address. Re-running is idempotent (identical text is not
    appended twice).
  * EXPORTED FILE (round trip, tools/ours/ida/README.md "Round trip"): a file whose header says it was written by
    export_symbols.py (symbols/p3fes.sym) is the text backup of the master database, and every row in it already
    passed the export rule, so it is restored as a whole rather than re-judged (`--as-hints` disables this and
    treats the file like a hint file):
      - a `source=<src>` row is a promotion (the comment line is written `verified`, or plain for a permissive
        source), F rows create their function with --create-funcs, D/L rows are made item heads;
      - `flirt` sets FUNC_LIB on the function (cleared on functions whose row has no tag);
      - a `sub_<EA>` row whose IDA dummy name differs here (`nullsub_N`, `j_x`: the master exports `sub_<EA>` where
        it withholds an unverified hint) gets the exported form pinned as its name;
      - D rows are re-created at the exported item size (`ensure_head` clears the whole range first: the VU1
        microcode labels sit inside IDA's mis-disassembled code items), L rows become instruction heads;
      - with --create-funcs, functions absent from the file are deleted (`pruned`), and with --chunks (default:
        `function_chunks.txt` next to the .sym when it exists) every function's main chunk end, tails and data
        items inside its chunks are set to the exported layout, then verified.
  * Prints a short summary; details go to <db dir>/logs/import.log. Returns exit code 1 if any name failed.
"""
import idapro  # noqa -- must be first
import argparse, os, re, sys, time

AUTO_RE = re.compile(r"^(sub_|nullsub_|j_sub_|j_nullsub_|loc_|off_|unk_|byte_|word_|dword_|qword_|xmmword_|asc_|locret_|flt_|dbl_|jpt_|def_)")
# Sources whose license permits committing their names (ADR-0009 S2a); everything else needs `verified`.
PERMISSIVE_SOURCES = {"fes-pc-recomp"}
# Sources that are our own analysis (Phase 2 topic deltas `phase2-<topic>`, Phase 5 slice deltas `phase5-<slice>`):
# authoritative, never treated as hints. Community sources (tge-pr4, snaku, ...) never match.
OUR_SOURCE_RE = re.compile(r"^(phase[25]-|manual$)")
COMMENT_LINE_RE = re.compile(r"^#\s*comment\s+([0-9A-Fa-f]{6,8})\s+(.+?)\s*$")
# Comment grammar written at a hinted address (repeatable comment), one line per source:
#   HINT[<source>] <name>            the hint placed this name (IDA had only an auto name)
#   HINT[<source>] <name> agrees     the name was already there (ours/FLIRT) -- the hint merely agrees
#   HINT[<source>] <name> verified   promoted: analyst-verified, exportable with `source=<source>`
HINT_LINE_RE = re.compile(r"^HINT\[([^\]]+)\] (\S+)(?: (verified|agrees))?$")
EXPORTED_MARK = "export_symbols.py"  # in the header of a .sym written by the exporter (symbols/p3fes.sym)

def parse_tags(tokens):
    """`key=value` tokens -> dict; bare `flirt` -> {'flirt': 'yes'}; a `# note` ends the tags."""
    tags = {}
    for t in tokens:
        if t.startswith("#"): break
        if "=" in t: k, v = t.split("=", 1); tags[k] = v
        elif t == "flirt": tags["flirt"] = "yes"
    return tags

def parse_sym(path, with_tags=False):
    """Rows (ea, size, kind, name) or, with_tags, (ea, size, kind, name, tags)."""
    rows = []
    for line in open(path, encoding="utf-8"):
        line = line.strip()
        if not line or line.startswith("#"): continue
        parts = line.split(None, 4)
        a, sz, kind, name = parts[:4]
        tags = parse_tags(parts[4].split()) if len(parts) > 4 else {}
        rows.append((int(a, 16), int(sz, 16), kind, name, tags) if with_tags else (int(a, 16), int(sz, 16), kind, name))
    return rows

def is_exported_sym(path):
    """True when the file's header (comment lines before the first row) names the exporter."""
    for line in open(path, encoding="utf-8"):
        if not line.startswith("#"): return False
        if EXPORTED_MARK in line: return True
    return False

def parse_chunks(path):
    """symbols/function_chunks.txt -> {start: ([(s, e), ...] main chunk first, [(ea, size), ...] data items)}."""
    out = {}
    for line in open(path, encoding="utf-8"):
        toks = line.split()
        if not toks or toks[0].startswith("#"): continue
        i = toks.index("C") + 1; ranges = []; data = []
        while i < len(toks) and toks[i] != "D":
            s, e = toks[i].split("-"); ranges.append((int(s, 16), int(e, 16))); i += 1
        for t in toks[i + 1:]:
            a, sz = t.split(":"); data.append((int(a, 16), int(sz)))
        out[int(toks[0], 16)] = (ranges, data)
    return out

def parse_comments(path):
    """`# comment <addr8> <text>` lines -> [(ea, text)]."""
    out = []
    for line in open(path, encoding="utf-8"):
        m = COMMENT_LINE_RE.match(line.strip())
        if m: out.append((int(m.group(1), 16), m.group(2)))
    return out

def apply_comment(ea, text):
    """Function comment at a function start, repeatable comment elsewhere; idempotent on identical text."""
    import ida_bytes, ida_funcs
    f = ida_funcs.get_func(ea)
    if f is not None and f.start_ea == ea:
        cur = ida_funcs.get_func_cmt(f, False) or ""
        if text in cur: return False
        ida_funcs.set_func_cmt(f, (cur + "\n" + text).strip() if cur else text, False); return True
    cur = ida_bytes.get_cmt(ea, True) or ""
    if text in cur: return False
    ida_bytes.set_cmt(ea, (cur + "\n" + text).strip() if cur else text, True); return True

def data_flag(size):
    import ida_bytes
    return {1: ida_bytes.byte_flag(), 2: ida_bytes.word_flag(), 4: ida_bytes.dword_flag(),
            8: ida_bytes.qword_flag(), 16: ida_bytes.oword_flag()}.get(size, ida_bytes.byte_flag())

def ensure_head(ea, size, kind="D", exact=False):
    """Make `ea` an item head so an authoritative D/L row can be named there.
    Topic deltas name globals that IDA buried inside auto-sized .bss/data blocks; splitting the containing
    item is the right fix for OUR rows (hint rows never change layout, see apply_hint).
    `exact` (exported file): a D row is also re-created when the item here has another size than the export
    (the whole range [ea, ea+size) is cleared first -- the VU1 microcode labels lie inside IDA's mis-disassembled
    code items, where clearing only the containing item left create_data refused), and an L row becomes an
    instruction head."""
    import ida_bytes, ida_idaapi, ida_ua
    fl = ida_bytes.get_flags(ea)
    if ida_bytes.is_head(fl) and not (exact and kind == "D" and size > 0 and ida_bytes.get_item_size(ea) != size):
        return True
    head = ea if ida_bytes.is_head(fl) else ida_bytes.get_item_head(ea)
    if kind == "L":
        ida_bytes.del_items(head, ida_bytes.DELIT_EXPAND, max(ea + 4 - head, 4))
        ida_ua.create_insn(ea)
        return ida_bytes.is_head(ida_bytes.get_flags(ea))
    span = (ea + size - head) if exact and size > 0 else ida_bytes.get_item_size(head)
    ida_bytes.del_items(head, ida_bytes.DELIT_SIMPLE, max(span, 1))
    if size > 0:
        ida_bytes.create_data(ea, data_flag(size), size, ida_idaapi.BADADDR)
    return ida_bytes.is_head(ida_bytes.get_flags(ea))

def set_ev_comment(ea, source, anchor):
    """Record `EV[<source>] <anchor>` once in the repeatable comment at ea."""
    import ida_bytes
    line = f"EV[{source}] {anchor}"
    cur = ida_bytes.get_cmt(ea, True) or ""
    if line in cur: return False
    ida_bytes.set_cmt(ea, (cur + "\n" + line).strip() if cur else line, True); return True

def parse_hint_comment(cmt):
    """Repeatable-comment text -> [(source, name, flag)] with flag in {"", "agrees", "verified"}."""
    out = []
    for ln in (cmt or "").splitlines():
        m = HINT_LINE_RE.match(ln.strip())
        if m: out.append((m.group(1), m.group(2), m.group(3) or ""))
    return out

# ---- export side of ADR-0009: which names may leave the database (every exporter writing a committed file uses this)
IDENT_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")

def load_manual_addresses(path):
    """Addresses named by names_manual.txt (analyst authority: a hint matching one counts as verified)."""
    out = set()
    if path and os.path.exists(path):
        for line in open(path, encoding="utf-8"):
            line = line.split("#", 1)[0].strip()
            if line: out.add(int(line.split()[0], 16))
    return out

def hint_status(ea, name, manual=frozenset()):
    """(source, exportable) if a hint PLACED `name` at ea (comment line without `agrees`), else None.
    Exportable: the source is permissive, the line says `verified`, or names_manual.txt owns the address.
    IDA may have suffixed the applied name (`_0`) on a clash, so the match ignores a trailing `_<digits>`."""
    import ida_bytes
    base = re.sub(r"_\d+$", "", name)
    placed = [(src, flag == "verified" or src in PERMISSIVE_SOURCES or ea in manual)
              for src, hname, flag in parse_hint_comment(ida_bytes.get_cmt(ea, True))
              if hname in (name, base) and flag != "agrees"]
    if not placed: return None
    ok = [src for src, good in placed if good]
    return (ok[0], True) if ok else (placed[0][0], False)

def withheld_name_map(manual=frozenset()):
    """{name: exported form} for every database name an unexportable hint placed: functions -> `sub_<EA>`,
    code labels -> `loc_<EA>`, data -> `data_<EA>` (the forms export_symbols.py writes)."""
    import idautils, ida_bytes, ida_funcs
    out = {}; fstarts = set()
    for fea in idautils.Functions():
        fstarts.add(fea); nm = ida_funcs.get_func_name(fea); hs = hint_status(fea, nm, manual)
        if hs is not None and not hs[1]: out[nm] = f"sub_{fea:X}"
    for ea, nm in idautils.Names():
        if ea in fstarts: continue
        hs = hint_status(ea, nm, manual)
        if hs is not None and not hs[1]:
            out[nm] = f"{'loc' if ida_bytes.is_code(ida_bytes.get_flags(ea)) else 'data'}_{ea:X}"
    return out

def scrub_names(text, withheld):
    """Free text (listings, operands) with every withheld name replaced by its exported form."""
    return IDENT_RE.sub(lambda m: withheld.get(m.group(0), m.group(0)), text) if withheld else text

def export_disasm(ea, withheld):
    """IDA's disassembly of the item at ea for a committed file: comments dropped (`#` on MIPS, `;` elsewhere;
    they carry HINT/EV lines) and withheld names replaced."""
    import idc
    return scrub_names(re.split(r"[#;]", idc.GetDisasm(ea), 1)[0].strip(), withheld)

THUNK_RE = re.compile(r"^j_")  # IDA derives `j_<target>` thunk names itself (flagged as user names), so hints may replace them

def has_user_name_at(ea):
    """True when the address carries a name a hint must not overwrite (ours, FLIRT, or any non-auto name)."""
    import ida_bytes, ida_name
    fl = ida_bytes.get_flags(ea); nm = ida_name.get_name(ea)
    if not nm or AUTO_RE.match(nm) or THUNK_RE.match(nm): return False
    return True  # named and not an IDA-generated form (the FF_NAME flag alone cannot tell: IDA thunk names carry it too)

def set_hint_comment(ea, source, name, marker=""):
    """Idempotently record `HINT[source] name[ marker]` in the repeatable comment at ea.
    An existing line for the same (source, name) is kept as it is unless `marker` upgrades it to `verified`."""
    import ida_bytes
    cur = ida_bytes.get_cmt(ea, True) or ""
    lines = [l for l in cur.splitlines() if l.strip()]
    for i, l in enumerate(lines):
        m = HINT_LINE_RE.match(l.strip())
        if m and m.group(1) == source and m.group(2) == name:
            if marker == "verified" and m.group(3) != "verified":
                lines[i] = f"HINT[{source}] {name} verified"; ida_bytes.set_cmt(ea, "\n".join(lines), True); return True
            return False
    lines.append(f"HINT[{source}] {name}" + (f" {marker}" if marker else ""))
    ida_bytes.set_cmt(ea, "\n".join(lines), True)
    return True

def apply_hint(ea, kind, name, source, verified, log, dry_run=False):
    """Apply one hint row. Returns status: named | same | conflict | no_func | mid_item | failed.
    Hints never overwrite a user/FLIRT name (`conflict`); `verified` rows do (promotion).
    Item layout is never changed: an F hint where no function starts (`no_func`) and a D/L hint inside an
    existing item (`mid_item`) get the comment only."""
    import ida_funcs, ida_name, ida_bytes
    marker = "verified" if verified else ""
    if kind == "F":
        f = ida_funcs.get_func(ea)
        if f is None or f.start_ea != ea:
            if not dry_run: set_hint_comment(ea, source, name, marker)
            return "no_func"
    elif not ida_bytes.is_head(ida_bytes.get_flags(ea)):
        if not dry_run: set_hint_comment(ea, source, name, marker)
        return "mid_item"
    cur = ida_name.get_name(ea) or ""
    if cur == name: status = "same"
    elif has_user_name_at(ea) and not verified: status = "conflict"
    else: status = "named"
    if dry_run: return status
    # `same` with no prior HINT line for this (source, name): the name was ours/FLIRT's -> record agreement only
    if status == "same" and not marker and not any(s == source and n == name for s, n, _ in parse_hint_comment(ida_bytes.get_cmt(ea, True))):
        marker = "agrees"
    set_hint_comment(ea, source, name, marker)
    if status == "named":
        if not ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            log(f"  FAILED hint set_name {ea:#x} {name} ({source})"); return "failed"
        got = ida_name.get_name(ea)
        if got != name: log(f"  clash: hint {ea:#x} wanted {name} got {got} ({source})")
    return status

# ---- function layout (exported file + --create-funcs)
def cut_chunk_at(ea, log):
    """A function start of the reference lies inside another function's chunk here: end that chunk at ea
    (main chunk: set_func_end; tail: re-append the part before ea). Returns True when ea is no longer inside."""
    import ida_funcs
    f = ida_funcs.get_func(ea)
    if f is None or f.start_ea == ea: return True
    ch = ida_funcs.get_fchunk(ea)
    if ch is not None and ida_funcs.is_func_tail(ch):
        s = ch.start_ea
        owners = []
        it = ida_funcs.func_parent_iterator_t(ch)
        ok = it.first()
        while ok: owners.append(it.parent()); ok = it.next()
        for o in owners:
            of = ida_funcs.get_func(o)
            ida_funcs.remove_func_tail(of, s)
            if s < ea: ida_funcs.append_func_tail(of, s, ea)
        log(f"  cut tail {s:#x} of {[hex(o) for o in owners]} at {ea:#x}")
    else:
        ida_funcs.set_func_end(f.start_ea, ea)
        log(f"  cut {ida_funcs.get_func_name(f.start_ea)} {f.start_ea:#x} at {ea:#x}")
    g = ida_funcs.get_func(ea)
    return g is None or g.start_ea == ea

def create_function(ea, end, log):
    """Make a function start at ea; `end` = its main-chunk end when known (BADADDR: let IDA find it).
    Escalates like create_funcs.py: decode the bytes if IDA typed them as data, add_func, auto_make_code +
    add_func, then undefine/decode the whole [ea, end) (clamped to the next function) and add_func again."""
    import ida_funcs, ida_bytes, ida_ua, ida_auto, ida_idaapi
    f = ida_funcs.get_func(ea)
    if f is not None and f.start_ea == ea: return True
    if f is not None and not cut_chunk_at(ea, log): return False
    def try_add():
        return ida_funcs.add_func(ea, end) if end != ida_idaapi.BADADDR else ida_funcs.add_func(ea)
    if not ida_bytes.is_code(ida_bytes.get_flags(ea)):
        ida_bytes.del_items(ea, ida_bytes.DELIT_EXPAND, 4); ida_ua.create_insn(ea); ida_auto.auto_wait()
    if try_add(): return True
    ida_auto.auto_make_code(ea); ida_auto.auto_wait()
    if try_add(): return True
    if end == ida_idaapi.BADADDR: return False
    nxt = ida_funcs.get_next_func(ea)
    e2 = min(end, nxt.start_ea) if nxt else end
    ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, e2 - ea)
    for a in range(ea, e2, 4): ida_ua.create_insn(a)
    ida_auto.auto_wait()
    return bool(ida_funcs.add_func(ea, e2))

def set_lib_flag(ea, lib):
    """FUNC_LIB on/off for the function at ea (the exporter derives the `flirt` tag from it). True if changed."""
    import ida_funcs
    f = ida_funcs.get_func(ea)
    if f is None or f.start_ea != ea: return False
    if bool(f.flags & ida_funcs.FUNC_LIB) == lib: return False
    f.flags = (f.flags | ida_funcs.FUNC_LIB) if lib else (f.flags & ~ida_funcs.FUNC_LIB)
    ida_funcs.update_func(f); return True

def prune_functions(keep, log):
    """Delete every function whose start is not in `keep` (the exported F rows are ALL the master's functions).
    IDA's dummy name of a deleted function is cleared so it does not come back as a data name."""
    import idautils, ida_funcs, ida_name, ida_bytes
    gone = []
    for fea in list(idautils.Functions()):
        if fea in keep: continue
        nm = ida_funcs.get_func_name(fea)
        if ida_funcs.del_func(fea):
            if not ida_bytes.has_user_name(ida_bytes.get_flags(fea)) or AUTO_RE.match(nm or ""):
                ida_name.set_name(fea, "", ida_name.SN_NOWARN)
            gone.append((fea, nm))
        else: log(f"  FAILED del_func {fea:#x} {nm}")
    if gone: log(f"  pruned {len(gone)} functions not in the file: {[(hex(e), n) for e, n in gone[:20]]}{' ...' if len(gone) > 20 else ''}")
    return len(gone)

def current_layout(start):
    """([(s, e)...] main first, [(ea, size)...]) of the function at start, as export_function_chunks.py sees it."""
    import idautils, ida_bytes
    ranges = [(s, e) for s, e in idautils.Chunks(start)]
    data = [(ea, ida_bytes.get_item_size(ea)) for s, e in ranges for ea in idautils.Heads(s, e)
            if not ida_bytes.is_code(ida_bytes.get_flags(ea))]
    return ranges, data

def apply_chunks(chunks, log):
    """Set every function's main-chunk end, tails and data items inside its chunks to the reference layout.
    Pass 1 fixes main ends and removes extra tails (so no range is still owned elsewhere), pass 2 appends the
    missing tails (shared tails are appended to every owner), pass 3 makes the words inside chunks instructions
    where the reference has code and data items of the exported size where it has data."""
    import ida_funcs, ida_bytes, ida_ua, ida_auto, ida_idaapi, idautils
    st = dict(main_end_set=0, tails_removed=0, tails_added=0, words_to_code=0, items_to_data=0, failed=0, no_func=0)
    for start, (ranges, _) in chunks.items():
        f = ida_funcs.get_func(start)
        if f is None or f.start_ea != start: st["no_func"] += 1; continue
        if f.end_ea != ranges[0][1]:
            if ida_funcs.set_func_end(start, ranges[0][1]): st["main_end_set"] += 1
            else: st["failed"] += 1; log(f"  FAILED set_func_end {start:#x} -> {ranges[0][1]:#x} (is {f.end_ea:#x})")
        want = set(ranges[1:])
        for s, e in [(s, e) for s, e in idautils.Chunks(start)][1:]:
            if (s, e) not in want:
                if ida_funcs.remove_func_tail(ida_funcs.get_func(start), s): st["tails_removed"] += 1
                else: st["failed"] += 1; log(f"  FAILED remove_func_tail {start:#x} {s:#x}-{e:#x}")
    for start, (ranges, _) in chunks.items():
        f = ida_funcs.get_func(start)
        if f is None or f.start_ea != start: continue
        have = set([(s, e) for s, e in idautils.Chunks(start)][1:])
        for s, e in ranges[1:]:
            if (s, e) in have: continue
            if not ida_bytes.is_code(ida_bytes.get_flags(s)):
                ida_bytes.del_items(s, ida_bytes.DELIT_SIMPLE, e - s)
                for a in range(s, e, 4): ida_ua.create_insn(a)
            if ida_funcs.append_func_tail(f, s, e): st["tails_added"] += 1
            else: st["failed"] += 1; log(f"  FAILED append_func_tail {start:#x} {s:#x}-{e:#x}")
    ida_auto.auto_wait()
    for start, (ranges, data) in chunks.items():
        f = ida_funcs.get_func(start)
        if f is None or f.start_ea != start: continue
        want = dict(data)
        for ea, sz in current_layout(start)[1]:
            if want.get(ea) == sz: continue
            # a data item the reference does not have (or has with another size): back to instructions
            ida_bytes.del_items(ea, ida_bytes.DELIT_SIMPLE, sz)
            if ea not in want:
                for a in range(ea, ea + sz, 4): ida_ua.create_insn(a)
                st["words_to_code"] += 1
        have = dict(current_layout(start)[1])
        for ea, sz in data:
            if have.get(ea) == sz: continue
            head = ida_bytes.get_item_head(ea)
            ida_bytes.del_items(head, ida_bytes.DELIT_SIMPLE, ea + sz - head)
            if ida_bytes.create_data(ea, data_flag(sz), sz, ida_idaapi.BADADDR): st["items_to_data"] += 1
            else: st["failed"] += 1; log(f"  FAILED create_data {ea:#x} size {sz} in {start:#x}")
        if any(ea not in have or have[ea] != sz for ea, sz in data) or len(have) != len(data):
            ida_funcs.reanalyze_function(ida_funcs.get_func(start))
    ida_auto.auto_wait()
    return st

def verify_chunks(chunks, log):
    """Count functions whose chunk ranges / data items still differ from the reference (logs the first 20)."""
    import ida_funcs
    bad = []
    for start, (ranges, data) in chunks.items():
        f = ida_funcs.get_func(start)
        if f is None or f.start_ea != start: bad.append((start, "missing")); continue
        cr, cd = current_layout(start)
        if cr != ranges: bad.append((start, f"chunks {[(hex(s), hex(e)) for s, e in cr]} != {[(hex(s), hex(e)) for s, e in ranges]}"))
        elif cd != data: bad.append((start, f"data {[(hex(a), s) for a, s in cd]} != {[(hex(a), s) for a, s in data]}"))
    for start, why in bad[:20]: log(f"  layout differs {start:#x}: {why}")
    return len(bad)

def apply_rows(rows, create_funcs, log, exported=False, chunks=None):
    """Apply parsed rows. `exported`: the file is the exporter's own output (see module docstring);
    `chunks`: parse_chunks() of function_chunks.txt (exact main-chunk ends for --create-funcs)."""
    import ida_funcs, ida_name, ida_idaapi
    stats = dict(funcs_created=0, funcs_failed=0, names_set=0, names_same=0, names_failed=0, auto_skipped=0, ev_recorded=0,
                 hints_named=0, hints_same=0, hints_conflict=0, hints_no_func=0, hints_mid_item=0, hints_promoted=0,
                 lib_flags=0, dummy_pinned=0)
    pins = []  # exported file: `sub_<EA>` rows to pin after every other name is set (pin_dummy_names)
    for row in rows:
        ea, sz, kind, name = row[:4]; tags = row[4] if len(row) > 4 else {}
        hint = "source" in tags and not OUR_SOURCE_RE.match(tags["source"])  # community row (ADR-0009)
        if hint and not exported:  # hint file: `verified=yes` promotes it, anything else is a hint
            verified = tags.get("verified") == "yes"
            st = apply_hint(ea, kind, name, tags["source"], verified, log)
            if st == "failed": stats["names_failed"] += 1
            else: stats["hints_" + st] += 1
            if verified and st in ("named", "same"): stats["hints_promoted"] += 1
            continue
        if kind == "F":
            f = ida_funcs.get_func(ea)
            if create_funcs and (f is None or f.start_ea != ea):
                if chunks and ea in chunks: end = chunks[ea][0][0][1]
                elif f is None and (sz or not exported): end = ea + sz if sz else ida_idaapi.BADADDR
                else: end = ida_idaapi.BADADDR
                if exported:
                    if create_function(ea, end, log): stats["funcs_created"] += 1
                    else: stats["funcs_failed"] += 1; log(f"  FAILED to create function {ea:#x} {name}")
                elif f is None and ida_funcs.add_func(ea, end):
                    stats["funcs_created"] += 1
            if exported and set_lib_flag(ea, tags.get("flirt") == "yes"): stats["lib_flags"] += 1
        if "ev" in tags and set_ev_comment(ea, tags.get("source", "manual"), tags["ev"]):
            stats["ev_recorded"] += 1
        if kind == "F":
            if AUTO_RE.match(name):
                stats["auto_skipped"] += 1
                if exported and name == f"sub_{ea:X}": pins.append(ea)
                continue
        elif not ensure_head(ea, sz, kind, exact=exported):
            stats["names_failed"] += 1; log(f"  FAILED to make an item head at {ea:#x} for {name}"); continue
        if ida_name.get_name(ea) == name: stats["names_same"] += 1
        elif ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            got = ida_name.get_name(ea)
            if got != name: log(f"  clash: {ea:#x} wanted {name} got {got}")
            stats["names_set"] += 1
        else:
            stats["names_failed"] += 1; log(f"  FAILED set_name {ea:#x} {name}"); continue
        if hint:  # exported file: the row passed the export rule -> restore it as the promotion it is
            set_hint_comment(ea, tags["source"], name, "" if tags["source"] in PERMISSIVE_SOURCES else "verified")
            stats["hints_promoted"] += 1
    stats["dummy_pinned"] = pin_dummy_names(pins, log)
    return stats

def pin_dummy_names(eas, log):
    """Exported file: a `sub_<EA>` row whose IDA dummy name here is another form (nullsub_N, or j_<target> for a
    thunk) -- the master withholds an unverified hint there and exports sub_<EA>; pin that form as the name so the
    exports agree. Done after every other name is set: IDA regenerates a thunk's j_<target> name when the target
    is renamed, which undid a pin made before the target's row."""
    import ida_funcs, ida_name
    n = 0
    for ea in eas:
        f = ida_funcs.get_func(ea); name = f"sub_{ea:X}"
        if f is None or f.start_ea != ea or ida_name.get_name(ea) == name: continue
        if ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_FORCE): n += 1
        else: log(f"  could not pin {name} over {ida_name.get_name(ea)}")
    return n

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("i64"); ap.add_argument("sym")
    ap.add_argument("--no-save", action="store_true"); ap.add_argument("--create-funcs", action="store_true")
    ap.add_argument("--chunks", default=None, help="symbols/function_chunks.txt (exported file only; default: the one next to the .sym)")
    ap.add_argument("--as-hints", action="store_true", help="treat an exported .sym like a hint file (no promotion/layout restore)")
    a = ap.parse_args()
    i64 = os.path.abspath(a.i64)
    logdir = os.path.join(os.path.dirname(i64), "logs"); os.makedirs(logdir, exist_ok=True)
    lf = open(os.path.join(logdir, "import.log"), "a", encoding="utf-8")
    def log(m): print(m, flush=True); lf.write(f"[{time.strftime('%H:%M:%S')}] {m}\n")
    rows = parse_sym(a.sym, with_tags=True); log(f"import {a.sym}: {len(rows)} rows into {i64}")
    exported = is_exported_sym(a.sym) and not a.as_hints
    chunks = None
    if exported:
        cpath = a.chunks or os.path.join(os.path.dirname(os.path.abspath(a.sym)), "function_chunks.txt")
        if a.create_funcs and os.path.exists(cpath):
            chunks = parse_chunks(cpath); log(f"exported file: restoring promotions, FUNC_LIB and the layout of {len(chunks)} functions from {cpath}")
        else: log("exported file: restoring promotions and FUNC_LIB" + ("" if a.create_funcs else " (no --create-funcs: layout untouched)"))
    idapro.enable_console_messages(False)
    rc = idapro.open_database(i64, False)
    if rc != 0: log(f"open failed rc={rc}"); sys.exit(rc)
    import ida_auto
    stats = apply_rows(rows, a.create_funcs, log, exported=exported, chunks=chunks)
    if exported and a.create_funcs:
        ida_auto.auto_wait()
        keep = {r[0] for r in rows if r[2] == "F"}
        stats["pruned"] = prune_functions(keep, log)
        if chunks:
            stats["layout"] = apply_chunks(chunks, log)
            stats["pruned"] += prune_functions(keep, log)  # analysis after the layout pass may have added functions
            ida_auto.auto_wait()
            stats["layout_differs"] = verify_chunks(chunks, log)
    comments = parse_comments(a.sym)
    stats["comments_applied"] = sum(1 for ea, text in comments if apply_comment(ea, text))
    stats["comments_total"] = len(comments)
    log(f"result: {stats}")
    idapro.close_database(not a.no_save)
    sys.exit(1 if stats["names_failed"] or stats["funcs_failed"] else 0)

if __name__ == "__main__":
    main()
