"""Move the replaced functions' recomp_gen forwarders out of game/ sources (recomp/README.md "Forwarders").

Since 2026-10-29 the one-line entry points
    void p3fes::recomp_gen::fn_<name>_<addr8>(p3fes::EEContext& ctx) { p3fes::game::<body>(ctx); }
are generated from game/replaced.txt by game/forwarders.cmake (plain for the game, stand-in hooked for the tests);
no source file writes them. This tool brings a tree there and keeps it there (idempotent):

- every such line in game/src (the qualified form at file scope, or the short form `void fn_..(..) {..}` inside a
  `namespace p3fes::recomp_gen` block, outside any #if) whose row is in game/replaced.txt is deleted; a <body> other
  than the row's name becomes a `0x<addr> <name> <body>` row of game/forwarders.txt;
- a replaced function whose entry point game/ defines another way is marked `0x<addr> <name> -` in
  game/forwarders.txt (the generator skips it): the 1,825 typed shims and shim-macro rows (P3FES_AI_SHIM(name,
  0030c510), X-lists expanded with a shim macro) that existed on 2026-10-29 (--init), plus any new row whose
  fn_<name>_<addr8> a source defines as a function. A new entry point made by a macro is not seen: the link reports
  the duplicate symbol, and the row gets its `-` by hand;
- a `-` row whose function now has a forwarder in a source loses its `-` (the forwarder moves out: generated);
  rows of functions no longer in game/replaced.txt are dropped.

Run it after merging a slice branch cut before this change (its sources still end with forwarders) or after
tools/ours/audit/regen_faithful.py. A tree that needs it does not link (duplicate fn_* symbols): that is the signal.

  python -I tools/ours/phase5/forwarders.py [--repo <tree>] [--check] [--init]

--check: change nothing; exit 1 when a source still holds a forwarder or game/forwarders.txt is out of date.
--init: the one-time migration (2026-10-29): every row without a forwarder in the sources becomes `-`.
Prints the counts: rows, generated forwarders, own entry points, lines removed.
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", "..", ".."))

QUAL = re.compile(r"^void p3fes::recomp_gen::(fn_\w+_([0-9a-f]{8}))\(p3fes::EEContext& ctx\) \{ p3fes::game::(\w+)\(ctx\); \}[ \t]*$")
SHORT = re.compile(r"^void (fn_\w+_([0-9a-f]{8}))\(p3fes::EEContext& ctx\) \{ p3fes::game::(\w+)\(ctx\); \}[ \t]*$")
NOTE = "// The recompiled program's entry points (the dispatch table and every generated call site use them)."

HEADER = """\
# Exceptions to the generated forwarders (game/forwarders.cmake; recomp/README.md "Forwarders").
# Every row of game/replaced.txt gets its recomp_gen entry point generated:
#     void p3fes::recomp_gen::fn_<name>_<addr8>(p3fes::EEContext& ctx) { p3fes::game::<name>(ctx); }
# (plain in p3fes, asking the test stand-ins first in p3fes_game_tests). Rows here change that:
#     0x<addr> <name> -       game/ defines this entry point itself (a typed shim or a shim macro): none is generated
#     0x<addr> <name> <body>  the forwarder calls p3fes::game::<body> instead of <name>
# Written by tools/ours/phase5/forwarders.py (run it after merging a slice that still writes forwarders into its
# sources); sorted by address.
"""


def sym_of(name, addr):
    return "fn_%s_%08x" % (re.sub(r"[^A-Za-z0-9_]", "_", name), addr)


def read_rows(repo):
    rows = {}
    with open(os.path.join(repo, "game", "replaced.txt"), encoding="utf-8") as f:
        for ln in f:
            t = ln.split("#", 1)[0].split()
            if len(t) >= 2 and t[0].lower().startswith("0x"):
                rows[int(t[0], 16)] = t[1]
    return rows


def read_list(repo):
    out = {}
    p = os.path.join(repo, "game", "forwarders.txt")
    if os.path.exists(p):
        with open(p, encoding="utf-8") as f:
            for ln in f:
                t = ln.split("#", 1)[0].split()
                if len(t) >= 3 and t[0].lower().startswith("0x"):
                    out[int(t[0], 16)] = t[2]
    return out


def write_list(repo, rows, lst):
    body = "".join("0x%x %s %s\n" % (a, rows.get(a, "?"), lst[a]) for a in sorted(lst))
    p = os.path.join(repo, "game", "forwarders.txt")
    old = open(p, encoding="utf-8").read() if os.path.exists(p) else None
    new = HEADER + body
    if old != new:
        with open(p, "w", encoding="utf-8", newline="\n") as f:
            f.write(new)
        return True
    return False


def sources(repo):
    for top in ("src", "include"):
        for d, _, fs in os.walk(os.path.join(repo, "game", top)):
            for n in sorted(fs):
                if n.endswith((".cpp", ".h", ".inc")):
                    yield os.path.join(d, n)


def load(path):
    raw = open(path, "rb").read().decode("utf-8")
    nl = "\r\n" if "\r\n" in raw else "\n"
    return raw.replace("\r\n", "\n").split("\n"), nl


def code_only(ln, state):
    """The line without comments and string / character literals; state[0]: inside a /* */ comment."""
    out, k, n = [], 0, len(ln)
    while k < n:
        if state[0]:
            e = ln.find("*/", k)
            if e < 0:
                return "".join(out)
            state[0], k = False, e + 2
            continue
        c = ln[k]
        if ln.startswith("//", k):
            break
        if ln.startswith("/*", k):
            state[0], k = True, k + 2
            continue
        if c in "\"'":
            e = k + 1
            while e < n and ln[e] != c:
                e += 2 if ln[e] == "\\" else 1
            k = e + 1
            continue
        out.append(c)
        k += 1
    return "".join(out)


def scan_file(lines, rows):
    """[(line index, addr, body)] of the forwarders the file holds, and [(line index, why)] of forwarder lines it
    cannot remove (inside #if, the short form outside namespace p3fes::recomp_gen, the qualified form inside a
    scope). Scopes come from the braces (comments and literals left out)."""
    found, refused = [], []
    pp = 0          # preprocessor conditional depth
    scopes = []     # one entry per open brace: the namespace name it opened, or None for any other brace
    cstate = [False]
    for i, ln in enumerate(lines):
        s = ln.strip()
        if s.startswith("#") and not cstate[0]:
            d = s[1:].strip()
            if d.startswith("if"):
                pp += 1
            elif d.startswith("endif"):
                pp = max(0, pp - 1)
            continue
        m = QUAL.match(ln)
        short = False
        if not m:
            m = SHORT.match(ln)
            short = True
        if m and not cstate[0]:
            a = int(m.group(2), 16)
            if a in rows and m.group(1) == sym_of(rows[a], a):
                inner = scopes[-1] if scopes else ""
                if short and inner != "p3fes::recomp_gen":
                    refused.append((i, "short-form forwarder outside namespace p3fes::recomp_gen"))
                elif not short and scopes:
                    refused.append((i, "qualified forwarder inside a scope"))
                elif pp:
                    refused.append((i, "forwarder inside #if"))
                else:
                    found.append((i, a, m.group(3)))
                continue
        code = code_only(ln, cstate)
        for mm in re.finditer(r"namespace(?:\s+([\w:]+))?\s*\{|[{}]", code):
            t = mm.group(0)
            if t == "}":
                if scopes:
                    scopes.pop()
            elif t == "{":
                scopes.append(None)
            else:
                scopes.append(mm.group(1) or "")
    return found, refused


def strip_lines(lines, idx):
    drop = set(idx)
    # a removed line between two blank lines takes one of them along (no double blank lines left behind)
    for i in sorted(idx):
        j = i + 1
        while j in drop:
            j += 1
        k = i - 1
        while k in drop:
            k -= 1
        if 0 <= k and j < len(lines) and not lines[k].strip() and not lines[j].strip():
            drop.add(j)
    out = [ln for i, ln in enumerate(lines) if i not in drop]
    # the note handgen wrote above its forwarders, when nothing follows it any more
    res = [ln for k, ln in enumerate(out) if not (ln.strip() == NOTE and all(not x.strip() for x in out[k + 1:]))]
    # a namespace p3fes::recomp_gen block left empty by the removal
    text = "\n".join(res)
    text = re.sub(r"\nnamespace p3fes::recomp_gen \{\n+\}[^\n]*\n", "\n", text)
    res = text.split("\n")
    while len(res) > 1 and not res[-1].strip() and not res[-2].strip():
        res.pop()
    return res


DEFN = re.compile(r"\b(fn_\w+_[0-9a-f]{8})\s*\(\s*(?:::)?(?:p3fes::)?EEContext\s*&\s*\w*\s*\)\s*(?:\{|$)")


def defined_entries(rows, texts):
    """{addr} of replaced functions whose fn_<name>_<addr8> a game/ source defines as a function (not a one-line
    forwarder; a shim macro is not seen here: such a row needs its `-` by hand, the link names it)."""
    by_sym = {sym_of(n, a): a for a, n in rows.items()}
    out = set()
    for text in texts.values():
        for ln in text:
            if QUAL.match(ln) or SHORT.match(ln) or ln.lstrip().startswith("//") or ln.rstrip().endswith(";"):
                continue
            for m in DEFN.finditer(ln):
                a = by_sym.get(m.group(1))
                if a is not None:
                    out.add(a)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--repo", default=REPO)
    ap.add_argument("--check", action="store_true", help="change nothing; exit 1 when the tree needs this tool")
    ap.add_argument("--init", action="store_true",
                    help="the first migration: every replaced row without a forwarder in the sources becomes '-'")
    a = ap.parse_args()
    repo = os.path.abspath(a.repo)
    rows = read_rows(repo)
    lst = read_list(repo)
    texts, nls, removed, refused, bodies = {}, {}, 0, [], {}
    edits = {}
    for p in sources(repo):
        lines, nl = load(p)
        texts[p], nls[p] = lines, nl
        if not p.endswith(".cpp"):
            continue
        found, bad = scan_file(lines, rows)
        refused += ["%s:%d: %s" % (os.path.relpath(p, repo), i + 1, why) for i, why in bad]
        if found:
            edits[p] = [i for i, _, _ in found]
            for _, addr, body in found:
                if addr in bodies:
                    refused.append("%s: 0x%x forwarded twice" % (os.path.relpath(p, repo), addr))
                bodies[addr] = body
            removed += len(found)
    for p, idx in edits.items():
        texts[p] = strip_lines(texts[p], idx)
    defined = defined_entries(rows, texts)
    new = {}
    for addr in rows:
        if addr in bodies:          # a forwarder moved out of a source now: generated
            if bodies[addr] != rows[addr]:
                new[addr] = bodies[addr]
        elif addr in lst:           # an earlier decision: '-' (own entry point) or a body name
            new[addr] = lst[addr]
        elif a.init or addr in defined:
            new[addr] = "-"
    gone = sorted(x for x in lst if x not in rows)
    own = sum(1 for v in new.values() if v == "-")
    print("forwarders: %d replaced rows; %d generated forwarders (%d with another body name), %d own entry points; "
          "%d forwarder lines %s in %d files; %d stale list rows" %
          (len(rows), len(rows) - own, len(new) - own, own, removed, "to remove" if a.check else "removed", len(edits),
           len(gone)))
    for r in refused[:40]:
        print("  refused: " + r)
    if a.check:
        stale = new != lst
        if stale:
            diff = sorted(set(new.items()) ^ set(lst.items()))
            print("  game/forwarders.txt out of date: %s" % ", ".join("0x%x %s" % d for d in diff[:8]))
        return 1 if (removed or stale or refused) else 0
    for p in edits:
        with open(p, "wb") as f:
            f.write(nls[p].join(texts[p]).encode("utf-8"))
    if write_list(repo, rows, new):
        print("  game/forwarders.txt rewritten (%d rows)" % len(new))
    return 1 if refused else 0


if __name__ == "__main__":
    sys.exit(main())
