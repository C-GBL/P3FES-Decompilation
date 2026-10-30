"""Index of the functions the pair tests stand in (tests/game, tests/game/stand_ins.h; docs/PHASE5_QUICK.md).

Since 2026-10-29 a replaced function can be stood in: the test build's forwarder of a replaced function asks the
installed stand-ins first (game/forwarders.cmake, recomp/README.md "Forwarders"). So this index no longer keeps a
function out of a packet (make_packet.py); it says which tests meet a stand-in for it (tested()), and the slice that
takes it runs those tests. Only the "stays recompiled" comments (held) still hold a function back. The index finds the
stand-ins exactly, from the forms the tests use (no fuzzy grep):

  w.si.install_recorder(<va>, ...)        w.si.install(<va>, "name", fn, ...)      si.install*(...) through a pointer
  <va> = a literal (0x1158B0u), a constant (constexpr / const / enum, multi-declarator, file-local first, then the
         tests' local headers it includes, then a name unique across tests/game), or the variable of a range-for over
         a constant table (kRecorded[] = {...}, rec[] = {{va, "name"}, ...}, std::vector / std::array initialisers;
         the first member of each braced row), `r.va` / `c.first` / std::get<0> of such a row.

Install calls whose address is computed at run time (a function parameter, `if_fn(e)`, the "absent" recorders of
run_pair_si_absent / run_case_w, which stand in only callees the test build does not emit) are listed as unresolved
with file:line and are not in the index. A test's expected values can depend on such a recorder (H_Memcard_Init's
socket handle 0x4242), so the callees they stood in during a real run of the suite are reported too -- every stand-in a
run served, read from ABSENT_LOG and ABSENT_LOG.<pid> (one hex address per line), which the lead writes after a gate:
`ctest -R p3fes_game_tests` in the gate tree with P3FES_STANDIN_LOG=<ABSENT_LOG> (tests/game/stand_ins.cpp). Function
starts a test names as a literal anywhere else (stop_pc / w.callee checks, not-emitted lists) are reported as "named"
(held_by_literal). An absent recorder is installed on a missing-function stop, which a replaced function no longer
gives, and a stop_pc check sees the replaced body run on: the slice checks those tests (packet.md lists them).

Cache: <cache dir>/standins.json, keyed by the git tree id of <rev>:tests/game and this script's hash; rebuilt
when either changes. Usage (Python 3.14, -I):
  python -I tools/ours/phase5/standins.py [--repo F:/P3FES-PORT/p3fes-port] [--rev main] [--dir <tests/game dir>]
         [--query 0x1158B0,...] [--unresolved] [--rebuild]
"""
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys

MAIN = r"F:\P3FES-PORT\p3fes-port"
CACHE_DIR = r"F:\P3FES-PORT\lead\packets\_cache"
ABSENT_LOG = r"F:\P3FES-PORT\lead\packets\absent.txt"
HERE = os.path.dirname(os.path.abspath(__file__))

# ---- source access ---------------------------------------------------------------------------------------------------


def git(repo, *args, data=None):
    r = subprocess.run(["git", "-C", repo] + list(args), input=data, capture_output=True)
    if r.returncode != 0:
        raise RuntimeError("git %s: %s" % (" ".join(args), r.stderr.decode("utf-8", "replace").strip()))
    return r.stdout


def read_rev(repo, rev):
    """{relative name: text} of every .h/.cpp of <rev>:tests/game (one git cat-file --batch)."""
    tree = git(repo, "ls-tree", "%s:tests/game" % rev).decode()
    ents = []
    for ln in tree.splitlines():
        meta, name = ln.split("\t", 1)
        _, typ, sha = meta.split()
        if typ == "blob" and name.endswith((".h", ".cpp")):
            ents.append((name, sha))
    out = git(repo, "cat-file", "--batch", data=("\n".join(s for _, s in ents) + "\n").encode())
    files, pos = {}, 0
    for name, sha in ents:
        nl = out.index(b"\n", pos)
        size = int(out[pos:nl].split()[2])
        files[name] = out[nl + 1:nl + 1 + size].decode("utf-8", "replace")
        pos = nl + 1 + size + 1
    return files


