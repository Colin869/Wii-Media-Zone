@echo off
echo ========================================
echo Japanese Wii Media Player Channel Builder
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

echo Building Wii Media Player for Japanese Wii...
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
echo Building Japanese Wii channel...
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
echo Japanese Wii Channel build completed!
echo ========================================
echo.
echo Japanese Wii Specific Settings:
echo - Region: JPN (Japanese)
echo - Title ID: 000100014D454450
echo - Japanese text support enabled
echo - Japanese filename support enabled
echo.
echo Next steps for Japanese Wii:
echo 1. Create a 128x128 icon.png for your channel
echo 2. Use CustomizeMii to create banner.bin
echo 3. Set region to JPN in CustomizeMii
echo 4. Use CustomizeMii or ShowMiiWads to create the final WAD
echo 5. Install the WAD on your Japanese Wii using a WAD manager
echo.
echo Files created:
echo - build/boot.dol (Japanese-compatible application)
echo - 00000000.app (channel application file)
echo - japanese_config.txt (Japanese Wii settings)
echo.
echo IMPORTANT: Make sure to set region to JPN when creating the WAD!
echo.
pause
