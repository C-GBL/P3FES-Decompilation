#Requires -Version 5.1
<#
.SYNOPSIS
  Machine-state round trip (runtime/STATE.md): for a route, running straight to vblank M must equal running to N,
  saving the machine, loading it in a fresh process and running on to M -- eeMemory.bin, gsMemory.bin, frame.png
  and capture.json byte for byte.
.DESCRIPTION
  powershell -File tools\ours\state\state_roundtrip.ps1 -Exe build\<tree>\bin\p3fes.exe -Route dorm -Points 1000,3000
  One process runs the route straight to M (no saves: the baseline); one runs it to M saving a state at every
  point (its own snapshot at M must equal the baseline too: saving perturbs nothing); then one process per point
  loads that state and runs on to M. -Gs d3d11 (default: offscreen exact, as the gates' -FastGs) or software.
  Processes run in parallel (-Jobs, default 3). Each process gets its own copy of the route's memory card (the
  copy-on-write files never collide). Exit 0 when every comparison is identical. Game data, cards and replay logs
  come from the main tree (-Main).
#>
param(
    [Parameter(Mandatory)][string]$Exe,
    [Parameter(Mandatory)][ValidateSet('dorm', 'm1', 'battle', 'fusion', 'shop', 'climb')][string]$Route,
    [Parameter(Mandatory)][Alias('Points')][string]$PointList,         # comma-separated vblanks N (powershell -File passes one string)
    [int]$Target = 0,                     # M (vblank); default: the route's gate point (m1: its sky:11 point is not a vblank: give -Target)
    [ValidateSet('d3d11', 'software')][string]$Gs = 'd3d11',
    [string]$Out = '',
    [int]$Jobs = 3,
    [string]$Main = 'F:\P3FES-PORT\p3fes-port',
    [string]$Baseline = '',               # an existing straight snapshot dir at M from the same exe and GS (skips that run)
    [switch]$KeepStates
)
$ErrorActionPreference = 'Stop'
$Exe = (Resolve-Path $Exe).Path
$repo = (Get-Location).Path
$refs = Join-Path $Main 'extracted\_ours'
$routes = @{
    dorm   = @{ card = ''; arg = '--memcard new'; input = 'to_dorm.txt'; at = 4900 }
    m1     = @{ card = ''; arg = ''; input = ''; at = 0 }
    battle = @{ card = 'tartarus.ps2'; input = 'to_battle.txt'; at = 6150 }
    fusion = @{ card = 'fusion.ps2'; input = 'fusion.txt'; at = 6300 }
    shop   = @{ card = 'shop_buy.ps2'; input = 'shop.txt'; at = 4100 }
    climb  = @{ card = 'full_battle.ps2'; input = 'full_battle.txt'; at = 39820 }
}
$r = $routes[$Route]
$Points = @($PointList.Split(',') | Where-Object { $_.Trim() } | ForEach-Object { [int]$_.Trim() })
if ($Target -le 0) { $Target = $r.at }
if ($Target -le 0) { throw "-Target is required for route $Route" }
foreach ($n in $Points) { if ($n -le 0 -or $n -ge $Target) { throw "point $n is not inside (0, $Target)" } }
if (-not $Out) { $Out = Join-Path $repo "build\state_roundtrip\$Route-$Gs" }
New-Item -ItemType Directory -Force $Out | Out-Null
$gsArgs = if ($Gs -eq 'd3d11') { '--gs-backend d3d11 --gs-exact' } else { '' }
$base = "--elf $Main\extracted\disc\SLUS_216.21 --iso $Main\input\persona3fes.iso --headless --quiet --vu1 aot $gsArgs"

# The route's card, one private copy per process (copy-on-write saves go to .\extracted\_ours\memcards\<name>).
New-Item -ItemType Directory -Force 'extracted\_ours\cards' | Out-Null
function Card-Arg($tag) {
    if ($r.card) {
        $name = "rt_${Route}_${Gs}_$tag.ps2"
        Copy-Item (Join-Path $refs "cards\$($r.card)") "extracted\_ours\cards\$name" -Force
        Remove-Item "extracted\_ours\memcards\$name" -ErrorAction SilentlyContinue
        return "--memcard extracted\_ours\cards\$name"
    }
    return $r.arg
}
$replay = if ($r.input) { "--replay-input $Main\config\inputs\$($r.input)" } else { '' }

