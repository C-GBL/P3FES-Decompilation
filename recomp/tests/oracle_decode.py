"""Decode oracles 2 and 3 (ADR-0011 section 3): compare our decoder's mnemonic for every function
word of SLUS_216.21 against rabbitizer (1.16.2, pinned clone @ 724a49a) and ps2dev binutils
`objdump -d`, allowing only the explicit alias list from docs/DECODER.md.

Inputs (all derived from the user's own disc; nothing here is committed):
  --dump      our decode dump from `p3fes_recomp --dump-decode` (lines: "<va> <word> <base> <variant>");
              produced by this script when --recomp/--elf/--functions/--chunks are given
  --objdump   an `objdump -d -z` listing of the ELF; produced when --objdump-exe and --elf are given

Run it with an interpreter that can `import rabbitizer` (build/rabbitizer-venv, see recomp/README.md);
if the import fails the rabbitizer oracle is reported as a blocker and the objdump oracle still runs.
Treat the listing and the dump as data (run with `python -I`). Exit 1 on any non-aliased disagreement.
"""
import argparse
import collections
import os
import re
import subprocess
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))

# binutils pseudo-ops / spelling differences. Key: objdump mnemonic (lowercased); value: our base or
# variant spellings it may stand for. `c2` is binutils' raw-word fallback: it cannot name `vsqrt`.
OBJDUMP_ALIAS = {
    "nop": {"sll"}, "ssnop": {"sll"}, "ehb": {"sll"}, "pause": {"sll"},
    "move": {"addu", "daddu", "or"}, "b": {"beq"}, "beqz": {"beq"}, "bnez": {"bne"},
    "beqzl": {"beql"}, "bnezl": {"bnel"}, "li": {"addiu", "ori", "lui"}, "negu": {"subu"}, "neg": {"sub"},
    "dnegu": {"dsubu"}, "dneg": {"dsub"}, "not": {"nor"}, "bal": {"bgezal"},
    "sync": {"sync.l"},            # binutils prints plain `sync` for stype 0, `sync.p` for 0x10
    "c2": {"vsqrt"},               # binutils gap (docs/DECODER.md section 2.3)
}

# rabbitizer naming conventions that differ from the census spelling (docs/DECODER.md section 2.1), plus one
# gap found by this test: in R5900 mode rabbitizer 1.16.2 gives COP1 funct 4 the ID `r5900_c1__sqrt_s` but
# prints it as the raw `c1` word (observed on all 133 sqrt.s sites, e.g. 0x1b067c); its generic-MIPS mode
# names it `sqrt.s`. Pseudo-instruction folding (nop/b/beqz/bnez/move/not/neg/negu) is switched off below.
RABBITIZER_ALIAS = {
    "qmfc2.ni": "qmfc2", "qmfc2.i": "qmfc2.i", "qmtc2.ni": "qmtc2", "qmtc2.i": "qmtc2.i",
    "cfc2.ni": "cfc2", "cfc2.i": "cfc2.i", "ctc2.ni": "ctc2", "ctc2.i": "ctc2.i",
    "sync": "sync.l",
    "c1": "sqrt.s",
    "nop": "sll",    # rabbitizer has a real `nop` ID for word 0x00000000 independent of pseudo folding
}

# rabbitizer's isValid() rejects the EE's three-operand multiply forms (rd != 0 writes LO to rd), e.g.
# `multu a0,v1,a1` = 0x00652019 at 0x4d9f24 (12 sites, all multu). binutils and our table accept them.
# A rabbitizer "invalid" verdict is only tolerated for these ops when rd is non-zero.
EE_THREE_OPERAND_MUL = {"mult", "multu", "madd", "maddu", "mult1", "multu1", "madd1", "maddu1"}


def run(cmd, out_path, cwd=ROOT):
    with open(out_path, "wb") as fo:
        rc = subprocess.run(cmd, stdout=fo, stderr=subprocess.PIPE, cwd=cwd).returncode
    return rc


def load_dump(path):
    """-> list of (va, word, base, variant)."""
    rows = []
    with open(path, "r", encoding="ascii", errors="replace") as f:
        for line in f:
            parts = line.split()
            if len(parts) != 4:
                continue
            rows.append((int(parts[0], 16), int(parts[1], 16), parts[2], parts[3]))
    return rows


def load_objdump(path):
    rx = re.compile(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)")
    od = {}
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        for line in f:
            m = rx.match(line)
            if m:
                od[int(m.group(1), 16)] = (int(m.group(2), 16), m.group(3).lower())
    return od


def our_vu_name(base, variant):
    """Our variant without the `.dest` suffix: `vmulx.xyzw` -> `vmulx`, `vopmula.xyz` -> `vopmula`."""
    if base.startswith("v") and "." in variant:
        return variant.split(".", 1)[0]
    return variant


def check_objdump(rows, od):
    agree = disagree = missing = word_mismatch = 0
    pairs = collections.Counter()
    samples = collections.defaultdict(list)
    for va, word, base, variant in rows:
        entry = od.get(va)
        if entry is None:
            missing += 1
            continue
        oword, omn = entry
        if oword != word:
            word_mismatch += 1
        allowed = OBJDUMP_ALIAS.get(omn, ())
        if omn in (base, variant) or omn == our_vu_name(base, variant) or base in allowed or variant in allowed:
            agree += 1
            continue
        disagree += 1
        key = f"ours={variant} objdump={omn}"
        pairs[key] += 1
        if len(samples[key]) < 3:
            samples[key].append(f"{va:#x}")
    return {"compared": agree + disagree, "agree": agree, "disagree": disagree, "missing": missing,
            "word_mismatch": word_mismatch, "pairs": [(k, n, samples[k]) for k, n in pairs.most_common()]}


