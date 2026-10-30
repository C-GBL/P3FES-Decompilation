"""PS2 BIOS ROMDIR parser (stdlib only; read-only; never writes ROM bytes anywhere).

Usage:
  python -I tools/ours/ida/bios_romdir.py <bios.bin> [--json OUT.json] [--entry NAME]

A PS2 BIOS image begins with the `RESET` ROMDIR record; the ROMDIR table is a run of
16-byte records {char name[10]; u16 extinfo_size; u32 file_size}. Files are laid out
consecutively from ROM offset 0 in table order, each starting at the 16-byte-aligned
offset after the previous one (`-` entries are alignment padding, the terminating record
has an empty name). The parser:
  * locates the ROMDIR (`RESET` record followed by a `ROMDIR` record),
  * lists every entry (name, offset, size, extinfo size),
  * prints the ROMVER string (version/region/date) so the image can be confirmed,
  * classifies the EE-kernel candidates (`EEKERNEL`? `KERNEL`? `EELOAD`? ...) and for each
    reports whether it is an ELF (and its ELF type/entry/program headers) or raw code
    (first `lui`/`jr`/`mtc0` words), so the load address can be derived with evidence.
With `--entry NAME` it prints only that entry's offset/size (for a loader to read in place).
Only metadata is printed: no ROM bytes beyond ≤4 decoded instruction words per candidate.
"""
import argparse, json, struct, sys

REC = struct.Struct("<10sHI")


def find_romdir(data):
    # RESET record: name "RESET" padded with NULs, then "ROMDIR" record right after it.
    pos = 0
    while True:
        pos = data.find(b"RESET\0\0\0\0\0", pos)
        if pos < 0:
            return -1
        if pos % 16 == 0 and data[pos + 16:pos + 22] == b"ROMDIR":
            return pos
        pos += 1


def parse(data):
    rd = find_romdir(data)
    if rd < 0:
        raise SystemExit("ROMDIR not found (no RESET/ROMDIR record pair)")
    entries, off, p = [], 0, rd
    while p + 16 <= len(data):
        name, ext, size = REC.unpack_from(data, p)
        name = name.rstrip(b"\0").decode("ascii", "replace")
        if not name:
            break
        entries.append({"name": name, "offset": off, "size": size, "extinfo": ext, "record": p})
        off = (off + size + 15) & ~15
        p += 16
    return rd, entries


def decode_mips(word):
    op = word >> 26
    if op == 0x0F:
        return f"lui ${(word >> 16) & 31}, {word & 0xFFFF:#x}"
    if op == 0x0D:
        return f"ori ${(word >> 16) & 31}, ${(word >> 21) & 31}, {word & 0xFFFF:#x}"
    if op == 0x09:
        return f"addiu ${(word >> 16) & 31}, ${(word >> 21) & 31}, {word & 0xFFFF:#x}"
    if op == 0x00 and (word & 0x3F) == 0x08:
        return f"jr ${(word >> 21) & 31}"
    if op == 0x02:
        return f"j {(word & 0x3FFFFFF) << 2:#x}"
    if op == 0x10 and ((word >> 21) & 31) == 4:
        return f"mtc0 ${(word >> 16) & 31}, ${(word >> 11) & 31}"
    if word == 0:
        return "nop"
    return f"<{word:#010x}>"


def describe_candidate(data, e):
    body = data[e["offset"]:e["offset"] + e["size"]]
    info = {"name": e["name"], "offset": e["offset"], "size": e["size"]}
    if body[:4] == b"\x7fELF":
        (e_type, e_machine, _ver, e_entry, e_phoff, _shoff, _flags, _ehsize, _phentsize,
         e_phnum) = struct.unpack_from("<HHIIIIIHHH", body, 16)
        info["format"] = "ELF32"
        info["e_type"], info["e_machine"], info["e_entry"] = e_type, e_machine, e_entry
        phs = []
        for i in range(e_phnum):
            p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, _al = struct.unpack_from(
                "<8I", body, e_phoff + i * 32)
            phs.append({"type": p_type, "offset": p_offset, "vaddr": p_vaddr, "paddr": p_paddr,
                        "filesz": p_filesz, "memsz": p_memsz, "flags": p_flags})
        info["phdrs"] = phs
    else:
        info["format"] = "raw"
        words = [struct.unpack_from("<I", body, i * 4)[0] for i in range(min(4, len(body) // 4))]
        info["first_insns"] = [decode_mips(w) for w in words]
    return info


KERNEL_CLASS = ("KERNEL", "EEKERNEL", "EELOAD", "KROM", "EELOADCNF", "EENULL")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("bios")
    ap.add_argument("--json")
    ap.add_argument("--entry")
    a = ap.parse_args()
    with open(a.bios, "rb") as f:
        data = f.read()
    rd, entries = parse(data)
    if a.entry:
        for e in entries:
            if e["name"] == a.entry:
                print(f"{e['offset']:#x} {e['size']:#x}")
                return 0
        print("not found", file=sys.stderr)
        return 1
    print(f"image size {len(data):#x}; ROMDIR table at {rd:#x}; {len(entries)} records")
    romver = next((e for e in entries if e["name"] == "ROMVER"), None)
    if romver:
        s = data[romver["offset"]:romver["offset"] + romver["size"]].rstrip(b"\0").decode("ascii", "replace")
        print(f"ROMVER = {s!r}")
    print(f"{'name':12s} {'offset':>9s} {'size':>9s} {'ext':>4s}")
    for e in entries:
        print(f"{e['name']:12s} {e['offset']:#9x} {e['size']:#9x} {e['extinfo']:4d}")
    cands = [describe_candidate(data, e) for e in entries if e["name"] in KERNEL_CLASS]
    print("\nkernel-class entries:")
    for c in cands:
        print(json.dumps(c, indent=None))
    if a.json:
        with open(a.json, "w", encoding="utf-8") as f:
            json.dump({"romdir_offset": rd, "entries": entries, "kernel_candidates": cands}, f, indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
