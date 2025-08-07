# Wii Media Player Channel Creation Guide

This guide will walk you through creating a Wii menu channel for your media player using the tools already available in your workspace.

## Prerequisites

✅ **Already Available in Your Workspace:**
- `CustomizeMii.exe` - For creating channel banners and WAD files
- `ShowMiiWads.exe` - Alternative WAD creation tool
- `libWiiSharp.dll` - Required library for WAD operations

## Step-by-Step Process

### Step 1: Build the Application
First, ensure your media player application is compiled:

**Windows:**
```cmd
cd apps\WiiMediaPlayerChannel
build_channel.bat
```

**Linux/Mac:**
```bash
cd apps/WiiMediaPlayerChannel
chmod +x build_channel.sh
./build_channel.sh
```

This will create:
- `build/boot.dol` - The compiled application
- `00000000.app` - The channel application file

### Step 2: Create Channel Assets

#### A. Channel Icon (icon.png)
Create a 128x128 pixel PNG image:
- Use any image editor (GIMP, Photoshop, Paint.NET, etc.)
- Design should represent media playback
- Save as `icon.png` in the channel directory

#### B. Channel Banner (banner.bin)
Using CustomizeMii:

1. **Open CustomizeMii.exe**
2. **Create New Channel Project:**
   - Click "New" or "Create Channel"
   - Set Title ID: `000100014D454450`
   - Set Channel Name: "Wii Media Player"

3. **Import Application:**
   - Click "Import DOL" or "Add Application"
   - Select your `build/boot.dol` file
   - This becomes the `00000000.app` file

4. **Create Banner:**
   - Click "Banner Editor" or "Edit Banner"
   - Design a 170x42 pixel banner
   - Add text: "Wii Media Player"
   - Add media-related graphics (play button, music notes, etc.)
   - Save as `banner.bin`

5. **Set Icon:**
   - Click "Icon Editor" or "Edit Icon"
   - Import your `icon.png` file
   - Adjust if needed

6. **Set Metadata:**
   - Copy the content from `meta.xml` into the metadata section
   - Set version to 1.0
   - Set region to "JPN" (Japanese)

### Step 3: Create the WAD File

#### Using CustomizeMii (Recommended)
1. **Build WAD:**
   - Click "Build WAD" or "Create WAD"
   - Choose output location
   - Name it `WiiMediaPlayer.wad`

2. **Verify WAD:**
   - The tool should show "WAD created successfully"
   - Check that the file size is reasonable (2-5 MB)

#### Alternative: Using ShowMiiWads
1. **Open ShowMiiWads.exe**
2. **Create New Channel:**
   - File → New Channel
   - Set Title ID: `000100014D454450`

3. **Import Files:**
   - Import `00000000.app` (your boot.dol)
   - Import `banner.bin`
   - Import `icon.png`
   - Import `meta.xml`

4. **Export WAD:**
   - File → Export → WAD
   - Save as `WiiMediaPlayer.wad`

### Step 4: Install on Wii

#### Method 1: WAD Manager Installation
1. **Copy WAD to SD Card:**
   - Copy `WiiMediaPlayer.wad` to your SD card
   - Place in a folder like `wads/` or root directory

2. **Install on Wii:**
   - Insert SD card into Wii
   - Launch Homebrew Channel
   - Run a WAD Manager (Wii Mod Lite, YAWMM, etc.)
   - Navigate to your WAD file
   - Select "Install"
   - Confirm installation

3. **Verify Installation:**
   - Return to Wii System Menu
   - Look for "Wii Media Player" channel
   - It should appear with your custom icon

#### Method 2: USB Installation
1. **Copy WAD to USB Drive:**
   - Copy `WiiMediaPlayer.wad` to USB drive
   - Use a USB-compatible WAD manager

2. **Install from USB:**
   - Follow same steps as SD card method
   - Select USB as source instead of SD

## Troubleshooting

### Common Issues

**WAD Won't Install:**
- Check that your Wii has Homebrew Channel
- Try a different WAD manager
- Verify WAD file isn't corrupted
- Check Wii system menu version compatibility

**Channel Crashes on Launch:**
- Rebuild the application with debug symbols
- Test the standalone application first
- Check that all libraries are properly linked

**Banner/Icon Not Showing:**
- Verify banner.bin was created properly
- Check icon.png is exactly 128x128 pixels
- Recreate the WAD file

**CustomizeMii Errors:**
- Ensure all required DLLs are present
- Run as administrator if needed
- Check file permissions

### File Verification

After building, verify these files exist:
```
WiiMediaPlayerChannel/
├── build/
│   └── boot.dol          # Compiled application
├── 00000000.app          # Channel application
├── icon.png              # Channel icon (128x128)
├── banner.bin            # Channel banner
├── meta.xml              # Channel metadata
└── WiiMediaPlayer.wad    # Final WAD file
```

## Advanced Customization

### Custom Title ID
You can change the title ID in `channel_config.txt`:
```
TITLE_ID=000100014D454450  # Change this if needed
```

### Custom Banner Animation
In CustomizeMii banner editor:
- Add multiple frames for animation
- Set frame timing
- Export animated banner

### Channel Placement
The channel will appear on your Wii's main menu. You can:
- Move it to different pages
- Arrange with other channels
- Create channel folders (if supported)

## Success Indicators

✅ **Successful Installation:**
- Channel appears on Wii System Menu
- Custom icon displays correctly
- Banner shows when hovering over channel
- Channel launches without errors
- All media player features work

## Next Steps

After successful installation:
1. Test all media player features
2. Create playlists and test M3U support
3. Try video effects and bookmarks
4. Share with other Wii users
5. Consider creating additional channels for other applications

## Support

If you encounter issues:
1. Check this troubleshooting guide
2. Review the main README.md
3. Test with the standalone application first
4. Consult Wii homebrew development forums
