#Requires -Version 5.1
<#
.SYNOPSIS
  A route in segments from machine states (runtime/STATE.md): each segment resumes the state at its start and is
  compared at its end, all segments in parallel.
.DESCRIPTION
  powershell -File tools\ours\state\state_segments.ps1 -Exe build\<tree>\bin\p3fes.exe -Route climb -Marks 10000,20000,30000 -Make
     one run from boot saves a state and a snapshot at every mark and at the route's end point (<Out>\state_<m>.p3st,
     <Out>\snap_<m>\); this is the from-boot reference for the segments.
  powershell -File tools\ours\state\state_segments.ps1 -Exe ... -Route climb -Marks 10000,20000,30000
     the segments [m_i, m_i+1) (the last one to the end point) run in parallel (-Jobs), each from state_<m_i>, and
     each end snapshot is compared with snap_<m_i+1> (eeMemory.bin, gsMemory.bin, frame.png, capture.json) or, with
     -RefRoot, with <RefRoot>\snap_<m>.
  States load only into the executable that saved them (runtime/STATE.md "Why the same executable"): -Make and the
  segment runs must use the same p3fes.exe. Uses: re-running stretches of one build (diagnostics, A/B of options,
  bisects inside one executable); it is also the shape a segmented gate would take once reference states can
  seed candidate builds.
