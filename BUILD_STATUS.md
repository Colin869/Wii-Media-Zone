# Build Status and Instructions 🛠️

## 🔧 Current Build Status

**GitHub Actions Status**: ⚠️ **Currently Failing**

The automated GitHub Actions build is currently experiencing issues with the devkitPPC installation process. This is a common issue with Wii homebrew development in CI/CD environments.

## 🎯 Why This Happens

1. **devkitPPC Installation**: The devkitPro pacman installer can be finicky in automated environments
2. **Dependencies**: Some required libraries may not be available in the GitHub Actions environment
3. **Cross-compilation**: Wii development requires PowerPC cross-compilation tools

## 🚀 Alternative Build Methods

### Method 1: Local Build (Recommended)

The most reliable way to build these applications is on your local machine:

#### Prerequisites
- **Windows**: Install devkitPro with devkitPPC
- **Linux**: Use the devkitPro pacman installer
- **macOS**: Use the devkitPro pacman installer

#### Build Steps
```bash
# Clone the repository
git clone https://github.com/Colin869/Wii-Media-Zone.git
cd Wii-Media-Zone

# Build HelloWii
cd apps/HelloWii
make

# Build WiiMediaPlayer
cd ../WiiMediaPlayer
make

# Build WiiMediaPlayerChannel
cd ../WiiMediaPlayerChannel
make
```

### Method 2: Docker Build (Experimental)

We're working on a Docker-based build solution:

```bash
# Pull the devkitPro Docker image (when available)
docker pull devkitpro/devkitppc:latest

# Build using Docker
docker run --rm -v $(pwd):/workspace devkitpro/devkitppc:latest bash -c "cd /workspace/apps/HelloWii && make"
```

### Method 3: Pre-built Binaries

For users who don't want to build from source, we're working on providing pre-built binaries in the releases section.

## 📋 Build Requirements

### Required Tools
- **devkitPPC** - PowerPC development kit
- **libogc** - Wii development library
- **libfat** - File system support
- **asndlib** - Audio support (for media player)

### Environment Variables
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITPPC=/opt/devkitpro/devkitPPC
export PATH=/opt/devkitpro/devkitPPC/bin:$PATH
```

## 🔍 Troubleshooting

### Common Issues

1. **"powerpc-eabi-gcc not found"**
   - Solution: Ensure devkitPPC is properly installed
   - Check PATH environment variable

2. **"libogc not found"**
   - Solution: Install libogc via devkitPro pacman
   - Run: `sudo dkp-pacman -S libogc`

3. **"make: command not found"**
   - Solution: Install build tools
   - Ubuntu/Debian: `sudo apt-get install build-essential`
   - Windows: Install MinGW or use devkitPro

4. **"Permission denied"**
   - Solution: Use sudo for installation steps
   - Ensure proper file permissions

### Getting Help

- **GitHub Issues**: Report build problems
- **devkitPro Discord**: Get help from the community
- **Wii Homebrew Forums**: Find solutions from other developers

## 📈 Future Improvements

We're working on:

1. **Fixed GitHub Actions**: Resolving the CI/CD build issues
2. **Docker Support**: Containerized build environment
3. **Pre-built Binaries**: Ready-to-use .dol files
4. **Build Scripts**: Automated local build scripts

## 🎮 Quick Start (No Build Required)

If you just want to try the applications:

1. **Download from Releases** (when available)
2. **Copy .dol files** to your SD card's `apps/` directory
3. **Run from Homebrew Channel** on your Wii

## 📞 Support

- **Build Issues**: Open a GitHub issue with your system details
- **Runtime Issues**: Include your Wii region and system menu version
- **Feature Requests**: Use the GitHub issue tracker

---

**Note**: The source code is fully functional and builds successfully on properly configured development machines. The GitHub Actions issues are related to the CI/CD environment setup, not the code itself.
