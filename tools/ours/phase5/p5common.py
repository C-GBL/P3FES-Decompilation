"""Shared helpers of the Phase 5 slice tooling (make_packet.py, slice.ps1's wire / sync / report steps).

Everything is read from git `main` of the main tree (not its working copy), so a packet describes exactly what a slice
merges onto. Gitignored inputs (ELF, IDA pseudocode) come from the main tree's folders.
"""
import glob
import json
import os
import re
import struct
import subprocess
import tempfile

MAIN = r"F:\P3FES-PORT\p3fes-port"
LEAD = r"F:\P3FES-PORT\lead"
PACKETS = os.path.join(LEAD, "packets")
CACHE = os.path.join(PACKETS, "_cache")
ELF = os.path.join(MAIN, r"extracted\disc\SLUS_216.21")
PSEUDO = os.path.join(MAIN, r"ida\pseudocode")
SCRATCH = r"C:\Users\Administrator\AppData\Local\Temp\claude\f--P3FES-PORT-p3fes-port\6dd115e6-e1c6-47fc-8d55-5460595faf8c\scratchpad"
GAME_END = 0x460000  # game code below the RenderWare band (docs/ANALYSIS/27_unmapped_bands.md)
K_STUBS = {0x19D3F0, 0x19D400}  # K_Assert / K_Abort: `jr $ra` in retail


def git(repo, *args, check=True):
    r = subprocess.run(["git", "-C", repo] + list(args), capture_output=True)
    if check and r.returncode != 0:
        raise RuntimeError("git %s: %s" % (" ".join(args), r.stderr.decode("utf-8", "replace").strip()))
    return r.stdout.decode("utf-8", "replace")


def main_sha(rev="main"):
    return git(MAIN, "rev-parse", rev).strip()


def main_file(path, rev="main"):
    """A file of `rev` (cached on disk by blob id; returns the cached path)."""
    blob = git(MAIN, "rev-parse", "%s:%s" % (rev, path)).strip()
    os.makedirs(os.path.join(CACHE, "blobs"), exist_ok=True)
    out = os.path.join(CACHE, "blobs", "%s_%s" % (blob[:16], os.path.basename(path)))
    if not os.path.exists(out):
        data = subprocess.run(["git", "-C", MAIN, "cat-file", "blob", blob], capture_output=True, check=True).stdout
        tmp = out + ".tmp"
        open(tmp, "wb").write(data)
        os.replace(tmp, out)
    return out


def read_text(path):
    return open(path, encoding="utf-8", errors="replace").read()


# ---- symbols ---------------------------------------------------------------------------------------------------------

def load_functions(path):
    """{start: (name, size)}"""
    return {int(f["a"], 16): (f["n"], f["s"]) for f in json.load(open(path, encoding="utf-8"))}


def load_chunks(path):
    """{start: ([(lo, hi)], {data item addresses})}"""
    out = {}
    for ln in open(path, encoding="utf-8"):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        start = int(p[0], 16)
        rngs, data, i, mode = [], set(), 2, None
        while i < len(p):
            if p[i] in ("C", "D"):
                mode = p[i]
            elif mode == "C":
                lo, hi = p[i].split("-")
                rngs.append((int(lo, 16), int(hi, 16)))
            elif mode == "D":
                a, n = p[i].split(":")
                for k in range(0, int(n), 4):
                    data.add(int(a, 16) + k)
            i += 1
        out[start] = (rngs, data)
    return out


def replaced_rows(text):
    """[(addr, name, block header)] of game/replaced.txt text; the header is the comment block above the rows."""
    rows, header, last_comment = [], "", []
    for ln in text.splitlines():
        s = ln.strip()
        if s.startswith("#"):
            last_comment.append(s.lstrip("# "))
            continue
        if not s:
            continue
        if last_comment:
            header = " ".join(last_comment)
            last_comment = []
        p = s.split()
        if p[0].lower().startswith("0x"):
            rows.append((int(p[0], 16), p[1] if len(p) > 1 else "", header))
    return rows


def cmake_hex_list(text, var):
    """Every address of set(<var> ...) and string(APPEND <var> ...) in a CMakeLists text."""
    out = set()
    for m in re.finditer(r"(?:set\(\s*%s\b|string\(\s*APPEND\s+%s\b)([^)]*)\)" % (var, var), text):
        out.update(int(x, 16) for x in re.findall(r"0x[0-9a-fA-F]+", m.group(1)))
    return out