def read_dir(d):
    return {n: open(os.path.join(d, n), encoding="utf-8", errors="replace").read()
            for n in sorted(os.listdir(d)) if n.endswith((".h", ".cpp"))}


def cache_key(repo, rev, d):
    me = hashlib.sha1(open(os.path.abspath(__file__), "rb").read()).hexdigest()[:12]
    if d:
        h = hashlib.sha1()
        for n in sorted(os.listdir(d)):
            if n.endswith((".h", ".cpp")):
                st = os.stat(os.path.join(d, n))
                h.update(("%s %d %d;" % (n, st.st_size, st.st_mtime_ns)).encode())
        return "dir:%s:%s:%s" % (os.path.abspath(d), h.hexdigest(), me)
    return "rev:%s:%s" % (git(repo, "rev-parse", "%s:tests/game" % rev).decode().strip(), me)

# ---- C++-lite parsing ------------------------------------------------------------------------------------------------


def strip(src):
    """Comments removed, string / char literal contents blanked; newlines kept (line numbers stay right)."""
    out, i, n = [], 0, len(src)
    while i < n:
        c = src[i]
        if c == "/" and i + 1 < n and src[i + 1] == "/":
            j = src.find("\n", i)
            i = n if j < 0 else j
        elif c == "/" and i + 1 < n and src[i + 1] == "*":
            j = src.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("\n" * src.count("\n", i, j))
            i = j
        elif c == "R" and src.startswith('R"', i):  # raw string R"d(...)d"
            k = src.index("(", i)
            delim = ")" + src[i + 2:k] + '"'
            j = src.find(delim, k)
            j = n if j < 0 else j + len(delim)
            out.append('""' + "\n" * src.count("\n", i, j))
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and src[j] != c:
                j += 2 if src[j] == "\\" else 1
            out.append(c + c)
            i = j + 1
        else:
            out.append(c)
            i += 1
    return "".join(out)


def match_brace(s, i):
    """Index just past the brace / paren group starting at s[i]."""
    open_c = s[i]
    close_c = {"{": "}", "(": ")", "[": "]"}[open_c]
    d = 0
    for j in range(i, len(s)):
        if s[j] == open_c:
            d += 1
        elif s[j] == close_c:
            d -= 1
            if d == 0:
                return j + 1
    return len(s)


def split_top(s, sep=",", angles=False):
    """s split at depth-0 `sep`; angles=True also nests <> (parameter lists: std::pair<u32, u64>)."""
    opens, closes = ("({[<", ")}]>") if angles else ("({[", ")}]")
    parts, d, cur = [], 0, []
    for ch in s:
        if ch in opens:
            d += 1
        elif ch in closes:
            d -= 1
        if ch == sep and d == 0:
            parts.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        parts.append("".join(cur))
    return [p.strip() for p in parts]


NUM = re.compile(r"\b(0[xX][0-9A-Fa-f]+|\d+)(?:[uU](?:ll|LL|l|L)?|ll|LL|l|L)?\b")
IDENT = re.compile(r"[A-Za-z_][\w:]*")
SAFE = re.compile(r"^[\s0-9xXa-fA-F()+\-*|&<>~^]*$")


def evaluate(expr, lookup):
    """An integer constant expression: literals, constants (lookup), + - * << >> | & ^ ~ ( ); None otherwise."""
    expr = expr.strip()
    expr = re.sub(r"\bstatic_cast<\s*[\w:]+\s*>", "", expr)
    expr = re.sub(r"\b(?:u32|u64|s32|u16|u8|uint32_t|std::uint32_t)\s*\(", "(", expr)
    bad = [False]

    def ident(m):
        name = m.group(0)
        if re.fullmatch(r"0[xX][0-9A-Fa-f]+|\d+", name):
            return name
        v = lookup(name.split("::")[-1]) if name not in ("u", "U") else None
        if v is None:
            bad[0] = True
            return "0"
        return str(v)

    e = NUM.sub(lambda m: m.group(1), expr)
    e = re.sub(r"\b[A-Za-z_][\w:]*\b", ident, e)
    if bad[0] or not e.strip() or not SAFE.match(e):
        return None
    try:
        v = eval(e, {"__builtins__": {}}, {})
    except Exception:
        return None
    return v if isinstance(v, int) else None


