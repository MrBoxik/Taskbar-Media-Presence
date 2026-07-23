[CmdletBinding()]
param(
    [string]$MusicBeeSdkPath
)

$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectFile = Join-Path $projectRoot 'MusicBeeVolumeBridge.csproj'
$sdkDirectory = Join-Path $projectRoot 'obj\official-sdk'
$downloadedSdkPath = Join-Path $sdkDirectory 'MusicBeeInterface.cs'
$outputDirectory = Join-Path (Split-Path -Parent $projectRoot) 'build\musicbee'
$expectedMusicBeeSdkSha256 = '28C7CC54278BA8ABC7DB288F222CC487AAB19B23AB993222DD3E29AB09BC26A8'
$targetDll = Join-Path $outputDirectory 'mb_TaskbarMediaPresence.dll'
$builtDll = Join-Path $projectRoot 'bin\Release\net48\mb_TaskbarMediaPresence.dll'

# Any failed invocation must leave no old DLL looking like a fresh release.
Remove-Item -LiteralPath $targetDll -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath $builtDll -Force -ErrorAction SilentlyContinue

if ([string]::IsNullOrWhiteSpace($MusicBeeSdkPath)) {
    New-Item -ItemType Directory -Path $sdkDirectory -Force | Out-Null
    # This is MusicBee's official plugin contract, not another plugin's source.
    $downloadPath = "$downloadedSdkPath.download"
    Remove-Item -LiteralPath $downloadPath -Force -ErrorAction SilentlyContinue
    try {
        Invoke-WebRequest -UseBasicParsing `
            -Uri 'https://www.getmusicbee.com/download/plugins/MusicBeeInterface.cs' `
            -OutFile $downloadPath

        $downloadHash = (Get-FileHash -LiteralPath $downloadPath -Algorithm SHA256).Hash
        if ($downloadHash -ne $expectedMusicBeeSdkSha256) {
            throw "The downloaded MusicBeeInterface.cs SHA-256 was $downloadHash, expected $expectedMusicBeeSdkSha256. The official contract may have changed; review it and update the pinned hash intentionally before building."
        }

        Move-Item -LiteralPath $downloadPath -Destination $downloadedSdkPath -Force
    }
    finally {
        Remove-Item -LiteralPath $downloadPath -Force -ErrorAction SilentlyContinue
    }
    $MusicBeeSdkPath = $downloadedSdkPath
}

$MusicBeeSdkPath = (Resolve-Path -LiteralPath $MusicBeeSdkPath).Path
$sdkHash = (Get-FileHash -LiteralPath $MusicBeeSdkPath -Algorithm SHA256).Hash
if ($sdkHash -ne $expectedMusicBeeSdkSha256) {
    throw "MusicBeeInterface.cs SHA-256 was $sdkHash, expected $expectedMusicBeeSdkSha256. Refusing to compile against an unreviewed plugin contract."
}

$windowsKitsRoot = Join-Path ${env:ProgramFiles(x86)} 'Windows Kits\10\UnionMetadata'
$windowsWinMd = Get-ChildItem -LiteralPath $windowsKitsRoot -Recurse -Filter Windows.winmd -File |
    Where-Object { $_.FullName -notmatch '[\\/]Facade[\\/]' } |
    Sort-Object { try { [version]$_.Directory.Name } catch { [version]'0.0' } } -Descending |
    Select-Object -First 1
if (-not $windowsWinMd) {
    throw 'Windows 10/11 SDK metadata (Windows.winmd) was not found. Install a Windows SDK and retry.'
}

$windowsRuntimeCandidates = @(
    (Join-Path $env:WINDIR 'Microsoft.NET\Framework\v4.0.30319\System.Runtime.WindowsRuntime.dll'),
    (Join-Path $env:WINDIR 'Microsoft.NET\Framework64\v4.0.30319\System.Runtime.WindowsRuntime.dll')
)
$windowsRuntimePath = $windowsRuntimeCandidates | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1
if (-not $windowsRuntimePath) {
    throw 'System.Runtime.WindowsRuntime.dll was not found. Install .NET Framework 4.8 and retry.'
}

New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null
$obsoleteArtifact = Join-Path $outputDirectory 'mb_TaskbarVolumeBridge.dll'
if (Test-Path -LiteralPath $obsoleteArtifact) {
    Remove-Item -LiteralPath $obsoleteArtifact -Force
}

dotnet build $projectFile `
    --configuration Release `
    --property:MusicBeeSdkPath="$MusicBeeSdkPath" `
    --property:WindowsWinMdPath="$($windowsWinMd.FullName)" `
    --property:WindowsRuntimePath="$windowsRuntimePath"
if ($LASTEXITCODE -ne 0) {
    throw "MusicBee companion compilation failed with exit code $LASTEXITCODE"
}

if (-not (Test-Path -LiteralPath $builtDll)) {
    throw "MusicBee companion compilation reported success but did not create $builtDll"
}
Copy-Item -LiteralPath $builtDll -Destination $targetDll -Force

$artifact = Get-Item -LiteralPath $targetDll
$hash = (Get-FileHash -LiteralPath $targetDll -Algorithm SHA256).Hash
Write-Host "Verified MusicBeeInterface.cs SHA256 $sdkHash"
Write-Host "Built $($artifact.FullName) ($($artifact.Length) bytes)"
Write-Host "SHA256 $hash"