# ---- the ELF: own-body skip rules ------------------------------------------------------------------------------------

class Elf:
    def __init__(self, path=ELF):
        self.data = open(path, "rb").read()
        d = self.data
        phoff, = struct.unpack_from("<I", d, 0x1C)
        phentsize, phnum = struct.unpack_from("<HH", d, 0x2A)
        self.segs = []
        for i in range(phnum):
            typ, off, vaddr, _, filesz, _, _, _ = struct.unpack_from("<8I", d, phoff + i * phentsize)
            if typ == 1:
                self.segs.append((vaddr, vaddr + filesz, off))

    def word(self, va):
        for lo, hi, off in self.segs:
            if lo <= va < hi:
                return struct.unpack_from("<I", self.data, off + va - lo)[0]
        return None


HW_RANGES = [(0x10000000, 0x10010000, "EE hw"), (0x11000000, 0x11010000, "VU mem"), (0x12000000, 0x12002000, "GS priv"),
             (0x1F800000, 0x1F810000, "IOP hw")]
MEM_OPS = {0x1A, 0x1B, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,
           0x2E, 0x31, 0x36, 0x37, 0x39, 0x3E, 0x3F}


def hw_name(addr):
    for base in (0, 0xA0000000, 0x80000000):  # KSEG1 / KSEG0 views of the same registers
        a = (addr - base) & 0xFFFFFFFF
        for lo, hi, n in HW_RANGES:
            if lo <= a < hi:
                return "%s 0x%08X" % (n, a)
    return None


