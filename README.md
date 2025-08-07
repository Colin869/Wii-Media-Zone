# Wii Media Zone 🎮

A comprehensive collection of Nintendo Wii homebrew applications and tools focused on media playback and entertainment.

## 📁 Project Overview

This repository contains several Wii homebrew applications and development tools:

### 🎵 Applications

#### 1. **HelloWii** - Basic Homebrew Example
- **Location**: `apps/HelloWii/`
- **Description**: A simple "Hello World" style homebrew application demonstrating basic Wii development concepts
- **Features**: Graphics rendering, Wii Remote input handling, console output
- **Perfect for**: Learning Wii homebrew development basics

#### 2. **WiiMediaPlayer** - Advanced Media Player
- **Location**: `apps/WiiMediaPlayer/`
- **Description**: A comprehensive media player supporting video and audio playback
- **Features**:
  - 🎬 Video and audio playback
  - 📁 File browser with thumbnails
  - 📋 M3U/M3U8 playlist support
  - 🎨 Advanced video effects and filters
  - 🔖 Bookmark system
  - ⚙️ Customizable playback settings
  - 🎯 Japanese Wii region support
  - 🎮 Enhanced Wii Remote controls

#### 3. **WiiMediaPlayerChannel** - Wii Menu Channel
- **Location**: `apps/WiiMediaPlayerChannel/`
- **Description**: A Wii System Menu channel version of the media player
- **Features**:
  - 🏠 Direct access from Wii menu
  - 🇯🇵 Japanese region compatibility
  - 🎨 Custom channel banner and icon
  - 📦 WAD installation ready

### 🛠️ Tools Included

- **CustomizeMii.exe** - Channel creation and customization tool
- **ShowMiiWads.exe** - WAD file management tool
- **WIT (Wii ISO Tools)** - Wii ISO and WAD manipulation
- **Various utilities** for Wii development and file management

## 🚀 Quick Start

### Prerequisites
- **devkitPPC** - PowerPC development kit
- **libogc** - Wii development library
- **A Wii with homebrew channel** - To run the applications

### Building Applications

#### HelloWii
```bash
cd apps/HelloWii
make
```

#### WiiMediaPlayer
```bash
cd apps/WiiMediaPlayer
make
```

#### WiiMediaPlayerChannel
```bash
cd apps/WiiMediaPlayerChannel
./build_channel.bat  # Windows
./build_channel.sh   # Linux/Mac
```

### Installation

1. **Copy the .dol file** to your SD card in the `apps/` directory
2. **Run from Homebrew Channel** on your Wii
3. **For the channel version**: Install the WAD file using a WAD manager

## 🎮 Controls

### WiiMediaPlayer Controls
- **D-Pad**: Navigate menus
- **A Button**: Select/Play
- **B Button**: Back/Stop
- **+/-**: Volume control
- **1/2**: Screenshot/Slow motion
- **Z/C**: Bookmark/Fast forward
- **HOME**: Return to Wii menu

## 🌟 Key Features

### Advanced Media Playback
- **Multi-format support**: MP3, WAV, OGG, MP4, AVI, MKV
- **Playlist management**: Create, edit, and organize playlists
- **Video effects**: Brightness, contrast, saturation, gamma, filters
- **Bookmark system**: Save and jump to specific positions
- **Enhanced controls**: Variable speed, frame stepping, reverse playback

### Japanese Wii Support
- **Region detection**: Automatically detects Japanese Wii
- **Japanese UI**: Displays Japanese text when appropriate
- **Japanese filenames**: Full support for Japanese file names
- **Localized messages**: Japanese system messages

### Development Features
- **Modular design**: Clean, maintainable code structure
- **Comprehensive documentation**: Detailed guides and READMEs
- **Build automation**: Scripts for easy compilation
- **Cross-platform**: Works on Windows, Linux, and Mac

## 📚 Documentation

Each application has its own detailed documentation:

- [HelloWii Documentation](apps/HelloWii/README.md)
- [WiiMediaPlayer Documentation](apps/WiiMediaPlayer/README.md)
- [WiiMediaPlayerChannel Documentation](apps/WiiMediaPlayerChannel/README.md)
- [Japanese Wii Guide](apps/WiiMediaPlayerChannel/JAPANESE_WII_GUIDE.md)

## 🔧 Development

### Project Structure
```
Wii Media Zone/
├── apps/
│   ├── HelloWii/              # Basic homebrew example
│   ├── WiiMediaPlayer/        # Advanced media player
│   └── WiiMediaPlayerChannel/ # Wii menu channel
├── external/                  # External tools and libraries
├── Tools/                     # Wii development utilities
└── README.md                  # This file
```

### Contributing
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly on a Wii
5. Submit a pull request

## 📄 License

This project is open source. Please check individual application directories for specific license information.

## 🙏 Acknowledgments

- **devkitPro team** - For the excellent Wii development tools
- **libogc developers** - For the Wii development library
- **Wii homebrew community** - For inspiration and support

## 🔗 Links

- **GitHub Repository**: https://github.com/Colin869/Wii-Media-Zone
- **devkitPro**: https://devkitpro.org/
- **Wii Homebrew Community**: Various forums and Discord servers

---

**Made with ❤️ for the Wii homebrew community**

*Enjoy your media on the Nintendo Wii! 🎮*
