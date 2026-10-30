"""Convert community symbol maps into private hint files (ADR-0009) and compare their function
boundaries with ours.

Plain CPython (no IDA). Run with `-I` because the inputs are untrusted third-party data:

  python -I tools/ours/ida/hints_convert.py --root . \
      --snaku tools/third_party/_community-eval/snaku \
      --pr4-rev pr4 \
      --fes-pc-recomp tools/third_party/_community-eval/fes-pc-recomp \
      [--compare symbols/functions.json] [--no-write]

Writes (all gitignored):
  symbols/hints/snaku.sym, symbols/hints/tge-pr4.sym, symbols/hints/fes-pc-recomp.sym
  ida/logs/hints_convert.log, ida/logs/hints_boundary.md (with --compare), ida/logs/hints_convert.json

Hint `.sym` line format = the project's `.sym` format plus tags:
  <addr8> <size8> <F|D|L> <name> source=<src> [module=<splat module>] [cite=<doc:line>] [# free text]
  * `source=` marks the row as a HINT: `import_symbols.py` applies it only onto IDA auto names and never
    over a user/FLIRT name. Promotion = append `verified=yes` to that one line (see import_symbols.py).
  * splat `type:func/data/label` -> F/D/L (no type -> D); splat `size:0x..` -> size8 (else 0).
  * Placeholder names are dropped: `func_XXXXXXXX`, `D_XXXXXXXX`, `jpt_*`, `lbl_*`, `jtbl_*`, `.L*`, and any
    name whose trailing hex token is its own address (`h_cdvd_00101100`, `libadxe_adx_dcd_0043976x`,
    `gUnk_007cad7c`, `sNextId_7CC530`).
Nothing here may be copied into symbols/p3fes.sym or docs/ (ADR-0009 §1-2); fes-pc-recomp (MIT) rows are
the only promotable-by-license source (§2a).
"""
import argparse, collections, hashlib, json, os, re, subprocess, sys, time

ELF_REL = os.path.join("extracted", "disc", "SLUS_216.21")
SPLAT_LINE = re.compile(r"^\s*([A-Za-z_.$][\w.$-]*)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*(?://\s*(.*))?$")
PLACEHOLDER_RE = re.compile(r"^(func_[0-9A-Fa-f]{6,8}|D_[0-9A-Fa-f]{6,8}|jpt_|lbl_|jtbl_|\.L|L[0-9A-Fa-f]{6,8}$|loc_|sub_|nullsub_|off_|unk_|byte_|word_|dword_)")
TRAIL_HEX_RE = re.compile(r"_([0-9A-Fa-f]{6,8}|[0-9A-Fa-f]{7}x)$")
KIND = {"func": "F", "data": "D", "label": "L"}

# Address bands from docs/ANALYSIS/03_strings_of_interest.md (leaked source-file table + SDK library strings).
# Half-open [start, end). Gaps are reported as "other game code".
BANDS = [
    (0x100000, 0x103DA0, "crt0 / h_cursor / h_cdvd (pre-band)"),
    (0x103DA0, 0x191AF0, "h_* camp/memory/fade/Sofdec/sound"),
    (0x1939D0, 0x198C60, "kwln* task kernel"),
    (0x199440, 0x1D9860, "k_* field/dungeon"),
    (0x1EF7F0, 0x27BBA0, "br_/bp_/sfl_/gc_/op_ battle UI, shuffle, title"),
    (0x28DBF0, 0x30FC40, "btl*/dat* battle core"),
    (0x35AEF0, 0x35F680, "scr* BF script VM"),
    (0x361350, 0x3BAC40, "mt_evt*/mt_scene*/itf*/fr* event+UI"),
    (0x3BDBD0, 0x4176F0, "comu*/nm*/fcl* social, fusion, shops"),
    (0x46F400, 0x470E10, "G3_2D*_Node renderer"),
    (0x470E10, 0x4F9168, "0x470E10..0x4F9168 engine/RenderWare (inferred)"),
    (0x4F9168, 0x51D460, "SCE SDK libs (libgraph..libdbc)"),
    (0x51D460, 0x5A0000, "0x51D460..0x5A0000 CRI/libc/other libs (inferred)"),
    (0x5A0000, 0xA00000, "data (.data/.rodata/.bss, VU1 microcode)"),
]
def band_of(ea):
    for lo, hi, label in BANDS:
        if lo <= ea < hi: return label
    return "other game code (between bands)"