#>
param(
    [Parameter(Mandatory)][string]$Exe,
    [Parameter(Mandatory)][ValidateSet('dorm', 'battle', 'fusion', 'shop', 'climb')][string]$Route,
    [Parameter(Mandatory)][string]$Marks,  # comma-separated vblanks
    [int]$Target = 0,
    [switch]$Make,
    [ValidateSet('d3d11', 'software')][string]$Gs = 'd3d11',
    [string]$Out = '',
    [string]$RefRoot = '',
    [int]$Jobs = 4,
    [string]$Main = 'F:\P3FES-PORT\p3fes-port'
)
$ErrorActionPreference = 'Stop'
$Exe = (Resolve-Path $Exe).Path
$repo = (Get-Location).Path
$refs = Join-Path $Main 'extracted\_ours'
$routes = @{
    dorm   = @{ card = ''; arg = '--memcard new'; input = 'to_dorm.txt'; at = 4900 }
    battle = @{ card = 'tartarus.ps2'; input = 'to_battle.txt'; at = 6150 }
    fusion = @{ card = 'fusion.ps2'; input = 'fusion.txt'; at = 6300 }
    shop   = @{ card = 'shop_buy.ps2'; input = 'shop.txt'; at = 4100 }
    climb  = @{ card = 'full_battle.ps2'; input = 'full_battle.txt'; at = 39820 }
}
$r = $routes[$Route]
if ($Target -le 0) { $Target = $r.at }
$ms = @($Marks.Split(',') | Where-Object { $_.Trim() } | ForEach-Object { [int]$_.Trim() } | Sort-Object)
foreach ($m in $ms) { if ($m -le 0 -or $m -ge $Target) { throw "mark $m is not inside (0, $Target)" } }
if (-not $Out) { $Out = Join-Path $repo "build\state_segments\$Route-$Gs" }
if (-not $RefRoot) { $RefRoot = $Out }
New-Item -ItemType Directory -Force $Out | Out-Null
New-Item -ItemType Directory -Force 'extracted\_ours\cards' | Out-Null
$gsArgs = if ($Gs -eq 'd3d11') { '--gs-backend d3d11 --gs-exact' } else { '' }
$base = "--elf $Main\extracted\disc\SLUS_216.21 --iso $Main\input\persona3fes.iso --headless --quiet --vu1 aot $gsArgs"
$replay = "--replay-input $Main\config\inputs\$($r.input)"
function Card-Arg($tag) {
    if (-not $r.card) { return $r.arg }
    $name = "seg_${Route}_${Gs}_$tag.ps2"
    Copy-Item (Join-Path $refs "cards\$($r.card)") "extracted\_ours\cards\$name" -Force
    Remove-Item "extracted\_ours\memcards\$name" -ErrorAction SilentlyContinue
    "--memcard extracted\_ours\cards\$name"
}
function Start-Run($tag, $extra) {
    $log = Join-Path $Out "$tag.log"
    $psi = New-Object Diagnostics.ProcessStartInfo
    $psi.FileName = $env:ComSpec
    $psi.Arguments = "/c `"`"$Exe`" $base $(Card-Arg $tag) $replay $extra > `"$log`" 2>&1`""
    $psi.UseShellExecute = $false
    $psi.WorkingDirectory = $repo
    [pscustomobject]@{ tag = $tag; proc = [Diagnostics.Process]::Start($psi); log = $log }
}
$sw = [Diagnostics.Stopwatch]::StartNew()
if ($Make) {
    $ends = $ms + @($Target)
    $a = (($ms | ForEach-Object { "--save-state-at vblank:$_ $(Join-Path $Out "state_$_.p3st")" }) +
          ($ends | ForEach-Object { "--snapshot-at vblank:$_ $(Join-Path $Out "snap_$_")" })) -join ' '
    foreach ($m in $ends) { Remove-Item -Recurse -Force (Join-Path $Out "snap_$m") -ErrorAction SilentlyContinue }
    $x = Start-Run 'make' $a
    $x.proc.WaitForExit()
    'make (from boot, {0} states + {1} snapshots): exit {2}, {3:N1} s' -f $ms.Count, $ends.Count, $x.proc.ExitCode, $sw.Elapsed.TotalSeconds
    Get-Content $x.log | Select-String '^p3fes: state vblank' | ForEach-Object { '  ' + $_.Line.Replace('p3fes: ', '') }
    Remove-Item "extracted\_ours\memcards\seg_${Route}_${Gs}_make.ps2", "extracted\_ours\cards\seg_${Route}_${Gs}_make.ps2" -ErrorAction SilentlyContinue
    exit $x.proc.ExitCode
}
# the first segment boots (0 -> first mark); every other one resumes the state at its start
$starts = @(0) + $ms
$segs = for ($i = 0; $i -lt $starts.Count; $i++) {
    $end = if ($i + 1 -lt $starts.Count) { $starts[$i + 1] } else { $Target }
    [pscustomobject]@{ from = $starts[$i]; to = $end; dir = (Join-Path $Out "seg_$($starts[$i])") }
}
$running = @()
foreach ($s in $segs) {
    $st = Join-Path $Out "state_$($s.from).p3st"
    $load = if ($s.from -eq 0) { '' } else { "--load-state $st" }
    if ($s.from -ne 0 -and -not (Test-Path $st)) { throw "no $st (run with -Make first)" }
    while (@($running | Where-Object { -not $_.proc.HasExited }).Count -ge $Jobs) { Start-Sleep -Milliseconds 500 }
    Remove-Item -Recurse -Force $s.dir -ErrorAction SilentlyContinue
    $x = Start-Run "seg_$($s.from)" "$load --snapshot-at vblank:$($s.to) $($s.dir)"
    $x | Add-Member -NotePropertyName seg -NotePropertyValue $s
    $running += $x
}
foreach ($x in $running) { $x.proc.WaitForExit() }
$failed = $false
foreach ($x in $running) {
    $s = $x.seg
    $ref = Join-Path $RefRoot "snap_$($s.to)"
    $res = foreach ($f in 'eeMemory.bin', 'gsMemory.bin', 'frame.png', 'capture.json') {
        $a = Join-Path $s.dir $f; $b = Join-Path $ref $f
        if ((Test-Path $a) -and (Test-Path $b) -and (Get-FileHash $a).Hash -eq (Get-FileHash $b).Hash) { 'same' } else { $failed = $true; "$f DIFFERS" }
    }
    $ok = if (@($res | Where-Object { $_ -ne 'same' }).Count -eq 0) { 'identical' } else { ($res | Where-Object { $_ -ne 'same' }) -join ', ' }
    'segment {0,6}-{1,-6} exit {2}  {3,7:N1} s  {4}' -f $s.from, $s.to, $x.proc.ExitCode, ($x.proc.ExitTime - $x.proc.StartTime).TotalSeconds, $ok
    if ($x.proc.ExitCode -ne 0) { $failed = $true }
    Remove-Item "extracted\_ours\memcards\seg_${Route}_${Gs}_$($x.tag).ps2", "extracted\_ours\cards\seg_${Route}_${Gs}_$($x.tag).ps2" -ErrorAction SilentlyContinue
}
'segments wall {0:N1} s ({1} segments, -Jobs {2})' -f $sw.Elapsed.TotalSeconds, $segs.Count, $Jobs
if ($failed) { 'SEGMENTS: FAILED'; exit 1 } else { 'SEGMENTS: PASSED'; exit 0 }
