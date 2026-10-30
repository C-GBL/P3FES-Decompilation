<#
.SYNOPSIS
  Boot PCSX2 2.8.2 (portable, tools/third_party/pcsx2) on an ISO with a wall-clock timeout and log capture.

.DESCRIPTION
  Starts pcsx2-qt.exe -portable -earlyconsolelog [-batch] [-nogui] [-slowboot|-fastboot] [extra] -- <iso>,
  waits up to -TimeoutSec, then stops it: first WM_CLOSE (Process.CloseMainWindow; [UI] ConfirmShutdown=false
  makes this a clean VM shutdown), then Stop-Process -Force as a last resort. The run's logs/emulog.txt is
  copied to -LogCopy (default extracted/_pcsx2/logs/emulog_<timestamp>.txt, gitignored).
  Exit code: 0 if PCSX2 exited by itself or on WM_CLOSE, 3 if it had to be killed, 2 on setup errors.

  -KeepRunning returns right after start (prints the PID) so a PINE client (pine.py) can drive the session;
  stop it later with: run_pcsx2.ps1 -StopPid <pid>  (WM_CLOSE first, kill after 15 s).

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\ours\pcsx2\run_pcsx2.ps1 -TimeoutSec 120 -SlowBoot
  powershell -ExecutionPolicy Bypass -File tools\ours\pcsx2\run_pcsx2.ps1 -KeepRunning
  powershell -ExecutionPolicy Bypass -File tools\ours\pcsx2\run_pcsx2.ps1 -StopPid 12345
#>
[CmdletBinding()]
param(
  [string]$Iso = "",
  [int]$TimeoutSec = 120,
  [switch]$SlowBoot,
  [switch]$FastBoot,
  [switch]$NoGui,
  [switch]$KeepRunning,
  [int]$StopPid = 0,
  [string[]]$ExtraArgs = @(),
  [string]$LogCopy = ""
)

$ErrorActionPreference = "Stop"
$Repo = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path
$Pcsx2Dir = Join-Path $Repo "tools\third_party\pcsx2"
$Exe = Join-Path $Pcsx2Dir "pcsx2-qt.exe"
$EmuLog = Join-Path $Pcsx2Dir "logs\emulog.txt"
if ($Iso -eq "") { $Iso = Join-Path $Repo "input\persona3fes.iso" }

function Stop-Pcsx2([System.Diagnostics.Process]$Proc, [int]$GraceSec = 15) {
  if ($Proc.HasExited) { return 0 }
  try { [void]$Proc.CloseMainWindow() } catch {}
  if ($Proc.WaitForExit($GraceSec * 1000)) { return 0 }
  Write-Warning "PCSX2 ignored WM_CLOSE for $GraceSec s; killing"
  Stop-Process -Id $Proc.Id -Force
  [void]$Proc.WaitForExit(5000)
  return 3
}

if ($StopPid -ne 0) {
  $p = Get-Process -Id $StopPid -ErrorAction SilentlyContinue
  if (-not $p) { Write-Host "pid $StopPid not running"; exit 0 }
  $rc = Stop-Pcsx2 $p
  Write-Host "stopped pid $StopPid (rc=$rc)"
  exit $rc
}

if (-not (Test-Path $Exe)) { Write-Error "pcsx2-qt.exe not found at $Exe"; exit 2 }
if (-not (Test-Path $Iso)) { Write-Error "ISO not found at $Iso"; exit 2 }
if (-not (Test-Path (Join-Path $Pcsx2Dir "inis\PCSX2.ini"))) {
  Write-Error "inis\PCSX2.ini missing; run pcsx2-qt.exe -portable -testconfig, then tools\ours\pcsx2\configure_ini.py"
  exit 2
}

# Keep a copy of the previous run's log (PCSX2 truncates emulog.txt on start).
if (Test-Path $EmuLog) { Copy-Item $EmuLog ($EmuLog + ".prev") -Force }

$argv = @("-portable", "-earlyconsolelog")
if (-not $KeepRunning) { $argv += "-batch" }
if ($NoGui) { $argv += "-nogui" }
if ($SlowBoot) { $argv += "-slowboot" }
if ($FastBoot) { $argv += "-fastboot" }
$argv += $ExtraArgs
$argv += @("--", $Iso)

$started = Get-Date
Write-Host ("[{0:HH:mm:ss}] start: {1} {2}" -f $started, $Exe, ($argv -join " "))
$proc = Start-Process -FilePath $Exe -ArgumentList $argv -WorkingDirectory $Pcsx2Dir -PassThru
Write-Host "pid=$($proc.Id)"

if ($KeepRunning) {
  Write-Host "left running; stop with: run_pcsx2.ps1 -StopPid $($proc.Id)"
  exit 0
}

$rc = 0
if ($proc.WaitForExit($TimeoutSec * 1000)) {
  Write-Host ("[{0:HH:mm:ss}] PCSX2 exited by itself, code {1}" -f (Get-Date), $proc.ExitCode)
} else {
  Write-Host ("[{0:HH:mm:ss}] timeout {1}s reached; closing" -f (Get-Date), $TimeoutSec)
  $rc = Stop-Pcsx2 $proc
}

if ($LogCopy -eq "") {
  $logDir = Join-Path $Repo "extracted\_pcsx2\logs"
  New-Item -ItemType Directory -Force $logDir | Out-Null
  $LogCopy = Join-Path $logDir ("emulog_{0:yyyyMMdd-HHmmss}.txt" -f $started)
}
if (Test-Path $EmuLog) {
  Copy-Item $EmuLog $LogCopy -Force
  Write-Host "emulog copied to $LogCopy ($((Get-Item $LogCopy).Length) bytes)"
} else {
  Write-Warning "no emulog.txt produced"
}
exit $rc
