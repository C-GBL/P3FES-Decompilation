# 18 — BF script VM (`FLW0`) and BMD message system (`MSG1`)

_Phase 5 analysis, second area (GOAL.md: "file system layer, BF script VM, BMD message rendering, …"). Database: `ida/work_script.i64` (copy of the master, opened headless; logs `ida/logs/script_vm_q1..q9.txt`). Every address is an EE virtual address. Tags: **obs** = read from the instructions / table bytes, **der** = derived arithmetically from an obs (gp offsets, table sizes), **inf** = inferred. The copy carries the community hint names as IDA comments (`HINT[tge-pr4]`, `HINT[snaku]`); every name used below was verified from the instructions before it was used, and `symbols/p3fes.sym` still exports most of them as `sub_*` (ADR-0009), so the `sub_*` name is given alongside. Names proposed/promoted: `symbols/deltas/script_vm.sym` (merged into the master and re-exported 2026-10-20: every name of the delta is now the IDA name in `symbols/p3fes.sym`; the `sub_*` forms quoted below are the names before that merge). Formats: `docs/FORMATS.md` §2 (BF) and §3 (BMD), `runtime/formats/bf.h`, `bmd.h`._

## 0. Headline

* **The BF interpreter is a function-pointer table, not a `jr` switch.** `scrTraceCode 0x35EBF0` (`sub_35EBF0`) reads the `u16 opcode` of the current instruction word, asserts `0 <= opcode < 35` (`scrTraceCode.c` lines 895/896 at `0x35EC20`/`0x35EC48`, obs) and calls `sScrOpcodeTbl[opcode]` at **`0x69D3E0`** (35 × u32, obs; `li $v0, 0x69D3E0; jalr` at `0x35EC90–0x35ECA0`). The table order equals `BfOpcode` in `runtime/include/p3fes/formats/bf.h` exactly (§2 table). Each handler takes the script task record in `$a0` and returns 1 (continue), 2 (yield) or 0 (script ended).
* **`scrExecOpcode_candidate 0x30FDF0` / `scrOpcodeJumpTable_candidate 0x7B90A0` are mis-named** (fes-pc-recomp, MIT, exported). The function asserts with `"datScript.c"` (`aDatscriptC`, lines 190–459, obs) and its 35-way `jr` switch (`symbols/jumptables.json` `jr_ea 0x30fe28`, 35 cases, default `0x311140`) selects a *battle data value* for a `(selector, unit-side)` pair — level, HP, max HP, skill fields of `dword_957190`/`dword_957194` (`datCalcGetLevel`, `datCalcGetHp`, `datCalcGetMaxHp` calls, obs). It is the `datScript.c` variable getter (279 callers), unrelated to `FLW0`. The 35-case coincidence is what misled the hint. Proposed names in the delta: `datScriptGetValue`, `tbl_datScriptGetValue_switch`.
* **COMM table verdict: confirmed from the bytes.** `sScrCommandTable 0x7B92B0` (`sub_*`-free name from tge-pr4, verified) is **502 entries × { u32 function, u32 argc }** (`0x7B92B0–0x7BA260`, obs); the entry count `0x1F6 = 502` is the dword at **`0x7BA260`** immediately after the table (obs; `CodeFunc_Comm 0x35CF20` bounds-checks the operand against it, line 343). 14 entries have a null function (`0x004, 0x005, 0x011, 0x01D–0x020, 0x022–0x025, 0x029, 0x02D, 0x02F`; asserted at line 344 if called); all 488 others point at function starts. argc histogram: 0 ×149, 1 ×231, 2 ×94, 3 ×14, 4 ×7, 5 ×1, 6 ×4, 7 ×1, 8 ×1. The only reader is `CodeFunc_Comm` (`li $v0, 0x7B92B0` at `0x35CF98`, obs). Entry 0 is `sub_3A2150` (1 arg): the **MSG** command (requests message `arg0` on the script's message handle, §5).
* **Loader / magic:** `scrStartScript2 0x35B930` (`sub_35B930`) is the only `FLW0` check: bytes `+8..+11 == 'F','L','W','0'` (`0x35B96C–0x35B9A0`, obs; `K_Abort("invalid script data!!", "scrScriptProcess.c", 280)` otherwise), then it walks the 5 section descriptors at `+0x20` by **type** (0 procedure labels, 1 jump labels, 2 instructions, 3 message data — taken only if `element_count != 0`, 4 strings; any other type aborts at line 306) and calls `scrStartScript 0x35B570`. `MSG1` is checked in `itfMesMngCheckBmdMagic 0x3A5090`: `+8 == 0x3047534D ('MSG0') || == 0x3147534D ('MSG1')` (obs). No code compares `'FLW0'` as a 32-bit immediate (imm32 scan of all code: only the two `MSG1` sites `0x3A4320`, `0x3A50AC`).
* **Entry points game code calls:** `scrCreateTaskFromHeader 0x35BB40` (20 callers: `K_Field_UpdateFieldRootTask`, `K_FldEvent_UpdateFldEventTask`, `K_Footstep_*`, `Y_Misc_*`…), `scrCreateTaskFromScriptMemory 0x35BC00` (27 callers; copies the BF into an `H_Malloc` buffer first), `scrCreateTask 0x35BD50` (from `scrCommand_SCR_RUN 0x35B280`, script-spawned scripts). `K_Data_LoadFldMainScript 0x1B7B10` (`sub_1B7B10`, called once from `kwlnInitMain+0x2DC`) loads `field/script/field.bf` through `H_Cdvd_Request/ReadSync` into an `RwHeapCalloc` copy whose pointer/size go to `gp-0x4AC8/-0x4ACC` (= `0x7CE228`/`0x7CE224`, der): the resident field script. Message handles are created by `itfMesMngInitialize 0x3A2D80` (12 callers, one of them `scrStartScript` for BF section 3).

Confidence: **high** for §1–§4 and §6 (every statement read from instructions); **medium** for §5 beyond the request path (the renderer's layout code was only skimmed).

## 1. Source files and address bands (obs: `K_Assert(file, line)` strings)

| Atlus file | Band | Content |
|---|---|---|
| `scrScriptProcess.c` | `0x35B570–0x35C2FC` | task creation/release, list of running scripts |
| `scrTraceCode.c` | `0x35C300–0x35F160` | the 35 opcode handlers, `scrOperation`, `scrTraceCode`, COMM parameter accessors |
| `scrCommonCommand.c` | `0x35AEB0–0x35B570` | generic COMM functions (`BIT_CHK`, `RAND`, `WAIT`, `SCR_RUN`, …) |
| `scrComuCommand.c` | `0x35F170–0x360ED0` | social-link COMM functions (table at `0x7B9680+`, consulted by the comu system, not by `CodeFunc_Comm`) |
| `itfMesManager.c` | `0x3A2150–0x3A8800` | message handles, request/draw state machine, draw types |
| `frFont.c`, `frFontEx.c`, `frTagTable.c`, `frFontRaster.c`, `fmGslCont.c` | `0x3AC5A0–0x3B4800` | text token walker, tag handlers, glyph rasteriser |
| `datScript.c` | `0x30FC40–0x3112C0` | battle data script variables (the mis-named "opcode" switch) |

## 2. The interpreter

### 2.1 Step function `scrTraceCode 0x35EBF0` (obs, `ida/logs/script_vm_q1.txt`)

```
loop:
  op = *(s16*)(task->insn + 4*task->pc)          ; lw 0x18 / lw 0xBC / lh 0
  assert 0 <= op < 35                            ; lines 895, 896
  if (g_scrTraceFlag == 1) H_Dbprt_FmtLog(">>>SCRIPT TRACE <0x%X>\n", operand)   ; gp-0x4AE8 = 0x7CE208 (der)
  r = sScrOpcodeTbl[op](task)                    ; 0x69D3E0
  r == 0 -> task->cmd_timer = 0; return 2        ; script ended (END with empty call stack)
  r == 2 -> break                                ; command yields this frame
  r == 1 -> task->cmd_timer = 0; goto loop       ; next instruction, same frame
task->cmd_timer++ (+0xD4); task->frames++ (+0xD0); return 1
```
`scrScriptProcess 0x35C270` is the per-frame task body (`dds3GetProcessWorkData` → `scrTraceCode`; 2 → `-1` = task done, 1 → 0, anything else `K_Abort(..., 1120)`); `scrForceTraceCode 0x35C250` runs one step synchronously. Only these two call `scrTraceCode` (obs).

### 2.2 Opcode table `sScrOpcodeTbl 0x69D3E0` (obs, 35 × u32; `.sym` names in parentheses)

| # | mnemonic (`bf.h`) | handler | behaviour (obs) |
|---|---|---|---|
| 0 | PUSHI | `CodeFunc_PushI 0x35C300` (`sub_35C300`) | push s32 from the next word, tag 0; pc += 2 |
| 1 | PUSHF | `CodeFunc_PushF 0x35C450` | push f32 from the next word, tag 1; pc += 2 |
| 2 | PUSHIX | `CodeFunc_PushIX 0x35C500` | push `g_scrGlobals->ints[operand]`, tag 0 |
| 3 | PUSHIF | `CodeFunc_PushIF 0x35C5B0` | push `g_scrGlobals->floats[operand]` (block +1024), tag 1 |
| 4 | PUSHREG | `CodeFunc_PushREG 0x35C870` | push the COMM return register (slot 27: tag `+0x3B`, value `+0xA8`) |
| 5 | POPIX | `CodeFunc_PopIX 0x35C900` | pop as int → `ints[operand]` |
| 6 | POPFX | `CodeFunc_PopFX 0x35CA70` | pop as float → `floats[operand]` |
| 7 | PROC | `CodeFunc_Proc 0x35CF00` | pc += 1 (**replaced**, §7) |
| 8 | COMM | `CodeFunc_Comm 0x35CF20` | §2.4 |
| 9 | END | `CodeFunc_End 0x35D040` | call stack empty → return 0 (script over); else pop a tag-4 slot (assert, line 383) → pc = value + 1 |
| 10 | JUMP | `CodeFunc_Jmp 0x35D1D0` | pc = proc_labels[operand].insn (**replaced**) |
| 11 | CALL | `CodeFunc_Call 0x35D210` | push pc with tag 4; pc = proc_labels[operand].insn |
| 12 | RUN | `CodeFunc_Run 0x35D2C0` | `K_Abort("CodeFunc_Run(..) Can't running command!!", 416)`; pc += 1 — unimplemented |
| 13 | GOTO | `CodeFunc_Goto 0x35D310` | pc = jump_labels[operand].insn (**replaced**) |
| 14–17 | ADD SUB MUL DIV | `0x35DFE0 0x35E020 0x35E060 0x35E0A0` | `scrOperation(task, 0..3)`; `sub_35E060` = MUL (`li $a1, 2` at `0x35E070`) |
| 18 | MINUS | `CodeFunc_Minus 0x35E0E0` | negate the top slot in place (int or float by tag; globals through their index) |
| 19 | NOT | `CodeFunc_Not 0x35E250` | pop, push `== 0` as int |
| 20 | OR | **`0x35E650`** (`sub_35E650`, hint "CodeFunc_And" — wrong) | `scrOperation(task, 4)` = `lhs != 0 \|\| rhs != 0` (`li $a1, 4` at `0x35E660`; case 4 at `scrOperation`) |
| 21 | AND | **`0x35E690`** (`sub_35E690`) | `scrOperation(task, 5)` = `&&` (`li $a1, 5` at `0x35E6A0`) |
| 22–27 | EQ NEQ S L SE LE | `0x35E6D0 … 0x35E810` | `scrOperation(task, 6..11)`: `==`, `!=`, `<`, `>`, `<=`, `>=` |
| 28 | IF | `CodeFunc_IF 0x35E850` | pop (int or float by tag); non-zero → pc += 1, zero → pc = jump_labels[operand].insn |
| 29 | PUSHIS | `CodeFunc_PushS 0x35C3B0` | push the sign-extended 16-bit operand, tag 0 |
| 30 | PUSHLIX | `CodeFunc_PushLIX 0x35C660` | push `local_ints[operand]` (task `+0xDC`) |
| 31 | PUSHLFX | `CodeFunc_PushLFX 0x35C710` | push `local_floats[operand]` (task `+0xE0`), tag 1 |
| 32 | POPLIX | `CodeFunc_PopLIX 0x35CC00` | pop as int → `local_ints[operand]` |
| 33 | POPLFX | `CodeFunc_PopLFX 0x35CD70` | pop as float → `local_floats[operand]` |
| 34 | PUSHSTR | `CodeFunc_PushSTR 0x35C7C0` | push `strings + operand` (task `+0xC4`), tag 5 |

Every handler reads the operand as `lh 2(insn)` (sign-extended) and the next value word as `lw 4(insn)`. "pc" is a word index (`sll 2` before the add, obs everywhere).

### 2.3 Operand stack and value tags (obs)

The task holds 28 slots: a tag byte at `+0x20 + i` and a u32 value at `+0x3C + 4*i`; `+0x1C` is the slot count (assert `< 27` before every push, `> 0` before every pop). Slot 27 doubles as the COMM return register. Tags seen in the code: **0 int, 1 float, 2 global-int index, 3 global-float index, 4 return address (CALL), 5 string pointer**. The pop helpers accept 0–4 (2/3 dereference `g_scrGlobals`), abort on anything else (`"PopInt(..) invalid stack type!!"` line 135, `"PopFloat(..) …(RET)"` 152 / `(?)` 161); in this build no handler *pushes* tag 2 or 3 (PUSHIX/PUSHIF push the value) — they are legacy. `scrOperation 0x35D350` pops two slots (top first), works in float when either tag is 1/3 and in int otherwise, and pushes the int/float result with tag 0/1; the integer and float halves are the two 12-case `jr` switches at `0x35D624` (table `0x7BA2A0`) and `0x35DAE0` (table `0x7BA270`) (`jumptables.json`, obs). DIV asserts on a zero divisor (line 527). The value on top of the stack is the *left* operand (`result = first_pop OP second_pop`, obs in cases 1 and 8).

Globals (der from gp = `0x7D2CF0`): `g_scrGlobals = *(u32*)0x7CCA5C` → `0x957C00` (ints at `+0`, floats at `+1024`); `g_scrCurrentTask 0x7CE5A8` (set by `CodeFunc_Comm` before the call, read by every `scrGet*Para`); task list head/tail/count `0x7CE580 / 0x7CE584 / 0x7CE57C`; `g_scrTraceFlag 0x7CE208`; `scrOperation` scratch `0x7CE590–0x7CE5A4`.

### 2.4 COMM dispatch `CodeFunc_Comm 0x35CF20` (obs)

```
id = operand; assert id >= 0 && id < *(0x7BA260)        ; lines 342, 343
fn = sScrCommandTable[id].function; assert fn           ; line 344
g_scrCurrentTask = task
if (fn()) { task->sp -= sScrCommandTable[id].argc; if (pc unchanged) pc++; return 1 }
else return 2                                            ; command still running: re-executed next frame
```
Arguments are therefore read *in place* by the command through `scrGetIntPara(i) 0x35ED20` (`sub_35ED20`, 497 callers): slot `sp-1-i`, converted by tag (float → `(int)`); `scrGetFloatPara 0x35EE60` returns the *address* of the value; `scrGetStrPara 0x35EFA0` requires tag 5. Results go through `scrSetIntReturnVal 0x35F060` (`sub_35F060`, 333 callers: `sb 0, 0x3B; sw $a0, 0xA8` on the current task) / `scrSetFloatReturnVal 0x35F080` (tag 1). A command that returns 0 keeps the pc, so the next `scrTraceCode` re-enters it with the same arguments — this is how `WAIT`/`SYNC` and the message commands block; `task->cmd_timer` (`+0xD4`, `scrGetCmdTimer 0x35F130`) counts the frames spent in the current command. A command may also move the pc itself (`scrCommand_SWITCH 0x35B110` → `scrGetLabelAddr 0x35F0A0` + `scrSetPC 0x35F120`), in which case `CodeFunc_Comm` does not increment it.

Verified COMM functions (names from the hint, behaviour read): `0x35AEB0 BIT_CHK` → `MT_Misc_BitChk(arg0)` → return value; `0x35AEF0` (`sub_35AEF0`) → `MT_Misc_BitOn` with `assert arg0 < 0x1600` (= BIT_ON); `0x35AF50 BIT_OFF`; `0x35AFB0 RAND` → `RpRandom() % (arg0+1)`; `0x35B000 SYNC` → done when `cmd_timer != 0` (one frame); `0x35B030 WAIT` → done when `cmd_timer >= arg0`; `0x35B090 PUT` → `printf("PUT -> %d\n")`; `0x35B280 SCR_RUN` → `scrCreateTask` of procedure `arg0` from the *current* script's sections, returns the dds3 handle; `0x35B390 SCR_KILL`; `0x35B440 SCR_EXISTS`; `0x35B4A0 SCR_GET_TIMER`; `0x35B110 SWITCH(sel, l0..l6)` → jump to label `arg[sel+1]`. COMM 0 `sub_3A2150` = MSG (§5.2), 1 `sub_3A2900` (message window type 4 + flag `0x200000`), 2 `sub_3A2970` (wait for the window to close), 3 `sub_3A2660` (selection, returns the chosen option through `scrSetIntReturnVal(*(s16*)(handle+86))`), 6 `sub_3A28A0`.

## 3. Script task record `ScrTask` (252 bytes, `H_Malloc` in `scrStartScript 0x35B570`; obs, offsets from the stores at `0x35B5E8–0x35B7C0`)

| off | type | meaning | evidence |
|---|---|---|---|
| `+0x00` | `char[24]` | name of the start procedure (copied from the label) | copy loop `0x35B60C` |
| `+0x18` | s32 | **pc** (instruction word index), seeded with `label.insn` | `sd` of the zero-extended u32 at `+0x18` also clears `+0x1C` |
| `+0x1C` | s32 | stack slot count | asserts `< 27` / `> 0` |
| `+0x20` | `u8[28]` | slot tags (§2.3); `+0x3B` = tag of the return register | `scrSetIntReturnVal` |
| `+0x3C` | `u32[28]` | slot values; `+0xA8` = return register | — |
| `+0xAC` | u32 | BF image base (header) | arg a1 |
| `+0xB0` | u32 | section table (`base + 0x20`) | arg a2 (`scrStartScript2` passes `a1 + 32`) |
| `+0xB4` | u32 | procedure labels (section 0, 32-byte records, `+0x18` = insn index) | JUMP/CALL |
| `+0xB8` | u32 | jump labels (section 1) | GOTO/IF |
| `+0xBC` | u32 | instruction words (section 2) | every handler |
| `+0xC0` | u32 | message data (section 3) or 0 | `scrStartScript`: `if (a6) itfMesMngInitialize(a6)` |
| `+0xC4` | u32 | string table (section 4) | PUSHSTR |
| `+0xC8` | s32 | start procedure index | `printf("procedure start <%s>")` |
| `+0xCC` | s32 | message handle (`-1` none), `scrGetMessageID 0x35F140` | `itfMesMngInitialize` result; window type set to 4 |
| `+0xD0` | s32 | frames executed (yields) | `scrTraceCode` |
| `+0xD4` | s32 | command timer (`scrGetCmdTimer`) | `scrTraceCode` |
| `+0xD8` | u32 | owned copy of the BF (`scrCreateTaskFromScriptMemory`) or 0, freed on release | `scrReleaseScript` "free script memory" |
| `+0xDC` | u32 | local ints: `H_Malloc(4 * (s16)header[+0x14])`, assert count `< 256` (line 202) | **resolves `FORMATS.md` §2 "unknown +14"**: `+0x14` = local int count, `+0x16` = local float count (assert `< 128`, line 214) |
| `+0xE0` | u32 | local floats | — |
| `+0xE4` | u32 | dds3 process handle (`dds3InitProcess(name, prio, 1, 1, scrScriptProcess, scrDestroyTask, task)`) | `scrCreateTask*` |
| `+0xE8/+0xEC` | u32 | prev / next in the running-script list (`0x7CE580/0x7CE584`, count `0x7CE57C`) | `scrStartScript` tail, `scrReleaseScript` |
| `+0xF0` | u32 | user word: written by `sub_35C1A0` (`scrSetUserData`, proposed) on the current process' work data, read by `sub_35F160` (`scrGetUserData`, 206 callers in the battle/field command sets) | obs |

`scrReleaseScript 0x35BE30` frees `+0xDC`, `+0xE0`, the message handle (`itfMesMngDestroyHandle 0x3A3060`) and `+0xD8`, unlinks and `H_Free`s the record; `scrDestroyTask 0x35C200` is the dds3 destructor that calls it. `scrFindPrcdIdxByName 0x35C090` finds a procedure index by `strcmp` over section 0 (used by the field/event code before `scrCreateTask*`).

## 4. Data flow of a BF from disc to execution (obs unless noted)

1. The BF bytes arrive through `H_Cdvd_Request`/`H_Cdvd_ReadSync` (topic 11); `scrCreateTaskFromScriptMemory` copies them (`H_Malloc` + `memset` + `memcpy`) so the loader's buffer can go; `scrCreateTaskFromHeader` runs them in place.
2. `scrStartScript2` validates `FLW0`, resolves the five sections by type to absolute pointers (`base + offset`), passes them plus the start procedure index.
3. `scrStartScript` allocates `ScrTask`, the local variable arrays, and — if section 3 has bytes — a message handle (`itfMesMngInitialize(section3)`, §5.1); it links the task into the list and logs `"procedure start <%s>"`.
4. `dds3InitProcess` registers `scrScriptProcess` as the per-frame body; each frame runs instructions until a COMM returns 0 (yield) or END empties the call stack.

## 5. BMD message system

### 5.1 Loading (`itfMesManager.c`)

* `itfMesMngInitialize 0x3A2D80` (`sub_*`-free, verified): `assert itfMesMngCheckBmdMagic(bmd)` (line 1693), takes a free manager slot from the list at `sItfMesManagerMsgHead` (`sub_3B49A0 0x3B49A0` = list pop), creates the handle with `sub_3A2EF0` and stores it in one of the slot's 4 handle entries (`+20 + 8*i`), returns the slot's id (`*(slot+8)`), `printf("itfMesMngInitialize() type=%d\n")`.
* `sub_3A2EF0 0x3A2EF0` (proposed `itfMesMngCreateHandle`): allocates the **488-byte message handle** (`H_Malloc`, or `RwHeapMalloc(488, 0x40000)` when `datGetFlag(5156)`), zeroes its state and binds the BMD with `sub_3A42C0 0x3A42C0` (proposed `itfMesMngBindBmd`): `handle+4 = bmd`; `sub_3A5030 0x3A5030` relocates the BMD **once** (flag byte `bmd+0x1C`, the low byte of the header's `+0x1C` word, set to 1 afterwards) by calling **`sub_35AC90 0x35AC90`**`(bmd+0x20, bmd+0x20, bmd + *(u32*)(bmd+0x10), *(s32*)(bmd+0x14))` — the relocation decoder documented in `FORMATS.md` §3, now read from the instructions (**replaced**, §7); `sub_3A5100 0x3A5100` returns `bmd + 0x20 + 8 * message_count` (the speaker block) and for `MSG1` files the handle keeps its third word (`handle+8`).
* Message lookup: `sub_3A50E0 0x3A50E0` (proposed `itfMesMngGetMessageEntry`) = `bmd + 0x20 + 8*index` → `{ u32 type, u32 ptr }`; `itfMesMngRequestMessage 0x3A30C0` asserts `type == 0` (dialogue, line 1873) and `sub_3A37C0` asserts `type == 1` (selection, line 2238). A dialogue record's `+24` is the u16 line count and `+26` the u16 speaker index (`0xFFFF` = none; bit 15 selects a named speaker via `itfMesMngGetMessageArg`) — matching `FORMATS.md` §3.

### 5.2 Request path from a script (obs)

`COMM 0` (`sub_3A2150`, proposed `scrCommand_MSG`): `h = scrGetMessageID()`; if `h >= 0` and the handle's "busy" byte (`handle+52`) is 0 → `sub_3A4360(h, 4)` then `itfMesMngRequestMessage(h, scrGetIntPara(0), 0)`; returns 0 (keep the pc, re-enter next frame) until the byte goes negative (window closed), then clears it and returns 1. `itfMesMngRequestMessage` resolves the entry, stores the record pointer (`handle+44`), the speaker, lays the text out (`sub_3A5980`), creates the name panel (`sub_3B2940`, `itfPnlRelease 0x3A8D60`) and sets the state bits (`handle+0` low 3 bits = 2 "open request" or 3; `|= 0x1000000`). Per-frame work is the manager task pair registered by `itfMesMngInitializeManager 0x3A4CE0` (`"CalcMsgMng"`, `"DrawMsgMng"`): `itfMesManagerUpdateCalcTask 0x3A8440` / `itfMesManagerUpdateDrawTask 0x3A84C0`, drawing through `itfMesManagerDrawTypeTbl 0x6A1C90` (15 × u32 → `itfMesManagerDrawType0..14`, obs; selected by `itfMesManagerDrawTypeDispatch 0x3A90C0`).

### 5.3 Text tokens (obs: `frFontProcessTagEx 0x3B2A30`, `sub_3B2430 0x3B2430` in `frFont.c`)

Both walkers read bytes from `ctx+16` at index `ctx+24`:
* `0x00` ends the line.
* `(b & 0xF0) == 0xF0`: **control code**; the second byte `f` is the function; the pair `(b << 8) | f` is passed to **`sFrTagTable[f]` at `0x6A2370`** (76 × u32, `0x6A2370–0x6A24A0`, obs; `sub_3B2430` asserts `2 <= f < 0x4D`, lines 3577/3578) with the walker context; then the index advances by `2 * ((b & 0x0F) - 1)` more bytes — i.e. the whole code is **`2 × low nibble` bytes long**, which is `bmd_tokenize`'s rule. A handler returning non-zero ends the line; `frFontProcessTagEx` also stops at `F1 31`, `F1 10`, `F1 04` (`0xF131/0xF110/0xF104`, obs).
* `0x0A`: newline (advances the y cursor by `8 * line_height` when the wrap flag is set).
* `b >= 0x80`: **two-byte glyph** `(b << 8) | next`; codes `>= 0xC080` are remapped by `-0x4000` into font slot 8; `0x20` draws as the wide space glyph `0x83F7`; other ASCII goes through as a one-byte glyph. Glyph records come from `sub_3B0970` and are rasterised by `frFontRasterDrawGlyph 0x3B38F0`.
* Tag handlers seen: `0x6A2378 [2] sub_3AC5A0`, `[3] sub_3AC600`, `[4] sub_3AC6C0` (sets bit 0 of the walker flags), `[6] sub_3AC6F0`, `[8] sub_3AC750` (`ctx+15 = byte - 1`: font/colour select from the next byte), `[0x11] sub_3ACBC0` (`sound/voice_e%03d_%03d/…adx`: the voice tag), `[0x3F] sub_3AEE00` (the `F1 3F` that starts most lines in `FORMATS.md` §3).

The `FORMATS.md` §3 "Unknown" items are thus partly closed: the control-code length rule and the function-byte dispatch are confirmed; what each of the 74 handlers does remains to be read (queue).

## 6. What Phase 5/6 must preserve

* The VM is pure guest code over guest memory: no hardware access. A native VM later (Phase 6) must keep the **re-entry semantics** of COMM (a command returning 0 is re-run with the same arguments and a growing `cmd_timer`), the stack-tag conversions (`(int)float`, `(float)int`) and the sign-extended 16-bit operands (negative operands index backwards; nothing in the 40 top-level BFs uses them — `test_bf.cpp` — but the code allows it).
* The relocation is applied **in place, once** (`bmd+0x1C` flag): a BMD that is reloaded from a fresh disc buffer is relocated again; one that is copied *after* relocation is not. Any native BMD loader must honour the flag the same way or the pointers double-relocate.
* Message windows run on the dds3 task scheduler (`itfMesManagerUpdateCalcTask`), not inside the script step; the script only polls the handle's busy byte.

## 7. Replaced in this wave (`game/src/script/script_vm.cpp`, `game/replaced.txt`)

| function | role | why it is safe |
|---|---|---|
| `CodeFunc_Proc 0x35CF00` | PROC: `pc += 1` | 6 instructions, no calls |
| `CodeFunc_Jmp 0x35D1D0` | JUMP: `pc = proc_labels[s16 operand].insn` | 13 instructions, no calls |
| `CodeFunc_Goto 0x35D310` | GOTO: `pc = jump_labels[s16 operand].insn` | 13 instructions, no calls |
| `ApplyRelocTable 0x35AC90` | BMD pointer relocation (§5.1) | 60 instructions, two loops, no calls; the only caller is `itfMesMngRelocateBmdOnce 0x3A5030` |

Pair tests: `tests/game/test_script_vm.cpp` (random task records / relocation streams of every encoding, plus the `DATTUTORIAL.BMD` table `07 16` from `FORMATS.md`). Whole-program gates: dorm replay and M1 (`docs/INTEGRATION_LOG.md`).

## 8. Open questions

* `CodeFunc_Run` (opcode 12) aborts: no BF in the game may use RUN — not censused here (`test_bf.cpp` could check all 40 + the packed ones).
* The 74 `sFrTagTable` handlers and the 15 draw types are unread; the glyph table for indices `>= 0x80` (`FORMATS.md` §3) still needs `DATA/FONT/*.FNT`.
* The social-link command table at `0x7B9680` (`{ fn, argc }` pairs starting with `K_Cmd_REQ_CLND_SKIP`, `sub_35F170`, `scrComuCommand_STARTED_COMU`…) has no code xref recorded by IDA (gp-relative); its reader was not located.
* `sub_35F160`/`sub_35C1A0` (`+0xF0` user word): the semantics of the value (a pointer to the command context, inf) were not traced into the 206 callers.
* The 51-case `jr` switch in `sub_361350` (`mt_evtMain.c`, table `0x7BA2F0`) is the event-system command dispatcher next to the script band; outside this topic.
