import re, sys, glob, collections, os
# Census of frame-counted logic over the Hex-Rays pseudocode reference (ida/pseudocode/fn/*.c, READ-ONLY hint).
# Heuristic classes per function (a function may be in several):
#   task_timer   calls kwlnTaskGetTimer (the task kernel's per-task frame counter)
#   script_wait  calls scrGetCmdTimer (frames spent in the current script command) or is a WAIT-like command
#   dt_const     loads the 1/30 s constant (0x7CADD4) -- found with the generated code (timeconst.py), listed here
#   rng          calls an RNG (RpRandom*, datCalcRand, rand)
#   counter_cmp  increments / decrements a memory field (++, --, += k, -= k with small integer k) and compares a
#                field against an integer literal >= 2 (frame counts: delays, durations, repeat rates)
#   smoothing    an exponential approach `x + (y - x) * c` with a float literal c in (0, 1) (per-frame lerp: frame-rate
#                dependent: at 60 Hz c must become 1 - sqrt(1 - c))
#   float_step   adds a float literal to a memory field (per-frame velocity / angle step)
# Band (docs/ANALYSIS/27 + topic docs) from the address.
root = sys.argv[1]
bands = [
    (0x100000, 0x190000, 'field/common lo (H_*, field, effects lo)'),
    (0x190000, 0x1A0000, 'kwln kernel / frame loop'),
    (0x1A0000, 0x1E0000, 'field / event / misc'),
    (0x1E0000, 0x2A0000, 'battle UI / title / facilities / effects'),
    (0x2A0000, 0x320000, 'battle (states, actions, data, models)'),
    (0x320000, 0x3B0000, 'battle camera/fx, script VM, misc'),
    (0x3B0000, 0x3D0000, 'scene / messages / comu'),
    (0x3D0000, 0x45EC00, 'facilities / Tartarus / social / UI'),
    (0x45EC00, 0x500000, 'RenderWare'),
    (0x500000, 0x5A2000, 'SDK / CRI / libc'),
]
def band(a):
    for lo, hi, n in bands:
        if lo <= a < hi: return n
    return '?'
dt_const = {0x111610, 0x111CB0, 0x1EDBE0, 0x20AC90, 0x313090, 0x313490, 0x314D30, 0x318770, 0x318870, 0x318910, 0x318990}
rng_names = re.compile(r'\b(RpRandom\w*|datCalcRand|rand|sub_488[0-9A-F]{3})\b')
callee_re = re.compile(r'^// callees \(\d+\): (.*)$')
incr = re.compile(r'(\+\+\*\(|--\*\(|\+\+[a-z]\w*\[|\) \+= [1-9]\b|\) -= [1-9]\b|\)\+\+|\)--)')
cmp_lit = re.compile(r'(>=|<=|==|>|<|!=) (\d+)\b')
smooth = re.compile(r'\+ \(([^;]*?) - ([^;]*?)\) \* (0\.\d+)')
fstep = re.compile(r'\+= (\d+\.\d+)|= \*\(float \*\)[^;]*\+ (\d+\.\d+);')
counts = collections.Counter()
per_band = collections.defaultdict(collections.Counter)
examples = collections.defaultdict(list)
nfun = 0
for f in sorted(glob.glob(os.path.join(root, 'fn', '*.c'))):
    base = os.path.basename(f)
    a = int(base[:8], 16)
    name = base[9:-2]
    txt = open(f, encoding='utf-8', errors='replace').read()
    nfun += 1
    callees = ''
    for line in txt.splitlines()[:12]:
        m = callee_re.match(line)
        if m: callees = m.group(1)
    body = txt.split('\n\n', 1)[-1]
    cls = set()
    if 'kwlnTaskGetTimer' in callees: cls.add('task_timer')
    if 'scrGetCmdTimer' in callees or re.search(r'scrCommand_\w*WAIT', name): cls.add('script_wait')
    if a in dt_const: cls.add('dt_const')
    if rng_names.search(callees): cls.add('rng')
    if incr.search(body) and any(2 <= int(m.group(2)) <= 7200 for m in cmp_lit.finditer(body)): cls.add('counter_cmp')
    if smooth.search(body): cls.add('smoothing')
    if fstep.search(body): cls.add('float_step')
    for c in cls:
        counts[c] += 1
        per_band[band(a)][c] += 1
        if len(examples[c]) < 400: examples[c].append(f'{a:06X} {name}')
    if cls:
        counts['any'] += 1
        per_band[band(a)]['any'] += 1
    per_band[band(a)]['functions'] += 1
print('functions scanned:', nfun)
for c, n in counts.most_common(): print(f'{c:12s} {n}')
print()
cols = ['functions', 'any', 'counter_cmp', 'task_timer', 'script_wait', 'smoothing', 'float_step', 'rng', 'dt_const']
print('| band | ' + ' | '.join(cols) + ' |')
for lo, hi, n in bands:
    print(f'| {n} | ' + ' | '.join(str(per_band[n][c]) for c in cols) + ' |')
for c in ['task_timer', 'script_wait', 'rng', 'smoothing']:
    print('\n##', c, len(examples[c]))
    print('  ' + ', '.join(examples[c][:60]))
