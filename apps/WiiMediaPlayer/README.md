# WiiMediaPlayer - Advanced Wii Homebrew Media Player

A comprehensive media player application for the Nintendo Wii that supports both video and audio playback with advanced features, M3U playlist support, custom video effects, and enhanced playback controls.

## 🎮 Advanced Features

### 🎵 M3U Playlist Support
- **Full M3U/M3U8 Support**: Load and save standard M3U playlists
- **Extended M3U**: Support for #EXTINF tags with duration and metadata
- **Playlist Management**: Create, edit, and organize playlists
- **Auto-Generated Playlists**: Favorites, Recently Played, Videos, Music
- **Playlist Operations**: Shuffle, sort by name/duration, loop modes
- **Smart Playlist Loading**: Auto-load playlists from SD card

### 🎬 Custom Movie Features
- **Video Filters**: Brightness, contrast, saturation, gamma, sharpness
- **Advanced Effects**: Sepia, grayscale, invert colors, blur effects
- **Real-time Processing**: Apply effects during playback
- **Aspect Ratio Control**: Auto, 4:3, 16:9, stretch modes
- **Deinterlacing**: Remove interlacing artifacts
- **Noise Reduction**: Reduce video noise and artifacts

### 📚 Bookmark System
- **Smart Bookmarks**: Save and jump to specific timestamps
- **Bookmark Management**: Add, remove, and organize bookmarks
- **Auto Bookmarks**: Create bookmarks during playback
- **Bookmark Export**: Save bookmarks to files
- **Quick Access**: Jump to bookmarks from menu

### 🎛️ Enhanced Playback Controls
- **Variable Speed**: Slow motion, fast forward, custom speeds
- **Frame Stepping**: Step through video frame by frame
- **Reverse Playback**: Play videos in reverse
- **Loop Modes**: No loop, single file, entire playlist
- **Auto Play**: Automatically play next file
- **Position Memory**: Remember playback positions

### 📸 Media Tools
- **Screenshot Capture**: Take screenshots during playback
- **Thumbnail Generation**: Create video thumbnails
- **Audio Extraction**: Extract audio from video files
- **Subtitle Merging**: Burn subtitles into videos
- **Subtitle Overlay**: Display external subtitle files

### ⚙️ Advanced Settings
- **Multi-page Settings**: Playback, video, and audio settings
- **Audio Sync**: Adjust audio/video synchronization
- **Equalizer**: Audio equalizer controls
- **Default Volume**: Set default playback volume
- **Subtitle Styling**: Font size, color, outline options

## 📋 Requirements

### Development Requirements
1. **devkitPPC** - PowerPC development kit
2. **libogc** - Open GameCube/Wii library
3. **libfat** - FAT filesystem support
4. **asndlib** - Audio library
5. **math library** - For advanced video effects

### Runtime Requirements
1. **Wii with Homebrew Channel** - To run the application
2. **SD Card** - For storing media files and playlists
3. **Wii Remote** - For navigation and control

## 🛠️ Building

### Prerequisites
1. Install devkitPPC development environment
2. Set `DEVKITPRO` environment variable
3. Ensure all required libraries are installed

### Build Commands
```bash
# Standard build
make

# Debug build with extra debugging info
make debug

# Optimized release build
make release

# Clean build files
make clean
```

### Build Output
- `WiiMediaPlayer.elf` - ELF executable
- `WiiMediaPlayer.dol` - DOL file ready for Wii

## 📁 Installation

### SD Card Setup
1. Create directory structure on SD card:
   ```
   SD:/apps/WiiMediaPlayer/
   ├── boot.dol
   ├── meta.xml
   └── icon.png (optional)
   ```

2. Copy the generated `WiiMediaPlayer.dol` to `boot.dol`
3. Copy `meta.xml` to the same directory
4. Insert SD card into Wii

### Media Files & Playlists
Place your media files and playlists on the SD card:
```
SD:/videos/          # Video files
SD:/music/           # Audio files
SD:/media/           # Mixed media files
SD:/playlists/       # M3U playlist files
SD:/screenshots/     # Screenshots (auto-created)
SD:/bookmarks/       # Bookmark files (auto-created)
```

## 🎯 Usage

### Main Menu
- **File Browser**: Browse and play media files
- **Playlist**: Manage and play M3U playlists
- **Settings**: Configure player options (3 pages)
- **Bookmarks**: Manage playback bookmarks
- **Video Effects**: Apply real-time video filters
- **Exit**: Return to Homebrew Channel

