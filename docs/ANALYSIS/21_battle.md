# 21 — Battle: the battle task tree, units, the `.TBL` data, damage/affinity formulas, the AI entry points

_Phase 5 analysis, fifth and last area of GOAL.md's order (file system → BF script VM → BMD messages → menu/UI → **battle**). Database: `ida/work_battle.i64` (a copy of the master taken once at the start of the session, opened headless with idalib; request/dump logs `ida/logs/battle_q1..q6.{req,txt}`, gp-relative reference scan `battle_q4.txt`). Every address is an EE virtual address. Tags: **obs** = read from the instructions / table bytes / file bytes, **der** = derived arithmetically from an obs, **inf** = inferred. The copy carries the community hint names as `HINT[tge-pr4]`/`HINT[snaku]` comments; `symbols/p3fes.sym` exports this whole band as `sub_*` except `datScriptGetValue 0x30FDF0` (ADR-0009), so names below are `name (sub_xxx)` where the hint name was verified from the instructions and is proposed in `symbols/deltas/battle.sym`, or `proposed` where the name is ours. Replacements: `game/src/battle/`, pair tests `tests/game/test_battle.cpp` (section 8). Table files were read from `extracted/BTL/BATTLE/*.TBL` with a 20-line Python section walker; no game bytes are copied here._

## 0. Headline

* **Entry.** A battle is started by the BF command **`btlScrCmd_CALL_BATTLE 0x27D5E0`** (`sub_*`-free hint, verified): it builds a 52-byte setup block — the hero's unit (`datUnitCreatePc(1)`), the party (`datUnitCreatePc(datGetPartyId(i))`, i < 4), the enemy genus `datUnitCreateEc(encounter)` and the field/room ids from the ENCOUNT record (`+18`/`+20`, default 221 / 1) — and hands it to **`adminiChangeSeq(6, block, 52, 0)`** (sequence 6 = battle). The sequence runs **`btlStart 0x27D1D0(block)`**: `btlCreate 0x27CED0` allocates the battle context **`gBtl` = `*(u32*)0x7CE3EC`** (1,821 gp-relative references, the hub of the whole band), creates the root `kwlnTask` **"battle"** (`0x7CC508`, prio 10, `btlUpdateTask 0x27CC30` / `btlDestroyTask 0x27CDF0`) with the children **"battle_draw_3d"** (prio 0x821, `btlUpdateDraw3DTask`), **"battle_draw_3d_front"** (0x1049), **"battle_draw_2d"** (0x106F) and the panel tasks (`bpRootCreateTasks 0x1FD6xx`), copies the block to `gBtl+0xBA8`, and enters the **btlMain state machine** at `INIT` (2) — or `TEST`/`MC` (18/19, flag `0x141B`) without a block (§1). The field side (`k_battle.c`) wraps it in **`K_Battle_CreateBattleTask 0x1D8B00`** ("battle(kosaka)", update `K_FldCamera_UpdateBattleKosakaTask 0x1D7D40`), the dungeon camera/encounter task.
* **State machines.** `btlMainSetState 0x29DE20` / `btlMainUpdateState 0x29DE80` drive a **20-row `{init, update, name}` table at `0x693760`** (`NULL NON INIT SCENE_SET UNIT_CREATE UNIT_LOAD START ACTION REVIVAL_MES REVIVAL WIN "ENEMY DEAD" CONDITION LOSE FADE_OUT END RESULT EXIT TEST MC`, §1.2); every actor's turn is a 1,200-byte **btlAction** object (`btlActionCreate 0x299E90`, list head `gBtl+0x14C`) run by `btlActionSetState 0x299D60` / `btlActionUpdateAll 0x299FB0` over **`sBtlActionTbl 0x693410`** (36 states `Non StandBy Start StartHome ChangeFormation Command Target Analyze AI Auto Support Bad Ready MoveTarget MoveHome Attack Skill Reinforce Summon Assist Event Error Endure Wait EscapeMes Escape Persona BadDamage RoundUpMes RoundUp Packet End EndHome Dead Exit Test`, §1.3). Turn order is the 12-slot list `gBtl+0x254` bubble-sorted by Agility (`sub_29A570`, `datCalcGetStat(unit, 3)` descending).
* **Units.** A combatant is a **60-byte `DatUnit`** (`datUnitInit 0x2FF890`): `u16 flags` (bit 2 = enemy), `u16 id`, `u16 base_id`, `u8 level`, `u16 hp` (+8), `u16 sp` (+0xA), `u32 status` (+0xC: 20 ailment bits + 12 high bits, bit 19 = dead), `u32 effect_flags` (+0x14), 21 buff/debuff slots as signed nibbles at +0x1C and turn counters at +0x29 (§2). Party units live inside `gGlobalWork` (hero at **`0x836224`**, members 2..10 at **`0x834010 + 868·(pc−2) + 4`**, `datGetUnit 0x16CD60`); an enemy genus is `RwHeapMalloc(372)` = header + **6 units** (`datUnitCreateEc 0x2FF3E0`). `datScriptGetValue 0x30FDF0` reads the attacker/target pair `0x957190`/`0x957194` set by `sub_30FC40` (§4).
* **Tables.** `sub_27DE40 0x27DE40` loads the 8 records of **`off_692D40`** (168 bytes each: `{name, name_F, {u32* dst, u32 size} × ≤20}`) through `sub_27DCD0`; a `.TBL` file is a sequence of **`{u32 size, bytes}` sections, each starting at the next multiple of 16**, copied one by one into the arena `dword_875D00` (§3). Verified contents: **SKILL.TBL** = `{s8 element, u8}[624]` + **`SkillRecord[464]` (44 B)** + 192 B; **UNIT.TBL** = **`EnemyRecord[336]` (62 B)** + **enemy affinities `u16[16]` per enemy** + 8 KB; **ENCOUNT.TBL** = **1,024 × 28-byte encounters** (`u16 units[5]` at +8) + four Tartarus floor tables read by `k_encount.c`; **MSG.TBL** = arcana names (21 B × 32), **skill names (19 B × 624)**, **enemy names (19 B × 336)**, persona names (17 B × 256), a text block; **AICALC.TBL** = 15 small constant tables (the level-difference and luck multipliers of `datScriptGetValue`), a 55 KB boss table and **two `FLW0` scripts (89 KB and 378 KB) — the AI is BF code** found by procedure name (`AI_EVENT_%03X_BTLSTART/ACTSTART/ACTEND` in `sub_2F6E00`, `AI_PC_%03X_%03X` in `sub_2C6F50`); PERSONA/EFFECT/MODEL sizes and readers are listed, their records not read.
* **Formulas (the Phase 5 pure code).** The damage pipeline is `datCalc.c`: **`sub_309490`** (hit/affinity check → result code 1 hit, 4 miss, 256 null, 512 repel/evade, 1024 drain; accuracy `clamp(f(…) − evasion, 50, 99) > rand(100)`), **`sub_303130`** (HP/SP change: 17 formula kinds from the skill record, boosts ×1.25/×1.5, criticals ×2, race/element multipliers, `clamp(dmg, skill_min, 31000) × (rand(11) + 95) / 100`), **`sub_306E80`** (the affinity word of a unit for an element: UNIT.TBL `rate = 5 × low byte`, flags bits 24..28 = null/repel/absorb/weak/resist, then passive skills 464..507 and the four element walls), and the AICALC "formula functions" `sDatScriptFuncTbl1..3 0x69AA90/AAE0/AB30` (17 each) such as `sub_30C520` = `10·√( 30·(power − 30) / (5·2·En_target) · St_attacker / 5 ) × affinity × leveldiff` (§5). `datCalcGetMaxHp 0x2FFDF0` = base (enemy +4 / PC growth table **`0x5DC1B4`**) × (1 + skill bonuses) + equipment, capped 999 for party members; `datCalcRand 0x2FFBC0(100)` re-rolls within ±3 of the previous roll.
* **Replaced this wave:** 16 datCalc leaves (HP/SP get/set, the six status-word functions, the two buff getters, four SKILL.TBL lookups incl. the status → element map), §8.