def scan_body(elf, rngs, data):
    """Own-body skip classes: {'hw': '...', 'syscall': n, 'cop0': n} (empty = clean), plus direct jal / j targets.
    hw: a load / store whose base register holds a hardware address built by lui (+ addiu / ori / daddiu) in this
    body (linear scan; a register written by anything else loses its value)."""
    flags, targets, jalr = {}, set(), 0
    val = {}
    for lo, hi in rngs:
        for pc in range(lo, hi, 4):
            if pc in data:
                continue
            w = elf.word(pc)
            if w is None:
                continue
            op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
            imm = w & 0xFFFF
            simm = imm - 0x10000 if imm & 0x8000 else imm
            dest = None
            if op == 0:
                f = w & 0x3F
                if f == 0x0C:
                    flags["syscall"] = flags.get("syscall", 0) + 1
                elif f == 0x09:
                    jalr += 1
                    dest = rd
                elif f not in (0x08, 0x0D, 0x0F, 0x1A, 0x1B, 0x11, 0x13):  # jr break sync div divu mthi mtlo
                    dest = rd
            elif op == 0x10:
                flags["cop0"] = flags.get("cop0", 0) + 1
            elif op in (2, 3):
                targets.add(((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2))
                if op == 3:
                    dest = 31
            elif op == 0x0F:
                val[rt] = (imm << 16) & 0xFFFFFFFF
                continue
            elif op in (0x09, 0x19):  # addiu / daddiu
                if rs in val:
                    val[rt] = (val[rs] + simm) & 0xFFFFFFFF
                    continue
                dest = rt
            elif op == 0x0D:  # ori
                if rs in val:
                    val[rt] = val[rs] | imm
                    continue
                dest = rt
            elif op in MEM_OPS:
                if rs in val:
                    n = hw_name((val[rs] + simm) & 0xFFFFFFFF)
                    if n and "hw" not in flags:
                        flags["hw"] = "%s at 0x%X" % (n, pc)
                if op in (0x1A, 0x1B, 0x1E, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x37):
                    dest = rt
            elif op in (0x08, 0x0A, 0x0B, 0x0C, 0x0E, 0x18):
                dest = rt
            elif op == 0x1C:  # MMI
                dest = rd
            elif op == 0x11 and rs in (0, 2):  # mfc1 / cfc1
                dest = rt
            elif op == 0x12 and rs in (1, 2):  # qmfc2 / cfc2
                dest = rt
            if dest:
                val.pop(dest, None)
    return flags, targets, jalr


CALLEE_CLASSES = [
    ("iop", re.compile(r"^_?i?sceSif|SifCallRpc|^_?sceRpc")),
    ("sound", re.compile(r"^_?i?sce(Sd|Sk|Spu2)[A-Z_]")),
    ("cd", re.compile(r"^_?i?sceCd")),
    ("adxf", re.compile(r"^(ADXF|adxf)_")),
    ("rofs", re.compile(r"^(ROFS|rofs|RFMAI|rfmai|rfdir)_?", re.I)),
]


def callee_class(name):
    for cls, rx in CALLEE_CLASSES:
        if rx.search(name):
            return cls
    return None


# ---- p3fes_handgen: refusals and the callees of each body -------------------------------------------------------------

def find_handgen():
    exes = glob.glob(os.path.join(MAIN, r"build\*\bin\p3fes_handgen.exe"))
    src = max(os.path.getmtime(os.path.join(MAIN, "recomp", "src", f)) for f in ("handgen.cpp", "handgen_main.cpp"))
    exes = [e for e in exes if os.path.getmtime(e) >= src]
    return max(exes, key=os.path.getmtime) if exes else None


def run_handgen(handgen, symdir, addrs, workdir):
    """{addr: [callee starts]} for generated functions, {addr: reason} for refused ones."""
    lst = os.path.join(workdir, "hg_list.txt")
    out = os.path.join(workdir, "hg_out.cpp")
    open(lst, "w").write("\n".join("0x%X" % a for a in sorted(addrs)) + "\n")
    cmd = [handgen, "--elf", ELF, "--functions", os.path.join(symdir, "functions.json"),
           "--chunks", os.path.join(symdir, "function_chunks.txt"), "--jumptables", os.path.join(symdir, "jumptables.json"),
           "--sym", os.path.join(symdir, "p3fes.sym"), "--only", "@" + lst, "--slice", "packet", "--out-cpp", out]
    r = subprocess.run(cmd, capture_output=True, text=True)
    refused = {}
    for ln in r.stderr.splitlines():
        m = re.match(r"p3fes_handgen: (\S+) @ 0x([0-9a-fA-F]+): not generated: (.*)", ln)
        if m:
            refused[int(m.group(2), 16)] = m.group(3).strip()
    callees = {}
    if os.path.exists(out):
        text = read_text(out)
        heads = [(m.start(), int(m.group(1), 16)) for m in re.finditer(r"^// 0x([0-9A-Fa-f]{8}) \S+ -- \d+ bytes", text, re.M)]
        for i, (pos, a) in enumerate(heads):
            end = heads[i + 1][0] if i + 1 < len(heads) else len(text)
            body = text[pos:end]
            cut = body.find("\n}  // namespace p3fes::game")
            if cut >= 0:
                body = body[:cut]
            refs = {int(x, 16) for x in re.findall(r"gen::fn_\w+?_([0-9a-f]{8})\b", body)}
            refs.discard(a)
            callees[a] = sorted(refs)
    return callees, refused, r.returncode


# ---- IDA pseudocode headers (callers, strings) ---------------------------------------------------------------------

def pseudo_facts(addr, name):
    """{'callers': n, 'data_refs': m, 'strings': [...], 'caller_names': [...]} from the export's header."""
    p = os.path.join(PSEUDO, "fn", "%08x_%s.c" % (addr, name))
    if not os.path.exists(p):
        hits = glob.glob(os.path.join(PSEUDO, "fn", "%08x_*.c" % addr))
        if not hits:
            return None
        p = hits[0]
    facts = {"callers": 0, "data_refs": 0, "strings": [], "caller_names": []}
    with open(p, encoding="utf-8", errors="replace") as f:
        for _ in range(16):
            ln = f.readline()
            if not ln.startswith("//"):
                break
            m = re.match(r"// callers \((\d+)(?:, \+(\d+) data refs)?\): (.*)", ln)
            if m:
                facts["callers"] = int(m.group(1))
                facts["data_refs"] = int(m.group(2) or 0)
                facts["caller_names"] = [x.split()[0] for x in m.group(3).split(", ") if x.strip() not in ("-", "")]
            m = re.match(r"// strings \(\d+\): (.*)", ln)
            if m:
                facts["strings"] = re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1))
    return facts


# ---- saved reach data (first-call probes of earlier slices) -----------------------------------------------------------

