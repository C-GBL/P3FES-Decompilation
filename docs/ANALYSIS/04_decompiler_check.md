# 04 — Hex-Rays MIPS decompiler on R5900 code

## Verdict: ADR-0004 confirmed empirically

* `ida_hexrays.init_hexrays_plugin()` returns **True** for processor `r5900l` (observed); `hexmips.dll` does not refuse the EE processor module and produces output for every function tried.
* **MMI and R5900-specific instructions are not lifted**: every one of them is emitted as an opaque `__asm { … }` block — `padduw`, `mthi1/mtlo1`, `mtsah`, `adda.s`, `sq`, `lq`, `phmadh`, `paddw`, `pxor`, `qfsrv`, `psraw` (observed in `start` `0x100008` and `sub_54F8C8` `0x54f8c8` below). Data flow through them is broken: values enter and leave as raw register pseudo-variables (`_$A6`, `_$T4`, `_$F1`), so the C around the blocks is not a faithful translation.
* **`syscall` is emitted as `__asm { syscall }` with the number dropped** (observed in `start`: the two bare `__asm { syscall }` are SetupThread 0x3C and SetupHeap 0x3D). The decompiler then mis-attributes their argument registers to the next call — `crt_init_runtime(10144896, -1, 655360, …)` is really `SetupHeap(0x9ACC80, -1)` / `SetupThread(…, 0xA0000, …)` leftovers. Pseudocode must never be the source of syscall numbers or crt0 semantics.
* Plain integer code decompiles cleanly: the leaf `sub_106FF0` (`0x106ff0`, 16 instructions, no MMI) becomes a one-line table lookup with no `__asm`.
* Scale of the problem: 1,790 MMI, 41,929 `lq/sq`, and 3,589 COP2 (VU0 macro) instructions across the binary (raw opcode census, 01). `lq/sq` alone appear in virtually every function prologue/epilogue (MW saves 128-bit registers), so almost no non-trivial function is free of `__asm`.

Consequences, unchanged from ADR-0004: Phase 3's recompiler consumes IDA's instruction stream (`ida_ua.decode_insn`/`idc.GetDisasm`), not pseudocode; pseudocode is a reading aid for Phase 5 on integer-heavy game logic (script VM, menus, battle tables) and must be cross-checked against the disassembly wherever an `__asm` block or `_$Rn` pseudo-register appears. The `hexmips` "display" quirk of dropping a leading underscore (`_sceExitThread` shows as `sceExitThread`) is cosmetic; the IDA names are the underscored ones in `symbols/p3fes.sym`.

## Generated data

