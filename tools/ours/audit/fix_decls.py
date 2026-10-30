"""Make sure every gen::fn_* a file calls is declared before its first use (regen_faithful.py's helper).

  python -I tools/ours/audit/fix_decls.py game/src/a.cpp [game/src/b.cpp ...]
Adds the missing declarations to the file's "Callees of the register-faithful bodies" block (creates it after the
last #include when there is none) and drops the block's entries the file declares elsewhere before their first use.
"""
import re
import sys

BLOCK = "// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.\nnamespace p3fes::recomp_gen {\n"


def fix(path):
    with open(path, encoding="utf-8") as fh:
        text = fh.read()
    used = []
    for m in re.finditer(r"\bgen::(fn_\w+)\b", text):
        if m.group(1) not in used:
            used.append(m.group(1))
    if not used:
        return 0
    b = text.find(BLOCK)
    if b < 0:
        incs = list(re.finditer(r'(?m)^#include [<"].*[>"]\n', text))
        at = incs[-1].end() if incs else 0
        text = text[:at] + "\n" + BLOCK + "}  // namespace p3fes::recomp_gen\n" + text[at:]
        b = text.find(BLOCK)
    block_end = text.find("}  // namespace p3fes::recomp_gen\n", b)
    before = text[:block_end]
    missing = [s for s in used if not re.search(r"\b" + s + r"\s*\(\s*(?:p3fes::)?EEContext\s*&\s*\w*\s*\)\s*;", before)]
    if missing:
        text = text[:block_end] + "".join(f"void {s}(p3fes::EEContext&);\n" for s in sorted(missing)) + text[block_end:]
        with open(path, "w", encoding="utf-8", newline="\r\n") as fh:
            fh.write(text)
    return len(missing)


def dedupe(path):
    """Drop the block's declarations that the file already has elsewhere before the symbol's first use."""
    with open(path, encoding="utf-8") as fh:
        text = fh.read()
    b = text.find(BLOCK)
    if b < 0:
        return 0
    block_end = text.find("}  // namespace p3fes::recomp_gen\n", b)
    body = text[b + len(BLOCK):block_end]
    rest_before, rest_after = text[:b], text[block_end:]
    keep, dropped = [], 0
    for ln in body.split("\n"):
        m = re.match(r"void (fn_\w+)\(p3fes::EEContext&\);$", ln)
        if not m:
            if ln:
                keep.append(ln)
            continue
        sym = m.group(1)
        use = re.search(r"\bgen::" + sym + r"\b|\b" + sym + r"\s*\(\s*ctx\s*\)", rest_after)
        upto = rest_after[:use.start()] if use else rest_after
        decl = r"\b" + sym + r"\s*\(\s*(?:p3fes::)?EEContext\s*&\s*\w*\s*\)\s*;"
        if re.search(decl, rest_before) or re.search(decl, upto):
            dropped += 1
        else:
            keep.append(ln)
    if not dropped:
        return 0
    if keep:
        text = rest_before + BLOCK + "\n".join(keep) + "\n" + rest_after
    else:  # the whole block (and the blank line before it) goes
        start = b - 1 if rest_before.endswith("\n\n") else b
        text = text[:start] + rest_after[len("}  // namespace p3fes::recomp_gen\n"):]
    with open(path, "w", encoding="utf-8", newline="\r\n") as fh:
        fh.write(text)
    return dropped


if __name__ == "__main__":
    paths = []
    for a in sys.argv[1:]:  # @file: one path per line
        paths += [ln.strip() for ln in open(a[1:], encoding="utf-8") if ln.strip()] if a.startswith("@") else [a]
    for p in paths:
        n = fix(p)
        d = dedupe(p)
        if n or d:
            print(f"{p}: {n} declarations added, {d} duplicates dropped")
