@echo off
setlocal

gcc -std=c11 -Wall -Wextra *.c enemies/*.c stages/*.c dialogue/*.c sparring/*.c sparring/characters/*.c arena/*.c -o wardogz.exe

if errorlevel 1 (
    echo.
    echo BUILD FAILED
    pause
    exit /b 1
)

echo.
echo BUILD SUCCESS
echo.

wardogz.exe

pause
endlocal