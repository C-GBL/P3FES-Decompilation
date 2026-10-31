"""skgen: the Standard Kit IOP modules as native C++ (modernize layer 3, steps 2-3; docs/MODERNIZE_PLAN.md section 3).

Reads the six IRX modules of the sound-effect stack (SDRDRV, MODHSYN, MODSESQ, SKSOUND, SKHSYNTH, SKSESQ) from the
user's disc image (extracted/disc/LIB31) and translates
their MIPS I code into C++ functions over a register file and the IOP RAM (runtime/native/sound/sk/sk_cpu.h), one
statement per instruction, the way p3fes_handgen writes the EE game code: the faithful form, which the lift pass
may later turn into natural C++. The code is placed at the addresses the faithful path loads the images to
(IopLayout::Pcsx2, runtime/hle/sif/iop/srv_sdr.h kSkModulesPcsx2), so every relocated constant is the faithful one.

  * Functions: the module entries, every export, every jal target, every text address built with lui/addiu or held
    in an R_MIPS_32 word (function pointers), found to a fixed point; each one's body is what its control flow
    reaches (branches, j, the eight jump tables); a j to another function is a tail call.
  * Delay slots: a branch condition / jump target is read before its slot runs, as on the R3000; jal / jalr set
    $ra before the slot. No load-delay model (the interpreter has none either; compiled code never reads the
    loaded register in the slot).
  * Calls: jal to a function -> a C++ call; to an import stub -> the exporting module's function (the libraries
    the six export to each other) or a host function (sk_host.cpp: libsd, the kernel); jalr -> sk::call_address.
    `jr $ra` returns (checked against the $ra the function was entered with).
  * Threads: an import that blocks (SleepThread, WaitSema, sceSifRpcLoop, ExitThread) parks the running thread:
    the caller returns at once (`if (c.parked) return;`) and the thread entry gets a resume label after each such
    call, which the host's scheduler jumps to when the thread is woken (registers restored from the thread).

The build runs it (runtime/native/sound/CMakeLists.txt, P3FES_LIB31_DIR) into <build>/runtime/native/sound/sk_gen: the output is
derived from game data and, like recomp/generated, never committed. By hand:
    python -I tools/ours/modernize/skgen.py --lib <extracted>/disc/LIB31 --out <dir> [--report FILE]
"""
import argparse
import os
import struct
import sys

MODULES = [  # load order (kwlnInitPS2Systems) and the faithful image bases (IopLayout::Pcsx2)
    ('SDRDRV', 0x00083230),
    ('MODHSYN', 0x00084F30),
    ('MODSESQ', 0x00095A30),
    ('SKSOUND', 0x00098630),
    ('SKHSYNTH', 0x0009A030),
    ('SKSESQ', 0x000B0730),
]

REG = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
       's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 'fp', 'ra']

# Host libraries: (library, ordinal) -> name (ps2sdk's import names, as runtime/hle/sif/iop/iop_kernel_hle.cpp and
# libsd_hle.cpp register them).
HOST = {
    'libsd': {2: 'sceSdQuit', 4: 'sceSdInit', 5: 'sceSdSetParam', 6: 'sceSdGetParam', 7: 'sceSdSetSwitch',
              8: 'sceSdGetSwitch', 9: 'sceSdSetAddr', 10: 'sceSdGetAddr', 11: 'sceSdSetCoreAttr',
              12: 'sceSdGetCoreAttr', 13: 'sceSdNote2Pitch', 14: 'sceSdPitch2Note', 15: 'sceSdProcBatch',
              16: 'sceSdProcBatchEx', 17: 'sceSdVoiceTrans', 18: 'sceSdBlockTrans', 19: 'sceSdVoiceTransStatus',
              20: 'sceSdBlockTransStatus', 21: 'sceSdSetTransCallback', 22: 'sceSdSetIRQCallback',
              23: 'sceSdSetEffectAttr', 24: 'sceSdGetEffectAttr', 25: 'sceSdClearEffectWorkArea',
              26: 'sceSdSetTransIntrHandler', 27: 'sceSdSetSpu2IntrHandler', 28: 'sceSdGetTransIntrHandlerArgument',
              29: 'sceSdGetSpu2IntrHandlerArgument', 30: 'sceSdStopTrans', 31: 'sceSdCleanEffectWorkArea',
              32: 'sceSdSetEffectMode', 33: 'sceSdSetEffectModeParams'},
    'thbase': {4: 'CreateThread', 5: 'DeleteThread', 6: 'StartThread', 7: 'StartThreadArgs', 8: 'ExitThread',
               9: 'ExitDeleteThread', 10: 'TerminateThread', 11: 'iTerminateThread', 14: 'ChangeThreadPriority',
               15: 'iChangeThreadPriority', 20: 'GetThreadId', 22: 'ReferThreadStatus', 23: 'iReferThreadStatus',
               24: 'SleepThread', 25: 'WakeupThread', 26: 'iWakeupThread', 27: 'CancelWakeupThread',
               28: 'iCancelWakeupThread', 33: 'DelayThread', 34: 'GetSystemTime', 39: 'USec2SysClock',
               40: 'SysClock2USec'},
    'thsemap': {4: 'CreateSema', 5: 'DeleteSema', 6: 'SignalSema', 7: 'iSignalSema', 8: 'WaitSema', 9: 'PollSema'},
    'timrman': {4: 'AllocHardTimer', 6: 'FreeHardTimer', 20: 'SetTimerHandler', 22: 'SetupHardTimer',
                23: 'StartHardTimer', 24: 'StopHardTimer'},
    'intrman': {17: 'CpuSuspendIntr', 18: 'CpuResumeIntr'},
    'sysmem': {4: 'AllocSysMemory', 5: 'FreeSysMemory', 14: 'Kprintf'},
    'loadcore': {6: 'RegisterLibraryEntries', 7: 'ReleaseLibraryEntries'},
    'sysclib': {8: 'look_ctype_table', 12: 'memcpy', 14: 'memset', 17: 'bzero', 27: 'strlen', 29: 'strncmp',
                36: 'strtol'},
    'stdio': {4: 'printf'},
    'sifcmd': {14: 'sceSifInitRpc', 15: 'sceSifBindRpc', 16: 'sceSifCallRpc', 17: 'sceSifRegisterRpc',
               19: 'sceSifSetRpcQueue', 22: 'sceSifRpcLoop', 24: 'sceSifRemoveRpc', 25: 'sceSifRemoveRpcQueue'},
}
BLOCKING = {('thbase', 24), ('thsemap', 8), ('sifcmd', 22), ('thbase', 8), ('thbase', 9)}


