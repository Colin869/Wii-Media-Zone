# Wii Media Player Channel

A professional Wii menu channel for the Wii Media Player application. This channel provides easy access to your media player directly from the Wii's system menu.

## Features

- **System Menu Integration**: Appears as a proper channel on your Wii's main menu
- **Professional Banner**: Animated banner with media player branding
- **Custom Icon**: 128x128 pixel channel icon
- **Easy Installation**: Simple WAD installation process
- **Full Functionality**: All features from the standalone media player

## Requirements

### Development Requirements
- devkitPPC (PowerPC development kit)
- libogc (Wii development libraries)
- CustomizeMii or ShowMiiWads (for WAD creation)
- Image editing software (for creating banner and icon)

### Installation Requirements
- Wii console with Homebrew Channel
- WAD Manager (like Wii Mod Lite, YAWMM, or Multi-Mod Manager)
- SD card for transferring the WAD file

## Building the Channel

### Step 1: Build the Application
First, ensure your Wii Media Player application is built:

```bash
cd apps/WiiMediaPlayer
make clean
make
```

### Step 2: Build the Channel
Navigate to the channel directory and build:

```bash
cd apps/WiiMediaPlayerChannel
make clean
make
```

This will:
- Compile the application from the source directory
- Create the `boot.dol` file
- Prepare the channel structure

### Step 3: Create Channel Assets

#### Channel Icon
Replace `icon.png` with a 128x128 pixel PNG image:
- Should represent media playback
- Use bright, appealing colors
- Keep it simple and recognizable

#### Channel Banner
Create a banner using CustomizeMii:
1. Open CustomizeMii
2. Create a new channel project
3. Import your `boot.dol` file
4. Design a 170x42 pixel banner
5. Add animation if desired
6. Export as `banner.bin`

### Step 4: Create the WAD File

#### Using CustomizeMii (Recommended)
1. Open CustomizeMii
2. Create a new channel project
3. Set the following:
   - Title ID: `000100014D454450`
   - Channel Name: "Wii Media Player"
   - Import your `boot.dol` as the main application
   - Import your `banner.bin` for the banner
   - Import your `icon.png` for the icon
   - Set the meta.xml content
4. Build the WAD file

#### Using ShowMiiWads
1. Open ShowMiiWads
2. Create a new channel
3. Import the required files:
   - `00000000.app` (your boot.dol)
   - `banner.bin`
   - `icon.png`
   - `meta.xml`
4. Set the title ID and other metadata
5. Export as WAD

## Installation

### Method 1: WAD Manager Installation
1. Copy the generated `WiiMediaPlayer.wad` to your SD card
2. Insert the SD card into your Wii
3. Launch a WAD Manager from the Homebrew Channel
4. Navigate to the WAD file and install it
5. The channel will appear on your Wii's main menu

### Method 2: USB Installation
1. Copy the WAD file to a USB drive
2. Use a USB-compatible WAD manager
3. Install the channel from the USB drive

## Channel Information

- **Title ID**: `000100014D454450` (Wii Media Player - MEDP)
- **Channel Name**: Wii Media Player
- **Version**: 1.0
- **Region**: Japanese (JPN)
- **Size**: Approximately 2-5 MB (depending on features)

## Usage

Once installed, the channel will appear on your Wii's main menu. Simply click on it to launch the media player. The channel provides the same functionality as the standalone application:

- **File Browser**: Navigate and play media files
- **Playlist Support**: M3U/M3U8 playlist management
- **Video Effects**: Apply filters and effects
- **Bookmarks**: Save and jump to specific positions
- **Settings**: Configure playback options
- **Advanced Controls**: Slow motion, fast forward, screenshots

## Troubleshooting

### Channel Won't Install
- Ensure your Wii has the Homebrew Channel installed
- Try a different WAD manager
- Check that the WAD file is not corrupted
- Verify your Wii's system menu version compatibility

### Channel Crashes on Launch
- Rebuild the application with debug symbols
- Check that all required libraries are linked
- Verify the boot.dol file is properly compiled
- Test the standalone application first

### Banner/Icon Not Displaying
- Ensure banner.bin is properly created
- Check icon.png dimensions (128x128)
- Verify file formats are correct
- Recreate the WAD file

### Performance Issues
- Optimize the application code
- Reduce memory usage
- Check for memory leaks
- Profile the application

## Development Notes

### File Structure
```
WiiMediaPlayerChannel/
├── meta.xml              # Channel metadata
├── icon.png              # Channel icon (128x128)
├── banner.bin            # Channel banner
├── 00000000.app          # Main application (boot.dol)
├── title.tik             # Title ticket (generated)
├── title.tmd             # Title metadata (generated)
├── channel_config.txt    # Configuration file
├── Makefile              # Build configuration
└── README.md             # This file
```

### Customization
- Modify `meta.xml` to change channel information
- Update `channel_config.txt` for different settings
- Create custom banners and icons
- Adjust the title ID if needed

## Legal Notice

This channel is for educational and personal use only. Ensure you comply with Nintendo's terms of service and local laws when installing homebrew software on your Wii console.

## Support

For issues and questions:
1. Check the troubleshooting section above
2. Review the main Wii Media Player documentation
3. Consult Wii homebrew development resources
4. Test with the standalone application first

## Version History

- **v1.0**: Initial channel release with full media player functionality
