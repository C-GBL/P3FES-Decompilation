<#
slice.ps1 -- the quiet Phase 5 slice pipeline (docs/PHASE5_QUICK.md). Run it from your worktree:

  powershell -File tools\ours\phase5\slice.ps1 <cmd> -Slice <slice> [-Jobs 3] [-Force] [-List <file>] [-Tests <glob>]

  gen     p3fes_handgen for the packet's gen list -> the .cpp / .h / test skeleton, then wire.py appends the rows
          and files to replaced.txt and the CMake lists (refuses to overwrite an existing file without -Force)
  pseudo  IDA pseudocode + handgen bodies of the slice list -> <scratch>\<slice>.pseudo.c (read by line ranges)
  build   gate.ps1 -Slice -BuildOnly (configure, emit with --replace, MSVC build of p3fes / tracediff / tests)
  test    the slice's pair tests on that tree (MSVC)
  clang   build p3fes_game_tests with clang-cl (build\<slice>-clang) and run the slice's pair tests
  audit   the faithfulness audit of the slice's functions (96 seeds + the packet's snapshots)
  step    build + test + audit (stops at the first failure)
  sync    merge main into the worktree, keeping the uncommitted work (shared lists re-applied as unions)
  final   sync, build, test, clang, then the gate (-Slice -NoSuites -FastGs, all six routes; the full suites run in the merge gate)
  report  the counts block for the slice report

Every command prints at most ~12 lines (verdict, counts, failing names + first error) and keeps the full log in
<worktree>\build\slice-logs\<cmd>.log. Exit code 0 = pass. The packet: F:\P3FES-PORT\lead\packets\<slice>\packet.json.
#>
param(
    [Parameter(Position = 0, Mandatory = $true)]
    [ValidateSet('gen', 'pseudo', 'build', 'test', 'clang', 'audit', 'step', 'sync', 'final', 'report')][string]$Cmd,
    [string]$Slice = $env:P3FES_SLICE,
    [string]$Repo = '',
    [string]$Packet = '',
    [string]$List = '',           # a list file instead of the packet's slice list (pseudo / audit)
    [string]$Tests = '',          # a doctest -sf glob instead of the packet's (test / clang)
    [string]$Scratch = '',
    [int]$Jobs = 3,
    [switch]$Force
)
$ErrorActionPreference = 'Continue'
$Main = 'F:\P3FES-PORT\p3fes-port'
$elf = Join-Path $Main 'extracted\disc\SLUS_216.21'
$py = Join-Path $env:LOCALAPPDATA 'Programs\Python\Python314\python.exe'
$here = $PSScriptRoot
if (-not $Slice) { 'slice.ps1: give -Slice <name> (or set $env:P3FES_SLICE)'; exit 2 }
if (-not $Repo) { $Repo = (Get-Location).Path }
$Repo = (Resolve-Path $Repo).Path
if (-not (Test-Path (Join-Path $Repo '.git'))) { "slice.ps1: $Repo is not a worktree root (run from your worktree)"; exit 2 }
if (-not $Packet) { $Packet = Join-Path 'F:\P3FES-PORT\lead\packets' $Slice }
$pjPath = Join-Path $Packet 'packet.json'
if (-not (Test-Path $pjPath)) { "slice.ps1: no packet $pjPath (make_packet.py $Slice ...)"; exit 2 }
$pj = Get-Content $pjPath -Raw | ConvertFrom-Json
if (-not $Scratch) { $Scratch = Join-Path 'C:\Users\ADMINI~1\AppData\Local\Temp\claude\f--P3FES-PORT-p3fes-port\6dd115e6-e1c6-47fc-8d55-5460595faf8c\scratchpad' $Slice }
$logs = Join-Path $Repo 'build\slice-logs'
New-Item -ItemType Directory -Force $logs, $Scratch | Out-Null
$tree = "build\$Slice-gate"
$clangTree = "build\$Slice-clang"
$list = if ($List) { (Resolve-Path $List).Path } else { $pj.list }
$testGlob = if ($Tests) { $Tests } else { $pj.test_glob }
Set-Location $Repo