function Start-Run($tag, $extra) {
    $log = Join-Path $Out "$tag.log"
    $psi = New-Object Diagnostics.ProcessStartInfo
    $psi.FileName = $env:ComSpec
    $psi.Arguments = "/c `"`"$Exe`" $base $(Card-Arg $tag) $replay $extra > `"$log`" 2>&1`""
    $psi.UseShellExecute = $false
    $psi.WorkingDirectory = $repo
    $p = [Diagnostics.Process]::Start($psi)
    [pscustomobject]@{ tag = $tag; proc = $p; log = $log; t0 = Get-Date }
}
function Wait-Slots($running, $max) {
    while (@($running | Where-Object { -not $_.proc.HasExited }).Count -ge $max) { Start-Sleep -Milliseconds 500 }
}

$sw = [Diagnostics.Stopwatch]::StartNew()
$runs = @()
$straight = if ($Baseline) { $Baseline } else { Join-Path $Out 'straight' }
if (-not $Baseline) {
    Remove-Item -Recurse -Force $straight -ErrorAction SilentlyContinue
    $runs += Start-Run 'straight' "--snapshot-at vblank:$Target $straight"
}
$saves = ($Points | ForEach-Object { "--save-state-at vblank:$_ $(Join-Path $Out "state_$_.p3st")" }) -join ' '
$saverSnap = Join-Path $Out 'saver'
Remove-Item -Recurse -Force $saverSnap -ErrorAction SilentlyContinue
$saver = Start-Run 'saver' "$saves --snapshot-at vblank:$Target $saverSnap"
$runs += $saver
# Loads start as soon as their state exists (the saver writes them in point order).
$pending = [System.Collections.Generic.List[int]]::new()
$Points | Sort-Object | ForEach-Object { $pending.Add($_) }
while ($pending.Count -gt 0) {
    $n = $pending[0]
    $st = Join-Path $Out "state_$n.p3st"
    if (Test-Path $st) {
        Wait-Slots $runs $Jobs
        $dir = Join-Path $Out "load_$n"
        Remove-Item -Recurse -Force $dir -ErrorAction SilentlyContinue
        $runs += Start-Run "load_$n" "--load-state $st --snapshot-at vblank:$Target $dir"
        $pending.RemoveAt(0)
    } elseif ($saver.proc.HasExited) {
        "point ${n}: no state written (see saver.log)"; $pending.RemoveAt(0)
    } else { Start-Sleep -Milliseconds 500 }
}
foreach ($x in $runs) { $x.proc.WaitForExit() }

function Same($a, $b) { (Test-Path $a) -and (Test-Path $b) -and ((Get-FileHash $a).Hash -eq (Get-FileHash $b).Hash) }
$failed = $false
"route $Route, GS $Gs, target vblank $Target, points $($Points -join ', ')"
foreach ($x in $runs) {
    $secs = ($x.proc.ExitTime - $x.proc.StartTime).TotalSeconds
    $line = '{0,-12} exit {1}  {2,7:N1} s' -f $x.tag, $x.proc.ExitCode, $secs
    $st = Get-Content $x.log | Select-String '^p3fes: state ' | ForEach-Object { '    ' + $_.Line.Replace('p3fes: ', '') }
    $line
    $st
    if ($x.proc.ExitCode -ne 0) { $failed = $true }
}
$dirs = @('saver') + ($Points | ForEach-Object { "load_$_" })
foreach ($d in $dirs) {
    $dd = Join-Path $Out $d
    $res = foreach ($f in 'eeMemory.bin', 'gsMemory.bin', 'frame.png', 'capture.json') {
        if (Same (Join-Path $straight $f) (Join-Path $dd $f)) { "$f same" } else { $failed = $true; "$f DIFFERS" }
    }
    '{0,-12} vs straight: {1}' -f $d, ($res -join ', ')
}
if (-not $KeepStates) { Get-ChildItem $Out -Filter 'state_*.p3st' | Remove-Item -ErrorAction SilentlyContinue }
foreach ($x in $runs) { Remove-Item "extracted\_ours\memcards\rt_${Route}_${Gs}_$($x.tag).ps2" -ErrorAction SilentlyContinue; Remove-Item "extracted\_ours\cards\rt_${Route}_${Gs}_$($x.tag).ps2" -ErrorAction SilentlyContinue }
'wall {0:N1} s' -f $sw.Elapsed.TotalSeconds
if ($failed) { 'ROUNDTRIP: FAILED'; exit 1 } else { 'ROUNDTRIP: PASSED'; exit 0 }