<!-- GENERATED:BEGIN (export_symbols.py) -->
_Generated 2026-10-21 06:38:58 by `tools/ours/ida/export_symbols.py` from `ida/p3fes.i64` (ELF SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc`). Do not edit inside the markers._

`ida_hexrays.init_hexrays_plugin()` -> **True** with processor `r5900l`.

### crt0 / `start` — `start` `0x00100008`

Result: OK: 61 lines, 8 lines containing `__asm`

```c
void __noreturn start()
{
  __int64 i; // $v0
  const char **v33; // $a2

  __asm
  {
    padduw  $at, $zero, $zero # HINT[tge-pr4] _start
    padduw  $v0, $zero, $zero
    padduw  $v1, $zero, $zero
    padduw  $a0, $zero, $zero
    padduw  $a1, $zero, $zero
    padduw  $a2, $zero, $zero
    padduw  $a3, $zero, $zero
    padduw  $a4, $zero, $zero
    padduw  $a5, $zero, $zero
    padduw  $a6, $zero, $zero
    padduw  $a7, $zero, $zero
    padduw  $t4, $zero, $zero
    padduw  $t5, $zero, $zero
    padduw  $t6, $zero, $zero
    padduw  $t7, $zero, $zero
    padduw  $s0, $zero, $zero
    padduw  $s1, $zero, $zero
    padduw  $s2, $zero, $zero
    padduw  $s3, $zero, $zero
    padduw  $s4, $zero, $zero
    padduw  $s5, $zero, $zero
    padduw  $s6, $zero, $zero
    padduw  $s7, $zero, $zero
    padduw  $t8, $zero, $zero
    padduw  $t9, $zero, $zero
    padduw  $gp, $zero, $zero
    padduw  $sp, $zero, $zero
    padduw  $fp, $zero, $zero
    padduw  $ra, $zero, $zero
  }
  __asm { mthi1   $zero }
  __asm
  {
    mtlo1   $zero
    mtsah   $zero, 0
  }
  _$F1 = 0.0;
  __asm { adda.s  $f0, $f1 }
  _sync();
  __asm { ctc1    $zero, FCSR }
  for ( i = (unsigned int)bss_start; (i & 0xF) != 0; i = (int)i + 1 )
    *(_BYTE *)i = 0;
  while ( i != 10144896 )
  {
    __asm { sq      $zero, 0($v0) }
    i = (int)i + 16;
  }
  __asm { syscall }
  __asm { syscall }
  crt_init_runtime(10144896, -1, 655360, (unsigned int)&crt0_args, (unsigned int)sceExitThread, _$A5, _$A6, _$A7);
  sceFlushCache(0);
  _ei();
  main(crt0_args, (const char **)data_95C284, v33);
}
```

### small leaf function — `sub_106FF0` `0x00106ff0`

Result: OK: 4 lines, 0 lines containing `__asm`

```c
__int64 __fastcall sub_106FF0(__int16 a1)
{
  return *(__int16 *)&data_7E2680[1648 * a1] == 3;
}
```

### MMI-heavy function (42 MMI opcodes, 432 bytes) — `sub_54F8C8` `0x0054f8c8`

Result: OK: 126 lines, 6 lines containing `__asm`

```c
__int64 __fastcall sub_54F8C8(int _$A0, int a2, __int64 a3)
{
  __int64 result; // $v0
  __int64 v5; // $t5
  _WORD *v6; // $t6
  _WORD *v32; // $t6

  result = a3;
  _$T4 = a2;
  LODWORD(v5) = a3;
  v6 = (_WORD *)(a3 + 64);
  do
  {
    __asm
    {
      lq      $a4, 0($a0)
      lq      $a5, 0($t4)
      phmadh  $a6, $a4, $a5
      lq      $a4, 0x10($a0)
      lq      $a5, 0x10($t4)
      phmadh  $a7, $a4, $a5
      paddw   $a6, $a7
      lq      $a4, 0x20($a0)
      lq      $a5, 0x20($t4)
      phmadh  $a7, $a4, $a5
      paddw   $a6, $a7
      lq      $a4, 0x30($a0)
      lq      $a5, 0x30($t4)
      phmadh  $a7, $a4, $a5
      paddw   $a6, $a7
      pxor    $a4, $a4
      mtsah   $a4, 4
      qfsrv   $a7, $a6, $a6
      paddw   $a6, $a7
    }
    __asm
    {
      pxor    $a5, $a5
      mtsah   $a5, 2
      qfsrv   $a7, $a6, $a6
      paddw   $a6, $a7
      psraw   $a6, 0xC
    }
    *(_WORD *)v5 = _$A6;
    *v6 = -(__int16)_$A6 - 1;
    _$T4 += 64;
    v5 = (int)v5 + 2;
    --v6;
  }
  while ( v5 != (_DWORD)a3 + 32 );
  *(_WORD *)v5 = 0;
  _$T4 = _$T4 + 1088;
  LODWORD(v5) = a3 + 66;
  v32 = (_WORD *)(a3 + 126);
  do
  {
    __asm
    {
      lq      $a4, 0($a0)
      lq      $a5, 0($t4)
      phmadh  $a6, $a4, $a5
      lq      $a4, 0x10($a0)
      lq      $a5, 0x10($t4)
      phmadh  $a7, $a4, $a5
      paddw   $a6, $a7
      lq      $a4, 0x20($a0)
      lq      $a5, 0x20($t4)
      phmadh  $a7, $a4, $a5
      paddw   $a6, $a7
      lq      $a4, 0x30($a0)
      lq      $a5, 0x30($t4)
      phmadh  $a7, $a4, $a5
      paddw   $a6, $a7
      pxor    $a4, $a4
      mtsah   $a4, 4
      qfsrv   $a7, $a6, $a6
      paddw   $a6, $a7
    }
    __asm
    {
      pxor    $a5, $a5
      mtsah   $a5, 2
      qfsrv   $a7, $a6, $a6
      paddw   $a6, $a7
      psraw   $a6, 0xC
    }
    *(_WORD *)v5 = _$A6;
    *v32 = _$A6;
    _$T4 += 64;
    v5 = (int)v5 + 2;
    --v32;
  }
  while ( v5 != (_DWORD)a3 + 96 );
  __asm
  {
    lq      $a4, 0($a0)
    lq      $a5, 0($t4)
    phmadh  $a6, $a4, $a5
    lq      $a4, 0x10($a0)
    lq      $a5, 0x10($t4)
    phmadh  $a7, $a4, $a5
    paddw   $a6, $a7
    lq      $a4, 0x20($a0)
    lq      $a5, 0x20($t4)
    phmadh  $a7, $a4, $a5
    paddw   $a6, $a7
    lq      $a4, 0x30($a0)
    lq      $a5, 0x30($t4)
    phmadh  $a7, $a4, $a5
    paddw   $a6, $a7
... [truncated]
```
<!-- GENERATED:END -->
