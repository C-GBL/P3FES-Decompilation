"""Swap hand-written game/ functions for their register-faithful p3fes_handgen bodies, keeping documentation and API.

For every function of the plan (the audit's 'differs' rows, tools/ours/audit/audit_faithful.py; any number of files):
  * p3fes_handgen writes the faithful body (the original's frame, spills, $ra links, every register at every check
    point, cycles) and its recomp_gen shim;
  * the old shim is replaced by the generated one (a definition or a P3FES_*_SHIM(...) macro row); a function whose
    entry point is generated (game/forwarders.cmake: no shim in the sources) gets the one-line forwarder appended to
    the file, for tools/ours/phase5/forwarders.py to move into game/forwarders.txt (it records a `_regs` body name);
  * the old hand-written definition of the same name is replaced: its comment block (above it and at the top of its
    body) moves above the generated body; when the old typed C++ API is still called (by game/ code or tests/game),
    it stays as a thin wrapper that sets $a0.. ($f12.. for floats) as the original caller would and returns $v0 / $f0;
    otherwise it goes, and the header's declaration becomes the register-ABI one (its comment stays). "Still called"
    is decided on the original texts with every planned function's old definition and shim left out (callers that are
    replaced in the same run do not count);
  * the callee declarations and hg_cpu.h are added.
Whatever it cannot place (no definition under the functions.json name, host-pointer parameters, ...) is listed as
MANUAL: those need a hand edit. Nothing is built here.

  python -I tools/ours/audit/regen_faithful.py --handgen build/x/bin/p3fes_handgen.exe --plan plan.tsv [--dry-run]
  plan.tsv: '<game/src/... file>\t<hex start>\t<note, e.g. the audit classes>' per function.
Afterwards: run tools/ours/phase5/forwarders.py (the forwarders out of the sources again), build, then remove the
helpers the compiler reports unused (C4505 / -Wunused-function) and handle MANUAL.
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fix_decls  # noqa: E402
import fix_hg  # noqa: E402

HG_NAMES = fix_hg.hg_names()

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
ELF = r"F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21"


# --- C++ text helpers ---------------------------------------------------------------------------------------------

def blank_comments(text):
    """The text with comments, string and char literals replaced by spaces (offsets kept)."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif c in "\"'":
            if c == "'" and i > 0 and (text[i - 1].isalnum()):  # digit separator 1'000
                i += 1
                continue
            j = i + 1
            while j < n and text[j] != c:
                if text[j] == "\\":
                    j += 1
                elif text[j] == "\n":
                    break
                j += 1
            for k in range(i + 1, min(j, n)):
                out[k] = " "
            i = j + 1
        else:
            i += 1
    return "".join(out)


