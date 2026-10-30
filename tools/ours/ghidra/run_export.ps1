# run_export.ps1 -- run the read-only Ghidra headless scripts against the existing p3fes project.
# Never re-imports (-process, not -import), never analyses (-noanalysis), never saves (-readOnly).
#
#   powershell -ExecutionPolicy Bypass -File tools\ours\ghidra\run_export.ps1            # export + decompile
#   powershell -ExecutionPolicy Bypass -File tools\ours\ghidra\run_export.ps1 -Step export
#   powershell -ExecutionPolicy Bypass -File tools\ours\ghidra\run_export.ps1 -Step decompile
#
# Outputs (all gitignored under ghidra/):
#   ghidra/functions_ghidra.json      ExportFunctions.java
#   ghidra/decomp/<addr>.c            DecompileList.java (targets: decomp_targets.txt)
#   ghidra/logs/headless_<step>.log   Ghidra application log      (-log)
#   ghidra/logs/script_<step>.log     script println output       (-scriptlog)
#   ghidra/logs/stdout_<step>.log     full console output
# Then: python tools\ours\ghidra\diff_functions.py symbols\functions.json ghidra\functions_ghidra.json
#
# Ad-hoc diagnostics (same headless flags, pass -postScript <script> <addrs.txt> <out.txt>):
#   InspectBoundaries.java  body ranges, terminating instruction, refs, gap words for listed addresses
#   MnemonicCensus.java     per-function mnemonic census with CALLOTHER (intrinsic) detection
param(
    [ValidateSet('export', 'decompile', 'all')] [string] $Step = 'all',
    [string] $GhidraRoot = 'C:\Users\Ash\Downloads\ghidra_12.1.4_PUBLIC',
    [string] $JavaHome = 'C:\Program Files\Java\jdk-25.0.4'
)
$ErrorActionPreference = 'Stop'
$env:JAVA_HOME = $JavaHome                   # inherited JAVA_HOME is jdk-17, too old for Ghidra 12
$env:PATH = "$JavaHome\bin;$env:PATH"
$repo = (Resolve-Path (Join-Path $PSScriptRoot '..\..\..')).Path
$proj = Join-Path $repo 'ghidra'
$logs = Join-Path $proj 'logs'
New-Item -ItemType Directory -Force $logs | Out-Null
$headless = Join-Path $GhidraRoot 'support\analyzeHeadless.bat'
$scriptPath = $PSScriptRoot

function Invoke-Headless([string] $name, [string[]] $post) {
    $hargs = @($proj, 'p3fes', '-process', 'SLUS_216.21', '-noanalysis', '-readOnly',
               '-scriptPath', $scriptPath,
               '-log', (Join-Path $logs "headless_$name.log"),
               '-scriptlog', (Join-Path $logs "script_$name.log"),
               '-postScript') + $post
    Write-Host "[run_export] $name ..."
    $stdout = Join-Path $logs "stdout_$name.log"
    $stderr = Join-Path $logs "stderr_$name.log"
    # Start-Process + file redirection: Java prints JVM warnings on stderr, which PowerShell 5.1
    # would otherwise wrap as NativeCommandError under $ErrorActionPreference = 'Stop'.
    $quoted = $hargs | ForEach-Object { if ($_ -match '\s') { '"' + $_ + '"' } else { $_ } }
    $p = Start-Process -FilePath $headless -ArgumentList $quoted -NoNewWindow -Wait -PassThru `
            -RedirectStandardOutput $stdout -RedirectStandardError $stderr
    if ($p.ExitCode -ne 0) { throw "analyzeHeadless exited $($p.ExitCode) (see $stdout / $stderr)" }
    Get-Content $stdout, $stderr | Select-String -Pattern 'ExportFunctions:|DecompileList:|ERROR|Exception|error:' |
        ForEach-Object { Write-Host "  $_" }
}

if ($Step -eq 'export' -or $Step -eq 'all') {
    Invoke-Headless 'export' @('ExportFunctions.java', (Join-Path $proj 'functions_ghidra.json'))
}
if ($Step -eq 'decompile' -or $Step -eq 'all') {
    $outDir = Join-Path $proj 'decomp'
    New-Item -ItemType Directory -Force $outDir | Out-Null
    Invoke-Headless 'decompile' @('DecompileList.java', (Join-Path $scriptPath 'decomp_targets.txt'), $outDir)
}
Write-Host "[run_export] done; logs in $logs"
