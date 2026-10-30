"""A shared object cache for the GENERATED translation units (recomp/generated/fn_*.cpp, the tests' gen_units_NN.cpp),
used as a CMake compiler launcher (-DP3FES_UNIT_CACHE=<dir>; recomp/CMakeLists.txt, tests/rt/CMakeLists.txt).

Every slice worktree compiles the same ~75 generated units (they differ only where a slice's replacements are), so a
fresh worktree's first build can take most of them from another tree's compile. The cache works like ccache's direct
mode, restricted to what generated code needs:

  key   = SHA-256 of the compiler (path, size, mtime), the command line with the source tree and build tree replaced by
          placeholders (minus /Fo and /Fd), the INCLUDE / CL / _CL_ environment, the source path relative to its tree
          and the source's content;
  entry = <cache>/m/<key>.json: the files the compile read (/showIncludes) -- content SHA-1 for files inside the
          source or build tree (recorded relative to it), size+mtime for the others (the compiler's and SDK's
          headers) -- and the SHA-256 of the object, stored as <cache>/o/<sha>.obj.
  hit   = every recorded file still has its recorded hash: the object is copied to /Fo and the include lines are
          printed again with THIS tree's paths (ninja's msvc deps parser reads them), so dependency tracking stays
          exact in every worktree.

Only compiles with /showIncludes are cached (anything else runs the compiler unchanged); a failed compile is never
stored; writes are atomic (temp file + rename) and best-effort, so concurrent builds in several worktrees are safe.
The cache prunes itself (least recently used objects) beyond P3FES_UNIT_CACHE_MAX_GB (default 12).
Generated code has no __FILE__ or other path-dependent text, which is what makes sharing objects across worktrees
exact; do not attach this launcher to hand-written code that embeds paths (doctest, asserts).

usage: python -I unit_cache.py --cache <dir> --root <source tree> --build <build tree> -- <compiler> <args...>
"""
import hashlib, json, os, random, shutil, subprocess, sys, tempfile, time


def die_through(cmd):
    """Run the compiler unchanged (no caching) and exit with its code."""
    sys.exit(subprocess.call(cmd))


def norm(p):
    return os.path.normcase(os.path.abspath(p))


def sha1_file(path):
    h = hashlib.sha1()
    with open(path, 'rb') as f:
        for b in iter(lambda: f.read(1 << 20), b''):
            h.update(b)
    return h.hexdigest()


class Trees:
    """Maps paths inside the source / build tree to placeholders and back."""

    def __init__(self, root, build):
        # build first: it may lie inside root. Compared case-insensitively (normcase), written with the given case.
        self.items = [('<BUILD>', norm(build)), ('<ROOT>', norm(root))]
        self.real = {'<BUILD>': os.path.abspath(build), '<ROOT>': os.path.abspath(root)}

    def rel(self, path):
        a = os.path.abspath(path)
        n = os.path.normcase(a)
        for tag, base in self.items:
            if n == base or n.startswith(base + os.sep):
                return tag + a[len(base):]  # the remainder keeps its case (ninja records it as given)
        return None

    def abs(self, rel):
        for tag, base in self.items:
            if rel.startswith(tag):
                return self.real[tag] + rel[len(tag):]
        return rel

    def text(self, s):
        """Replace both trees in a command-line argument (any case, either slash)."""
        low = s.lower().replace('/', '\\')
        out = s
        for tag, base in self.items:
            b = base.lower()
            i = low.find(b)
            while i >= 0:
                out = out[:i] + tag + out[i + len(b):]
                low = low[:i] + tag.lower() + low[i + len(b):]
                i = low.find(b, i + len(tag))
        return out


def dep_sig(trees, path):
    """(recorded name, signature) of a file the compile read."""
    r = trees.rel(path)
    if r is not None:
        return r, 'sha1:' + sha1_file(path)
    st = os.stat(path)
    return os.path.abspath(path), 'stat:%d:%d' % (st.st_size, st.st_mtime_ns)


def still_valid(trees, deps):
    for name, sig in deps:
        path = trees.abs(name)
        try:
            if sig.startswith('sha1:'):
                if 'sha1:' + sha1_file(path) != sig:
                    return False
            else:
                st = os.stat(path)
                if 'stat:%d:%d' % (st.st_size, st.st_mtime_ns) != sig:
                    return False
        except OSError:
            return False
    return True


def atomic_write(path, data):
    d = os.path.dirname(path)
    fd, tmp = tempfile.mkstemp(dir=d, prefix='.tmp-')
    try:
        with os.fdopen(fd, 'wb') as f:
            f.write(data)
        for _ in range(5):
            try:
                os.replace(tmp, path)
                return True
            except PermissionError:  # a reader holds the target open (Windows)
                time.sleep(0.05)
    finally:
        if os.path.exists(tmp):
            os.remove(tmp)
    return False


def prune(cache):
    limit = float(os.environ.get('P3FES_UNIT_CACHE_MAX_GB', '12')) * (1 << 30)
    objs = []
    for e in os.scandir(os.path.join(cache, 'o')):
        if e.name.endswith('.obj'):
            st = e.stat()
            objs.append((st.st_mtime, st.st_size, e.path))
    total = sum(o[1] for o in objs)
    if total <= limit:
        return
    for mtime, size, path in sorted(objs):  # oldest use first (a hit touches its object)
        try:
            os.remove(path)
            total -= size
        except OSError:
            pass
        if total <= 0.7 * limit:
            break


