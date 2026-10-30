#Requires -Version 5.1
<#
.SYNOPSIS
  Puts every build/analysis dependency of this machine on PATH for the current PowerShell session.
.DESCRIPTION
  Dot-source it:   . .\tools\env.ps1
  Enters the VS 2022 x64 developer shell (cl, link, cmake, ninja, msbuild, Windows SDK) and adds the
  ps2dev EE toolchain, tools\bin, Gradle and the JDK. Sets P3FES_* variables for tools that are not
  on PATH. Nothing is installed or downloaded; missing pieces are reported, not fetched.
  Machine layout and provenance: CLAUDE.md, docs/HANDOFF.md.
#>
$ErrorActionPreference = 'Stop'
$Root = Split-Path $PSScriptRoot -Parent

# --- VS 2022 developer shell (x64 host, x64 target) ---------------------------------------------
# Any VS 2022 edition with the C++ tools (Build Tools, Community, ...), found with vswhere. Enter the
# dev shell unless the cl.exe already on PATH belongs to that install: an unrelated cl.exe on the
# system PATH (e.g. an old VS .NET 2003) must not short-circuit it.
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$installerDir = Split-Path $vswhere -Parent   # VsDevCmd's own scripts call vswhere.exe by name
if ($env:Path -notlike "*$installerDir*") { $env:Path = "$installerDir;$env:Path" }
$vs = & $vswhere -version '[17.0,18.0)' -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -latest -property installationPath
if (-not $vs) { throw 'No VS 2022 install with the C++ x64 tools found (vswhere).' }
$cl = Get-Command cl.exe -ErrorAction SilentlyContinue
if (-not $cl -or -not $cl.Source.StartsWith($vs, [StringComparison]::OrdinalIgnoreCase)) {
    Import-Module (Join-Path $vs 'Common7\Tools\Microsoft.VisualStudio.DevShell.dll')
    $here = Get-Location
    Enter-VsDevShell -VsInstallPath $vs -SkipAutomaticLocation -DevCmdArguments '-arch=x64 -host_arch=x64' | Out-Null
    Set-Location $here
}

# --- project-local tools (all built from pinned source on 2026-10-19) ---------------------------
$env:JAVA_HOME          = 'C:\Program Files\Java\jdk-21.0.12.1'
$env:GHIDRA_INSTALL_DIR = 'C:\ghidra'
$env:P3FES_IDA_DIR      = 'C:\Program Files\IDA Professional 9.3'
$env:P3FES_PYTHON       = Join-Path $env:LOCALAPPDATA 'Programs\Python\Python314\python.exe'   # docs say C:\Python314; this machine is per-user
$env:P3FES_RABBITIZER_PY = Join-Path $Root 'deps\venv\rabbitizer\Scripts\python.exe'           # interpreter for recomp/tests/oracle_decode.py
$env:P3FES_PCSX2        = Join-Path $Root 'tools\third_party\pcsx2\pcsx2-qt.exe'
$env:PS2DEV             = Join-Path $Root 'tools\third_party\ps2dev\ps2dev'

$add = @(
    (Join-Path $vs 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin'),  # VS-bundled cmake, ahead of any
    (Join-Path $vs 'Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja'),      # loose cmake/ninja on the system PATH
    (Join-Path $env:PS2DEV 'ee\bin'),                 # mips64r5900el-ps2-elf-{gcc,objdump,as,ld,...}
    (Join-Path $Root 'tools\bin'),                    # cvm_tool.exe
    (Join-Path $Root 'tools\bin\vgmstream'),          # vgmstream-cli.exe
    (Join-Path $Root 'deps\tools\gradle-9.7.1\bin'),  # gradle (Ghidra extension builds)
    (Join-Path $env:JAVA_HOME 'bin')
)
foreach ($p in $add) {   # move to the front (the dev shell may already have added it behind the system PATH)
    $env:Path = (@($p) + @($env:Path -split ';' | Where-Object { $_ -and $_.TrimEnd('\') -ne $p.TrimEnd('\') })) -join ';'
}

# --- report --------------------------------------------------------------------------------------
$check = [ordered]@{
    'cl'        = 'cl.exe'; 'clang-cl' = 'clang-cl.exe'; 'cmake' = 'cmake.exe'; 'ninja' = 'ninja.exe'; 'msbuild' = 'MSBuild.exe'
    'dotnet'    = 'dotnet.exe'; 'git' = 'git.exe'; 'java' = 'java.exe'; 'gradle' = 'gradle.bat'
    'ee-gcc'    = 'mips64r5900el-ps2-elf-gcc.exe'; 'ee-objdump' = 'mips64r5900el-ps2-elf-objdump.exe'
    'cvm_tool'  = 'cvm_tool.exe'; 'vgmstream' = 'vgmstream-cli.exe'
}
foreach ($k in $check.Keys) {
    $c = Get-Command $check[$k] -ErrorAction SilentlyContinue
    '{0,-11} {1}' -f $k, $(if ($c) { $c.Source } else { 'MISSING' })
}
foreach ($v in 'P3FES_PYTHON', 'P3FES_RABBITIZER_PY', 'P3FES_PCSX2', 'P3FES_IDA_DIR', 'GHIDRA_INSTALL_DIR') {
    $val = [Environment]::GetEnvironmentVariable($v)
    '{0,-20} {1}{2}' -f $v, $val, $(if (Test-Path $val) { '' } else { '   (MISSING)' })
}
