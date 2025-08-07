@echo off
echo ========================================
echo WiiMPC Builder
echo ========================================
echo.

REM Check if devkitPPC is installed
if not defined DEVKITPPC (
    echo ERROR: devkitPPC is not installed or not in PATH
    echo Please install devkitPPC and add it to your PATH
    echo Download from: https://devkitpro.org/
    pause
    exit /b 1
)

echo Building WiiMPC...
make clean
if errorlevel 1 (
    echo ERROR: Failed to clean
    pause
    exit /b 1
)

make
if errorlevel 1 (
    echo ERROR: Failed to build WiiMPC
    pause
    exit /b 1
)

echo.
echo ========================================
echo WiiMPC build completed successfully!
echo ========================================
echo.
echo Files created:
echo - WiiMPC.dol (main application)
echo - WiiMPC.elf (debug version)
echo.
echo Next steps:
echo 1. Copy WiiMPC.dol to your SD card
echo 2. Place it in SD:/apps/WiiMPC/
echo 3. Run from Homebrew Channel
echo.
pause