def sha256(p):
    h = hashlib.sha256()
    with open(p, "rb") as f:
        for c in iter(lambda: f.read(1 << 20), b""): h.update(c)
    return h.hexdigest()

def is_placeholder(name, ea):
    if PLACEHOLDER_RE.match(name): return True
    m = TRAIL_HEX_RE.search(name)
    if m:
        tok = m.group(1).lower()
        if tok.endswith("x"): return int(tok[:-1], 16) == (ea >> 4)
        return int(tok, 16) == ea
    return False

def parse_splat(text, source):
    """Yield (ea, size, kind, name, module) for descriptive symbols; return stats."""
    rows, st = [], collections.Counter()
    module = ""
    seen = {}
    all_funcs = []  # every type:func start incl. placeholders (addresses are boundary facts, names are not)
    for ln in text.splitlines():
        s = ln.strip()
        if not s: continue
        if s.startswith("//"):
            module = s[2:].strip(); continue
        m = SPLAT_LINE.match(s)
        if not m: st["unparsed"] += 1; continue
        name, ea, attrs = m.group(1), int(m.group(2), 16), (m.group(3) or "")
        st["total"] += 1
        typ = re.search(r"type:(\w+)", attrs); sz = re.search(r"size:0x([0-9A-Fa-f]+)", attrs)
        kind = KIND.get(typ.group(1), "D") if typ else "D"
        st["kind_" + kind] += 1
        if sz: st["with_size"] += 1
        if kind == "F": all_funcs.append((ea, int(sz.group(1), 16) if sz else 0))
        if is_placeholder(name, ea): st["placeholder_dropped"] += 1; continue
        if ea in seen:
            st["dup_addr_dropped"] += 1; continue
        seen[ea] = name
        rows.append((ea, int(sz.group(1), 16) if sz else 0, kind, name, module))
    st["descriptive_kept"] = len(rows)
    rows.sort(); all_funcs = sorted(set(all_funcs))
    return rows, st, all_funcs

def git_show(clone, rev, relpath):
    out = subprocess.run(["git", "-C", clone, "show", f"{rev}:{relpath}"], capture_output=True, check=True)
    return out.stdout.decode("utf-8", "replace")

def git_head(clone, rev="HEAD"):
    return subprocess.run(["git", "-C", clone, "rev-parse", rev], capture_output=True, text=True, check=True).stdout.strip()