def u32(x):
    return x & 0xFFFFFFFF


def s16(x):
    x &= 0xFFFF
    return x - 0x10000 if x & 0x8000 else x


class Irx:
    def __init__(self, name, path, base):
        self.name, self.base = name, base
        d = open(path, 'rb').read()
        self.file = d
        phoff, shoff = struct.unpack_from('<II', d, 28)
        phentsize, phnum, shentsize, shnum, _ = struct.unpack_from('<HHHHH', d, 42)
        load = iopmod = None
        for i in range(phnum):
            t, off, va, pa, fs, ms = struct.unpack_from('<IIIIII', d, phoff + i * phentsize)
            if t == 1 and load is None:
                load = (off, fs, ms)
            if t == 0x70000080 and iopmod is None:
                iopmod = (off, fs)
        io = iopmod[0]
        self.entry, self.gp, self.text, self.data, self.bss = struct.unpack_from('<IIIII', io and d or d, io + 4)
        self.size = max(load[2], self.text + self.data + self.bss)
        img = bytearray(self.size)
        img[:load[1]] = d[load[0]:load[0] + load[1]]
        self.raw = bytes(img)  # unrelocated (for the text hash)
        self.rels = []
        for i in range(shnum):
            name, typ, flags, addr, off, size = struct.unpack_from('<IIIIII', d, shoff + i * shentsize)
            if typ == 9:
                for k in range(size // 8):
                    a, info = struct.unpack_from('<II', d, off + k * 8)
                    self.rels.append((a, info & 0xFF))
        # relocate at base (irx_loader.cpp's rules: HI16 pairs with the following LO16)
        self.reltype = {}
        hi = None
        for a, t in self.rels:
            self.reltype[a] = t
            x = struct.unpack_from('<I', img, a)[0]
            if t == 2:
                struct.pack_into('<I', img, a, u32(x + base))
            elif t == 4:
                struct.pack_into('<I', img, a, (x & ~0x03FFFFFF & 0xFFFFFFFF) | ((x + (base >> 2)) & 0x03FFFFFF))
            elif t == 5:
                assert hi is None, 'HI16 without LO16'
                hi = (a, x)
            elif t == 6:
                assert hi is not None, 'orphan LO16'
                lo = u32(s16(x))
                v = u32(lo + (hi[1] << 16) + base)
                struct.pack_into('<I', img, a, (x & 0xFFFF0000) | (v & 0xFFFF))
                if v & 0x8000:
                    v = u32(v + 0x10000)
                struct.pack_into('<I', img, hi[0], (hi[1] & 0xFFFF0000) | (v >> 16))
                hi = None
            else:
                raise SystemExit(f'{name}: relocation type {t}')
        self.img = bytes(img)
        h = 0xCBF29CE484222325  # FNV-1a 64 of the unrelocated text (NativeSk::install checks it)
        for b in self.raw[:self.text]:
            h = ((h ^ b) * 0x100000001B3) & 0xFFFFFFFFFFFFFFFF
        self.text_hash = h
        # import / export tables
        self.imports = {}  # stub offset -> (library, ordinal)
        self.exports = {}  # library -> [function absolute addresses]
        a = 0
        while a + 20 <= self.size:
            w0, w1 = self.w(a), self.w(a + 4)
            if w0 == 0x41E00000 and w1 == 0:
                lib = self.img[a + 12:a + 20].split(b'\0')[0].decode()
                s = a + 20
                while s + 8 <= self.size and self.w(s) == 0x03E00008 and (self.w(s + 4) & 0xFFFF0000) == 0x24000000:
                    self.imports[s] = (lib, self.w(s + 4) & 0xFFFF)
                    s += 8
                a = s + 8
                continue
            if w0 == 0x41C00000 and w1 == 0:
                lib = self.img[a + 12:a + 20].split(b'\0')[0].decode()
                s = a + 20
                fns = []
                while s + 4 <= self.size and self.w(s) != 0:
                    fns.append(self.w(s))
                    s += 4
                self.exports[lib] = fns
                self.export_range = getattr(self, 'export_range', []) + [(a, s + 4)]
                a = s + 4
                continue
            a += 4

    def w(self, a):
        return struct.unpack_from('<I', self.img, a)[0]

    def in_text(self, absaddr):
        o = absaddr - self.base
        return 0 <= o < self.text and o % 4 == 0


class Insn:
    __slots__ = ('a', 'w', 'op', 'rs', 'rt', 'rd', 'sa', 'fn', 'imm', 'simm')

    def __init__(self, a, w):
        self.a, self.w = a, w
        self.op = w >> 26
        self.rs, self.rt, self.rd, self.sa, self.fn = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 63
        self.imm = w & 0xFFFF
        self.simm = s16(w)

    def kind(self):
        op, fn = self.op, self.fn
        if op == 0:
            if fn == 8:
                return 'jr'
            if fn == 9:
                return 'jalr'
            return 'alu'
        if op == 1:
            return 'regimm'
        if op == 2:
            return 'j'
        if op == 3:
            return 'jal'
        if op in (4, 5, 6, 7):
            return 'branch'
        return 'alu'

    def writes(self):
        """registers written (for the delay-slot / condition ordering)"""
        op, fn = self.op, self.fn
        if op == 0:
            if fn in (8, 12, 13, 0x11, 0x13, 0x18, 0x19, 0x1A, 0x1B):
                return set()
            return {self.rd}
        if op in (0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26):
            return {self.rt}
        if op == 3:
            return {31}
        if op == 1 and (self.rt & 0x1E) == 0x10:
            return {31}
        return set()


class Gen:
    def __init__(self, mods):
        self.mods = mods
        self.by_name = {m.name: m for m in mods}
        self.lib_owner = {}
        for m in mods:
            for lib, fns in m.exports.items():
                self.lib_owner.setdefault(lib, (m, fns))
        self.roots = {}  # abs addr -> module
        self.hostused = set()
        self.problems = []

    def mod_of(self, absaddr):
        for m in self.mods:
            if m.in_text(absaddr):
                return m
        return None

    def is_code(self, m, v):
        o = v - m.base
        return m.in_text(v) and o not in m.imports and not any(lo <= o < hi for lo, hi in getattr(m, 'export_range', []))

    def insn(self, m, absaddr):
        return Insn(absaddr, m.w(absaddr - m.base))

    def import_at(self, m, absaddr):
        """(kind, value): ('host', (lib, ord)) / ('guest', abs fn) for an import stub, else None"""
        imp = m.imports.get(absaddr - m.base)
        if not imp:
            return None
        lib, o = imp
        if lib in self.lib_owner:
            owner, fns = self.lib_owner[lib]
            if o >= len(fns):
                raise SystemExit(f'{m.name}: import {lib} {o} beyond the export table')
            return ('guest', fns[o])
        if lib not in HOST or o not in HOST[lib]:
            raise SystemExit(f'{m.name}: host import {lib} {o} has no name in HOST')
        return ('host', (lib, o))

    def jump_table(self, m, a):
        """targets of the jump table used by the `jr` at a (lui at,%hi(T); addu at,at,rX; lw rY,%lo(T)(at); jr rY)"""
        jr = self.insn(m, a)
        reg = jr.rs
        lw = hi = None
        bound = None
        for k in range(1, 14):
            p = self.insn(m, a - 4 * k)
            if lw is None and p.op == 0x23 and p.rt == reg:
                lw = p
                continue
            if lw is not None and hi is None and p.op == 0x0F and p.rt == lw.rs:
                hi = p
                continue
            if p.op == 0x0B and bound is None and hi is not None:  # sltiu: the bound check
                bound = p.imm
                break
        if lw is None or hi is None:
            return None
        table = u32((hi.imm << 16) + lw.simm)
        off = table - m.base
        out = []
        n = 0
        while off + 4 * n + 4 <= m.size and m.reltype.get(off + 4 * n) == 2:
            t = m.w(off + 4 * n)
            if not m.in_text(t):
                break
            out.append(t)
            n += 1
            if bound is not None and n >= bound:
                break
        if bound is not None and n != bound:
            self.problems.append(f'{m.name} jr {a - m.base:#x}: table {table:#x} has {n} entries, bound {bound}')
        return table, out

    def body(self, m, root):
        """reachable instruction addresses of the function at root, its labels, calls, jump tables"""
        seen, work = set(), [root]
        labels = {root}
        tables = {}
        calls = set()
        while work:
            a = work.pop()
            while True:
                if a in seen:
                    break
                if not m.in_text(a):
                    raise SystemExit(f'{m.name} {root - m.base:#x}: flow leaves the text at {a - m.base:#x}')
                if (a - m.base) in m.imports:
                    raise SystemExit(f'{m.name} {root - m.base:#x}: flow runs into an import stub at {a - m.base:#x}')
                if any(lo <= a - m.base < hi for lo, hi in getattr(m, 'export_range', [])):
                    raise SystemExit(f'{m.name} {root - m.base:#x}: flow runs into an export table at {a - m.base:#x}')
                seen.add(a)
                i = self.insn(m, a)
                k = i.kind()
                if k in ('branch', 'regimm', 'j', 'jal', 'jr', 'jalr'):
                    seen.add(a + 4)  # the delay slot
                    d = self.insn(m, a + 4)
                    if d.kind() != 'alu':
                        raise SystemExit(f'{m.name}: control transfer in a delay slot at {a + 4 - m.base:#x}')
                if k == 'branch' or k == 'regimm':
                    if k == 'regimm' and i.rt not in (0, 1):
                        raise SystemExit(f'{m.name}: bltzal/bgezal at {a - m.base:#x}')
                    t = u32(a + 4 + (i.simm << 2))
                    labels.add(t)
                    labels.add(a + 8)
                    work.append(t)
                    if i.op == 4 and i.rs == 0 and i.rt == 0:  # b (beq zero, zero): unconditional
                        break
                    a += 8
                    continue
                if k == 'j':
                    t = (a & 0xF0000000) | ((i.w & 0x03FFFFFF) << 2)
                    imp = self.import_at(m, t)
                    if imp or (t in self.roots and t != root):
                        calls.add(t)
                    else:
                        labels.add(t)
                        work.append(t)
                    break
                if k == 'jal':
                    t = (a & 0xF0000000) | ((i.w & 0x03FFFFFF) << 2)
                    calls.add(t)
                    labels.add(a + 8)
                    a += 8
                    continue
                if k == 'jalr':
                    labels.add(a + 8)
                    a += 8
                    continue
                if k == 'jr':
                    if i.rs != 31:
                        jt = self.jump_table(m, a)
                        if jt is None:
                            self.problems.append(f'{m.name} {a - m.base:#x}: jr {REG[i.rs]} without a jump table (indirect tail call)')
                        else:
                            tables[a] = jt
                            for t in jt[1]:
                                labels.add(t)
                                work.append(t)
                    break
                a += 4
        return seen, labels, tables, calls

    def discover(self):
        for m in self.mods:
            self.roots[m.base + m.entry] = m
            for lib, fns in m.exports.items():
                for f in fns:
                    if self.mod_of(f) is m:
                        self.roots[f] = m
        # data function pointers: R_MIPS_32 words outside the export tables pointing into text (jump-table words are
        # removed below once the tables are known)
        cand = {}
        for m in self.mods:
            for off, t in m.reltype.items():
                if t != 2:
                    continue
                if any(lo <= off < hi for lo, hi in getattr(m, 'export_range', [])):
                    continue
                v = m.w(off)
                if self.is_code(m, v):
                    cand.setdefault(m, {})[off] = v
            # lui/addiu pairs naming a text address (handlers, thread entries, callbacks)
            pairs = []

            hi = None
            for off, t in m.rels:
                if t == 5:
                    hi = off
                elif t == 6 and hi is not None:
                    pairs.append((hi, off))
                    hi = None
            for h, l in pairs:
                if l >= m.text:
                    continue
                hi_i, lo_i = Insn(0, m.w(h)), Insn(0, m.w(l))
                if lo_i.op == 0x09:
                    v = u32((hi_i.imm << 16) + lo_i.simm)
                    if self.is_code(m, v):
                        self.roots[v] = m
        table_words = set()
        while True:
          changed = True
          while changed:  # the call graph to a fixed point first: only then are all jump tables known
            changed = False
            for root in sorted(self.roots):
                m = self.roots[root]
                seen, labels, tables, calls = self.body(m, root)
                for a, (tab, tg) in tables.items():
                    for n in range(len(tg)):
                        table_words.add((m.name, tab - m.base + 4 * n))
                for t in calls:
                    tm = self.mod_of(t)
                    if tm is None:
                        raise SystemExit(f'{m.name}: call outside the modules {t:#x}')
                    imp = self.import_at(tm, t)
                    if imp:
                        if imp[0] == 'guest' and imp[1] not in self.roots:
                            self.roots[imp[1]] = self.mod_of(imp[1])
                            changed = True
                        continue
                    if t not in self.roots:
                        self.roots[t] = tm
                        changed = True
          added = False
          for m, offs in cand.items():
                for off, v in offs.items():
                    if (m.name, off) in table_words:
                        continue
                    if v not in self.roots:
                        self.roots[v] = m
                        added = True
          if not added:
                break
        self.table_words = table_words

    def fname(self, absaddr):
        m = self.mod_of(absaddr)
        return f'{m.name.lower()}_{absaddr - m.base:04x}'

    def host_name(self, lib, o):
        return f'imp_{lib}_{HOST[lib][o]}'

    def callee(self, m, t):
        """C++ callee for a call/tail-call target, and whether it may park"""
        imp = self.import_at(self.mod_of(t), t)
        if imp and imp[0] == 'host':
            self.hostused.add(imp[1])
            return self.host_name(*imp[1]) + '(c)', imp[1] in BLOCKING
        if imp:
            t = imp[1]
        return self.fname(t) + '(c)', t in self.may_park

    # ---- emission ---------------------------------------------------------------------------------------------
    def alu(self, i, R):
        """C++ statement for a non-control instruction (None: a nop)"""
        op, fn, rs, rt, rd, sa = i.op, i.fn, R(i.rs), R(i.rt), i.rd, i.sa
        a = i.a

        def dst(r, expr):
            if r == 0:
                return None
            return f'{R(r)} = {expr};'
        if op == 0:
            if fn == 0x00:
                if i.w == 0:
                    return None
                return dst(rd, f'{rt} << {sa}' if sa else rt)
            if fn == 0x02:
                return dst(rd, f'{rt} >> {sa}' if sa else rt)
            if fn == 0x03:
                return dst(rd, f'u32(s32({rt}) >> {sa})' if sa else rt)
            if fn == 0x04:
                return dst(rd, f'{rt} << ({rs} & 31u)')
            if fn == 0x06:
                return dst(rd, f'{rt} >> ({rs} & 31u)')
            if fn == 0x07:
                return dst(rd, f'u32(s32({rt}) >> ({rs} & 31u))')
            if fn == 0x0C:
                return f'c.trap(0x{a:08X}u, "syscall");'
            if fn == 0x0D:
                return f'c.trap(0x{a:08X}u, "break {(i.w >> 6) & 0xFFFFF}");'
            if fn == 0x10:
                return dst(rd, 'c.hi')
            if fn == 0x11:
                return f'c.hi = {rs};'
            if fn == 0x12:
                return dst(rd, 'c.lo')
            if fn == 0x13:
                return f'c.lo = {rs};'
            if fn == 0x18:
                return f'mult(c, {rs}, {rt});'
            if fn == 0x19:
                return f'multu(c, {rs}, {rt});'
            if fn == 0x1A:
                return f'div(c, {rs}, {rt});'
            if fn == 0x1B:
                return f'divu(c, {rs}, {rt});'
            if fn in (0x20, 0x21):
                if i.rt == 0:
                    return dst(rd, rs)
                if i.rs == 0:
                    return dst(rd, rt)
                return dst(rd, f'{rs} + {rt}')
            if fn in (0x22, 0x23):
                return dst(rd, f'{rs} - {rt}' if i.rs else f'0u - {rt}')
            if fn == 0x24:
                return dst(rd, f'{rs} & {rt}')
            if fn == 0x25:
                if i.rt == 0:
                    return dst(rd, rs)
                if i.rs == 0:
                    return dst(rd, rt)
                return dst(rd, f'{rs} | {rt}')
            if fn == 0x26:
                return dst(rd, f'{rs} ^ {rt}')
            if fn == 0x27:
                return dst(rd, f'~({rs} | {rt})')
            if fn == 0x2A:
                return dst(rd, f's32({rs}) < s32({rt}) ? 1u : 0u')
            if fn == 0x2B:
                return dst(rd, f'{rs} < {rt} ? 1u : 0u')
            raise SystemExit(f'SPECIAL function {fn:#x} at {a:#x}')
        simm, imm = i.simm, i.imm
        ea = f'{rs} + 0x{simm:X}u' if simm > 0 else (f'{rs} - 0x{-simm:X}u' if simm < 0 else rs)
        if i.rs == 0:
            ea = f'0x{u32(simm):X}u'
        if op in (0x08, 0x09):
            if i.rs == 0:
                return dst(i.rt, f'0x{u32(simm):X}u')
            return dst(i.rt, ea)
        if op == 0x0A:
            return dst(i.rt, f's32({rs}) < {simm} ? 1u : 0u')
        if op == 0x0B:
            return dst(i.rt, f'{rs} < 0x{u32(simm):X}u ? 1u : 0u')
        if op == 0x0C:
            return dst(i.rt, f'{rs} & 0x{imm:X}u')
        if op == 0x0D:
            return dst(i.rt, f'{rs} | 0x{imm:X}u' if i.rs else f'0x{imm:X}u')
        if op == 0x0E:
            return dst(i.rt, f'{rs} ^ 0x{imm:X}u')
        if op == 0x0F:
            return dst(i.rt, f'0x{u32(imm << 16):X}u')
        loads = {0x20: 'lb', 0x21: 'lh', 0x23: 'lw', 0x24: 'lbu', 0x25: 'lhu'}
        if op in loads:
            return dst(i.rt, f'c.{loads[op]}({ea})')
        if op == 0x22:
            return dst(i.rt, f'c.lwl({ea}, {rt})')
        if op == 0x26:
            return dst(i.rt, f'c.lwr({ea}, {rt})')
        stores = {0x28: 'sb', 0x29: 'sh', 0x2B: 'sw', 0x2A: 'swl', 0x2E: 'swr'}
        if op in stores:
            return f'c.{stores[op]}({ea}, {rt});'
        raise SystemExit(f'opcode {op:#x} at {a:#x}')

    def emit_function(self, m, root):
        seen, labels, tables, calls = self.body(m, root)
        resume = []
        used = set()

        def R(r):
            if r == 0:
                return '0u'
            used.add(r)
            return REG[r]
        lines = []
        addrs = sorted(seen)
        first = addrs[0]
        skip = set()
        goto_needed = set()

        def label(t):
            goto_needed.add(t)
            return f'L_{t - m.base:04X}'
        body = []
        for a in addrs:
            if a in skip:
                if a in labels and a != root:
                    # a delay slot that is also a branch target: its own copy, after the branch's fall-through
                    pass
                else:
                    continue
            i = self.insn(m, a)
            k = i.kind()
            if a in labels:
                body.append(('label', a))
            if a in skip:  # delay slot reached by a jump: run it, then fall through to a + 4
                st = self.alu(i, R)
                if st:
                    body.append(('st', st))
                continue
            if k == 'alu':
                st = self.alu(i, R)
                if st:
                    body.append(('st', st))
                continue
            d = self.insn(m, a + 4)
            skip.add(a + 4)
            ds = self.alu(d, R)
            dw = d.writes()
            if k in ('branch', 'regimm'):
                t = u32(a + 4 + (i.simm << 2))
                rs, rt = R(i.rs), R(i.rt)
                if k == 'branch':
                    cond = {4: f'{rs} == {rt}', 5: f'{rs} != {rt}', 6: f's32({rs}) <= 0', 7: f's32({rs}) > 0'}[i.op]
                    if i.op == 4 and i.rs == 0 and i.rt == 0:
                        cond = None
                    reads = {i.rs, i.rt} - {0}
                else:
                    cond = f's32({rs}) < 0' if i.rt == 0 else f's32({rs}) >= 0'
                    reads = {i.rs} - {0}
                if cond is None:
                    if ds:
                        body.append(('st', ds))
                    body.append(('st', f'goto {label(t)};'))
                elif not (dw & reads):
                    if ds:
                        body.append(('st', ds))
                    body.append(('st', f'if ({cond}) goto {label(t)};'))
                else:
                    body.append(('st', f'{{ const bool taken = {cond}; {ds or ""} if (taken) goto {label(t)}; }}'.replace('  ', ' ')))
                if (a + 4) in labels:
                    body.append(('st', f'goto {label(a + 8)};'))
                continue
            if k == 'j':
                t = (a & 0xF0000000) | ((i.w & 0x03FFFFFF) << 2)
                if ds:
                    body.append(('st', ds))
                if t in calls:
                    callee, parks = self.callee(m, t)
                    body.append(('st', f'{callee}; return;  // tail call'))
                else:
                    body.append(('st', f'goto {label(t)};'))
                continue
            if k == 'jal':
                t = (a & 0xF0000000) | ((i.w & 0x03FFFFFF) << 2)
                body.append(('st', f'ra = 0x{a + 8:08X}u;'))
                used.add(31)
                if ds:
                    body.append(('st', ds))
                callee, parks = self.callee(m, t)
                body.append(('st', f'{callee};'))
                if parks:
                    body.append(('st', 'if (c.parked) return;'))
                    if parks is True and self.import_at(self.mod_of(t), t):
                        resume.append(a + 8)
                if (a + 4) in labels:
                    body.append(('st', f'goto {label(a + 8)};'))
                continue
            if k == 'jalr':
                rs = R(i.rs)
                if i.rd in dw or i.rs in dw or i.rs == i.rd:
                    body.append(('st', f'{{ const u32 target = {rs}; {R(i.rd)} = 0x{a + 8:08X}u; {ds or ""} call_address(c, target); }}'))
                else:
                    if i.rd:
                        body.append(('st', f'{REG[i.rd]} = 0x{a + 8:08X}u;'))
                        used.add(i.rd)
                    if ds:
                        body.append(('st', ds))
                    body.append(('st', f'call_address(c, {rs});'))
                body.append(('st', 'if (c.parked) return;'))
                if (a + 4) in labels:
                    body.append(('st', f'goto {label(a + 8)};'))
                continue
            if k == 'jr':
                if i.rs == 31:
                    used.add(31)
                    if 31 in dw:
                        body.append(('st', f'{{ const u32 target = ra; {ds} if (target != ra0) c.bad_return(0x{root:08X}u, target); return; }}'))
                    else:
                        if ds:
                            body.append(('st', ds))
                        body.append(('st', f'if (ra != ra0) c.bad_return(0x{root:08X}u, ra);'))
                        body.append(('st', 'return;'))
                    continue
                rs = R(i.rs)
                tab = tables.get(a)
                pre = f'const u32 target = {rs}; ' + (ds or '')
                if tab is None:
                    body.append(('st', f'{{ {pre} call_address(c, target); return; }}  // indirect tail call'))
                    continue
                cases = ' '.join(f'case 0x{t:08X}u: goto {label(t)};' for t in sorted(set(tab[1])))
                body.append(('st', f'{{ {pre} switch (target) {{ {cases} default: c.bad_jump(0x{a:08X}u, target); return; }} }}'))
                continue
            raise SystemExit(f'unhandled {k} at {a:#x}')
        # assemble
        out = []
        out.append(f'// {m.name} +0x{root - m.base:04X} ({root:#010x})')
        out.append(f'void {self.fname(root)}(Cpu& c) {{')
        regs = sorted(used - {0})
        if regs:
            out.append('    ' + ' '.join(f'u32& {REG[r]} = c.r[{r}];' for r in regs))
        if 31 not in used:
            out.append('    u32& ra = c.r[31];')
        out.append('    u32 ra0 = ra;')
        if resume:
            cases = ' '.join(f'case 0x{t:08X}u: goto L_{t - m.base:04X};' for t in sorted(set(resume)))
            out.append(f'    if (c.resume) {{ const u32 rp = c.resume; c.resume = 0; ra0 = c.resume_ra0; switch (rp) {{ {cases} default: c.bad_jump(0x{root:08X}u, rp); return; }} }}')
            for t in resume:
                goto_needed.add(t)
        if first != root:
            out.append(f'    goto L_{root - m.base:04X};')
            goto_needed.add(root)
        for kind, v in body:
            if kind == 'label':
                if v in goto_needed:
                    out.append(f'L_{v - m.base:04X}:')
            else:
                out.append('    ' + v)
        # a label right before the closing brace needs a statement
        if out[-1].endswith(':'):
            out.append('    ;')
        out.append('    c.fell_off(0x' + f'{root:08X}' + 'u);')
        out.append('}')
        # labels referenced but not emitted (a jump into the middle of a skipped delay slot) are errors
        emitted = {v for kind, v in body if kind == 'label'}
        for t in goto_needed:
            if t not in emitted:
                raise SystemExit(f'{m.name} {root - m.base:#x}: label {t - m.base:#x} not emitted')
        return out, resume

    def analyse_parking(self):
        self.may_park = set()
        changed = True
        while changed:
            changed = False
            for root, m in self.roots.items():
                if root in self.may_park:
                    continue
                seen, labels, tables, calls = self.body(m, root)
                parks = False
                for t in calls:
                    imp = self.import_at(self.mod_of(t), t)
                    if imp and imp[0] == 'host':
                        parks |= imp[1] in BLOCKING
                    else:
                        tt = imp[1] if imp else t
                        parks |= tt in self.may_park
                if parks:
                    self.may_park.add(root)
                    changed = True


def write_if_changed(path, text):
    # always written: the build's custom command (runtime/native/sound/CMakeLists.txt) reruns only when skgen.py or a
    # module file changes, and its outputs must then be newer than both
    with open(path, 'w', newline='\n') as f:
        f.write(text)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--lib', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--report')
    o = ap.parse_args()
    mods = [Irx(n, os.path.join(o.lib, n + '.IRX'), b) for n, b in MODULES]
    g = Gen(mods)
    g.discover()
    g.analyse_parking()
    os.makedirs(o.out, exist_ok=True)
    hdr = ['// Generated by tools/ours/modernize/skgen.py from the six SK IRX modules of the user\'s disc (LIB31); do not edit.',
           '// The functions of SDRDRV, MODHSYN, MODSESQ, SKSOUND, SKHSYNTH and SKSESQ as native C++ (sk_cpu.h; README.md).',
           '#pragma once', '', '#include "sk_cpu.h"', '#include "sk_imports.h"', '#include "sk_modules.h"', '',
           'namespace p3fes::native::sound::sk {', '', 'inline constexpr bool kGenerated = true;', '']
    hdr.append(f'inline constexpr ModuleImage kModules[{len(mods)}] = {{')
    for m in mods:
        hdr.append(f'    {{"{m.name}.IRX", 0x{m.base:08X}u, 0x{m.base + m.entry:08X}u, 0x{m.base + m.gp:08X}u, 0x{m.text:X}u, 0x{m.data:X}u, 0x{m.bss:X}u, 0x{m.text_hash:016X}ull}},')
    hdr.append('};')
    hdr.append('')
    report = []
    total = 0
    tables = []
    for m in mods:
        roots = sorted(r for r, mm in g.roots.items() if mm is m)
        src = [f'// Generated by tools/ours/modernize/skgen.py from {m.name}.IRX (text FNV-1a 64 {m.text_hash:016X}); do not edit.',
               f'// {m.name}: {len(roots)} functions, image at {m.base:#010x} (IopLayout::Pcsx2). One statement per instruction',
               '// (runtime/native/sound/sk/README.md "Generated code").',
               '#include "sk_gen.h"', '',
               '// One statement per instruction: registers a path never reads and the guard after a last return are expected.',
               '#if defined(_MSC_VER) && !defined(__clang__)', '#pragma warning(disable : 4189 4702)', '#endif',
               '#if defined(__clang__)', '#pragma clang diagnostic ignored "-Wunused-variable"',
               '#pragma clang diagnostic ignored "-Wunreachable-code"', '#endif', '',
               'namespace p3fes::native::sound::sk {', '']
        n_insn = 0
        for r in roots:
            lines, resume = g.emit_function(m, r)
            src += lines + ['']
            hdr.append(f'void {g.fname(r)}(Cpu& c);')
            tables.append((r, g.fname(r)))
            n_insn += len(g.body(m, r)[0])
        src.append('}  // namespace p3fes::native::sound::sk')
        write_if_changed(os.path.join(o.out, f'sk_gen_{m.name.lower()}.cpp'), '\n'.join(src) + '\n')
        report.append(f'{m.name}: {len(roots)} functions, {n_insn} instructions emitted (text {m.text // 4} words)')
        big = sorted(((len(g.body(m, r)[0]), r) for r in roots), reverse=True)[:6]
        report.append('    largest: ' + ', '.join(f'{r - m.base:#x}={n}' for n, r in big))
        total += len(roots)
    hdr.append('')
    # every import the code calls must be one sk_imports.h declares (sk_imports.cpp implements)
    imp_h = open(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..', 'runtime', 'native', 'sound', 'sk',
                              'sk_imports.h')).read()
    missing = [g.host_name(lib, o_) for lib, o_ in sorted(g.hostused) if f'void {g.host_name(lib, o_)}(Cpu& c);' not in imp_h]
    if missing:
        raise SystemExit('imports sk_imports.h does not declare: ' + ', '.join(missing))
    hdr.append('// Every function by its IOP address, ascending (call_address, the thread entries).')
    hdr.append(f'inline constexpr FnEntry kFunctions[{len(tables)}] = {{')
    for r, n in sorted(tables):
        hdr.append(f'    {{0x{r:08X}u, &{n}}},')
    hdr.append('};')
    hdr.append('')
    hdr.append('}  // namespace p3fes::native::sound::sk')
    write_if_changed(os.path.join(o.out, 'sk_gen.h'), '\n'.join(hdr) + '\n')
    report.append(f'total {total} functions; host imports used {len(g.hostused)}; may-park {len(g.may_park)}')
    report += g.problems
    txt = '\n'.join(report)
    print(txt)
    if o.report:
        with open(o.report, 'w') as f:
            f.write(txt + '\n')


if __name__ == '__main__':
    main()