def match_brace(clean, open_at):
    depth = 0
    for i in range(open_at, len(clean)):
        if clean[i] == "{":
            depth += 1
        elif clean[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    return -1


def line_start(text, pos):
    return text.rfind("\n", 0, pos) + 1


def line_end(text, pos):
    j = text.find("\n", pos)
    return len(text) if j < 0 else j + 1


def leading_comment(text, start):
    """Start offset of the contiguous // comment block right above `start` (a line start), or start."""
    pos = start
    while pos > 0:
        prev = line_start(text, pos - 1)
        ln = text[prev:pos].strip()
        if ln.startswith("//"):
            pos = prev
        else:
            break
    return pos


def find_definitions(text, clean, name):
    """Column-0 definitions of `name(EEContext& ...)`: (comment_start, start, sig_end_brace, end, signature)."""
    res = []
    for m in re.finditer(r"(?m)^([A-Za-z_][\w:<>,\s\*&]*?)\b" + re.escape(name) + r"\s*\(", clean):
        start = m.start()
        if "\n" in m.group(1):
            continue
        head = m.group(1).strip()
        if head.startswith(("return", "else", "case")) or head == "" and not clean[start:].startswith(name):
            continue
        # the parameter list
        p = m.end() - 1
        depth = 0
        q = p
        while q < len(clean):
            if clean[q] == "(":
                depth += 1
            elif clean[q] == ")":
                depth -= 1
                if depth == 0:
                    break
            q += 1
        params = text[p + 1:q]
        if "EEContext" not in params.split(",")[0]:
            continue
        r = q + 1
        while r < len(clean) and clean[r] not in "{;":
            r += 1
        if r >= len(clean) or clean[r] != "{":
            continue
        end = match_brace(clean, r)
        if end < 0:
            continue
        res.append((leading_comment(text, start), start, r, line_end(text, end), head, params))
    return res


def split_params(params):
    out, depth, cur = [], 0, ""
    for c in params:
        if c in "(<":
            depth += 1
        elif c in ")>":
            depth -= 1
        if c == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


INT_TYPES = {"u8", "s8", "u16", "s16", "u32", "s32", "int", "unsigned", "char", "bool", "short", "unsigned int",
             "uint32_t", "int32_t", "std::uint32_t", "std::int32_t", "uint8_t", "std::uint8_t", "int16_t", "uint16_t"}
WIDE_TYPES = {"u64", "s64", "std::uint64_t", "std::int64_t", "uint64_t", "int64_t"}


def param_type_name(p):
    p = p.split("=")[0].strip()
    m = re.match(r"^(.*?)([A-Za-z_]\w*)$", p)
    if not m:
        return p, ""
    return m.group(1).strip(), m.group(2)


def make_wrapper(ret, name, body_name, params):
    """The typed API as a wrapper around the register body, or (None, reason)."""
    ps = split_params(params)
    ctx_type, ctx_name = param_type_name(ps[0])
    lines = []
    gi = fi = 0
    gprs = ["GPR_A0", "GPR_A1", "GPR_A2", "GPR_A3", "GPR_T0", "GPR_T1", "GPR_T2", "GPR_T3"]
    for p in ps[1:]:
        t, n = param_type_name(p)
        tt = t.replace("const ", "").strip()
        if tt in INT_TYPES or tt.endswith("_t") and "int" in tt:
            if gi >= len(gprs):
                return None, "more than 8 integer parameters"
            lines.append(f"    ee::core::set_gpr64({ctx_name}, {gprs[gi]}, ee::core::sext32(static_cast<u32>({n})));")
            gi += 1
        elif tt in WIDE_TYPES:
            lines.append(f"    ee::core::set_gpr64({ctx_name}, {gprs[gi]}, static_cast<u64>({n}));")
            gi += 1
        elif tt == "float":
            lines.append(f"    std::memcpy(&{ctx_name}.fpr[{12 + fi}], &{n}, 4);")
            fi += 1
        else:
            return None, f"parameter type '{t}'"
    r = ret.replace("static", "").replace("inline", "").strip()
    call = f"    {body_name}({ctx_name});"
    if r == "void":
        tail = []
    elif r in INT_TYPES or r in WIDE_TYPES or r.endswith("_t"):
        tail = [f"    return static_cast<{r}>(ee::core::gpr64({ctx_name}, GPR_V0));"]
    elif r == "float":
        tail = [f"    float f;", f"    std::memcpy(&f, &{ctx_name}.fpr[0], 4);", "    return f;"]
    else:
        return None, f"return type '{ret}'"
    head = f"{ret} {name}({params}) {{"
    doc = ("// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register\n"
           "// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original\n"
           "// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.\n")
    return doc + head + "\n" + "\n".join(lines + [call] + tail) + "\n}\n", None


_CLEAN = {}


def references(name, files, skip):
    """Calls of `name(` outside comments in `files`, minus the (path, start, end) spans in `skip`."""
    pat = re.compile(r"(?<![\w.>])(?:(?:p3fes::)?game::)?" + re.escape(name) + r"\s*\(")
    hits = []
    for path in files:
        clean = _CLEAN.get(path)
        if clean is None:
            with open(path, encoding="utf-8") as fh:
                clean = _CLEAN[path] = blank_comments(fh.read())
        if name not in clean:
            continue
        for m in pat.finditer(clean):
            if any(path == s[0] and s[1] <= m.start() < s[2] for s in skip):
                continue
            # declarations (`void name(EEContext& ctx);`) are not calls
            ls = line_start(clean, m.start())
            le = clean.find("\n", m.start())
            ln = clean[ls:le if le >= 0 else len(clean)]
            if re.match(r"^\s*[\w:<>\*&\s]+\b" + re.escape(name) + r"\s*\([^;]*EEContext\s*&[^;]*\)\s*(noexcept\s*)?;", ln):
                continue
            hits.append((path, m.start()))
    return hits


# --- the generated translation unit -------------------------------------------------------------------------------

def parse_generated(cpp):
    decls = re.findall(r"(?m)^void fn_\w+\(p3fes::EEContext&\);$", cpp)
    bodies = {}
    for m in re.finditer(r"(?m)^// 0x([0-9A-F]+) (\S+) -- .*\n(?://.*\n)*void (\w+)\(EEContext& ctx\) \{\n", cpp):
        end = cpp.find("\n}\n", m.end() - 2)
        bodies[int(m.group(1), 16)] = (m.group(3), cpp[m.start():end + 3])
    shims = {}
    for m in re.finditer(r"(?m)^void p3fes::recomp_gen::(fn_\w+_([0-9a-f]{8}))\(p3fes::EEContext& ctx\) \{ (.*) \}$", cpp):
        shims[int(m.group(2), 16)] = (m.group(1), m.group(3))
    return decls, bodies, shims


def all_sources():
    out = []
    for top in ("game/src", "game/include", "tests/game"):
        for root, _, files in os.walk(os.path.join(REPO, top)):
            for f in files:
                if f.endswith((".cpp", ".h")):
                    out.append(os.path.normpath(os.path.join(root, f)))
    return out


def run_handgen(handgen, starts):
    with tempfile.TemporaryDirectory() as td:
        lst = os.path.join(td, "list.txt")
        with open(lst, "w") as fh:
            fh.write("\n".join(f"0x{a:X}" for a in starts) + "\n")
        out = os.path.join(td, "out.cpp")
        r = subprocess.run([os.path.abspath(handgen), "--elf", ELF, "--functions", os.path.join(REPO, "symbols/functions.json"),
                            "--chunks", os.path.join(REPO, "symbols/function_chunks.txt"),
                            "--jumptables", os.path.join(REPO, "symbols/jumptables.json"),
                            "--sym", os.path.join(REPO, "symbols/p3fes.sym"), "--only", "@" + lst, "--slice", "audit",
                            "--shim", "--out-cpp", out], capture_output=True, text=True)
        if r.returncode != 0:
            sys.exit(r.stderr)
        with open(out, encoding="utf-8") as fh:
            return fh.read()


def shim_span(text, clean, shim_sym, name, addr):
    """(start, end, kind) of the old shim: a definition of shim_sym, or a P3FES_*(name, addr..) macro row."""
    m = re.search(r"(?m)^[ \t]*void\s+(?:p3fes::recomp_gen::)?" + re.escape(shim_sym) +
                  r"\s*\(\s*(?:p3fes::)?EEContext\s*&\s*\w*\s*\)\s*(?:noexcept\s*)?\{", clean)
    if m:
        e = match_brace(clean, m.end() - 1)
        kind = "qualified" if "p3fes::recomp_gen::" in text[m.start():m.end()] else "plain"
        return m.start(), line_end(text, e), kind
    addr8 = f"{addr:08x}".lstrip("0")
    mm = re.search(r"(?m)^[ \t]*P3FES_\w+\(\s*" + re.escape(name) + r"\s*,\s*(?:0x)?0*" + addr8 + r"\b[^\n]*\n", clean, re.I)
    if mm:
        return mm.start(), mm.end(), "macro"
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--handgen", required=True)
    ap.add_argument("--plan", required=True, help="TSV: <file under the repo> <hex start> [classes] per line")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    plan = {}  # file -> [(addr, note)]
    for ln in open(args.plan, encoding="utf-8"):
        p = ln.rstrip("\n").split("\t")
        if len(p) >= 2 and not ln.startswith("#"):
            plan.setdefault(p[0], []).append((int(p[1], 16), p[2] if len(p) > 2 else ""))
    starts = [a for rows in plan.values() for a, _ in rows]
    decls, bodies, shims = parse_generated(run_handgen(args.handgen, starts))
    # the replaced functions whose entry point a source defines itself (game/forwarders.txt '-' rows); the others'
    # entry points are generated (game/forwarders.cmake)
    own = set()
    with open(os.path.join(REPO, "game", "forwarders.txt"), encoding="utf-8") as fh:
        for ln in fh:
            t = ln.split("#", 1)[0].split()
            if len(t) >= 3 and t[2] == "-":
                own.add(int(t[0], 16))

    # Phase A, on the original texts: where each listed function's old shim and old definitions are, and who else
    # still calls its typed API once every listed function is replaced.
    files = all_sources()
    originals = {}
    for f in files:
        with open(f, encoding="utf-8") as fh:
            originals[f] = fh.read()
    skip = []
    info = {}
    for rel, rows in plan.items():
        src = os.path.normpath(os.path.join(REPO, rel))
        text = originals[src]
        clean = blank_comments(text)
        for addr, _ in rows:
            if addr not in bodies:
                continue
            name = bodies[addr][0]
            ss = shim_span(text, clean, shims[addr][0], name, addr)
            if ss:
                skip.append((src, ss[0], ss[1]))
            for d in find_definitions(text, clean, name):
                skip.append((src, d[1], d[3]))
    for rel, rows in plan.items():
        for addr, _ in rows:
            if addr in bodies:
                info[addr] = references(bodies[addr][0], files, skip)

    manual = []
    edited = {}
    for rel, rows in plan.items():
        src = os.path.normpath(os.path.join(REPO, rel))
        text = originals[src]
        headers = [os.path.join(REPO, "game/include", h) for h in re.findall(r'(?m)^#include "(p3fes/game/[\w/]+\.h)"', text)]
        headers = [os.path.normpath(h) for h in headers]
        for addr, cls in rows:
            if addr not in bodies or addr not in shims:
                manual.append(f"{rel}: 0x{addr:X}: not generated")
                continue
            name, body = bodies[addr]
            shim_sym = shims[addr][0]
            clean = blank_comments(text)
            defs = find_definitions(text, clean, name)
            conflict = any(len(split_params(d[5])) == 1 and re.sub(r"\b(static|inline)\b", "", d[4]).strip() != "void" for d in defs)
            body_name = name + "_regs" if conflict else name
            if conflict:
                body = re.sub(r"(?m)^void " + re.escape(name) + r"\(EEContext& ctx\) \{", f"void {body_name}(EEContext& ctx) {{", body, count=1)
            # 1. the shim
            ss = shim_span(text, clean, shim_sym, name, addr)
            if not ss and addr in own:
                manual.append(f"{rel}: {name}: no shim found (generated shim not placed)")
                continue
            if not ss:
                # a generated entry point (game/forwarders.cmake): the forwarder goes at the end of the file, and
                # forwarders.py moves it out again (recording a body name other than the function's)
                text = text.rstrip("\n") + "\n" + \
                    f"void p3fes::recomp_gen::{shim_sym}(p3fes::EEContext& ctx) {{ p3fes::game::{body_name}(ctx); }}\n"
            else:
                new = (f"void p3fes::recomp_gen::{shim_sym}(p3fes::EEContext& ctx) {{ p3fes::game::{body_name}(ctx); }}\n"
                       if ss[2] == "qualified" else f"void {shim_sym}(p3fes::EEContext& ctx) {{ p3fes::game::{body_name}(ctx); }}\n")
                indent = re.match(r"[ \t]*", text[ss[0]:]).group(0)
                text = text[:ss[0]] + indent + new + text[ss[1]:]
            clean = blank_comments(text)
            # 2. the body, in place of the old definition
            gen_lines = body.split("\n")
            gen_head = gen_lines[0] + "\n"  # "// 0x... name -- N bytes; frame ..."
            k = 1
            while gen_lines[k].startswith("//"):
                k += 1  # drop "Generated by p3fes_handgen: ..." (the note says it)
            # block-scope using-declarations instead of `using namespace hg;` (a file's own helpers keep their names)
            gen_def = fix_hg.fix_text("\n".join(gen_lines[k:]), HG_NAMES)[0]
            first = "// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit" + (": " + cls if cls else "") + "):\n"
            if len(first) > 119:
                first = "// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit; it found: " + cls + "):\n"
                if len(first) > 119:
                    first = "// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):\n// it found: " + cls + ".\n"
            note = first + ("// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.\n")
            defs = find_definitions(text, clean, name)
            if not defs:
                manual.append(f"{rel}: {name}: no definition under this name (old implementation left in place: remove it if unused)")
                kk = [mm.start() for mm in re.finditer(r"(?m)^}\s*//\s*namespace p3fes::game\b", text)]
                if not kk:
                    manual.append(f"{rel}: {name}: no '}}  // namespace p3fes::game' to insert before")
                    continue
                text = text[:kk[-1]] + gen_head + note.replace("; the notes above come from the earlier hand version", "") + gen_def + "\n" + text[kk[-1]:]
                continue
            if len(defs) > 1:
                manual.append(f"{rel}: {name}: {len(defs)} definitions (overloads); the first replaced")
            cstart, start, brace, end, ret, params = defs[0]
            doc = text[cstart:start]
            inner = []
            for ln in text[brace + 1:end].split("\n")[1:]:
                s2 = ln.strip()
                if s2.startswith("//"):
                    inner.append(s2)
                else:
                    break
            carried = doc + ("\n".join(inner) + "\n" if inner else "")
            refs = info.get(addr, [])
            nparams = len(split_params(params))
            plain_void = nparams == 1 and re.sub(r"\b(static|inline)\b", "", ret).strip() == "void"
            new_text = gen_head + carried + note + gen_def
            if refs and not plain_void:
                w, why = make_wrapper(ret, name, body_name, params)
                if w is None:
                    where = sorted({os.path.relpath(h[0], REPO).replace("\\", "/") for h in refs})
                    manual.append(f"{rel}: {name}: typed API still called ({len(refs)} sites: {', '.join(where)}) and no wrapper ({why}): old definition kept")
                    text = text[:cstart] + new_text + "\n" + text[cstart:]
                    continue
                new_text += "\n" + w
            elif not plain_void:
                for h in headers:
                    ht = edited.get(h, originals.get(h))
                    if ht is None:
                        continue
                    hc = blank_comments(ht)
                    dm = re.search(r"(?m)^([ \t]*)[\w:<>\*&\s]*?\b" + re.escape(name) + r"\s*\([^;{]*EEContext\s*&[^;{]*\)\s*(?:noexcept\s*)?;[^\n]*\n", hc)
                    if dm:
                        edited[h] = ht[:dm.start()] + f"{dm.group(1)}void {body_name}(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0\n" + ht[dm.end():]
            text = text[:cstart] + new_text + text[end:]

        # 3. callee declarations, the register view, the gen alias
        clean = blank_comments(text)
        need = []
        for d in decls:
            sym = d.split("(")[0][5:]
            if sym in clean and re.search(r"\b" + re.escape(sym) + r"\s*\(\s*(?:p3fes::)?EEContext\s*&\s*\w*\s*\)\s*[;{]", clean) is None:
                need.append(d)
        incs = list(re.finditer(r'(?m)^#include [<"].*[>"]\n', text))
        at = incs[-1].end() if incs else 0
        add = ""
        if '#include "p3fes/game/hg_cpu.h"' not in text:
            add += '#include "p3fes/game/hg_cpu.h"\n'
        if need:
            add += ("\n// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.\n"
                    "namespace p3fes::recomp_gen {\n" + "\n".join(need) + "\n}  // namespace p3fes::recomp_gen\n")
        if "<cstring>" not in text and "std::memcpy" in text:
            add = "#include <cstring>\n" + add
        if add:
            text = text[:at] + add + text[at:]
        edited[src] = text  # (each body declares its own block-scope `namespace gen`)

    if args.dry_run:
        for f, t in edited.items():
            print(f"===== {f}: {len(t)} chars")
    else:
        for f, t in edited.items():
            with open(f, "w", encoding="utf-8", newline="\r\n") as fh:  # the work tree's CRLF (core.autocrlf)
                fh.write(t)
            if f.endswith(".cpp"):
                fix_decls.fix(f)  # every gen::fn_* declared before its first use
    for m in manual:
        print("MANUAL:", m)
    print(f"{len(starts)} functions in {len(plan)} files, {len(manual)} manual notes")
    return 0


if __name__ == "__main__":
    sys.exit(main())