# fes-pc-recomp (MIT) address-level findings. Names the project itself uses are kept verbatim (cvFs*);
# role names coined here from its prose carry the project's `_candidate` suffix (inference, not verified).
# cite = file:line in the clone at the recorded commit.
FES_PC_RECOMP = [
    # file layer
    (0x100D80, 0x140, "F", "fileRequestGet_candidate", "docs/formats.md:567,573", "logs `REQ CDVD %s`; 218 callers; looks up/allocates 868-byte request object in list at 0x7E0380"),
    (0x100EC0, 0, "F", "fileRequestState_candidate", "docs/formats.md:573", "neighbour handling request-object state (counters at +860)"),
    (0x101240, 0, "F", "fileRequestSplitPath_candidate", "docs/formats.md:573", "splits request path into parts at +344/+600"),
    (0x7E0380, 4, "D", "fileRequestListHead_candidate", "docs/formats.md:573", "linked-list head of file request objects"),
    (0x960184, 4, "D", "fileRequestAllocFn_candidate", "docs/formats.md:573", "allocator function pointer used for 868-byte request objects"),
    (0x555B10, 0, "F", "cvFsAddDev", "docs/formats.md:568,575", "CRI cvFs: registers a device (name, interface name)"),
    (0x555FA0, 0, "F", "cvFsFindDevByName_candidate", "docs/formats.md:574", "finds device by name"),
    (0x5561E8, 0, "F", "cvFsSplitDevicePath_candidate", "docs/formats.md:574", "splits `device:\\rest`"),
    (0x556048, 0, "F", "cvFsOpen", "docs/formats.md:568,574", "CRI cvFs: open(path, mode, option) via device vtable +16"),
    (0x5564E0, 0, "F", "cvFsReqRd", "docs/formats.md:568,575", "CRI cvFs: read request via device vtable +32"),
    (0x997518, 0x140, "D", "cvFsHandleTable", "docs/formats.md:574", "40 handles x 8 bytes (device, device handle)"),
    (0x565E10, 0, "F", "ROFS_driver_first_candidate", "docs/formats.md:568", "start of `ROFS_*` read-only archive driver 0x565E10..0x56C5F0"),
    # frame pacing
    (0x4D47F0, 0, "F", "vblankStartHandler_candidate", "docs/formats.md:599", "VBLANK-start INTC handler; flips display buffers after drawn-flag/counter check"),
    (0x4D4350, 0, "F", "dmaEndHandler_candidate", "docs/formats.md:599", "DMA-end handler for channels 1 and 2"),
    (0x4D6470, 0, "F", "installFrameIntHandlers_candidate", "docs/formats.md:599", "registers VBLANK handler 0x4D47F0 and DMA-end handlers 0x4D4350"),
    (0x4D67B0, 0, "F", "frameIntSetupCaller_candidate", "docs/formats.md:599", "sole caller of 0x4D6470; called from 0x4E1060"),
    (0x4D6A50, 0, "F", "clearFrameTarget_candidate", "docs/formats.md:599", "clears the frame-target byte"),
    (0x4E1060, 0, "F", "startupInit_candidate", "docs/formats.md:598,599", "start-up function calling 0x4D67B0 and 0x4F9938 once"),
    (0x4F94E0, 0, "F", "gsSetDisplayEnv_candidate", "docs/formats.md:599", "display environment function used by the VBLANK flip"),
    (0x4F9938, 0, "F", "gsSyncVWait_candidate", "docs/formats.md:598", "sole user of polling waits 0x5035F0/0x503680; returns odd/even field"),
    (0x5035F0, 0, "F", "vsyncPollWait0_candidate", "docs/formats.md:598", "clear VBLANK-start bit then poll, interrupts off"),
    (0x503680, 0, "F", "vsyncPollWait1_candidate", "docs/formats.md:598", "second polling wait"),
    (0x4241D0, 0, "F", "timer0TickRead_candidate", "docs/formats.md:600", "EE timer 0 tick reader called twice"),
    # BF script engine
    (0x30FDF0, 0, "F", "scrExecOpcode_candidate", "docs/formats.md:292", "35-way opcode dispatch through table 0x7B90A0"),
    (0x7B90A0, 35 * 4, "D", "scrOpcodeJumpTable_candidate", "docs/formats.md:292", "35 x 4-byte opcode jump table"),
    (0x7B92B0, 502 * 8, "D", "scrCommFunctionTable", "docs/formats.md:293; docs/script-functions.md:5; tools/p3fes_bf.py:646", "502 x 8-byte (function address, arg count) BF COMM table"),
    # VU1 microcode region
    (0x5A0000, 0, "L", "vu1MicrocodeRegionStart_candidate", "docs/formats.md:557,559", "VU microcode as data 0x5A0000..0x77xxxx: 383 blocks, 421 MPG uploads, 181 programs"),
]

