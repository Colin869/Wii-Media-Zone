# HelloWii - Wii Homebrew Application

A simple "Hello World" style homebrew application for the Nintendo Wii that demonstrates basic graphics, input handling, and Wii development concepts.

## Features

- Basic video initialization and display
- Wii Remote input handling
- Simple graphics rendering
- Console output for debugging
- Proper Wii homebrew structure

## Requirements

To build this application, you need:

1. **devkitPPC** - The PowerPC development kit
2. **libogc** - The Open GameCube/Wii library
3. **A Wii with homebrew channel** - To run the application

## Building

1. Make sure you have devkitPPC installed and configured
2. Set the `DEVKITPRO` environment variable to point to your devkitPPC installation
3. Run the build command:

```bash
make
```

This will create:
- `HelloWii.elf` - The ELF executable
- `HelloWii.dol` - The DOL file ready for Wii

## Installation

1. Copy the `HelloWii.dol` file to your SD card
2. Place it in the directory structure: `SD:/apps/HelloWii/boot.dol`
3. Copy the `meta.xml` file to the same directory
4. Insert the SD card into your Wii
5. Launch the Homebrew Channel
6. Select "HelloWii" from the application list

## Controls

- **A Button**: Change rectangle color
- **B Button**: Exit application
- **HOME Button**: Return to Wii menu

## Project Structure

```
HelloWii/
├── source/
│   └── main.c          # Main application source
├── meta.xml            # Application metadata
├── Makefile            # Build configuration
└── README.md           # This file
```

## Development Notes

This is a basic example that demonstrates:
- Wii video system initialization
- Frame buffer management
- Wii Remote input handling
- Basic graphics operations
- Proper application structure

For more advanced development, consider:
- Using GX graphics library for better graphics
- Adding proper font rendering
- Implementing sound support
- Adding file I/O operations
- Using the Wii's hardware features

## Troubleshooting

If the application doesn't build:
1. Check that devkitPPC is properly installed
2. Verify the `DEVKITPRO` environment variable is set
3. Ensure all required libraries are installed

If the application doesn't run on Wii:
1. Make sure your Wii has the Homebrew Channel installed
2. Verify the file structure on the SD card is correct
3. Check that the DOL file is not corrupted

## License

This is a basic example application. Feel free to modify and use as a starting point for your own Wii homebrew projects.
