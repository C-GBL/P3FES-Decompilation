"""flirt_audit.py -- strip known-bad FLIRT matches from the master database.

Why this exists (see docs/ANALYSIS/05_flirt.md and ADR-0007): the community PS2 SDK
signature pack bundles x86 host-toolchain libraries (OpenSSL, bfd, Tcl/Tk ...) next to the
Sony/SN/Metrowerks libraries, and FLIRT happily matches their tiny getters/thunks against
unrelated R5900 code.  It also emits `unknown_libname_N` for matches without a name and can
create "functions" inside the data band.  None of those are facts about the binary.

Rules (each stripped name is logged with its rule):
  host-lib         name matches a host-toolchain library prefix (OpenSSL/bfd/Tcl/Tk/readline/zlib/png)
  unknown_libname  IDA placeholder for a nameless signature match
  data-band        FLIRT-derived function starting at/after the end of code (0x5A1400 per 00_elf_layout)
                   -> the bogus function is deleted, not just renamed
  gcc-mangled      Itanium-ABI C++ names (`_ZN...`, libstdc++ iostream getters) below the SDK band
                   (0x4F9000): the game is Metrowerks-built and its GCC-built libraries (CRI) are C,
                   so these tiny-getter matches are collisions. Disable with --keep-gcc-mangled.

Everything else FLIRT produced is KEPT and stays tagged `flirt` (derived) in symbols/p3fes.sym.

Usage (idalib venv python; run from the repo root):
  python tools/ours/ida/flirt_audit.py ida/p3fes.i64 symbols/p3fes.sym [--dry-run] [--log ida/logs/flirt_audit.json]
Then re-export:  python tools/ours/ida/export_symbols.py ida/p3fes.i64 . --apply-names tools/ours/ida/names_manual.txt
"""
import idapro  # must be first

import argparse
import json
import re
import sys
import time

ap = argparse.ArgumentParser()
ap.add_argument("db")
ap.add_argument("sym", help="symbols/p3fes.sym exported after the FLIRT pass (5th field `flirt`)")
ap.add_argument("--dry-run", action="store_true")
ap.add_argument("--log", default="ida/logs/flirt_audit.json")
ap.add_argument("--code-end", type=lambda s: int(s, 16), default=0x5A1400,
                help="first address that is data, hex (default 0x5A1400 from docs/ANALYSIS/00_elf_layout.md)")
ap.add_argument("--sdk-band-start", type=lambda s: int(s, 16), default=0x4F9000,
                help="start of the SCE SDK library band, hex (docs/ANALYSIS/03); GCC-mangled names below it are stripped")
ap.add_argument("--keep-gcc-mangled", action="store_true", help="only report GCC-mangled names below the SDK band, do not strip")
A = ap.parse_args()

HOST = re.compile(r"^(j_)?(SSL_|ssl_|BIO_|EVP_|BN_|X509|RSA_|CRYPTO_|ERR_|ASN1|OBJ_|PEM_|RAND_|DH_|DSA_|"
                  r"bfd_|Tcl|Tk_|tk[A-Z]|readline|rl_|png_|zlib|inflate|deflate|gz[a-z]+$|libiberty|cplus_)")
UNKNOWN = re.compile(r"^unknown_libname_\d+(_\d+)?$")
GCC_MANGLED = re.compile(r"^_Z[NKSt]")

flirt, host_labels = [], []
for ln in open(A.sym, encoding="utf-8"):
    if ln.startswith("#") or not ln.strip():
        continue
    p = ln.split()
    if len(p) >= 5 and any(t.startswith("flirt") for t in p[4:]):
        flirt.append((int(p[0], 16), p[3]))
    elif len(p) >= 4 and p[2] in ("L", "D") and HOST.match(p[3]):
        # FLIRT also names non-function labels/data; those rows carry no `flirt` tag
        host_labels.append((int(p[0], 16), p[3]))
print(f"[audit] FLIRT-tagged records in {A.sym}: {len(flirt)}; host-lib-named labels/data: {len(host_labels)}")
flirt += host_labels

t0 = time.time()
rc = idapro.open_database(A.db, False)
if rc != 0:
    sys.exit(f"open_database rc={rc}")
import ida_auto, ida_funcs, ida_name  # noqa: E402  (idalib must be initialised first)

stripped, kept_suspicious, skipped = [], [], []
for ea, name in flirt:
    cur = ida_name.get_name(ea) or ""
    if cur != name:
        skipped.append({"ea": f"0x{ea:06x}", "sym_name": name, "db_name": cur})
        continue
    if HOST.match(name):
        reason = "host-lib"
    elif UNKNOWN.match(name):
        reason = "unknown_libname"
    elif ea >= A.code_end:
        reason = "data-band"
    elif GCC_MANGLED.match(name) and ea < A.sdk_band_start:
        if A.keep_gcc_mangled:
            kept_suspicious.append({"ea": f"0x{ea:06x}", "name": name})
            continue
        reason = "gcc-mangled"
    else:
        continue
    stripped.append({"ea": f"0x{ea:06x}", "name": name, "rule": reason})
    if A.dry_run:
        continue
    f = ida_funcs.get_func(ea)
    if reason == "data-band":
        if f and f.start_ea == ea:
            ida_funcs.del_func(ea)
        ida_name.set_name(ea, "", ida_name.SN_NOWARN)
        continue
    ida_name.set_name(ea, "", ida_name.SN_NOWARN)       # back to the auto sub_/loc_ name
    if f and f.start_ea == ea and (f.flags & ida_funcs.FUNC_LIB):
        f.flags &= ~ida_funcs.FUNC_LIB
        ida_funcs.update_func(f)

if not A.dry_run:
    ida_auto.auto_wait()

by_rule = {}
for s in stripped:
    by_rule[s["rule"]] = by_rule.get(s["rule"], 0) + 1
summary = {
    "db": A.db, "dry_run": A.dry_run, "flirt_records": len(flirt),
    "stripped_total": len(stripped), "stripped_by_rule": by_rule,
    "kept_suspicious_gcc_mangled_below_sdk_band": len(kept_suspicious),
    "skipped_name_changed_since_export": len(skipped),
    "stripped": stripped, "kept_suspicious": kept_suspicious, "skipped": skipped,
}
import os  # noqa: E402
os.makedirs(os.path.dirname(A.log), exist_ok=True)
json.dump(summary, open(A.log, "w", encoding="utf-8"), indent=1)
print(f"[audit] stripped {len(stripped)} {by_rule}; kept-suspicious {len(kept_suspicious)}; skipped {len(skipped)}; "
      f"log {A.log}; {'DRY RUN' if A.dry_run else 'saving'} ({time.time()-t0:.1f}s)")
idapro.close_database(save=not A.dry_run)