TYPES = r"(?:u32|u64|s32|s64|u16|u8|int|unsigned(?:\s+int)?|uint32_t|std::uint32_t|std::uint64_t|auto|Addr|VA|GuestAddr)"
CONST_RE = re.compile(r"(?:(?:static|inline)\s+)*(?:constexpr|const)\s+(?:(?:static|inline)\s+)*" + TYPES + r"\s+([^;{}()]+?);")
ENUM_RE = re.compile(r"\benum\b(?:\s+class|\s+struct)?\s*\w*\s*(?::\s*[\w:]+)?\s*\{")
CONT_RE = re.compile(r"\b([A-Za-z_]\w*)\s*(?:\[\s*\w*\s*\])?\s*=\s*\{|>\s*([A-Za-z_]\w*)\s*\{")
INSTALL_RE = re.compile(r"(?:\.|->)install(?:_recorder)?\s*\(|\binstall_recorder\s*\(")
FOR_RE = re.compile(r"\bfor\s*\(")


class FileInfo:
    def __init__(self, name, text):
        self.name = name
        self.s = strip(text)
        self.raw_consts = {}   # name -> expression text
        self.consts = {}
        self.conts = {}        # name -> (position, element expressions)
        self.includes = re.findall(r'#\s*include\s+"([^"/\\]+)"', text)
        for m in CONST_RE.finditer(self.s):
            for decl in split_top(m.group(1)):
                if "=" in decl:
                    k, v = decl.split("=", 1)
                    k = k.strip()
                    if re.fullmatch(r"[A-Za-z_]\w*", k):
                        self.raw_consts.setdefault(k, v)
        for m in ENUM_RE.finditer(self.s):
            j = match_brace(self.s, m.end() - 1)
            prev = None
            for decl in split_top(self.s[m.end():j - 1]):
                if "=" in decl:
                    k, v = decl.split("=", 1)
                    self.raw_consts.setdefault(k.strip(), v)
                    prev = k.strip()
                elif re.fullmatch(r"[A-Za-z_]\w*", decl) and prev:
                    self.raw_consts.setdefault(decl, "(%s) + 1" % prev)
                    prev = decl
        for m in CONT_RE.finditer(self.s):
            name = m.group(1) or m.group(2)
            b = m.end() - 1
            e = match_brace(self.s, b)
            self.conts.setdefault(name, []).append((m.start(), self.elements(self.s[b + 1:e - 1])))

    @staticmethod
    def elements(body):
        body = body.strip()
        # std::array<..> x = {{ ... }}: one more level of braces around the whole list
        while body.startswith("{") and match_brace(body, 0) == len(body) and body.count("{") > 1 and \
                split_top(body[1:-1])[0].startswith("{"):
            body = body[1:-1].strip()
        out = []
        for it in split_top(body):
            if it.startswith("{"):
                inner = split_top(it[1:match_brace(it, 0) - 1])
                out.append(inner[0] if inner else "")
            elif it.startswith(("std::pair", "std::make_pair")) or re.match(r"[\w:]+\s*\{", it):
                k = it.find("{") if "{" in it else it.find("(")
                inner = split_top(it[k + 1:match_brace(it, k) - 1])
                out.append(inner[0] if inner else "")
            else:
                out.append(it)
        return out

    def line(self, pos):
        return self.s.count("\n", 0, pos) + 1