def main():
    a = sys.argv[1:]
    if '--' not in a:
        sys.exit('unit_cache: usage: --cache <dir> --root <dir> --build <dir> -- <compiler> <args...>')
    sep = a.index('--')
    opts, cmd = a[:sep], a[sep + 1:]
    o = dict(zip(opts[0::2], opts[1::2]))
    cache, root, build = o.get('--cache'), o.get('--root'), o.get('--build')
    if not cache or not cmd:
        die_through(cmd)
    trees = Trees(root, build)
    args = cmd[1:]
    obj = next((x[3:] for x in args if x[:3].lower() in ('/fo', '-fo') and len(x) > 3), None)
    src = next((x for x in reversed(args) if x.lower().endswith(('.cpp', '.cc', '.cxx', '.c'))), None)
    if not obj or not src or not any(x.lower() in ('/showincludes', '-showincludes') for x in args):
        die_through(cmd)
    if any(x.lower().startswith(('/zi', '-zi', '/z7', '-z7')) for x in args):
        die_through(cmd)  # debug information records source paths (or lives in a PDB): never shared (Debug trees)
    src_abs = src if os.path.isabs(src) else os.path.join(os.getcwd(), src)
    obj_abs = obj if os.path.isabs(obj) else os.path.join(os.getcwd(), obj)
    try:
        st = os.stat(cmd[0]) if os.path.isabs(cmd[0]) else os.stat(shutil.which(cmd[0]))
        h = hashlib.sha256()
        h.update(('compiler %s %d %d\n' % (norm(cmd[0]), st.st_size, st.st_mtime_ns)).encode())
        for x in args:
            if x[:3].lower() in ('/fo', '-fo', '/fd', '-fd'):
                continue
            h.update(trees.text(x).encode() + b'\0')
        for v in ('INCLUDE', 'CL', '_CL_'):
            h.update(('%s=%s\n' % (v, trees.text(os.environ.get(v, '')))).encode())
        h.update(((trees.rel(src_abs) or norm(src_abs)) + '\n' + sha1_file(src_abs)).encode())
        key = h.hexdigest()
    except OSError:
        die_through(cmd)
    for d in ('m', 'o'):
        os.makedirs(os.path.join(cache, d), exist_ok=True)
    man_path = os.path.join(cache, 'm', key + '.json')

    # lookup
    entries = []
    try:
        with open(man_path, 'rb') as f:
            entries = json.loads(f.read())
    except (OSError, ValueError):
        entries = []
    for ent in entries:
        cobj = os.path.join(cache, 'o', ent['obj'] + '.obj')
        if os.path.exists(cobj) and still_valid(trees, ent['deps']):
            try:
                shutil.copyfile(cobj, obj_abs)
                os.utime(cobj)
            except OSError:
                break  # fall back to compiling
            out = ''.join(ent['prefix'] + ' ' + trees.abs(n) + '\n' for n in ent['includes'])
            sys.stdout.write(out)
            sys.stdout.flush()
            return 0

    # miss: compile, pass the output through, store the result
    t_start = time.time()
    p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    sys.stdout.buffer.write(p.stdout)
    sys.stdout.flush()
    sys.stderr.buffer.write(p.stderr)
    sys.stderr.flush()
    if p.returncode != 0 or not os.path.exists(obj_abs):
        return p.returncode
    try:
        # cl writes the include notes to stdout; read stderr too (clang-cl versions differ; ninja merges both)
        text = p.stdout.decode('utf-8', 'replace') + '\n' + p.stderr.decode('utf-8', 'replace')
        prefix, includes = None, []
        for line in text.splitlines():
            i = line.find(': ')
            # "Note: including file:   <path>" (the prefix is localised; it is the text up to the second colon)
            j = line.find(':', i + 2) if i >= 0 else -1
            if j > 0 and line[j + 1:].startswith(' ') and os.path.isabs(line[j + 1:].strip()):
                cand = line[:j + 1]
                if prefix is None:
                    prefix = cand
                if cand == prefix:
                    includes.append(line[j + 1:].strip())
        if prefix is None:
            with open(src_abs, 'rb') as f:
                if b'#include' in f.read():
                    raise RuntimeError('no include notes in the compiler output')  # never store an entry without deps
            prefix = 'Note: including file:'
        for f in [src_abs] + includes:  # a file written while it compiled: the object may hold either text
            if os.stat(f).st_mtime > t_start:
                raise RuntimeError('%s changed during the compile' % f)
        deps = [dep_sig(trees, src_abs)]
        seen = set()
        names = []
        for inc in includes:
            n, sig = dep_sig(trees, inc)
            names.append(n)
            if n not in seen:
                seen.add(n)
                deps.append([n, sig])
        with open(obj_abs, 'rb') as f:
            data = f.read()
        osha = hashlib.sha256(data).hexdigest()
        cobj = os.path.join(cache, 'o', osha + '.obj')
        if not os.path.exists(cobj):
            atomic_write(cobj, data)
        try:
            with open(man_path, 'rb') as f:
                entries = json.loads(f.read())
        except (OSError, ValueError):
            entries = []
        entries = [e for e in entries if e.get('obj') != osha][-7:] + [
            {'obj': osha, 'deps': deps, 'prefix': prefix, 'includes': names}]
        atomic_write(man_path, json.dumps(entries).encode())
        if random.random() < 0.05:
            prune(cache)
    except Exception as e:  # the cache is best-effort; the compile itself succeeded
        sys.stderr.write('unit_cache: not stored (%s)\n' % e)
    return 0


if __name__ == '__main__':
    sys.exit(main())