# cmd /c <line> > log 2>&1 (appending with -Append); returns the exit code
function Exec([string]$line, [string]$log, [switch]$Append, [int]$TimeoutSec = 7200) {
    # capped (2026-10-30): a hung test or build is killed with its process tree after $TimeoutSec and returns 124,
    # instead of holding the agent for hours
    $op = if ($Append) { '>>' } else { '>' }
    $psi = New-Object Diagnostics.ProcessStartInfo
    $psi.FileName = $env:ComSpec
    $psi.Arguments = "/c `"$line $op `"$log`" 2>&1`""
    $psi.UseShellExecute = $false
    $psi.WorkingDirectory = (Get-Location).Path
    $p = [Diagnostics.Process]::Start($psi)
    if (-not $p.WaitForExit($TimeoutSec * 1000)) {
        cmd /c "taskkill /T /F /PID $($p.Id)" *> $null
        $p.WaitForExit()
        Add-Content $log "TIMEOUT: killed after $TimeoutSec s: $line" -Encoding ascii
        Write-Host "  TIMEOUT after $TimeoutSec s (killed): see $log"   # not pipeline output: callers take the exit code
        return 124
    }
    return $p.ExitCode
}
function Py([string]$argline) { return (cmd /c "`"$py`" -I $argline 2>&1") }
function Done([string]$what, [int]$rc, [string]$log) {
    '{0}: {1}  log: {2}' -f $what, $(if ($rc -eq 0) { 'PASS' } else { "FAIL (exit $rc)" }), $log
}
function Use-Env { if (-not $script:envDone) { . (Join-Path $Main 'tools\env.ps1') *> $null; $script:envDone = $true } }

function Do-Gen {
    $log = Join-Path $logs 'gen.log'
    if ([int]$pj.gen_count -eq 0) { 'gen: the packet has nothing left to generate'; $script:rc = 0; return }
    $hg = Join-Path $Repo "$tree\bin\p3fes_handgen.exe"
    if (-not (Test-Path $hg)) {
        $hg = (Get-ChildItem (Join-Path $Main 'build\*\bin\p3fes_handgen.exe') -ErrorAction SilentlyContinue | Sort-Object LastWriteTime -Descending | Select-Object -First 1).FullName
    }
    if (-not $hg) { 'gen: no p3fes_handgen.exe (run slice.ps1 build first)'; $script:rc = 1; return }
    foreach ($f in $pj.out_cpp, $pj.out_h, $pj.test) {
        if ((Test-Path (Join-Path $Repo $f)) -and -not $Force) { "gen: $f exists (-Force overwrites it)"; $script:rc = 1; return }
    }
    New-Item -ItemType Directory -Force (Split-Path (Join-Path $Repo $pj.out_cpp)) | Out-Null
    $rows = Join-Path $logs "$Slice.rows"
    $rc = Exec ("`"$hg`" --elf $elf --functions symbols\functions.json --chunks symbols\function_chunks.txt " +
        "--jumptables symbols\jumptables.json --sym symbols\p3fes.sym --only @$($pj.gen_list) --slice $Slice " +
        "--header-include $($pj.header_include) --out-cpp $($pj.out_cpp) --out-h $($pj.out_h) --out-replaced $rows " +
        "--out-test $($pj.test) --no-shim") $log  # entry points: generated from replaced.txt (game/forwarders.cmake)
    $sum = Get-Content $log | Select-String 'functions generated' | Select-Object -Last 1
    if ($sum) { '  ' + ($sum.Line -replace ';.*', '') }
    Get-Content $log | Select-String 'not generated' | Select-Object -First 5 | ForEach-Object { '  ' + $_.Line.Trim() }
    if (-not (Test-Path $rows)) { Done 'gen' 1 $log; $script:rc = 1; return }
    $w = Py "`"$here\wire.py`" --repo `"$Repo`" --packet `"$pjPath`" --rows `"$rows`""
    $w | Add-Content $log
    $w | ForEach-Object { "  $_" }
    '  wrote {0}, {1}, {2}' -f $pj.out_cpp, $pj.out_h, $pj.test
    $rc2 = if ($w -match 'Traceback') { 1 } else { $rc }
    Done 'gen' $rc2 $log
    $script:rc = $rc2; return
}

function Do-Pseudo {
    $log = Join-Path $logs 'pseudo.log'
    $out = Join-Path $Scratch "$Slice.pseudo.c"
    $hgArgs = (Get-ChildItem (Join-Path $Repo 'game\src') -Recurse -Filter "$Slice*.cpp" | ForEach-Object { "--handgen `"$($_.FullName)`"" }) -join ' '
    $rc = Exec "`"$py`" -I tools\ours\ida\pseudo.py --only @$list $hgArgs --out `"$out`"" $log
    Get-Content $log | Where-Object { $_ -match '\d' } | Select-Object -Last 3 | ForEach-Object { '  ' + $_.Trim().Substring(0, [Math]::Min(220, $_.Trim().Length)) }
    '  {0} lines in {1} (read it by line ranges; the table is at the top)' -f ((Get-Content $out -ErrorAction SilentlyContinue | Measure-Object -Line).Lines), $out
    Done 'pseudo' $rc $log
    $script:rc = $rc; return
}

