# Wii Media Zone 🎮
       
A comprehensive collection of Nintendo Wii homebrew applications and tools focused on media playback and entertainment.
       
## 📁 Project Overview

This repository contains several Wii homebrew applications:

### 🎵 WiiMediaPlayer
A comprehensive media player supporting video and audio playback with advanced features like M3U playlists, video effects, and bookmarks.



### 👋 HelloWii
A simple "Hello World" style application demonstrating basic Wii homebrew development concepts.

### 📺 WiiMediaPlayerChannel
A Wii System Menu channel version of the media player for easy access.

## 🚀 Quick Start

### Prerequisites
- **Wii with Homebrew Channel** installed
- **SD Card** with apps folder
- **devkitPPC** (for building from source)

### Installation
1. **Download** the desired `.dol` files from releases
2. **Copy** to `SD:/apps/[ApplicationName]/`
3. **Run** from Homebrew Channel

## 🎮 Controls



### WiiMediaPlayer Controls
- **D-Pad**: Navigate file browser and menus
- **A Button**: Play/pause, select
- **B Button**: Stop, go back
- **+/-**: Volume control
- **1/2**: Bookmark, screenshot
- **Z/C**: Slow motion, fast forward

## 🌟 Key Features



### WiiMediaPlayer Features
- **Video & Audio Support**: Multiple format playback
- **M3U Playlist Support**: Load and manage playlists
- **Video Effects**: Brightness, contrast, saturation, filters
- **Bookmark System**: Save and jump to positions
- **Advanced Controls**: Variable speed, frame stepping

## 🇯🇵 Japanese Wii Support

All applications include full Japanese Wii compatibility:
- **Region Detection**: Automatic Japanese Wii detection
- **Japanese UI**: Localized interface text
- **Japanese Filenames**: Support for Japanese characters
- **Japanese Playlists**: M3U files with Japanese metadata

## 🛠️ Development

### Building from Source
```bash
# Clone the repository
git clone https://github.com/Colin869/Wii-Media-Zone.git
cd Wii-Media-Zone

# Build specific application
cd apps/WiiMediaPlayer
make

# Or build all applications
cd ..
make -C apps/WiiMediaPlayer
make -C apps/HelloWii
```

### Requirements
- **devkitPPC**: PowerPC development kit
- **libogc**: Wii development library
- **libfat**: FAT filesystem support

## 📚 Documentation

Each application includes detailed documentation:
- **README.md**: Usage guide and features
- **Controls**: Detailed control schemes
- **Installation**: Step-by-step setup
- **Troubleshooting**: Common issues and solutions

## 🔗 Links

- **GitHub Repository**: https://github.com/Colin869/Wii-Media-Zone

- **Homebrew Channel**: https://hbc.hackmii.com/
- **devkitPro**: https://devkitpro.org/

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

---

**Note**: These applications are for educational and personal use only. Please ensure you comply with all applicable laws and Nintendo's terms of service.