class Index:
    def __init__(self, files):
        self.f = {n: FileInfo(n, t) for n, t in files.items()}
        self.global_names = {}
        self.gcache = {}
        self.scopes = {}
        for fi in self.f.values():
            for k, v in fi.raw_consts.items():
                self.global_names.setdefault(k, set()).add((fi.name, v.strip()))

    def scope(self, fi, seen=None):
        """fi, then the local headers it includes (transitively)."""
        if seen is None:
            if fi.name not in self.scopes:
                self.scopes[fi.name] = self.scope(fi, [])
            return self.scopes[fi.name]
        if fi.name in seen:
            return seen
        seen.append(fi.name)
        for inc in fi.includes:
            if inc in self.f:
                self.scope(self.f[inc], seen)
        return seen

    def const(self, fi, name, depth=0):
        if depth > 8:
            return None
        for n in self.scope(fi):
            g = self.f[n]
            if name in g.raw_consts:
                if name not in g.consts:
                    g.consts[name] = None
                    g.consts[name] = evaluate(g.raw_consts[name], lambda x: self.const(g, x, depth + 1))
                return g.consts[name]
        if name in self.gcache:
            return self.gcache[name]
        self.gcache[name] = None  # (a cycle resolves to "not a constant")
        cands = self.global_names.get(name, set())
        vals = {evaluate(v, lambda x: self.const(self.f[fn], x, depth + 1)) for fn, v in cands}
        self.gcache[name] = vals.pop() if len(vals) == 1 else None
        return self.gcache[name]

    def rows(self, fi, name):
        """Every row a table named `name` gets in fi's scope: its initialisers (`name[] = {..}`, `name{..}`,
        `.name = {..}`) and its push_back / emplace_back arguments. [(file, row expression, position)] or None."""
        name = name.strip().split("::")[-1].split(".")[-1]
        found = []
        for n in self.scope(fi):
            g = self.f[n]
            found += [(g, e, p) for p, el in g.conts.get(name, []) for e in el]
            for m in re.finditer(r"\b%s\s*(?:\.|->)\s*(?:push_back|emplace_back)\s*\(" % re.escape(name), g.s):
                k = m.end() - 1
                args = split_top(g.s[k + 1:match_brace(g.s, k) - 1])
                if args:
                    rows = FileInfo.elements("{" + ",".join(args) + "}") if args[0].startswith("{") else [args[0]]
                    found += [(g, e, m.start()) for e in rows]
        return found or None

    def callable_at(self, fi, pos):
        """[(name, [parameter names])] of the lambdas / functions whose body contains pos, innermost first."""
        s, best = fi.s, []
        lo = max(0, pos - 20000)
        for m in re.finditer(r"(?:\b(\w+)\s*=\s*)?\[[^\[\]]*\]\s*\(([^()]*)\)[^{;()]*\{|\b(\w+)\s*\(([^()]*)\)\s*(?:const\s*)?(?:noexcept\s*)?\{",
                             s[lo:pos]):
            name = m.group(1) or m.group(3)
            if name in ("if", "for", "while", "switch", "catch", "return"):
                continue
            b = lo + m.end() - 1
            if match_brace(s, b) > pos:
                best.append((name, [p.strip() for p in split_top(m.group(2) if m.group(2) is not None else m.group(4), angles=True)]))
        return best[::-1]

    def call_args(self, fi, name, index, lambda_local):
        """[(file, argument expression, position)] at every call of `name` (same file for a lambda)."""
        out = []
        for g in ([fi] if lambda_local else self.f.values()):
            for m in re.finditer(r"(?<![\w.:>])%s\s*\(" % re.escape(name), g.s):
                k = m.end() - 1
                e = match_brace(g.s, k)
                if re.match(r"\s*(?:const\s*)?(?:noexcept\s*)?(?:->[^{;]*)?\{", g.s[e:e + 80]):
                    continue  # the definition itself
                args = split_top(g.s[k + 1:e - 1])
                if len(args) > index:  # (fewer: the parameter's default)
                    out.append((g, args[index], m.start()))
        return out

    def param_index(self, fi, var, pos):
        for name, params in self.callable_at(fi, pos):
            for i, p in enumerate(params):
                if re.search(r"\b%s\s*(?:=.*)?$" % re.escape(var), p):
                    if not name:
                        return None  # a parameter of an unnamed lambda (a WorldSetup): its caller is the harness
                    return name, i, bool(re.search(r"\b%s\s*=\s*\[" % re.escape(name), fi.s))
        return None

    def run(self):
        hits, unresolved = {}, []
        for fi in self.f.values():
            s = fi.s
            for m in INSTALL_RE.finditer(s):
                k = m.end() - 1
                args = split_top(s[k + 1:match_brace(s, k) - 1])
                if not args:
                    continue
                a0 = args[0]
                if re.match(r"(?:const\s+)?(?:u32|u64|unsigned|uint32_t)\s+\w+$", a0) or re.fullmatch(r"(?:\w+\.)?si", a0):
                    continue  # the method's own definition / declaration; FakeCd::install(si) (its own calls are indexed)
                where = "%s:%d" % (fi.name, fi.line(m.start()))
                vals, why = self.resolve(fi, a0, m.start())
                if why:
                    unresolved.append((where, a0, why))
                for v in vals or []:
                    hits.setdefault(v, [])
                    if where not in hits[v]:
                        hits[v].append(where)
        return hits, unresolved

    @staticmethod
    def stmt_end(s, i):
        """End of the statement starting at s[i] (a loop body): a braced block, or up to its ';' (nested
        if / for / while bodies included)."""
        j = i
        while j < len(s) and s[j].isspace():
            j += 1
        if j < len(s) and s[j] == "{":
            return match_brace(s, j)
        m = re.match(r"(?:for|if|while|switch)\s*\(", s[j:])
        if m:
            return Index.stmt_end(s, match_brace(s, j + m.end() - 1))
        d = 0
        for k in range(j, len(s)):
            if s[k] in "({[":
                d += 1
            elif s[k] in ")}]":
                d -= 1
                if d < 0:
                    return k
            elif s[k] == ";" and d == 0:
                return k + 1
        return len(s)

    def resolve(self, fi, a0, pos, depth=0):
        """([addresses], '') or (None, why)."""
        v = evaluate(a0, lambda x: self.const(fi, x))
        if v is not None:
            return [v], ""
        if depth > 4:
            return None, "too deep"
        call = re.fullmatch(r"(\w+)\s*\((.*)\)", a0.strip(), re.S)
        if call:  # a lookup helper `u32 f(..) { return kTable[..]; }`: every row of the table
            d = re.search(r"\b%s\s*\([^()]*\)\s*\{\s*return\s+(\w+)\s*\[" % re.escape(call.group(1)), fi.s)
            if d:
                return self.resolve_rows(fi, d.group(1), pos, depth + 1)
        m = re.fullmatch(r"(?:std::get<0>\(\s*(\w+)\s*\)|(\w+)\s*(?:\.|->)\s*(?:va|first|addr|a|fn)|(\w+))", a0.strip())
        if not m:
            return None, "computed"
        var = m.group(1) or m.group(2) or m.group(3)
        # 1. the variable of the nearest preceding range-for that binds it
        cont = None
        for f in FOR_RE.finditer(fi.s, max(0, pos - 4000), pos):
            e = match_brace(fi.s, f.end() - 1)
            if self.stmt_end(fi.s, e) < pos:
                continue  # that loop ended before the call
            head = fi.s[f.end():e - 1]
            parts = re.split(r"(?<!:):(?!:)", head, maxsplit=1)
            if len(parts) == 2 and ";" not in head and re.search(r"\b%s\b" % re.escape(var), parts[0]):
                cont = parts[1].strip()
        if cont is not None:
            return self.resolve_rows(fi, cont, pos, depth)
        # 2. a parameter of the enclosing function / lambda: the arguments of its calls
        p = self.param_index(fi, var, pos)
        if p:
            vals = []
            sites = self.call_args(fi, p[0], p[1], p[2])
            if not sites:
                return None, "parameter of %s (no call found)" % p[0]
            for g, arg, at in sites:
                r, why = self.resolve(g, arg, at, depth + 1)
                vals.extend(r or [])
                if why:
                    return vals, "parameter of %s: %s" % (p[0], why)
            return vals, ""
        return None, "not a constant, a table row or a parameter"

    def resolve_rows(self, fi, cont, pos, depth):
        """The addresses of every row of the range `cont` (braced list, table, or a parameter holding one)."""
        typed = re.match(r"[\w:]+\s*(?:<.*>)?\s*\{", cont, re.S)  # std::initializer_list<...>{...}
        if typed and match_brace(cont, typed.end() - 1) == len(cont):
            cont = cont[typed.end() - 1:]
        if cont.startswith("{"):
            elems = [(fi, e, pos) for e in FileInfo.elements(cont[1:match_brace(cont, 0) - 1])]
        else:
            elems = self.rows(fi, cont)
        if elems is None:
            name = cont.split(".")[-1].split("->")[-1].strip()
            p = self.param_index(fi, name, pos) if re.fullmatch(r"\w+", name) else None
            if not p:
                return None, "range-for over '%s' (run-time list)" % cont
            vals = []
            for g2, arg, at in self.call_args(fi, p[0], p[1], p[2]):
                r, why = (self.resolve_rows(g2, arg, at, depth + 1) if depth < 4 else (None, "too deep"))
                vals.extend(r or [])
                if why:
                    return vals, "range-for over parameter '%s' of %s: %s" % (name, p[0], why)
            return (vals, "") if vals else (None, "range-for over parameter '%s' (no call found)" % name)
        vals, bad = [], []
        for g, x, at in elems:
            r, why = self.resolve(g, x, at, depth + 1)
            if r:
                vals.extend(r)
            if why:
                bad.append(x[:30])
        if bad:  # partial: the constant rows are indexed, the rest reported
            return vals, "table '%s' has run-time rows (%s)" % (cont[:40], ", ".join(bad[:2]))
        return vals, ""