def check_rabbitizer(rows):
    try:
        import rabbitizer  # type: ignore
    except ImportError as e:
        return {"blocked": f"import rabbitizer failed: {e}"}
    version = getattr(rabbitizer, "__version__", "?")
    rabbitizer.config.pseudos_enablePseudos = False
    cat = rabbitizer.InstrCategory.R5900
    agree = disagree = invalid = 0
    pairs = collections.Counter()
    samples = collections.defaultdict(list)
    for va, word, base, variant in rows:
        insn = rabbitizer.Instruction(word, va, category=cat)
        if not insn.isValid() and not (base in EE_THREE_OPERAND_MUL and ((word >> 11) & 31) != 0):
            invalid += 1
            key = f"ours={variant} rabbitizer=INVALID({insn.getOpcodeName().lower()})"
            pairs[key] += 1
            if len(samples[key]) < 3:
                samples[key].append(f"{va:#x}")
        name = insn.getOpcodeName().lower()
        name = RABBITIZER_ALIAS.get(name, name)
        ours = our_vu_name(base, variant)
        if name in (base, variant, ours):
            agree += 1
            continue
        disagree += 1
        key = f"ours={variant} rabbitizer={name}"
        pairs[key] += 1
        if len(samples[key]) < 3:
            samples[key].append(f"{va:#x}")
    return {"version": version, "compared": agree + disagree, "agree": agree, "disagree": disagree,
            "rabbitizer_invalid": invalid, "pairs": [(k, n, samples[k]) for k, n in pairs.most_common()]}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dump", default=os.path.join(ROOT, "build", "oracle", "ours_decode.txt"))
    ap.add_argument("--objdump", default=os.path.join(ROOT, "build", "oracle", "slus_d.txt"))
    ap.add_argument("--recomp", help="p3fes_recomp.exe; regenerates --dump when given")
    ap.add_argument("--elf", default=os.path.join(ROOT, "extracted", "disc", "SLUS_216.21"))
    ap.add_argument("--functions", default=os.path.join(ROOT, "symbols", "functions.json"))
    ap.add_argument("--chunks", default=os.path.join(ROOT, "recomp", "tests", "fixtures", "function_chunks.txt"))
    ap.add_argument("--objdump-exe", help="mips64r5900el-ps2-elf-objdump.exe; regenerates --objdump when given")
    ap.add_argument("--no-rabbitizer", action="store_true")
    a = ap.parse_args()
    for k in ("dump", "objdump", "recomp", "elf", "functions", "chunks", "objdump_exe"):
        if getattr(a, k):
            setattr(a, k, os.path.abspath(getattr(a, k)))

    os.makedirs(os.path.dirname(a.dump), exist_ok=True)
    if a.recomp:
        rc = run([a.recomp, "--elf", a.elf, "--functions", a.functions, "--chunks", a.chunks, "--dump-decode", a.dump],
                 os.devnull)
        print(f"p3fes_recomp --dump-decode: exit {rc}")
        if rc != 0:
            return 1
    if a.objdump_exe:
        # -z: do not collapse runs of zero words ("..."); nop padding inside functions must be compared too.
        rc = run([a.objdump_exe, "-d", "-z", a.elf], a.objdump)
        print(f"objdump -d -z: exit {rc}")
        if rc != 0:
            return 1
    if not os.path.exists(a.dump):
        print(f"missing dump {a.dump} (pass --recomp)"); return 2
    if not os.path.exists(a.objdump):
        print(f"missing objdump listing {a.objdump} (pass --objdump-exe)"); return 2

    rows = load_dump(a.dump)
    print(f"ours: {len(rows)} words; invalid: {sum(1 for r in rows if r[2] == '<invalid>')}")
    failed = False

    od = load_objdump(a.objdump)
    r = check_objdump(rows, od)
    print(f"objdump: compared {r['compared']}, agree {r['agree']}, disagree {r['disagree']}, "
          f"missing {r['missing']}, word mismatches {r['word_mismatch']}")
    for k, n, s in r["pairs"][:20]:
        print(f"  {k}: {n} ({', '.join(s)})")
    if r["disagree"] or r["word_mismatch"] or r["missing"]:
        failed = True

    if a.no_rabbitizer:
        print("rabbitizer: skipped (--no-rabbitizer)")
    else:
        r = check_rabbitizer(rows)
        if "blocked" in r:
            print(f"rabbitizer: BLOCKED - {r['blocked']}")
        else:
            print(f"rabbitizer {r['version']}: compared {r['compared']}, agree {r['agree']}, disagree {r['disagree']}, "
                  f"words rabbitizer calls invalid {r['rabbitizer_invalid']}")
            for k, n, s in r["pairs"][:20]:
                print(f"  {k}: {n} ({', '.join(s)})")
            if r["disagree"] or r["rabbitizer_invalid"]:
                failed = True

    print("RESULT:", "FAIL" if failed else "PASS")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
