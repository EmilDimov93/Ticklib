Write-Host "Building..." -ForegroundColor Blue
$buildOutput = cmake --build build --config Release 2>&1
$issues = $buildOutput | Select-String -Pattern "error","warning" -SimpleMatch

if ($issues.Count -eq 0) {
    Write-Host "Running..." -ForegroundColor Green
    .\build\Release\Ticklib.exe
    Write-Host ""
    Write-Host "Finished" -ForegroundColor Magenta
} else {
    Write-Host "Build failed with warnings or errors:" -ForegroundColor Red
    $issues | ForEach-Object { Write-Host $_ -ForegroundColor Yellow }
}