@echo off
echo ========================================
echo Wii Media Player Channel Builder
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

echo Building Wii Media Player application...
cd ..\WiiMediaPlayer
make clean
if errorlevel 1 (
    echo ERROR: Failed to clean Wii Media Player
    pause
    exit /b 1
)

make
if errorlevel 1 (
    echo ERROR: Failed to build Wii Media Player
    pause
    exit /b 1
)

echo.
echo Building channel...
cd ..\WiiMediaPlayerChannel
make clean
if errorlevel 1 (
    echo ERROR: Failed to clean channel
    pause
    exit /b 1
)

make
if errorlevel 1 (
    echo ERROR: Failed to build channel
    pause
    exit /b 1
)

echo.
echo ========================================
echo Channel build completed successfully!
echo ========================================
echo.
echo Next steps:
echo 1. Create a 128x128 icon.png for your channel
echo 2. Use CustomizeMii to create banner.bin
echo 3. Use CustomizeMii or ShowMiiWads to create the final WAD
echo 4. Install the WAD on your Wii using a WAD manager
echo.
echo Files created:
echo - build/boot.dol (main application)
echo - 00000000.app (channel application file)
echo.
pause