### File Browser
- Navigate through directories with D-Pad
- Select files with A button
- Return to menu with B button
- Files are color-coded: [VIDEO] in green, [AUDIO] in blue

### Enhanced Player Controls
- **A Button**: Play/Pause
- **B Button**: Stop and return to menu
- **D-Pad Left/Right**: Seek backward/forward
- **+/- Buttons**: Volume up/down
- **1 Button**: Add bookmark
- **2 Button**: Take screenshot
- **Z Button**: Toggle slow motion
- **C Button**: Toggle fast forward
- **HOME Button**: Exit application

### Playlist Features
- **Load M3U Files**: Automatically loads .m3u and .m3u8 files
- **Shuffle Play**: Randomize playlist order
- **Sort Options**: Sort by name or duration
- **Loop Modes**: No loop, single file, entire playlist
- **Playlist Navigation**: Next/previous track controls

### Video Effects
- **Real-time Filters**: Apply during playback
- **Adjustable Parameters**: Fine-tune effect settings
- **Preset Effects**: Sepia, grayscale, invert, blur
- **Custom Settings**: Save and load effect presets

### Bookmark System
- **Quick Bookmarks**: Press 1 during playback
- **Named Bookmarks**: Create with custom names
- **Time Stamps**: Jump to exact positions
- **Bookmark List**: View and manage all bookmarks

## 🔧 Technical Details

### Architecture
- **Modular Design**: Separate modules for playlists, effects, and features
- **State Machine**: Clean state management for all screens
- **Memory Management**: Efficient allocation and cleanup
- **File System**: FAT32 support with auto-directory creation

### Supported Formats
- **Video**: MP4, AVI, MKV (with decoder libraries)
- **Audio**: MP3, WAV, OGG (with decoder libraries)
- **Playlists**: M3U, M3U8 (full support)
- **Subtitles**: SRT, ASS (basic support)

### Performance
- **Optimized Rendering**: Hardware-accelerated graphics
- **Real-time Effects**: Efficient video processing
- **Memory Efficient**: Minimal memory footprint
- **Fast Loading**: Quick playlist and file scanning

## 🚀 Advanced Features

### M3U Playlist Engine
- **Standard Compliance**: Full M3U/M3U8 specification support
- **Extended Info**: Parse #EXTINF duration and metadata
- **Auto-discovery**: Find playlists in playlists directory
- **Smart Loading**: Handle relative and absolute paths

### Video Processing Pipeline
- **Real-time Filters**: Apply effects during playback
- **Hardware Optimization**: Use Wii's graphics capabilities
- **Quality Preservation**: Maintain video quality during processing
- **Effect Combinations**: Apply multiple effects simultaneously

### Bookmark System
- **Persistent Storage**: Save bookmarks to files
- **Smart Organization**: Auto-categorize bookmarks
- **Quick Access**: Jump to bookmarks instantly
- **Export/Import**: Share bookmarks between sessions

### Enhanced UI
- **Multi-page Navigation**: Organized settings and features
- **Visual Feedback**: Color-coded file types and states
- **Intuitive Controls**: Wii Remote optimized interface
- **Status Information**: Display current settings and state

## 🐛 Troubleshooting

### Build Issues
1. **Missing devkitPPC**: Install devkitPPC development environment
2. **Library errors**: Ensure all required libraries are installed
3. **Math library**: Add `-lm` to linker flags for video effects

### Runtime Issues
1. **No files found**: Check SD card format (FAT32) and file locations
2. **Playlist not loading**: Verify M3U file format and paths
3. **Effects not working**: Check video format compatibility
4. **Bookmarks not saving**: Ensure write permissions on SD card

### Common Solutions
- Format SD card as FAT32
- Place media files in accessible directories
- Use supported file formats
- Check file permissions and corruption
- Create playlists directory manually if needed

## 📄 License

This is a homebrew application for educational and personal use. Feel free to modify and distribute according to your needs.

## 🤝 Contributing

Contributions are welcome! Areas for improvement:
- Additional codec support
- More video effects and filters
- Enhanced playlist features
- Performance optimizations
- UI/UX enhancements

## 📞 Support

For issues and questions:
1. Check the troubleshooting section
2. Review the source code comments
3. Test with different file formats
4. Verify Wii and SD card compatibility

---

**Note**: This is an advanced media player framework with comprehensive features. For full media playback, additional decoder libraries (like libmad for MP3, libavcodec for video) would need to be integrated.