function Do-Build {
    $log = Join-Path $logs 'build.log'
    $rc = Exec "powershell -NoProfile -ExecutionPolicy Bypass -File $Main\tools\ours\gate\gate.ps1 -Repo `"$Repo`" -Tree $tree -Slice -BuildOnly -Jobs $Jobs" $log
    Get-Content $log | Select-String '^(configure|reconfigure|emit|build|total|BUILD|ABORT)' | ForEach-Object { '  ' + $_.Line.Trim() }
    if ($rc -ne 0) { Py "`"$here\p5report.py`" build `"$(Join-Path $Repo "$tree.gate.log")`"" }
    Done 'build' $rc "$log (compiler output: $tree.gate.log)"
    $script:rc = $rc; return
}

function Run-Tests([string]$dir, [string]$log) {
    $exe = Join-Path $Repo "$dir\bin\p3fes_game_tests.exe"
    if (-not (Test-Path $exe)) { "  no $exe (build first)"; $script:rc = 1; return }
    $rc = Exec "`"$exe`" `"-sf=$testGlob`"" $log -TimeoutSec 1800
    Py "`"$here\p5report.py`" doctest `"$log`"" | ForEach-Object { "  $_" }
    $script:rc = $rc; return
}

function Do-Test {
    $log = Join-Path $logs 'test.log'
    Run-Tests $tree $log; $rc = $script:rc
    Done "test (MSVC, -sf=$testGlob)" $rc $log
    $script:rc = $rc; return
}