# ---- build / load ----------------------------------------------------------------------------------------------------


def build(repo=MAIN, rev="main", d=None, cache_dir=CACHE_DIR, rebuild=False):
    """{'key', 'hits': {addr hex: [file:line,...]}, 'unresolved': [[where, expr, why], ...]} (cached)."""
    key = cache_key(repo, rev, d)
    os.makedirs(cache_dir, exist_ok=True)
    tag = "dir" if d else rev.replace("/", "_")
    path = os.path.join(cache_dir, "standins.%s.json" % tag)
    if not rebuild and os.path.exists(path):
        try:
            c = json.load(open(path, encoding="utf-8"))
            if c.get("key") == key:
                return c
        except (OSError, ValueError):
            pass
    files = read_dir(d) if d else read_rev(repo, rev)
    hits, unresolved = Index(files).run()
    c = {"key": key, "files": len(files), "held": held_by_comment(files),
         "named": held_by_literal(files, function_starts(repo)),
         "hits": {"0x%X" % a: w for a, w in sorted(hits.items())},
         "unresolved": [list(u) for u in unresolved]}
    tmp = path + ".tmp"
    json.dump(c, open(tmp, "w", encoding="utf-8"), indent=0)
    os.replace(tmp, path)
    return c


HELD = re.compile(r"\b(?:stays|stay|kept|keep|left|remains?)\s+recompiled\b", re.I)


