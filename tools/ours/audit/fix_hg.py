"""Turn the `using namespace hg;` of p3fes_handgen bodies pasted into an existing file into block-scope using-declarations.

A using-directive at block scope makes hg's names visible as if declared in p3fes::game, so a file's own helper of
the same name (a local charge / jal / sll / Gpr) makes the calls ambiguous. Block-scope using-declarations of exactly
the hg names a body uses hide the file's names instead (and a block-scope `namespace gen = ...` hides another `gen`).
Idempotent: a block it wrote before is recomputed.

  python -I tools/ours/audit/fix_hg.py game/src/a.cpp ... | @list.txt
"""
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
TYPES = ("Gpr", "Fpr", "Vf", "Fn")


def hg_names():
    with open(os.path.join(REPO, "game/include/p3fes/game/hg_cpu.h"), encoding="utf-8") as fh:
        h = fh.read()
    names = set()
    for m in re.finditer(r"(?m)^(?:inline|constexpr)\s[^(]*?\b(\w+)\(", h):
        names.add(m.group(1))
    for m in re.finditer(r"P3FES_HG_\w+\((\w+)\)", h):
        names.add(m.group(1))
    for m in re.finditer(r"P3FES_HG_V[23]\((\w+)\)", h):  # these also define name##_bc
        names.add(m.group(1) + "_bc")
    names.discard("operator")
    return names


HEAD = re.compile(r"(?m)^([ \t]*)(?:using namespace hg;\n|(?:namespace gen = ::p3fes::recomp_gen;\n[ \t]*)?using hg::[^;]*;\n)")


def fix_text(text, names):
    out, pos, n = [], 0, 0
    for m in HEAD.finditer(text):
        end = text.find("\n}\n", m.end())  # the function's closing brace at column 0
        body = text[m.end():end]
        clean = re.sub(r"//[^\n]*", "", body)
        clean = re.sub(r'"(?:\\.|[^"\\])*"', '""', clean)
        used = {w for w in re.findall(r"(?<![\w:.])([A-Za-z_]\w*)\s*[({]", clean) if w in names}
        for t in TYPES:
            if re.search(r"(?<![\w:])" + t + r"\s+\w", clean):
                used.add(t)
        ind = m.group(1)
        repl = f"{ind}namespace gen = ::p3fes::recomp_gen;\n" if "gen::" in clean else ""
        if used:
            parts = [f"hg::{u}" for u in sorted(used)]
            lines, cur = [], ind + "using "
            for i, p in enumerate(parts):
                piece = p + (", " if i + 1 < len(parts) else ";")
                if len(cur) + len(piece) > 118 and cur.strip() != "using":
                    lines.append(cur.rstrip())
                    cur = ind + "      " + piece
                else:
                    cur += piece
            lines.append(cur)
            repl += "\n".join(lines) + "\n"
        out.append(text[pos:m.start()])
        out.append(repl)
        pos = m.end()
        n += 1
    out.append(text[pos:])
    return "".join(out), n


def main():
    names = hg_names()
    paths = []
    for a in sys.argv[1:]:
        paths += [ln.strip() for ln in open(a[1:], encoding="utf-8") if ln.strip()] if a.startswith("@") else [a]
    for p in paths:
        with open(p, encoding="utf-8") as fh:
            text = fh.read()
        new, n = fix_text(text, names)
        if new != text:
            with open(p, "w", encoding="utf-8", newline="\r\n") as fh:
                fh.write(new)
            print(f"{p}: {n} bodies")


if __name__ == "__main__":
    main()
