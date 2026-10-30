#Requires -Version 5.1
<#
.SYNOPSIS
  Reproduces every third-party tool acquisition for the P3FES port into
  tools/third_party/<name>/, tools/downloads/ and tools/bin/ (all gitignored).

.DESCRIPTION
  Idempotent: re-running verifies pins/digests and skips work already done.
  Every git clone is pinned to a commit; every download is pinned to a URL and
  a SHA-256 digest. Digests marked "publisher" were taken from the GitHub
  release asset digest field; digests marked "recorded" were computed by us on
  first download (the publisher offers only GPG signatures or nothing).

  Downloaded archives are untrusted data: each is extracted into its own fresh
  directory and nothing is executed from inside an archive's directory with
  that directory as the current working directory.

  Nothing here touches input/, extracted/, PATH, the registry or any global
  install. No PS2 BIOS and no game data are ever downloaded.

  See docs/TOOLS.md for what each tool is for.

.PARAMETER SkipBuild
  Only fetch/extract; do not run dotnet/clang-cl builds.
.PARAMETER Only
  Restrict to the named steps (e.g. -Only pcsx2,ps2dev).
.PARAMETER IncludeUnlicensedSigs
  OPT-IN (default off): also fetch the unlicensed community PS2 SDK FLIRT
  signature pack (step 'ida-sigs') and install it into IDA's user signature
  directory (%APPDATA%\Hex-Rays\IDA Pro\sig\mips). See docs/TOOLS.md and
  docs/DECISIONS.md ADR-0007. Without this switch the step does not run, even
  with -Only ida-sigs.
#>
[CmdletBinding()]
param(
    [switch]$SkipBuild,
    [string[]]$Only,
    [switch]$IncludeUnlicensedSigs
)

Set-StrictMode -Version 2
$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$ToolsRoot   = $PSScriptRoot
$ThirdParty  = Join-Path $ToolsRoot 'third_party'
$Downloads   = Join-Path $ToolsRoot 'downloads'
$Bin         = Join-Path $ToolsRoot 'bin'
foreach ($d in $ThirdParty, $Downloads, $Bin) { New-Item -ItemType Directory -Force $d | Out-Null }

# ---- host tools we rely on (never installed by this script) -----------------
$SevenZip = 'C:\Program Files\7-Zip\7z.exe'
if (-not (Test-Path $SevenZip)) { $c = Get-Command 7z.exe -ErrorAction SilentlyContinue; if ($c) { $SevenZip = $c.Source } }
$Tar      = "$env:SystemRoot\System32\tar.exe"          # bsdtar, ships with Windows 10 1803+
$ClangCl  = 'C:\Program Files\LLVM\bin\clang-cl.exe'
$Git      = (Get-Command git.exe).Source
$Dotnet   = (Get-Command dotnet.exe -ErrorAction SilentlyContinue)
if ($Dotnet) { $Dotnet = $Dotnet.Source }

function Step([string]$name) {
    if ($Only -and ($Only -notcontains $name)) { return $false }
    Write-Host "`n=== $name ===" -ForegroundColor Cyan
    return $true
}

function Get-Sha256([string]$path) { (Get-FileHash -Algorithm SHA256 -Path $path).Hash.ToLowerInvariant() }

function Fetch-File([string]$url, [string]$name, [string]$sha256) {
    $dst = Join-Path $Downloads $name
    if ((Test-Path $dst) -and ((Get-Sha256 $dst) -eq $sha256)) { Write-Host "  cached  $name"; return $dst }
    Write-Host "  download $url"
    Invoke-WebRequest -Uri $url -OutFile $dst -UseBasicParsing
    $got = Get-Sha256 $dst
    if ($got -ne $sha256) { Remove-Item $dst -Force; throw "SHA-256 mismatch for $name`n  expected $sha256`n  got      $got" }
    Write-Host "  verified $name"
    return $dst
}

function Fresh-Dir([string]$path) {
    if (Test-Path $path) { Remove-Item -Recurse -Force $path }
    New-Item -ItemType Directory -Force $path | Out-Null
    return $path
}