ROUTES = ("dorm", "m1", "battle", "fusion", "shop", "climb")
REACH_GLOBS = [r"*\hits_*.txt", r"*\hits.txt", r"*\reach\reach_*.txt", r"*\reach_*.txt", r"*\probe_*.txt",
               r"*\*\reach_*.txt"]


def load_reach(functions, scratch=SCRATCH):
    """{addr: (max count, {routes})} from the probe outputs earlier slices left in the scratch folders (lines
    `<hex> [count]`, `F <hex> <count>`, `first <name>`, `0x<hex> <name> <size> routes=N total=T ...`). Only exact
    function starts count; a line with total=0 / routes=0 is a non-hit. Cached by the files' sizes and times."""
    files = sorted({f for g in REACH_GLOBS for f in glob.glob(os.path.join(scratch, g))})
    key = ";".join("%s:%d:%d" % (f, os.path.getsize(f), os.path.getmtime(f)) for f in files)
    cp = os.path.join(CACHE, "reach.json")
    try:
        c = json.load(open(cp, encoding="utf-8"))
        if c.get("key") == key:
            return {int(a, 16): (v[0], set(v[1])) for a, v in c["reach"].items()}, c["files"]
    except (OSError, ValueError):
        pass
    by_name = {n: a for a, (n, _) in functions.items()}
    reach, used = {}, 0
    for f in files:
        base = os.path.basename(f).lower()
        routes = {r for r in ROUTES if r in base} or set()
        got = 0
        for ln in open(f, encoding="utf-8", errors="replace"):
            p = ln.split()
            if not p or p[0].startswith("#"):
                continue
            if p[0] == "F" and len(p) >= 3:
                p = p[1:]
            a, cnt = None, 1
            if p[0] == "first" and len(p) == 2:
                a = by_name.get(p[1])
            elif re.fullmatch(r"(0x)?[0-9a-fA-F]+", p[0]):
                a = int(p[0], 16)
                if len(p) == 2 and p[1].isdigit():
                    cnt = int(p[1])
                elif len(p) > 2:
                    kv = dict(x.split("=", 1) for x in p if "=" in x)
                    if "total" in kv:
                        cnt = int(kv["total"]) if kv["total"].isdigit() else 0
                        routes = routes | {r for r in ROUTES if kv.get(r, "0") not in ("0", "")}
                    elif kv.get("routes") == "0":
                        cnt = 0
                    elif not any(x.isdigit() for x in p[1:]):
                        cnt = 1
                    else:
                        continue  # an unknown table shape: not a hit list
            if a is None or a not in functions or cnt <= 0:
                continue
            old = reach.get(a, (0, set()))
            reach[a] = (max(old[0], cnt), old[1] | routes)
            got += 1
        used += 1 if got else 0
    os.makedirs(CACHE, exist_ok=True)
    json.dump({"key": key, "files": used, "reach": {"0x%X" % a: [c, sorted(r)] for a, (c, r) in reach.items()}},
              open(cp, "w", encoding="utf-8"))
    return reach, used


# ---- packets ---------------------------------------------------------------------------------------------------------

def other_claims(slice_name):
    """{addr: slice} of every packet's claims.txt but this slice's."""
    out = {}
    for f in glob.glob(os.path.join(PACKETS, "*", "claims.txt")):
        s = os.path.basename(os.path.dirname(f))
        if s == slice_name or s.startswith("_"):
            continue
        for ln in open(f, encoding="utf-8"):
            ln = ln.split("#", 1)[0].strip()
            if ln:
                out.setdefault(int(ln.split()[0], 16), s)
    return out


def parse_addr_list(spec):
    """'0x1,0x2' or '@file' (one hex per line, '#' comments) -> [addr]"""
    if spec.startswith("@"):
        out = []
        for ln in open(spec[1:], encoding="utf-8"):
            ln = ln.split("#", 1)[0].strip()
            if ln:
                out.append(int(ln.split()[0], 16))
        return out
    return [int(x, 16) for x in spec.replace(";", ",").split(",") if x.strip()]


def tokens(text):
    """Rough token count (~4 characters per token for this kind of text)."""
    return (len(text) + 3) // 4


def tmpdir(tag):
    d = os.path.join(CACHE, "work_" + tag)
    os.makedirs(d, exist_ok=True)
    return d
