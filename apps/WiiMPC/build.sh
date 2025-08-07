#!/bin/bash

echo "========================================"
echo "WiiMPC Builder"
echo "========================================"
echo

# Check if devkitPPC is installed
if [ -z "$DEVKITPPC" ]; then
    echo "ERROR: devkitPPC is not installed or not in PATH"
    echo "Please install devkitPPC and add it to your PATH"
    echo "Download from: https://devkitpro.org/"
    exit 1
fi

echo "Building WiiMPC..."
make clean
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to clean"
    exit 1
fi

make
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to build WiiMPC"
    exit 1
fi

echo
echo "========================================"
echo "WiiMPC build completed successfully!"
echo "========================================"
echo
echo "Files created:"
echo "- WiiMPC.dol (main application)"
echo "- WiiMPC.elf (debug version)"
echo
echo "Next steps:"
echo "1. Copy WiiMPC.dol to your SD card"
echo "2. Place it in SD:/apps/WiiMPC/"
echo "3. Run from Homebrew Channel"
echo