function Clone-Pinned([string]$name, [string]$url, [string]$commit, [switch]$Submodules, [switch]$Shallow) {
    $dst = Join-Path $ThirdParty $name
    if (-not (Test-Path (Join-Path $dst '.git'))) {
        if ($Shallow) {
            New-Item -ItemType Directory -Force $dst | Out-Null
            & $Git -C $dst init -q
            & $Git -C $dst remote add origin $url
            & $Git -C $dst fetch -q --depth 1 origin $commit
            & $Git -C $dst checkout -q FETCH_HEAD
        } else {
            & $Git clone -q $url $dst
        }
    }
    $head = (& $Git -C $dst rev-parse HEAD).Trim()
    if ($head -ne $commit) {
        if (-not $Shallow) { & $Git -C $dst fetch -q origin }
        else { & $Git -C $dst fetch -q --depth 1 origin $commit }
        & $Git -C $dst checkout -q $commit
        $head = (& $Git -C $dst rev-parse HEAD).Trim()
        if ($head -ne $commit) { throw "${name}: could not check out $commit" }
    }
    if ($Submodules) { & $Git -C $dst submodule update --init --recursive -q }
    Write-Host "  $name @ $head"
    return $dst
}

function Run-Dotnet([string[]]$dotnetArgs) {
    # NB: do not name this parameter $args; PowerShell reserves that automatic variable.
    if (-not $Dotnet) { Write-Warning "dotnet not found; skipping build"; return }
    & $Dotnet @dotnetArgs
    if ($LASTEXITCODE -ne 0) { Write-Warning "dotnet exited $LASTEXITCODE (see above)" }
}

