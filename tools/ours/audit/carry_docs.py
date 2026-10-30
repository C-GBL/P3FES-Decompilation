"""Carry the old documentation onto regenerated bodies that got none (regen_faithful.py's helper).

regen_faithful.py moves the comment block of the old definition *of the same name*. Where the old body was a member of
a register view (`void Cpu::colour_vertices_const()`, called by a one-line `sub_487EF0` wrapper) or a lambda / helper,
that block sat elsewhere. This pass looks, for every regenerated body whose comment holds only the generated head line
and the audit note, for the old file's comment blocks (in `--base`, e.g. main) that name the function (its name or its
start address) on their first line and directly precede a definition, and puts the first such block above the note.

  python -I tools/ours/audit/carry_docs.py --base main --plan plan.tsv
"""
import argparse
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from regen_faithful import REPO  # noqa: E402

NOTE = "// Register-faithful since 2026-10-21 (faithfulness audit"


def comment_blocks(text):
    """(first line, block text) of every contiguous // block that directly precedes a non-comment, non-blank line."""
    lines = text.split("\n")
    out = []
    i = 0
    while i < len(lines):
        if lines[i].lstrip().startswith("//"):
            j = i
            while j < len(lines) and lines[j].lstrip().startswith("//"):
                j += 1
            nxt = lines[j] if j < len(lines) else ""
            if nxt.strip() and not nxt.strip().startswith("}") and "(" in nxt:  # a definition / declaration follows
                block = [ln.strip() for ln in lines[i:j]]
                out.append((block[0], block, nxt.strip()))
            i = j
        else:
            i += 1
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", default="main")
    ap.add_argument("--plan", required=True)
    args = ap.parse_args()
    plan = {}
    for ln in open(args.plan, encoding="utf-8"):
        p = ln.rstrip("\n").split("\t")
        if len(p) >= 2:
            plan.setdefault(p[0], []).append(int(p[1], 16))
    total = 0
    for rel, addrs in plan.items():
        path = os.path.join(REPO, rel)
        text = open(path, encoding="utf-8").read()
        base = subprocess.run(["git", "-C", REPO, "show", f"{args.base}:{rel}"], capture_output=True, text=True,
                              encoding="utf-8").stdout.replace("\r\n", "\n")
        blocks = comment_blocks(base)
        changed = False
        for addr in addrs:
            # the generated head line "// 0x0048_7EF0 name -- N bytes; ..." and the note right after it
            m = re.search(r"(?m)^// 0x%08X (\S+) -- [^\n]*\n(%s)" % (addr, re.escape(NOTE)), text)
            if not m:
                continue
            name = m.group(1)
            want = [b for b in blocks if re.search(r"(?<![\w])" + re.escape(name) + r"(?![\w])", b[0])
                    or re.search(r"0x0*%X\b" % addr, b[0], re.I)]
            # prefer a block above a definition of something else than the shim
            want = [b for b in want if not b[2].startswith("void fn_")]
            if not want:
                continue
            # a block that starts with the name or the address first (one that only mentions it comes last)
            want.sort(key=lambda b: 0 if re.match(r"//\s*(?:%s\b|0x0*%X\b)" % (re.escape(name), addr), b[0], re.I) else 1)
            block = "\n".join(want[0][1]) + "\n"
            text = text[:m.start(2)] + block + text[m.start(2):]
            changed = True
            total += 1
        if changed:
            with open(path, "w", encoding="utf-8", newline="\r\n") as fh:
                fh.write(text)
    # the note's second sentence names "the notes above"; where there are none, say so plainly
    for rel in plan:
        path = os.path.join(REPO, rel)
        text = open(path, encoding="utf-8").read()
        new = re.sub(r"(?m)^(// 0x[0-9A-F]{8} \S+ -- [^\n]*\n)" +
                     r"(// Register-faithful since 2026-10-21 \(faithfulness audit[^\n]*\n(?:// it found[^\n]*\n)?)" +
                     r"// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version\.\n",
                     lambda mm: mm.group(1) + mm.group(2) + "// p3fes_handgen's body, statement for statement the original's.\n", text)
        if new != text:
            with open(path, "w", encoding="utf-8", newline="\r\n") as fh:
                fh.write(new)
    print(f"{total} doc blocks carried")


if __name__ == "__main__":
    main()