Confidence: **high** for §1–§3 and §6 (tables and dispatch read from the instructions and verified against the files), **medium** for §4–§5 (the float arithmetic of the formula functions was read from the decompiler's rendering of `mul.s`/`sqrt.s` chains; the integer parts and every table index were checked in the disassembly).

## 1. The battle task tree

### 1.1 Source files and address bands (obs: `K_Assert(file, line)` strings and task names)

| Atlus file | Band | Content |
|---|---|---|
| `k_encount.c` `0x683B28`, `k_battle.c` `0x683B68` | `0x1D7300–0x1D9860` | Tartarus encounter pick (`sub_1D78C0`), `K_Battle_CreateBattleTask 0x1D8B00`, the field battle camera task |
| `br_*`, `bp_*`, `bai_main.c` `0x68E980`, `sfl_*`, `gc_*` | `0x1EF7F0–0x27BBA0` | battle result, battle panel (command menu), auto-battle AI UI, shuffle time (topic 20 §1 lists them) |
| `btl*` root (`btlStart`, `btlCreate`, tables) | `0x27CC30–0x27E400` | battle context, root tasks, `.TBL` loader, `btlPacket*` |
| `btlUnit*` | `0x27E410–0x289650` | 3D unit objects (`btlUnitCreate 0x2875A0`, move/rotate/anim packets) |
| `btlAction.c` `0x693318` | `0x289650–0x29B0E0` | the per-turn action state machine, `btlOrder*` turn list |
| `btlMain*` | `0x29B0E0–0x29E400` | the battle state machine table `0x693760` |
| `btlCamera*`, `btlFormation.c` `0x696430`, `btlEffect*` | `0x29E400–0x2BF9B0` | camera, formation, effect packets, "battle_command_calc/draw" tasks |
| `btlAICommand.c` `0x696F88`, `btlAIScript.c` `0x697720` | `0x2BF9B0–0x2D1570` | AI command selection (BF COMM functions), `AI_PC_%03X_%03X` |
| `btlTarget*`, `btlEfficacy.c` `0x6978E0`, `btlSupport.c` `0x697B18` | `0x2D1570–0x2DD9B0` | targeting, results/EXP accounting (`sub_2D7560`), support (Fuuka) |
| `btlSound*`, `btlVoice*`, `btlBossCamera*`, `btlBossElizabeth.c` `0x69A4B0` | `0x2DD9B0–0x2FF260` | BGM/SE/voice, boss cameras and boss scripts |
| `datUnit.c` `0x69AA70` | `0x2FF260–0x2FFBC0` | unit records and genus allocation (§2) |
| `datCalc.c` `0x69AA80` | `0x2FFBC0–0x30C510` | every formula (§5) |
| `datScript.c` `0x69AB78` | `0x30C510–0x311310` | the 48 AICALC formula functions + `datScriptGetValue` (§4) |

### 1.2 `btlMain`: the battle state machine (obs)

`btlMainSetState 0x29DE20(s)`: `gBtl+0x2B4 = s; gBtl+0x2BC = 0; tbl[s].init(&gBtl->state)` with **`tbl = 0x693760`**, 12-byte rows `{init, update, name}` (obs, `dword_693760[3*s]`, `dword_693764[3*s]`; the three readers are `btlMainSetState`, `btlMainUpdateState`, `btlMainSetStateNon 0x29DF40`). `btlMainUpdateState 0x29DE80`: a pending state in `gBtl+0x2B8` is entered first; `r = tbl[s].update()`; a non-zero `r` becomes the pending state; `gBtl+0x2BC` (frames in state) `++`.

| # | name (`0x693760` row) | init / update | what was read |
|---|---|---|---|
| 0 | `NULL` | `0 / 0` | — |
| 1 | `NON` | `btlMainInitStateNon 0x29B0E0` / `…Update 0x29B0F0` | idle |
| 2 | `INIT` | `0x29B100` / `0x29B160` | `sub_2DCF80(3/4, 0)`, `sub_2DCED0(0)` (sound), **`sub_2F6E00`** (boss setup by encounter id 416..436/456 → 1,044-byte boss records in AICALC section 15 at `gBtl+0xB18`; looks up the three `AI_EVENT_%03X_*` procedures in the AICALC section-17 BF with `scrFindPrcdIdxByName`), `sub_17B180(1)` |
| 3 | `SCENE_SET` | `0x29B170` / `0x29B190` | scene load |
| 4 | `UNIT_CREATE` | `btlMainInitStateUnitCreate 0x29B280` / `0x29B760` | party models (`mdlSearch`, `MT_Scene_CreateResModelCharNoShadow`), enemy `btlUnit`s for the live genus slots, formation `sub_2B71E0`; the **advantage roll**: ENCOUNT flags bit 5 → scripted, else `sub_2D50C0` → `gBtl+0x1A` = 2 player advantage / 1 enemy advantage / 0 normal (`sub_29A750` builds the order; `datCalcRand(12)` skips on a flag), and on enemy advantage **33 % distress** (`datCalcRand(100) < 33 → datCalcSetBadStatus(unit, 2)`) for party units whose level + 2 ≤ `btlGetMeanLevel(1,0)` and whose affinity to element `sub_308120(-1, 2)` has no null/repel bits |
| 5 | `UNIT_LOAD` | `0x29BE40` / `0x29C110` | waits for the loads (`sub_2FF320` = genus-ready byte) |
| 6 | `START` | `0x29C250` / `btlMainUpdateStateStart 0x29C290` | waits for packets; `gBtl+0xC |= 0x800`; **→ 7** |
| 7 | `ACTION` | `0x29C330` / `btlMainUpdateStateAction 0x29C340` | the turn loop: returns 0 until `gBtl+0xC & 0x80` (end flag set by `sub_27D380`, §1.4); then builds the result block `gBtl+0xBDC` (survivors, `brRootCreateBattleResult2`) and goes **→ 10 WIN / 11 ENEMY DEAD** (outcome 1, by `gBtl+0x10 & 2`), **→ 8 REVIVAL_MES or 13 LOSE** (outcome 2, by `sub_27D560`: a party member with skill effect 4040 = revival), **→ 14 FADE_OUT** (outcome 3 escape) |
| 8/9 | `REVIVAL_MES` / `REVIVAL` | `0x29C5D0`/`0x29C680`, `0x29C700`/`0x29CCD0` | the "revive and continue" path |
| 10 | `WIN` | `0x29CE90` / `0x29D0D0` | victory |
| 11 | `ENEMY DEAD` | `0x29CDE0` / `0x29CE20` | |
| 12 | `CONDITION` | `btlMainInitStateCondition 0x29D1F0` / `0x29D6E0` | **→ 14** when no packets remain |
| 13 | `LOSE` | `0x29D720` / `sub_29D730` | game over |
| 14 | `FADE_OUT` | `0x29D760` / `0x29D800` | |
| 15 | `END` | `btlMainInitStateEnd 0x29D870` / `0x29DB60` | writes HP/SP back (`datCalcSetHp/SetSp`, `sub_300410/480` = add with clamp to max), clears battle-only statuses |
| 16 | `RESULT` | `0x29DBF0` / `0x29DC20` | the result screen task |
| 17 | `EXIT` | `0x29DCF0` / `0x29DD50` | |
| 18 | `TEST` | `0x29DDB0` / `0x29DDC0` | `btlStart(NULL)` without flag `0x141B` |
| 19 | `MC` | `0x29DE00` / `0x29DE10` | `btlStart(NULL)` with flag `0x141B` |

`btlStart 0x27D1D0` enters **2** with a setup block (`gBtl+0xBA5 = 0`, block → `gBtl+0xBA8`, `gBtl+0x244/0x246 = block+0x18/0x1A`) and **18/19** without (`gBtl+0xBA5 = 1`); then `gBtl+0xC |= 1`.

### 1.3 `btlAction`: one actor's turn (obs)

`btlActionCreate 0x299E90`: `RwHeapMalloc(1200)`, zeroed; `btlTargetInit(action+56)`; `+14 = 0` (next state), `+20 = 8`; `+0` = `btlGetUID()`; `+8` = running serial `gp-0x67C0`; `+36 = −1`; `+54 = datCalcRand(60)`; linked at the head `gBtl+0x14C` (`+1188` prev, `+1192` next); state 0 entered through `sBtlActionTbl[0].init`. **`btlActionSetState 0x299D60(action, s)`**: `+16 = +12` (previous), `+12 = s`, `+28 = 0` (frames), `sBtlActionTbl[3*s].init(action)`; `btlActionSetStateWithDelay 0x299DB0` fills `+14` (next) and `+18` (countdown). **`btlActionUpdateAll 0x299FB0`** walks the list: a pending `+14` counts `+18` down and switches when it reaches 0; an active action (`+24 & 1`) runs `tbl[+12].update(action)` and `+28 += 2`; one flagged `+26 & 2` is unlinked and `RwFree`d. The 36 rows of **`sBtlActionTbl 0x693410`** are the `btlActionInitState*`/`UpdateState*` pairs listed in order in `ida/logs/battle_q2.txt`/`q3.txt` (`0x28A990` Non … `0x299D20` Test); the largest bodies are `UpdateStateSkill 0x290BE0` (16,684 B), `UpdateStateAttack 0x28EB50` (8,316 B), `UpdateStateEscape 0x296890`. `btlActionUpdateStateAttack` / `Skill` are where `sub_309490` and `sub_303130` (§5) are called per target and where the 18 EFFECT.TBL section-0 reads happen (`0x7CE400`, animation records; not read further).

### 1.4 End-of-battle check `sub_27D380` (proposed `btlMainCheckBattleEnd`; obs)

Walks the action list counting, per active action whose `+26 & 1` and not `+24 & 0x20`: dead units (`datCalcIsDead(unit, 0)`), live enemies (`+162 == 1`) and live party members (`+162 == 0`); the hero dead (`unit.id == 1`) forces outcome **2 (lose)**; all enemies dead → **1 (win)**, unless a live enemy remains and `sub_2FD660()` (boss rule) → 0 (continue); only enemies left → **3**. The outcome goes to `gBtl+0x1C` and the function returns 1 when the battle is over.

## 2. Unit structures (`datUnit.c`; obs)

### 2.1 Where the units live

| who | record | evidence |
|---|---|---|
| hero | `DatUnit` at **`0x836224`** (`gGlobalWork 0x836200 + 0x24`) | `datGetUnit 0x16CD60`: `pc == 1 → byte_836224`; `datGetLevel/GetMaxHp 0x16C470/0x16C5F0` pass it to `datCalcGet*` |
| party member pc 2..10 | **`0x834010 + 868·(pc−2) + 4`** (868-byte member record: unit at +4, equipment slot indices `s16[]` at +0x54, persona at +0xDC) | `datGetUnit` (`(pc−2)·868 + 4`), `datGetEquipmentIdx 0x16CB80` (`0x83399C + 868·pc + 2·slot`), `datPersonaGetByPcId 0x174800` (`dword_834010[217·pc − 379]`) |
| hero's equipment / persona | slot indices at `0x83678C`; persona `datPersonaGetHeroPersona(word_836BA8)` | `datGetEquipmentIdx`, `datPersonaGetByPcId` |
| a party "genus" | 12 B `{u16 kind = 0, u16 count = 1, u32 unit}` | `datUnitCreatePc 0x2FF340(pc)` |
| an enemy genus | 372 B `{u16 kind = 1, u16 count, u32 units = +12, u16 encounter_id, …}` + **6 × 60-byte units at +12** | `datUnitCreateEc 0x2FF3E0(encounter)`: counts the non-zero `u16 units[5]` at ENCOUNT record +8, `datUnitInit(+12 + 60·k, 1, id)` for each; `sub_2FF540` (proposed `datUnitEcAddEnemy`: first free slot of 6, reinforcement/summon), `datUnitEcRemoveEnemy 0x2FF660`, `sub_2FF790` (proposed `datUnitIsGenusDead`: every unit `datCalcIsDead`), `datUnitDestroyGenus 0x2FF760` = `RwFree` |

### 2.2 `DatUnit` (60 bytes; `game/include/p3fes/game/battle.h`)

| off | type | meaning | evidence |
|---|---|---|---|
| +0x00 | u16 | flags: **bit 0** initialised, **bit 2 enemy** (`& 4` is the enemy/party test in every `datCalc` function), bit 4/5/7/8 copied from EnemyRecord flags bits 3/4/8/9, **bit 9** has one of the evade skills 544/545/546 | `datUnitInit 0x2FF890` |
| +0x02 | u16 | id: pc 1..10 (assert `< 0xB`) or enemy 0..335 (assert `< 0x150`) | `datUnitInit`, every assert |
| +0x04 | u16 | base id (the id at creation; the affinity table is indexed by it) | `datUnitInit`, `sub_306E80` |
| +0x06 | u8 | level (enemies, **and the hero**: `datCalcGetLevel 0x2FFCC0` reads +6 when `flags & 4` or `id == 1`; other members use `datPersonaGetLevel` = persona +4) | obs |
| +0x08 / +0x0A | u16 | HP / SP (`datCalcGetHp 0x2FFD70`, `GetSp 0x2FFD80`; `SetHp 0x2FFD90` / `SetSp 0x2FFDC0` cap a value ≥ 1000 at **999 unless the unit is an enemy**) | obs |
| +0x0C | u32 | bad-status word: `datCalcGetBadStatusNoDown 0x300530` = low 20 bits; `datCalcSetBadStatus 0x3004F0(unit, bits)` replaces the low 20 bits when `bits & 0xFFFFF != 0` and always ors the high 12; `ClearBadStatus 0x300560` ands `~bits`; `ChkBadStatus 0x300580`; **bit 19 (0x80000) = dead** (`datCalcIsDead 0x30B5A0`: that bit, or `hp + delta <= 0`). Bits seen: 2 distress (advantage roll), 8 (instant-kill check in `sub_309490`), 0x10 critical-eligible ("down" — `sub_303130` ×2 with skill 543), 0x20/0x40 frozen/shocked (map to ice/elec in `sub_308120`), 0x100/0x200/0x400/0x10000 the four light/dark death-class bits (`sub_308120` → element 7), 0x100000 (an "always hit / no formula" flag in `sub_309490`), 0x80000+ dead | obs |
| +0x14 | u32 | effect flags: bit *i* = buff slot *i* active (slots 17..20 exist only as bits); bits 0x80000/0x100000 = attack-type flags read by `sub_301880` | `sub_301230`, `sub_301540`, `sub_301750` |
| +0x18 | u32 | zeroed by `sub_301870` (10 call sites in the AI) | obs |
| +0x1C | u8[9] | **buff levels: slots 0..16 as signed nibbles** (even slot = low nibble, odd = high; 8..15 stand for −7..0 via `nibble − 15`), set by `sub_301030(unit, slot, level)` (assert −8 < level < 8), changed by `sub_301230(unit, slot, ±1)` (clamped to −1..1 per step), read by `sub_300F60` / `sub_301750`; slots used: 8/9 (null-class walls), 10 (accuracy multiplier), 11 (repel-class), 13/14/15/16 (fire/ice/elec/wind walls → `sub_306E80`), 3 (defense), 0/1 attack flags | obs |
| +0x29 | u8[9] | the matching 4-bit turn counters (`sub_301150`) | obs |
| +0x38 | u16 | the result message id the calc selected (4639 critical, 4640..4642 evade, 4604..4623 accuracy skills) | `sub_303130`, `sub_309490` |

`sub_301540(unit, slot)` clears one slot (nibble, counter and flag bit; asserts `slot < 21`), `sub_301690` clears all 21 (`btlMainInitStateEnd`, death, exit).

### 2.3 EnemyRecord (UNIT.TBL section 0, 62 bytes × 336; obs from the readers, checked on record 1 = "Cowardly Maya")

| off | type | meaning | reader |
|---|---|---|---|
| +0 | u16 | flags: bit 3 → unit 0x10, bit 4 → 0x20, bit 6 → result flag `gBtl+0xBDC |= 2` (`sub_2D7560`), bit 8 → 0x80, bit 9 → 0x100 | `datUnitInit`, `sub_2D7560` |
| +2 | u8 | race/kind 0..14 (equipment "slayer" effects 36..48 / 144..169 by race in `sub_303130`) | `sub_303130` |
| +3 | u8 | level | `datUnitInit` |
| +4 / +6 | u16 | max HP / max SP | `datUnitInit`, `datCalcGetMaxHp/MaxSp` |
| +8 | u8[5] | St, Ma, En, Ag, Lu (`sub_300B60`, clamped 1..99 by `datCalcGetStat`) | obs |
| +14 | u16[8] | skills (`sub_308BB0` returns the address; `sub_308BA0` = 8) | obs |
| +0x38 | u8 | normal-attack accuracy % (record 1: 98) | `sub_309080(unit, 1)` |
| +0x3A | u16 | normal-attack power | `sub_309080(unit, 0)` |
| +0x3C | u16 | normal-attack skill id → its element through SKILL section 0 | `sub_3082F0`, `sub_308930`, `sub_309490` |

UNIT.TBL **section 1** (`0x7CE414`, 32 B × 336) = **`u16 affinity[16]` per enemy**, indexed by `base_id`: `rate% = 5 × low byte`, high byte = flags placed at bits 24..31 (`sub_306E80`; record 1 shows `0x0014` = 100 % and `0x0800` = weak at element 3 = fire, obs from the file). Section 2 (`0x7CE424`, 8 KB) is read by `datPersona.c` (`sub_1733B0`, `sub_173460` = a PC's affinity through the persona — inf: persona affinities, 256 × 32 B).

## 3. The `.TBL` loader and the table map

### 3.1 Loader (obs)

`kwlnInitMain` → `sub_27E180 0x27E180` (zeroes `gp-0x481C/0x4818/0x4814` = arena offset `0x7CE4D4`, request handle `0x7CE4D8`, reload index `0x7CE4DC`) → **`sub_27DE40(1)`** (proposed `btlTableLoadAll`): for `i < 8` calls **`sub_27DCD0(off_692D40 + 168·i, sync = 1)`** (proposed `btlTableLoad`); with `sync = 0` it is the per-frame body of `btlUpdateTableReloadTask 0x27E1D0` (one record per call, `gp-0x4814` counts to 8). `sub_27DCD0`: picks `name` or `name_F` by `datGetScenarioMode()` (The Answer uses the `_F` files), `H_Cdvd_Request` + `ReadSync` (or `IsFileLoaded` polling), then walks the file's sections: for each record pair `k` while `dst[k] != 0`: `*dst[k] = 0x875D00 + offset`; `memcpy(*dst[k], section + 4, size)`; `offset += align16(size)` and `section += align16(size + 4)` (the `(x + 15) & ~15` idiom at `0x27DDA4–0x27DDC0` / `0x27DDD8–0x27DDF0`). The record's `size` words (second of each pair) are not read by the loader. `sub_27DF20` patches 23 table rows and two static tables (`0x68F0F0`, `0x68FAB0`) for The Answer.

### 3.2 Records of `off_692D40` → section pointers → readers (obs: words at `0x692D40–0x693280`, section sizes from the files, readers from the gp-relative scan `battle_q4.txt`)

| record | file (sizes on disc) | section → pointer (bytes) | what it is |
|---|---|---|---|
| 0 `0x692D40` | `battle/SKILL.TBL` (21,904 B) | 0 → `0x7CE3F4` (0x4E0): **`{s8 element, u8}[624]`** (the element of every skill id, −1 = none; 1 `sub_3082F0`); 1 → `0x7CE3F8` (0x4FC0): **`SkillRecord[464]`, 44 B** (98 readers); 2 → `0x7CE3FC` (0xC0) (`sub_30C0C0/30C220`, `sub_2E3D50`) | SkillRecord fields read: +0 `flags0` (**bit 1 physical**: `sub_3088B0`, `sub_311250`), +1 `flags1` (bit 0 field-usable, `sub_300AF0`), +2 kind (1 HP / 2 SP formula set), +14 accuracy % (0 = sure hit), +17 / +20 HP / SP formula id, +18 / +22 `s16` HP / SP base, +25 (case 18 of §4), +36 target class (1 = instant death, 2/3 moon-phase, 4/5 condition), +37/+38 (cases 20/21), +40 `u16` minimum damage |
| 1 `0x692DE8` | `battle/UNIT.TBL` (39,824 B) | 0 → `0x7CE410` (0x5160) EnemyRecord[336]; 1 → `0x7CE414` (0x2A00) enemy affinities; 2 → `0x7CE424` (0x2000) persona affinities (inf) | §2.3 |
| 2 `0x692E90` | `battle/MSG.TBL` (45,648 B; no `_F`) | 0 → `0x7CE4F0` (0x2A0): **arcana names 21 B × 32** (`sub_30BBB0(id < 0x20) = base + 21·id`; "Fool", "Magician"…); 1 → `0x7CE4EC` (0x2E50): **skill names 19 B × 624** (`sub_30BB40(id < 0x270)`); 2 → `0x7CE4E8` (0x18F0): **enemy names 19 B × 336** ("Cowardly Maya" = id 1); 3 → `0x7CE4E4` (0x1100): persona names 17 B × 256 (`sub_173220`, `sub_3D3D20` ×6); 4 → `0x7CE4E0` (0x5723): a text block kept by `btlCreate` | names are plain ASCII, NUL-padded |
| 3 `0x692F38` | `battle/PERSONA.TBL` (46,448 B) | 0 → `0x7CE420` (0xE00, 78 readers in `datPersona.c`/the status screens: 14 B × 256 persona records), 1 → `0x7CE428` (0x4600), 2 → `0x7CE430` (0x4DC0), 3 → `0x7CE434` (0xDC8), 4..16 → `0x7CE44C,450,454,458,45C,460,464,468,438,43C,440,444,448` (small: 0x6E, 0x46, 0x6E, 0x6E, 0x5A, 0x46, 0x3C, 0x3C, 0x190, 0xC, 0x1A, 0xB4, 0x1C; readers `sub_1FA0D0/1FA4F0` (fusion), `sub_1FB560`, `sub_1FBA70`, `sub_274590`) | persona stats/skills/fusion rules; records not read in this topic |
| 4 `0x692FE0` | `battle/ENCOUNT.TBL` (62,544 B) | 0 → **`gEncountTbl 0x7CE4A8`** (0x7000): **1,024 × 28-byte encounters**: +0 `u32 flags` (bit 4/5 advantage override, bit 8 no-escape class, bit 9; `btlMainInitStateUnitCreate`), +8 **`u16 units[5]`**, +18 `u16` field id, +20 `u16` room, +24 `u32` BGM (`btlSoundPlayBgm`); 1 → `0x7CE4B0` (0x1388), 2 → `0x7CE4B4` (0x578), 3 → `0x7CE4AC` (0x3A9C), 4 → `0x7CE4B8` (0x3084) | §3.3 |
| 5 `0x693088` | `battle/EFFECT.TBL` (62,080 B; no `_F`) | 0 → `0x7CE400` (0x32C0; `btlActionUpdateStateSkill` ×18, camera), 1 → `0x7CE404` (0x63C0; `sub_2B47B0`), 2 → `0x7CE4BC` (0x59B8; boss setup `sub_2F6E00`), 3 → `0x7CE4C4` (0x40), 4 → `0x7CE4C8` (0x48), 5 → `0x7CE4C0` (0x174) | skill animation / camera records (not read) |
| 6 `0x693130` | `battle/MODEL.TBL` (105,840 B; no `_F`) | 0 → `0x7CE408` (0x940), 1 → `0x7CE40C` (0xB6E), 2 → `0x7CE418` (0x13080), 3 → `0x7CE42C` (0x5800) | model/animation ids (not read) |
| 7 `0x6931D8` | `battle/AICALC.TBL` (524,240 B) | 0 → `0x7CE46C` (0x1F8 = **126 floats**: the level-difference multipliers, two 63-entry halves; case 23/33 of §4), 1 → `0x7CE470` (0x34 = 13 floats; case 24), 2 → `0x7CE474` (0x3C), 3 → `0x7CE478` (0x14 = 10 × s16; case 25), 4 → `0x7CE47C` (0x28 = 20 × s16; case 26 clamps the index at 20 and so reads 2 bytes past the section — obs), 5 → `0x7CE480` (0xC; `sub_301880`), 6 → `0x7CE488` (0xF), 7 → `0x7CE48C` (0x20), 8 → `0x7CE484` (0x30), 9 → `0x7CE490` (0x2C), 10 → `0x7CE494` (0x3C), 11 → `0x7CE498` (0x3C), 12 → `0x7CE49C` (0x54), 13 → `0x7CE4A0` (0x55), 14 → `0x7CE4A4` (0x40), 15 → `0x7CE41C` (0xD740 = **1,044-byte boss records**, `sub_2F6E00`), 16 → `0x7CE4CC` (0x15CC9, **`FLW0` at +8**: the per-character AI scripts `AI_PC_%03X_%03X`, inf from `sub_2C6F50`), 17 → `0x7CE4D0` (0x5C66D, **`FLW0`**: the event/boss AI, `AI_EVENT_%03X_*` obs) | the AI is BF code run by the script VM of topic 18 with the `btlAI*` COMM functions |

### 3.3 Tartarus encounters (`k_encount.c`; obs)

`sub_1D78C0(floor, a2, a3)` (proposed `K_Encount_PickEncounter`): floors `0x14..0x1C`, `0x28..0x30` (with `a2 == 0`), `0x33..0x3A`, `0x47..0x4E` are the block-boundary floors and take their group from ENCOUNT section 1 (`0x7CE4B0 + 10·a3 + 6`); floors `0x1F..0x27` from section 2 (`0x7CE4B4 + 200·floor + 10·a2 − 6204`); other floors return 0 (no random encounter table — their encounters come from the field data, inf). The `u16` so found indexes **180-byte groups in section 4** (`0x7CE4B8`): 15 × 12-byte entries `{u16 weight, u16 encounter_id, …, byte 7 bit 0 = weight doubled when `K_FldDungeon_GetFloorKind() == 2`}`; the pick is `RpRandom() % Σweights` walked cumulatively; `K_Assert("k_encount.c", 327)` on a zero total. `sub_1D7300/1D75F0/1D76E0/1D77D0` read sections 1–3 for the floor layout (`sub_1D0720` caller; not read further).

## 4. `datScript.c`: the AICALC evaluation context (obs)

**`sub_30FC40(fn, attacker, target, skill, mode)`** (proposed `datScriptCalc`): stores `gDatScriptAttacker 0x957190`, `gDatScriptTarget 0x957194`, `gDatScriptSkill u16 0x95719C`, `gDatScriptMode 0x9571A0`, clears bit 0 of `0x9571A4` (result-valid); picks **`sDatScriptFuncTbl2 0x69AAE0`** when `datGetFlag(0x1311)`, **`sDatScriptFuncTbl3 0x69AB30`** when `datGetFlag(0x1319)`, else **`sDatScriptFuncTbl1 0x69AA90`** (17 entries each, entry 0 a nullsub; asserts `fn < 0x11`, lines 0x8B/0x90/0x93); calls `tbl[fn]()`; asserts the result flag (line 0x9B) and returns **`gDatScriptResult 0x957198`** (set by `sub_311190(v)` = `0x957198 = v; 0x9571A4 |= 1`). Callers: `sub_303130` (fn 1/2/3/15 = damage/recovery/heal formulas), `sub_309490` (fn 4 = accuracy), `sub_2DC180` ×7 (status infliction), `sub_305970`, `sub_30A740`, `sub_30C2A0`. The three tables are the three difficulty/mode formula sets (inf: flags `0x1311`/`0x1319`).

Each formula function (`sub_30C520 … sub_30FAF0`, 48 functions) reads its inputs through **`datScriptGetValue 0x30FDF0(selector, index)`** (`datScript.c` lines 190–459; `jpt 0x7B90A0`, 35 cases; `K_Assert` when the needed unit pointer is NULL):

| case | value | source |
|---|---|---|
| 1 / 2 | level of attacker / target | `datCalcGetLevel` |
| 3 / 4 | HP | `datCalcGetHp` |
| 5 / 6 | max HP | `datCalcGetMaxHp` |
| 7 / 8 | SP | unit +0xA |
| 9 / 10 | max SP | `sub_300100` (proposed `datCalcGetMaxSp`) |
| 11 / 12 | affinity of attacker / target to the skill's element: `sub_306E80(unit, sub_3082F0(attacker, skill))` is evaluated; the case then yields the float constant 100.0 (`0x42C80000`) — the multiplier itself reaches the formula through the affinity word's rate (inf: the decompiler shows only the constant; not traced further) | obs/inf |
| 13 / 14 | stat `index` (0 St, 1 Ma, 2 En, 3 Ag, 4 Lu; assert `index < 5`) of attacker / target | `sub_300C90` (proposed `datCalcGetStat`) |
| 15 / 16 | affinity of attacker / target to the element that resists the status `gDatScriptMode` (`sub_308120(skill, mode)`, skipped for 16/17/−1) → 100.0 as above | obs |
| 17 | skill accuracy: physical → `sub_309080(attacker, 1)` (weapon/normal-attack accuracy), else `SkillRecord+14` | obs |
| 18 | `SkillRecord+25` | obs |
| 19 | skill power: physical or `+17 == 16` → `sub_309080(attacker, 0)` (weapon power: enemy +0x3A, PC `sub_16F9F0`), else `+18` (mode 1, HP) / `+22` (mode 2, SP); any other mode asserts (line 316) | obs |
| 20 / 21 | `SkillRecord+37` / `+38` | obs |
| 22 | the constant **31000** (the damage ceiling) | obs |
| 23 | `AICALC0[clamp(lvA − lvB, −31, 31) + 31]` (float; `+94` instead of `+31` when `gBtl == NULL`, i.e. outside a battle) | obs |
| 24 | `AICALC1[clamp((lvA − lvB ± 1) / 3, −6, 6)]` | obs |
| 25 | `AICALC3[min(Lu_attacker / 10, 9)]` (s16) | obs |
| 26 | `AICALC4[min(Lu_attacker / 5, 20)]` (s16) | obs |
| 27 | `*(u16*)(gBtl + 0xB98) + 1` (the round counter + 1, inf) | obs |
| 28 | the constant `0x950000` | obs |
| 29 / 30 | `sub_309250(attacker, 0 / 1)` (enemy: 10; PC: body armour defense `sub_16FCC0` / evasion `sub_16FBD0` through equipment slot 2) | obs |
| 31 / 32 | the same for the target | obs |
| 33 | as 23 without the `gBtl` offset | obs |
| 34 | `*(u16*)(gBtl + 0xB9E)` | obs |

Example, **fn 1 = `sub_30C520`** (physical-or-magic attack damage, the AICALC "ATTACK" formula): with `P = GV(19)` (power), `St = GV(13, 0)`, `En = GV(14, 2)` (the target's Endurance, read twice and summed = `2·En`), `A = GV(12)`, `L = GV(23)` (level-difference multiplier):
* PC attacker, physical: `dmg = 10·√( (30·(P − 30)) / (5·2·En) · (St / 5) ) · A · L`
* PC attacker, magic: the same with `30·P` (no `− 30`)
* enemy attacker: `En' = c1 · ( GV(32)/4 + 2·En )` (`GV(32)` = the target's armour, `c1 = *(float*)(gp−32636)`), `dmg = c2 · ( 10·√( 30·P / (5·En') · St/5 ) · A · L )` (`c2 = *(float*)(gp−32100)`), the magic variant subtracting 10 before `· A`.
`sub_30C930` (fn 2, recovery) uses `GV(13, 1)` (Ma) and the Luck table `GV(25)` in a multiply-add. The remaining 46 functions follow the same shape (not transcribed; queue).

## 5. `datCalc.c`: the formulas (obs unless marked)

### 5.1 Base values

* **`datCalcGetMaxHp 0x2FFDF0(unit)`** (784 B): `base = enemy ? EnemyRecord+4 : u16 at 0x5DC1B4 + 44·level + 4·pc` (the PC growth table: 44-byte rows = 11 pcs × `{u16 hp, u16 sp}`, `sub_16CC00`); `bonus = Σ` skills 537/538/539 (+10/20/30 %), 620 (+50 %), 567 (+100 %), 568 (−50 %), each `base·n/100` with the EE `div`; `+ 10·n26 + 20·n27 + 30·n28 + 40·n29 + 50·n30 + 100·n142` where `nX = datCalcCountEquipmentWithEffect(unit, X)`; `total = base + bonus`, **capped at 999 for party members** (`datCalc.c` lines 169/172 assert the id ranges). **`sub_300100`** (proposed `datCalcGetMaxSp`) is the same body with skills 540/541/542/621, 567 (−50 %) / 568 (+100 %) swapped, equipment 31..35 and 143, the growth table at `0x5DC1B6`. `sub_300410/0x300480` (proposed `datCalcAddHp/AddSp`): `hp = clamp(hp + delta, 0, max)`.
* **`datCalcGetLevel 0x2FFCC0`**: unit +6 for enemies and the hero, else the persona's level (`datPersonaGetByPcId` +4); asserts a non-zero level (line 70).
* **`sub_300C90`** (proposed `datCalcGetStat(unit, stat)`): enemy → `EnemyRecord+8+stat`; PC → `sub_1738D0(pc, stat)` = persona base (+28+stat) + `datPersonaGetBonusStat` + `datPersonaGetStat3` + `sub_173C60`, clamped 0..99; then **clamped to 1..99** (lines 0x304/0x30B).
* **`datCalcHasSkill 0x3005E0(unit, skill)`**: the 8 slots (`sub_308BB0`: enemy `EnemyRecord+14`, PC `datPersonaGetSkillsByPcId`) and, for PCs, the accessory (equipment slot 3 → item `sub_170E40(id 3000..3999)`, 36-byte records, `+0x1C` = granted skill). `datCalcGetPassiveSkillFlags 0x300D80`: bits for 547..552, 607, 608. `sub_300750(pc, effect)`: any of equipment slots 0..2 has effect `effect` (`datGetEquipmentEffect`); `datCalcCountEquipmentWithEffect 0x3009A0` counts them.
* **`datCalcRand 0x2FFBC0(n)`**: `n == 100` → `((effMiscRand(0) & 0xFFF) + (effMiscRand(0) & 0xFFF)) & 0xFFF) / 41` (0..99), **re-rolled once when within ±3 of the previous roll** (`gp-0x47E0` = `0x7CE510`); else `effMiscRand(0) % n` (`K_Assert` on `n == 0`, line 26).
* **`datCalcIsLowHp 0x30B5E0`**: `100·hp / maxhp < 26`.

### 5.2 Elements and affinities

* Element indices (obs from the users): 0 slash, 1 strike, 2 pierce, 3 fire, 4 ice, 5 electricity, 6 wind, 7 light, 8 dark, 9..15 the ailment rows, 16/17/18 almighty/recovery/support (always rate 100), −1 none. **`sub_3080C0(e)`** (proposed `datCalcGetElementBit`) = `1 << (e + 1)` (assert `e < 19`, line 3752) — so bit 0 = none, bits 1..3 physical (`0xE`), `0xE0000` the three neutral rows.
* **`sub_3082F0(unit, skill)`** (proposed `datCalcGetSkillElement`): physical skill (`flags0 & 2`) with a unit → the weapon element: enemy `EnemyRecord+0x3C` (a skill id) → section 0; PC `item(+30)` of equipment slot 0 (`sub_170D60`: 40-byte item records below id 1000); otherwise `s8` SKILL section 0 `[2·skill]`.
* **`sub_308120(skill, status_bit)`** (proposed `datCalcGetElementForStatus`): with a skill, element 8 (dark) wins; otherwise the status bit maps to the row that resists it: `0x1 → 10, 0x2 → 12, 0x4 → 13, 0x8 → 14, 0x10 → 15, 0x20 → 4 (ice: frozen), 0x40 → 5 (elec: shocked), 0x80 → 11, 0x100/0x200/0x400/0x10000 → 7 (light), 0x8000 → 9` (`K_Assert` line 3817 otherwise; the function then returns whatever `$s0` held — the caller's register when no skill was given, obs).
* **`sub_306E80(unit, e)`** (proposed `datCalcGetAffinity`, 4,664 B): 16/17/18 → 100; −1 → 0; `word = enemy ? UNIT sec 1[base_id·32 + 2e] : sub_173460(pc, e)`; `rate = 5 × low byte`, `flags = high byte << 16`; when the rate byte is 0 the flags decide: **bit 27 (0x08) weak → 125 (150 with flag 4889)**, **bits 24/25/26 (0x01/0x02/0x04) → 100**, **bit 28 (0x10) → 50**; then the unit's passive skills per element add bits **0x10000000 resist / 0x1000000 null / 0x2000000 repel / 0x4000000 absorb** (quartets 464..491 for elements 0..6: e.g. fire 476 Resist, 477 Null, 478 Repel, 479 Absorb; light/dark 492..497; ailments 498..506/612..619 plus equipment 183..188; 507 = "resist all but 7"); the four **element walls** (buff slots 13/14/15/16 for fire/ice/elec/wind) and equipment 73..99 force rate 100 and clear repel/absorb (`v13`/`v12` merges at `0x307F60+`). **`sub_30B4B0(unit, e)`** wraps it (−1 → 0, neutral rows → 100).
* **`sub_309490(attacker, target, skill, flags)`** (proposed `datCalcCheckHit`, 4,784 B): returns the **result code**: **1 hit, 4 miss, 256 null, 512 repel/evade (no damage to the target; the caller handles the reflection), 1024 drain** (inf names; the codes are obs: `sub_303130` turns 1024 into recovery and zeroes 2/4/256). Order: skill class `+36 == 1` (instant death) → `target.status & 8 ? 1 : 4`; element bit (weapon element for physical skills); for non-neutral elements: physical → the target's dodge flag `+20 & 0x20000` → 512, the attacker-side **evade skills 546/545/544 (or equipment 179/178/177) at 20/15/10 %** → 512 with message 4642/4641/4640; magic → `+20 & 0x40000` → 512; buff slot 11 > 0 → 512; slots 8/9 → 256; the affinity bits of `sub_30B4B0` → 512 (0x2000000) / 1024 (0x4000000) / 256 (0x1000000); then **accuracy**: `SkillRecord+14 == 0` → miss?/sure hit (`+14 != 0` guards the formula: 0 → **4**); attacker status 0x100000 or target flag 0x80 or target status 512/2/64/32 (asleep, distressed, shocked, frozen) → **1**; else `rate = (int)(m · (float)AICALC_fn4) − evasion` with `m` = the per-element "Hit Rate Up" skills 508..521 (×`gp-32604`/`gp-32572` consts, messages 4604..4617), 526/527 (physical/magic), 563 (×0.5), buff slot 10 (×`gp-32544`), 564 = always hit; `evasion = Σ` equipment effects 103..129 (+5/10/15 by element); **`rate = clamp(rate, 50, 99)`; hit iff `datCalcRand(100) < rate`**, else 4 with the message.
* **`sub_303130(skill, attacker, target, hits, result, kind, flags, hp_or_sp)`** (proposed `datCalcDamage`, 10,304 B; asserts `skill < 0x270`/`< 464`, lines 1731/1732): selects formula `f = SkillRecord+17` (HP) / `+20` (SP) with base `b = +18` / `+22` and the unit's current and max value; kinds (obs, `jpt` cases): 0 none; **1, 0xC, 0xE: AICALC fn 2 (SP skills) or fn 1 (HP) + b**, 0xC/0xD capped at the target's current value, 0xE divided by `hits`; 2: recovery fn 3/1 + b; 3: `cur − b` (to leave b); 4/0xD: fixed b; 5: fixed recovery b; 6/7: `50 + b` damage/recovery; 8/9: `cur·b/100`; 0xA/0xB: `max·b/100`; 0xF: `datCalcRand(b)` recovery; 0x10: fn 15. For a formula damage (`flags & 1` clear): element boosts (fire 528/529, ice 530/531, elec 532/533, wind 534/535 → ×1.25 / ×1.5; equipment 173..176), **critical** `target.status & 0x10` with skill 543 → ×2, message 4639; weapon-type skills 582..586/573 ×1.25 (`datCalcGetHeldWeaponType 0x308C60`), 574/575 ×1.25, target 564 ×0.5; race slayers (EnemyRecord+2 = 2..14 → equipment 36..48 ×1.25, 144..169 ×1.5/×1.75); the target's resist equipment 73..99 (×consts); then **`dmg = (int)(mult · crit · atkbuff · (base · tgtbuff))`** (`sub_301880(attacker, 0|1, skill)` / `(target, 3, skill)` are the buff multipliers), **`dmg = clamp(dmg, SkillRecord+40, 31000)`**, **`dmg = dmg · (datCalcRand(11) + 95) / 100`** (±5 %), `hits == 16` → 500 fixed, at least 1. Recovery takes the same tail without the race/resist steps (570 doubles). Result code 1024 turns damage into recovery, 4/2/256 zero both; the return is `−damage` or `+recovery`.

### 5.3 Other datCalc helpers (obs; sizes from `functions.json`)

`sub_300AF0(skill)` (proposed `datCalcIsSkillUsableOnField`): `id < 464 && !(flags0 & 2) && (flags1 & 1)` — 32 skills on the disc; `sub_3088B0` (proposed `datCalcIsPhysicalSkill`) — 16 skills; `sub_3086C0` = `SkillRecord+3`; `sub_308A50(id)` = `0x110 <= id < 0x131`; `sub_308860(id)` = `0xC0 <= id < 0xC6` (the six Mix Raid ids, inf); `sub_308930(unit)` = the attack skill id of the held weapon type (items `+0x1E` 1..6 → 0x15F..0x15A); `sub_308ED0/sub_3093A0` = the held weapon's item id (asserts `< 0xFF`, the latter also `0xC0..0xDF`); `sub_308A80(unit)` = a random Mix-Raid-capable skill of the unit; `sub_308FD0`; `sub_30BB40/sub_30BBB0` = skill / arcana name pointers (§3.2); `sub_30C440` (proposed `datCalcRestorePartyAll`): for pc 1..10 `datSetHp(max)`, `sub_16CF90(sub_16C670)` (SP), `datClearBadStatus(−1)` (used by `K_FldEvent_UpdateFldEventTask`).

## 6. What Phase 5/6 must preserve

* The formulas are integer code with EE `div`/`divu` (`datCalcRand`, the percent bonuses, the clamps) around short `float` chains (`mul.s`, `sqrt.s`, `cvt.w.s`): a native rewrite must keep the EE single-precision semantics (`p3fes/ee/fpu.h`: `sqrt.s` is exact, `cvt.w.s` truncates with saturation) and the exact evaluation order of the multiplier products, or damage values drift by 1.
* `datCalcRand`'s re-roll rule and the `effMiscRand` stream make every battle outcome a pure function of the RNG state; snapshot diffs across a battle must keep that stream (topic 15's MT19937 is a different generator — `effMiscRand 0x357FD0` is the effect library's).
* The AI is BF script (`FLW0` blobs inside AICALC.TBL) run by the topic-18 VM with the `btlAI*` COMM set: a native VM needs those COMM functions (the `scrGetUserData` word is the action object, `sub_2D0A30` stores the chosen skill at `action+108/110`).
* `K_Assert` is `jr $ra`: every "assert then index" pair in this band (skill ids ≥ 464, enemies ≥ 336, slots ≥ 21) reads out of the table; the hand versions reproduce the read.

## 7. Open questions

* Cases 11/12/15/16 of `datScriptGetValue` return the float constant 100.0 after calling `sub_306E80`; how the affinity rate reaches the formula (a global written inside `sub_306E80`, or `$f0`) was not traced — the decompiler loses the FPU register flow. Needed before a native damage path.
* The formula functions `sub_30CB90 … sub_30FAF0` (46 of 48) and the three table selections (`0x1311`/`0x1319`) are unread; the per-difficulty constants at `gp-32100/-32544/-32572/-32604/-32636` were not resolved to addresses.
* PERSONA/EFFECT/MODEL record layouts; UNIT.TBL section 2 (persona affinities, inf); the 55 KB boss table rows beyond the pointer arithmetic of `sub_2F6E00`.
* The exact meaning of result code 2 and of status bits 0x8000/0x80 in `sub_308120`; whether 512 is reported as "repel" or "evade" by the panel (`bp_*`) is not read.
* `sub_27D560`'s skill 4040 ("revival" condition) and the `gBtl+0xC` flag words (bits 1, 0x80, 0x100, 0x800, 0x800000, 0x200000, 0x100000, 0x4000000) deserve a bit table once the btlMain bodies are read in full.

## 8. Replaced in this wave (`game/src/battle/`, `game/replaced.txt`; the delta was imported into the master 2026-10-20, so `game/` and `symbols/p3fes.sym` now carry the names of the second column)

| function (address) | name (was the proposed one; the master's since 2026-10-20) | role | size | why it is safe |
|---|---|---|---|---|
| `0x2FFD70` / `0x2FFD80` | `datCalcGetHp` / `datCalcGetSp` | `u16` at +8 / +0xA | 12 B each | one load |
| `0x2FFD90` / `0x2FFDC0` | `datCalcSetHp` / `datCalcSetSp` | store with the party cap at 999 (§2.2) | 48 B each | two loads, one store; `$v0` untouched like the original |
| `0x300550` / `0x300530` | `datCalcGetBadStatus` / `…NoDown` | the status word / its low 20 bits | 12 / 20 B | one load |
| `0x3004F0` | `datCalcSetBadStatus` | replace the low 20 bits when given, or in the high 12 | 64 B | two read-modify-writes; returns the word as `$v0` did |
| `0x300560` / `0x300580` | `datCalcClearBadStatus` / `datCalcChkBadStatus` | `&= ~bits` / `(word & bits) != 0` | 24 / 20 B | one load |
| `0x30B5A0` | `datCalcIsDead` | bit 19 or `hp + delta <= 0` (32-bit wrap kept) | 60 B | two loads |
| `0x300F60` / `0x301750` | `datCalcGetEffectLevel` / `datCalcGetEffectState` | the signed nibble / the flag bit of a buff slot | 196 / 284 B | `K_Assert` through `guest::call`, nibble arithmetic |
| `0x300AF0` / `0x3088B0` | `datCalcIsSkillUsableOnField` / `datCalcIsPhysicalSkill` | SKILL.TBL flag bits by id | 104 / 116 B | table pointer + record read; the assert path reads past the table as the original does |
| `0x3080C0` | `datCalcGetElementBit` | `1 << ((e + 1) & 31)` | 84 B | pure arithmetic |
| `0x308120` | `datCalcGetElementForStatus` | the 13-entry status → element map, the dark override through `datCalcGetSkillElement 0x3082F0` (`guest::call`) | 452 B | if-chain; the caller's `$s0` is returned on the no-match path exactly as the compiled code does |

Pair tests: `tests/game/test_battle.cpp` — randomised unit records in the guest arena (2,500 HP/SP rounds incl. the cap boundary and wide values, 3,000 status rounds with single-bit/high-only/low-only masks, 3,000 `IsDead` rounds around `hp + delta == 0` and the 32-bit wrap, 1,200 × 44 buff-slot rounds incl. the assertion paths), the real `battle/SKILL.TBL` sections 0 and 1 (every id 0..599 for the flag lookups, 464 skills × the status map, the seven Dark skills, `physical == 16`, `field == 32`), element rows −40..60. Whole-program gates: dorm replay and M1 (`docs/INTEGRATION_LOG.md`); the dorm route has no battle, so they only show nothing else moved.

## 9. Names proposed in `symbols/deltas/battle.sym` (imported into the master 2026-10-20)

138 rows + 7 function comments: **89 promotions** of tge-pr4 names whose behaviour was checked here (83 F: the btlMain table's 38 init/update functions (states 1..19) and its three drivers, the btlAction drivers, `btlStart`/`btlCreate`/root tasks, `datUnit*`, the datCalc accessors of §2.2/§5.1, `datGetUnit`/`datGetEquipmentIdx`/`datPersonaGetByPcId`; 6 D: `gBtl`, `gEncountTbl`, `sBtlActionTbl`, `sDatScriptFuncTbl1..3`) — `sub_29D730` takes the hint `btlMainUpdateStateLose` from its row of `0x693760` — and **49 names of our own** (39 F, 10 D). Besides the `proposed` names in the text above, the delta names: `datUnitIsGenusReady sub_2FF320`, `btlTableInit sub_27E180`, `btlTablePatchForAnswer sub_27DF20`, `btlBossSetup sub_2F6E00`, `btlOrderSortByAgility sub_29A570`, `datCalcSetEffectLevel sub_301030`, `datCalcAddEffectLevel sub_301230`, `datCalcClearEffect sub_301540`, `datCalcClearAllEffects sub_301690`, `datCalcGetEffectLevel sub_300F60`, `datCalcGetEffectState sub_301750`, `datCalcGetEffectMultiplier sub_301880`, `datCalcGetSkillSlotCount sub_308BA0`, `datCalcGetSkillList sub_308BB0`, `datCalcGetWeaponParam sub_309080`, `datCalcGetArmorParam sub_309250`, `datCalcGetAffinityChecked sub_30B4B0`, `datGetSkillName sub_30BB40`, `datGetArcanaName sub_30BBB0`, `datScriptSetResult sub_311190`; data `sBtlMainStateTbl 0x693760`, `gBtlSkillElementTbl 0x7CE3F4`, `gBtlSkillTbl 0x7CE3F8`, `gBtlEnemyTbl 0x7CE410`, `gBtlEnemyAffinityTbl 0x7CE414`, `gDatScriptAttacker/Target/Result/Skill/Mode 0x957190..0x9571A0`. `btlTableLoadAll sub_27DE40` and `tbl_btlTableFiles 0x692D40` are already proposed by `menu_ui.sym` and are not repeated. Queue: `docs/ANALYSIS/queue_battle.txt`.

Imported 2026-10-20 (`import_symbols.py`): every row landed except the D promotion `gBtl 0x7CE3EC` — the master has no item there (an unexplored `.bss` byte) and a tge-pr4 row never changes the layout, so it is `mid_item`: only its `HINT[tge-pr4] gBtl verified` comment is on the master and `symbols/p3fes.sym` has no row for it until the word is typed (an own-analysis D row there would create the item).
