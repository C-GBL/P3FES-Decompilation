#Requires -Version 5.1
<#
.SYNOPSIS
  The merge gate, for the main tree or any agent worktree: build, test suites on both compilers, and the three
  replay gates (dorm, M1, battle) against the main tree's references.
.DESCRIPTION
  Run from anywhere:   powershell -File tools\ours\gate\gate.ps1 [-Tree build\<name>] [-ClangTree build\<name>-clang] [-FastGs]
  The repository is the one this script lives in (a worktree runs its own code); game data, references, the
  memory card and the VU1 dumps come from the main tree (-Main), where the gitignored inputs live.
  Fast configuration (the user's rule since 2026-10-20): MSVC Release, all 114 VU1 programs compiled ahead of time
  (round 3, docs/ANALYSIS/24 §8: ~6 min at -j 2 the first time, then from the unit cache; -HotAot compiles only
  g3_skin 006f8b1c + g3_generic 006b8d4c, the others run on the exact interpreter), every run uncapped (headless runs
  are never paced). Gate runs use --vu1 aot.
  -FastGs: the replay gates rasterise on the GPU (--gs-backend d3d11 --gs-exact: an offscreen D3D11 device in exact
  mode, byte-identical to the software GS; docs/ANALYSIS/25 §12); a device without ROVs/doubles falls back to
  software (the route's line says so). Software stays the default.
  Order: MSVC build (the emitter rewrites only units whose text changed), then the three replay gates start as
  background processes, together with the MSVC ctest; the clang-cl build and its ctest run in the foreground
  meanwhile. -Serial: everything one after the other (the pre-2026-10-20 order). The pair-test counts come from
  ctest's log (p3fes_game_tests runs once per compiler).
  Suites (since 2026-10-20, fourth step): p3fes_game_tests is one ctest entry per test file (tests/game, doctest
  --source-file; P3FES_GAME_TESTS_SHARDED), so ctest -j runs the files in parallel; the counts printed are the sums
  over those entries, and the gate fails unless they cover the binary's own case count (--count) exactly. The
  clang-cl suites build as Release (a second compiler's optimised codegen, like the MSVC tree; preset
  clangcl-x64-release): an existing -ClangTree of another build type is re-configured in place. -ClangDebug: the
  clang-cl Debug tree; -WholeGameTests: p3fes_game_tests as one ctest entry (both the pre-2026-10-20 way).
  -TestJobs: ctest -j (default -Jobs).
  Slice agents (since 2026-10-21): -Slice builds only p3fes, tracediff and p3fes_game_tests, runs only the
  p3fes_game_tests entries and skips clang-cl (even with -ClangTree); the lead's merge gate (no -Slice, -ClangTree
  given) keeps every suite on both compilers. -BuildOnly stops after the MSVC build (a slice's pair-test tree is its
  gate tree: one tree, built once, then incrementally). -NoSuites (slice.ps1 final, since 2026-10-29): no ctest at all --
  the slice's own pair tests already ran on both compilers in its test / clang steps; the full suites run once, in the
  lead's merge gate (the machine is CPU-bound: each full run is ~3 CPU-hours). Shared object cache: configured trees compile the generated
  units, runtime/ and game/ through tools/ours/gate/unit_cache.py with <Main>\build\_unit_cache (a fresh worktree
  takes what any tree compiled from the same text); -NoUnitCache turns it off for the tree.
  A failed configure/emit/MSVC build aborts: no test or gate runs on stale binaries; a failed clang-cl build skips
  the clang-cl suites and fails the gate. A failing suite fails the gate. Every route checks frame.png (SHA-256),
  eeMemory.bin (tracediff, dead stack excluded) and gsMemory.bin (SHA-256 against the reference's).
  Outputs: <Tree>\gate\{dorm,m1,battle}\ (snapshots), <Tree>\gate\*.log and <Tree>.gate.log.
  -StateCheck (machine states, runtime/STATE.md): every route also saves the whole machine at a mid-route vblank
  ($statePoints); a fresh process loads that state and runs on to the route's snapshot point, and its eeMemory.bin,
  gsMemory.bin, frame.png and capture.json must equal the route's own byte for byte. Catches state the save/load
  misses (a new component without state()). The loads start as soon as the states exist.
  Machine states need a dev-only build (-DP3FES_MACHINE_STATES=ON: fixed image base, the saver's /GS cookie adopted;
  runtime/STATE.md): the gate configures its tree that way; -NoMachineStates configures a normal ASLR build (OFF) and
  then -StateCheck / -Segments are refused.
  -Segments (runtime/STATE.md "Reference mode", "Segments"): instead of one from-boot run per route compared with the
  zero-replacement references, the same executable runs each route in --reference-mode (every replaced function as
  its recompiled original) from boot, saving a state and a snapshot at every mark ($segmentMarks); each segment
  [S, E) then runs in hand mode from the reference state at S (segment 0 from boot) to E and must equal the
  reference snapshot at E (frame, eeMemory.bin with the dead stack excluded, gsMemory.bin). A segment therefore tests
  only the hand code running inside it, and the segments of all routes run in parallel (-SegmentJobs) as the
  reference runs pass their marks. The reference runs' end snapshots are also compared with the zero-replacement
  references (reference mode == the norep program). The from-boot routes stay the authoritative merge gate.
#>
param(
    [string]$Tree = 'build\gate',
    [string]$ClangTree = '',          # e.g. build\gate-clang; empty = skip the clang-cl suites
    [string]$Main = 'F:\P3FES-PORT\p3fes-port',
    [switch]$NoEmit,
    [switch]$FullAot,                 # (the default since round 3; kept so old command lines still parse)
    [switch]$HotAot,                  # compile only the two hot VU1 programs (the pre-round-3 fast configuration)
    [switch]$FastGs,                  # replay gates on the GPU (exact mode; byte-identical to the software GS)
    [switch]$Serial,                  # no overlap: builds, suites and the three routes one after the other
    [switch]$NoBuild,                 # skip configure/emit/build and the suites: re-run the replay gates only
    [switch]$ClangDebug,              # the clang-cl suites on a Debug tree (the pre-2026-10-20 way); default Release
    [switch]$WholeGameTests,          # p3fes_game_tests as one ctest entry (the pre-2026-10-20 way), not one per file
    [switch]$StateCheck,              # each route saves a machine state mid-way; a fresh process resumes it and must match
    [switch]$Segments,                # routes in segments from reference-mode states of this build (see above)
    [int]$SegmentJobs = 8,            # -Segments: game processes at once (reference runs + segments)
    [switch]$NoMachineStates,         # configure a normal ASLR build (P3FES_MACHINE_STATES=OFF): no states, no -Segments
    [switch]$Slice,                   # a slice agent's gate: MSVC only (no clang-cl, even with -ClangTree), builds only
                                      # p3fes, tracediff and p3fes_game_tests, runs only the p3fes_game_tests entries;
                                      # the lead's merge gate (no -Slice, with -ClangTree) runs every suite on both compilers
    [switch]$NoSuites,                # skip the ctest suites: a slice's `final` already ran its own pair tests on both
                                      # compilers; the lead's merge gate runs every suite (since 2026-10-29, user-approved)
    [switch]$BuildOnly,               # stop after configure/emit/MSVC build: the tree a slice runs its pair tests from
    [switch]$NoUnitCache,             # compile the generated units here instead of taking them from <Main>\build\_unit_cache
    [string]$Routes = '',             # comma-separated route names to run (dorm,m1,battle,fusion,shop,climb); default: all,
                                      # except that -Slice skips the climb (~20 min) -- the lead's merge gate runs it
    [int]$Jobs = 4,
    [int]$TestJobs = 0,               # ctest -j; 0 = -Jobs
    [string]$Repo = ''                # the tree to build and gate; default: the repository this script lives in.
                                      # Agents: run the MAIN tree's copy with -Repo <your worktree> (fixes reach you at once)
)
$t0 = [Diagnostics.Stopwatch]::StartNew()
if (-not $Repo) { $Repo = (Resolve-Path (Join-Path $PSScriptRoot '..\..\..')).Path } else { $Repo = (Resolve-Path $Repo).Path }
Set-Location $Repo
. (Join-Path $Main 'tools\env.ps1') *> $null
$ErrorActionPreference = 'Continue'
$elf = Join-Path $Main 'extracted\disc\SLUS_216.21'
$iso = Join-Path $Main 'input\persona3fes.iso'
$ref = Join-Path $Main 'extracted\_ours'
$b = Join-Path $Tree 'bin'
$out = Join-Path $Tree 'gate'
$log = Join-Path $Repo "$Tree.gate.log"
New-Item -ItemType Directory -Force (Split-Path $log) | Out-Null
New-Item -ItemType Directory -Force $out | Out-Null
Set-Content $log '' -Encoding ascii
$failed = $false

function Secs($sw) { '{0,6:N1} s' -f $sw.Elapsed.TotalSeconds }
function Run($what, $cmd, [switch]$Fatal) {
    $sw = [Diagnostics.Stopwatch]::StartNew()
    cmd /c "$cmd >> `"$log`" 2>&1"; $rc = $LASTEXITCODE
    if ($rc -ne 0 -and $what -like 'build*') { Start-Sleep 5; cmd /c "$cmd >> `"$log`" 2>&1"; $rc = $LASTEXITCODE; $what += ' (retry)' }
    $script:lastRc = $rc
    "{0,-14} exit {1}  {2}" -f $what, $rc, (Secs $sw)
    if ($rc -ne 0) { $script:failed = $true; if ($Fatal) { 'ABORT: no tests or gates on stale binaries'; exit 1 } }
    return
}
# A background process: `cmd /c <line> > <file> 2>&1` (start time, exit code and end time stay on the object).
function Start-Bg($line, $file) {
    $psi = New-Object Diagnostics.ProcessStartInfo
    $psi.FileName = $env:ComSpec
    $psi.Arguments = "/c `"$line > `"$file`" 2>&1`""
    $psi.UseShellExecute = $false
    $psi.WorkingDirectory = $Repo
    [Diagnostics.Process]::Start($psi)
}
# A cache entry of a configured tree ('' when the tree or the entry is absent).
function Get-CacheVar($dir, $name) {
    $c = Join-Path $dir 'CMakeCache.txt'
    if (-not (Test-Path $c)) { return '' }
    $m = Select-String -Path $c -Pattern ('^{0}:[A-Z]+=(.*)$' -f [regex]::Escape($name)) | Select-Object -First 1
    if ($m) { $m.Matches[0].Groups[1].Value } else { '' }
}
# Re-configure an existing tree whose cache holds other values than the gate's (a changed build type rebuilds it).
function Sync-Cache($what, $dir, [hashtable]$vars) {
    $d = @(foreach ($k in $vars.Keys) { if ((Get-CacheVar $dir $k) -ne $vars[$k]) { "-D$k=$($vars[$k])" } })
    if ($d.Count) { Run $what ("cmake -B $dir " + ($d -join ' ')) }
}
# p3fes_game_tests: one ctest entry per test file unless -WholeGameTests (only where the repo has the option).
$shardVars = @{}
if (Select-String -Quiet -Path (Join-Path $Repo 'tests\game\CMakeLists.txt') -Pattern 'P3FES_GAME_TESTS_SHARDED') {
    $shardVars['P3FES_GAME_TESTS_SHARDED'] = $(if ($WholeGameTests) { 'OFF' } else { 'ON' })
}
# The shared object cache of the generated units (tools/ours/gate/unit_cache.py: a fresh worktree takes the ~75 program
# units and the tests' generated buckets from any tree that compiled the same text), unless -NoUnitCache; only where
# the repo has it. (Kept in the same table: both trees are configured and re-synced with these entries.)
if (Test-Path (Join-Path $Repo 'tools\ours\gate\unit_cache.cmake')) {
    $shardVars['P3FES_UNIT_CACHE'] = $(if ($NoUnitCache) { '' } else { (Join-Path $Main 'build\_unit_cache').Replace('\', '/') })
}
# Machine states (dev-only build option, runtime/STATE.md): ON unless -NoMachineStates; only where the repo has it.
if (Select-String -Quiet -Path (Join-Path $Repo 'runtime\app\CMakeLists.txt') -Pattern 'P3FES_MACHINE_STATES') {
    $shardVars['P3FES_MACHINE_STATES'] = $(if ($NoMachineStates) { 'OFF' } else { 'ON' })
}
if ($NoMachineStates -and ($StateCheck -or $Segments)) { 'ABORT: -StateCheck / -Segments need machine states (drop -NoMachineStates)'; exit 1 }
$shardDefs = ($shardVars.Keys | ForEach-Object { "-D$_=$($shardVars[$_])" }) -join ' '
if ($TestJobs -le 0) { $TestJobs = $Jobs }
# ctest of one tree as a background process; Report-Suites prints its summary, failures and the pair-test counts.
$ctestFilter = if ($Slice) { ' -R p3fes_game_tests' } else { '' }   # -Slice: the pair tests only
function Start-Suites($dir) { Start-Bg "ctest --test-dir $dir -j $TestJobs$ctestFilter" (Join-Path $out ("ctest-{0}.log" -f (Split-Path $dir -Leaf))) }
function Report-Suites($what, $dir, $p) {
    $p.WaitForExit()
    $f = Join-Path $out ("ctest-{0}.log" -f (Split-Path $dir -Leaf))
    $o = Get-Content $f
    Add-Content $log "---- $what ----" -Encoding ascii; $o | Add-Content $log -Encoding ascii
    "{0,-14} exit {1}  {2,6:N1} s  {3}" -f $what, $p.ExitCode, ($p.ExitTime - $p.StartTime).TotalSeconds, (($o | Select-String 'tests passed') -join '')
    $o | Select-String -CaseSensitive '\*\*\*(?!Skipped)|tests FAILED' | ForEach-Object { "               $_" }   # (emit_subset skips by design)
    if ($p.ExitCode -ne 0) { $script:failed = $true }
    # the slowest entry bounds the suite phase
    $slow = $o | Select-String 'Test +#\d+: (\S+) \.+ +Passed +([\d.]+) sec' | ForEach-Object { [pscustomobject]@{ n = $_.Matches[0].Groups[1].Value; s = [double]$_.Matches[0].Groups[2].Value } } |
        Sort-Object s -Descending | Select-Object -First 3
    if ($slow) { '               slowest: ' + (($slow | ForEach-Object { '{0} {1:N1} s' -f $_.n, $_.s }) -join ', ') }
    # p3fes_game_tests ran inside ctest (one entry, or one per test file): the doctest summaries are in ctest's
    # LastTest.log; the counts are their sums
    $lt = Join-Path $dir 'Testing\Temporary\LastTest.log'
    if (Test-Path $lt) {
        $cur = ''; $k = 0; $c = [int64[]](0, 0, 0); $a = [int64[]](0, 0, 0)
        foreach ($line in [IO.File]::ReadLines((Resolve-Path $lt).Path)) {
            if ($line -match '^\d+/\d+ Testing: (\S+)\s*$') { $cur = $Matches[1]; continue }
            if ($cur -notmatch '^p3fes_game_tests(\.|$)') { continue }
            if ($line -match '^\[doctest\] test cases:\s*(\d+)\s*\|\s*(\d+) passed\s*\|\s*(\d+) failed') { $k++; for ($j = 0; $j -lt 3; $j++) { $c[$j] += [int64]$Matches[$j + 1] } }
            elseif ($line -match '^\[doctest\] assertions:\s*(\d+)\s*\|\s*(\d+) passed\s*\|\s*(\d+) failed') { for ($j = 0; $j -lt 3; $j++) { $a[$j] += [int64]$Matches[$j + 1] } }
        }
        if ($k) {
            "pair tests     [doctest] test cases: {0} | {1} passed | {2} failed  ({3} ctest {4})" -f $c[0], $c[1], $c[2], $k, $(if ($k -eq 1) { 'entry' } else { 'entries' })
            "pair tests     [doctest] assertions: {0} | {1} passed | {2} failed" -f $a[0], $a[1], $a[2]
            # every case ran exactly once: the entries' cases add up to the binary's own count
            $exe = Join-Path $dir 'bin\p3fes_game_tests.exe'
            $cnt = if (Test-Path $exe) { & $exe --count 2>$null | Select-String 'unskipped test cases passing the current filters: (\d+)' | Select-Object -First 1 } else { $null }
            if (-not $cnt) { 'pair tests     cannot read the case count of p3fes_game_tests (--count)'; $script:failed = $true }
            elseif ([int64]$cnt.Matches[0].Groups[1].Value -ne $c[0]) {
                'pair tests     MISMATCH: the ctest entries ran {0} cases, the binary has {1}' -f $c[0], $cnt.Matches[0].Groups[1].Value; $script:failed = $true
            }
        } else { 'pair tests     no p3fes_game_tests summary in LastTest.log'; $script:failed = $true }
    }
}

$bgSuites = @()
if (-not $NoBuild) {
    $aotList = if ($HotAot) { '006f8b1c,006b8d4c' } else { '' }
    $aotOnly = "-DP3FES_VU1_AOT_ONLY=$aotList"
    if (-not (Test-Path (Join-Path $Tree 'CMakeCache.txt'))) {
        if (-not (Test-Path 'recomp\generated\dispatch.cpp')) {   # configuring needs emitted code: emit with a built emitter first
            # the newest emitter: old trees hold emitters from before --replace existed
            $em = Get-ChildItem (Join-Path $Main 'build\*\bin\p3fes_recomp.exe') -ErrorAction SilentlyContinue | Sort-Object LastWriteTime -Descending | Select-Object -First 1
            if (-not $em) { 'ABORT: no p3fes_recomp.exe to bootstrap emission'; exit 1 }
            Run 'emit (boot)' "$($em.FullName) --elf $elf --functions symbols\functions.json --chunks symbols\function_chunks.txt --jumptables symbols\jumptables.json --out recomp\generated --replace game\replaced.txt" -Fatal
        }
        Run 'configure' "cmake --preset msvc-x64-release -B $Tree -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt -DP3FES_RT_EXEC_ELF=$elf -DP3FES_VU1_AOT=ON -DP3FES_VU1_AOT_DUMPS=$Main\ida\logs\vu1 $aotOnly $shardDefs" -Fatal
    } else { $script:lastRc = 0; Sync-Cache 'reconfigure' $Tree ($shardVars + @{ P3FES_VU1_AOT_ONLY = $aotList }); if ($lastRc) { 'ABORT: re-configure failed'; exit 1 } }
    Run 'build recomp' "cmake --build $Tree --target p3fes_recomp -j $Jobs" -Fatal
    # the emitter rewrites only units whose text changed: re-emitting an unchanged program costs no recompilation
    if (-not $NoEmit) { Run 'emit' "$b\p3fes_recomp.exe --elf $elf --functions symbols\functions.json --chunks symbols\function_chunks.txt --jumptables symbols\jumptables.json --out recomp\generated --replace game\replaced.txt" -Fatal }
    # -Slice: only what the slice gate runs (the game, the snapshot diff, the pair tests); the runtime suites, tools
    # and the stubs link check are built and run by the lead's merge gate
    $targets = if ($Slice) { ' --target p3fes tracediff p3fes_game_tests' } else { '' }
    Run 'build msvc' "cmake --build $Tree -j $Jobs$targets" -Fatal
}
if ($BuildOnly) { 'total          {0}' -f (Secs $t0); if ($failed) { 'BUILD: FAILED'; exit 1 } else { 'BUILD: OK (-BuildOnly: no suites, no replay gates)'; exit 0 } }
if ($Slice -and $ClangTree) { "clang-cl       skipped (-Slice: the lead's merge gate builds and tests clang-cl)"; $ClangTree = '' }

# ---- the replay gates (background unless -Serial) -----------------------------------------------------------------
$gs = if ($FastGs) { '--gs-backend d3d11 --gs-exact' } else { '' }
# (not $routes: PowerShell names are case-insensitive, and the [string] -Routes parameter would turn the list into
# one string -- every route then failed to start)
$routeSet = @(
    @{ name = 'dorm';   args = "--memcard new --replay-input $Main\config\inputs\to_dorm.txt --snapshot-at vblank:4900"; ref = 'dorm_replay_4900' },
    @{ name = 'm1';     args = '--snapshot-at sky:11'; ref = 'v_m1' },
    @{ name = 'battle'; args = "--memcard $ref\cards\tartarus.ps2 --replay-input $Main\config\inputs\to_battle.txt --snapshot-at vblank:6150"; ref = 'battle_ref_6150' },
    # the user's Velvet Room recording (2026-10-21): enters the Velvet Room and fuses; reference from a zero-replacement
    # build at 57948d7 (F:\P3FES-PORT\norep, build\norep2)
    @{ name = 'fusion'; args = "--memcard $ref\cards\fusion.ps2 --replay-input $Main\config\inputs\fusion.txt --snapshot-at vblank:6300"; ref = 'fusion_ref_6300' },
    # the user's shop recording (2026-10-21): the pharmacy's item menu and the shopkeeper; it caught the missing
    # spills of RFMAI_ToUpperStr and frFontCreateGlyphNode
    @{ name = 'shop';   args = "--memcard $ref\cards\shop_buy.ps2 --replay-input $Main\config\inputs\shop.txt --snapshot-at vblank:4100"; ref = 'shop_ref_4100' },
    # the user's full Tartarus climb (2026-10-21): floors, fights and the boss, ~39,800 vblanks (~15 min headless, the
    # longest route); it caught datSetFlag's missing frame. A transient 318-byte heap-frame difference at vblank 17000
    # (gone by the end) is still open -- the faithfulness audit is on it.
    @{ name = 'climb';  args = "--memcard $ref\cards\full_battle.ps2 --replay-input $Main\config\inputs\full_battle.txt --snapshot-at vblank:39820"; ref = 'climb_ref_39820' }
)
$wanted = if ($Routes) { $Routes.Split(',') | ForEach-Object { $_.Trim() } } elseif ($Slice) { 'dorm', 'm1', 'battle', 'fusion', 'shop' } else { $null }
if ($wanted) {
    $routeSet = @($routeSet | Where-Object { $wanted -contains $_.name })
    'routes         {0}{1}' -f ($routeSet.name -join ', '), $(if (-not $Routes -and $Slice) { ' (-Slice: the climb runs in the merge gate)' } else { '' })
}
# the memory card opens copy-on-write into .\extracted\_ours\memcards (relative to this repo): start from the pristine card
foreach ($c in 'tartarus.ps2', 'fusion.ps2', 'shop_buy.ps2', 'full_battle.ps2') { Remove-Item (Join-Path $Repo "extracted\_ours\memcards\$c") -ErrorAction SilentlyContinue }
# -StateCheck: the vblank at which each route saves the machine (runtime/STATE.md); a route not listed is not checked.
# (The save goes before the route's arguments: they end with --snapshot-at K:N, whose directory Start-Route appends.)
$statePoints = @{ dorm = 3500; m1 = 300; battle = 4700; fusion = 4500; shop = 3000; climb = 20000 }
function Start-Route($r) {
    $r.dir = Join-Path $out $r.name
    Remove-Item -Recurse -Force $r.dir -ErrorAction SilentlyContinue
    $r.log = Join-Path $out "$($r.name).log"
    $save = ''
    if ($StateCheck -and $statePoints.ContainsKey($r.name)) {
        $r.state = Join-Path $out "$($r.name).p3st"
        Remove-Item $r.state -ErrorAction SilentlyContinue
        $save = "--save-state-at vblank:$($statePoints[$r.name]) $($r.state)"
    }
    $r.proc = Start-Bg "$b\p3fes.exe --elf $elf --iso $iso --headless --quiet --vu1 aot $gs $save $($r.args) $($r.dir)" $r.log
}
# The resumed runs: the route's arguments with a private copy of its memory card (copy-on-write names never collide).
function Start-StateLoads {
    if (-not $StateCheck) { return }
    foreach ($r in $routeSet) {
        if (-not $r.state -or $r.load -or -not (Test-Path $r.state)) { continue }
        $a = $r.args
        if ($a -match '--memcard (\S+\\cards\\)(\S+)') {
            $mine = "state_$($Matches[2])"
            Copy-Item (Join-Path $Matches[1] $Matches[2]) (Join-Path $Repo "extracted\_ours\cards\$mine") -Force
            Remove-Item (Join-Path $Repo "extracted\_ours\memcards\$mine") -ErrorAction SilentlyContinue
            $a = $a.Replace("$($Matches[1])$($Matches[2])", "extracted\_ours\cards\$mine")
        }
        $r.rtdir = Join-Path $out "$($r.name)-state"
        Remove-Item -Recurse -Force $r.rtdir -ErrorAction SilentlyContinue
        $r.rtlog = Join-Path $out "$($r.name)-state.log"
        $r.load = Start-Bg "$b\p3fes.exe --elf $elf --iso $iso --headless --quiet --vu1 aot $gs --load-state $($r.state) $a $($r.rtdir)" $r.rtlog
    }
}
if ($StateCheck -or $Segments) { New-Item -ItemType Directory -Force (Join-Path $Repo 'extracted\_ours\cards') | Out-Null }
# ---- -Segments ---------------------------------------------------------------------------------------------------
# Segment starts per route (vblanks); a route with none is one segment (hand mode from boot vs reference mode from boot).
$segmentMarks = @{ dorm = @(2500); m1 = @(); battle = @(2500, 4700); fusion = @(2500, 4500); shop = @(2000); climb = @(6500, 13000, 19500, 26000, 33000) }
# A private copy of the route's memory card for one process (copy-on-write names never collide).
function Private-Card($a, $tag) {
    if ($a -match '--memcard (\S+\\cards\\)(\S+)') {
        $mine = "${tag}_$($Matches[2])"
        Copy-Item (Join-Path $Matches[1] $Matches[2]) (Join-Path $Repo "extracted\_ours\cards\$mine") -Force
        Remove-Item (Join-Path $Repo "extracted\_ours\memcards\$mine") -ErrorAction SilentlyContinue
        return $a.Replace("$($Matches[1])$($Matches[2])", "extracted\_ours\cards\$mine")
    }
    return $a
}
function Run-Segments {
    $exe = "$b\p3fes.exe --elf $elf --iso $iso --headless --quiet --vu1 aot $gs"
    $jobs = @()      # every game process: @{ tag; proc; log }
    $segs = @()      # @{ route; from; to; spec; dir; refdir; state; job }
    foreach ($r in $routeSet) {
        $marks = @($segmentMarks[$r.name])
        $sd = Join-Path $out "seg-$($r.name)"
        Remove-Item -Recurse -Force $sd -ErrorAction SilentlyContinue
        New-Item -ItemType Directory -Force $sd | Out-Null
        # the route's own end point: its arguments end with --snapshot-at K:N
        $endSpec = if ($r.args -match '--snapshot-at (\S+)$') { $Matches[1] } else { '' }
        $base = $r.args -replace '\s*--snapshot-at \S+$', ''
        $refArgs = ($marks | ForEach-Object { "--save-state-at vblank:$_ $sd\state_$_.p3st --snapshot-at vblank:$_ $sd\ref_$_" }) -join ' '
        $r.refend = Join-Path $sd 'ref_end'
        $plog = Join-Path $sd 'reference.log'
        $jobs += @{ tag = "$($r.name) reference"; log = $plog; proc = (Start-Bg "$exe --reference-mode $refArgs $(Private-Card $base "segref_$($r.name)") --snapshot-at $endSpec $($r.refend)" $plog); route = $r }
        $starts = @(0) + $marks
        for ($i = 0; $i -lt $starts.Count; $i++) {
            $last = $i + 1 -ge $starts.Count
            $segs += @{ route = $r; from = $starts[$i]; to = $(if ($last) { $endSpec } else { "vblank:$($starts[$i + 1])" });
                        dir = (Join-Path $sd "seg_$($starts[$i])"); refdir = $(if ($last) { $r.refend } else { Join-Path $sd "ref_$($starts[$i + 1])" });
                        state = $(if ($i -eq 0) { '' } else { Join-Path $sd "state_$($starts[$i]).p3st" }); base = $base; job = $null }
        }
    }
    # launch segments as their states appear (segment 0 at once), at most -SegmentJobs game processes at a time
    while (@($segs | Where-Object { -not $_.job }).Count) {
        foreach ($s in $segs) {
            if ($s.job) { continue }
            if (@($jobs | Where-Object { -not $_.proc.HasExited }).Count -ge $SegmentJobs) { break }
            $refJob = $jobs | Where-Object { $_.route -eq $s.route } | Select-Object -First 1
            if ($s.state -and -not (Test-Path $s.state)) {
                if ($refJob.proc.HasExited) { $s.job = @{ tag = "$($s.route.name) $($s.from)"; proc = $null; log = '' } }   # never saved
                continue
            }
            Remove-Item -Recurse -Force $s.dir -ErrorAction SilentlyContinue
            $plog = "$($s.dir).log"
            $load = if ($s.state) { "--load-state $($s.state)" } else { '' }
            $s.job = @{ tag = "$($s.route.name) $($s.from)"; log = $plog; proc = (Start-Bg "$exe $load $(Private-Card $s.base "seg$($s.from)_$($s.route.name)") --snapshot-at $($s.to) $($s.dir)" $plog) }
            $jobs += $s.job
        }
        Start-Sleep -Milliseconds 500
    }
    foreach ($j in $jobs) { if ($j.proc) { $j.proc.WaitForExit() } }
    $script:gatesWall = $swGates.Elapsed.TotalSeconds
    foreach ($r in $routeSet) {
        $rj = $jobs | Where-Object { $_.route -eq $r } | Select-Object -First 1
        Add-Content $log "---- $($r.name) reference ----" -Encoding ascii; Get-Content $rj.log | Add-Content $log -Encoding ascii
        $refDir = Join-Path $ref $r.ref
        $d = cmd /c "$b\tracediff.exe snapshot $refDir\eeMemory.bin $($r.refend)\eeMemory.bin --dead-stack $($r.refend)\capture.json 2>&1" | Select-String 'differing bytes'
        $same = (Test-Path "$($r.refend)\frame.png") -and (Get-FileHash "$($r.refend)\frame.png").Hash -eq (Get-FileHash "$refDir\frame.png").Hash -and
                (Get-FileHash "$($r.refend)\gsMemory.bin").Hash -eq (Get-FileHash "$refDir\gsMemory.bin").Hash
        "{0,-14} exit {1}  {2,6:N1} s  reference mode vs the zero-replacement reference: frame+gsMemory {3}, eeMemory {4}" -f "$($r.name) ref", $rj.proc.ExitCode,
            ($rj.proc.ExitTime - $rj.proc.StartTime).TotalSeconds, $(if ($same) { 'identical' } else { 'DIFFER' }), "$d".Trim()
        if ($rj.proc.ExitCode -ne 0 -or -not $same -or "$d" -notmatch 'differing bytes: 0 ') { $script:failed = $true }
        foreach ($s in @($segs | Where-Object { $_.route -eq $r })) {
            $name = '{0} {1}-{2}' -f $r.name, $s.from, ($s.to -replace '^vblank:', '')
            if (-not $s.job.proc) { "{0,-22} not run: no reference state at {1}" -f $name, $s.from; $script:failed = $true; continue }
            Add-Content $log "---- segment $name ----" -Encoding ascii; Get-Content $s.job.log | Add-Content $log -Encoding ascii
            $f1 = Join-Path $s.dir 'frame.png'; $f2 = Join-Path $s.refdir 'frame.png'
            $fr = (Test-Path $f1) -and (Test-Path $f2) -and (Get-FileHash $f1).Hash -eq (Get-FileHash $f2).Hash
            $gm = (Test-Path "$($s.dir)\gsMemory.bin") -and (Get-FileHash "$($s.dir)\gsMemory.bin").Hash -eq (Get-FileHash "$($s.refdir)\gsMemory.bin").Hash
            $td = cmd /c "$b\tracediff.exe snapshot $($s.refdir)\eeMemory.bin $($s.dir)\eeMemory.bin --dead-stack $($s.dir)\capture.json 2>&1" | Select-String 'differing bytes'
            $ok = $s.job.proc.ExitCode -eq 0 -and $fr -and $gm -and "$td" -match 'differing bytes: 0 '
            "{0,-22} exit {1}  {2,6:N1} s  frame {3}, gsMemory {4}, eeMemory {5}" -f $name, $s.job.proc.ExitCode, ($s.job.proc.ExitTime - $s.job.proc.StartTime).TotalSeconds,
                $(if ($fr) { 'same' } else { 'DIFFERS' }), $(if ($gm) { 'same' } else { 'DIFFERS' }), "$td".Trim()
            if (-not $ok) { $script:failed = $true }
        }
        Get-ChildItem (Join-Path $out "seg-$($r.name)") -Filter 'state_*.p3st' -ErrorAction SilentlyContinue | Remove-Item -ErrorAction SilentlyContinue
    }
}
'replay gates   {0}, GS {1} (at {2})' -f $(if ($Serial) { 'serial' } else { 'parallel, overlapping the suites' }), $(if ($FastGs) { 'd3d11 exact (offscreen)' } else { 'software' }), (Secs $t0).Trim()
$swGates = [Diagnostics.Stopwatch]::StartNew()
if ($Segments) {
    # the reference runs and the segments, then the suites (no overlap: segments already use -SegmentJobs processes)
    Run-Segments
    if (-not $NoBuild) {
        if ($NoSuites) { 'ctest          skipped (-NoSuites)' } else {
            $msvcSuites = Start-Suites $Tree
            if ($ClangTree) { 'clang-cl       not run with -Segments (the merge gate runs it)' }
            Report-Suites 'ctest msvc' $Tree $msvcSuites
        }
    }
    'replay gates   {0,6:N1} s wall (-Segments: reference runs + segments)' -f $gatesWall
    'total          {0}' -f (Secs $t0)
    if ($failed) { 'GATE: FAILED'; exit 1 } else { 'GATE: PASSED' }
    exit 0
}
if (-not $Serial) {
    # A route process is single-threaded (+ the GPU render thread with -FastGs), working set ~100-200 MB.
    foreach ($r in $routeSet) { Start-Route $r }
    if (-not $NoBuild -and -not $NoSuites) { $msvcSuites = Start-Suites $Tree }
}
if (-not $NoBuild) {
    if ($Serial -and -not $NoSuites) { $msvcSuites = Start-Suites $Tree; $msvcSuites.WaitForExit() }
    if ($ClangTree) {
        # Release unless -ClangDebug (the second compiler's optimised codegen); the preset when this repo has it
        $clangType = if ($ClangDebug) { 'Debug' } else { 'Release' }
        $clangPreset = if (-not $ClangDebug -and (Select-String -Quiet -Path (Join-Path $Repo 'CMakePresets.json') -Pattern '"clangcl-x64-release"')) { 'clangcl-x64-release' } else { 'clangcl-x64-debug' }
        $script:lastRc = 0
        if (-not (Test-Path (Join-Path $ClangTree 'CMakeCache.txt'))) { Run 'configure clang' "cmake --preset $clangPreset -B $ClangTree -DP3FES_RT_EXEC_ELF=$elf -DCMAKE_BUILD_TYPE=$clangType $shardDefs" }
        else {
            $was = Get-CacheVar $ClangTree 'CMAKE_BUILD_TYPE'
            if ($was -ne $clangType) { "clang-cl tree  $ClangTree was $was`: re-configured as $clangType (a full rebuild)" }
            Sync-Cache 'reconfig clang' $ClangTree (@{ CMAKE_BUILD_TYPE = $clangType } + $shardVars)
        }
        $clangOk = $lastRc -eq 0
        if ($clangOk) { Run 'build clang' "cmake --build $ClangTree -j $Jobs"; $clangOk = $lastRc -eq 0 }
        if ($clangOk) { $clangSuites = Start-Suites $ClangTree; $clangSuites.WaitForExit() } else { 'clang-cl build failed: its suites were not run' }
    }
    Start-StateLoads
    if ($NoSuites) { "ctest          skipped (-NoSuites: the slice's own pair tests ran in its test / clang steps; the merge gate runs every suite)" }
    else { Report-Suites 'ctest msvc' $Tree $msvcSuites }
    if ($ClangTree -and $clangSuites) { Report-Suites 'ctest clang' $ClangTree $clangSuites }
}
if ($Serial) { $swGates.Restart(); foreach ($r in $routeSet) { Start-Route $r; $r.proc.WaitForExit() } }
foreach ($r in $routeSet) { Start-StateLoads; $r.proc.WaitForExit() }
Start-StateLoads
foreach ($r in $routeSet) { if ($r.load) { $r.load.WaitForExit() } }
$gatesWall = $swGates.Elapsed.TotalSeconds
foreach ($r in $routeSet) {
    $name = $r.name; $dir = $r.dir; $refDir = Join-Path $ref $r.ref
    Add-Content $log "---- $name ----" -Encoding ascii; Get-Content $r.log | Add-Content $log -Encoding ascii
    $rc = $r.proc.ExitCode
    $gsLine = (Get-Content $r.log | Select-String 'p3fes: gs-backend: (d3d11 headless|software)' | Select-Object -First 1)
    $gsWhat = if ($gsLine -match 'd3d11 headless') { 'd3d11' } elseif ($gsLine) { "$gsLine".Replace('p3fes: gs-backend: ', '') } else { 'software' }
    "{0,-14} exit {1}  {2,6:N1} s  GS {3}" -f $name, $rc, ($r.proc.ExitTime - $r.proc.StartTime).TotalSeconds, $gsWhat
    if ($rc -ne 0) { $failed = $true }
    $frame = Join-Path $dir 'frame.png'
    if (Test-Path $frame) { '{0,-14} frame {1}' -f $name, (Get-FileHash $frame).Hash } else { "${name}: no frame.png"; $failed = $true; continue }
    $d = cmd /c "$b\tracediff.exe snapshot $refDir\eeMemory.bin $dir\eeMemory.bin --dead-stack $dir\capture.json 2>&1" | Select-String 'differing bytes'
    "{0,-14} {1}" -f '', $d
    if ("$d" -notmatch 'differing bytes: 0 ') { $failed = $true }
    $g = Join-Path $dir 'gsMemory.bin'
    $gsSame = (Test-Path $g) -and ((Get-FileHash $g).Hash -eq (Get-FileHash (Join-Path $refDir 'gsMemory.bin')).Hash)
    "{0,-14} gsMemory {1}" -f '', $(if ($gsSame) { 'identical' } else { 'DIFFERS' })
    if (-not $gsSame) { $failed = $true }
    if ($StateCheck -and $r.state) {
        $sline = (Get-Content $r.log | Select-String '^p3fes: state vblank:' | Select-Object -First 1)
        if (-not $r.load) { "{0,-14} no state saved: {1}" -f "$name-state", $sline; $failed = $true; continue }
        Add-Content $log "---- $name-state ----" -Encoding ascii; Get-Content $r.rtlog | Add-Content $log -Encoding ascii
        $res = foreach ($f in 'eeMemory.bin', 'gsMemory.bin', 'frame.png', 'capture.json') {
            $x = Join-Path $dir $f; $y = Join-Path $r.rtdir $f
            if ((Test-Path $x) -and (Test-Path $y) -and (Get-FileHash $x).Hash -eq (Get-FileHash $y).Hash) { "$f same" } else { $failed = $true; "$f DIFFERS" }
        }
        $size = if ("$sline" -match '\(([\d.]+ MiB), ([\d.]+ s);') { "$($Matches[1]), saved in $($Matches[2])" } else { '?' }
        $ld = (Get-Content $r.rtlog | Select-String 'loaded in ([\d.]+ s)' | Select-Object -First 1)
        "{0,-14} exit {1}  {2,6:N1} s  from vblank {3} ({4}; loaded in {5})" -f "$name-state", $r.load.ExitCode,
            ($r.load.ExitTime - $r.load.StartTime).TotalSeconds, $statePoints[$name], $size, $(if ($ld) { $ld.Matches[0].Groups[1].Value } else { '?' })
        if ($r.load.ExitCode -ne 0) { $failed = $true }
        "{0,-14} vs the route: {1}" -f '', ($res -join ', ')
        Remove-Item $r.state -ErrorAction SilentlyContinue
    }
}
'replay gates   {0,6:N1} s wall{1}' -f $gatesWall, $(if ($Serial) { '' } else { ' (from their start, incl. the overlapped suites)' })
'expected frames: dorm EE0EB5DA4042B042..., m1 E3A93615056A12B6..., battle CFAA5A615C721AF7..., fusion 9B5B5374654299DB..., shop 1165B3E0312F684F..., climb F3440652970E0161...'
'total          {0}' -f (Secs $t0)
if ($failed) { 'GATE: FAILED'; exit 1 } else { 'GATE: PASSED' }
