# 28 — Automatic type and struct recovery (p3fes_types)

_Phase 5 tooling, 2026-10-21. Our own analysis of SLUS_216.21: offsets, widths, accessor addresses. Names only where the
project's headers already establish them (ADR-0009)._

Slice agents used to work out struct offsets one function at a time. `p3fes_types` proposes struct layouts for the whole
program in about 3 s. Slice agents then confirm the layouts and name the fields. The same output feeds the multiplayer
readiness criterion: documented, binary-proven layouts for units, field objects, Tartarus floors, tasks and battle state.

| What | Where |
|---|---|
| Analysis (C++, reuses the recompiler's decoder and CFG) | `recomp/src/types.h`, `types_analyze.cpp`, `types_solve.cpp`, `types_main.cpp` → target `p3fes_types` |
| Seeds: header-known records and where their pointers arrive | `tools/ours/types/seeds.json` (203 records, 1,635 fields, 1,445 anchors, each with header file:line) |
| Post-processing: validation, types.json, headers, report | `tools/ours/types/types_build.py` (+ `make_anchors.py`) |
| Machine-readable output | `tools/ours/types/types.json` (committed) |
| Query | `tools/ours/types/types_query.py` |
| Proposed headers (generated; not included by game code yet) | `game/include/p3fes/game/types/{unit,battle_state,task,field_object,tartarus_floor,effect_node,script_event,model,calendar,common}.h` |

## Running it

```
cmake -S recomp -B build\types-recomp -G Ninja -DCMAKE_BUILD_TYPE=Release     # or any configured tree
cmake --build build\types-recomp --target p3fes_types
python -I tools\ours\types\types_build.py --exe build\types-recomp\bin\p3fes_types.exe `
    --headers game\include\p3fes\game\types --report build\types_report.md        # writes tools\ours\types\types.json
python -I tools\ours\types\types_query.py --addr datCalcGetHp
```

Defaults are the main tree's ELF (`extracted\disc\SLUS_216.21`) and snapshots (`extracted\_ours`). The raw solver output
goes to `build\types.raw.json` (`--raw` to move it).

## Method

**Phase 1: per-function dataflow** (`types_analyze.cpp`). The tool runs over every function of `symbols/functions.json`,
using `emit_analyze`'s chunks, delay slots, reachability, jump tables and mid-body entries. Each GPR holds one abstract
value:

* `Ptr(tv, off, stride)`: a pointer into a *type variable* plus a constant offset. A stride means indexed: `addu` with a
  scaled index, or a pointer that steps through a loop.
* `Const` with a flag for "complete address". This covers lui+addiu/ori and gp-relative values (`$gp = 0x7D2CF0`).
* `GIdx`: a global plus an index.
* `Stack(off)`: spill slots are tracked, including the 128-bit `sq`/`lq` saves of callee-saved registers.
* `Scaled(var, k)`: an unknown integer times a known factor. This follows Metrowerks' `sll`/`addu` multiply chains and
  `mult` by a constant, so `x*12` ends up as stride 12.
* Unknown.

At entry, `$a0..$t3` are `Ptr(Param(f, i))`. After a `jal`, `$v0` is `Ptr(CallResult(site))`, and `$at`, `$v1`,
`$a*`, `$t*` and LO are clobbered. The rules for loads, stores and transfers:

* Every load or store through a `Ptr` records an access: offset, width, signed/unsigned/float/vector/64/128, load or
  store, function and pc.
* A `lw` result is a new type variable, "the pointee of that field": a *deref* constraint.
* A load or store through an absolute address is recorded per address.
* A pointer stored into a field gives a *store* constraint.
* Pointers in `$a0..$t3` at a call give *arg* constraints. A pointer to the middle of an object (`Ptr` with an offset)
  gives an *embed* relation.
* `$v0` at `jr $ra` gives a *return* constraint.
* A `jalr` through a loaded value gives an *indirect call*.

At a merge point, two different pointers in one register become a *phi* variable. Its links count only when the merged
value is used afterwards (an access, an argument, a store, a return), so a dead register cannot unify two unrelated
types. The dataflow is a worklist fixpoint without recording, followed by one recording pass over the converged
in-states.

**Phase 2: unification** (`types_solve.cpp`). This is a union-find over the type variables, field-sensitive in the
Steensgaard style: when two classes unify, so do the pointees of their common fields. The steps run in order of
confidence:

1. Joins (phis).
2. Field derefs.
3. Pointer stores.
4. Returns inside a function.
5. Call arguments.
6. Call results.
7. Calls through function-pointer fields.

These rules keep unrelated types apart:

* **Layout veto.** Two classes do not merge when their accesses conflict. A conflict is the same offset accessed with
  disjoint 1/2/4-byte widths, a float against a sub-word integer, or an access that starts inside another field's
  bytes. A few conflicts are tolerated among many agreeing offsets (at most one per ten).
* **Anchors (seeds).** `seeds.json` pins each header-known record onto the pointers that reach it: a function argument,
  a return value, a global pointer slot, or a global object. Two different records never merge. A record with a
  documented size never gains an access at or past its end, or before its start. This rule alone took `KwlnTask` from
  191 merged fields to its own 27.
* **Evidence and polymorphism.**
  * A callee parameter links its callers only when it has field accesses of its own. So `memcpy`, `printf` and free
    lists, whose parameters are only walked byte by byte, link nothing.
  * A callee side whose callers pass conflicting layouts is marked polymorphic and is not linked (75 such sides).
  * A function that returns a pointer field of its own parameter (a getter such as `kwlnTaskGetWorkData`) never links
    its callers' results.
  * An indirect call links only the "self" argument: the argument of the class the function pointer was loaded from,
    as in `task->update(task)`. That argument is linked to the parameters of the callbacks stored in that field.

**Post-processing** (`types_build.py`):

* Folds absolute-address accesses into the records that live at fixed addresses (`gGlobalWork`, the font styles, ...).
* Compares every anchored class with its header: a field is *found* when it is accessed at its documented offset with
  its documented width (any access inside an array or aggregate counts). It is a *conflict* when the width differs or
  an access starts inside a scalar.
* Checks the layouts against the six replay snapshots. Instances are reached from global pointer slots and global
  objects, following pointer fields up to six levels. A pointer field must hold 0 or a RAM/code address, a function
  pointer 0 or a code address, a float field a plausible float. Documented fields are checked by their documented
  type.
* Writes the compact `types.json`, the headers and the report below.

## How good is it

* **Coverage.** All 14,500 functions were analysed (none skipped). 12,886 classes have field accesses; 2,309 have 4 or
  more fields. `types.json` keeps 7,829 classes: the anchored ones, those with 2 or more fields, and parameter types
  with fields.
* **Against the headers.** Of 1,336 documented fields in 163 anchored records, **983 are found** at their offset and
  width, and **13 conflict**. 340 are not accessed through the anchors: they are reached from parents the solver did
  not link, or never accessed at all.
* **Against the snapshots.** 21,997 of 22,397 checks pass on the 13,477 accepted instances, which is 98.2 %. Fields of
  anchored records pass 11,914 of 12,285, and fields with 3 or more accessors pass 10,041 of 10,155. Before the
  acceptance filter, which drops instances where fewer than 80 % of fields look plausible (stale pointers, polymorphic
  fields), 30,824 of 40,995 checks pass. The filter is needed because a global that still points at freed memory
  counts its garbage against every field.
* **Instances found** (`KwlnTask` reached through the task lists): 55 in dorm, 64 to 71 in battle, 87 in the climb.
  Snapshot instances for the other records are in the table below.
* **Runtime.** `p3fes_types` takes 2.6 s in all: 0.7 s to load the ELF and symbols, 1.35 s for the dataflow over 2.3 M
  instruction visits, 0.6 s to solve and write. Post-processing takes 0.75 s, snapshots included.

**Limits.**

* Context-insensitive. Classes reached only through generic code stay unlinked, and some unanchored classes are merged
  views of several records. `EffectNode` (352 fields) and `MdlModel` (118 fields) are the largest. Each header lists
  the offsets beyond a documented size as "views merged from other records".
* Work areas reached only as `task + 0x3C` are not anchored yet: 28 records, with names in `seeds.json`
  `"anchors": []`. Anchoring them on their creators' `H_Malloc` results is the next step.
* No sizes for unanchored types beyond "highest offset accessed".
* Accesses through `$sp` into local structs are not attributed. A stack object is tracked only once its address is
  passed on.
* The confidence of a field is a heuristic (accessor count and snapshot checks), not a proof. The pair tests and the
  slice's own reading remain the proof.

## Three examples (from the generated headers)

**`KwlnTask`** (`types/task.h`): 16 of 16 documented fields found, 0 conflicts. 743 parameter slots carry it: every
`kwlnTask*` function and the update/destroy callbacks, linked through `task->update(task)`. For example, `+0x3C work` is
read by 499 functions (the `H_Cursor_*` family first), and `+0x40/+0x44/+0x48` are the list links of
`kwlnTaskAddToList 0x193BA0` and `kwlnTaskRemoveFromList 0x1939D0`. 55 to 87 live tasks per snapshot pass every
documented pointer check.

**`DatUnit`** (`types/unit.h`): 9 of 11 documented fields found, 0 conflicts. 99 parameter slots carry it. For example,
`+0x8 hp` (u16) is read by 16 functions including `datCalcGetHp 0x2FFD70`, and `+0xC status` (u32) by 19 including
`datUnitInit 0x2FF890`. The `+0x2` id is also indexed with stride 60, which matches the 60-byte record size: the unit
arrays.

**`FldUnit`** (`types/field_object.h`, the field actor): 11 of 17 documented fields found, 0 conflicts, plus 9
recovered offsets. Among them are three floats at `+0x30/+0x34/+0x38` (`sub_1C7CE0`, `sub_1C8120`; plausible floats in
all six snapshots) and four more task pointers at `+0x170/+0x174/+0x178/+0x180`, next to the documented
`kUnitTask364/380` (`sub_1D0110`; valid in all six snapshots).

## Header conflicts worth a look

These come from the generated report. Each is either a header to correct or a merge to explain. Each row names
functions that access the field with the other width.

| record | offset | header | recovered | accessors |
|---|---|---|---|---|
| gBtl | +0xA18 | u32 support request pending | width 2 | sub_2DAA20 0x2DAA20, sub_2DAD00 0x2DAD00 |
| gBtl | +0xA2C | u32 support requested line | width 2 | sub_2DAA20 0x2DAA20, sub_2DAD00 0x2DAD00 |
| gBtl | +0xA38 | u32 formation id | width 2 | sub_28AA20 0x28AA20, btlActionUpdateStateAttack 0x28EB50 |
| gBtl | +0xA92 | s16 support timer 2 | width 1 | btlSupportResetTimers 0x2DCBC0, btlSupportTickTimers 0x2DCC40 |
| btlAction | +0x70 | u32 command word +112 | width 2 | btlActionUpdateStateSkill 0x290BE0, sub_295C00 0x295C00 |
| EplModelObj | +0x54 | ptr draw layer | width 2 | sub_34C5A0 0x34C5A0, sub_34C5D0 0x34C5D0 |
| EplClumpParticleObj | +0xC | s32 kind word (3 = emit) | width 2 | sub_34DB30 0x34DB30, sub_34DC00 0x34DC00 |
| EffectInstance | +0x54 | u32 entry count | width 2 | sub_2B94F0 0x2B94F0, sub_2BA3A0 0x2BA3A0 |
| MdlModel | +0xD8 | u32 flags (bit 2) | width 2 | sub_19B2B0 0x19B2B0, sub_19C4B0 0x19C4B0 |
| EffectSlot | +0x0 | u32 flags | width 2 | sub_2BB580 0x2BB580, sub_2BBE00 0x2BBE00 |
| EffectSlot | +0x8 | u32 fade step | width 1 | sub_2BB580 0x2BB580, sub_2BBE00 0x2BBE00 |
| EplK3Particle | +0x14 | s32 colour phase | width 1 | sub_34D150 0x34D150 |
| NmListNode | +0x4 | u32 word +4 (nmListFindByWord4) | width 2 | sub_3D74F0 0x3D74F0 |

## Numbers

_Generated by `tools/ours/types/types_build.py --report` (2026-10-21)._

| | |
|---|---|
| functions analysed | 14500 of 14500 |
| instruction visits (dataflow) | 2323791 |
| type variables / accesses / absolute-address accesses | 326788 / 132931 / 31559 |
| constraints / unions / vetoes (anchor clashes) | 361509 / 117113 / 526 (159) |
| polymorphic callee sides (not linked) | 75 |
| classes with fields (raw) / in types.json | 12886 / 7829 |
| classes with >= 4 fields | 2309 |
| types.json | 4.2 MB |
| runtime | p3fes_types 2.62 s (phase 1 1.35 s); post-processing 0.74 s |

Header agreement (seeds.json: 203 records from the project's headers and topic docs, 163 with a recovered class): 1336 known fields, **983 found**, **13 conflicting**, 340 not accessed through the anchors, 1483 recovered-only offsets inside the documented sizes.

Snapshots: field checks (pointer fields hold 0 or a RAM / code address, float fields plausible floats) on accepted instances reached from global pointers: 21997 of 22397 pass (pointers 17665/17811, floats 4332/4586); fields of anchored records 11914/12285; fields with >= 3 accessor functions 10041/10155.

Before the acceptance filter (every instance reached): 30824 of 40995 checks pass.

| snapshot | instances accepted | rejected (< 80 % of fields plausible) | classes with instances |
|---|---|---|---|
| battle_ref_6150 | 2255 | 96 | 1144 |
| b_5800 | 2395 | 101 | 1157 |
| dorm_replay_4900 | 2145 | 84 | 1113 |
| climb_ref_17000 | 2266 | 100 | 1137 |
| fusion_ref_6300 | 2181 | 85 | 1121 |
| shop_ref_4100 | 2235 | 98 | 1135 |

Per record (multiplayer areas first):

| record | class | fields recovered | params | known | found | conflicts | new | snapshot instances |
|---|---|---|---|---|---|---|---|---|
| DatUnit | 439 | 11 | 99 | 11 | 9 | 0 | 2 | battle_ref_6150 2, b_5800 4, dorm_replay_4900 1, climb_ref_17000 3, fusion_ref_6300 1, shop_ref_4100 1 |
| btlUnit | 7 | 132 | 113 | 20 | 17 | 0 | 113 | battle_ref_6150 1, b_5800 7 |
| btlTarget | 1725 | 4 | 1 | 6 | 4 | 0 | 0 | - |
| Persona | 833 | 7 | 41 | 4 | 2 | 0 | 5 | - |
| PartyMemberRecord | 9803 | 0 | 0 | 4 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| gBtl | 2 | 215 | 0 | 72 | 59 | 4 | 148 | battle_ref_6150 1, b_5800 1 |
| btlAction | 27 | 54 | 147 | 41 | 35 | 1 | 17 | battle_ref_6150 1, b_5800 4 |
| BtlPacket | 111 | 24 | 2 | 19 | 18 | 0 | 6 | - |
| BtlSetupBlock | 10268 | 0 | 2 | 5 | 0 | 0 | 0 | - |
| DatScriptContext | 12404 | 6 | 0 | 6 | 6 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| BtlMainStateRecord | 1731 | 4 | 1 | 3 | 0 | 0 | 0 | - |
| KwlnTask | 89 | 27 | 743 | 16 | 16 | 0 | 5 | battle_ref_6150 64, b_5800 71, dorm_replay_4900 55, climb_ref_17000 87, fusion_ref_6300 61, shop_ref_4100 65 |
| FldUnit | 259 | 24 | 16 | 17 | 11 | 0 | 9 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| sField | 20 | 65 | 0 | 27 | 26 | 0 | 31 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| MtScene | 458 | 11 | 0 | 9 | 9 | 0 | 2 | - |
| SceneRes | 16 | 72 | 9 | 13 | 10 | 0 | 61 | - |
| TreasureBox | 10054 | 0 | 0 | 3 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| FldGridCell | 12706 | 0 | 0 | 10 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| FldBlockDesc | 40 | 40 | 3 | 6 | 5 | 0 | 0 | - |
| FldDngFloorEntry | 5453 | 1 | 0 | 8 | 1 | 0 | 0 | - |
| EncountRecord | 10073 | 0 | 0 | 5 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| EffectNode | 1 | 352 | 40 | 2 | 2 | 0 | 339 | - |
| EplModelObj | 374 | 12 | 4 | 13 | 8 | 1 | 1 | - |
| EplNodeModelObj | 379 | 12 | 3 | 14 | 10 | 0 | 0 | - |
| EplClumpParticleObj | 158 | 20 | 8 | 6 | 5 | 1 | 14 | - |
| EplTexParticleObj | 205 | 17 | 8 | 10 | 9 | 0 | 8 | - |
| EffectInstance | 125 | 23 | 3 | 9 | 8 | 1 | 14 | - |
| ScrTask | 161 | 20 | 1 | 24 | 20 | 0 | 0 | dorm_replay_4900 1, fusion_ref_6300 2, shop_ref_4100 1 |
| EventWork | 635 | 9 | 1 | 4 | 3 | 0 | 6 | - |
| BfHeader | 906 | 7 | 5 | 5 | 4 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 2, climb_ref_17000 1, fusion_ref_6300 2, shop_ref_4100 2 |
| BfLabel | 10658 | 0 | 2 | 3 | 0 | 0 | 0 | dorm_replay_4900 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RpAtomic | 200 | 17 | 16 | 17 | 14 | 0 | 1 | battle_ref_6150 4, b_5800 4, dorm_replay_4900 6, climb_ref_17000 11, fusion_ref_6300 9, shop_ref_4100 6 |
| RwFrame | 138 | 21 | 32 | 3 | 2 | 0 | 19 | battle_ref_6150 11, b_5800 11, dorm_replay_4900 6, climb_ref_17000 11, fusion_ref_6300 15, shop_ref_4100 6 |
| RpGeometry | 258 | 15 | 10 | 4 | 4 | 0 | 11 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RwMatrix | 280 | 14 | 176 | 5 | 5 | 0 | 1 | battle_ref_6150 16, b_5800 16, dorm_replay_4900 18, climb_ref_17000 18, fusion_ref_6300 18, shop_ref_4100 18 |
| MdlModel | 8 | 118 | 58 | 3 | 2 | 1 | 115 | battle_ref_6150 4, b_5800 7, dorm_replay_4900 1, climb_ref_17000 5, fusion_ref_6300 6, shop_ref_4100 2 |
| RwCamera | 39 | 41 | 2 | 11 | 8 | 0 | 24 | - |
| gGlobalWork | 9765 | 44 | 0 | 15 | 13 | 0 | 21 | dorm_replay_4900 1, climb_ref_17000 1, shop_ref_4100 1 |
| BattleResultWork | 1684 | 4 | 0 | 16 | 3 | 0 | 1 | battle_ref_6150 1 |
| BcmWork | 12 | 91 | 1 | 38 | 31 | 0 | 56 | - |
| BedHeader | 333 | 13 | 16 | 8 | 4 | 0 | 8 | battle_ref_6150 1, b_5800 1 |
| BfSectionDesc | 6980 | 1 | 2 | 4 | 1 | 0 | 0 | dorm_replay_4900 1, fusion_ref_6300 1, shop_ref_4100 1 |
| BmdDialogueRecord | 4182 | 2 | 1 | 3 | 2 | 0 | 0 | - |
| BmdHeader | 1341 | 5 | 7 | 9 | 5 | 0 | 0 | - |
| BmdMessageEntry | 4181 | 2 | 0 | 2 | 2 | 0 | 0 | - |
| BmdSpeakerBlock | 7276 | 1 | 0 | 4 | 1 | 0 | 0 | - |
| BpSpriteRecord | 123 | 23 | 6 | 8 | 8 | 0 | 0 | - |
| BpSpriteSet | 1343 | 5 | 2 | 2 | 2 | 0 | 3 | - |
| BtlAiCondRow | 12712 | 1 | 0 | 3 | 1 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| BtlAiTargetRow | 12713 | 1 | 0 | 2 | 1 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| BtlCommandList | 12406 | 2 | 0 | 12 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| BtlTableLoadRecord | 3703 | 2 | 1 | 6 | 2 | 0 | 0 | - |
| DatUnitEnemyGenus | 1365 | 5 | 2 | 5 | 4 | 0 | 1 | battle_ref_6150 1, b_5800 1, climb_ref_17000 1, fusion_ref_6300 1 |
| DatUnitPartyGenus | 10074 | 0 | 0 | 3 | 0 | 0 | 0 | - |
| EffectSlot | 598 | 9 | 1 | 8 | 6 | 2 | 1 | b_5800 7 |
| EncountGroupEntry | 10093 | 0 | 0 | 3 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| EnemyRecord | 10221 | 0 | 0 | 11 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| EplK3Particle | 1121 | 6 | 1 | 4 | 3 | 1 | 0 | - |
| EplK4Particle | 899 | 7 | 1 | 7 | 7 | 0 | 0 | - |
| EplParticleSystem | 882 | 7 | 4 | 4 | 4 | 0 | 3 | - |
| EventCfg | 469 | 11 | 0 | 4 | 4 | 0 | 2 | - |
| FieldParams | 244 | 16 | 0 | 12 | 8 | 0 | 8 | - |
| FieldTableEntry | 12714 | 9 | 0 | 2 | 2 | 0 | 7 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| FmGslEntry | 1959 | 4 | 1 | 3 | 3 | 0 | 1 | battle_ref_6150 18, b_5800 24, dorm_replay_4900 29, climb_ref_17000 13, fusion_ref_6300 13, shop_ref_4100 18 |
| FmGslGlyphRegions | 2854 | 3 | 2 | 3 | 3 | 0 | 0 | - |
| FontRasterSlot | 626 | 9 | 1 | 6 | 6 | 0 | 3 | battle_ref_6150 51, b_5800 44, dorm_replay_4900 35, climb_ref_17000 36, fusion_ref_6300 28, shop_ref_4100 51 |
| FontRasterSlotManager | 1146 | 6 | 0 | 4 | 4 | 0 | 2 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| FrFontGlyphNode | 242 | 16 | 5 | 15 | 15 | 0 | 1 | battle_ref_6150 1, b_5800 22 |
| FrFontHuffmanBlock | 2853 | 3 | 2 | 8 | 3 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| FrFontLineNode | 155 | 20 | 40 | 13 | 13 | 0 | 7 | battle_ref_6150 1, b_5800 5 |
| FrFontStyle | 10888 | 8 | 0 | 7 | 7 | 0 | 1 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| FrFontTagScan | 2851 | 3 | 1 | 3 | 3 | 0 | 0 | - |
| FrFontTagWindow | 10851 | 0 | 1 | 4 | 0 | 0 | 0 | - |
| GmRootWork | 850 | 7 | 0 | 7 | 7 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| GrowthRow | 12405 | 0 | 0 | 2 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| HCdvdCacheEntry | 9627 | 2 | 0 | 6 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| HCdvdFile | 1560 | 4 | 1 | 12 | 4 | 0 | 0 | - |
| HCdvdPakEntry | 107 | 24 | 267 | 2 | 1 | 0 | 0 | battle_ref_6150 207, b_5800 207, dorm_replay_4900 207, climb_ref_17000 207, fusion_ref_6300 207, shop_ref_4100 207 |
| HCdvdRequest | 311 | 13 | 0 | 18 | 13 | 0 | 0 | battle_ref_6150 7, b_5800 7, dorm_replay_4900 7, climb_ref_17000 7, fusion_ref_6300 7, shop_ref_4100 7 |
| HSndcomSlot | 12718 | 18 | 0 | 17 | 17 | 0 | 1 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| H_CampRootDrawWork | 3 | 179 | 15 | 10 | 10 | 0 | 169 | - |
| Im2DDescriptor | 4732 | 2 | 1 | 4 | 2 | 0 | 0 | - |
| Im2DIndexedMesh | 851 | 7 | 2 | 4 | 4 | 0 | 3 | - |
| ItfMesHandle | 28 | 54 | 22 | 20 | 20 | 0 | 34 | battle_ref_6150 6, b_5800 6, dorm_replay_4900 6, climb_ref_17000 6, fusion_ref_6300 6, shop_ref_4100 6 |
| ItfMesManagerSlot | 2835 | 3 | 1 | 6 | 3 | 0 | 0 | - |
| ItfMesPanelRecord | 459 | 11 | 2 | 3 | 3 | 0 | 8 | - |
| ItfMesSelectRecord | 387 | 12 | 1 | 12 | 12 | 0 | 0 | - |
| ItfMesSlotLinks | 4218 | 2 | 2 | 3 | 2 | 0 | 0 | battle_ref_6150 21, b_5800 21, dorm_replay_4900 22, climb_ref_17000 20, fusion_ref_6300 22, shop_ref_4100 22 |
| ItfMesSlotList | 1945 | 4 | 3 | 4 | 4 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| ItfMesSpeakerRecord | 1944 | 4 | 1 | 4 | 4 | 0 | 0 | - |
| ItfMesTextRecord | 340 | 13 | 1 | 13 | 13 | 0 | 0 | - |
| ItfMesWindowRecord | 923 | 7 | 1 | 7 | 7 | 0 | 0 | - |
| ItfPnl | 166 | 20 | 21 | 12 | 12 | 0 | 5 | - |
| KPatchEntry | 1510 | 6 | 0 | 2 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| LevelGapRow | 12708 | 0 | 0 | 2 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| LfModuleLoadArg | 1509 | 6 | 0 | 4 | 4 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| MsgWinRecord | 1163 | 6 | 2 | 6 | 6 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| NmCmdList | 1439 | 5 | 61 | 30 | 5 | 0 | 0 | - |
| NmCmdListRow | 742 | 8 | 11 | 10 | 4 | 0 | 4 | - |
| NmListHeader | 1966 | 4 | 2 | 5 | 4 | 0 | 0 | - |
| NmListNode | 1162 | 6 | 90 | 6 | 5 | 1 | 0 | shop_ref_4100 5 |
| NmListObject | 743 | 8 | 57 | 10 | 8 | 0 | 0 | battle_ref_6150 3, b_5800 3, dorm_replay_4900 3, climb_ref_17000 4, fusion_ref_6300 4, shop_ref_4100 5 |
| NpcListNode | 585 | 9 | 1 | 2 | 2 | 0 | 7 | - |
| ObjListNode | 1673 | 4 | 1 | 2 | 2 | 0 | 2 | - |
| OpMenuWork | 34 | 45 | 1 | 4 | 4 | 0 | 41 | - |
| OpResWork | 144 | 21 | 1 | 5 | 5 | 0 | 2 | - |
| OpRootWork | 371 | 12 | 0 | 11 | 11 | 0 | 1 | - |
| OpTitleWork | 2528 | 3 | 1 | 3 | 3 | 0 | 0 | - |
| OpWaitWork | 231 | 16 | 1 | 3 | 3 | 0 | 13 | - |
| PTankData | 127 | 23 | 6 | 29 | 13 | 0 | 7 | - |
| PTankLock | 190 | 18 | 1 | 14 | 14 | 0 | 0 | - |
| PadRpcBuf | 1261 | 7 | 0 | 6 | 6 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| PcModelSlot | 10067 | 3 | 0 | 3 | 3 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| PdsRegistry | 4525 | 2 | 1 | 2 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| PdsRegistryEntry | 8069 | 1 | 0 | 2 | 1 | 0 | 0 | - |
| RofsDirLstEnt | 802 | 8 | 1 | 6 | 6 | 0 | 0 | - |
| RofsDirLstHdr | 3224 | 3 | 10 | 5 | 3 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RofsHandle | 222 | 17 | 20 | 17 | 17 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RofsVolume | 1532 | 5 | 2 | 9 | 5 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RofsWork | 170 | 20 | 0 | 4 | 4 | 0 | 16 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RpMaterial | 4637 | 2 | 0 | 4 | 2 | 0 | 0 | - |
| RpMeshHeader | 774 | 8 | 1 | 3 | 3 | 0 | 5 | - |
| RpPDSClusterRef | 12851 | 0 | 0 | 2 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RpPDSMatPipeDef | 347 | 13 | 1 | 14 | 13 | 0 | 0 | - |
| RpSkin | 4529 | 2 | 2 | 3 | 1 | 0 | 1 | - |
| RpWorld | 153 | 20 | 37 | 6 | 3 | 0 | 17 | battle_ref_6150 3, b_5800 2, dorm_replay_4900 3, climb_ref_17000 6, fusion_ref_6300 7, shop_ref_4100 3 |
| RpWorldSector | 4522 | 2 | 12 | 3 | 1 | 0 | 1 | - |
| RwDMAQueueEntry | 4725 | 2 | 0 | 2 | 2 | 0 | 0 | battle_ref_6150 3, b_5800 3, dorm_replay_4900 3, climb_ref_17000 3, fusion_ref_6300 3, shop_ref_4100 3 |
| RwGlobals | 9897 | 56 | 0 | 9 | 9 | 0 | 27 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RwIm2DVertex | 60 | 32 | 5 | 12 | 8 | 0 | 0 | - |
| RwRaster | 274 | 15 | 36 | 3 | 3 | 0 | 12 | battle_ref_6150 26, b_5800 22, dorm_replay_4900 21, climb_ref_17000 20, fusion_ref_6300 16, shop_ref_4100 26 |
| RwSkyFlipData | 11810 | 80 | 1 | 7 | 6 | 0 | 0 | - |
| RwSphere | 1639 | 4 | 1 | 2 | 2 | 0 | 0 | - |
| RwTexture | 2063 | 4 | 2 | 3 | 2 | 0 | 2 | - |
| RwVideoMode | 3105 | 6 | 0 | 6 | 6 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RwVu1CodeDesc | 12833 | 2 | 0 | 2 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RwVu1CodePacket | 12719 | 0 | 0 | 6 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| RxPS2AllPipeData | 397 | 12 | 16 | 21 | 12 | 0 | 0 | - |
| SceSemaParam | 11725 | 2 | 1 | 6 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SceSifDmaData | 2302 | 4 | 1 | 4 | 4 | 0 | 0 | battle_ref_6150 2, b_5800 2, dorm_replay_4900 2, climb_ref_17000 2, fusion_ref_6300 2, shop_ref_4100 2 |
| SceSifRpcClientData | 654 | 9 | 4 | 10 | 9 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SceThreadParam | 1041 | 6 | 1 | 12 | 6 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| ScrCommandEntry | 12711 | 2 | 0 | 2 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| ScrGlobals | 10668 | 0 | 0 | 2 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| ScrSeqRecord | 1864 | 4 | 1 | 4 | 4 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SdrRemoteArgBlock | 1262 | 7 | 0 | 2 | 2 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SequenceEntry | 12709 | 3 | 0 | 3 | 3 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SkCmdBlock | 12014 | 8 | 0 | 3 | 3 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SkillRecord | 9808 | 0 | 0 | 18 | 0 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SkinGlobals | 12701 | 8 | 0 | 6 | 6 | 0 | 2 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| SprFile | 1303 | 5 | 11 | 5 | 2 | 0 | 3 | battle_ref_6150 3, b_5800 3, dorm_replay_4900 3, climb_ref_17000 3, fusion_ref_6300 3, shop_ref_4100 3 |
| SprHandle | 173 | 19 | 4 | 10 | 10 | 0 | 7 | climb_ref_17000 4 |
| TexCache | 12702 | 15 | 0 | 13 | 13 | 0 | 2 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| TexCacheSlot | 3126 | 3 | 0 | 3 | 3 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| ThinkEntry | 10016 | 0 | 1 | 3 | 0 | 0 | 0 | - |
| Vec4TableEntry | 11181 | 3 | 0 | 3 | 3 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
| btlActionCommandRec | 857 | 7 | 5 | 2 | 2 | 0 | 5 | - |
| dvCiHandle | 486 | 11 | 0 | 4 | 3 | 0 | 8 | - |
| sceGsDBuffDc | 11833 | 36 | 1 | 9 | 7 | 0 | 0 | - |
| sceGsDispEnv | 1500 | 10 | 1 | 5 | 5 | 0 | 0 | - |
| sceGsDrawEnv1 | 246 | 16 | 1 | 16 | 16 | 0 | 0 | battle_ref_6150 2, b_5800 2, dorm_replay_4900 2, climb_ref_17000 2, fusion_ref_6300 2, shop_ref_4100 2 |
| sceGsDrawEnv2 | 247 | 16 | 1 | 10 | 10 | 0 | 0 | - |
| sceGsGParam | 1256 | 6 | 0 | 6 | 6 | 0 | 0 | battle_ref_6150 1, b_5800 1, dorm_replay_4900 1, climb_ref_17000 1, fusion_ref_6300 1, shop_ref_4100 1 |
