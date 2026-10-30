"""Wire a slice's generated functions into the shared files (append-only, idempotent; slice.ps1 gen calls it).

  python -I tools/ours/phase5/wire.py --repo <worktree> --packet <packet.json> --rows <handgen --out-replaced file>

- game/replaced.txt: the rows under `# Phase 5 slice <slice>: <desc> (<files>)` (a new block at the end, or added to the
  slice's existing block);
- tests/game/CMakeLists.txt: the slice's `_replaced` block (`# <slice> slice ...` .. `# end <slice>`, before
  p3fes_rt_emitted_lib; its string(APPEND _replaced ...) lines are rewritten from the replaced.txt block, other lines
  in it -- _callees -- are kept) and the test file in the p3fes_game_tests source list;
- game/CMakeLists.txt: the header and the source in the p3fes_game source list.
"""
import argparse
import json
import os
import re
import sys


def load(path):
    raw = open(path, "rb").read().decode("utf-8")
    nl = "\r\n" if "\r\n" in raw else "\n"
    return raw.replace("\r\n", "\n").split("\n"), nl


def save(path, lines, nl):
    open(path, "wb").write(nl.join(lines).encode("utf-8"))


def slice_block(lines, s):
    """(first, last) line index of the slice's replaced.txt block (header .. last row), or None."""
    start = None
    for i, ln in enumerate(lines):
        if re.match(r"#\s*Phase 5 slice %s\b" % re.escape(s), ln):
            start = i
            break
    if start is None:
        return None
    end, seen = start, False
    for j in range(start + 1, len(lines)):
        t = lines[j].strip()
        if t.lower().startswith("0x"):
            end, seen = j, True
        elif t.startswith("#") and seen:
            break  # the next block's header
    return start, end


def wire(repo, pj, rows):
    s = pj["slice"]
    out = []
    # ---- game/replaced.txt
    rp = os.path.join(repo, "game", "replaced.txt")
    lines, nl = load(rp)
    present = {int(ln.split()[0], 16) for ln in lines if ln.strip().lower().startswith("0x")}
    new = [r for r in rows if int(r.split()[0], 16) not in present]
    blk = slice_block(lines, s)
    if blk is None:
        while lines and not lines[-1].strip():
            lines.pop()
        files = "%s, %s" % (pj["out_cpp"], pj["out_h"].replace("game/include/", ""))
        lines += ["# Phase 5 slice %s: %s (%s)" % (s, pj.get("desc") or "(describe the slice)", files)] + new + [""]
    else:
        lines[blk[1] + 1:blk[1] + 1] = new
    save(rp, lines, nl)
    blk = slice_block(lines, s)
    mine = [ln.split()[0].lower() for ln in lines[blk[0]:blk[1] + 1] if ln.strip().lower().startswith("0x")]
    out.append("replaced.txt: +%d rows (slice block %d rows)" % (len(new), len(mine)))
    # ---- tests/game/CMakeLists.txt
    tp = os.path.join(repo, "tests", "game", "CMakeLists.txt")
    lines, nl = load(tp)
    app = ['    string(APPEND _replaced ",%s")' % ",".join(mine[i:i + 12]) for i in range(0, len(mine), 12)]
    b = next((i for i, ln in enumerate(lines) if re.match(r"\s*# %s slice\b" % re.escape(s), ln)), None)
    if b is None:
        at = next(i for i, ln in enumerate(lines) if ln.lstrip().startswith("p3fes_rt_emitted_lib(p3fes_game_gen"))
        lines[at:at] = ["    # %s slice (%s, %s): %s" % (s, pj["out_cpp"], os.path.basename(pj["test"]), pj.get("desc") or "-")] + \
            app + ["    # end %s" % s]
    else:
        e = next(i for i in range(b, len(lines)) if re.match(r"\s*# end %s\b" % re.escape(s), lines[i]))
        keep = [ln for ln in lines[b + 1:e] if "APPEND _replaced" not in ln]
        lines[b + 1:e] = keep + app
    test = os.path.basename(pj["test"])
    if not any(ln.strip() == test for ln in lines):
        inc = next(i for i, ln in enumerate(lines) if ln.startswith("target_include_directories(p3fes_game_tests"))
        close = max(i for i in range(inc) if lines[i].strip() == ")")
        lines[close:close] = ["    " + test]
    save(tp, lines, nl)
    out.append("tests/game/CMakeLists.txt: _replaced block %d addresses, test %s listed" % (len(mine), test))
    # ---- game/CMakeLists.txt
    gp = os.path.join(repo, "game", "CMakeLists.txt")
    lines, nl = load(gp)
    want = [pj["out_h"].replace("game/", "", 1), pj["out_cpp"].replace("game/", "", 1)]
    add = [w for w in want if not any(ln.strip() == w for ln in lines)]
    if add:
        alias = next(i for i, ln in enumerate(lines) if ln.startswith("add_library(p3fes::game ALIAS"))
        close = max(i for i in range(alias) if lines[i].strip() == ")")
        lines[close:close] = ["    " + w for w in add]
        save(gp, lines, nl)
    out.append("game/CMakeLists.txt: +%d files" % len(add))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", required=True)
    ap.add_argument("--packet", required=True)
    ap.add_argument("--rows", required=True)
    a = ap.parse_args()
    pj = json.load(open(a.packet, encoding="utf-8"))
    rows = [ln.strip() for ln in open(a.rows, encoding="utf-8") if ln.strip().lower().startswith("0x")]
    for ln in wire(a.repo, pj, rows):
        print(ln)
    return 0


if __name__ == "__main__":
    sys.exit(main())
