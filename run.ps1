# Настраиваем PowerShell на работу с UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# Добавляем OpenCV в PATH
$env:PATH += ";C:\opencv\build\x64\vc16\bin"

# Создаем build при необходимости
if (-not (Test-Path "build")) {
    Write-Host "build отсутствует - создаем."
    mkdir build | Out-Null
}

# Переходим в build
cd build

# Конфигурируем проект
Write-Host "Конфигурирование CMake..."
cmake ..

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "Ошибка конфигурации CMake!"
    exit 1
}

# Собираем проект
Write-Host "Сборка проекта..."
cmake --build . --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "Ошибка сборки!"
    exit 1
}

# Запускаем программу
Write-Host ""
Write-Host "Запуск программы!"
.\Release\PSMVA.exe