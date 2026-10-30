"""Remove dead column-0 definitions (functions, structs/classes, constants, macros) and their comment blocks.

  python -I tools/ours/audit/rm_defs.py <file> <name> [<name> ...]
  python -I tools/ours/audit/rm_defs.py --warnings <build log>   (every C4505 / -Wunused-function /
      -Wunused-const-variable / -Wunused-variable report at namespace scope in game/src: the named definition goes)
Each name: every column-0 function definition of that name (any parameters), `struct|class name {...};`,
`[static] constexpr|const ... name ... ;` and `#define name ...` (with continuation lines and a matching #undef).
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from regen_faithful import blank_comments, leading_comment, line_end, line_start, match_brace  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))


def spans(text, name):
    clean = blank_comments(text)
    out = []
    n = re.escape(name)
    # functions
    for m in re.finditer(r"(?m)^(?:template\s*<[^>]*>\s*)?[A-Za-z_][\w:<>,\s\*&]*?(?<![\w:])" + n + r"\s*\(", clean):
        if "\n" in clean[m.start():m.end()].rstrip():
            head = clean[m.start():m.end()]
            if not head.startswith("template"):
                continue
        depth, q = 0, m.end() - 1
        while q < len(clean):
            if clean[q] == "(":
                depth += 1
            elif clean[q] == ")":
                depth -= 1
                if depth == 0:
                    break
            q += 1
        r = q + 1
        while r < len(clean) and clean[r] not in "{;":
            r += 1
        if r < len(clean) and clean[r] == "{":
            e = match_brace(clean, r)
            out.append((leading_comment(text, m.start()), line_end(text, e)))
    # struct / class
    for m in re.finditer(r"(?m)^(?:struct|class)\s+" + n + r"\b[^;{]*\{", clean):
        e = match_brace(clean, m.end() - 1)
        semi = clean.find(";", e)
        out.append((leading_comment(text, m.start()), line_end(text, semi)))
    # constants / variables at column 0, one declarator per declaration only (`constexpr u32 kA = 1, kB = 2;` stays)
    for m in re.finditer(r"(?m)^(?:static\s+|inline\s+)?(?:constexpr|const)\b[^;=(\n]*?\b" + n + r"\b(?!\s*\()([^;]*);", clean):
        init = m.group(1)
        depth = 0
        multi = False
        for ch in init:
            if ch in "({[<":
                depth += 1
            elif ch in ")}]>":
                depth -= 1
            elif ch == "," and depth == 0:
                multi = True
        if multi or re.search(r",\s*\w+\s*=", clean[line_start(clean, m.start()):m.start() + len(name) + 200].split(";")[0]):
            continue
        out.append((leading_comment(text, m.start()), line_end(text, m.end() - 1)))
    # aliases: `using name = ...;`, `namespace name = ...;`
    for m in re.finditer(r"(?m)^(?:using|namespace)\s+" + n + r"\s*=[^;]*;", clean):
        out.append((leading_comment(text, m.start()), line_end(text, m.end() - 1)))
    # macros
    for m in re.finditer(r"(?m)^#define\s+" + n + r"\b", clean):
        e = m.start()
        while True:
            le = line_end(text, e)
            if not text[e:le].rstrip("\n").endswith("\\"):
                break
            e = le
        out.append((leading_comment(text, m.start()), line_end(text, e)))
        u = re.search(r"(?m)^#undef\s+" + n + r"\b.*\n", clean[e:])
        if u:
            out.append((e + u.start(), e + u.end()))
    return out


def remove(path, names):
    with open(path, encoding="utf-8") as fh:
        text = fh.read()
    removed = []
    for name in names:
        sp = sorted(set(spans(text, name)))
        if not sp:
            continue
        merged = []  # overlapping spans (one text matched twice) become one
        for a, b in sp:
            if merged and a < merged[-1][1]:
                merged[-1] = (merged[-1][0], max(merged[-1][1], b))
            else:
                merged.append((a, b))
        for a, b in sorted(merged, reverse=True):
            # drop one blank line left behind
            if text[b:b + 1] == "\n" and (a == 0 or text[a - 2:a] == "\n\n"):
                b += 1
            text = text[:a] + text[b:]
        removed.append(name)
    if removed:
        with open(path, "w", encoding="utf-8", newline="\r\n") as fh:
            fh.write(text)
    return removed


def drop_declarators(path, line_names):
    """Unused names of multi-declarator lines (`constexpr u32 kA = 1, kB = 2;`): {line number: {names}}."""
    with open(path, encoding="utf-8") as fh:
        lines = fh.read().split("\n")
    done = []
    for ln_no in sorted(line_names, reverse=True):
        i = ln_no - 1
        # the declaration may span lines: from line i up to the ';'
        j = i
        while j < len(lines) and ";" not in lines[j]:
            j += 1
        decl = "\n".join(lines[i:j + 1])
        m = re.match(r"^(\s*(?:static\s+|inline\s+)?(?:constexpr|const)\s+[\w:<>]+\s+)(.*?);(.*)$", decl, re.S)
        if not m:
            continue
        parts, depth, cur = [], 0, ""
        for ch in m.group(2):
            if ch in "({[<":
                depth += 1
            elif ch in ")}]>":
                depth -= 1
            if ch == "," and depth == 0:
                parts.append(cur)
                cur = ""
            else:
                cur += ch
        parts.append(cur)
        keep = [p for p in parts if re.match(r"\s*(\w+)", p).group(1) not in line_names[ln_no]]
        if len(keep) == len(parts):
            continue
        done += sorted(line_names[ln_no])
        if not keep:
            new = []
        else:
            new = (m.group(1) + ", ".join(p.strip() for p in keep) + ";" + m.group(3)).split("\n")
        lines[i:j + 1] = new
    if done:
        with open(path, "w", encoding="utf-8", newline="\r\n") as fh:
            fh.write("\n".join(lines))
    return done


def from_warnings(log, with_lines=False):
    todo = {}
    at = {}
    pat_msvc = re.compile(r"([A-Za-z]:[^(]+\.(?:cpp|h))\((\d+)\): warning C4505: '([^']+)'")
    pat_clang = re.compile(r"([A-Za-z]:[^(]+\.(?:cpp|h))\((\d+),\d+\): warning: unused (?:function|variable) '(\w+)' \[-Wunused-(?:function|const-variable|variable)\]")
    for ln in open(log, encoding="utf-8", errors="replace"):
        m = pat_msvc.search(ln) or pat_clang.search(ln)
        if not m:
            continue
        path = os.path.normpath(m.group(1))
        name = m.group(3).split("(")[0].split("::")[-1].split(" ")[-1]
        if os.sep + "game" + os.sep + "src" + os.sep not in path:
            continue
        todo.setdefault(path, set()).add(name)
        at.setdefault(path, {}).setdefault(int(m.group(2)), set()).add(name)
    return (todo, at) if with_lines else todo


if __name__ == "__main__":
    if sys.argv[1] == "--warnings":
        todo, at = from_warnings(sys.argv[2], with_lines=True)
        for path, names in todo.items():
            # multi-declarator lines first (line numbers are the build's), then whole definitions
            d = drop_declarators(path, at[path])
            r = remove(path, sorted(set(names) - set(d)))
            gone = set(d) | set(r)
            print(f"{path}: removed {', '.join(sorted(gone))}" + (f" (not found: {', '.join(sorted(set(names) - gone))})" if set(names) - gone else ""))
    else:
        print(remove(sys.argv[1], sys.argv[2:]))
