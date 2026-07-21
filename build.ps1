[CmdletBinding()]
param(
    [ValidateSet('all', '64', '32')]
    [string]$Architecture = 'all'
)

$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$sourcePath = Join-Path $projectRoot 'taskbar-media-presence.wh.cpp'
$windhawkRoot = Join-Path $env:ProgramFiles 'Windhawk'
$compilerRoot = Join-Path $windhawkRoot 'Compiler'
$compilerPath = Join-Path $compilerRoot 'bin\clang++.exe'
$windhawkIni = Join-Path $windhawkRoot 'windhawk.ini'

if (-not (Test-Path -LiteralPath $sourcePath)) {
    throw "Source file not found: $sourcePath"
}
if (-not (Test-Path -LiteralPath $compilerPath)) {
    throw "Windhawk compiler not found: $compilerPath"
}

$engineRelativePath = Get-Content -LiteralPath $windhawkIni |
    Where-Object { $_ -like 'EnginePath=*' } |
    Select-Object -First 1
if (-not $engineRelativePath) {
    throw "EnginePath is missing from $windhawkIni"
}
$engineRelativePath = $engineRelativePath.Substring('EnginePath='.Length)
$engineRoot = Join-Path $windhawkRoot $engineRelativePath

$targets = @(
    @{ Folder = '64'; Triple = 'x86_64-w64-mingw32' },
    @{ Folder = '32'; Triple = 'i686-w64-mingw32' }
)
if ($Architecture -ne 'all') {
    $targets = $targets | Where-Object { $_.Folder -eq $Architecture }
}

Push-Location $compilerRoot
try {
    foreach ($target in $targets) {
        $outputDirectory = Join-Path $projectRoot (Join-Path 'build' $target.Folder)
        New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null
        $outputPath = Join-Path $outputDirectory 'taskbar-media-presence_0.10.1.dll'
        $engineLibrary = Join-Path $engineRoot (Join-Path $target.Folder 'windhawk.lib')

        $compilerArgs = @(
            '-std=c++23', '-O2', '-shared',
            '-DUNICODE', '-D_UNICODE',
            '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00',
            '-D_WIN32_IE=0x0A00', '-DNTDDI_VERSION=0x0A000008',
            '-D__USE_MINGW_ANSI_STDIO=0', '-DWH_MOD',
            '-DWH_MOD_ID=L"taskbar-media-presence"',
            '-DWH_MOD_VERSION=L"0.10.1"',
            '-DWH_WINDHAWK_VERSION=0x01070300',
            $engineLibrary,
            '-x', 'c++', $sourcePath,
            '-include', 'windhawk_api.h',
            '-target', $target.Triple,
            '-Wl,--export-all-symbols',
            '-o', $outputPath,
            '-lole32', '-loleaut32', '-lruntimeobject', '-lversion',
            '-luuid', '-luser32', '-lwindowsapp', '-lshell32', '-lgdi32',
            '-lshlwapi', '-lwindowscodecs', '-ldwmapi', '-lshcore', '-lksuser',
            '-lcomctl32', '-lwinhttp'
        )

        & $compilerPath @compilerArgs
        if ($LASTEXITCODE -ne 0) {
            throw "Compilation failed for $($target.Triple) with exit code $LASTEXITCODE"
        }

        $artifact = Get-Item -LiteralPath $outputPath
        Write-Host "Built $($artifact.FullName) ($($artifact.Length) bytes)"
    }
}
finally {
    Pop-Location
}