def held_by_comment(files):
    """{'sub_XXXXXX' addr hex: [file:line]}: functions a test comment says must stay recompiled (`(the release,
    sub_21BB60, stays recompiled: test_field6_result counts ...)`): the names in the comment text before the phrase,
    on its line and the comment line above."""
    out = {}
    for name, text in files.items():
        lines = text.split("\n")
        for i, ln in enumerate(lines):
            m = HELD.search(ln)
            if not m or "//" not in ln[:m.start()] and not (i and lines[i - 1].strip().startswith("//")):
                continue
            chunk = (lines[i - 1] if i and lines[i - 1].strip().startswith("//") else "") + " " + ln[:m.start()]
            chunk = re.split(r"[.;:]\s", chunk)[-1]
            for a in re.findall(r"\bsub_([0-9A-F]{5,8})\b", chunk):
                out.setdefault("0x%X" % int(a, 16), []).append("%s:%d" % (name, i + 1))
    return out


LITERAL = re.compile(r"\b0[xX]([0-9A-Fa-f]{6,8})[uU]?\b")


def function_starts(repo=MAIN):
    """{start: name} of symbols/functions.json (the working file of <repo>)."""
    with open(os.path.join(repo, "symbols", "functions.json"), encoding="utf-8") as f:
        return {int(r["a"], 16): r["n"] for r in json.load(f)}


