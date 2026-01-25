@echo off

echo ===============================
echo Build Project
echo ===============================

if not exist build mkdir build
cd build

echo Configurando com CMake...
cmake .. -G "MinGW Makefiles"

if errorlevel 1 (
    echo ERRO no cmake
    pause
    exit /b
)

echo Compilando...
mingw32-make

if errorlevel 1 (
    echo ERRO na compilacao
    pause
    exit /b
)

echo ===============================
echo Executando teste.exe
echo ===============================

teste.exe
pause
