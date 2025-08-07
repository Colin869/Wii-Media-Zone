# Mii Pants Color Changer 🎨

A homebrew application for the Nintendo Wii that allows you to change the pants colors of your Mii characters. Customize your Miis with colors not available in the standard Wii Mii Channel!

## 🌟 Features

### 🎨 Color Customization
- **16 Different Colors**: Red, Orange, Yellow, Lime, Green, Teal, Cyan, Blue, Navy, Purple, Magenta, Pink, Brown, Maroon, Olive, Gray
- **Real-time Preview**: See changes before saving
- **Before/After Comparison**: View original vs modified Miis side by side

### 🎮 User Interface
- **Intuitive Controls**: Simple D-pad navigation
- **Japanese Support**: Full Japanese Wii compatibility
- **Visual Color Grid**: Easy color selection with visual swatches
- **Mii List**: Browse and select from all your Miis

### 🔧 Technical Features
- **NAND Access**: Reads and writes Mii data directly from Wii NAND
- **Safe Operations**: Backup original Mii data before modifications
- **Progress Indicators**: Visual feedback during save operations
- **Error Handling**: Graceful handling of file operations

## 🎮 Controls

### Main Menu
- **D-Pad**: Navigate options
- **A Button**: Select option
- **HOME**: Return to Wii menu

### Mii Selection
- **D-Pad Up/Down**: Navigate Mii list
- **A Button**: Select Mii
- **B Button**: Go back to menu

### Color Selection
- **D-Pad**: Navigate color grid (4x4 layout)
- **A Button**: Apply selected color
- **B Button**: Go back to Mii selection

### Preview Screen
- **A Button**: Save changes
- **B Button**: Cancel and go back

### Success Screen
- **A Button**: Continue to main menu
- **HOME**: Exit application

## 🚀 Installation

### Prerequisites
- **Wii with Homebrew Channel** installed
- **SD Card** with apps folder
- **devkitPPC** (for building from source)

### Quick Install
1. **Download** the `.dol` file
2. **Copy** to `SD:/apps/MiiPantsChanger/`
3. **Run** from Homebrew Channel

### Building from Source
```bash
# Clone the repository
git clone https://github.com/Colin869/Wii-Media-Zone.git
cd Wii-Media-Zone/apps/MiiPantsChanger

# Build the application
make

# Copy to SD card
cp MiiPantsChanger.dol /path/to/sd/card/apps/MiiPantsChanger/
```

## 📋 Usage Guide

### Step 1: Launch Application
1. Insert SD card with the application
2. Open Homebrew Channel
3. Select "Mii Pants Color Changer"
4. Wait for initialization

### Step 2: Select a Mii
1. Choose "Select Mii" from main menu
2. Browse through your Mii list
3. Current pants color is shown next to each Mii
4. Select the Mii you want to modify

### Step 3: Choose New Color
1. Navigate the 4x4 color grid using D-pad
2. Each color shows a preview swatch
3. Select your desired pants color
4. Press A to apply the color

### Step 4: Preview Changes
1. View side-by-side comparison
2. Original Mii on the left
3. Modified Mii on the right
4. Press A to save or B to cancel

### Step 5: Save Changes
1. Application shows save progress
2. Wait for completion message
3. Changes are now permanent
4. Check Wii Menu to see updated Mii

## 🔧 Technical Details

### Mii Data Structure
The application works with the Wii's Mii data format:
- **File Location**: NAND filesystem
- **Data Format**: Binary Mii structure
- **Size**: 74 bytes per Mii
- **Checksums**: Automatically updated

### Supported Colors
| Color | RGB Value | Description |
|-------|-----------|-------------|
| Red | #FF0000 | Classic red |
| Orange | #FF8000 | Bright orange |
| Yellow | #FFFF00 | Bright yellow |
| Lime | #80FF00 | Lime green |
| Green | #00FF00 | Bright green |
| Teal | #008080 | Teal blue |
| Cyan | #00FFFF | Bright cyan |
| Blue | #0000FF | Classic blue |
| Navy | #000080 | Dark blue |
| Purple | #8000FF | Bright purple |
| Magenta | #FF00FF | Bright magenta |
| Pink | #FF80FF | Light pink |
| Brown | #804000 | Dark brown |
| Maroon | #800000 | Dark red |
| Olive | #808000 | Olive green |
| Gray | #808080 | Medium gray |

### File Operations
- **Reading**: Loads Mii data from NAND
- **Modification**: Updates pants color byte
- **Writing**: Saves modified data back to NAND
- **Backup**: Preserves original data

## 🛡️ Safety Features

### Data Protection
- **Automatic Backups**: Original Mii data is preserved
- **Validation**: Checks data integrity before saving
- **Error Recovery**: Graceful handling of file errors
- **Safe Mode**: Won't overwrite critical system files

### Compatibility
- **Wii Regions**: NTSC, PAL, JPN (Japanese)
- **System Menu**: 4.0 and higher
- **Mii Channel**: Compatible with all versions
- **Homebrew Channel**: Works with all versions

## 🔍 Troubleshooting

### Common Issues

#### "No Miis Found"
- **Cause**: No Mii data in NAND
- **Solution**: Create Miis in Mii Channel first

#### "Save Failed"
- **Cause**: NAND write protection or corruption
- **Solution**: Check NAND health, try again

#### "Application Freezes"
- **Cause**: Memory or file system issues
- **Solution**: Restart Wii, check SD card

#### "Colors Not Showing"
- **Cause**: Display or video mode issues
- **Solution**: Check TV settings, try different video mode

### Getting Help
- **GitHub Issues**: Report bugs and problems
- **Wii Homebrew Forums**: Community support
- **Discord**: Real-time help from developers

## 📈 Future Enhancements

### Planned Features
- **Shirt Color Changer**: Modify shirt colors too
- **Shoe Color Changer**: Customize shoe colors
- **Batch Operations**: Change multiple Miis at once
- **Custom Colors**: RGB color picker
- **Patterns**: Add patterns and textures
- **Export/Import**: Save and share custom Miis

### Technical Improvements
- **Better UI**: Enhanced graphics and animations
- **Faster Loading**: Optimized file operations
- **More Colors**: Extended color palette
- **3D Preview**: Real 3D Mii rendering

## 🙏 Acknowledgments

- **Nintendo**: For the Wii platform and Mii system
- **devkitPro Team**: For excellent development tools
- **Wii Homebrew Community**: For inspiration and support
- **Mii Research Community**: For Mii data format documentation

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](../LICENSE) file for details.

## 🔗 Links

- **GitHub Repository**: https://github.com/Colin869/Wii-Media-Zone
- **Homebrew Channel**: https://hbc.hackmii.com/
- **devkitPro**: https://devkitpro.org/

---

**Made with ❤️ for the Wii homebrew community**

*Customize your Miis like never before! 🎨*