# =============================================================================
# 1. CVM / ROFS: JayFoxRox/cvm_tool (roxfan's ROFS tool). C++, built with clang-cl.
#    License: JayFoxRox's changes CC0; roxfan's original has NO stated license.
# =============================================================================
if (Step 'cvm_tool') {
    $src = Clone-Pinned 'cvm_tool' 'https://github.com/JayFoxRox/cvm_tool' '33d937a5059d1a06e3e0ab60cd372794ccbdf456'
    if (-not $SkipBuild) {
        if (-not (Test-Path $ClangCl)) { Write-Warning 'clang-cl not found; cvm_tool not built' }
        else {
            $obj = Fresh-Dir (Join-Path $src 'build-clangcl')
            # Upstream CMakeLists.txt lacks cmake_minimum_required and injects POSIX
            # shims (-D_fseeki64=fseek) that break MSVC-style CRTs, so compile directly.
            & $ClangCl /nologo /O2 /EHsc /W3 /D_FILE_OFFSET_BITS=64 /D_CRT_SECURE_NO_WARNINGS "/Fo$obj\" `
                "$src\cvm_tool.cpp" "$src\rofs_crypt.cpp" "$src\iso_parser.cpp" "$src\cvm_parser.cpp" `
                /link "/OUT:$Bin\cvm_tool.exe"
            if ($LASTEXITCODE -ne 0) { Write-Warning "cvm_tool build failed ($LASTEXITCODE)" } else { Write-Host "  built $Bin\cvm_tool.exe" }
        }
    }
}

# =============================================================================
# 2. Atlus-Script-Tools (formerly AtlusScriptToolchain): BF flow scripts / BMD
#    message scripts. GPL-3.0. net8.0 (runs on the installed 8.0.x runtime).
#    Both the pinned source (built locally) and the matching release zip.
# =============================================================================
if (Step 'atlus-script-tools') {
    $src = Clone-Pinned 'Atlus-Script-Tools' 'https://github.com/tge-was-taken/Atlus-Script-Tools' '1c557a092dd7610829b7215be0f0f5101acf1d72'
    $zip = Fetch-File 'https://github.com/tge-was-taken/Atlus-Script-Tools/releases/download/v1.0-1c557a092dd7610829b7215be0f0f5101acf1d72/Atlus-Script-Tools.zip' `
                      'Atlus-Script-Tools-1c557a09.zip' 'fb73bfb4976e48406ebd36991f23335728b212775507cb73b5b8bec8a1e9575d'   # publisher
    $out = Fresh-Dir (Join-Path $Bin 'AtlusScriptCompiler')
    Expand-Archive -Force $zip $out
    if (-not $SkipBuild) {
        # Output lands in <repo>\Build\Release\net8.0\ (Directory.Build.props).
        Run-Dotnet @('build', "$src\Source\AtlusScriptCompiler\AtlusScriptCompiler.csproj", '-c', 'Release', '-nologo', '-v', 'q')
    }
}

# =============================================================================
# 3. PersonaEditor (Meloman19): PersonaEditorLib, MIT, net8.0 class library.
#    BIN/PAC containers, PM1, BF/BMD text, TMX, SPR/SPD, FNT, TBL.
# =============================================================================
if (Step 'persona-editor') {
    $src = Clone-Pinned 'PersonaEditor' 'https://github.com/Meloman19/PersonaEditor' '5305355d159ee7d74eb830b325dd7a5f9a777961'
    if (-not $SkipBuild) {
        Run-Dotnet @('build', "$src\PersonaEditorLib\PersonaEditorLib.csproj", '-c', 'Release', '-nologo', '-v', 'q')
    }
}

# =============================================================================
# 4. AtlusFileSystemLibrary (TGE): PAK/PAC/BIN pack variants + PAKPack CLI.
#    GPL-2.0. Old-style .NET Framework 4.7 csproj; the 4.7 targeting pack is
#    absent on this host but 4.8 is, so we override TargetFrameworkVersion.
# =============================================================================
if (Step 'atlus-filesystem-library') {
    $src = Clone-Pinned 'AtlusFileSystemLibrary' 'https://github.com/tge-was-taken/AtlusFileSystemLibrary' 'd70da989be2d82179b58b81c104b46778f409c91'
    if (-not $SkipBuild) {
        Run-Dotnet @('build', "$src\Source\PackTools\PAKPack\PAKPack.csproj", '-c', 'Release', '-nologo', '-v', 'q', '-p:TargetFrameworkVersion=v4.8')
    }
}

# =============================================================================
# 5. Amicitia (TGE): reference source for CVM/ISO, AMD, RMD (RenderWare), TMX,
#    SPR, PAK. NO LICENSE FILE (all rights reserved by default) -> read-only
#    reference, not built, nothing copied into our code.
# =============================================================================
if (Step 'amicitia') {
    Clone-Pinned 'Amicitia' 'https://github.com/tge-was-taken/Amicitia' '6b6312af992d27cc8b45122480d5bb1b23aa4202' -Submodules | Out-Null
}

# =============================================================================
# 6. ps2sdk source (headers): AFL-2.0. Shallow clone at a pinned commit.
# =============================================================================
if (Step 'ps2sdk') {
    Clone-Pinned 'ps2sdk' 'https://github.com/ps2dev/ps2sdk' '329e2bb43287e16af16c4dde1c614e2662c24468' -Shallow | Out-Null
}

# =============================================================================
# 7. ps2dev v2.0.0 prebuilt Windows toolchain (EE/IOP/DVP gcc 15.2 + binutils +
#    ps2sdk + gsKit), built by ps2dev CI under MSYS2 MINGW32. The binaries are
#    32-bit and need MINGW32 runtime DLLs that ps2dev does not bundle; we fetch
#    the exact MSYS2 packages and drop their DLLs beside the executables.
#    Licenses: GCC/binutils GPL-3.0 (+ runtime exception), ps2sdk AFL-2.0,
#    gsKit AFL-2.0, newlib BSD-ish, MSYS2 runtime libs: see each package.
# =============================================================================
if (Step 'ps2dev') {
    $tgz = Fetch-File 'https://github.com/ps2dev/ps2dev/releases/download/v2.0.0/ps2dev-windows-latest.tar.gz' `
                      'ps2dev-v2.0.0-windows-latest.tar.gz' 'bab98ee210c62aa3bd98d9bdda2af3f92a628e6e3d63e4b52f243ae56e3eb4ce'   # publisher
    $dst = Join-Path $ThirdParty 'ps2dev'
    $gcc = Join-Path $dst 'ps2dev\ee\bin\mips64r5900el-ps2-elf-gcc.exe'
    if (-not (Test-Path $gcc)) {
        Fresh-Dir $dst | Out-Null
        # ps2dev/ps2sdk/ports/bin/bz* are symlinks; bsdtar cannot create them
        # without privilege, so exclude them (they are irrelevant bzip2 wrappers).
        & $Tar -xzf $tgz -C $dst --exclude 'ps2dev/ps2sdk/ports/bin/bunzip' --exclude 'ps2dev/ps2sdk/ports/bin/bzcat' `
               --exclude 'ps2dev/ps2sdk/ports/bin/bzcmp' --exclude 'ps2dev/ps2sdk/ports/bin/bzegrep' `
               --exclude 'ps2dev/ps2sdk/ports/bin/bzfgrep' --exclude 'ps2dev/ps2sdk/ports/bin/bzless'
        if ($LASTEXITCODE -ne 0) { throw "tar failed ($LASTEXITCODE) extracting ps2dev" }
    } else { Write-Host '  ps2dev already extracted' }

    # MSYS2 MINGW32 runtime DLLs. Digests recorded by us on 2026-10-18 (MSYS2 publishes GPG .sig files, not SHA-256).
    $msysBase = 'https://repo.msys2.org/mingw/mingw32/'
    $msysPkgs = @(
        @{ n='mingw-w64-i686-libiconv-1.19-1-any.pkg.tar.zst';                              s='12307416cfe45b6fbe1fb29c28594590bb59883856edf41b043d0daf684e4668' },
        @{ n='mingw-w64-i686-libwinpthread-git-12.0.0.r747.g1a99f8514-1-any.pkg.tar.zst';  s='98c3deccf54869f4b0c98fdb22fb73e88cabb7fba0fdba85bbb1b2437d788171' },
        @{ n='mingw-w64-i686-zstd-1.5.7-2-any.pkg.tar.zst';                                 s='e31d4194702b12f83b7b27b03fe4a68a5c2edc63dc4bd4689ab9d5a7bd8e5fff' },
        @{ n='mingw-w64-i686-gmp-6.3.0-2-any.pkg.tar.zst';                                  s='cb23f87b33c20ae2de9638145a56bffdddf01a2afce2cb6dc43753d4e27bc448' },
        @{ n='mingw-w64-i686-isl-0.28-1-any.pkg.tar.zst';                                   s='df526ad433d959e5910e0f49f0343c61c992d5e8a7b28e27ca2bd8ffdf07304c' },
        @{ n='mingw-w64-i686-mpc-1.4.1-1-any.pkg.tar.zst';                                  s='200e0a7612c2b667507a03d08b51f45e12db8bfc076fd5185f7c58f2c8a9acde' },
        @{ n='mingw-w64-i686-mpfr-4.2.2-3-any.pkg.tar.zst';                                 s='87cd116c4e4deb2fe89b713c58e6c123c0b415ffff97d13ab2465bbca316c33c' },
        @{ n='mingw-w64-i686-gcc-libs-15.2.0-14-any.pkg.tar.zst';                           s='e5d6036b6b258b9811ed0655456837d34f741f5d4ad4b819c580d95716801562' },
        @{ n='mingw-w64-i686-expat-2.9.0-1-any.pkg.tar.zst';                                s='51982a212b8624931a77f0ee351720bc0e113f563177b858a87884f58b89e5f4' },
        @{ n='mingw-w64-i686-xz-5.8.4-1-any.pkg.tar.zst';                                   s='b4517bb12a6fbf4f34d606dfdfed33bd2277eb2a2aade2a64365742580967b4d' },
        @{ n='mingw-w64-i686-termcap-1.3.1-8-any.pkg.tar.zst';                              s='0ca17704d8ca67424488ae85ec30af1d980c4de635e61933130789a48e136103' }
    )
    $pkgDir = Join-Path $Downloads 'msys2-mingw32'; New-Item -ItemType Directory -Force $pkgDir | Out-Null
    $stage  = Fresh-Dir (Join-Path $dst 'mingw32-runtime-stage')
    foreach ($p in $msysPkgs) {
        $f = Join-Path $pkgDir $p.n
        if (-not ((Test-Path $f) -and ((Get-Sha256 $f) -eq $p.s))) {
            Write-Host "  download $($msysBase)$($p.n)"
            Invoke-WebRequest -Uri ($msysBase + $p.n) -OutFile $f -UseBasicParsing
            $got = Get-Sha256 $f
            if ($got -ne $p.s) { Remove-Item $f -Force; throw "SHA-256 mismatch for $($p.n): got $got" }
        }
        # .pkg.tar.zst -> tar stream -> only mingw32/bin/*.dll
        cmd /c "`"$SevenZip`" x -so `"$f`" | `"$SevenZip`" x -si -ttar -y -o`"$stage`" mingw32/bin/*.dll" | Out-Null
    }
    # Three executable directories, each searched independently by the Windows
    # loader: the driver dir (gcc, binutils, gdb), cc1/collect2/lto1 under
    # libexec, and the target-prefixed as/ld that the driver actually invokes.
    $eeBin    = Join-Path $dst 'ps2dev\ee\bin'
    $libexec  = (Get-ChildItem (Join-Path $dst 'ps2dev\ee\libexec\gcc\mips64r5900el-ps2-elf') -Directory | Select-Object -First 1).FullName
    $tgtBin   = Join-Path $dst 'ps2dev\ee\mips64r5900el-ps2-elf\bin'
    $dlls = Get-ChildItem (Join-Path $stage 'mingw32\bin') -Filter *.dll
    foreach ($target in $eeBin, $libexec, $tgtBin) { Copy-Item $dlls.FullName $target -Force }
    Remove-Item -Recurse -Force $stage
    Write-Host "  installed $($dlls.Count) MINGW32 runtime DLLs into ee\bin, libexec\...\15.2.0 and mips64r5900el-ps2-elf\bin"
    & $gcc --version | Select-Object -First 1
}

# =============================================================================
# 8. PCSX2 v2.8.2 (Qt, Windows x64, portable 7z). GPL-3.0.
#    REQUIRES A PS2 BIOS DUMPED FROM THE USER'S OWN CONSOLE -> put it in
#    tools/third_party/pcsx2/bios/. Never downloaded here.
# =============================================================================
if (Step 'pcsx2') {
    $a = Fetch-File 'https://github.com/PCSX2/pcsx2/releases/download/v2.8.2/pcsx2-v2.8.2-windows-x64-Qt.7z' `
                    'pcsx2-v2.8.2-windows-x64-Qt.7z' '7dfc829ca1994cc1045ac49f05e39b6cf968b72e6a374c40e05c2a2b4ac200b4'   # publisher
    $dst = Join-Path $ThirdParty 'pcsx2'
    if (-not (Test-Path (Join-Path $dst 'pcsx2-qt.exe'))) {
        Fresh-Dir $dst | Out-Null
        & $SevenZip x -y "-o$dst" $a | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "7z failed extracting PCSX2" }
    } else { Write-Host '  PCSX2 already extracted' }
    # portable.txt keeps inis/bios/memcards/dumps under tools/third_party/pcsx2 instead of %USERPROFILE%\Documents\PCSX2.
    $marker = Join-Path $dst 'portable.txt'; if (-not (Test-Path $marker)) { New-Item -ItemType File $marker | Out-Null }
    New-Item -ItemType Directory -Force (Join-Path $dst 'bios') | Out-Null
}

# =============================================================================
# 9. vgmstream r2117 (win64 CLI): ADX/AHX/ADS inspection + decode. ISC-style license (COPYING).
# =============================================================================
if (Step 'vgmstream') {
    $a = Fetch-File 'https://github.com/vgmstream/vgmstream/releases/download/r2117/vgmstream-win64.zip' `
                    'vgmstream-r2117-win64.zip' '6c4a8a3813864fefed081bbd337dbc0ad93bf88e0b92f5db98d7ab258b22dc6c'   # publisher
    $dst = Fresh-Dir (Join-Path $Bin 'vgmstream')
    Expand-Archive -Force $a $dst
}

# =============================================================================
# 10. ghidra-emotionengine-reloaded v2.1.38 for Ghidra 12.1.4 (Apache-2.0):
#     R5900 + VU0/VU1 SLEIGH for the Ghidra we already have. Secondary surface
#     next to IDA; the zip is what Ghidra's "Install Extensions" dialog consumes.
# =============================================================================
if (Step 'ghidra-ee') {
    $a = Fetch-File 'https://github.com/chaoticgd/ghidra-emotionengine-reloaded/releases/download/v2.1.38/ghidra_12.1.4_PUBLIC_20261004_ghidra-emotionengine-reloaded.zip' `
                    'ghidra_12.1.4_PUBLIC_20261004_ghidra-emotionengine-reloaded.zip' 'e389ff3e921d9f7d4db2ece9906f808545ce4ff519d9e25a019b72ea509f240b'   # publisher
    $dst = Fresh-Dir (Join-Path $ThirdParty 'ghidra-emotionengine-reloaded')
    Expand-Archive -Force $a $dst
}

# =============================================================================
# 11. OPT-IN ONLY (-IncludeUnlicensedSigs): community PS2 SDK FLIRT signatures
#     by Amorri40 (with pool7), ASSEMBLERgames thread "[Reverse Engineering]
#     PS2 Signature Files for IDA Pro" (2018-02-11). NO LICENSE; derived from
#     Sony's proprietary libsce* libraries (plus SN Systems libsn and Metrowerks
#     CodeWarrior runtimes) -> private use on this machine only (ADR-0007).
#     assemblergames.com is offline and the assemblergames.org mirror 404s on
#     attachments, so the pinned sources are Wayback Machine raw captures
#     ("id_" URLs) of the original forum attachments. Everything lands in the
#     gitignored tools/downloads/, tools/third_party/ida-sigs/ and IDA's *user*
#     signature directory, never Program Files. A default run never enters
#     this block; -Only ida-sigs without the switch is a no-op.
#     Note: the pack's .sig headers carry processor id 0x00, exactly like
#     Hex-Rays' own sig/mips/psx.sig, so the header byte is not checked; the
#     pattern bytes were verified as little-endian MIPS (docs/TOOLS.md).
# =============================================================================
if ($IncludeUnlicensedSigs -and (Step 'ida-sigs')) {
    $wb  = 'https://web.archive.org/web/'
    $att = 'id_/https://assemblergames.com/attachments/'
    # n = local archive name; c = Wayback capture timestamp; a = attachment path;
    # s = archive SHA-256 (recorded 2026-10-18); sig = .sig inside the archive; h = .sig SHA-256;
    # install = copy into the IDA user sig dir. PS2SDK_2.0.0 is fetched and verified but NOT
    # installed: 74% of its patterns are x86 host-toolchain libraries (libbfd/tcl/tk/readline)
    # and it contains no Sony EE library at all (only libgcc/libstdc++).
    $sigSets = @(
        @{ n='ps2sdk_3-0-3.zip';          c='20180401075846'; a='ps2sdk_3-0-3-zip.30724/';          s='430ee82c1bad2d5da3dd275c836bf03f44cd1b5cadf3ee884a04bd34f0fcf212'; sig='generated\PS2SDK_3.0.3\PS2SDK_3.0.3.sig';                           h='5605f6b20a3cfa85ac206c4650a7ccf593adb4a4bd73da3c5f6b8b29b76c3f36'; install=$true  },
        @{ n='ps2sdk_3-0-2.zip';          c='20180401075841'; a='ps2sdk_3-0-2-zip.30723/';          s='e28e63e137c800d7ca40a006481f401c0a4aa4657fc35da04c4aea3aa3d48041'; sig='generated\PS2SDK_3.0.2\PS2SDK_3.0.2.sig';                           h='b61cccdb6d6661dcac59b771f6d4f1add4293059ebd6d50342da02fab679b20b'; install=$true  },
        @{ n='ps2sdk_3-0-0.zip';          c='20180401075845'; a='ps2sdk_3-0-0-zip.30722/';          s='08d5781e6ef76f6cdaa70b701b321b3f88c0600342bcfe8daef515b080f93d62'; sig='generated\PS2SDK_3.0.0\PS2SDK_3.0.0.sig';                           h='8af4e9861a4be621cbbe8ff99a2983e53d5c9efc8658913d30744546e0722588'; install=$true  },
        @{ n='ps2sdk_2-4-2.zip';          c='20180401075842'; a='ps2sdk_2-4-2-zip.30721/';          s='f940dab6d4eadbb5eed6b585b6cb699a21c3e7061b71ee6b0ce416805eca25a4'; sig='generated\PS2SDK_2.4.2\PS2SDK_2.4.2.sig';                           h='7dd6dc2c0cae56b1afd8dc02ce216314a64ec555ae328314c740cbc810418272'; install=$true  },
        @{ n='ps2sdk_2-0-0.zip';          c='20180401075849'; a='ps2sdk_2-0-0-zip.30720/';          s='2c589f647776aa35866a5768e19fcb10422316ac01c5eb9a50def0d95569ae34'; sig='generated\PS2SDK_2.0.0\PS2SDK_2.0.0.sig';                           h='d334274330dc91c0c561c2f8fb22f0b5b40724b6b2104b255fe9652b1e65403a'; install=$false },
        @{ n='ps2sdk_1-0-0.zip';          c='20180401075845'; a='ps2sdk_1-0-0-zip.30719/';          s='43fa000d45d72eb3b361e591b1e4067ac2d9eb2c197bd75ad0c04ecdaf30daa6'; sig='generated\PS2SDK_1.0.0\PS2SDK_1.0.0.sig';                           h='8746db3b3007c92d4d37fef7b7a6a773a6e8a828aac72520759a952f525d02b9'; install=$true  },
        @{ n='libsn.zip';                 c='20191109100357'; a='libsn-zip.30726/';                 s='b477b135fcaba5fba498c7a0015f3c1b711bc9c2dedcebb14d46627d52d3bfc0'; sig='generated\libsn\libsn.sig';                                         h='30de7efe25add58b51cc6b51e6af5c89738ac369fc30174f1a9c728fbaab526c'; install=$true  },
        @{ n='metrowerkscodewarrior.zip'; c='20191109100353'; a='metrowerkscodewarrior-zip.30725/'; s='e7556f918d54e435f7da0a9ae4a70f417246caeff6bc84155fd099b73b15ef56'; sig='generated\MetrowerksCodewarrior\MetrowerksCodewarrior.sig';         h='452828a10519ea64cf52394bd62c5ed9977673dec9694ee99011172596d55ffe'; install=$true  }
    )
    New-Item -ItemType Directory -Force (Join-Path $Downloads 'ida-sigs-amorri40\wayback') | Out-Null
    $extRoot = Join-Path $ThirdParty 'ida-sigs'; New-Item -ItemType Directory -Force $extRoot | Out-Null
    foreach ($scope in 'User', 'Machine') {
        $v = [Environment]::GetEnvironmentVariable('IDAUSR', $scope)
        if ($v) { Write-Warning "IDAUSR is set at $scope scope ('$v'); IDA reads sig/mips from there, not from %APPDATA%\Hex-Rays\IDA Pro" }
    }
    $sigDir = Join-Path $env:APPDATA 'Hex-Rays\IDA Pro\sig\mips'; New-Item -ItemType Directory -Force $sigDir | Out-Null
    $manifest = @(
        '# PS2 SDK FLIRT signatures for IDA (processor module mips, r5900l) - UNLICENSED community pack.',
        "# Author: Amorri40 (with pool7), ASSEMBLERgames thread '[Reverse Engineering] PS2 Signature Files for IDA Pro', 2018-02-11.",
        '# Derived from Sony''s proprietary PS2 SDK libraries (and SN Systems libsn / Metrowerks CodeWarrior runtimes).',
        '# No license granted by the author or Sony. Private use on this machine only (p3fes-port docs/DECISIONS.md ADR-0007).',
        '# NEVER commit, package or redistribute. Reproduce with: tools/fetch_tools.ps1 -IncludeUnlicensedSigs. Details: docs/TOOLS.md.',
        "# Installed $(Get-Date -Format yyyy-MM-dd). Collision resolution (.exc) and pattern (.pat) files: tools/third_party/ida-sigs/<set>/generated/.",
        '# Withheld (verified, not installed): PS2SDK_2.0.0.sig - 74% of its patterns are x86 host-toolchain libraries, no Sony EE libs.',
        '#',
        "# installed file`tsha256 (.sig)`tsource archive (Wayback raw capture of the original forum attachment)`tarchive sha256"
    )
    foreach ($set in $sigSets) {
        $zip = Fetch-File ($wb + $set.c + $att + $set.a) ('ida-sigs-amorri40\wayback\' + $set.n) $set.s
        $out = Fresh-Dir (Join-Path $extRoot ($set.n -replace '\.zip$', ''))
        Expand-Archive -Force $zip $out
        $sig = Join-Path $out $set.sig
        $got = Get-Sha256 $sig
        if ($got -ne $set.h) { throw "SHA-256 mismatch for $($set.sig): got $got" }
        $magic = [Text.Encoding]::ASCII.GetString([IO.File]::ReadAllBytes($sig), 0, 6)
        if ($magic -ne 'IDASGN') { throw "$($set.sig): not a FLIRT signature file (magic '$magic')" }
        $leaf = Split-Path $sig -Leaf
        if ($set.install) {
            Copy-Item $sig $sigDir -Force
            $manifest += "$leaf`t$got`t$wb$($set.c)$att$($set.a) ($($set.n))`t$($set.s)"
            Write-Host "  installed $leaf"
        } else {
            Write-Host "  verified, NOT installed (x86 host-library content): $leaf"
        }
    }
    Set-Content -Path (Join-Path $sigDir 'MANIFEST.txt') -Value $manifest -Encoding ASCII
    Write-Host "  -> $sigDir (IDA: File > Load file > FLIRT signature file, or the Signatures window)"
}

Write-Host "`nDone. See docs/TOOLS.md." -ForegroundColor Green