def write_hint_file(path, rows, header_lines):
    with open(path, "w", encoding="utf-8", newline="\n") as fh:
        for h in header_lines: fh.write("# " + h + "\n")
        for r in rows: fh.write(r + "\n")

def compare_boundaries(func_rows_by_source, functions_json, log):
    """Third-opinion boundary comparison vs symbols/functions.json. Sizes on the community side are
    implied (next start - start, over ALL community func starts incl. placeholders) because splat sizes are
    essentially absent; labelled derived. `rows` = (ea, explicit_size) for every type:func entry."""
    ours = json.load(open(functions_json, encoding="utf-8"))
    our_start = {int(f["a"], 16): f for f in ours}
    our_sorted = sorted(our_start)
    out = ["<!-- generated by tools/ours/ida/hints_convert.py --compare; derived from gitignored hint files -->"]
    result = {}
    for src, rows in func_rows_by_source.items():
        starts = sorted(r[0] for r in rows)
        sset = set(starts)
        same = [a for a in starts if a in our_start]
        theirs_only = [a for a in starts if a not in our_start]
        ours_only = [a for a in our_sorted if a not in sset]
        # implied sizes: next start in the *same* list (community) vs IDA total size
        nxt = {a: b for a, b in zip(starts, starts[1:])}
        explicit = {r[0]: r[1] for r in rows if r[1]}
        deltas = []
        same_size = diff_size = ida_longer = comm_longer = 0
        for a in same:
            if a in explicit: theirs = explicit[a]; how = "explicit"
            elif a in nxt: theirs = nxt[a] - a; how = "implied"
            else: continue
            mine = our_start[a]["s"]
            if theirs == mine or (how == "implied" and 0 < theirs - mine < 16): same_size += 1  # <16 = alignment padding
            else:
                diff_size += 1
                if mine > theirs: ida_longer += 1
                else: comm_longer += 1
                deltas.append((abs(theirs - mine), a, mine, theirs, how, our_start[a]["n"]))
        deltas.sort(reverse=True)
        by_band_theirs = collections.Counter(band_of(a) for a in theirs_only)
        by_band_ours = collections.Counter(band_of(a) for a in ours_only)
        result[src] = dict(func_rows=len(rows), same_start=len(same), same_start_same_size=same_size,
                           same_start_diff_size=diff_size, ida_longer=ida_longer, community_longer=comm_longer,
                           community_only=len(theirs_only), ida_only=len(ours_only), explicit_sizes=len(explicit))
        log(f"compare {src}: {result[src]}")
        out.append(f"\n### {src} vs `symbols/functions.json` ({len(ours)} IDA functions)\n")
        out.append("| Metric | Count |\n|---|---|")
        out.append(f"| community `type:func` starts (all, incl. placeholder names) | {len(rows)} |")
        out.append(f"| same start address | {len(same)} |")
        out.append(f"| same start, consistent size (community size derived = next community start - start, matching within <16 bytes of alignment padding; {len(explicit)} explicit `size:`) | {same_size} |")
        out.append(f"| same start, different size (derived) | {diff_size} |")
        out.append(f"| ... IDA function longer than the community gap (IDA spans past the next community start: a merge/split disagreement) | {ida_longer} |")
        out.append(f"| ... community gap longer by >=16 bytes (IDA ends earlier: IDA split, or unreached code/data before the next community start) | {comm_longer} |")
        out.append(f"| community-only starts (no IDA function starts there) | {len(theirs_only)} |")
        out.append(f"| IDA-only starts (no community `type:func` there) | {len(ours_only)} |")
        out.append("\n**Disagreements by band** (start-address mismatches)\n\n| Band | community-only | IDA-only |\n|---|---|---|")
        for lo, hi, label in BANDS + [(0, 0, "other game code (between bands)")]:
            if by_band_theirs[label] or by_band_ours[label]:
                out.append(f"| {label} | {by_band_theirs[label]} | {by_band_ours[label]} |")
        out.append("\n**30 largest size deltas** (IDA total chunk size vs community derived size; `derived` = next community start minus start, so a gap or an unnamed placeholder in between inflates it)\n")
        out.append("| Address | IDA name | IDA size | community size | how | delta |\n|---|---|---|---|---|---|")
        for d, a, mine, theirs, how, nm in deltas[:30]:
            out.append(f"| `0x{a:06X}` | `{nm}` | {mine:#x} | {theirs:#x} | {how} | {d:#x} |")
        result[src]["top_deltas"] = [dict(ea=f"0x{a:06X}", ida=mine, community=theirs, how=how, name=nm) for d, a, mine, theirs, how, nm in deltas[:30]]
        result[src]["community_only_by_band"] = dict(by_band_theirs); result[src]["ida_only_by_band"] = dict(by_band_ours)
        result[src]["community_only_sample"] = [f"0x{a:06X}" for a in theirs_only[:12]]
    return "\n".join(out), result

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", default=".")
    ap.add_argument("--snaku", help="path of the snaku clone")
    ap.add_argument("--pr4-rev", default=None, help="git rev in the snaku clone holding PR #4 (e.g. pr4)")
    ap.add_argument("--fes-pc-recomp", help="path of the fes-pc-recomp clone (MIT)")
    ap.add_argument("--compare", default=None, help="symbols/functions.json for the boundary comparison")
    ap.add_argument("--no-write", action="store_true")
    a = ap.parse_args()
    root = os.path.abspath(a.root)
    hints_dir = os.path.join(root, "symbols", "hints"); logdir = os.path.join(root, "ida", "logs")
    os.makedirs(hints_dir, exist_ok=True); os.makedirs(logdir, exist_ok=True)
    lf = open(os.path.join(logdir, "hints_convert.log"), "a", encoding="utf-8")
    def log(m): lf.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] {m}\n"); lf.flush()
    elf = os.path.join(root, ELF_REL); elf_sha = sha256(elf) if os.path.exists(elf) else "unavailable"
    stamp = time.strftime("%Y-%m-%d %H:%M:%S")
    summary = {"elf_sha256": elf_sha, "generated": stamp, "sources": {}}
    func_rows = {}; all_funcs = {}

    def emit(src, rows, origin, commit, license_note, extra_header=()):
        hdr = [f"{src}.sym  private symbol HINTS for SLUS_216.21 (ADR-0009) -- never commit, never copy into symbols/p3fes.sym or docs/",
               f"origin {origin} commit {commit}", f"license {license_note}", f"ELF SHA-256 {elf_sha}",
               f"generated {stamp} by tools/ours/ida/hints_convert.py",
               "<addr8> <size8> <F|D|L> <name> source=<src> [module=..] [cite=..] [# note]   -- `source=` = hint (auto names only); add `verified=yes` to promote"] + list(extra_header)
        lines = []
        for ea, sz, kind, name, module in rows:
            tag = f"source={src}" + (f" module={module.replace(' ', '_')}" if module else "")
            lines.append(f"{ea:08x} {sz:08x} {kind} {name} {tag}")
        if not a.no_write: write_hint_file(os.path.join(hints_dir, f"{src}.sym"), lines, hdr)
        func_rows[src] = [r for r in rows if r[2] == "F"]

    if a.snaku:
        clone = os.path.abspath(a.snaku); rel = "config/SLUS_216.21/symbol_addrs.txt"
        text = open(os.path.join(clone, rel), encoding="utf-8", errors="replace").read()
        rows, st, allf = parse_splat(text, "snaku"); all_funcs["snaku"] = allf
        head = git_head(clone)
        emit("snaku", rows, "https://github.com/snaku/Persona3-FES-Decompilation " + rel, head, "NONE (all rights reserved) -> hints only, ADR-0009 S1")
        summary["sources"]["snaku"] = dict(st, commit=head); log(f"snaku {head}: {dict(st)}")
        if a.pr4_rev:
            try:
                text = git_show(clone, a.pr4_rev, rel); head4 = git_head(clone, a.pr4_rev)
                rows, st, allf = parse_splat(text, "tge-pr4"); all_funcs["tge-pr4"] = allf
                emit("tge-pr4", rows, f"https://github.com/snaku/Persona3-FES-Decompilation pull/4 (tge-was-taken) {rel}", head4, "NONE (all rights reserved) -> hints only, ADR-0009 S1")
                summary["sources"]["tge-pr4"] = dict(st, commit=head4); log(f"tge-pr4 {head4}: {dict(st)}")
            except subprocess.CalledProcessError as e:
                log(f"pr4 unavailable: {e}"); summary["sources"]["tge-pr4"] = {"error": "rev not available"}
    if a.fes_pc_recomp:
        clone = os.path.abspath(a.fes_pc_recomp); head = git_head(clone)
        rows = []
        lines = []
        for ea, sz, kind, name, cite, note in sorted(FES_PC_RECOMP):
            rows.append((ea, sz, kind, name, ""))
            lines.append(f"{ea:08x} {sz:08x} {kind} {name} source=fes-pc-recomp cite={cite.replace(' ', '')} # {note}")
        hdr = ["fes-pc-recomp.sym  symbol HINTS for SLUS_216.21 from Virtual-AK/fes-pc-recomp (MIT) -- promotable under ADR-0009 S2a with attribution",
               f"origin https://github.com/Virtual-AK/fes-pc-recomp docs/formats.md, docs/script-functions.md, tools/p3fes_bf.py commit {head}",
               "license MIT (LICENSE: Copyright (c) 2026 ps2-native-tools contributors)", f"ELF SHA-256 {elf_sha}",
               f"generated {stamp} by tools/ours/ida/hints_convert.py (curated table FES_PC_RECOMP)",
               "names without `_candidate` are the project's own identifiers (cvFs*); `_candidate` names are roles coined from its prose, unverified",
               "<addr8> <size8> <F|D|L> <name> source=fes-pc-recomp cite=<file:line> # note"]
        if not a.no_write: write_hint_file(os.path.join(hints_dir, "fes-pc-recomp.sym"), lines, hdr)
        func_rows["fes-pc-recomp"] = [r for r in rows if r[2] == "F"]
        st = collections.Counter(total=len(rows), descriptive_kept=len(rows), placeholder_dropped=0)
        for r in rows: st["kind_" + r[2]] += 1
        summary["sources"]["fes-pc-recomp"] = dict(st, commit=head); log(f"fes-pc-recomp {head}: {dict(st)}")
    if a.compare:
        md, res = compare_boundaries(all_funcs, os.path.join(root, a.compare), log)
        open(os.path.join(logdir, "hints_boundary.md"), "w", encoding="utf-8", newline="\n").write(md + "\n")
        summary["boundary"] = res
    json.dump(summary, open(os.path.join(logdir, "hints_convert.json"), "w", encoding="utf-8"), indent=1)
    for src, st in summary["sources"].items():
        print(f"{src}: total={st.get('total')} kept={st.get('descriptive_kept')} dropped={st.get('placeholder_dropped')} F={st.get('kind_F',0)} D={st.get('kind_D',0)} L={st.get('kind_L',0)} sized={st.get('with_size',0)}")
    if "boundary" in summary:
        for src, r in summary["boundary"].items():
            print(f"boundary {src}: same_start={r['same_start']} consistent_size={r['same_start_same_size']} diff_size={r['same_start_diff_size']} (ida_longer={r['ida_longer']} community_longer={r['community_longer']}) community_only={r['community_only']} ida_only={r['ida_only']}")

if __name__ == "__main__":
    main()
