import re, struct, sys, glob, collections
# Census of frame-time constants: data words equal to 1/30, 1/60, 30.0, 60.0 (and 2/30) in the ELF, and the
# functions of the recompiled program that load them ($gp-relative lwc1/lw, or lui+lwc1 absolute).
elf_path, gen_dir = sys.argv[1], sys.argv[2]
GP = 0x7D2CF0
elf = open(elf_path, 'rb').read()
phoff = struct.unpack_from('<I', elf, 0x1C)[0]
phnum = struct.unpack_from('<H', elf, 0x2C)[0]
want = {0x3D088889: '1/30 s', 0x3C888889: '1/60 s', 0x41F00000: '30.0', 0x42700000: '60.0', 0x3D888889: '1/15 s'}
addr_val = {}
for i in range(phnum):
    t, off, va, pa, fsz, msz, fl, al = struct.unpack_from('<8I', elf, phoff + 32 * i)
    if t != 1: continue
    for o in range(0, fsz - 3, 4):
        a = va + o
        if a < 0x5A2000: continue  # code band
        w = struct.unpack_from('<I', elf, off + o)[0]
        if w in want: addr_val[a] = w
fnre = re.compile(r'^// (\S+) @ 0x([0-9a-f]+)')
ld = re.compile(r'rt::(lwc1|lw)\(ctx, (\d+), (\d+), (-?\d+)\)')
lui = re.compile(r'rt::lui\(ctx, (\d+), 0x([0-9a-f]+)u\)')
uses = collections.defaultdict(lambda: collections.defaultdict(int))  # const addr -> fn -> count
for f in sorted(glob.glob(gen_dir + '/fn_*.cpp')):
    cur = None
    hi = {}
    for line in open(f, encoding='utf-8', errors='replace'):
        m = fnre.match(line)
        if m:
            cur = (m.group(2), m.group(1)); hi = {}
            continue
        m = lui.search(line)
        if m:
            hi[int(m.group(1))] = int(m.group(2), 16) << 16
            continue
        m = ld.search(line)
        if m:
            base, off = int(m.group(3)), int(m.group(4))
            if base == 28: a = (GP + off) & 0xFFFFFFFF
            elif base in hi: a = (hi[base] + off) & 0xFFFFFFFF
            else: continue
            if a in addr_val: uses[a][cur] += 1
by_val = collections.defaultdict(list)
for a, v in sorted(addr_val.items()): by_val[v].append(a)
total_fns = set()
for v, name in want.items():
    addrs = by_val[v]
    fns = set()
    for a in addrs: fns |= set(uses[a].keys())
    total_fns |= fns
    print(f'== {name} (0x{v:08X}): {len(addrs)} data words, {sum(1 for a in addrs if uses[a])} referenced, {len(fns)} functions')
    for a in addrs:
        if not uses[a]: continue
        print(f'  0x{a:08X}: ' + ', '.join(f'{n} {x}' for x, n in sorted(uses[a])))
print('functions using any:', len(total_fns))
