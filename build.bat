@echo off

gcc *.c */*.c -o wardogz.exe

if %errorlevel% neq 0 (
    echo.
    echo BUILD FAILED
    pause
    exit /b
)

echo.
echo BUILD SUCCESS
echo.

wardogz.exe

pause