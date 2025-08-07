# Contributing to Wii Media Zone 🎮

Thank you for your interest in contributing to Wii Media Zone! This document provides guidelines and information for contributors.

## 🤝 How to Contribute

### Reporting Issues
- Use the GitHub issue tracker
- Provide detailed information about the problem
- Include steps to reproduce the issue
- Mention your Wii region and system menu version

### Suggesting Features
- Open a feature request issue
- Describe the feature in detail
- Explain why it would be useful
- Consider implementation complexity

### Code Contributions
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly on a Wii
5. Commit your changes (`git commit -m 'Add amazing feature'`)
6. Push to the branch (`git push origin feature/amazing-feature`)
7. Open a Pull Request

## 🛠️ Development Setup

### Prerequisites
- **devkitPPC** - PowerPC development kit
- **libogc** - Wii development library
- **A Wii with homebrew channel** - For testing

### Building
```bash
# Build HelloWii
cd apps/HelloWii
make

# Build WiiMediaPlayer
cd apps/WiiMediaPlayer
make

# Build WiiMediaPlayerChannel
cd apps/WiiMediaPlayerChannel
make
```

## 📝 Coding Standards

### C Code Style
- Use 4-space indentation
- Use descriptive variable and function names
- Add comments for complex logic
- Follow the existing code style in each file

### File Organization
- Keep source files in `source/` directories
- Use header files for function declarations
- Organize related functionality into modules

### Wii-Specific Guidelines
- Always check for NULL pointers
- Handle Wii Remote disconnections gracefully
- Use proper memory management
- Test on both NTSC and PAL Wiis

## 🧪 Testing

### Required Testing
- Test on actual Wii hardware
- Test with different Wii regions (NTSC, PAL, JPN)
- Test with various file formats
- Test edge cases (large files, corrupted files, etc.)

### Testing Checklist
- [ ] Application compiles without warnings
- [ ] Application runs on Wii
- [ ] All features work as expected
- [ ] No memory leaks
- [ ] Handles errors gracefully
- [ ] Works with Japanese Wii (if applicable)

## 📋 Pull Request Guidelines

### Before Submitting
- [ ] Code compiles without errors
- [ ] All tests pass
- [ ] Documentation is updated
- [ ] No new warnings are introduced
- [ ] Code follows style guidelines

### Pull Request Template
```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Code refactoring

## Testing
- [ ] Tested on NTSC Wii
- [ ] Tested on PAL Wii
- [ ] Tested on Japanese Wii
- [ ] Tested with various file formats

## Screenshots (if applicable)
Add screenshots of UI changes

## Additional Notes
Any additional information
```

## 🏷️ Commit Message Guidelines

Use clear, descriptive commit messages:
- Use present tense ("Add feature" not "Added feature")
- Use imperative mood ("Move cursor" not "Moves cursor")
- Limit first line to 72 characters
- Reference issues when applicable

Examples:
```
Add M3U playlist support
Fix memory leak in decoder
Update Japanese Wii compatibility
```

## 🎯 Areas for Contribution

### High Priority
- Bug fixes and stability improvements
- Performance optimizations
- Additional file format support
- Enhanced UI/UX

### Medium Priority
- New video/audio effects
- Additional playlist formats
- Network streaming support
- Save state functionality

### Low Priority
- Additional themes/skins
- Plugin system
- Advanced configuration options
- Additional language support

## 📞 Getting Help

- **GitHub Issues**: For bugs and feature requests
- **GitHub Discussions**: For general questions
- **Wii Homebrew Community**: For Wii-specific questions

## 🙏 Recognition

Contributors will be recognized in:
- The project README
- Release notes
- GitHub contributors page

Thank you for contributing to Wii Media Zone! 🎮