function Do-Clang {
    Use-Env
    $blog = Join-Path $logs 'clang-build.log'
    $log = Join-Path $logs 'clang-test.log'
    if (-not (Test-Path 'recomp\generated\dispatch.cpp')) { 'clang: recomp\generated is not emitted (slice.ps1 build first)'; $script:rc = 1; return }
    $rc = 0
    if (-not (Test-Path (Join-Path $clangTree 'CMakeCache.txt'))) {
        $cache = (Join-Path $Main 'build\_unit_cache').Replace('\', '/')
        $rc = Exec "cmake --preset clangcl-x64-release -B $clangTree -DP3FES_RT_EXEC_ELF=$elf -DP3FES_GAME_TESTS_SHARDED=ON -DP3FES_UNIT_CACHE=$cache -DP3FES_MACHINE_STATES=ON" $blog
    }
    if ($rc -eq 0) { $rc = Exec "cmake --build $clangTree --target p3fes_game_tests -j $Jobs" $blog -Append }
    if ($rc -ne 0) {
        '  clang-cl build failed'
        Py "`"$here\p5report.py`" build `"$blog`"" | ForEach-Object { $_ }
        Done 'clang' $rc $blog
        $script:rc = $rc; return
    }
    Run-Tests $clangTree $log; $rc = $script:rc
    Done "clang (clang-cl, -sf=$testGlob)" $rc $log
    $script:rc = $rc; return
}

function Do-Audit {
    Use-Env
    $log = Join-Path $logs 'audit.log'
    $tsv = Join-Path $logs 'audit.tsv'
    $cache = Join-Path $tree 'CMakeCache.txt'
    if (-not (Test-Path $cache)) { 'audit: no gate tree (slice.ps1 build first)'; $script:rc = 1; return }
    $rc = 0
    if (-not (Select-String -Quiet -Path $cache -Pattern '^P3FES_AUDIT_FAITHFUL:BOOL=ON')) { $rc = Exec "cmake -B $tree -DP3FES_AUDIT_FAITHFUL=ON" $log }
    if ($rc -eq 0) { $rc = Exec "cmake --build $tree --target p3fes_audit_faithful -j $Jobs" $log -Append }
    if ($rc -ne 0) {
        '  audit build failed'
        Py "`"$here\p5report.py`" build `"$log`"" | ForEach-Object { $_ }
        Done 'audit' $rc $log
        $script:rc = $rc; return
    }
    $names = (Py "`"$here\p5report.py`" names `"$list`" symbols\functions.json") -join ''
    $snaps = ($pj.snapshots -join ',')
    $rc = Exec ("`"$py`" -I tools\ours\audit\audit_faithful.py --exe $tree\bin\p3fes_audit_faithful.exe --out `"$tsv`" " +
        "--only $names --seeds $($pj.seeds) --snapshots $snaps --snapshot-seeds $($pj.snapshot_seeds) --objdir $tree\game --jobs $Jobs") $log -Append
    $r = Py "`"$here\p5report.py`" audit `"$tsv`""
    $r | ForEach-Object { "  $_" }
    if ($rc -eq 0 -and ($r -match ', [1-9]\d* not')) { $rc = 1 }
    Done 'audit' $rc $log
    $script:rc = $rc; return
}

function Do-Sync {
    $log = Join-Path $logs 'sync.log'
    $rc = Exec "`"$py`" -I `"$here\sync.py`" --repo `"$Repo`" --slice $Slice" $log
    Get-Content $log | Select-Object -First 9 | ForEach-Object { '  ' + $_ }
    Done 'sync' $rc $log
    $script:rc = $rc; return
}

function Do-Gate {
    $log = Join-Path $logs 'gate.log'
    $rc = Exec "powershell -NoProfile -ExecutionPolicy Bypass -File $Main\tools\ours\gate\gate.ps1 -Repo `"$Repo`" -Tree $tree -Slice -NoSuites -FastGs -Jobs $Jobs -Routes dorm,m1,battle,fusion,shop,climb" $log
    Py "`"$here\p5report.py`" gate `"$log`"" | ForEach-Object { $_ }
    Done 'gate (-Slice -NoSuites -FastGs, six routes)' $rc $log
    $script:rc = $rc; return
}

$script:rc = 0
function Ok { return ($script:rc -eq 0) }
switch ($Cmd) {
    'gen' { Do-Gen }
    'pseudo' { Do-Pseudo }
    'build' { Do-Build }
    'test' { Do-Test }
    'clang' { Do-Clang }
    'audit' { Do-Audit }
    'step' { Do-Build; if (Ok) { Do-Test }; if (Ok) { Do-Audit } }
    'sync' { Do-Sync }
    'final' {
        Do-Sync
        if (Ok) { Do-Build }
        if (Ok) { Do-Test }
        if (Ok) { Do-Clang }
        if (Ok) { Do-Gate }
        if (Ok) { 'final: PASS -- commit once with explicit pathspecs, then slice.ps1 report' }
    }
    'report' { Py "`"$here\p5report.py`" report `"$Repo`" $Slice `"$pjPath`"" | ForEach-Object { $_ } }
}
exit $script:rc