def held_by_literal(files, starts):
    """{addr hex: [file:line]}: function starts a test names as a literal outside the install forms above -- a stop_pc
    or w.callee check, a list of callees the test build must not emit, a call it compares. Replacing such a function
    changes what the test sees (sweep3, 2026-10-28: test_field_big / test_field_hi / test_sweep1_msg). The tested
    functions themselves are replaced already, so they are never candidates."""
    out = {}
    for name, text in files.items():
        s = strip(text)
        for i, ln in enumerate(s.split("\n")):
            for m in LITERAL.finditer(ln):
                a = int(m.group(1), 16)
                if a in starts:
                    w = out.setdefault("0x%X" % a, [])
                    if len(w) < 4:
                        w.append("%s:%d" % (name, i + 1))
    return out


def absent_run(path=ABSENT_LOG):
    """{addr: ["served by a stand-in in a p3fes_game_tests run"]}: <path> and its per-process <path>.<pid> files;
    empty when there are none."""
    d, base = os.path.split(path)
    vals = set()
    for n in os.listdir(d) if os.path.isdir(d) else []:
        if n == base or n.startswith(base + "."):
            with open(os.path.join(d, n), encoding="utf-8") as f:
                vals |= {int(t, 16) for t in f.read().split() if t.strip()}
    return {a: ["served by a stand-in in a p3fes_game_tests run (%s)" % base] for a in vals}


def addresses(c):
    return {int(a, 16): w for a, w in c["hits"].items()}


def tested(c, absent_path=ABSENT_LOG):
    """{addr: ["stands in: file:line", "names: file:line", "served in a suite run"]}: every way a test of the index
    meets the function (none of them keeps it out of a packet since the hooked forwarders, 2026-10-29)."""
    out = {}
    for a, w in c["hits"].items():
        out.setdefault(int(a, 16), []).extend("stands in: " + x for x in w[:4])
    for a, w in c.get("named", {}).items():
        out.setdefault(int(a, 16), []).extend("names: " + x for x in w[:2])
    for a in absent_run(absent_path):
        out.setdefault(a, []).append("served in a suite run (%s)" % os.path.basename(absent_path))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--repo", default=MAIN)
    ap.add_argument("--rev", default="main")
    ap.add_argument("--dir", default=None, help="index a working tests/game folder instead of <rev>")
    ap.add_argument("--cache-dir", default=CACHE_DIR)
    ap.add_argument("--rebuild", action="store_true")
    ap.add_argument("--query", default="")
    ap.add_argument("--unresolved", action="store_true")
    a = ap.parse_args()
    c = build(a.repo, a.rev, a.dir, a.cache_dir, a.rebuild)
    print("stand-ins: %d addresses from %d files; %d install calls unresolved (run-time lists)" %
          (len(c["hits"]), c["files"], len(c["unresolved"])))
    if a.query:
        t = tested(c)
        for q in a.query.split(","):
            v = int(q, 16)
            print("  0x%X: %s" % (v, "; ".join(t[v][:6]) if v in t else "no test stands it in, names it or served it"))
    if a.unresolved:
        for w, e, why in c["unresolved"]:
            print("  %s  %s  (%s)" % (w, e, why))
    return 0


if __name__ == "__main__":
    sys.exit(main())
