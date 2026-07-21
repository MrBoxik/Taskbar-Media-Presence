[CmdletBinding()]
param()

$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectFile = Join-Path $projectRoot 'MusicBeeVolumeBridge.csproj'
$sdkDirectory = Join-Path $projectRoot 'obj\official-sdk'
$sdkPath = Join-Path $sdkDirectory 'MusicBeeInterface.cs'
$outputDirectory = Join-Path (Split-Path -Parent $projectRoot) 'build\musicbee'

New-Item -ItemType Directory -Path $sdkDirectory -Force | Out-Null
New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null

# MusicBee publishes this interface specifically as its plugin SDK. Keeping it
# outside our source avoids copying any third-party implementation into the
# bridge while ensuring the build uses MusicBee's current official contract.
Invoke-WebRequest -UseBasicParsing `
    -Uri 'https://www.getmusicbee.com/download/plugins/MusicBeeInterface.cs' `
    -OutFile $sdkPath

dotnet build $projectFile `
    --configuration Release `
    --property:MusicBeeSdkPath="$sdkPath"
if ($LASTEXITCODE -ne 0) {
    throw "MusicBee volume bridge compilation failed with exit code $LASTEXITCODE"
}

$builtDll = Join-Path $projectRoot 'bin\Release\net48\mb_TaskbarVolumeBridge.dll'
$targetDll = Join-Path $outputDirectory 'mb_TaskbarVolumeBridge.dll'
Copy-Item -LiteralPath $builtDll -Destination $targetDll -Force

$artifact = Get-Item -LiteralPath $targetDll
Write-Host "Built $($artifact.FullName) ($($artifact.Length) bytes)"
