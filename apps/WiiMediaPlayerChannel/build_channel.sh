#!/bin/bash

echo "========================================"
echo "Wii Media Player Channel Builder"
echo "========================================"
echo

# Check if devkitPPC is installed
if [ -z "$DEVKITPPC" ]; then
    echo "ERROR: devkitPPC is not installed or not in PATH"
    echo "Please install devkitPPC and add it to your PATH"
    echo "Download from: https://devkitpro.org/"
    exit 1
fi

echo "Building Wii Media Player application..."
cd ../WiiMediaPlayer
make clean
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to clean Wii Media Player"
    exit 1
fi

make
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to build Wii Media Player"
    exit 1
fi

echo
echo "Building channel..."
cd ../WiiMediaPlayerChannel
make clean
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to clean channel"
    exit 1
fi

make
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to build channel"
    exit 1
fi

echo
echo "========================================"
echo "Channel build completed successfully!"
echo "========================================"
echo
echo "Next steps:"
echo "1. Create a 128x128 icon.png for your channel"
echo "2. Use CustomizeMii to create banner.bin"
echo "3. Use CustomizeMii or ShowMiiWads to create the final WAD"
echo "4. Install the WAD on your Wii using a WAD manager"
echo
echo "Files created:"
echo "- build/boot.dol (main application)"
echo "- 00000000.app (channel application file)"
echo
